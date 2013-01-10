#include "esp_internal.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <apr_dso.h>
#include <apr_strings.h>
#include <apr_tables.h>

#ifndef WIN32
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>
#endif

void* _GetDSOSym(apr_dso_handle_t* dso_handle, const char* szSymName)
{
	assert(dso_handle && szSymName);
	apr_dso_handle_sym_t sym;
	apr_status_t bOK = apr_dso_sym(&sym, dso_handle, szSymName);
	if(bOK == APR_SUCCESS && sym)
		return sym;
	else
		return NULL;
}

static int _PrintAPRTable_callback(void* rec, const char* key, const char* value)
{
	printf("    %s = %s \n", key, value);
	return 1;
}

void PrintAPRTable(apr_table_t* table, const char* description)
{
	if(description)
		printf("apr_table %s: \n", description);
	else
		printf("apr_table: \n");

	apr_table_do(_PrintAPRTable_callback, NULL, table, NULL);

	printf("end table. \n\n");
}

time_t GetFileLastModifyTime(const char* file)
{
#ifdef WIN32
	time_t ret_time = 0;
	HANDLE hFile = CreateFile(file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return ret_time;
	//You can also retrieve file times using the FindFirstFile and FindNextFile functions.
	FILETIME lastWriteTime;
	if(GetFileTime(hFile, NULL, NULL, &lastWriteTime))
	{
		SYSTEMTIME systime;
		if(FileTimeToSystemTime(&lastWriteTime, &systime))
		{
			tm t;
			t.tm_year = systime.wYear - 1900;
			t.tm_mon = systime.wMonth - 1;
			t.tm_mday = systime.wDay;
			t.tm_hour = systime.wHour;
			t.tm_min = systime.wMinute;
			t.tm_sec = systime.wSecond;
			t.tm_isdst = -1;
			ret_time = mktime(&t);
		}
	}
	CloseHandle(hFile);
	return ret_time;
#else
	struct stat st;
	return stat(file, &st) ? (time_t)0 : st.st_mtime;
#endif
}
