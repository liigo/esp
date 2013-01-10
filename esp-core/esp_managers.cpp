#include "esp_managers.h"
#include <string>
#include <list>
#include <algorithm>
#include <apr_strings.h>
#include <apr_pools.h>
#include <apr_file_info.h>
#include "string_util.h"
#include "esp_prop.h"
#include "esp_globals.h"
#include "esp_objects.h"
#include "esp_template.h"
#include "esp_serverapi.h"
#include "esp_session.h"
#include "esp_log.h"
#include "esp_internal.h"


// ESP对象/库/属性的管理器
// by Liigo, before 2009.

using namespace std;


// ESPObjectPool

ESPObject* ESPObjectPool::GetFromPool(const char* szTypeName)
{
	ESPString2ObjectMap::iterator it = m_map.find(szTypeName);
	if(it == m_map.end())
		return NULL;
	
	vector<ESPObject*>* pVector = (*it).second;
	if(!pVector->empty())
	{
		ESPObject* pObject = pVector->back();
		pVector->pop_back();
		return pObject;
	}
	else
		return NULL;
}

void ESPObjectPool::ReturnToPool(ESPObject* pObject)
{
	string strTypeName = pObject->type_info->type_name;
	ESPString2ObjectMap::iterator it = m_map.find(strTypeName);
	if(it != m_map.end())
	{
		(*it).second->push_back(pObject);
	}
	else
	{
		vector<ESPObject*>* pVector = new vector<ESPObject*>();
		pVector->push_back(pObject);
		m_map[strTypeName] = pVector;
	}
}

void ESPObjectPool::BatchReturnToPool(const ESPObjectPool& sourcePool)
{
	ESPString2ObjectMap::const_iterator srcIt = sourcePool.m_map.begin();
	for(; srcIt != sourcePool.m_map.end(); ++srcIt)
	{
		const string& strTypeName = (*srcIt).first;
		vector<ESPObject*>* pSrcVector = (*srcIt).second;

		ESPString2ObjectMap::iterator thisIt = m_map.find(strTypeName);
		if(thisIt != m_map.end())
		{
			vector<ESPObject*>* pThisVector = (*thisIt).second;
			pThisVector->insert(pThisVector->end(), pSrcVector->begin(), pSrcVector->end());
		}
		else
		{
			vector<ESPObject*>* pThisVector = new vector<ESPObject*>();
			pThisVector->insert(pThisVector->end(), pSrcVector->begin(), pSrcVector->end());
			m_map[strTypeName] = pThisVector;
		}
	}
}

void ESPObjectPool::ProcessAll(PFN_DeleteESPObjectFromPool pfnProcessObject)
{
	assert(pfnProcessObject);
	ESPString2ObjectMap::iterator it;
	for(it = m_map.begin(); it != m_map.end(); ++it)
	{
		vector<ESPObject*>* pVector = (*it).second;
		for(unsigned int i = 0, n = pVector->size(); i < n; ++i)
			pfnProcessObject((*pVector)[i]);
	}
}

void ESPObjectPool::DeleteAll(PFN_DeleteESPObjectFromPool pfnDeleteObject)
{
	ESPString2ObjectMap::iterator it;
	for(it = m_map.begin(); it != m_map.end(); ++it)
	{
		vector<ESPObject*>* pVector = (*it).second;
		if(pfnDeleteObject)
		{
			for(unsigned int i = 0, n = pVector->size(); i < n; ++i)
				pfnDeleteObject((*pVector)[i]);
		}
		delete pVector;
	}
	m_map.clear();
}

//ESPLibraryManager

bool ESPLibraryManager::LoadFromDir(const char* szDirPath, bool bIncludeSubDir)
{
	ESPThreadGuard threadGuard(m_mutex);
	apr_pool_t* pool;
	apr_pool_create(&pool, NULL);
	
	char* szDir = apr_pstrdup(pool, szDirPath);
	size_t nLen = strlen(szDir);
	for(size_t i = 0; i < nLen; i++)
	{
		if(szDir[i] == '\\')  szDir[i] = '/';  //应apr要求, 目录分隔符使用'/'
	}
	if(szDir[nLen-1] == '/')  szDir[nLen-1] = '\0'; //不以'/'结尾
	
	string tempdir = szDir;
	EnumFilesOfDir(tempdir, bIncludeSubDir, pool); //遍历目录, 遇到文件调用 OnEnumFile()
	
	apr_pool_destroy(pool);
	return true;
}

void ESPLibraryManager::EnumFilesOfDir(std::string& strDir, bool bEnumSubDir, apr_pool_t* pool)
{
	apr_dir_t* dir;
	apr_status_t status = apr_dir_open(&dir, strDir.c_str(), pool);
	if(status != APR_SUCCESS || dir == NULL)
		return;
	
	apr_finfo_t finfo;
	apr_int32_t wanted = APR_FINFO_TYPE|APR_FINFO_NAME;
	while(1)
	{
		status = apr_dir_read(&finfo, wanted, dir);
		
		if(status == APR_INCOMPLETE)
			continue;
		else if (status != APR_SUCCESS)
			break;
		
		if(finfo.filetype == APR_REG /* regular file */)
		{
			std::string tempfile = strDir + "/" + finfo.name;
			OnEnumFile(tempfile);
		}
		else if(bEnumSubDir && finfo.filetype == APR_DIR)
		{
			if(strcmp(finfo.name, ".") == 0 || strcmp(finfo.name, "..") == 0) 
				continue;
			std::string tempdir = strDir + "/" + finfo.name;
			EnumFilesOfDir(tempdir, true, pool);
		}
	}
	
	status = apr_dir_close(dir);
	assert(status == APR_SUCCESS);
	return;
}

//目录间的分隔符均为'/'
void ESPLibraryManager::OnEnumFile(std::string& strFile)
{
	if(strFile.rfind(".esp") == strFile.length() - 4 || strFile.rfind(".esc") == strFile.length() - 4)
		return; //ignore .esp .esc files, they are not esp library

	const char* szFileName = strFile.c_str();
	ESPLibrary* pLib = new ESPLibrary();
	assert(pLib);
	if(pLib == NULL) return;

	if(pLib->Load(szFileName) == false)
	{
		ESP_CORE_LOG((LOG_ERROR, "Load ESP Library Error: %s", szFileName));
		assert(false && "failed when load esp library");
		delete pLib; 
		return;
	}

	vector<string>& pageNames = (vector<string>&) pLib->GetPageNames();
	vector<string>& componentNames = (vector<string>&) pLib->GetComponentNames();
	vector<string>::iterator i;

	if(pageNames.size() > 0)
	{
		for(i = pageNames.begin(); i != pageNames.end(); i++)
			m_pageName2LibMap[*i] = pLib; //页面名称快速查询表
	}

	if(componentNames.size() > 0)
	{
		for(i = componentNames.begin(); i != componentNames.end(); i++)
			m_componentName2LibMap[*i] = pLib; //组件名称快速查询表
	}

	if(pageNames.size() > 0 || componentNames.size() > 0)
	{
		m_librarys.push_back(pLib); //记录ESPLibrary*列表
		pLib->Unload(); //以后用到该库时Reload()即可
	}
	else
		delete pLib;
}

void ESPLibraryManager::FreeAllLibrary()
{
	ESPThreadGuard threadGuard(m_mutex);

	m_pageName2LibMap.clear();
	m_componentName2LibMap.clear();

	ESPLibrary* pLib = NULL;
	std::vector<ESPLibrary*>::iterator it;
	for(it = m_librarys.begin(); it != m_librarys.end(); ++it)
	{
		pLib = *it;
		pLib->Unload();
		delete pLib;
	}
	m_librarys.clear();
}

ESPLibrary* ESPLibraryManager::FindLibraryByPageName(const char* pageName)
{
	ESPThreadGuard threadGuard(m_mutex);
	STL_HASH_MAP(string,ESPLibrary*)::iterator i = m_pageName2LibMap.find(pageName);
	if(i != m_pageName2LibMap.end())
		return (*i).second;
	else
		return NULL;
}

ESPLibrary* ESPLibraryManager::FindLibraryByComponentName(const char* componentName)
{
	ESPThreadGuard threadGuard(m_mutex);
	STL_HASH_MAP(string,ESPLibrary*)::iterator i = m_componentName2LibMap.find(componentName);
	if(i != m_componentName2LibMap.end())
		return (*i).second;
	else
		return NULL;
}

// ESPObjectManager

extern const char* ESP_LIB_PATH; //defined in esp_template.cpp

ESPObjectManager::ESPObjectManager() : m_typeInfoManager(m_libManager),
									m_mutexPagePool(NULL), m_mutexComponentPool(NULL)
{
	m_libManager.LoadFromDir(ESP_LIB_PATH, false);
}

ESPObjectManager::~ESPObjectManager()
{
	ESP_CORE_LOG((LOG_INFO, "Delete all pages and components in the pool"));
	m_pagePool.DeleteAll(DeletePage);
	m_componentPool.DeleteAll(DeleteComponent);
}

//可能返回NULL（当typeName为非法类型名称时）
ESPPage* ESPObjectManager::AcquirePage(const char* typeName, const char* instanceName, ESPServerAPI* serverApi)
{
	ESP_CORE_LOG((LOG_INFO, "AcquirePage(%s)", typeName));

	m_mutexPagePool.Lock();
	ESPPage* page = m_pagePool.GetFromPool(typeName);
	m_mutexPagePool.Unlock();

	if(page)
	{
		page->instance_name = apr_pstrdup(page->pool, instanceName);
		page->props->FillInitialValues();
		page->server_api = serverApi;
		page->session = esp_session::session(page);
		ParseRequestData(page);
		ESP_CORE_LOG((LOG_INFO, "AcquirePage(%s) got[0x%x]", typeName, page));
		return page;
	}
	else
	{
		page = CreatePage(typeName, serverApi, ESP_GetRootAPRPool());
		if(page)
		{
			page->session = esp_session::session(page);
			ParseRequestData(page);
		}
		ESP_CORE_LOG((LOG_INFO, "AcquirePage(%s) got[0x%x]", typeName, page?page:NULL));
		return page;
	}
}

void ESPObjectManager::ReleasePage(ESPPage* page)
{
	ESP_CORE_LOG((LOG_INFO, "ReleasePage(%s)[0x%x]", page->type_info->type_name, page));

	//页面的组件池中的所有组件归还到全局组件池
	m_mutexComponentPool.Lock();
	m_componentPool.BatchReturnToPool(*page->component_pool);
	m_mutexComponentPool.Unlock();

	//入池前的清理
	page->instance_name = NULL;
	page->props->RemoveAll();
	page->name_manager->InvalidateAllInstanceNames();
	page->component_pool->DeleteAll(NULL);
	page->server_api = NULL;

	//入池
	m_mutexPagePool.Lock();
	m_pagePool.ReturnToPool(page);
	m_mutexPagePool.Unlock();
}

//可能返回NULL（当typeName为非法类型名称时）
ESPComponent* ESPObjectManager::AcquireComponent(const char* typeName, const char* instanceName, ESPObject* parent)
{
	assert(parent);

	//优先从当前页面的组件池中获取，没有的话再从全局组件池获取
	ESPComponent* component = parent->page->component_pool->GetFromPool(typeName);
	if(component == NULL)
	{
		ESPThreadGuard theadGuard(m_mutexComponentPool);
		component = (ESPComponent*) m_componentPool.GetFromPool(typeName);
	}

	//组件池中没有，则创建新的组件
	if(component == NULL)
		component = CreateComponent(typeName, parent->page->pool);
	else
		component->props->FillInitialValues();

	if(component)
	{
		component->parent = parent;
		component->page = parent->page;
		component->session = component->page->session;

		//设置组件名称(instance name)
		ESPInstanceNameManager* pInstanceNameManager = component->page->name_manager;
		pInstanceNameManager->AssignInstanceName(component, instanceName);
	}

	return component;
}

void ESPObjectManager::ReleaseComponent(ESPComponent* component, bool returnsToGlobalPool)
{
	//入池前清理component
	component->instance_name = NULL;
	component->session = NULL;
	component->name_manager = NULL;
	component->props->RemoveAll();

	//入池
	if(returnsToGlobalPool)
	{
		//入全局组件池
		ESPThreadGuard threadGuard(m_mutexComponentPool);
		m_componentPool.ReturnToPool(component);
	} else {
		//入页面组件池
		component->page->component_pool->ReturnToPool(component);
	}
}

ESPObject* ESPObjectManager::CreateESPObject(bool isPage, const char* typeName, apr_pool_t* pool)
{
	assert(pool);

	ESPLibrary* pLibrary = NULL;
	if(isPage)
		pLibrary = m_libManager.FindLibraryByPageName(typeName);
	else
		pLibrary = m_libManager.FindLibraryByComponentName(typeName);

	if(pLibrary)
	{
		if(!pLibrary->IsLoaded())
			pLibrary->Reload(); //m_libManager必然已经加载过该库, 可以Reload()
	}
	else
	{
		ESP_CORE_LOG((LOG_ERROR, "CreateESPObject() Error: Can't find a library that defines the %s type: %s", isPage?"page":"component", typeName));
		assert(false && "undefined esp page or component");
		return NULL;
	}

	ESPObject* pObject = (ESPObject*) malloc(sizeof(ESPObject));
	if(pObject == NULL) return NULL;
	memset(pObject, 0, sizeof(ESPObject));

	pObject->type_info = (isPage ? m_typeInfoManager.GetPageTypeInfo(typeName)
								 : m_typeInfoManager.GetComponentTypeInfo(typeName));
	assert(pObject->type_info);

	pObject->pool = pool;
	pObject->page = NULL; //在创建Page和Component时填充
	pObject->server_api = NULL; //在创建Page时填充
	pObject->session = NULL;

	pObject->props = new ESPPropValues(pObject->type_info->prop_infos);
	pObject->props->FillInitialValues();

	return pObject;
}

void ESPObjectManager::DeleteESPOBject(ESPObject* pThis)
{
	ESPObject_RemoveAllPropeties(pThis);
	delete (ESPPropValues*)(pThis->props);

	memset(pThis, 0, sizeof(ESPObject));
	free(pThis);
}

ESPPage* ESPObjectManager::CreatePage(const char* typeName, ESPServerAPI* serverApi, apr_pool_t* pool)
{
	assert(serverApi && pool);
	ESPPage* pPage = CreateESPObject(true, typeName, pool);
	if(pPage == NULL)
	{
		ESP_CORE_LOG((LOG_ERROR, "CreatePage(%s) Error!", typeName));
		return NULL;
	}

	pPage->page = pPage; //指向自身!
	pPage->parent = NULL;
	pPage->session = NULL;
	pPage->name_manager = new ESPInstanceNameManager();
	pPage->component_pool = new ESPObjectPool();
	pPage->server_api = serverApi;

	ESP_CORE_LOG((LOG_INFO, "CreatePage(%s) got[0x%x]", typeName, pPage));
	return pPage;
}

void ESPObjectManager::DeletePage(ESPPage* page)
{
	ESP_CORE_LOG((LOG_INFO, "DeletePage(%s)[0x%x]", page->type_info->type_name, page));
	delete page->name_manager;
	delete page->component_pool;
	DeleteESPOBject(page);
}

ESPComponent* ESPObjectManager::CreateComponent(const char* typeName, apr_pool_t* pool)
{
	ESPComponent* pComponent = (ESPComponent*) CreateESPObject(false, typeName, pool);
	if(pComponent == NULL)
	{
		ESP_CORE_LOG((LOG_ERROR, "CreateComponent(%s) Error!", typeName));
		return NULL; //TODO: 错误处理, 向用户反馈
	}

	ESP_CORE_LOG((LOG_INFO, "CreateComponent(%s) got[0x%x]", typeName, pComponent));
	return pComponent;
}

void ESPObjectManager::DeleteComponent(ESPComponent* component)
{
	ESP_CORE_LOG((LOG_INFO, "DeleteComponent(%s)[0x%x]", component->type_info->type_name, component));
	DeleteESPOBject(component);
}

//要求参数data的后面多出一个'\0'（不算在len内）以简化处理
static bool ParseRequestDataToPropValues(char* data, size_t len, ESPPropValues* pPropValues, char* namePrefix)
{
	if(data == NULL || len <= 0) return false;

	char* key = data;
	char* value = NULL;
	
	for(size_t i = 0; i < len; ++i)
	{
		if(data[i] == '=')
		{
			data[i] = '\0'; //end of the key
			value = data + i + 1; //begin of the value
			continue;
		}

		if(data[i] == '&')
		{
			data[i] = '\0'; //end of the value
	
			pPropValues->SetProperty_Text(string(namePrefix)+key, value);

			key = data + i + 1; //begin of the next key
			value = NULL;
			continue;
		}
	}

	if(key < data + len) //at least has a last key, and maybe a value
	{
		if(value) //also has a last value
		{
			pPropValues->SetProperty_Text(string(namePrefix)+key, value);
		}
		else //no value, only a key
		{
			pPropValues->SetProperty_Text(string(namePrefix)+key, "");
		}
	}

	return true;
}

class MemBufferDataWriter : public ESPDataWriter
{
public:
	MemBufferDataWriter(liigo::MemBuffer& memBuffer) : m_memBuffer(memBuffer)
	{
	}
	
	virtual void WriteData(void* pData, int nLength)
	{
		m_memBuffer.appendData(pData, (size_t)nLength);
	}

private:
	liigo::MemBuffer& m_memBuffer;
};

//todo: parse to page->request_args
bool ESPObjectManager::ParseRequestData(ESPPage* page)
{
	ESPRequestMethod method = page->server_api->GetRequestMethod();
	if(method == ESPRequestMethod_GET)
	{
		const char* szQueryString = NULL;
		bool needFreeQueryString = false;
		page->server_api->GetQueryString(&szQueryString, needFreeQueryString);
		if(szQueryString)
		{
			page->props->SetProperty_Text(std::string("?"), szQueryString);
			std::string querystr = szQueryString;
			ParseRequestDataToPropValues((char*)querystr.c_str(), querystr.size(), page->props, "?");
			if(needFreeQueryString)
				page->server_api->FreeData(szQueryString);
		}
	}
	else if(method == ESPRequestMethod_POST)
	{
		//TODO(liigo): 检查限制请求类型和内容长度
		liigo::MemBuffer postedData;
		MemBufferDataWriter writer(postedData);
		page->server_api->ReadRequestData(-1, writer);
		if(postedData.getDataSize() > 0)
		{
			postedData.appendChar('\0'); //额外添加一个'\0'，see ParseRequestDataToPropValues()
			ParseRequestDataToPropValues((char*)postedData.getData(), postedData.getDataSize()-1, page->props, "?");
		}
	}

	return true;
}

//------------------------------------
// ESPLibrary

//默认取文件名全小写形式作为ESP库名称
static string _GetDefaultLibName(string libFileName)
{
	const char* szLibFileName = libFileName.c_str();
	assert(szLibFileName != NULL);
	char* pDot = (char*)strrchr(szLibFileName, '.');
	if(pDot) *pDot = '\0';
	const char* pS1  = strrchr(szLibFileName, '/');
	const char* pS2  = strrchr(szLibFileName, '\\');
	const char* pName = (pS1 > pS2 ? pS1 : pS2);
	pName = (pName == NULL ? szLibFileName : pName + 1);
	char* p = (char*)pName;
	while(*p)
	{
		*p = tolower(*p); p++;
	}
	return pName;
}

bool ESPLibrary::Load(const char* szLibFileName, const char* szLibName /* = NULL */)
{
	assert(IsLoaded() == false);
	ESPThreadGuard threadGuard(m_mutex);

	//加载动态库
	apr_status_t bOK = apr_dso_load(&m_dso_handle, szLibFileName, ESP_GetRootAPRPool());
	if(bOK != APR_SUCCESS || m_dso_handle == NULL)
	{
		char errinfo[256];
		ESP_CORE_LOG((LOG_ERROR, "Load ESP Library Failed: %s", szLibFileName));
		ESP_CORE_LOG((LOG_ERROR, "Error Info: %s", apr_dso_error(m_dso_handle,errinfo,256)));
		//assert(false && "Load ESP library error. ");
		return false;
	}
	
	//获取所有已知函数
	initMethodFuncs();
	
	//调用初始化函数(ESP_InitLibrary)
	if(m_funcs.pfnInitLibrary)
	{
		bool initOK = m_funcs.pfnInitLibrary();
		if(!initOK)
		{
			//初始化失败则卸载(并自动调用清理函数)
			Unload();
			return false;
		}
	}

	ESP_CORE_LOG((LOG_INFO, "Load ESP Library Successfully: %s", szLibFileName));

	//获取并设置库信息
	m_name = (szLibName != NULL ? szLibName : _GetDefaultLibName(szLibFileName));
	m_fileName = szLibFileName;

	if(m_funcs.pfnGetPageNames)
	{
		const char* pageNames = m_funcs.pfnGetPageNames();
		ParseCommaSeparatedString(pageNames, m_pageNames);
		std::sort(m_pageNames.begin(), m_pageNames.end()); //排序,以便以后使用二分查找
		ESP_CORE_LOG((LOG_INFO, "Library defined pages: %s", pageNames));
	}
	if(m_funcs.pfnGetComponentNames)
	{
		const char* componentNames = m_funcs.pfnGetComponentNames();
		ParseCommaSeparatedString(componentNames, m_componentNames);
		std::sort(m_componentNames.begin(), m_componentNames.end()); //排序,以便以后使用二分查找
		ESP_CORE_LOG((LOG_INFO, "Library defined components: %s", componentNames));
	}

	return true;
}

bool ESPLibrary::Reload()
{
	assert(m_fileName.length() > 0);
	assert(!IsLoaded());
	return Load(m_fileName.c_str(), m_name.c_str());
}

bool ESPLibrary::Unload()
{
	if(IsLoaded() == false)
		return true;

	ESPThreadGuard threadGuard(m_mutex);

	//调用清理函数(ESP_CleanLibrary)
	if(m_funcs.pfnCleanLibrary)
		m_funcs.pfnCleanLibrary();

	//卸载库
	if(m_dso_handle)
	{
		apr_dso_unload(m_dso_handle);
		m_dso_handle = NULL;
	}

	return true;
}

const char* ESPLibrary::Notify(int type, int iParam1, int iParam2, const char* szParam1, const char* szParam2)
{
	ESPThreadGuard threadGuard(m_mutex);
	if(m_funcs.pfnNotifyLibrary)
		return m_funcs.pfnNotifyLibrary(type, iParam1, iParam2, szParam1, szParam2);
	return NULL;
}

void ESPLibrary::initMethodFuncs()
{
	assert(m_dso_handle);

#define _GetMethodFunc(funcname,functype)  (functype)_GetDSOSym(m_dso_handle, funcname)

	m_funcs.pfnInitLibrary       = _GetMethodFunc("esp_init_library", PFN_ESPLibrary_Init);
	m_funcs.pfnCleanLibrary      = _GetMethodFunc("esp_clean_library", PFN_ESPLibrary_Clean);
	m_funcs.pfnNotifyLibrary     = _GetMethodFunc("esp_notify_library", PFN_ESPLibrary_Notify);
	m_funcs.pfnGetPageNames      = _GetMethodFunc("esp_page_names", PFN_ESPLibrary_GetPageNames);
	m_funcs.pfnGetComponentNames = _GetMethodFunc("esp_component_names", PFN_ESPLibrary_GetComponentNames);
}

bool ESPLibrary::FindPageName(const char* szPageName) 
{
	ESPThreadGuard threadGuard(m_mutex);
	return std::binary_search(m_pageNames.begin(), m_pageNames.end(), szPageName); 
}

bool ESPLibrary::FindComponentName(const char* szComponentName)
{
	ESPThreadGuard threadGuard(m_mutex);
	return std::binary_search(m_componentNames.begin(), m_componentNames.end(), szComponentName);
}

//-------------------------------------------
// ESPInstanceNameManager

bool ESPInstanceNameManager::AssignInstanceName(ESPComponent* component, const char* baseInstanceName)
{
	assert(component);
	if(baseInstanceName == NULL || strlen(baseInstanceName) == 0)
		return true; //允许没有名称

	_ESPInstanceNameNumMap::iterator i = m_InstanceNameNumMap.find(baseInstanceName);

	if(i == m_InstanceNameNumMap.end())
	{
		component->instance_name = apr_pstrdup(component->pool, baseInstanceName);
		m_InstanceNameNumMap[baseInstanceName] = 1;
	}
	else
	{
		char num[32];
		//itoa((*i).second, num, 10); //Linux stdlib.h 内没有定义itoa！http://stackoverflow.com/questions/190229/where-is-the-itoa-function-in-linux
		sprintf(num, "%d", (*i).second);
		component->instance_name = apr_pstrcat(component->pool, baseInstanceName, num, NULL);
		(*i).second += 1;
	}

	m_InstanceNameMap[component->instance_name] = component;

	return true;
}

ESPComponent* ESPInstanceNameManager::FindByInstanceName(const char* szInstanceName)
{
	_ESPInstanceNameMap::iterator i = m_InstanceNameMap.find(szInstanceName);
	if(i == m_InstanceNameMap.end())
		return NULL; //not found
	return (*i).second;
}

void ESPInstanceNameManager::InvalidateAllInstanceNames()
{
	m_InstanceNameNumMap.clear();
	m_InstanceNameMap.clear();
}

//-----------------------------------------------------------------------
// ESPTypeInfoManager

ESPTypeInfoManager::ESPTypeInfoManager(ESPLibraryManager& libManager) : m_libManager(libManager), m_mutex(NULL)
{
	apr_pool_create(&m_pool, NULL);
	assert(m_pool);
}

ESPTypeInfoManager::~ESPTypeInfoManager()
{
	FreeAllTypeInfos();
	apr_pool_destroy(m_pool);
}

ESPTypeInfo* ESPTypeInfoManager::GetPageTypeInfo(const char* szTypeName)
{
	ESPThreadGuard threadGuard(m_mutex);
	ESPName2TypeInfo::iterator i = m_PageTypeInfos.find(szTypeName);
	if(i != m_PageTypeInfos.end())
		return (*i).second;

	//LoadPageTypeInfo()要不要并发? 
	//如果不并发，全系统同一时刻只能加载一个类型，慢。如果并发，如何避免同一类型同时重复加载?

	ESPTypeInfo* pTypeInfo = LoadPageTypeInfo(szTypeName);
	if(pTypeInfo)
	{
		m_PageTypeInfos[szTypeName] = pTypeInfo;
		return pTypeInfo;
	}

	ESP_CORE_LOG((LOG_ERROR, "LoadPageTypeInfo Error: %s", szTypeName));
	return NULL;
}

ESPTypeInfo* ESPTypeInfoManager::GetComponentTypeInfo(const char* szTypeName)
{
	ESPThreadGuard threadGuard(m_mutex);
	ESPName2TypeInfo::iterator i = m_ComponentTypeInfos.find(szTypeName);
	if(i != m_ComponentTypeInfos.end())
		return (*i).second;

	ESPTypeInfo* pTypeInfo = LoadComponentTypeInfo(szTypeName);
	if(pTypeInfo)
	{
		m_ComponentTypeInfos[szTypeName] = pTypeInfo;
		return pTypeInfo;
	}

	ESP_CORE_LOG((LOG_ERROR, "LoadComponentTypeInfo Error: %s", szTypeName));
	return NULL;
}


#define INVOKE_DefinePropOrParam(funcName) \
	Invoke_DefinePropOrParam(pLib->GetDSOHandle(), szTypeName, funcName);

ESPTypeInfo* ESPTypeInfoManager::LoadTypeInfo(ESPLibrary* pLib, const char* szTypeName)
{
	if(pLib == NULL) return NULL;
	if(pLib->IsLoaded() == false) pLib->Reload();

	ESP_CORE_LOG((LOG_INFO, "Begin LoadTypeInfo(%s) in library %s ...", szTypeName, pLib->GetName()));

	ESPTypeInfo* pTypeInfo = (ESPTypeInfo*) malloc(sizeof(ESPTypeInfo));
	memset(pTypeInfo, 0, sizeof(ESPTypeInfo));

	pTypeInfo->pool = m_pool;
	pTypeInfo->type_name = apr_pstrdup(pTypeInfo->pool, szTypeName);

	pTypeInfo->library = pLib;
	pTypeInfo->dso_handle = pLib->GetDSOHandle();

	pTypeInfo->esp_template = new ESPTemplate();

	//以下, 分别调用 xxx_define_[public/private_]properties/parameters()
	//并根据其返回值文本解析出ESPPropInfos
	//这个几函数中定义的属性, 其默认可见度(public/private)不同

	ESPPropInfos* pPropInfs = new ESPPropInfos();
	char* szError = NULL;

	const char* szDefines = INVOKE_DefinePropOrParam("define_public_properties");
	ParsePropInfos(szDefines, true, pPropInfs, &szError);

	szDefines = INVOKE_DefinePropOrParam("define_private_properties");
	ParsePropInfos(szDefines, false, pPropInfs, &szError);

	szDefines = INVOKE_DefinePropOrParam("define_properties");
	ParsePropInfos(szDefines, false, pPropInfs, &szError);

	szDefines = INVOKE_DefinePropOrParam("define_public_parameters");
	ParsePropInfos(szDefines, true, pPropInfs, &szError);

	szDefines = INVOKE_DefinePropOrParam("define_private_parameters");
	ParsePropInfos(szDefines, false, pPropInfs, &szError);

	szDefines = INVOKE_DefinePropOrParam("define_parameters");
	ParsePropInfos(szDefines, false, pPropInfs, &szError);

	pTypeInfo->prop_infos = pPropInfs;

	ESP_CORE_LOG((LOG_INFO, "LoadTypeInfo Successfully: %s.%s", pLib->GetName(), szTypeName));
	return pTypeInfo;
}

ESPTypeInfo* ESPTypeInfoManager::LoadPageTypeInfo(const char* szTypeName)
{
	ESPLibrary* pLib = m_libManager.FindLibraryByPageName(szTypeName);
	return LoadTypeInfo(pLib, szTypeName);
}

ESPTypeInfo* ESPTypeInfoManager::LoadComponentTypeInfo(const char* szTypeName)
{
	ESPLibrary* pLib = m_libManager.FindLibraryByComponentName(szTypeName);
	return LoadTypeInfo(pLib, szTypeName);
}

const char* ESPTypeInfoManager::Invoke_DefinePropOrParam(apr_dso_handle_t* hLib, const char* szTypeName, const char* szFuncName)
{
	assert(szTypeName && szFuncName);

	liigo::MemBuffer fullFuncName;
	fullFuncName.appendText(szTypeName);
	fullFuncName.appendChar('_');
	fullFuncName.appendText(szFuncName, -1, true);
	const char* szFullFuncName = (const char*) fullFuncName.getData();

	PFN_ESPObject_DefinePropOrParam pfn = (PFN_ESPObject_DefinePropOrParam) _GetDSOSym(hLib, szFullFuncName);
	if(pfn)
	{
		const char* szResult = pfn();
		ESP_CORE_LOG((LOG_INFO, "%s() returns: %s", szFullFuncName, szResult ? szResult : ""));
		return szResult;
	}
	return NULL;
}

void ESPTypeInfoManager::FreeAllTypeInfos()
{
	ESPThreadGuard threadGuard(m_mutex);

	ESPTypeInfo* pTypeInfo = NULL;
	ESPName2TypeInfo::iterator i;

	//删除页面类型信息
	for(i = m_PageTypeInfos.begin(); i != m_PageTypeInfos.end(); i++)
	{
		pTypeInfo = (*i).second;
		delete(pTypeInfo->prop_infos);
		free(pTypeInfo);
	}
	m_PageTypeInfos.clear();

	//删除组件类型信息
	for(i = m_ComponentTypeInfos.begin(); i != m_ComponentTypeInfos.end(); i++)
	{
		pTypeInfo = (*i).second;
		delete(pTypeInfo->prop_infos);
		free(pTypeInfo);
	}
	m_ComponentTypeInfos.clear();

	//删除内存池
	apr_pool_destroy(m_pool);
	m_pool = NULL;
}

//-----------------------------------------------------------------------------

ESPApplication* ESPVirtualHost::GetApplication(const std::string& appName)
{
	ESPName2ApplicationMap::iterator i = m_apps.find(appName);
	if(i != m_apps.end())
		return (*i).second;

	//todo: 创建ESPApplication*并放入表中,然后返回
	return NULL;
}

ESPVirtualHost* ESPApplicationManager::GetVirtualHost(const std::string& vhostName)
{
	ESPName2VirtualHostMap::iterator i = m_vhosts.find(vhostName);
	if(i != m_vhosts.end())
		return (*i).second;

	//todo: 创建ESPVirtualHost*并放入表中,然后返回
	return NULL;
}

ESPApplication* ESPApplicationManager::GetApplication(const std::string& vhostName, const std::string& appName)
{
	ESPVirtualHost* pVirtualHost = GetVirtualHost(vhostName);
	return (pVirtualHost ? pVirtualHost->GetApplication(appName) : NULL);
}

