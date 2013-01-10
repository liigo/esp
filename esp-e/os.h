#ifndef __OS_H__
#define __OS_H__


int OS_LoadLibrary (const char* szLibraryName);

bool OS_FreeLibrary (int hLibraryModule);

void* OS_GetProcAddress (int hLibraryModule, const char* szProcName);


#endif //__OS_H__
