#ifndef __ESP_GLOBALS_H__
#define __ESP_GLOBALS_H__

#include <stdlib.h>
#include <apr_pools.h>
#include <assert.h>
#include "esp_managers.h"

//ʹ��ESP֮ǰ�������ȵ��ô˺���!
void ESP_Initialize();
void ESP_Finalize();

class ESPGlobals;

//����ȫ��Ψһ��ESPGlobals����, ��Ч�� ESPGlobals::GetInstance()
ESPGlobals& ESP_GetGlobals();

//ȫ�ָ��ڴ��(apr_pool_t*)
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
	//����ESPGlobals��ȫ��Ψһ����ʵ��ָ��
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
