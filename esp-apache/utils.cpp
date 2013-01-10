#include "utils.h"

#include <stdlib.h>
#include <stdio.h>

#ifdef WIN32
	#include <windows.h>
#else
	#include <unistd.h>
	#include<sys/types.h>
	#include<sys/stat.h>
#endif

//取当前可执行文件(或加载当前动态库的可执行文件)的完整路径文件名称
//返回值写入参数 filenameBuffer 中, 成功返回true, 失败返回false.
bool GetProcessImageFullFileName(char* filenameBuffer, int bufferLength)
{
#ifdef WIN32
	int nsize = GetModuleFileName(NULL, filenameBuffer, bufferLength-1);
	return (nsize > 0 && nsize < (bufferLength-1));
#else
	const static char* PROC_SELF_EXE = "/proc/self/exe";
	int nReadSize = readlink(PROC_SELF_EXE, filenameBuffer, bufferLength-1);
	return (nReadSize > 0);
#endif
}

//返回 mod_esp.so 的全路径文件名, 可能为NULL
//不要修改返回值
const char* GetESPModuleFileName()
{
	const int bufferLength = 1024;
	static char esp_so_file_name[bufferLength+1] = {0};

	if(GetProcessImageFullFileName(esp_so_file_name, bufferLength) == false)
		return NULL;
	
	// remove "bin/httpd.exe" and append "modules/mod_esp.so",
	// need at least 5 chars space in the buffer
	int len = strlen(esp_so_file_name);
	if(bufferLength - len < 5)
		return NULL;

	esp_so_file_name[len - strlen("bin/httpd.exe")] = '\0';

#ifdef WIN32
	strcat(esp_so_file_name, "modules\\mod_esp.so");
#else
	strcat(esp_so_file_name, "modules/mod_esp.so");
#endif
	
	return esp_so_file_name;
}

static int _PrintAPRTable_callback(void* rec, const char* key, const char* value)
{
	printf("    %s = %s \n", key, value);
	return 1;
}

void __PrintAPRTable(apr_table_t* table, const char* description)
{
	if(description)
		printf("apr_table %s: \n", description);
	else
		printf("apr_table: \n");

	apr_table_do(_PrintAPRTable_callback, NULL, table, NULL);

	printf("end table. \n\n");
}
