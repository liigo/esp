#ifndef __ESP_MANAGERS_H__
#define __ESP_MANAGERS_H__

// ESPObjectManager: 负责 库/页面/组件 的 加载/创建/缓存/释放

#include <vector>
#include <string>
#include <apr_dso.h>
#include "esp_objects.h"
#include "esp_utils.h"
#include "stl_hash_map.h"

//Library

class ESPLibrary;

#ifndef WIN32
	#define __stdcall 
#endif

typedef bool (__stdcall *PFN_ESPLibrary_Init) ();
typedef void (__stdcall *PFN_ESPLibrary_Clean) ();
typedef const char* (__stdcall *PFN_ESPLibrary_Notify) (int type, int iParam1, int iParam2, const char* szParam1, const char* szParam2);
typedef const char* (__stdcall *PFN_ESPLibrary_GetPageNames) ();
typedef const char* (__stdcall *PFN_ESPLibrary_GetComponentNames) ();


struct ESPLibraryFuncs
{
	PFN_ESPLibrary_Init pfnInitLibrary;
	PFN_ESPLibrary_Clean pfnCleanLibrary;
	PFN_ESPLibrary_Notify pfnNotifyLibrary;
	PFN_ESPLibrary_GetPageNames pfnGetPageNames;
	PFN_ESPLibrary_GetComponentNames pfnGetComponentNames;
};

class ESPLibrary
{
private:
	std::string m_name;
	std::string m_fileName;
	std::vector<std::string> m_pageNames;
	std::vector<std::string> m_componentNames;
	apr_dso_handle_t* m_dso_handle;
	ESPLibraryFuncs m_funcs;
	ESPThreadMutex m_mutex;

public:
	ESPLibrary() : m_mutex(NULL)
	{
		m_dso_handle = NULL;
		memset(&m_funcs, 0, sizeof(ESPLibraryFuncs));
	}
	
	bool Load(const char* szLibFileName, const char* szLibName = NULL);
	bool Unload(); //卸载库, 但仍然尽量保留库信息
	bool Reload();
	bool IsLoaded() { ESPThreadGuard threadGuard(m_mutex); return m_dso_handle != 0; }
	const char* Notify(int type, int iParam1, int iParam2, const char* szParam1, const char* szParam2);
	
	//返回值表示指定名称是否在本库中定义
	bool FindPageName(const char* szPageName);
	bool FindComponentName(const char* szComponentName);
	
	const std::vector<std::string>& GetPageNames() { ESPThreadGuard threadGuard(m_mutex); return m_pageNames; }
	const std::vector<std::string>& GetComponentNames() { ESPThreadGuard threadGuard(m_mutex); return m_componentNames; }

	const char* GetName() { ESPThreadGuard threadGuard(m_mutex); return m_name.c_str(); }
	const char* GetFileName() { ESPThreadGuard threadGuard(m_mutex); return m_fileName.c_str(); }
	apr_dso_handle_t* GetDSOHandle() { ESPThreadGuard threadGuard(m_mutex); return m_dso_handle; }
	
private:
	bool cleanLibrary();
	void initMethodFuncs();
};

class ESPLibraryManager
{
private:
	std::vector<ESPLibrary*> m_librarys; //libraries
	STL_HASH_MAP(std::string,ESPLibrary*) m_pageName2LibMap;
	STL_HASH_MAP(std::string,ESPLibrary*) m_componentName2LibMap;
	ESPThreadMutex m_mutex;
public:
	ESPLibraryManager() : m_mutex(NULL) {}
	~ESPLibraryManager() { FreeAllLibrary(); }

private:
	//阻止对象复制和赋值
	ESPLibraryManager(const ESPLibraryManager& other);
	const ESPLibraryManager& operator=(const ESPLibraryManager& other);

public:
	bool LoadFromDir(const char* szDirPath, bool bIncludeSubDir);
	ESPLibrary* FindLibraryByPageName(const char* pageName);
	ESPLibrary* FindLibraryByComponentName(const char* componentName);
	void FreeAllLibrary();
private:
	void EnumFilesOfDir(std::string& strDir, bool bEnumSubDir, apr_pool_t* pool);
	void OnEnumFile(std::string& strFile);
};

typedef const char* (__stdcall *PFN_ESPObject_DefinePropOrParam)();

class ESPTypeInfoManager
{
private:
	ESPLibraryManager& m_libManager;
	apr_pool_t* m_pool;

	typedef STL_HASH_MAP(std::string,ESPTypeInfo*) ESPName2TypeInfo;
	ESPName2TypeInfo m_PageTypeInfos;
	ESPName2TypeInfo m_ComponentTypeInfos;
	ESPThreadMutex m_mutex;

public:
	ESPTypeInfoManager(ESPLibraryManager& libManager);
	~ESPTypeInfoManager();

	ESPTypeInfo* GetPageTypeInfo(const char* szTypeName);
	ESPTypeInfo* GetComponentTypeInfo(const char* szTypeName);

private:
	ESPTypeInfo* LoadPageTypeInfo(const char* szTypeName);
	ESPTypeInfo* LoadComponentTypeInfo(const char* szTypeName);
	ESPTypeInfo* LoadTypeInfo(ESPLibrary* pLib, const char* szTypeName);
	void FreeAllTypeInfos();
	static const char* Invoke_DefinePropOrParam(apr_dso_handle_t* hLib, const char* szTypeName, const char* szFuncName);
};

//一个类型名称对应多个对象
class ESPObjectPool
{
private:
	typedef STL_HASH_MAP(std::string, std::vector<ESPObject*>*) ESPString2ObjectMap;
	ESPString2ObjectMap m_map;
	typedef void (*PFN_ProcessESPObjectFromPool) (ESPObject* pObject);
	typedef void (*PFN_DeleteESPObjectFromPool) (ESPObject* pObject);
public:
	ESPObjectPool() {}
	ESPObject* GetFromPool(const char* szTypeName);
	void ReturnToPool(ESPObject* pObject);
	void BatchReturnToPool(const ESPObjectPool& sourcePool);
	void ProcessAll(PFN_ProcessESPObjectFromPool pfnProcessObject);
	void DeleteAll(PFN_DeleteESPObjectFromPool pfnDeleteObject);
};

class ESPObjectManager
{
private:
	ESPLibraryManager m_libManager;
	ESPObjectPool m_pagePool;
	ESPObjectPool m_componentPool;
	ESPTypeInfoManager m_typeInfoManager;
	ESPThreadMutex m_mutexPagePool, m_mutexComponentPool;
public:
	ESPObjectManager();
	~ESPObjectManager();

public:
	ESPPage* AcquirePage(const char* typeName, const char* instanceName, ESPServerAPI* serverApi);
	void ReleasePage(ESPPage* page);

	ESPComponent* AcquireComponent(const char* typeName, const char* instanceName, ESPObject* parent);
	void ReleaseComponent(ESPComponent* component, bool returnToGlobalPool);

private:
	ESPPage* CreatePage(const char* typeName, ESPServerAPI* serverApi, apr_pool_t* pool);
	static void DeletePage(ESPPage* page);
	ESPComponent* CreateComponent(const char* typeName, apr_pool_t* pool);
	static void DeleteComponent(ESPComponent* component);
	ESPObject* CreateESPObject(bool isPage, const char* typeName, apr_pool_t* pool);
	static void DeleteESPOBject(ESPObject* object);
	bool ParseRequestData(ESPPage* page);
};


//每个页面有且只有一个ESPInstanceNameManager, 它负责为页面内的所有组件分配保证不重复的实例名称
//在Page创建时创建, Page销毁时销毁, 在Page返回缓冲池时InvalidateAllNames()
class ESPInstanceNameManager
{
private:
	typedef STL_HASH_MAP(std::string,size_t) _ESPInstanceNameNumMap;
	_ESPInstanceNameNumMap m_InstanceNameNumMap; //相同的baseName则顺序编号, baseName1,baseName2,...

	typedef STL_HASH_MAP(std::string,ESPComponent*) _ESPInstanceNameMap;
	_ESPInstanceNameMap m_InstanceNameMap;
public:
	bool AssignInstanceName(ESPComponent* component, const char* baseInstanceName); //baseName可为NULL
	void InvalidateAllInstanceNames();
	ESPComponent* FindByInstanceName(const char* szInstanceName);
};

class ESPApplicationObjectManager
{

};

class ESPVirtualHost;
class ESPApplicationManager;

class ESPApplication
{
private:
	std::string m_appName;
	ESPObjectManager m_appObjectManager;
};

class ESPVirtualHost
{
private:
	typedef STL_HASH_MAP(std::string,ESPApplication*) ESPName2ApplicationMap;
	ESPName2ApplicationMap m_apps;
	ESPObjectManager m_vhostObjectManager;
	std::string m_vhostName;
public:
	ESPApplication* GetApplication(const std::string& appName);
};

class ESPApplicationManager
{
private:
	typedef STL_HASH_MAP(std::string,ESPVirtualHost*) ESPName2VirtualHostMap;
	ESPName2VirtualHostMap m_vhosts;
	ESPObjectManager m_serverObjectManager;

public:
	ESPVirtualHost* GetVirtualHost(const std::string& vhostName);
	ESPApplication* GetApplication(const std::string& vhostName, const std::string& appName);

private:

};



#endif //__ESP_MANAGERS_H__
