#ifndef __ESP_LOG_H__
#define __ESP_LOG_H__

//---------------------------------------------------------
//#define LOG4C_ENABLE
#include "..\other\log4c-amalg\log4c_amalgamation.h"

#if defined(LOG4C_ENABLE) && !defined(ESP_LOG_INIT)

	#define ESP_LOG_INIT()   log_init_with_string("", "esp-log.config");
	#define ESP_LOG_FINIT()  LOG4C_FINI()

	//example: ESP_LOG((LOG_ERROR, "the value: %d", value))
	#define ESP_LOG(X) \
	{ \
		const struct ST_LogParam st_LogParam = log_vsnprintf_wrapper X; \
		log_msg( \
		__FILE__, \
		__LINE__, \
		/*DEFAULT_LOG_CATEGORY_NAME*/ "esp", \
		st_LogParam.iPriority, \
		st_LogParam.strMsg \
		); \
		free((char *)st_LogParam.strMsg); \
	}

	//example: ESP_CORE_LOG((LOG_ERROR, "the value: %d", value))
	#define ESP_CORE_LOG(X) \
	{ \
		const struct ST_LogParam st_LogParam = log_vsnprintf_wrapper X; \
		log_msg( \
		__FILE__, \
		__LINE__, \
		/*DEFAULT_LOG_CATEGORY_NAME*/ "esp-core", \
		st_LogParam.iPriority, \
		st_LogParam.strMsg \
		); \
		free((char *)st_LogParam.strMsg); \
	}

	//example: ESP_LOG_CATEGORY(("category", LOG_ERROR, "the value: %d", value))
	#define ESP_LOG_CATEGORY(X) \
	{ \
		const struct ST_LogParam st_LogParam = log_category_vsnprintf_wrapper X; \
		log_msg( \
		__FILE__, \
		__LINE__, \
		st_LogParam.strCategory, \
		st_LogParam.iPriority, \
		st_LogParam.strMsg \
		); \
		free((char *)st_LogParam.strMsg); \
	}

	//example: ESP_LOG_CATEGORY(("category", LOG_ERROR, "the value: %d", value))
	#define ESP_LOG_CATEGORY_NFL(X) \
	{ \
		const struct ST_LogParam st_LogParam = log_category_vsnprintf_wrapper X; \
		log_msg_no_file_num( \
		st_LogParam.strCategory, \
		st_LogParam.iPriority, \
		st_LogParam.strMsg \
		); \
		free((char *)st_LogParam.strMsg); \
	}

#endif

#ifndef LOG4C_ENABLE
	#define ESP_LOG_INIT()
	#define ESP_LOG_FINIT()
	#define ESP_LOG(X)
	#define ESP_CORE_LOG(X)
	#define ESP_LOG_CATEGORY(X)
	#define ESP_LOG_CATEGORY_NFL(X)
#endif

//---------------------------------------------------------

bool ESP_LogSetup(const char* logFileName);
void ESP_LogCleanup(void);
void ESP_Log(int type, const char* catalog, const char* data);
void ESP_LogFlush(void);

#endif //__ESP_LOG_H__
