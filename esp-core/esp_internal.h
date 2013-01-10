#ifndef __ESP_INTERNAL_H__
#define __ESP_INTERNAL_H__

#include <string>
#include <time.h>
#include <apr_dso.h>
#include <apr_tables.h>

void* _GetDSOSym(apr_dso_handle_t* dso_handle, const char* szSymName);
void PrintAPRTable(apr_table_t* table, const char* description);

time_t GetFileLastModifyTime(const char* file);


#endif //__ESP_INTERNAL_H__
