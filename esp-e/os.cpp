
#ifdef WIN32
	#include <windows.h>
#elif _LINUX
	#include <dlfcn.h>
#endif

//////////////////////////////////////////////////////////////////////////
// 加载、卸载动态链接库，取动态库中的函数地址

int OS_LoadLibrary (const char* szLibraryName)
{
	int handle = 0;
#ifdef WIN32
	handle = (int) ::LoadLibrary(szLibraryName);
#elif _LINUX
	handle = (int) dlopen(szLibraryName, RTLD_LAZY);
#endif
	return handle;
}

bool OS_FreeLibrary (int hLibraryModule)
{
#ifdef WIN32
	return (::FreeLibrary((HMODULE)hLibraryModule) ? true : false);
#elif _LINUX
	return (dlclose((void*)hLibraryModule) ? true : false);
#endif
}

void* OS_GetProcAddress (int hLibraryModule, const char* szProcName)
{
#ifdef WIN32
	return (void*) ::GetProcAddress ((HMODULE)hLibraryModule, szProcName);
#elif _LINUX
	return (void*) dlsym ((void*)hLibraryModule, szProcName);
#endif
}
