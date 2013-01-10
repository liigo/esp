#include "esp_objects.h"
#include <assert.h>
#include <string.h>
#include <apr_strings.h>
#include "esp_session.h"
#include "esp_errors.h"
#include "esp_template.h"
#include "esp_globals.h"
#include "esp_clientapi.h"
#include "esp_serverapi.h"
#include "esp_prop.h"
#include "esp_internal.h"
#include "string_util.h"


// 定义ESP对象的基本结构及其基础接口
// by Liigo, before 2009.

using namespace std;

//ESPComponent

ESPPage* ESPComponent_GetPage(ESPComponent* pThis)
{
	return pThis->page;
}

//ESPObject

bool ESPObject_IsPage(ESPObject* pThis)
{
	return (pThis == pThis->page);
}

ESPPage* ESPObject_GetPage(ESPObject* pThis)
{
	return pThis->page;
}

ESPObject* ESPObject_GetParent(ESPObject* pThis)
{
	return pThis->parent;
}

const char* ESPObject_GetInstanceName(ESPObject* pThis)
{
	return pThis->instance_name;
}

const char* ESPObject_GetTypeName(ESPObject* pThis)
{
	return pThis->type_info->type_name;
}

const char* ESPObject_GetLibraryName(ESPObject* pThis)
{
	return pThis->type_info->library->GetName();
}

const char* ESPObject_GetLibraryFile(ESPObject* pThis)
{
	return pThis->type_info->library->GetFileName();
}

size_t ESPObject_GetAllPropertyCount(ESPObject* pThis)
{
	return pThis->props->GetAllPropertyCount();
}

char** ESPObject_GetPropertyNames(ESPObject* pThis, bool includePublic, bool includePrivate, bool includeInformal, size_t* pCount)
{
	return pThis->props->GetPropertyNames(includePublic, includePrivate, includeInformal, *pCount);
}

bool ESPObject_IsPropertyExist(ESPObject* pThis, const char* name, ESPPropType type)
{
	return pThis->props->IsPropertyExist(string(name), type);
}

ESPPropType ESPObject_GetPropertyType(ESPObject* pThis, const char* name)
{
	return pThis->props->GetPropertyType(string(name));
}

//返回的文本不需要删除, 请复制后使用
bool ESPObject_GetPropertyInfos(ESPObject* pThis, const char* name, 
								ESPPropType* type, char** desc, char** initial, bool* ispublic, bool* istemp)
{
	ESPPropInfo* pInfo = pThis->props->GetPropertyInfo(string(name));
	if(pInfo == NULL) return false;

	if(type) *type = pInfo->m_type;
	if(desc) *desc = (char*) pInfo->m_description.c_str();
	if(initial) *initial = (char*) pInfo->m_initial_text.c_str();
	if(ispublic) *ispublic = pInfo->m_is_public;
	if(istemp) *istemp = (pInfo->m_is_formal == false);

	return true;
}

bool ESPObject_RemoveAllPropeties(ESPObject* pThis)
{
	return pThis->props->RemoveAll();
}

bool ESPObject_SetProperty(ESPObject* pThis, const char* name, const char* value)
{
	return pThis->props->SetProperty(string(name), value);
}

char* ESPObject_GetProperty(ESPObject* pThis, const char* name)
{
	return mallocstr(pThis->props->GetProperty(string(name)).c_str(), -1);
}

bool ESPObject_SetBoolProperty(ESPObject* pThis, const char* name, bool v)
{
	return pThis->props->SetProperty_Bool(string(name), v);
}

bool ESPObject_GetBoolProperty(ESPObject* pThis, const char* name)
{
	return pThis->props->GetProperty_Bool(string(name));
}

bool ESPObject_SetIntProperty(ESPObject* pThis, const char* name, int v)
{
	return pThis->props->SetProperty_Int(string(name), v);
}

int ESPObject_GetIntProperty(ESPObject* pThis, const char* name)
{
	return pThis->props->GetProperty_Int(string(name));
}

bool ESPObject_SetInt64Property(ESPObject* pThis, const char* name, ESP_INT64 v)
{
	return pThis->props->SetProperty_Int64(string(name), v);
}

ESP_INT64 ESPObject_GetInt64Property(ESPObject* pThis, const char* name)
{
	return pThis->props->GetProperty_Int64(string(name));
}

bool ESPObject_SetFloatProperty(ESPObject* pThis, const char* name, float v)
{
	return pThis->props->SetProperty_Float(string(name), v);
}

float ESPObject_GetFloatProperty(ESPObject* pThis, const char* name)
{
	return pThis->props->GetProperty_Float(string(name));
}

bool ESPObject_SetDoubleProperty(ESPObject* pThis, const char* name, double v)
{
	return pThis->props->SetProperty_Double(string(name), v);
}

double ESPObject_GetDoubleProperty(ESPObject* pThis, const char* name)
{
	return pThis->props->GetProperty_Double(string(name));
}

const char* ESPObject_GetTextProperty(ESPObject* pThis, const char* name)
{
	return pThis->props->GetProperty_Text(string(name));
}

bool ESPObject_SetTextProperty(ESPObject* pThis, const char* name, const char* v)
{
	return pThis->props->SetProperty_Text(string(name), v);
}

const void* ESPObject_GetBinaryProperty(ESPObject* pThis, const char* name, size_t* len)
{
	return pThis->props->GetProperty_Binary(string(name), *len);
}

bool ESPObject_SetBinaryProperty(ESPObject* pThis, const char* name, void* data, size_t len)
{
	return pThis->props->SetProperty_Binary(string(name), data, len);
}

const char* ESPObject_GetRequestInfo(ESPObject* pThis, ESPRequestInfoIndex index)
{
	switch(index)
	{
	case ESPRequestInfoIndex_URI:
		{
			//返回ScriptName
			//因为此处返回给易语言的信息，主要用来生成带有path_info的触发ESP组件事件的链接
			//如果这里带有QueryString，就不好插入path_info了
			//FIXME(liigo): 关于URI和ScriptName的概念，还需要仔细理解，现在感觉有点模糊
			//TODO: 修正支持库里的相关命名
			const char* szScriptName = NULL; bool needFree;
			pThis->page->server_api->GetScriptName(&szScriptName, needFree);
			char* result = apr_pstrdup(pThis->page->server_api->GetRequestPool(), szScriptName);
			if(szScriptName && needFree)
				pThis->page->server_api->FreeData(szScriptName);
			return result;
		}
	case ESPRequestInfoIndex_QueryString:
		{
			const char* szQueryString = NULL; bool needFreeQS;
			pThis->page->server_api->GetQueryString(&szQueryString, needFreeQS);
			char* result = apr_pstrdup(pThis->page->server_api->GetRequestPool(), szQueryString);
			if(szQueryString && needFreeQS)
				pThis->page->server_api->FreeData(szQueryString);
			return result;
		}
	}

	return NULL;
}

void ESPObject_RuntimeError(ESPObject* pThis, const char* type, const char* description)
{
	ESP_RuntimeError(pThis->page, type, description);
}

#ifndef WIN32
	#define __stdcall 
#endif

// x_on_<eventName>
// x_on_<eventName>_from_<componentInstanceName>
typedef bool (__stdcall *PFN_ESPEventMethod1) (ESPObject* pThis, ESPObject* pEventSender, const char* szEventParam); 

// x_onevent
// x_onevent_from_<componentInstanceName>
typedef bool (__stdcall *PFN_ESPEventMethod2) (ESPObject* pThis, ESPObject* pEventSender, const char* szEventName, const char* szEventParam);

bool _InvokeEventMethod(ESPObject* pObject, ESPObject* pEventSender, const char* szEventName, const char* szEventParam)
{
	const char* szSenderName = (pEventSender->instance_name == NULL ? "" : pEventSender->instance_name);

	string onFuncName = string(pObject->type_info->type_name) + "_on_" + szEventName;
	string onFromFuncName = onFuncName + "_from_" + szSenderName;

	PFN_ESPEventMethod1 eventFunc1 = (PFN_ESPEventMethod1)_GetDSOSym(pObject->type_info->dso_handle, onFromFuncName.c_str());
	if(eventFunc1)
	{
		return eventFunc1(pObject, pEventSender, szEventParam); // on_*_from_*
	}
	else
	{
		eventFunc1 = (PFN_ESPEventMethod1)_GetDSOSym(pObject->type_info->dso_handle, onFuncName.c_str());
		if(eventFunc1)
			return eventFunc1(pObject, pEventSender, szEventParam); // on_*
	}


	string oneventFuncName = string(pObject->type_info->type_name) + "_onevent";
	string oneventFromFuncName = oneventFuncName + "_from_" + szSenderName;

	PFN_ESPEventMethod2 eventFunc2 = (PFN_ESPEventMethod2)_GetDSOSym(pObject->type_info->dso_handle, oneventFromFuncName.c_str());
	if(eventFunc2)
	{
		return eventFunc2(pObject, pEventSender, szEventName, szEventParam); // onevent_from_*
	}
	else
	{
		eventFunc2 = (PFN_ESPEventMethod2)_GetDSOSym(pObject->type_info->dso_handle, oneventFuncName.c_str());
		if(eventFunc2)
			return eventFunc2(pObject, pEventSender, szEventName, szEventParam); // onevent
	}

	return true;
}

bool ESPObject_FireEvent(ESPObject* pThis, const char* szEventName, const char* szEventParam)
{
	bool continueSendEvent = false;
	ESPObject* pObject = pThis;

	while(pObject)
	{
		continueSendEvent = _InvokeEventMethod(pObject, pThis, szEventName, szEventParam);
		if(!continueSendEvent)
			break;
		pObject = pObject->parent;
	}

	return true;
}

bool ESPObject_IsRuntimeErrorOccurred(ESPObject* pThis)
{
	return ESP_IsRuntimeErrorOccurred(pThis->page);
}


//Renderable

typedef bool (__stdcall *PFN_RenderMethod) (ESPRenderable* pThis, ESPRenderContext* pRenderContext);

static bool _InvokeRenderMethod(ESPRenderable* pThis, ESPRenderContext* pRenderContext, const char* methodName, bool defaultReturnValue)
{
	assert(pThis && pThis->type_info && pThis->type_info->dso_handle);

	char* funcName = apr_pstrcat(pThis->pool, pThis->type_info->type_name, "_", methodName, NULL);

	apr_dso_handle_sym_t sym = NULL;
	apr_status_t state = apr_dso_sym(&sym, pThis->type_info->dso_handle, funcName);
	PFN_RenderMethod pfnRenderMethod = (PFN_RenderMethod) sym;

	if(state == APR_SUCCESS && pfnRenderMethod)
	{
		return pfnRenderMethod(pThis, pRenderContext);
	}
	else
	{
		return defaultReturnValue;
	}
}

bool ESPRenderable_SetupRender(ESPRenderable* pThis, ESPRenderContext* pRenderContext)
{
	return _InvokeRenderMethod(pThis, pRenderContext, "setup_render", true);
}

bool ESPRenderable_BeforeRender(ESPRenderable* pThis, ESPRenderContext* pRenderContext)
{
	return _InvokeRenderMethod(pThis, pRenderContext, "before_render", true);
}

bool ESPRenderable_BeforeRenderTemplate(ESPRenderable* pThis, ESPRenderContext* pRenderContext)
{
	return _InvokeRenderMethod(pThis, pRenderContext, "before_render_template", true);
}

bool ESPRenderable_BeforeRenderBody(ESPRenderable* pThis, ESPRenderContext* pRenderContext)
{
	return _InvokeRenderMethod(pThis, pRenderContext, "before_render_body", true);
}

bool ESPRenderable_RenderBody(ESPRenderable* pThis, ESPRenderContext* pRenderContext)
{
	return _InvokeRenderMethod(pThis, pRenderContext, "render_body", true);
}

bool ESPRenderable_AfterRenderBody(ESPRenderable* pThis, ESPRenderContext* pRenderContext)
{
	return _InvokeRenderMethod(pThis, pRenderContext, "after_render_body", true);
}

bool ESPRenderable_AfterRenderTemplate(ESPRenderable* pThis, ESPRenderContext* pRenderContext)
{
	return _InvokeRenderMethod(pThis, pRenderContext, "after_render_template", true);
}

bool ESPRenderable_AfterRender(ESPRenderable* pThis, ESPRenderContext* pRenderContext)
{
	return _InvokeRenderMethod(pThis, pRenderContext, "after_render", true);
}

bool ESPRenderable_CleanupRender(ESPRenderable* pThis, ESPRenderContext* pRenderContext)
{
	return _InvokeRenderMethod(pThis, pRenderContext, "cleanup_render", true);
}

//暂时不用
bool ESPRenderable_Render(ESPRenderable* pThis, ESPRenderContext* pRenderContext)
{
	return true;
}

//RenderContext

void ESPRenderContext_Output(ESPRenderContext* pThis, const void* pData, size_t nDataLen)
{
	((liigo::MemBuffer*)pThis)->appendData(pData, nDataLen);
}

const char* ESPObject_GetSession(ESPObject* pThis, const char* key)
{
	esp_session::session_kv* session = (esp_session::session_kv*) pThis->page->session;
	if(session == NULL)
		return NULL;

	esp_session::session_kv::iterator it = session->find(key);

	if(it != session->end())
		return (*it).second.c_str();
	else
		return NULL;
}

bool ESPObject_SetSession(ESPObject* pThis, const char* key, const char* value)
{
	esp_session::session_kv* session = (esp_session::session_kv*) pThis->page->session;
	if(session == NULL)
		return false;

	(*session)[key] = value;

	return true;
}

// ESPPage

