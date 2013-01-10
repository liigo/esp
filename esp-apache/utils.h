#ifndef __MOD_ESP_UTILS_H__
#define __MOD_ESP_UTILS_H__

#include <apr_tables.h>

const char* GetESPModuleFileName();
void __PrintAPRTable(apr_table_t* table, const char* description);

#endif //__MOD_ESP_UTILS_H__
