#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <httpext.h>
#include "../esp-core/esp.h"
#include "espserverapi_impl.h"

static HINSTANCE gs_dllModule = NULL;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if(fdwReason == DLL_PROCESS_ATTACH)
	{
		gs_dllModule = hinstDLL;
	}
	return TRUE;
}

//导出给esp.fne调用
const ESPClientAPI* ESP_GetClientAPI()
{
	return ESPCore_GetClientAPI();
}

BOOL WINAPI GetExtensionVersion(HSE_VERSION_INFO* pVer)
{
	pVer->dwExtensionVersion = 100; //1.00
	strcpy(pVer->lpszExtensionDesc, "ESP extension for IIS");

	//将esp.dll全路径文件名写入指定环境变量, 以便易支持库(esp.fne)读取
	char filepath[MAX_PATH + 1];
	assert(gs_dllModule);
	GetModuleFileName(gs_dllModule, filepath, MAX_PATH + 1);
	SetEnvironmentVariable(ENV_NAME_OF_ESP_MOD_FILE_PATH, filepath);

	ESP_Initialize();
	return TRUE;
}

BOOL WINAPI TerminateExtension(DWORD dwFlags)
{
	ESP_Finalize();
	return TRUE;
}

static output(EXTENSION_CONTROL_BLOCK* pECB, const char* szText)
{
	DWORD x = strlen(szText);
	pECB->WriteClient(pECB->ConnID, (char*)szText, &x, 0);
	x = 2;
	pECB->WriteClient(pECB->ConnID, "\r\n", &x, 0);
}

static bool MapURL2File(EXTENSION_CONTROL_BLOCK* pECB, const char* szScriptName, std::string& filename);

DWORD WINAPI HttpExtensionProc(EXTENSION_CONTROL_BLOCK* pECB)
{
	IISESPServerAPI_Impl espServerAPI(pECB);

	const char* szScriptName = NULL; bool needFreeScriptName = false;
	espServerAPI.GetServerVariable("SCRIPT_NAME", &szScriptName, needFreeScriptName);
	assert(szScriptName);

	std::string espFileName;
	if(MapURL2File(pECB, szScriptName, espFileName) == false)
	{
		if(needFreeScriptName)
			espServerAPI.FreeData(szScriptName);
		return HSE_STATUS_ERROR;
	}

	std::string espFullPageName, espLibName, espPageName;
	if(ESP_ParsePageName(szScriptName, espFullPageName, espLibName, espPageName))
	{
		ESPPage* page = ESP_AcquirePage(espPageName.c_str(), espPageName.c_str(), &espServerAPI);
		if(page)
		{
			page->type_info->esp_template->LoadFile(espFileName.c_str());

			liigo::MemBuffer outBuffer;
			ESPRenderResult renderResult = page->type_info->esp_template->RenderPageTemplate(page, &outBuffer);
			if(renderResult == ESPRenderResult_OK)
			{
				//发送回复头
				char bufferContentLength[16];
				itoa(outBuffer.getDataSize(), bufferContentLength, 10);
				std::string headers;
				headers += "Content-Type: text/html;charset=utf-8\r\n";
				headers += "Content-Length: "; headers += bufferContentLength; headers += "\r\n";
				if(espServerAPI.cookie.size() > 0) //Set-Cookie
				{
					headers += "Set-Cookie: "; headers += espServerAPI.cookie; headers += "\r\n";
				}
				headers += "X-Powered-By: ESP/1.0; Easy Server Pages; http://esp.eyuyan.com\r\n";
				headers += "\r\n";
				espServerAPI.SendResponseHeader(std::string("200 OK"), headers);
				//发送回复体
				DWORD dataSize = outBuffer.getDataSize();
				pECB->WriteClient(pECB->ConnID, outBuffer.getData(), &dataSize, 0);
			}

			ESP_ReleasePage(page);
		}
	}

	if(needFreeScriptName)
		espServerAPI.FreeData(szScriptName);

	return HSE_STATUS_SUCCESS;
}

static bool MapURL2File(EXTENSION_CONTROL_BLOCK* pECB, const char* szScriptName, std::string& filename)
{
	if(szScriptName == NULL || *szScriptName == '\0') return false;
	int n = strlen(szScriptName);
	DWORD nBuffer = n > MAX_PATH ? n : MAX_PATH;
	void* pBuffer = malloc(nBuffer + 1);
	memcpy(pBuffer, szScriptName, n + 1);	
	BOOL bOK = pECB->ServerSupportFunction(pECB->ConnID, HSE_REQ_MAP_URL_TO_PATH, pBuffer, &nBuffer, NULL);
	if(bOK)
		filename = (const char*) pBuffer;
	free(pBuffer);
	return bOK == TRUE;
}

