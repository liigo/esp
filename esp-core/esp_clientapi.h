#ifndef __ESP_CLIENTAPI_H__
#define __ESP_CLIENTAPI_H__

#include <stddef.h>

#ifdef __cplusplus
	extern "C" {
#endif

typedef int ESPObjectID, ESPComponentID, ESPPageID, ESPRenderableID, ESPRenderContextID;

#ifdef WIN32
	typedef __int64 ESP_INT64;
#else
	typedef long long ESP_INT64;
#endif

enum ESPPropType
{
	ESPPropType_NULL = 0,
	ESPPropType_BOOL,
	ESPPropType_INT,
	ESPPropType_INT64,
	ESPPropType_FLOAT,
	ESPPropType_DOUBLE,
	ESPPropType_TEXT,
	ESPPropType_BINARY,
};

enum ESPRequestInfoIndex
{
	ESPRequestInfoIndex_URI = 0,
	ESPRequestInfoIndex_QueryString,
};

//�����������
//���¶ദ��int��ʾbool���ͣ�0/1�ֱ��ʾfalse/true��: ��C������ʽ�ṩ�ӿ�
typedef size_t (*PFN_ESPObject_GetAllPropertyCount) (ESPObjectID oid);
typedef char** (*PFN_ESPObject_GetPropertyNames) (ESPObjectID oid, int includePublic, int includePrivate, int includeInformal, size_t* pCount);
typedef int (*PFN_ESPObject_IsPropertyExist) (ESPObjectID oid, const char* name, enum ESPPropType type);
typedef enum ESPPropType (*PFN_ESPObject_GetPropertyType) (ESPObjectID oid, const char* name);
typedef int (*PFN_ESPObject_GetPropertyInfos) (ESPObjectID oid, const char* name, enum ESPPropType* type, char** desc, char** initial, int* ispublic, int* istemp);
typedef int (*PFN_ESPObject_RemoveAllPropeties) (ESPObjectID oid);
typedef char* (*PFN_ESPObject_GetProperty) (ESPObjectID oid, const char* name);
typedef int (*PFN_ESPObject_SetProperty) (ESPObjectID oid, const char* name, const char* value);
typedef int (*PFN_ESPObject_SetBoolProperty) (ESPObjectID oid, const char* name, int v);
typedef int (*PFN_ESPObject_GetBoolProperty) (ESPObjectID oid, const char* name);
typedef int (*PFN_ESPObject_SetIntProperty) (ESPObjectID oid, const char* name, int v);
typedef int (*PFN_ESPObject_GetIntProperty) (ESPObjectID oid, const char* name);
typedef int (*PFN_ESPObject_SetInt64Property) (ESPObjectID oid, const char* name, ESP_INT64 v);
typedef ESP_INT64 (*PFN_ESPObject_GetInt64Property) (ESPObjectID oid, const char* name);
typedef int (*PFN_ESPObject_SetFloatProperty) (ESPObjectID oid, const char* name, float v);
typedef float (*PFN_ESPObject_GetFloatProperty) (ESPObjectID oid, const char* name);
typedef int (*PFN_ESPObject_SetDoubleProperty) (ESPObjectID oid, const char* name, double v);
typedef double (*PFN_ESPObject_GetDoubleProperty) (ESPObjectID oid, const char* name);
typedef const char* (*PFN_ESPObject_GetTextProperty) (ESPObjectID oid, const char* name);
typedef int (*PFN_ESPObject_SetTextProperty) (ESPObjectID oid, const char* name, const char* value);
typedef const void* (*PFN_ESPObject_GetBinaryProperty) (ESPObjectID oid, const char* name, size_t* len);
typedef int (*PFN_ESPObject_SetBinaryProperty) (ESPObjectID oid, const char* name, void* data, size_t len);

typedef const char* (*PFN_ESPObject_GetRequestInfo) (ESPObjectID oid, enum ESPRequestInfoIndex index);
typedef ESPPageID (*PFN_ESPObject_GetPage) (ESPObjectID oid);
typedef ESPObjectID (*PFN_ESPObject_GetParent) (ESPObjectID oid);
typedef void (*PFN_ESPObject_RuntimeError) (ESPObjectID oid, const char* type, const char* description);
typedef const char* (*PFN_ESPObject_GetSession) (ESPObjectID oid, const char* key);
typedef int (*PFN_ESPObject_SetSession) (ESPObjectID oid, const char* key, const char* value);

typedef int (*PFN_ESPObject_IsPage) (ESPObjectID oid);
typedef const char* (*PFN_ESPObject_GetInstanceName) (ESPObjectID oid);
typedef const char* (*PFN_ESPObject_GetTypeName) (ESPObjectID oid);
typedef const char* (*PFN_ESPObject_GetLibraryName) (ESPObjectID oid);
typedef const char* (*PFN_ESPObject_GetLibraryFile) (ESPObjectID oid);

typedef void (*PFN_ESPRenderContext_Output) (ESPRenderContextID rcid, const void* pData, size_t nDataLen);

typedef void (*PFN_ESP_Log) (int type, const char* catalog, const char* data);
typedef void (*PFN_ESP_FreeData) (void* pData);


//ESP���ĺ���������WEB��������ESPר��ģ�飨esp-apache,esp-nginx,esp-lighttpd,esp-iis�ȣ���ͬ���ڲ�ʹ��
//ESPģ�鵼�����ش˽ṹ��ָ��ĺ���ESP_GetClientAPI(void)����������֧�ֿ�(esp.fne)����������֧�ֿ����
struct ESPClientAPI
{
	//����ɾ���������������˳�������󣬱������±���ESPģ�顢������֧�ֿ�(esp.fne)����̬�����ESP��

	PFN_ESPObject_GetAllPropertyCount pfn_ESPObject_GetAllPropertyCount;
	PFN_ESPObject_GetPropertyNames pfn_ESPObject_GetPropertyNames;
	PFN_ESPObject_IsPropertyExist pfn_ESPObject_IsPropertyExist;
	PFN_ESPObject_GetPropertyType pfn_ESPObject_GetPropertyType;
	PFN_ESPObject_GetPropertyInfos pfn_ESPObject_GetPropertyInfos;
	PFN_ESPObject_RemoveAllPropeties pfn_ESPObject_RemoveAllPropeties;
	PFN_ESPObject_GetProperty pfn_ESPObject_GetProperty;
	PFN_ESPObject_SetProperty pfn_ESPObject_SetProperty;
	PFN_ESPObject_GetBoolProperty pfn_ESPObject_GetBoolProperty;
	PFN_ESPObject_SetBoolProperty pfn_ESPObject_SetBoolProperty;
	PFN_ESPObject_GetIntProperty pfn_ESPObject_GetIntProperty;
	PFN_ESPObject_SetIntProperty pfn_ESPObject_SetIntProperty;
	PFN_ESPObject_GetInt64Property pfn_ESPObject_GetInt64Property;
	PFN_ESPObject_SetInt64Property pfn_ESPObject_SetInt64Property;
	PFN_ESPObject_GetFloatProperty pfn_ESPObject_GetFloatProperty;
	PFN_ESPObject_SetFloatProperty pfn_ESPObject_SetFloatProperty;
	PFN_ESPObject_GetDoubleProperty pfn_ESPObject_GetDoubleProperty;
	PFN_ESPObject_SetDoubleProperty pfn_ESPObject_SetDoubleProperty;
	PFN_ESPObject_GetTextProperty pfn_ESPObject_GetTextProperty;
	PFN_ESPObject_SetTextProperty pfn_ESPObject_SetTextProperty;
	PFN_ESPObject_GetBinaryProperty pfn_ESPObject_GetBinaryProperty;
	PFN_ESPObject_SetBinaryProperty pfn_ESPObject_SetBinaryProperty;

	PFN_ESPObject_GetPage pfn_ESPObject_GetPage;
	PFN_ESPObject_GetParent pfn_ESPObject_GetParent;
	PFN_ESPObject_RuntimeError pfn_ESPObject_RuntimeError;
	PFN_ESPObject_GetSession pfn_ESPObject_GetSession;
	PFN_ESPObject_SetSession pfn_ESPObject_SetSession;
	PFN_ESPObject_GetRequestInfo pfn_ESPObject_GetRequestInfo;

	PFN_ESPObject_IsPage pfn_ESPObject_IsPage;
	PFN_ESPObject_GetInstanceName pfn_ESPObject_GetInstanceName;
	PFN_ESPObject_GetTypeName pfn_ESPObject_GetTypeName;
	PFN_ESPObject_GetLibraryName pfn_ESPObject_GetLibraryName;
	PFN_ESPObject_GetLibraryFile pfn_ESPObject_GetLibraryFile;

	PFN_ESPRenderContext_Output pfn_ESPRenderContext_Output;

	PFN_ESP_Log pfn_Log;
	PFN_ESP_FreeData pfn_FreeData;
};

//ESPģ�����ʱ������ȫ·���ļ���д���(������)��������, �Ա�������֧�ֿ�(esp.fne)���Ҳ�����
#define ENV_NAME_OF_ESP_MOD_FILE_PATH  "ESP_MOD_FILE_PATH"

//ESPģ��Ϊ������֧�ֿ⵼���ĺ�������
#define FUNC_NAME_OF_ESP_GetClientAPI  "ESP_GetClientAPI"

//ESPģ��Ϊ������֧�ֿ⵼���ĺ���ԭ��
typedef const struct ESPClientAPI* (*PFN_ESP_GetClientAPI) ();

//ESP_GetClientAPI�������ڲ�ʵ�ֺ�������
const struct ESPClientAPI* ESPCore_GetClientAPI();

/*
Web Server's ESP modules should implements ESP_GetClientAPI() like this:

extern "C"
#ifdef WIN32
	__declspec(dllexport)
#endif
const ESPClientAPI* ESP_GetClientAPI()
{
	return ESPCore_GetClientAPI();
}
*/


#ifdef __cplusplus
	} //close extern "C"
#endif

#endif //__ESP_CLIENTAPI_H__
