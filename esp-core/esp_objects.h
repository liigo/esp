#ifndef __ESP_OBJECTS_H__
#define __ESP_OBJECTS_H__

#include <apr_pools.h>
#include <apr_dso.h>
#include "esp_clientapi.h" // to use ESPPropType, ESPRequestInfoIndex and ESP_INT64

class ESPPropInfos;
class ESPPropValues;
class ESPLibrary;
class ESPTemplate;
class ESPInstanceNameManager;
class ESPServerAPI;
class ESPObjectPool;

//������Ϣ, ����ͬ���Ͷ�����
struct ESPTypeInfo
{
	char* type_name;
	ESPPropInfos* prop_infos;
	apr_pool_t* pool;
	ESPLibrary* library;
	apr_dso_handle_t* dso_handle; //��library�е���Ϣ�غϣ��˴���Ϊ���Ż�
	ESPTemplate* esp_template;
};

//ҳ�����, �������
struct ESPObject
{
	ESPTypeInfo* type_info;
	ESPPropValues* props;
	apr_pool_t* pool;
	char* instance_name;
	ESPObject* page;
	ESPObject* parent;
	//TODO(liigo): ����ĳ�Ա���ΪESPPage����?
	ESPInstanceNameManager* name_manager;
	ESPObjectPool* component_pool;
	ESPServerAPI* server_api;
	void* session; //esp_session::session_kv*
};

typedef ESPObject  ESPComponent, ESPPage, ESPRenderable;


//Page
int ESPPage_FireEvent(ESPPage* pThis);

//Component
ESPPage* ESPComponent_GetPage(ESPComponent* pThis);

//Object
const char* ESPObject_GetRequestInfo(ESPObject* pThis, ESPRequestInfoIndex index);
ESPPage* ESPObject_GetPage(ESPObject* pThis);
ESPObject* ESPObject_GetParent(ESPObject* pThis);
bool ESPObject_FireEvent(ESPObject* pThis, const char* szEventName, const char* szEventParam);
void ESPObject_RuntimeError(ESPObject* pThis, const char* type, const char* description);
bool ESPObject_IsRuntimeErrorOccurred(ESPObject* pThis);
const char* ESPObject_GetSession(ESPObject* pThis, const char* key);
bool ESPObject_SetSession(ESPObject* pThis, const char* key, const char* value);
bool ESPObject_IsPage(ESPObject* pThis);
const char* ESPObject_GetInstanceName(ESPObject* pThis);
const char* ESPObject_GetTypeName(ESPObject* pThis);
const char* ESPObject_GetLibraryName(ESPObject* pThis);
const char* ESPObject_GetLibraryFile(ESPObject* pThis);

size_t ESPObject_GetAllPropertyCount(ESPObject* pThis);
char** ESPObject_GetPropertyNames(ESPObject* pThis, bool includePublic, bool includePrivate, bool includeInformal, size_t* pCount);
bool ESPObject_IsPropertyExist(ESPObject* pThis, const char* name, ESPPropType type);
ESPPropType ESPObject_GetPropertyType(ESPObject* pThis, const char* name);
bool ESPObject_GetPropertyInfos(ESPObject* pThis, const char* name, ESPPropType* type, char** desc, char** initial, bool* ispublic, bool* istemp); //���ص��ı�����Ҫɾ��, �븴�ƺ�ʹ�á����������������ΪNULL��
bool ESPObject_RemoveAllPropeties(ESPObject* pThis);
char* ESPObject_GetProperty(ESPObject* pThis, const char* name); //��������ֵ���ı���ʽ���ڲ��Զ����������͵�����ֵת��Ϊ�ı��󷵻أ�������ֵ����ͨ��free()ɾ��
bool ESPObject_SetProperty(ESPObject* pThis, const char* name, const char* value); //���ı���ʽ��������ֵ���ڲ��Զ��������ͼ���ת��
bool ESPObject_SetBoolProperty(ESPObject* pThis, const char* name, bool v);
bool ESPObject_GetBoolProperty(ESPObject* pThis, const char* name);
bool ESPObject_SetIntProperty(ESPObject* pThis, const char* name, int v);
int ESPObject_GetIntProperty(ESPObject* pThis, const char* name);
bool ESPObject_SetInt64Property(ESPObject* pThis, const char* name, ESP_INT64 v);
ESP_INT64 ESPObject_GetInt64Property(ESPObject* pThis, const char* name);
bool ESPObject_SetFloatProperty(ESPObject* pThis, const char* name, float v);
float ESPObject_GetFloatProperty(ESPObject* pThis, const char* name);
bool ESPObject_SetDoubleProperty(ESPObject* pThis, const char* name, double v);
double ESPObject_GetDoubleProperty(ESPObject* pThis, const char* name);
bool ESPObject_SetBoolProperty(ESPObject* pThis, const char* name, bool v);
bool ESPObject_GetBoolProperty(ESPObject* pThis, const char* name);
const char* ESPObject_GetTextProperty(ESPObject* pThis, const char* name); //����ֵ����ɾ�������޸�
bool ESPObject_SetTextProperty(ESPObject* pThis, const char* name, const char* value);
const void* ESPObject_GetBinaryProperty(ESPObject* pThis, const char* name, size_t* len); //����ֵ����ɾ�������޸�
bool ESPObject_SetBinaryProperty(ESPObject* pThis, const char* name, void* data, size_t len);

//RenderContext
struct ESPRenderContext {};
void ESPRenderContext_Output(ESPRenderContext* pThis, const void* pData, size_t nDataLen);

//Renderable
bool ESPRenderable_Render(ESPRenderable* pThis, ESPRenderContext* pRenderContext);
bool ESPRenderable_SetupRender(ESPRenderable* pThis, ESPRenderContext* pRenderContext);
bool ESPRenderable_BeforeRender(ESPRenderable* pThis, ESPRenderContext* pRenderContext);
bool ESPRenderable_BeforeRenderTemplate(ESPRenderable* pThis, ESPRenderContext* pRenderContext);
bool ESPRenderable_BeforeRenderBody(ESPRenderable* pThis, ESPRenderContext* pRenderContext);
bool ESPRenderable_RenderBody(ESPRenderable* pThis, ESPRenderContext* pRenderContext);
bool ESPRenderable_AfterRenderBody(ESPRenderable* pThis, ESPRenderContext* pRenderContext);
bool ESPRenderable_AfterRenderTemplate(ESPRenderable* pThis, ESPRenderContext* pRenderContext);
bool ESPRenderable_AfterRender(ESPRenderable* pThis, ESPRenderContext* pRenderContext);
bool ESPRenderable_CleanupRender(ESPRenderable* pThis, ESPRenderContext* pRenderContext);


#endif //__ESP_OBJECTS_H__
