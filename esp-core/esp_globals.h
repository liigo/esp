#ifndef __ESP_GLOBALS_H__
#define __ESP_GLOBALS_H__

#include <stdlib.h>
#include <apr_pools.h>
#include <assert.h>
#include "esp_managers.h"

//使用ESP之前必须首先调用此函数!
void ESP_Initialize();
void ESP_Finalize();

class ESPGlobals;

//返回全局唯一的ESPGlobals引用, 等效于 ESPGlobals::GetInstance()
ESPGlobals& ESP_GetGlobals();

//全局根内存池(apr_pool_t*)
apr_pool_t* ESP_GetRootAPRPool();


class ESPGlobals
{
private:
	static ESPGlobals* m_instance;

	ESPObjectManager m_objectManager;

private:
	ESPGlobals() {}
	~ESPGlobals() {}
	ESPGlobals(const ESPGlobals& other);
	const ESPGlobals& operator=(const ESPGlobals& other);

public:
	//返回ESPGlobals的全局唯一对象实例指针
	static ESPGlobals* GetInstance()
	{
		if(m_instance == NULL)
		{
			m_instance = new ESPGlobals();
			atexit(DeleteInstance);
		}
		return m_instance;
	}

	static void DeleteInstance()
	{
		delete m_instance;
		m_instance = NULL;
	}

	apr_pool_t* GetPool() { return ESP_GetRootAPRPool(); }

	ESPObjectManager& GetObjectManager() { return m_objectManager; }
};


#endif //__ESP_GLOBALS_H__
