#include "esp_utils.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "esp_globals.h"

bool ESP_ParsePageName(const char* szScriptName, std::string& fullPageName, std::string& libName, std::string& pageName)
{
	char* szFullPageName = NULL;
	std::string scriptName = szScriptName;
	const char* pScriptName = scriptName.c_str();
	char* szDot = strrchr(pScriptName, '.');
	if(szDot)
	{
		*szDot = '\0';
		char* pSlash1 = strrchr(pScriptName, '/');
		if(pSlash1)
		{
			pageName = pSlash1 + 1;
			*pSlash1 = '\0';
			char* pSlash2 = strrchr(pScriptName, '/');
			if(pSlash2)
			{
				libName = pSlash2 + 1;
				fullPageName = libName + "." + pageName;
				return true;
			} else {
				libName = "";
				fullPageName = pageName;
				return true;
			}
		}
	}
	return false;
}

// ESPThreadMutex

ESPThreadMutex::ESPThreadMutex(apr_pool_t* pool)
{
	apr_status_t s = apr_thread_mutex_create(&m_mutex, APR_THREAD_MUTEX_DEFAULT, 
											 pool ? pool : ESP_GetRootAPRPool());
	assert(s == APR_SUCCESS);
}

ESPThreadMutex::~ESPThreadMutex()
{
	apr_thread_mutex_destroy(m_mutex);
}
