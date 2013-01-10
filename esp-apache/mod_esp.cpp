#include <string>
#include <apr_strings.h>
#include <apr_env.h>
#include <httpd.h>
#include <http_config.h>
#include <http_core.h>
#include <http_main.h>
#include <http_protocol.h>
#include <http_request.h>
#include <http_connection.h>
#include <http_log.h>

#include "../esp-core/esp.h"
#include "espserverapi_impl.h"
#include "utils.h"

// ��ģ��ĵ������ã�
// ִ�г���C:\Program Files\Apache Software Foundation\Apache2.2\bin\httpd.exe
// ����Ŀ¼��C:\Program Files\Apache Software Foundation\Apache2.2\bin
// ���в�����-X
// ���� -X ������ʾ��Apache�Ե���ģʽ����
// by liiigo. 2012-6-12.

static int esp_handler(request_rec *r)
{
	//����ESP����ʱ�쳣 (todo: need move to translate_name hook?)
	if(r->status == HTTP_INTERNAL_SERVER_ERROR 
		&& strcmp(r->uri, "/esp-runtime-error") == 0)
	{
		ApacheESPServerAPI_Impl espServerAPI(r);
		ESP_ProcessRuntimeError(&espServerAPI);
		return DONE;
	}

	if(apr_strnatcasecmp(r->handler, "esp") != 0 &&
			apr_strnatcasecmp(r->handler, "application/x-esp") != 0)
		return DECLINED;

	ApacheESPServerAPI_Impl espServerAPI(r);
	const char* szScriptName; bool needFreeScriptName;
	espServerAPI.GetScriptName(&szScriptName, needFreeScriptName);

	std::string espFullPageName, espLibName, espPageName;
	if(ESP_ParsePageName(szScriptName, espFullPageName, espLibName, espPageName))
	{
		if(needFreeScriptName) espServerAPI.FreeData(szScriptName);

		ESPPage* page = ESP_AcquirePage(espPageName.c_str(), espPageName.c_str(), &espServerAPI);
		if(page)
		{
			page->type_info->esp_template->LoadFile(r->filename);

			liigo::MemBuffer outBuffer;
			ESPRenderResult renderResult = page->type_info->esp_template->RenderPageTemplate(page, &outBuffer);
			if(renderResult == ESPRenderResult_OK)
			{
				r->content_type = "text/html"; //Content-Type: text/html;charset=utf-8;
				r->clength = outBuffer.getDataSize(); //Content_Length: 
				apr_table_setn(r->headers_out, "X-Powered-By",
						"ESP/1.0; Easy Server Pages; http://esp.eyuyan.com"); //X-Powered-By: 
				ap_rwrite(outBuffer.getData(), outBuffer.getDataSize(), r);
			}

			ESP_ReleasePage(page);
		}
		return DONE;
	}

	if(needFreeScriptName) espServerAPI.FreeData(szScriptName);
	return OK;
}

//Apache���Ⱥ����μ���ģ�飬��һ�μ��غ�����ж�أ�Ȼ��ܿ��ּ��صڶ��Ρ�������Ϊ����֡�
//��������������Ϊ�Լ����㹻��������ô�������Ҳ���Ϊ��ô�����mod�����ߴ����޷�������鷳��

static void register_hooks(apr_pool_t *p)
{
	//��mod_esp.soȫ·���ļ���д�뻷������, �Ա���֧�ֿ�(modesp.fne)��ȡ������
	apr_env_set(ENV_NAME_OF_ESP_MOD_FILE_PATH, GetESPModuleFileName(), p);

	//��ʼ��ESP
	ESP_Initialize();

	//ע��Apache����������esp_handler
	ap_hook_handler(esp_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

//ȷ���˳�ʱִ��ESP_Finalize()
class esp_finalizer
{
public:
	~esp_finalizer()
	{
		ESP_Finalize();
	}
};
static esp_finalizer espfinalizer;


module AP_MODULE_DECLARE_DATA esp_module =
{
	STANDARD20_MODULE_STUFF,
	NULL, /* per-directory config creator */
	NULL, /* dir config merger */
	NULL, /* server config creator */
	NULL, /* server config merger */
	NULL, /* command table */
	register_hooks, /* set up other request processing hooks */
};

//��������ESP_GetClientAPI(), ��������֧�ֿ�(esp.fne)����������֧�ֿ����
extern "C"
#ifdef WIN32
	__declspec(dllexport)
#endif
const ESPClientAPI* ESP_GetClientAPI()
{
	return ESPCore_GetClientAPI();
}
