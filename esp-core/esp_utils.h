#ifndef __ESP_UTILS_H__
#define __ESP_UTILS_H__

#include <string>
#include <apr_pools.h>
#include <apr_thread_mutex.h>

bool ESP_ParsePageName(const char* szScriptName, std::string& fullPageName, std::string& libName, std::string& pageName);

//ThreadMutex, ThreadGuard

class ESPThreadMutex
{
private:
	apr_thread_mutex_t* m_mutex;
public:
	explicit ESPThreadMutex(apr_pool_t* pool);
	~ESPThreadMutex();

	bool Lock()    { return apr_thread_mutex_lock(m_mutex) == APR_SUCCESS; }
	bool TryLock() { return apr_thread_mutex_trylock(m_mutex) == APR_SUCCESS; }
	bool Unlock()  { return apr_thread_mutex_unlock(m_mutex) == APR_SUCCESS; }
};

class ESPThreadGuard
{
private:
	ESPThreadMutex& m_mutex;
public:
	ESPThreadGuard(ESPThreadMutex& mutex) : m_mutex(mutex)
	{
		m_mutex.Lock();
	}
	~ESPThreadGuard()
	{
		m_mutex.Unlock();
	}
};

#endif //__ESP_UTILS_H__
