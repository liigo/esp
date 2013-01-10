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

// 本模块的调试设置：
// 执行程序：C:\Program Files\Apache Software Foundation\Apache2.2\bin\httpd.exe
// 工作目录：C:\Program Files\Apache Software Foundation\Apache2.2\bin
// 运行参数：-X
// 其中 -X 参数表示让Apache以调试模式运行
// by liiigo. 2012-6-12.

static int esp_handler(request_rec *r)
{
	//处理ESP运行时异常 (todo: need move to translate_name hook?)
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

//Apache会先后两次加载模块，第一次加载后立刻卸载，然后很快又加载第二次。这种行为很奇怪。
//但是他们作者认为自己有足够的理由这么做，并且不认为这么做会给mod开发者带来无法解决的麻烦。

static void register_hooks(apr_pool_t *p)
{
	//将mod_esp.so全路径文件名写入环境变量, 以便易支持库(modesp.fne)读取并加载
	apr_env_set(ENV_NAME_OF_ESP_MOD_FILE_PATH, GetESPModuleFileName(), p);

	//初始化ESP
	ESP_Initialize();

	//注册Apache内容生成器esp_handler
	ap_hook_handler(esp_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

//确保退出时执行ESP_Finalize()
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

//导出函数ESP_GetClientAPI(), 供易语言支持库(esp.fne)或其他语言支持库调用
extern "C"
#ifdef WIN32
	__declspec(dllexport)
#endif
const ESPClientAPI* ESP_GetClientAPI()
{
	return ESPCore_GetClientAPI();
}
