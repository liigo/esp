#include "esp_globals.h"
#include <apr_general.h>
#include "esp_log.h"

void ESP_Initialize()
{
	apr_initialize();
	atexit(apr_terminate);

	ESP_LOG_INIT();
	ESP_CORE_LOG((LOG_INFO, "ESP_Initialize()"));


	ESP_GetRootAPRPool();
	ESPGlobals::GetInstance();
}

void ESP_Finalize()
{
	ESP_CORE_LOG((LOG_INFO, "ESP_Finalize()"));
	ESP_LOG_FINIT();
	return;
}

//初始化类静态成员
ESPGlobals* ESPGlobals::m_instance = NULL;

ESPGlobals& ESP_GetGlobals()
{
	static ESPGlobals* s_ESPGlobals = ESPGlobals::GetInstance();
	return *s_ESPGlobals;
}

static void _ESP_DeleteRootAPRPool()
{
	apr_pool_destroy(ESP_GetRootAPRPool());
}

apr_pool_t* ESP_GetRootAPRPool()
{
	static apr_pool_t* s_pool = NULL;
	if(s_pool == NULL)
	{
		apr_status_t status = apr_pool_create(&s_pool, NULL);
		assert(status == APR_SUCCESS && s_pool != NULL);
		atexit(_ESP_DeleteRootAPRPool);
	}
	return s_pool;
}

ESPPage* ESP_AcquirePage(const char* typeName, const char* instanceName, ESPServerAPI* serverApi)
{
	return ESP_GetGlobals().GetObjectManager().AcquirePage(typeName, instanceName, serverApi);
}

void ESP_ReleasePage(ESPPage* page)
{
	ESP_GetGlobals().GetObjectManager().ReleasePage(page);
}
