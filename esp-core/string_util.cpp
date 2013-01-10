#include "string_util.h"
#include <assert.h>


bool char_iequal (char elem1, char elem2 )
{
	//std::locale loc; //! sgi stl no <local>
	//return std::tolower(elem1, loc) == std::tolower(elem2, loc);
	return tolower(elem1) == tolower(elem2);
}

//alloc a new str, need to be free use freestr()
//len can be -1
char* mallocstr(const char* szSrc, size_t len)
{
	if(szSrc == NULL || *szSrc == '\0' || len == 0)
		return NULL;
	char* szText = NULL;
	if(len == -1) len = strlen(szSrc);
	if(len > 0)
	{
		szText = (char*) malloc(len + 1);
		assert(szText);
		if(szText == NULL) return NULL;
		memcpy(szText, szSrc, len);
		szText[len] = '\0';
		return szText;
	}
	return NULL;
}

//free a str returned by mallocstr()
void freestr(char* sz)
{
	if(sz) free(sz);
}

//malloc a new bin, need to be free by freebin()
void* mallocbin(void* pDataSrc, size_t len)
{
	if(pDataSrc == NULL || len == 0)
		return NULL;
	void* pData = malloc(len);
	assert(pData);
	if(pData == NULL) return NULL;
	memcpy(pData, pDataSrc, len);
	return pData;
}

//free a bin returned by mallocbin()
void freebin(void* pData)
{
	if(pData) free(pData);
}
