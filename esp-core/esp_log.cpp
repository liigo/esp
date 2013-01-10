//---------------------------------------------------------
//#define LOG4C_ENABLE
#define IMPLEMENT_LOG4C
#include "../other/log4c-amalg/log4c_amalgamation.h"
//---------------------------------------------------------

#include "esp_log.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>


// 写日志文件, by Liigo, 2012-5.

FILE* g_logfile;

bool ESP_LogSetup(const char* logFileName)
{
	if(logFileName)
	{
		g_logfile = fopen(logFileName, "wb");
		unsigned char utf8BOM[] = { 0xef, 0xbb, 0xbf };
		fwrite(utf8BOM, sizeof(char), sizeof(utf8BOM), g_logfile);
	}
	else
	{
		g_logfile = stdout;
	}

	return (g_logfile == NULL);
}

void ESP_LogCleanup(void)
{
	if(g_logfile && g_logfile != stdout)
	{
		fclose(g_logfile);
	}
	g_logfile = NULL;
}

static inline bool logText(const char* szText)
{
	if(szText && *szText)
	{
		fwrite(szText, 1, strlen(szText), g_logfile);
		return true;
	}
	return false;
}

static bool logType(int type)
{
	assert(type >= 0 && type <= 5);
	static const char* typeTextArray[] = { "", "[debug]", "[info]", "[warning]", "[error]", "[fatal]" };
	const char* typeText = typeTextArray[type];
	return logText(typeText);
}

static void logTime(void)
{
	time_t t = time(NULL);
	logText(asctime(localtime(&t)));
}

void ESP_Log(int type, const char* catalog, const char* data)
{
	if(g_logfile == NULL) return;

	if(logType(type)) logText(" - ");
	if(logText(catalog)) logText(" - ");
	logText("["); logTime(); logText("]: ");
	logText(data);
}

void ESP_LogFlush(void)
{
	if(g_logfile) fflush(g_logfile);
}
