#include "esp_clientapi.h"
#include <stdlib.h>
#include <memory.h>
#include <apr_tables.h>
#include <apr_pools.h>
#include "esp_objects.h"
#include "esp_log.h"

//ESP_GetClientAPI()的内部实现函数
extern "C" const struct ESPClientAPI* ESPCore_GetClientAPI()
{
	static ESPClientAPI  funcs;
	static ESPClientAPI* pFuncs = NULL;

	if(pFuncs == NULL)
	{
		pFuncs = &funcs;

		memset(&funcs, 0, sizeof(ESPClientAPI));

		funcs.pfn_ESPObject_GetAllPropertyCount = (PFN_ESPObject_GetAllPropertyCount) ESPObject_GetAllPropertyCount;
		funcs.pfn_ESPObject_GetPropertyNames = (PFN_ESPObject_GetPropertyNames) ESPObject_GetPropertyNames;
		funcs.pfn_ESPObject_IsPropertyExist = (PFN_ESPObject_IsPropertyExist) ESPObject_IsPropertyExist;
		funcs.pfn_ESPObject_GetPropertyType = (PFN_ESPObject_GetPropertyType) ESPObject_GetPropertyType;
		funcs.pfn_ESPObject_GetPropertyInfos = (PFN_ESPObject_GetPropertyInfos) ESPObject_GetPropertyInfos;
		funcs.pfn_ESPObject_RemoveAllPropeties = (PFN_ESPObject_RemoveAllPropeties) ESPObject_RemoveAllPropeties;
		funcs.pfn_ESPObject_GetProperty = (PFN_ESPObject_GetProperty) ESPObject_GetProperty;
		funcs.pfn_ESPObject_SetProperty = (PFN_ESPObject_SetProperty) ESPObject_SetProperty;
		funcs.pfn_ESPObject_GetBoolProperty = (PFN_ESPObject_GetBoolProperty) ESPObject_GetBoolProperty;
		funcs.pfn_ESPObject_SetBoolProperty = (PFN_ESPObject_SetBoolProperty) ESPObject_SetBoolProperty;
		funcs.pfn_ESPObject_GetIntProperty = (PFN_ESPObject_GetIntProperty) ESPObject_GetIntProperty;
		funcs.pfn_ESPObject_SetIntProperty = (PFN_ESPObject_SetIntProperty) ESPObject_SetIntProperty;
		funcs.pfn_ESPObject_GetInt64Property = (PFN_ESPObject_GetInt64Property) ESPObject_GetInt64Property;
		funcs.pfn_ESPObject_SetInt64Property = (PFN_ESPObject_SetInt64Property) ESPObject_SetInt64Property;
		funcs.pfn_ESPObject_GetFloatProperty = (PFN_ESPObject_GetFloatProperty) ESPObject_GetFloatProperty;
		funcs.pfn_ESPObject_SetFloatProperty = (PFN_ESPObject_SetFloatProperty) ESPObject_SetFloatProperty;
		funcs.pfn_ESPObject_GetDoubleProperty = (PFN_ESPObject_GetDoubleProperty) ESPObject_GetDoubleProperty;
		funcs.pfn_ESPObject_SetDoubleProperty = (PFN_ESPObject_SetDoubleProperty) ESPObject_SetDoubleProperty;
		funcs.pfn_ESPObject_GetTextProperty = (PFN_ESPObject_GetTextProperty) ESPObject_GetTextProperty;
		funcs.pfn_ESPObject_SetTextProperty = (PFN_ESPObject_SetTextProperty) ESPObject_SetTextProperty;
		funcs.pfn_ESPObject_GetBinaryProperty = (PFN_ESPObject_GetBinaryProperty) ESPObject_GetBinaryProperty;
		funcs.pfn_ESPObject_SetBinaryProperty = (PFN_ESPObject_SetBinaryProperty) ESPObject_SetBinaryProperty;

		funcs.pfn_ESPObject_GetPage = (PFN_ESPObject_GetPage) ESPObject_GetPage;
		funcs.pfn_ESPObject_GetParent = (PFN_ESPObject_GetParent) ESPObject_GetParent;
		funcs.pfn_ESPObject_RuntimeError = (PFN_ESPObject_RuntimeError) ESPObject_RuntimeError;
		funcs.pfn_ESPObject_GetSession = (PFN_ESPObject_GetSession) ESPObject_GetSession;
		funcs.pfn_ESPObject_SetSession = (PFN_ESPObject_SetSession) ESPObject_SetSession;
		funcs.pfn_ESPObject_GetRequestInfo = (PFN_ESPObject_GetRequestInfo) ESPObject_GetRequestInfo;

		funcs.pfn_ESPObject_IsPage = (PFN_ESPObject_IsPage) ESPObject_IsPage;
		funcs.pfn_ESPObject_GetInstanceName = (PFN_ESPObject_GetInstanceName) ESPObject_GetInstanceName;
		funcs.pfn_ESPObject_GetTypeName = (PFN_ESPObject_GetTypeName) ESPObject_GetTypeName;
		funcs.pfn_ESPObject_GetLibraryName = (PFN_ESPObject_GetLibraryName) ESPObject_GetLibraryName;
		funcs.pfn_ESPObject_GetLibraryFile = (PFN_ESPObject_GetLibraryFile) ESPObject_GetLibraryFile;

		funcs.pfn_ESPRenderContext_Output = (PFN_ESPRenderContext_Output) ESPRenderContext_Output;

		funcs.pfn_Log = (PFN_ESP_Log) ESP_Log;
		funcs.pfn_FreeData = (PFN_ESP_FreeData) free;
	}

	return (const ESPClientAPI*) pFuncs;
}
