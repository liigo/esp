/**********************************************************
* 版权所有 (C)2009, 
*
* 文件名称：log4c_amalgamation.h
* 内容摘要：日志记录头文件
* 其它说明：
* 当前版本：
* 作    者：温辉敏
* 完成日期：2009-7-18
*
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容：
*
*
使用说明:本日志系统比较简单就一个头文件即可实现日志模块以进行日志的记录.

(一.)C语言程序中记录日志

1.工程中任意一个 *.c 文件(记住只要一个c文件有下面的代码就OK，如main函数所在c文件)包含如下代码：
	#define IMPLEMENT_LOG4C
	#include "log4c_amalgamation.h"

2.其它要记录日志的*.c 文件包含如下代码:
	#include "log4c_amalgamation.h"

3.工程中要定义预定义宏定义 #define LOG4C_ENABLE,可以通过控制该宏定义开关来关闭日志模块

4.日志模块初始化代码，必须调用日志模块初始化代码后才能正确记录日志:
  下面的代码会自动在可执行程序目录下生成log4crc日志模块配置文件(若存在则不生成),
  配置文件中可以指定日志级别等（见8.日志配置文件log4crc文件内容）
	LOG4C_INIT_DEFAULT();

5.日志模块扫尾代码，程序退出时调用扫尾代码防止内存资源泄漏
	LOG4C_FINI();

6.可以记录日志了:
	LOG4C((LOG_ERROR, "Hello world! My age is %d, and my name is %s!", 28, "Jess" ));

7.例子:本工程包含main.c 和 test.c两个文件,使用了log4c_amalgamation.h头文件来记录日志
工程中预定义了#define LOG4C_ENABLE 宏定义
 main.c的代码:
------------------------------------------------------------------------------------------------
 #include <stdio.h>

 ///下面两条语句将日志模块的实现代码加入进来
 ///#define IMPLEMENT_LOG4C语句一定要在#include "log4c_amalgamation.h"语句之前。
 #define IMPLEMENT_LOG4C
 #include "log4c_amalgamation.h"

 extern void test();

 void main(int argc, char **argv)
 {
	 LOG4C_INIT_DEFAULT();

	 LOG4C((LOG_ERROR, "Hello world! My age is %d, and my name is %s!", 28, "Jess" ));
	 test();

	 LOG4C_FINI(); 
 }
-------------------------------------------------------------------------------------------------

 test.c的代码:
------------------------------------------------------------------------------------------------
 #include <stdio.h>
 #include "log4c_amalgamation.h"

 void test()
 {
	LOG4C((LOG_ERROR, "Hello world! My age is %d, and my name is %s!", 28, "Jess" ));
 }
------------------------------------------------------------------------------------------------

8.日志配置文件log4crc文件内容:
  8.1.priority的值即为日志级别,可以设置的有:fatal/alert/crit/error/warn/notice/info/debug/trace/notset/unknown/,
      各个日志级别越来越弱，fatal表示只有fatal的日志才输出，alert表示只有fatal/alert级别的日志才输出，其它一次类推，
	  unknown表输出所有级别的日志信息.
  8.2.maxsize的值为进行日志文件回滚时日志文件的大小,单位是字节。
  8.3.maxnum的值表示至多记录多少个日志文件,然后重新回滚到第一个日志文件名。
  8.4.prefix的值是生成日志文件的文件名前缀。
------------------------------------------------------------------------------------------------
<?xml version="1.0" encoding="ISO-8859-1"?>
<!DOCTYPE log4c SYSTEM "">

<log4c version="1.2.1">
<config>
<bufsize>0</bufsize>
<debug level="2"/>
<nocleanup>0</nocleanup>
<reread>1</reread>
</config>

<category name="root" priority="notice"  appender="aname"/>

<rollingpolicy name="a_policy_name" type="sizewin" maxsize="1048576" maxnum="15" />
<appender name="aname" type="rollingfile"  logdir="." prefix="log" layout="dated_threadid" rollingpolicy="a_policy_name" />

<appender name="stdout" type="stream" layout="dated_threadid"/>
<appender name="stderr" type="stream" layout="dated"/>
<appender name="syslog" type="syslog" layout="basic"/>
</log4c>

------------------------------------------------------------------------------------------------

**********************************************************/

#if !defined(AFX_LOG4C_AMALGAMATION_H__DD58A78D_C125_410F_B4C8_F0067B797121__INCLUDED_)
#define AFX_LOG4C_AMALGAMATION_H__DD58A78D_C125_410F_B4C8_F0067B797121__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///#if defined(LOG_USELOG4CXX)  && defined(__cplusplus)
#if defined(__cplusplus)
/************** Begin of config_log.h *******************************************/
/*
* config_log.h
* 
* 下面两个目录各有本文件的一个拷贝,两个文件是一样的
*		apache-log4cxx-0.10.0\apache-log4cxx-0.10.0\src\main\include\
*		apache-log4cxx-0.10.0\apache-log4cxx-0.10.0\src\main\Log4cxxWrapper\
* added by 温辉敏 in 2008-06-16
* 日志配置头文件
* 通过预编译头文件LOG_USELOG4CXX来控制是否使用log4cxx日志记录系统,
* 若没有定义LOG_USELOG4CXX预编译开关的话则不适用log4cxx的日志记录系统
* 要使用log4cxx日志记录系统时，可在本文件中定义LOG_USELOG4CXX宏定义，
*/
#if !defined(AFX_CONFIG_LOG_H__4735DC75_04BF_445A_9FB0_4146D6333F85__INCLUDED_)
#define AFX_CONFIG_LOG_H__4735DC75_04BF_445A_9FB0_4146D6333F85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if !defined( LOG_USELOG4CXX) && !defined(LOG4C_ENABLE)

#define PTODO_LINENUMBER_TO_STRING(x) #x
#define PTODO_LINENUMBER(x) PTODO_LINENUMBER_TO_STRING(x)
#define INCLUDE_FILE_AND_LINE(string) __FILE__"(" PTODO_LINENUMBER(__LINE__) "): "string

///#pragma message (INCLUDE_FILE_AND_LINE("温馨提示:只有定义了预编译开关定义了LOG_USELOG4CXX宏命令才使用log4cxx日志记录系统"))
#ifdef __cplusplus
#pragma message (INCLUDE_FILE_AND_LINE("温馨提示:只有定义了预编译开关定义了LOG4C_ENABLE或LOG_USELOG4CXX宏命令才使用log4cxx日志记录系统"))
#else
#pragma message (INCLUDE_FILE_AND_LINE("温馨提示:只有定义了预编译开关定义了LOG4C_ENABLE宏命令才使用log4cxx日志记录系统"))
#endif

#endif ///!defined( LOG_USELOG4CXX) && !defined(LOG4C_ENABLE)

///只有定义了LOG_USELOG4CXX宏命令才使用log4cxx日志记录系统
#if defined(LOG_USELOG4CXX)  && defined(__cplusplus)
///#include "log4c_cxxWrapper.h"

#ifndef DEFAULT_LOG_CATEGORY_NAME
#define DEFAULT_LOG_CATEGORY_NAME "root"
#endif
//////////////////////////////////////////////////////////////////////////

/**
* Predefined Levels of priorities. These correspond to the priority levels
* used by syslog(3).
**/
enum E_LOG_4C_LEVEL{
	/** fatal */	LOG_LEVEL_FATAL		= 000, 
	/** alert */	LOG_LEVEL_ALERT		= 100, 
	/** crit */	    LOG_LEVEL_CRIT		= 200, 
	/** error */	LOG_LEVEL_ERROR		= 300, 
	/** warn */	    LOG_LEVEL_WARN		= 400, 
	/** notice */	LOG_LEVEL_NOTICE	= 500, 
	/** info */	    LOG_LEVEL_INFO		= 600, 
	/** debug */	LOG_LEVEL_DEBUG		= 700,
	/** trace */	LOG_LEVEL_TRACE		= 800,
	/** notset */	LOG_LEVEL_NOTSET	= 900,
	/** unknown */	LOG_LEVEL_UNKNOWN	= 1000
} ;

/** 输出文件名和行号的日志输出宏
下面的宏定义采用了ostrstream类型的对象进行中转,可以输出对象如PTIME和CORBA::Exception& e等到输出流中
然后再输入到LOG4CXX_LOG宏定义中
*/ 
#define LOG4CXX(level, message) \
{ \
	using namespace std; \
	std::ostrstream ostrs; \
	ostrs << message << ends; \
	CLog4c::Instance()->LogMsg(__FILE__, __LINE__, level, ostrs.str(), ""); \
	ostrs.rdbuf()->freeze(0); \
}

/** 输出文件名和行号的日志输出宏
方便用户使用再定义一个新的宏定义
*/
#define LOG LOG4CXX

/** 不输出文件名和行号的日志输出宏
下面的宏定义采用了ostrstream类型的对象进行中转,可以输出对象如PTIME和CORBA::Exception& e等到输出流中
然后再输入到LOG4CXX_LOG宏定义中
*/ 
#define LOG4CXX_NO_FILENUM(level, message) \
{ \
	using namespace std; \
	std::ostrstream ostrs; \
	ostrs << message << ends; \
	CLog4c::Instance()->LogMsg(level, ostrs.str(), ""); \
	ostrs.rdbuf()->freeze(0); \
}

/** 不输出文件名和行号的日志输出宏
方便用户使用再定义一个新的宏定义
*/
#define LOG_NO_FILENUM LOG4CXX_NO_FILENUM	

/** 不输出文件名和行号和不进行任何格式转换(换行也没有)字符串原样输出的日志输出宏
下面的宏定义采用了ostrstream类型的对象进行中转,可以输出对象如PTIME和CORBA::Exception& e等到输出流中
然后再输入到LOG4CXX_LOG宏定义中
*/ 
#define LOG_NO_FILENUM_NO_LAYOUT(level, message) \
{ \
	using namespace std; \
	std::ostrstream ostrs; \
	ostrs << message << ends; \
	CLog4c::Instance()->LogMsgNoFileNumAndNoLayout(level, ostrs.str(), ""); \
	ostrs.rdbuf()->freeze(0); \
}

/** 不输出文件名和行号和不进行任何格式转换(换行也没有)字符串原样输出的日志输出宏
方便用户使用再定义一个新的宏定义
*/
#define LOG_ORIGIN LOG_NO_FILENUM_NO_LAYOUT	

/** Trace an execution block.
This macro creates a trace variable for tracking the entry and exit of program
blocks. It creates an instance of the PTraceBlock class that will output a
trace message at the line PTRACE_BLOCK is called and then on exit from the
scope it is defined in.
*/
#define LOG_BLOCK(name) \
	CLog4c::CBlock __trace_block_instance(__FILE__, __LINE__, name)

/** 记录函数进出的日志
自动输出当前所在的函数进出和对应的消息到日志文件中去
*/
#define LOG_FUN(message) \
	using namespace std; \
	std::ostrstream ostrs; \
	ostrs << "FUN<" << __FUNCTION__ << ">:" << message << ends; \
	CLog4c::CBlock __trace_block_instance(__FILE__, __LINE__, ostrs.str()); \
	ostrs.rdbuf()->freeze(0); 

/** Trace the execution of a line.
This macro outputs a trace of a source file line execution.
*/
#define LOG_LINE() \
{ \
	LOG4CXX(LOG_LEVEL_TRACE, "line:" << __LINE__); \
}

/**将内存中数据以十六进制方式打印出来的一个宏定义
作者:温辉敏 日期:2008-03-20
*/
#define LOG_HEX_DUMP(level, ptrBuffer, lBufferLen)	\
{	\
	char *ptrStr = CLog4c::sprintf_data((char*)(ptrBuffer), (lBufferLen));\
	LOG(level, ptrStr );\
	FREEP(ptrStr);\
}

/**采用sprintf的方式来输出日志,注意这里要使用两个括号:
LOG_PRINTF((LOG_ERROR, "Hello world! My age is %d, and my name is %s!", 8, "黄道义" ));
作者:温辉敏 日期:2009-04-20
*/
#define LOG_PRINTF(X) \
{ \
	const int iPriority = CLog4c::Instance()->GetPriorityWrapper X; \
	char * strMsg = (char *)CLog4c::Instance()->LogVsnprintfWrapper X; \
	CLog4c::Instance()->LogMsg( __FILE__, __LINE__, iPriority, strMsg, ""); \
	FREEP(strMsg); \
}

/** Output trace on condition.
This macro outputs a trace of any information needed, using standard stream
output operators. The output is only made if the conditional is TRUE. 
*/
#define LOG_IF(level, cond, message) \
{ \
	if(cond) \
	{ \
		LOG4CXX(level, message); \
	} \
}

/** 输出文件名和行号的日志输出宏,记录完日志直接return
下面的宏定义采用了ostrstream类型的对象进行中转,可以输出对象如PTIME和CORBA::Exception& e等到输出流中
然后再输入到LOG宏定义中
作者:温辉敏 日期:2009-04-21
*/ 
#define LOG_RETURN(level, message) \
{ \
	LOG(level, message); \
	return; \
}

/** 输出文件名和行号的日志输出宏,记录完日志直接return returnValue;
下面的宏定义采用了ostrstream类型的对象进行中转,可以输出对象如PTIME和CORBA::Exception& e等到输出流中
然后再输入到LOG宏定义中
作者:温辉敏 日期:2009-04-21
*/ 
#define LOG_RETURN_WITH_VALUE(level, message, returnValue) \
{ \
	LOG(level, message); \
	return returnValue; \
}

/**
LOG初始化函数,传入配置文件名
*/
#define LOG_INIT(strConfigFile) \
	CLog4c::Instance()->Init(strConfigFile);

/**
LOG初始化函数,传入配置文件的字符串内容
*/
#define LOG_INIT_WITH_STRING(X) \
	CLog4c::Instance()->InitWithString X;

/**日志记录模块初始化宏定义
LOG缺省初始化函数
注意事项: 必须初始化日志模块后才能正确记录日志
本初始化不要求应用程序所在目录有日志配置文件log4crc，会自动生成一个缺省的log4crc文件
使用例子: LOG_INIT_DEFAULT();
作者:温辉敏  日期:2009-7-22
*/
#define LOG_INIT_DEFAULT() \
	CLog4c::Instance()->Init("");

/************************************************************************
下面的为通过设置参数设置日志模块参数的宏定义(功能和LOG_INIT和LOG_INIT_DEFAULT类似):
1.必须先调用LOG_PARAM_XXXX系列宏定义设置参数,
1.1.如设置日志记录级别、生成日志文件名等。
1.2.若不LOG_PARAM_XXXX系列宏定义则将使用默认设置参数。
2.然后调用LOG_INIT_WITH_PARAM宏定义来初始化日志模块。
3.此时就可以记录日志了。
*/
#define LOG_PARAM_CFG_FILE_NAME(strCfgFileName) \
	LOG4C_PARAM_CFG_FILE_NAME(strCfgFileName) 
#define LOG_PARAM_LOG_LEVEL(strLogLevel) \
	LOG4C_PARAM_LOG_LEVEL(strLogLevel) 
#define LOG_PARAM_LOG_FILE_NAME(strLogFileName) \
	LOG4C_PARAM_LOG_FILE_NAME(strLogFileName) 
#define LOG_PARAM_LOG_FILE_SIZE(iFileSize) \
	LOG4C_PARAM_LOG_FILE_SIZE(iFileSize) 
#define LOG_PARAM_LOG_FILE_NUM(iFileNum) \
	LOG4C_PARAM_LOG_FILE_NUM(iFileNum)
#define LOG_PARAM_REREAD_LOG_CFG_FILE(bReReadLogCfgFile) \
	LOG4C_PARAM_REREAD_LOG_CFG_FILE(bReReadLogCfgFile)
#define LOG_INIT_WITH_PARAM() \
	LOG4C_INIT_WITH_PARAM()

#define LOG_INIT_WITH_PARAM_MULTI_PROCESS() \
	LOG4C_INIT_WITH_PARAM_MULTI_PROCESS()
/************************************************************************/

/**
LOG结束清理函数
*/
#define LOG_FINI() \
	CLog4c::DestroyInstance()


#else


#define LOG4CXX(level, message)
#define LOG LOG4CXX
#define LOG4CXX_NO_FILENUM(level, message)
#define LOG_NO_FILENUM LOG4CXX_NO_FILENUM	
#define LOG_NO_FILENUM_NO_LAYOUT(level, message)
#define LOG_ORIGIN LOG_NO_FILENUM_NO_LAYOUT
#define LOG_BLOCK(name)
#define LOG_FUN(message)
#define LOG_IF(level, cond, message)
#define LOG_LINE()
#define LOG_HEX_DUMP(level, ptrBuffer, lBufferLen)
#define LOG_PRINTF(X)
#define LOG_RETURN(level, message)
#define LOG_RETURN_WITH_VALUE(level, message, returnValue)
#define LOG_INIT(strConfigFile)
#define LOG_INIT_WITH_STRING(X)
#define LOG_INIT_DEFAULT()
#define LOG_FINI() 

#define LOG_PARAM_CFG_FILE_NAME(strCfgFileName) 
#define LOG_PARAM_LOG_LEVEL(iLogLevel) 
#define LOG_PARAM_LOG_FILE_NAME(strLogFileName) 
#define LOG_PARAM_LOG_FILE_SIZE(iFileSize) 
#define LOG_PARAM_LOG_FILE_NUM(iFileNum)
#define LOG_PARAM_REREAD_LOG_CFG_FILE(bReReadLogCfgFile)
#define LOG_INIT_WITH_PARAM()
#define LOG_INIT_WITH_PARAM_MULTI_PROCESS()

#endif ///defined(LOG_USELOG4CXX)  && defined(__cplusplus)

#endif // !defined(AFX_CONFIG_LOG_H__4735DC75_04BF_445A_9FB0_4146D6333F85__INCLUDED_)
/************** End of config_log.h *******************************************/
#endif /// defined(__cplusplus)
/************** Begin of log4c/defs.h *******************************************/
/* $Id$
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef __log4c_defs_h
#define __log4c_defs_h

/**
* @file defs.h
*
* @brief types and declarations enclosures for C++.
*
**/   

#ifdef  __cplusplus
# define __LOG4C_BEGIN_DECLS  extern "C" {
# define __LOG4C_END_DECLS    }
#else
# define __LOG4C_BEGIN_DECLS
# define __LOG4C_END_DECLS
#endif

#define LOG4C_INLINE inline
#define LOG4C_API    extern
#define LOG4C_DATA   extern

#ifdef __HP_cc
#define inline __inline
#endif

#ifdef _WIN32
///# include <log4c/config-win32.h>
#endif

#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 1000 + __GNUC_MINOR__)
#endif /* GCC_VERSION */

#if GCC_VERSION < 2009
#define OLD_VARIADIC_MACRO 1
#endif

#endif /* __log4c_defs_h */

/************** End of log4c/defs.h *******************************************/

#ifdef _WIN32
/************** Begin of log4c/config-win32.h *******************************************/

/* $Id$
*
* See the COPYING file for the terms of usage and distribution.
*/

/* This file defines some labels as required for
compiling with Microsoft Visual C++ 6
*/

#ifndef __log4c_config_win32_h
#define __log4c_config_win32_h

#include <time.h>
#include <windows.h>
#include <winsock.h>

//////////////////////////////////////////////////////////////////////////
/// 生成和使用dll时使用
#ifndef LOG4C_DATA
#define LOG4C_DATA
#endif

#ifndef LOG4C_API
#define LOG4C_API
#endif

#ifndef LOG4C_CLASS_API
#define LOG4C_CLASS_API
#endif

/* This is defined to be 'inline' by default,
but with msvc6 undef it so that inlined
functions are just normal functions.
*/
#undef LOG4C_INLINE
#define LOG4C_INLINE

#endif /* __log4c_config_win32_h */

/************** End of log4c/config-win32.h *******************************************/
#endif

/************** Begin of Log.h *******************************************/
/************************************************************************
 * Log.h
 *
 * added by 温辉敏 in 2008-2-3
 * 日志相关代码的头文件
 ************************************************************************/
#if !defined(AFX_LOG_H__4735DC75_04BF_445A_9FB0_4146D6333F85__INCLUDED_)
#define AFX_LOG_H__4735DC75_04BF_445A_9FB0_4146D6333F85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///用户不需要使用日志,不要定义LOG_USELOG4CXX和LOG4C_ENABLE宏命令就可以了
#if !defined(LOG_USELOG4CXX) && !defined(LOG4C_ENABLE)

#define LOG4C(X) 
#define LOG4C_INIT()

#define LOG4C_PARAM_CFG_FILE_NAME(strCfgFileName) 
#define LOG4C_PARAM_LOG_LEVEL(strLogLevel) 
#define LOG4C_PARAM_LOG_FILE_NAME(strLogFileName) 
#define LOG4C_PARAM_LOG_FILE_SIZE(iFileSize) 
#define LOG4C_PARAM_LOG_FILE_NUM(iFileNum)
#define LOG4C_PARAM_REREAD_LOG_CFG_FILE(bReReadLogCfgFile)
#define LOG4C_INIT_WITH_PARAM()
#define LOG4C_INIT_WITH_PARAM_MULTI_PROCESS()

#define LOG4C_FINI()
#define LOG4C_INIT_DEFAULT()

#define LOG4C_NO_FILENUM(X) 
#define LOG4C_NO_FILENUM_NO_LAYOUT(X)
#define LOG4C_ORIGIN LOG4C_NO_FILENUM_NO_LAYOUT
#define LOG4C_BLOCK_BEGIN(X)
#define LOG4C_BLOCK_END(X) 
#define LOG4C_FUN(X) 
#define LOG4C_IF(X)
#define LOG4C_LINE()
#define LOG4C_HEX_DUMP(X)
#define LOG4C_RETURN(X)
#define LOG4C_RETURN_WITH_VALUE(X, reurnValue)

#else

#include <stdlib.h>

/**日志记录模块初始化宏定义
注意事项: 必须初始化日志模块后才能正确记录日志
本初始化不要求应用程序所在目录有日志配置文件log4crc，会自动生成一个缺省的log4crc文件
使用例子: LOG4C_INIT_DEFAULT();
作者:温辉敏  日期:2009-7-17
*/
#define LOG4C_INIT_DEFAULT() \
	log_init_with_string("", "")

/**日志记录模块初始化宏定义
注意事项: 必须初始化日志模块后才能正确记录日志
本初始化要求应用程序所在目录有日志配置文件log4crc才行
使用例子: LOG4C_INIT();
作者:温辉敏  日期:2009-7-17
*/
#define LOG4C_INIT() \
	log_init()

/************************************************************************
下面的为通过设置参数设置日志模块参数的宏定义(功能和LOG4C_INIT和LOG4C_INIT_DEFAULT类似):
1.必须先调用LOG_PARAM_XXXX系列宏定义设置参数,
1.1.如设置日志记录级别、生成日志文件名等。
1.2.若不LOG_PARAM_XXXX系列宏定义则将使用默认设置参数。
2.然后调用LOG_INIT_WITH_PARAM宏定义来初始化日志模块。
3.此时就可以记录日志了。
*/
#define LOG4C_PARAM_CFG_FILE_NAME(strCfgFileName) \
	log_set_log_cfg_file_name(strCfgFileName)

#define LOG4C_PARAM_LOG_LEVEL(strLogLevel) \
	log_set_log_level(strLogLevel)

#define LOG4C_PARAM_LOG_FILE_NAME(strLogFileName) \
	log_set_log_file_name(strLogFileName)

#define LOG4C_PARAM_LOG_FILE_SIZE(iFileSize) \
	log_set_log_file_size(iFileSize)

#define LOG4C_PARAM_LOG_FILE_NUM(iFileNum) \
	log_set_log_file_num(iFileNum)

#define LOG4C_PARAM_REREAD_LOG_CFG_FILE(bReReadLogCfgFile) \
	log_set_reread_log_cfg_file(bReReadLogCfgFile)

#define LOG4C_INIT_WITH_PARAM() \
	log_init_with_param()

#define LOG4C_INIT_WITH_PARAM_MULTI_PROCESS() \
	log_init_with_param_multi_process()

/************************************************************************/

/**日志记录模块结束宏定义
注意事项: 必须正确结束日志模块后才不会造成内存、资源泄漏
使用例子: LOG4C_FINI();
作者:温辉敏  日期:2009-7-17
*/
#define LOG4C_FINI() \
	log_fini()

/**日志记录宏定义
注意事项: 使用时参数必须使用两个括号括起来，LOG4C((X));见下面例子
使用例子: LOG4C((LOG_ERROR, "Hello World! My Name is %s, and my age is %d ", "Jess", "28" ));
作者:温辉敏  日期:2008-2-4
*/
#define LOG4C(X) \
{ \
	const struct ST_LogParam st_LogParam = log_vsnprintf_wrapper X; \
	log_msg( \
	__FILE__, \
	__LINE__, \
	DEFAULT_LOG_CATEGORY_NAME, \
	st_LogParam.iPriority, \
	st_LogParam.strMsg \
	); \
	free((char *)st_LogParam.strMsg); \
}

#define LOG4C_NO_FILENUM(X) \
{ \
	const struct ST_LogParam st_LogParam = log_vsnprintf_wrapper X; \
	log_msg_no_file_num( \
	DEFAULT_LOG_CATEGORY_NAME, \
	st_LogParam.iPriority, \
	st_LogParam.strMsg \
	); \
	free((char *)st_LogParam.strMsg); \
}

#define LOG4C_NO_FILENUM_NO_LAYOUT(X) \
{ \
	const struct ST_LogParam st_LogParam = log_vsnprintf_wrapper X; \
	log_msg_no_file_num_no_layout( \
	DEFAULT_LOG_CATEGORY_NAME, \
	st_LogParam.iPriority, \
	st_LogParam.strMsg \
	); \
	free((char *)st_LogParam.strMsg); \
}

#define LOG4C_ORIGIN LOG4C_NO_FILENUM_NO_LAYOUT

#define LOG4C_BLOCK_BEGIN(X) \
{ \
	const struct ST_LogParam st_LogParam = log_vsnprintf_wrapper_msg X; \
	log4c_block_begin(__FILE__, __LINE__, st_LogParam.strMsg);\
	free((char *)st_LogParam.strMsg); \
}

#define LOG4C_BLOCK_END(X) \
{	\
	const struct ST_LogParam st_LogParam = log_vsnprintf_wrapper_msg X; \
	log4c_block_end(__FILE__, __LINE__, st_LogParam.strMsg);\
	free((char *)st_LogParam.strMsg); \
}

#define LOG4C_FUN(X) \
{ \
	const struct ST_LogParam st_LogParam = log_vsnprintf_wrapper_msg X; \
	const char *ptrStrMsg = log_vsnprintf_wrapper_fun_msg(__FUNCTION__, st_LogParam.strMsg); \
	log_msg(\
		__FILE__, \
		__LINE__, \
		DEFAULT_LOG_CATEGORY_NAME, \
		LOG4C_PRIORITY_TRACE, \
		ptrStrMsg \
		);\
	free((char *)st_LogParam.strMsg); \
	free((char *)ptrStrMsg); \
}

/** Output trace on condition.
This macro outputs a trace of any information needed, using standard stream
output operators. The output is only made if the conditional is TRUE. 
example: LOG4C_IF((4>3, LOG4C_PRIORITY_TRACE, "HELLO"));
*/
#define LOG4C_IF(X) \
{ \
	const struct ST_LogParam st_LogParam = log_condition_vsnprintf_wrapper X; \
	if( st_LogParam.iCondition ) \
	{ \
		log_msg( \
			__FILE__, \
			__LINE__, \
			DEFAULT_LOG_CATEGORY_NAME, \
			st_LogParam.iPriority, \
			st_LogParam.strMsg \
		); \
	} \
	free((char *)st_LogParam.strMsg); \
}

/** Trace the execution of a line.
This macro outputs a trace of a source file line execution.
*/
#define LOG4C_LINE() \
{ \
	char strBuffer[128] = {0}; \
	_snprintf(strBuffer, sizeof(strBuffer), "line:%d", __LINE__);\
	log_msg( \
		__FILE__, \
		__LINE__, \
		DEFAULT_LOG_CATEGORY_NAME, \
		LOG4C_PRIORITY_TRACE, \
		strBuffer \
		); \
}

/**将内存中数据以十六进制方式打印出来的一个宏定义
example:LOG4C_HEX_DUMP((LOG4C_PRIORITY_TRACE, strHexBuf, iHexBufLen));
作者:温辉敏 日期:2009-07-24
*/
#define LOG4C_HEX_DUMP(X)	\
{	\
	const struct ST_LogParam st_LogParam = log_hex_dump_vsnprintf_wrapper X; \
	char *ptrStr = log4c_sprintf_data((char*)(st_LogParam.strHexBuf), (st_LogParam.iHexBufLen));\
	log_msg( \
		__FILE__, \
		__LINE__, \
		DEFAULT_LOG_CATEGORY_NAME, \
		st_LogParam.iPriority, \
		ptrStr \
		); \
	free(ptrStr);\
}

/** 输出文件名和行号的日志输出宏,记录完日志直接return
然后再输入到LOG宏定义中
作者:温辉敏 日期:2009-04-21
*/ 
#define LOG4C_RETURN(X) \
{ \
	LOG4C(X); \
	return; \
}

/** 输出文件名和行号的日志输出宏,记录完日志直接return returnValue;
然后再输入到LOG宏定义中
example:LOG4C_RETURN_WITH_VALUE(( LOG4C_PRIORITY_TRACE, "message%d", 1), returnValue);
作者:温辉敏 日期:2009-04-21
*/ 
#define LOG4C_RETURN_WITH_VALUE(X, returnValue) \
{ \
	LOG4C(X); \
	return returnValue; \
}

#endif ///!defined(LOG_USELOG4CXX) 	&& 	!defined(LOG4C_ENABLE)

#if ((defined(LOG_USELOG4CXX) && defined(__cplusplus)) || defined(LOG4C_ENABLE)) 

#ifdef _WIN32
///log4c正确使用必须的一些宏定义
#define snprintf _snprintf

#ifndef HAVE_CONFIG_H
	#define HAVE_CONFIG_H
#endif
///#define LOG4C_EXPORTS
#endif

///定义linux下使用到而不存在的类型
#ifdef linux
	///typedef int BOOL;
#ifndef BOOL 
	#define BOOL int
	#define FALSE 0
	#define TRUE 1
#endif
	#define _snprintf snprintf
	///#define _x_strncpy strncpy
#endif

///进行LOG宏定义参数获取的结果
struct ST_LogParam
{
	char *strMsg;
	int iPriority;

	///LOG4C_IF时的条件参数
	int iCondition;

	///LOG4C_HEX_DUMP时的参数
	char *strHexBuf;
	int iHexBufLen;

	///category名 add by liigo, see: log_category_vsnprintf_wrapper()
	const char* strCategory;
};

/// 日志输出缺省category
#ifndef DEFAULT_LOG_CATEGORY_NAME
	#define DEFAULT_LOG_CATEGORY_NAME "root"
#endif

/** 日志记录级别
*/
/** fatal */	#define LOG_FATAL		LOG4C_PRIORITY_FATAL	
/** alert */	#define LOG_ALERT		LOG4C_PRIORITY_ALERT	
/** crit */	    #define LOG_CRIT		LOG4C_PRIORITY_CRIT		
/** error */	#define LOG_ERROR		LOG4C_PRIORITY_ERROR	
/** warn */	    #define LOG_WARN		LOG4C_PRIORITY_WARN		
/** notice */	#define LOG_NOTICE		LOG4C_PRIORITY_NOTICE	
/** info */	    #define LOG_INFO		LOG4C_PRIORITY_INFO		
/** debug */	#define LOG_DEBUG		LOG4C_PRIORITY_DEBUG	
/** trace */	#define LOG_TRACE		LOG4C_PRIORITY_TRACE	
/** notset */	#define LOG_NOTSET		LOG4C_PRIORITY_NOTSET	
/** unknown */	#define LOG_UNKNOWN		LOG4C_PRIORITY_UNKNOWN

///#include <log4c/defs.h>

__LOG4C_BEGIN_DECLS

/** 日志模块初始化
@return int:return 0 for success 
作者:温辉敏  日期:2008-2-3
*/
LOG4C_API int log_init();

/** 日志模块初始化,指定配置文件名称
@return int:return 0 for success 
作者:温辉敏  日期:2008-9-5
*/
LOG4C_API int log_init_with_cfg_file(const char *strCfgFileName);

/** 日志模块清理
@return int:return 0 for success 
作者:温辉敏  日期:2008-2-3
*/
LOG4C_API int log_fini();

/**宏参数抽取priority函数
本函数接受LOG_DEBUG(X)的参数，并从该宏定义的参数中返回priority的值
@return const int : iPriority.
作者:温辉敏  日期:2008-2-4
*/
LOG4C_API const int log_get_priority_wrapper(
	const int iPriority,	///日志记录级别
	const char* strFormat,	///日志内容格式
	...						///日志内容
	);

/**
将大小为count的缓冲区中内容按字节以16进制字符串打印出来,
返回值即为指向相应的字符串，
该返回指向的存储区域要调用本函数的用户显示的进行删除
*/
LOG4C_API char * log4c_sprintf_data(char *buff, int count);

/**vsnprintf函数的wrapper函数
本函数只使用第二个及以后的参数,使用vsnprintf函数将strFormat和后面的不定参数va_list va;以
vsnprintf(strMsg, sizeof(strMsg), strFormat, va);
形式格式化输出到一缓冲区中并以字符串的形式返回
作者:温辉敏  日期:2008-2-4
*/
LOG4C_API const struct ST_LogParam log_vsnprintf_wrapper(
	const int iPriority,	///日志记录级别
	const char* strFormat,	///日志内容格式
	...						///日志内容
	);

/*by liigo*/
LOG4C_API const struct ST_LogParam log_category_vsnprintf_wrapper(
	const char* category,	///category名
	const int iPriority,	///日志记录级别
	const char* strFormat,	///日志内容格式
	...						///日志内容
	);

/**vsnprintf函数的wrapper函数
本函数只使用第二个及以后的参数,使用vsnprintf函数将strFormat和后面的不定参数va_list va;以
vsnprintf(strMsg, sizeof(strMsg), strFormat, va);
形式格式化输出到一缓冲区中并以字符串的形式返回
作者:温辉敏  日期:2008-2-4
*/
LOG4C_API const struct ST_LogParam log_condition_vsnprintf_wrapper(
	const int iCondition,	///条件
	const int iPriority,	///日志记录级别
	const char* strFormat,	///日志内容格式
	...						///日志内容
	);

LOG4C_API const struct ST_LogParam log_hex_dump_vsnprintf_wrapper(
	const int iPriority,	///日志记录级别
	const char* strHexBuf,	///缓冲区首地址
	const int iHexBufLen,	///缓冲区长度
	...						///日志内容
	);

/**vsnprintf函数的wrapper函数
本函数只使用第二个及以后的参数,使用vsnprintf函数将strFormat和后面的不定参数va_list va;以
vsnprintf(strMsg, sizeof(strMsg), strFormat, va);
形式格式化输出到一缓冲区中并以字符串的形式返回
作者:温辉敏  日期:2008-2-4
*/
LOG4C_API const struct ST_LogParam log_vsnprintf_wrapper_msg(
	const char* strFormat,	///日志内容格式
	...						///日志内容
	);

/**vsnprintf函数的wrapper函数
本函数只使用第二个及以后的参数,使用vsnprintf函数将strFormat和后面的不定参数va_list va;以
vsnprintf(strMsg, sizeof(strMsg), strFormat, va);
形式格式化输出到一缓冲区中并以字符串的形式返回
作者:温辉敏  日期:2008-2-4
*/
const char * log_vsnprintf_wrapper_fun_msg(
	const char* strFunName,	///函数名
	const char* strFormat,	///日志内容格式
	...						///日志内容
	);

/** 日志记录
日志记录为一个字符串指针指向的内容
@return void
作者:温辉敏  日期:2008-2-3
*/
LOG4C_API void log_msg(
			const char *strFile,	///文件名
			const int iLineNum,		///行号
			const char *strCatName,	///category名
			const int iPriority,	///日志记录级别
			const char *strFormat,	///日志内容格式
			...						///日志内容
			);

/** 日志记录,不记录文件名和行号
日志记录为一个字符串指针指向的内容
@return void
作者:温辉敏  日期:2008-2-3
*/
LOG4C_API void log_msg_no_file_num(
			const char *strCatName,	///category名
			const int iPriority,	///日志记录级别
			const char *strFormat,	///日志内容格式
			...						///日志内容
			);

/** 日志记录,不记录文件名和行号,没有任何layout转换，直接输出相应的字符文本到日志中
此条记录没有行号，也没有线程号，也没有回车等
日志记录为一个字符串指针指向的内容
@return void
作者:温辉敏  日期:2008-9-14
*/
LOG4C_API void log_msg_no_file_num_no_layout(
		   const char *strCatName,	///category名
		   const int iPriority,		///日志记录级别
		   const char *strFormat,	///日志内容格式
		   ...						///日志内容
		   );


/** 日志模块初始化
以日志配置文件字符串内容和日志配置文件命作为参数
若相应配置文件存在则使用，否则按照给定内容和文件名创建日志配置文件并使用之
@return int，0 表成功
作者:温辉敏  日期:2008-2-3
*/
LOG4C_API int log_init_with_string(
			const char *strFileContent,
			const char *strFileName 
			);

/** 日志模块初始化
以日志配置文件命作为参数
@return int，0 表成功
作者:温辉敏  日期:2008-2-3
*/
LOG4C_API int log_init_with_cfg_file_wrapper(
			const char * strConfigFile
			);

/** 日志模块初始化-日志配置文件的文件名设置
以日志配置文件命作为参数
@return void
作者:温辉敏  日期:2009-7-20
*/
LOG4C_API void log_set_log_cfg_file_name(const char *strFileName);

/** 日志模块初始化-生成的日志文件的文件名设置
以日志文件命作为参数
@return void
作者:温辉敏  日期:2009-7-20
*/
LOG4C_API void log_set_log_file_name(const char *strFileName);

/** 日志模块初始化-日志记录级别设置
@return void
作者:温辉敏  日期:2009-7-20
*/
LOG4C_API void log_set_log_level(const char *strLogLevel);

/** 日志模块初始化-日志记录文件的大设置
@return void
作者:温辉敏  日期:2009-7-20
*/
LOG4C_API void log_set_log_file_size(const int iFileSize);

/** 日志模块初始化-日志记录文件的个数设置
记录到最大个数后将回滚重复覆盖第一个日志文件，依次类推
@return void
作者:温辉敏  日期:2009-7-20
*/
LOG4C_API void log_set_log_file_num(const int iFileNum);

/** 日志模块初始化-是否实时读取日志配置文件
设置是否每次记录时都读取日志配置文件
@param:const BOOL m_bReReadLogCfgFile
@return void
作者:温辉敏  日期:2009-7-20
*/
LOG4C_API void log_set_reread_log_cfg_file(const BOOL bReReadLogCfgFile);

/** 日志模块初始化-带参数进行日志模块初始化
这里的参数则为上面的几个API设置的参数，
所以本函数一定要在日志配置参数设置好之后调用设置的参数才能生效的
@return int,LOG4C_OK,成功;LOG4C_FAILURE,失败
作者:温辉敏  日期:2009-7-20
*/
LOG4C_API int log_init_with_param();

/** 日志模块初始化-带参数进行日志模块初始化,程序的多个运行实例产生的日志不互相冲突
这里的参数则为上面的几个API设置的参数，
所以本函数一定要在日志配置参数设置好之后调用设置的参数才能生效的
@return int,LOG4C_OK,成功;LOG4C_FAILURE,失败
作者:温辉敏  日期:2009-7-21
*/
LOG4C_API int log_init_with_param_multi_process();

/** 日志记录Block方式能清楚的表明调用层次
类似下面这种B-Entry类型日志:
main.cpp(87) B-Entry	==> main
main.cpp(90) B-Entry	====> main_01
main.cpp(92) B-Entry	======> main_02
main.cpp(92) B-Exit	<====== main_02 
main.cpp(90) B-Exit	<==== main_01
@return void
作者:温辉敏  日期:2009-7-24
*/
LOG4C_API void log4c_block_begin(const char * fileName, int lineNum, const char * traceName);

/** 日志记录Block方式能清楚的表明调用层次
类似下面这种B-Exit类型日志:
main.cpp(87) B-Entry	==> main
main.cpp(90) B-Entry	====> main_01
main.cpp(92) B-Entry	======> main_02
main.cpp(92) B-Exit	<====== main_02 
main.cpp(90) B-Exit	<==== main_01
@return void
作者:温辉敏  日期:2009-7-24
*/
LOG4C_API void log4c_block_end(const char * fileName, int lineNum, const char * traceName);

/**检测配置文件是否存在
@return const int : iPriority.
作者:温辉敏  日期:2008-2-18
*/
extern const int log_check(void);

/**检测配置文件是否存在,只检测传入的配置文件名
@return const int : iPriority.
作者:温辉敏  日期:2008-9-4
*/
extern const int log_check_with_cfg_file(const char *strCfgFileName);

/**宏参数抽取format函数
本函数接受LOG_DEBUG(X)的参数，并从该宏定义的参数中返回format的值
@return const char* : strFormat
作者:温辉敏  日期:2008-2-4
*/
extern const char* log_get_format_wrapper(
	const int iPriority,	///日志记录级别
	const char* strFormat,	///日志内容格式
	...						///日志内容
	);


/** 设置appender
@return int:
作者:温辉敏  日期:2008-2-3
*/
extern int log_setappender(
			const char *strCatName,		///category名
			const char *strAppenderName ///appender名
			);

/** 日志记录
支持类似printf函数的带格式输出
@return void
作者:温辉敏  日期:2008-2-3
*/
extern void log_log(
			const char *strCatName,	///category名
			const int iPriority,	///日志记录级别
			const char *strFormat,	///日志内容格式
			...						///日志内容
			);

/** 日志模块初始化-日志模块使用实例个数自增
@return void
作者:温辉敏  日期:2009-7-21
*/
extern void IncreaseLogModuleUsage();

__LOG4C_END_DECLS

///#include "log4c.h"
#endif ///((defined(LOG_USELOG4CXX) && defined(__cplusplus)) || defined(LOG4C_ENABLE))

#endif // !defined(AFX_LOG_H__4735DC75_04BF_445A_9FB0_4146D6333F85__INCLUDED_)
/************** End of Log.h *******************************************/

#if ( defined(LOG_USELOG4CXX) && defined(__cplusplus) )|| defined(LOG4C_ENABLE)

__LOG4C_BEGIN_DECLS

/************** Begin of log4c/version.h *******************************************/
/* $Id$
*
* version.h
* 
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef log4c_version_h
#define log4c_version_h

/**
* @file version.h
*
* @brief log4c version information
**/

///#include <log4c/defs.h>

__LOG4C_BEGIN_DECLS

/**
* constant macro holding the major version of log4c
**/
#define LOG4C_MAJOR_VERSION 1
/**
* constant macro holding the minor version of log4c
**/
#define LOG4C_MINOR_VERSION 2
/**
* constant macro holding the micro version of log4c
**/
#define LOG4C_MICRO_VERSION 1

/**
* constant variable holding the major version of log4c
**/
extern const int log4c_major_version;
/**
* constant variable holding the minor version of log4c
**/
extern const int log4c_minor_version;
/**
* constant variable holding the micro version of log4c
**/
extern const int log4c_micro_version;

/**
* @return a string containing the full log4c version
**/
extern const char* log4c_version(void);

__LOG4C_END_DECLS

#endif
/************** End of log4c/version.h *******************************************/

/************** Begin of log4c/init.h *******************************************/
/* $Id$
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef __log4c_init_h
#define __log4c_init_h

///#include <log4c/defs.h>
#include <stdio.h>

/**
* @file init.h
*
* @brief log4c constructors and destructors
*
**/   

/**
* constructor
* 
* @returns 0 for success 
**/
LOG4C_API int log4c_init(void);

/**
* another constructor
* 
* 带有配置文件名的初始化函数
* 完成功能和log4c_init完全一致，只是这里的配置文件名以参数形式传入的
* @returns 0 for success .
* 作者:温辉敏 日期:2008-9-6
*/
LOG4C_API int log4c_init_with_cfg_file(const char *strCfgFileName);

/**
* destructor
*
* @returns 0 for success 
**/
LOG4C_API int log4c_fini(void);

/*
* Dumps all the current appender, layout and rollingpolicy types
* known by log4c.
* @param stream to write to
*/
LOG4C_API void log4c_dump_all_types(FILE *fp);

/*
* Dumps all the current instances of categories, appenders, layouts
* and rollingpolicy objects.
* An instances of a type consists of the base
* type information (name plus function table) and an instance name and
* configuration.  For example one can have an instance of the rollingfile
* appender which logs to /var/tmp and another instance which logs to 
* /usr/tmp.  They are both of type rollingfile, but are distinct instances of
* it
* @param stream to write t
*/
LOG4C_API void log4c_dump_all_instances(FILE *fp);

#endif

/************** End of log4c/init.h *******************************************/

/************** Begin of log4c/rc.h *******************************************/
/* $Id$
*
* rc.h
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef __log4c_rc_h
#define __log4c_rc_h

/**
* @file rc.h
*
* @brief log4c resource configuration
*
**/

///#include <log4c/defs.h>

__LOG4C_BEGIN_DECLS

/**
* @brief resource configuration object
*
* Attributes description:
* 
* @li @c nocleanup don't perform memory cleanup in log4c library 
*        destructor or in log4c_fini()
* @li @c bufsize maximum logging buffer size. 0 for no limits
* @li @c debug activate log4c debugging
**/
typedef struct 
{
	struct 
	{
		int nocleanup;
		int bufsize;
		int debug;
		int reread;
	} config;

} log4c_rc_t;

/**
* default log4c resource configuration object
**/
// 修改 [7/21/2008 温辉敏]
///LOG4C_API log4c_rc_t * const	log4c_rc;
LOG4C_DATA log4c_rc_t * const	log4c_rc;

/**
* load log4c resource configuration file
*
* @param a_filename name of file to load
**/
LOG4C_API int log4c_load(const char* a_filename);

/**
* @internal
**/
LOG4C_API int log4c_rc_load(log4c_rc_t* a_rc, const char* a_filename);

/*
* Rereads any log4crc files that have changed
*/
LOG4C_API void log4c_reread(void);

__LOG4C_END_DECLS

#endif

/************** End of log4c/rc.h *******************************************/

/************** Begin of log4c/buffer.h *******************************************/
/* $Id$
*
* buffer.h
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef __log4c_buffer_h
#define __log4c_buffer_h

/**
* @file buffer.h
*
* @brief log4c buffer
*
**/

///#include <log4c/defs.h>
#include <stddef.h>

__LOG4C_BEGIN_DECLS

/**
* @brief buffer object
*
* Attributes description:
*
* @li @c size current size of the buffer
* @li @c maxsize maximum size of the buffer. 0 means no limitation.
* @li @c data raw data
**/
typedef struct
{
	size_t buf_size;
	size_t buf_maxsize;
	char*  buf_data;

} log4c_buffer_t;

#define LOG4C_BUFFER_SIZE_DEFAULT  512

#define LOG4C_BUFFER_SIZE_MAX 1024*10

__LOG4C_END_DECLS

#endif
/************** End of log4c/buffer.h *******************************************/

/************** Begin of log4c/location_info.h *******************************************/
/* $Id$
*
* location_info.h
* 
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.


* See the COPYING file for the terms of usage and distribution.
*/

#ifndef log4c_location_info_h
#define log4c_location_info_h

/**
* @file location_info.h
*
* @brief The internal representation of caller location information.
* 
* When a affirmative logging decision is made a log4c_location_info_t is
* created and is passed around the different log4c components.
**/

///#include <log4c/defs.h>

__LOG4C_BEGIN_DECLS

/**
* @brief logging location information
*
* Attributes description:
* 
* @li @c loc_file file name
* @li @c loc_line file line
* @li @c loc_function function name
* @li @c loc_data user data
*
* @todo ptrThis is not used
**/
typedef struct 
{
	const char* loc_file;
	int loc_line;
	const char* loc_function;
	void* loc_data;

} log4c_location_info_t;

/**
* log4c_location_info_t initializer 
**/
#ifdef __GNUC__
#   define LOG4C_LOCATION_INFO_INITIALIZER(user_data) { __FILE__, __LINE__, __FUNCTION__, user_data }
#else
#   define LOG4C_LOCATION_INFO_INITIALIZER(user_data) { __FILE__, __LINE__, "(nil)", user_data }
#endif

#define __log4c_str(n) #n

#ifdef __GNUC__
#   define __log4c_location(n)	__FUNCTION__ "() at " __FILE__ ":" __log4c_str(n)
#else
#   define __log4c_location(n)	__FILE__ ":" __log4c_str(n)
#endif

/**
* This macro returns the literal representation of a logging event
* location
**/
#define log4c_location __log4c_location(__LINE__)

__LOG4C_END_DECLS

#endif
/************** End of log4c/location_info.h *******************************************/

/************** Begin of log4c/logging_event.h *******************************************/
/* $Id$
*
* logging_event.h
* 
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef log4c_logging_event_h
#define log4c_logging_event_h

/**
* @file logging_event.h
*
* @brief the internal representation of logging events. 
* 
* When a affirmative logging decision is made a log4c_logging_event
* instance is created. This instance is passed around the different log4c
* components.
**/

///#include <log4c/defs.h>
///#include <log4c/buffer.h>
///#include <log4c/location_info.h>
#ifndef _WIN32
#include <sys/time.h>
#endif

__LOG4C_BEGIN_DECLS

struct __log4c_category;

/**
* @brief logging event object
* 
* Attributes description:
* 
* @li @c evt_category category name. 
* @li @c evt_priority priority of logging event.
* @li @c evt_msg The application supplied message of logging event.
* @li @c evt_buffer a pre allocated buffer to be used by layouts to
*        format in a multi-thread environment.
* @li @c evt_rendered_msg The application supplied message after layout format.
* @li @c evt_timestamp The number of seconds elapsed since the epoch
* (1/1/1970 00:00:00 UTC) until logging event was created.
* @li @c evt_loc The event's location information 
**/
typedef struct 
{
	const char* evt_category;
	int	evt_priority;
	const char* evt_msg;
	const char* evt_rendered_msg;
	log4c_buffer_t evt_buffer;
	/* ok, ptrThis is probably not a good way to do it--should define a common type here
	and have the base acessor function do the mapping
	*/
#ifndef _WIN32
	struct timeval evt_timestamp;
#else
	FILETIME evt_timestamp;
#endif
	const log4c_location_info_t* evt_loc;

} log4c_logging_event_t;

/**
* Constructor for a logging event.
*
* @param a_category the category name
* @param a_priority the category initial priority
* @param a_message the message of ptrThis event
*
* @todo need to handle multi-threading (NDC)
**/
LOG4C_API log4c_logging_event_t* log4c_logging_event_new(
	const char* a_category,
	int		a_priority,
	const char*	a_message
);

/**
* Destructor for a logging event.
* @param a_event the logging event object
**/
LOG4C_API void log4c_logging_event_delete(log4c_logging_event_t* a_event);

__LOG4C_END_DECLS

#endif

/************** End of log4c/logging_event.h *******************************************/

/************** Begin of log4c/layout.h *******************************************/
/* $Id$
*
* layout.h
* 
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef log4c_layout_h
#define log4c_layout_h

/**
* @file layout.h
*
* @brief Interface for user specific layout format of log4c_logging_event
* events. 
*
* @todo the layout interface needs a better configuration system
* depending on the layout type. The udata field is a just a trick.
*
* @todo a pattern layout would be welcomed !!
**/

///#include <log4c/defs.h>
///#include <log4c/logging_event.h>
#include <stdio.h>

__LOG4C_BEGIN_DECLS

struct __log4c_layout;

/**
* log4c layout class 
**/
typedef struct __log4c_layout log4c_layout_t;

/**
* @brief log4c layout type class
*
* Attributes description:
* 
* @li @c name layout type name 
* @li @c format 
**/
typedef struct log4c_layout_type {
	const char* name;
	const char* (*format) (const log4c_layout_t*, const log4c_logging_event_t*);
} log4c_layout_type_t;

/**
* Get a pointer to an existing layout type.
*
* @param a_name the name of the layout type to return.  
* @returns a pointer to an existing layout type, or NULL if no layout
* type with the specified name exists.
**/
LOG4C_API const log4c_layout_type_t* log4c_layout_type_get(const char* a_name);

/**
* Use ptrThis function to register a layout type with log4c.
* Once ptrThis is done you may refer to ptrThis type by name both 
* programatically and in the log4c configuration file.
*
* @param a_type a pointer to the new layout type to set.
* @returns a pointer to the previous layout type of same name.
*
* Example code fragment: 
* @code
* 
* const log4c_layout_type_t log4c_layout_type_xml = {
*    "s13_xml",
*    xml_format,
* };
*  
* log4c_layout_type_set(&log4c_layout_type_xml);
*
* @endcode
**/
LOG4C_API const log4c_layout_type_t* log4c_layout_type_set(
	const log4c_layout_type_t* a_type);

/**
* Get a pointer to an existing layout.
*
* @param a_name the name of the layout to return.
* @returns a pointer to an existing layout, or NULL if no layout
* with the specfied name exists.
**/
LOG4C_API log4c_layout_t* log4c_layout_get(const char* a_name);

/**
* Constructor for layout. 
**/
LOG4C_API log4c_layout_t* log4c_layout_new(const char* a_name);

/**
* Destructor for layout.
**/
LOG4C_API void log4c_layout_delete(log4c_layout_t* a_layout);

/**
* @param a_layout the log4c_layout_t object
* @return the layout name
**/
LOG4C_API const char* log4c_layout_get_name(const log4c_layout_t* a_layout);

/**
* @param a_layout the log4c_layout_t object
* @return a log4c_layout_type_t object
**/
LOG4C_API const log4c_layout_type_t* log4c_layout_get_type(
	const log4c_layout_t* a_layout);

/**
* sets the layout type
*
* @param a_layout the log4c_layout_t object
* @param a_type the new layout type
* @return the previous layout type
*
**/
LOG4C_API const log4c_layout_type_t* log4c_layout_set_type(
	log4c_layout_t* a_layout,
	const log4c_layout_type_t* a_type
	);

/**
* @param a_layout the log4c_layout_t object
* @return the layout user data
**/
LOG4C_API void* log4c_layout_get_udata(const log4c_layout_t* a_layout);

/**
* sets the layout user data
*
* @param a_layout the log4c_layout_t object
* @param a_udata the new layout user data
* @return the previous layout user data
**/
LOG4C_API void* log4c_layout_set_udata(log4c_layout_t*	a_layout, 
									   void*		a_udata);
/**
* format a log4c_logging_event events to a string.
*
* @param a_layout the log4c_layout_t object
* @param a_event a logging_event_t object
* @returns an appendable string.
**/
LOG4C_API const char* log4c_layout_format(
	const log4c_layout_t*		a_layout,
	const log4c_logging_event_t*	a_event);

/**
* prints the layout on a stream
* @param a_layout the log4c_layout_t object
* @param a_stream the stream
**/
LOG4C_API void log4c_layout_print(
	const log4c_layout_t* a_layout, FILE* a_stream);

/**
* prints all the current registered layout types on a stream
*
* @param fp the stream
**/                            
LOG4C_API void log4c_layout_types_print(FILE *fp);


/** 删除本layout.c文件中定义的全局和静态的指针指向的内存,防止内存泄漏
如：
1.gs_types.
2.
@return void.
作者：温辉敏 日期:2008.09.08
*/
LOG4C_API void log4c_layout_delete_global();

/**
* Helper macro to define static layout types.
*
* @param a_type the log4c_layout_type_t object to define
* @warning needs GCC support: otherwise ptrThis macro does nothing
* @deprecated This macro, and the static initialialization
* of layouts in general, is deprecated. Use rather
* the log4c_layout_type_set() function to initialize your appenders
* before calling log4c_init() 
**/
#ifdef __GNUC__
#   define log4c_layout_type_define(a_type) \
	typedef int log4c_layout_type_define_##a_type __attribute__((deprecated)); \
	static log4c_layout_type_define_##a_type __unsused_var __attribute__((unused));
#else
#   define log4c_layout_type_define(a_type)
#endif

/**
* @internal
**/
struct __sd_factory;
LOG4C_API struct __sd_factory* log4c_layout_factory;

__LOG4C_END_DECLS

#endif

/************** End of log4c/layout.h *******************************************/

/************** Begin of log4c/appender.h *******************************************/
/* $Id$
*
* appender.h
* 
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef log4c_appender_h
#define log4c_appender_h

/**
* @file appender.h
*
* @brief Implement ptrThis interface for your own strategies for printing log
* statements.
*
* @todo the appender interface needs a better configuration system
* depending on the layout type. The udata field is a just a trick.
**/

///#include <log4c/defs.h>
///#include <log4c/layout.h>
#include <stdio.h>

__LOG4C_BEGIN_DECLS

struct __log4c_appender;

/**
* log4c appender class 
**/
typedef struct __log4c_appender log4c_appender_t;

/**
* @brief log4c appender type class
*
* Attributes description:
* 
* @li @c name appender type name 
* @li @c open
* @li @c append
* @li @c close
**/
typedef struct log4c_appender_type {
	const char*	  name;
	int (*open)	  (log4c_appender_t*);
	int (*append) (log4c_appender_t*, const log4c_logging_event_t*);
	int (*close)  (log4c_appender_t*);
} log4c_appender_type_t;

/**
* Get a pointer to an existing appender type.
*
* @param a_name the name of the appender type to return.  
* @returns a pointer to an existing appender type, or NULL if no appender
* type with the specified name exists.
**/
LOG4C_API const log4c_appender_type_t* log4c_appender_type_get(const char* a_name);

/**
* Use ptrThis function to register an appender type with log4c.
* Once ptrThis is done you may refer to ptrThis type by name both 
* programmatically and in the log4c
* configuration file.
*
* @param a_type a pointer to the new appender type to set.
* @returns a pointer to the previous appender type of same name.
* 
* Example code fragment: 
* @code
* 
* const log4c_appender_type_t log4c_appender_type_s13_file = {
*   "s13_file",
*   s13_file_open,
*   s13_file_append,
*   s13_file_close,
* };
*  
*  log4c_appender_type_set(&log4c_appender_type_s13_file);
* @endcode
**/
LOG4C_API const log4c_appender_type_t* log4c_appender_type_set(
	const log4c_appender_type_t* a_type);

/**
* Get a pointer to an existing appender.
*
* @param a_name the name of the appender to return.
* @returns a pointer to an existing appender, or NULL if no appender
* with the specfied name exists.
**/
LOG4C_API log4c_appender_t* log4c_appender_get(const char* a_name);

/**
* Constructor for log4c_appender_t. 
**/
LOG4C_API log4c_appender_t* log4c_appender_new(const char* a_name);

/**
* Destructor for log4c_appender_t.
**/
LOG4C_API void log4c_appender_delete(log4c_appender_t* a_appender);

/**
* @param a_appender the log4c_appender_t object
* @return the appender name
**/
LOG4C_API const char* log4c_appender_get_name(const log4c_appender_t* a_appender);

/**
* @param a_appender the log4c_appender_t object
* @return the appender operations
**/
LOG4C_API const log4c_appender_type_t* log4c_appender_get_type(
	const log4c_appender_t* a_appender);

/**
* @param a_appender the log4c_appender_t object
* @return the appender layout
**/
LOG4C_API const log4c_layout_t* log4c_appender_get_layout(
	const log4c_appender_t* a_appender);

/**
* @param a_appender the log4c_appender_t object
* @return the appender user data
**/
LOG4C_API void* log4c_appender_get_udata(const log4c_appender_t* a_appender);

/**
* sets the appender type
*
* @param a_appender the log4c_appender_t object
* @param a_type the new appender type
* @return the previous appender type
**/
LOG4C_API const log4c_appender_type_t* log4c_appender_set_type(
	log4c_appender_t* a_appender,
	const log4c_appender_type_t* a_type);

/**
* sets the appender user data
*
* @param a_appender the log4c_appender_t object
* @param a_udata the new appender user data
* @return the previous appender user data
**/
LOG4C_API void* log4c_appender_set_udata(log4c_appender_t*	a_appender, 
										 void* a_udata);

/**
* sets the appender layout
*
* @param a_appender the log4c_appender_t object
* @param a_layout the new appender layout
* @return the previous appender layout
**/
LOG4C_API const log4c_layout_t* log4c_appender_set_layout(
	log4c_appender_t* a_appender,
	const log4c_layout_t* a_layout);

/**
* opens the appender.
*
* @param a_appender the log4c_appender_t object
**/
LOG4C_API int log4c_appender_open(log4c_appender_t* a_appender);

/**
* log in appender specific way.
*
* @param a_appender the log4c_appender object
* @param a_event the log4c_logging_event_t object to log.
**/
LOG4C_API int log4c_appender_append(
									log4c_appender_t* a_appender,
									log4c_logging_event_t* a_event);

/**
* log in appender specific way.
*
* @param a_appender the log4c_appender object
* @param a_event the log4c_logging_event_t object to log.
**/
LOG4C_API int log4c_appender_append_no_file_num_no_layout(
	log4c_appender_t* a_appender,
	log4c_logging_event_t* a_event);

/**
* closes the appender
*
* @param a_appender the log4c_appender_t object
* @return zero if successful, -1 otherwise
**/
LOG4C_API int log4c_appender_close(log4c_appender_t* a_appender);

/**
* prints the appender on a stream
*
* @param a_appender the log4c_appender_t object
* @param a_stream the stream
**/
LOG4C_API void log4c_appender_print(const log4c_appender_t* a_appender, 
									FILE* a_stream);

/**
* prints all the current registered appender types on a stream
*
* @param fp the stream
**/                            
LOG4C_API void log4c_appender_types_print(FILE *fp);

/** 删除本appender.c文件中定义的全局和静态的指针指向的内存,防止内存泄漏
如：
1.gs_types.
2.
@return void.
作者：温辉敏 日期:2008.09.08
*/
LOG4C_API void log4c_appender_delete_global();

/**
* Helper macro to define static appender types.
*
* @param a_type the log4c_appender_type_t object to define
* @warning needs GCC support: otherwise ptrThis macro does nothing
* @deprecated This macro, and the static initialialization
* of appenders in general, is deprecated. Use rather
* the log4c_appender_type_set() function to initialize your appenders
* before calling log4c_init() 
*
**/
#ifdef __GNUC__
#   define log4c_appender_type_define(a_type) \
	typedef int log4c_appender_type_define_##a_type __attribute__((deprecated)); \
	static log4c_appender_type_define_##a_type __unsused_var __attribute__ ((unused));
#else
#   define log4c_appender_type_define(a_type)
#endif

/**
* @internal
**/
struct __sd_factory;
LOG4C_API struct __sd_factory* log4c_appender_factory;

__LOG4C_END_DECLS

#endif

/************** End of log4c/appender.h *******************************************/

/************** Begin of log4c/rollingpolicy.h *******************************************/

/*
* rollingpolicy.h
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef log4c_rollingpolicy_h
#define log4c_rollingpolicy_h

/**
* @file rollingpolicy.h
*
* @brief Log4c rolling policy interface. Defines the interface for
* managing and providing rolling policies.
*
* A rolling policy is used to confogure a rollingfile appender to tell
* it when to trigger a rolover event.
*/ 

#include <stdio.h>
///#include <log4c/defs.h>
///#include <log4c/layout.h>

__LOG4C_BEGIN_DECLS

struct __log4c_rollingpolicy;

/**
* log4c rollingpolicy type 
*/
typedef struct __log4c_rollingpolicy log4c_rollingpolicy_t;


#define ROLLINGFILE_DEFAULT_LOG_DIR "."
#define ROLLINGFILE_DEFAULT_LOG_PREFIX "log"

typedef struct __rollingfile_udata rollingfile_udata_t; /* opaque */


/**
* @brief log4c rollingpolicy type.  Defines the interface a specific policy
* must provide to the rollingfile appender.
*
* Attributes description:
* 
* @li @c name rollingpolicy type name 
* @li @c init() init the rollingpolicy
* @li @c is_triggering_event()
* @li @c rollover()
*
**/
typedef struct log4c_rollingpolicy_type {
	const char*	name;
	int (*init)(log4c_rollingpolicy_t *a_this, rollingfile_udata_t* rfudatap );
	int (*is_triggering_event)( log4c_rollingpolicy_t* a_policy,
		const log4c_logging_event_t*,
		long current_file_size );
	int (*rollover)(log4c_rollingpolicy_t* a_policy, FILE **);  
	int (*fini)(log4c_rollingpolicy_t *a_this);
} log4c_rollingpolicy_type_t;

/**
* Get a new rolling policy
* @param policy_name a name for the policy
* @return a new rolling policy, otherwise NULL.
*/ 
LOG4C_API log4c_rollingpolicy_t* log4c_rollingpolicy_get(
	const char* policy_name);

/**
* Use ptrThis function to register a rollingpolicy type with log4c.
* Once ptrThis is done you may refer to ptrThis type by name both 
* programmatically and in the log4c configuration file.
*
* @param a_type a pointer to the new rollingpolicy type to register.
* @returns a pointer to the previous rollingpolicy type of same name.
*
* Example code fragment: 
* @code
* 
* const log4c_rollingpolicy_type_t log4c_rollingpolicy_type_sizewin = {
*   "sizewin",
*   sizewin_init,
*   sizewin_is_triggering_event,
*   sizewin_rollover
* };
*
* log4c_rollingpolicy_type_set(&log4c_rollingpolicy_type_sizewin);
* @endcode
* 
*/
LOG4C_API const log4c_rollingpolicy_type_t* log4c_rollingpolicy_type_set(
	const log4c_rollingpolicy_type_t* a_type);

/**
* Configure a rolling policy with a specific policy.
* @param policyp pointer to the rolling policy
* @param udatap a specific policy type, for example sizewin.
* @return zero if successful, non-zero otherwise.
*/                                  
LOG4C_API void log4c_rollingpolicy_set_udata(log4c_rollingpolicy_t* policyp,
											 void *udatap);
/**
* Call the initialization code of a rolling policy.
* @param policyp pointer to the rolling policy
* @param app the rolling appender ptrThis policy is used with
* @return zero if successful, non-zero otherwise.
*/
LOG4C_API int log4c_rollingpolicy_init(log4c_rollingpolicy_t *policyp,
									   rollingfile_udata_t* rfup );

/**
* Call the un initialization code of a rolling policy.
* This will call the fini routine of the particular rollingpolicy type
* to allow it to free up resources.  If the call to fini in the 
* rollingpolicy type fails then the rollingpolicy is not uninitialized.
* Try again later model...
* @param policyp pointer to the rolling policy
* @return zero if successful, non-zero otherwise.
*/
LOG4C_API int log4c_rollingpolicy_fini(log4c_rollingpolicy_t *a_this);

/**
* Determine if a logging event should trigger a rollover according to
* the given policy.
* @param policyp pointer to the rolling policy
* @param evtp the logging event pointer.
* @param current_file_size the size of the current file being logged to.
* @return non-zero if rollover required, zero otherwise.
*/ 
LOG4C_API int log4c_rollingpolicy_is_triggering_event(
	log4c_rollingpolicy_t* policyp,
	const log4c_logging_event_t* evtp,
	long current_file_size );
/**
* Effect a rollover according to policyp on the given file stream.
* @param policyp pointer to the rolling policy
* @param fp filestream to rollover.
* @return zero if successful, non-zero otherwise.
* The policy can return an indication that something went wrong but
* that the rollingfile appender can stull go ahead and log by returning an
* error code <= ROLLINGPOLICY_ROLLOVER_ERR_CAN_LOG.  Anything greater than
* means that the rolling file appender will not try to log it's message.
*/        

#define  ROLLINGPOLICY_ROLLOVER_ERR_CAN_LOG 0x05
LOG4C_API int log4c_rollingpolicy_rollover(log4c_rollingpolicy_t* policyp,
										   FILE ** fp);

/**
* sets the rolling policy type
*
* @param a_rollingpolicy the log4c_rollingpolicy_t object
* @param a_type the new rollingpolicy type
* @return the previous appender type
**/
LOG4C_API const log4c_rollingpolicy_type_t* log4c_rollingpolicy_set_type(
	log4c_rollingpolicy_t* a_rollingpolicy,
	const log4c_rollingpolicy_type_t* a_type);

/**
* Get a pointer to an existing rollingpolicy type.
*
* @param a_name the name of the rollingpolicy type to return.  
* @returns a pointer to an existing rollingpolicy type, or NULL if no 
* rollingpolicy type with the specified name exists.
*/
LOG4C_API const log4c_rollingpolicy_type_t* log4c_rollingpolicy_type_get(
	const char* a_name);

/**
* Get the rolling policy configuration.
* @param policyp pointer to the rolling policy
* @return pointer to the rolling policy configuration.
*/                                             
LOG4C_API void* log4c_rollingpolicy_get_udata(
	const log4c_rollingpolicy_t* policyp);

/**
* Get the rollingfile appender associated with ptrThis policy.
* @param policyp pointer to the rolling policy
* @return pointer to the rolling file appender associated with ptrThis policy
*/                          
LOG4C_API rollingfile_udata_t* log4c_rollingpolicy_get_rfudata(
	const log4c_rollingpolicy_t* policyp);

LOG4C_API void* log4c_rollingpolicy_get_name(const log4c_rollingpolicy_t* a_this);                        

LOG4C_API log4c_rollingpolicy_t* log4c_rollingpolicy_new(const char* a_name);
LOG4C_API void log4c_rollingpolicy_delete(log4c_rollingpolicy_t* a_this);
LOG4C_API void log4c_rollingpolicy_print(const log4c_rollingpolicy_t* a_this,
										 FILE* a_stream);

LOG4C_API int log4c_rollingpolicy_is_initialized(log4c_rollingpolicy_t* a_this);
LOG4C_API void log4c_rollingpolicy_types_print(FILE *fp);

/** 删除本rollingpolicy.c文件中定义的全局和静态的指针指向的内存,防止内存泄漏
如：
1.gs_types.
2.
@return void.
作者：温辉敏 日期:2008.09.08
*/
LOG4C_API void log4c_rollingpolicy_delete_global();

/**
* @internal
**/
struct __sd_factory;
LOG4C_API struct __sd_factory* log4c_rollingpolicy_factory;

__LOG4C_END_DECLS
#endif

/************** End of log4c/rollingpolicy.h *******************************************/


/************** Begin of log4c/priority.h *******************************************/
/* $Id$
*
* priority.h
* 
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef log4c_priority_h
#define log4c_priority_h

/**
* @file priority.h
*
* @brief The priority class provides importance levels with which one can
* categorize log messages.
**/

///#include <log4c/defs.h>

__LOG4C_BEGIN_DECLS

/**
* Predefined Levels of priorities. These correspond to the priority levels
* used by syslog(3).
**/
typedef enum {
	/** fatal */	LOG4C_PRIORITY_FATAL	= 000, 
	/** alert */	LOG4C_PRIORITY_ALERT	= 100, 
	/** crit */	    LOG4C_PRIORITY_CRIT		= 200, 
	/** error */	LOG4C_PRIORITY_ERROR	= 300, 
	/** warn */	    LOG4C_PRIORITY_WARN		= 400, 
	/** notice */	LOG4C_PRIORITY_NOTICE	= 500, 
	/** info */	    LOG4C_PRIORITY_INFO		= 600, 
	/** debug */	LOG4C_PRIORITY_DEBUG	= 700,
	/** trace */	LOG4C_PRIORITY_TRACE	= 800,
	/** notset */	LOG4C_PRIORITY_NOTSET	= 900,
	/** unknown */	LOG4C_PRIORITY_UNKNOWN	= 1000
} log4c_priority_level_t;

/**
* @param a_priority a numeric value of the priority.
* @returns the given priority string name.
**/
LOG4C_API const char* log4c_priority_to_string(int a_priority);

/**
* @param a_priority_name a priority string name.
* @returns the given numeric value of the priority.
**/
LOG4C_API int log4c_priority_to_int(const char* a_priority_name);

__LOG4C_END_DECLS

#endif

/************** End of log4c/priority.h *******************************************/

/************** Begin of log4c/category.h *******************************************/
/* $Id$
*
* category.h
* 
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef log4c_category_h
#define log4c_category_h

/**
* @file category.h
*
* @brief central class in the log4c package. 
* 
* One of the distintive features of log4j (and hence log4c) are
* hierarchical categories and their evaluation.
*
**/   

#include <stdio.h>
#include <stdarg.h>
///#include <log4c/defs.h>
///#include <log4c/priority.h>
///#include <log4c/location_info.h>

__LOG4C_BEGIN_DECLS

struct __log4c_appender;
struct __log4c_category;

/**
* log4c category class 
**/
typedef struct __log4c_category	log4c_category_t;

/**
* Instantiate a log4c_category_t with name @a name. This method
* does not set priority of the category which is by default @c
* LOG4C_PRIORITY_NOTSET.
* 
* @param a_name The name of the category to retrieve.
**/
LOG4C_API log4c_category_t* log4c_category_get(const char* a_name);

/**
* Fill in an array with the log4c categories.
*
* @param a_cats array of categories that will be filled
* @param a_ncats number of categories in the array
*
* @returns -1 if it fails or the number of available categories in
* log4c.
**/
LOG4C_API int log4c_category_list(log4c_category_t** a_cats, int a_ncats);

/**
* Constructor for a log4c_category_t.
*
* @param a_name the category name
* @returns a log4c_category object
* @warning ptrThis method should not be called directly. You should use the
* log4c_category_get() method in order to preserve the categories
* hierarchy.
**/
LOG4C_API log4c_category_t* log4c_category_new(const char* a_name);

/**
* Destructor for a log4c_category_t.
*
* @param a_category the log4c_category_t object
**/
LOG4C_API void log4c_category_delete(log4c_category_t* a_category);

/**
* Return the category name.
* @param a_category the log4c_category_t object
* @returns the category name.
*/       
LOG4C_API const char* log4c_category_get_name(const log4c_category_t* a_category);

/**
* Returns the Appender for ptrThis log4c_category_t, or NULL if no Appender has
* been set.
* @param a_category the log4c_category_t object
* @returns The Appender.
**/
LOG4C_API const struct __log4c_appender* log4c_category_get_appender(
	const log4c_category_t* a_category);

/**
* Get the additivity flag for ptrThis log4c_category_t..
*
* @param a_category the log4c_category_t object
* @return the category additivity
**/
LOG4C_API int log4c_category_get_additivity(const log4c_category_t* a_category);

/**
* Returns the assigned Priority, if any, for ptrThis log4c_category_t.
* @param a_category the log4c_category_t object
* @return Priority - the assigned Priority, can be LOG4C_PRIORITY_NOTSET
**/
LOG4C_API int log4c_category_get_priority(const log4c_category_t* a_category);

/**
* Starting from ptrThis category, search the category hierarchy for a set
* priority and return it. Otherwise, return the priority of the root
* category.
*
* @param a_category the log4c_category_t object
*
* @todo the log4c_category_t is designed so that ptrThis method executes as
* quickly as possible. It could even be faster if the set priority was
* propagated through the children hierarchy of a category.
**/
LOG4C_API int log4c_category_get_chainedpriority(const log4c_category_t* a_category);

/**
* Sets a new appender for ptrThis category.
*
* @param a_category the log4c_category_t object
* @param a_appender the new category appender
* @return the previous category appender
**/
LOG4C_API const struct __log4c_appender* log4c_category_set_appender(
	log4c_category_t* a_category,
struct __log4c_appender* a_appender);
/**
* Sets a new priority of ptrThis category.
*
* @param a_category the log4c_category_t object
* @param a_priority the new priority to set. Use LOG4C_PRIORITY_NOTSET to
* let the category use its parents priority as effective priority.
* @return the previous category priority
**/
LOG4C_API int log4c_category_set_priority(log4c_category_t* a_category,
										  int a_priority);

/**
* Sets a new additivity flag for ptrThis category.
*
* @param a_category the log4c_category_t object
* @param a_additivity the new category additivity
* @return the previous category additivity
**/
LOG4C_API int log4c_category_set_additivity(log4c_category_t* a_category,
											int a_additivity);
/**
* prints the log4c_category_t object on a stream
*
* @param a_category the log4c_category_t object
* @param a_stream The stream
**/ 
LOG4C_API void log4c_category_print(const log4c_category_t* a_category, FILE* a_stream); 

/** 
* Returns true if the chained priority of the log4c_category_t is equal to
* or higher than given priority.
* @param a_category the log4c_category_t object
* @param a_priority The priority to compare with.
* @returns whether logging is enable for ptrThis priority.
**/
#if !defined(_WIN32) && !defined(__HP_cc)
static inline int log4c_category_is_priority_enabled(const log4c_category_t* a_category,
													 int a_priority)
{
	return log4c_category_get_chainedpriority(a_category) >= a_priority;
}
#else
#define log4c_category_is_priority_enabled(a,b) \
	(log4c_category_get_chainedpriority(a) >= b)
#endif

/**
* Return true if the category will log messages with priority @c
* LOG4C_PRIORITY_FATAL.
*
* @param a_category the log4c_category_t object
* @returns Whether the category will log.
**/ 
#if !defined(_WIN32) && !defined(__HP_cc)
static inline int log4c_category_is_fatal_enabled(const log4c_category_t* a_category)
{	
	return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_FATAL);
}
#else
#define log4c_category_is_fatal_enabled(a)  \
	(log4c_category_is_priority_enabled(a,LOG4C_PRIORITY_FATAL))
#endif

/**
* Return true if the category will log messages with priority @c
* LOG4C_PRIORITY_ALERT.
*
* @param a_category the log4c_category_t object
* @returns Whether the category will log.
**/ 
#if !defined(_WIN32) && !defined(__HP_cc)
static inline int log4c_category_is_alert_enabled(const log4c_category_t* a_category) 
{	
	return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_ALERT); 
}
#else
#define log4c_category_is_alert_enabled(a) \
	(log4c_category_is_priority_enabled(a,LOG4C_PRIORITY_ALERT))
#endif

/**
* Return true if the category will log messages with priority @c
* LOG4C_PRIORITY_CRIT.
*
* @param a_category the log4c_category_t object
* @returns Whether the category will log.
**/ 
#if !defined(_WIN32) && !defined(__HP_cc)
static inline int log4c_category_is_crit_enabled(const log4c_category_t* a_category) 
{	
	return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_CRIT); 
}
#else
#define log4c_category_is_crit_enabled(a) \
	(log4c_category_is_priority_enabled(a, LOG4C_PRIORITY_CRIT))
#endif

/**
* Return true if the category will log messages with priority @c
* LOG4C_PRIORITY_ERROR.
*
* @param a_category the log4c_category_t object
* @returns Whether the category will log.
**/ 
#if !defined(_WIN32) && !defined(__HP_cc)
static inline int log4c_category_is_error_enabled(const log4c_category_t* a_category) 
{	
	return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_ERROR); 
}
#else
#define log4c_category_is_error_enabled(a) \
	(log4c_category_is_priority_enabled(a, LOG4C_PRIORITY_ERROR))
#endif

/**
* Return true if the category will log messages with priority @c
* LOG4C_PRIORITY_WARN.
*
* @param a_category the log4c_category_t object
* @returns Whether the category will log.
**/ 
#if !defined(_WIN32) && !defined(__HP_cc)
static inline int log4c_category_is_warn_enabled(const log4c_category_t* a_category) 
{	
	return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_WARN); 
}
#else
#define log4c_category_is_warn_enabled(a) \
	log4c_category_is_warn_enabled(a) \
	(log4c_category_is_priority_enabled(a, LOG4C_PRIORITY_WARN))
#endif

/**
* Return true if the category will log messages with priority @c
* LOG4C_PRIORITY_NOTICE.
*
* @param a_category the log4c_category_t object
* @returns Whether the category will log.
**/ 
#if !defined(_WIN32) && !defined(__HP_cc)
static inline int log4c_category_is_notice_enabled(const log4c_category_t* a_category) 
{	
	return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_NOTICE); 
}
#else 
#define log4c_category_is_notice_enabled(a) \
	(log4c_category_is_priority_enabled(a, LOG4C_PRIORITY_NOTICE))
#endif

/**
* Return true if the category will log messages with priority @c
* LOG4C_PRIORITY_INFO.
*
* @param a_category the log4c_category_t object
* @returns Whether the category will log.
**/ 
#if !defined(_WIN32) && !defined(__HP_cc)
static inline int log4c_category_is_info_enabled(const log4c_category_t* a_category) 
{	
	return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_INFO); 
}
#else
#define log4c_category_is_info_enabled(a) \
	(log4c_category_is_priority_enabled(a, LOG4C_PRIORITY_INFO))
#endif

/**
* Return true if the category will log messages with priority @c
* LOG4C_PRIORITY_DEBUG.
*
* @param a_category the log4c_category_t object
* @returns Whether the category will log.
**/ 
#if !defined(_WIN32) && !defined(__HP_cc)
static inline int log4c_category_is_debug_enabled(const log4c_category_t* a_category) 
{	
	return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_DEBUG); 
}
#else
#define log4c_category_is_debug_enabled(a) \
	(log4c_category_is_priority_enabled(a, LOG4C_PRIORITY_DEBUG))
#endif

/**
* Return true if the category will log messages with priority @c
* LOG4C_PRIORITY_TRACE.
*
* @param a_category the log4c_category_t object
* @returns Whether the category will log.
**/ 
#if !defined(_WIN32) && !defined(__HP_cc)
static inline int log4c_category_is_trace_enabled(const log4c_category_t* a_category) 
{	
	return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_TRACE); 
}
#else
#define log4c_category_is_trace_enabled(a) \
	(log4c_category_is_priority_enabled(a, LOG4C_PRIORITY_TRACE))
#endif

/**
* @internal
**/
LOG4C_API void __log4c_category_vlog(const log4c_category_t* a_category, 
									 const log4c_location_info_t* a_locinfo, 
									 int a_priority,
									 const char* a_format, 
									 va_list a_args);

/**
* @internal
**/
LOG4C_API void __log4c_category_vlog_no_file_num_no_layout(
	const log4c_category_t* a_category, 
	const log4c_location_info_t* a_locinfo, 
	int a_priority,
	const char* a_format, 
	va_list a_args);

/**
* @internal
*
* @bug the log4c_location_info_t object is not set correctly. A macro is
* needed.
**/

/* msvc doesn't allow "inline" nor variable args in a macro
* so cannot #define these ones.
*/

static LOG4C_INLINE void log4c_category_vlog(const log4c_category_t* a_category, 
											 int a_priority,
											 const char* a_format, 
											 va_list a_args)
{
	const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);

	__log4c_category_vlog(a_category, &locinfo, a_priority, a_format, a_args);
}

/**
* @internal
*
* @bug the log4c_location_info_t object is not set correctly. A macro is
* needed.
**/

/* msvc doesn't allow "inline" nor variable args in a macro
* so cannot #define these ones.
*/

static LOG4C_INLINE void log4c_category_vlog_no_file_num_no_layout(const log4c_category_t* a_category, 
																   int a_priority,
																   const char* a_format, 
																   va_list a_args)
{
	const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);

	__log4c_category_vlog_no_file_num_no_layout(a_category, &locinfo, a_priority, a_format, a_args);
}

/** 
* Log a message with the specified priority.
* @param a_category the log4c_category_t object
* @param a_priority The priority of ptrThis log message.
* @param a_format Format specifier for the string to write 
* in the log file.
* @param ... The arguments for a_format 
**/  
static LOG4C_INLINE void log4c_category_log(const log4c_category_t* a_category,
											int a_priority,
											const char* a_format,
											...)
{
	if (log4c_category_is_priority_enabled(a_category, a_priority)) {
		va_list va;
		va_start(va, a_format);
		log4c_category_vlog(a_category, a_priority, a_format, va);
		va_end(va);
	}
}

/** 
* Log a message with the specified priority and a user location info.
* @param a_category the log4c_category_t object
* @param a_locinfo a user  location info
* @param a_priority The priority of ptrThis log message.
* @param a_format Format specifier for the string to write 
* in the log file.
* @param ... The arguments for a_format 
**/  
static LOG4C_INLINE void log4c_category_log_locinfo(
	const log4c_category_t* a_category,
	const log4c_location_info_t* a_locinfo, 
	int a_priority,
	const char* a_format,
	...)
{
	if (log4c_category_is_priority_enabled(a_category, a_priority)) {
		va_list va;
		va_start(va, a_format);
		__log4c_category_vlog(a_category, a_locinfo, a_priority, a_format, va);
		va_end(va);
	}
}

/** 
* Log a message with fatal priority.
* @param a_category the log4c_category_t object
* @param a_format Format specifier for the string to write 
* in the log file.
* @param ... The arguments for a_format 
**/  
static LOG4C_INLINE void log4c_category_fatal(const log4c_category_t* a_category,
											  const char* a_format,
											  ...)
{
	if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_FATAL)) {
		va_list va;
		va_start(va, a_format);
		log4c_category_vlog(a_category, LOG4C_PRIORITY_FATAL, a_format, va);
		va_end(va);
	}
}

/** 
* Log a message with alert priority.
* @param a_category the log4c_category_t object
* @param a_format Format specifier for the string to write 
* in the log file.
* @param ... The arguments for a_format 
**/  
static LOG4C_INLINE void log4c_category_alert(const log4c_category_t* a_category,
											  const char* a_format,
											  ...)
{
	if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_ALERT)) {
		va_list va;
		va_start(va, a_format);
		log4c_category_vlog(a_category, LOG4C_PRIORITY_ALERT, a_format, va);
		va_end(va);
	}
}

/** 
* Log a message with crit priority.
* @param a_category the log4c_category_t object
* @param a_format Format specifier for the string to write 
* in the log file.
* @param ... The arguments for a_format 
**/  
static LOG4C_INLINE void log4c_category_crit(const log4c_category_t* a_category,
											 const char* a_format,
											 ...)
{
	if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_CRIT)) {
		va_list va;
		va_start(va, a_format);
		log4c_category_vlog(a_category, LOG4C_PRIORITY_CRIT, a_format, va);
		va_end(va);
	}
}

/** 
* Log a message with error priority.
* @param a_category the log4c_category_t object
* @param a_format Format specifier for the string to write 
* in the log file.
* @param ... The arguments for a_format 
**/  
static LOG4C_INLINE void log4c_category_error(const log4c_category_t* a_category,
											  const char* a_format,
											  ...)
{
	if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_ERROR)) {
		va_list va;
		va_start(va, a_format);
		log4c_category_vlog(a_category, LOG4C_PRIORITY_ERROR, a_format, va);
		va_end(va);
	}
}

/** 
* Log a message with warn priority.
* @param a_category the log4c_category_t object
* @param a_format Format specifier for the string to write 
* in the log file.
* @param ... The arguments for a_format 
**/  
static LOG4C_INLINE void log4c_category_warn(const log4c_category_t* a_category,
											 const char* a_format,
											 ...)
{
	if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_WARN)) {
		va_list va;
		va_start(va, a_format);
		log4c_category_vlog(a_category, LOG4C_PRIORITY_WARN, a_format, va);
		va_end(va);
	}
}

/** 
* Log a message with notice priority.
* @param a_category the log4c_category_t object
* @param a_format Format specifier for the string to write 
* in the log file.
* @param ... The arguments for a_format 
**/  
static LOG4C_INLINE void log4c_category_notice(const log4c_category_t* a_category,
											   const char* a_format,
											   ...)
{
	if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_NOTICE)) {
		va_list va;
		va_start(va, a_format);
		log4c_category_vlog(a_category, LOG4C_PRIORITY_NOTICE, a_format, va);
		va_end(va);
	}
}

/** 
* Log a message with info priority.
* @param a_category the log4c_category_t object
* @param a_format Format specifier for the string to write 
* in the log file.
* @param ... The arguments for a_format 
**/  
static LOG4C_INLINE void log4c_category_info(const log4c_category_t* a_category,
											 const char* a_format,
											 ...)
{
	if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_INFO)) {
		va_list va;
		va_start(va, a_format);
		log4c_category_vlog(a_category, LOG4C_PRIORITY_INFO, a_format, va);
		va_end(va);
	}
}

/** 
* Log a message with debug priority.
* @param a_category the log4c_category_t object
* @param a_format Format specifier for the string to write 
* in the log file.
* @param ... The arguments for a_format 
**/  
static LOG4C_INLINE void log4c_category_debug(const log4c_category_t* a_category,
											  const char* a_format,
											  ...)
{
	if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_DEBUG)) {
		va_list va;
		va_start(va, a_format);
		log4c_category_vlog(a_category, LOG4C_PRIORITY_DEBUG, a_format, va);
		va_end(va);
	}
}

/** 
* Log a message with trace priority.
* @param a_category the log4c_category_t object
* @param a_format Format specifier for the string to write 
* in the log file.
* @param ... The arguments for a_format 
**/  
static LOG4C_INLINE void __log4c_category_trace(const log4c_category_t* a_category,
												const char* a_format,
												...)
{
	if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_TRACE)) {
		va_list va;
		va_start(va, a_format);
		log4c_category_vlog(a_category, LOG4C_PRIORITY_TRACE, a_format, va);
		va_end(va);
	}
}

#ifdef __GNUC__

#ifdef OLD_VARIADIC_MACRO

#  define log4c_category_trace(a_category, a_format, args...) \
	__log4c_category_trace(a_category, log4c_location "\n" a_format, ##args )

#else

#  define log4c_category_trace(a_category, a_format, ...) \
	__log4c_category_trace(a_category, log4c_location "\n" a_format, ##__VA_ARGS__ )

#endif /* OLD_VARIADIC_MACRO */


#else
#  define log4c_category_trace __log4c_category_trace
#endif  /* __GNUC__ */

/**
* Helper macro to define static categories.
*
* @param a_category the log4c_category_t pointer name
* @param a_name the category name
**/
#ifdef __GNUC__
#   define log4c_category_define(a_category, a_name) \
	typedef log4c_category_t log4c_category_define_##a_category __attribute__((deprecated)); \
	static log4c_category_define_##a_category* a_category  __attribute__ ((unused)) = NULL;
#else
#   define log4c_category_define(a_category, a_name)
#endif

/**
* @internal
**/
struct __sd_factory;
LOG4C_API struct __sd_factory* log4c_category_factory;

__LOG4C_END_DECLS

#endif

/************** End of log4c/category.h *******************************************/

#if ( ( defined(LOG_USELOG4CXX) && defined(__cplusplus) ) || defined(LOG4C_ENABLE) ) && defined(IMPLEMENT_LOG4C)

#pragma   warning(push)  
#pragma   warning(disable:4996 4090 4018) 
///#pragma   warning(once:4996)

/************** Begin of GlobalMacro.h *******************************************/
/**********************************************************
* 版权所有 (C)2008, 51.com
*
* 文件名称：GlobalMacro.h
* 内容摘要：全局宏定义的头文件
*			本文件包含了所有要用到的全局宏的定义
* 其它说明：
* 当前版本：
* 作    者：温辉敏
* 完成日期：2009-1-02
*
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容：
**********************************************************/
#if !defined(AFX_GLOBALMACRO_H__DD58A78D_C125_410F_B4C8_F0067B797121__INCLUDED_)
#define AFX_GLOBALMACRO_H__DD58A78D_C125_410F_B4C8_F0067B797121__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 获取数组的维数 [7/1/2008 温辉敏]
#define PARRAYSIZE(array) ((sizeof(array)/sizeof(array[0])))

/** Declare all the standard PWlib class information.
This macro is used to provide the basic run-time typing capability needed
by the library. All descendent classes from the #PObject# class require
these functions for correct operation. Either use ptrThis macro or the
#PDECLARE_CLASS# macro.

The use of the #PDECLARE_CLASS# macro is no longer recommended for reasons
of compatibility with documentation systems.
*/
#define CLASSINFO(cls, par) \
  public: \
	static const char * Class() \
	{ return #cls; } \
	virtual const char * GetClass(unsigned ancestor = 0) const \
	{ return ancestor > 0 ? par::GetClass(ancestor-1) : cls::Class(); } \
	virtual BOOL IsClass(const char * clsName) const \
	{ return strcmp(clsName, cls::Class()) == 0; } \
	virtual BOOL IsDescendant(const char * clsName) const \
	{ return strcmp(clsName, cls::Class()) == 0 || \
	  par::IsDescendant(clsName); } 


/** Declare all the standard PWlib class information.
This macro is used to provide the basic run-time typing capability needed
by the library. All descendent classes from the #PObject# class require
these functions for correct operation. Either use ptrThis macro or the
#PDECLARE_CLASS# macro.

The use of the #PDECLARE_CLASS# macro is no longer recommended for reasons
of compatibility with documentation systems.
*/
#define CLASSINFO_BASE(cls) \
  public: \
	static const char * Class() \
	{ return #cls; } \
	virtual const char * GetClass(unsigned ancestor = 0) const \
	{ return cls::Class(); } \
	virtual BOOL IsClass(const char * clsName) const \
	{ return strcmp(clsName, cls::Class()) == 0; } \
	virtual BOOL IsDescendant(const char * clsName) const \
	{ return strcmp(clsName, cls::Class()) == 0; } 


/* 函数返回基本状态信息  */
#ifdef LOG4C_OK
#undef LOG4C_OK
#endif /* #ifdef LOG4C_OK */
#ifndef LOG4C_OK
#define LOG4C_OK               (0)    /* 成功返回	*/
#endif /* #ifndef LOG4C_OK */

/* 函数返回基本状态信息  */
#ifdef LOG4C_FAILURE
#undef LOG4C_FAILURE
#endif /* #ifdef LOG4C_FAILURE */
#ifndef LOG4C_FAILURE
#define LOG4C_FAILURE           (-1)    /* 失败返回	*/
#endif /* #ifndef LOG4C_FAILURE */

//////////////////////////////////////////////////////////////////////////
///一些宏定义

///删除一个数组指针的宏定义
//lint -emacro(774, DELETEA)
#ifndef DELETEA
#define DELETEA(ptr) \
	if(NULL != ptr) \
	{ \
		delete[] ptr; \
		ptr = NULL; \
	}
#endif

///删除一个指针的宏定义
#ifndef FREEP
#define FREEP(ptr)		\
	if(NULL != ptr)		\
	{					\
		free(ptr) ;		\
		ptr = NULL;		\
	}
#endif

///删除一个指针的宏定义
//lint -emacro(774, DELETEP)
#define DELETEP(ptr)	\
	if(NULL != (ptr))		\
	{					\
		delete (ptr);		\
		(ptr) = NULL;		\
	}

///删除一个GDI对象的宏定义
//lint -emacro(774, DELETEOBJECT)
#define DELETEOBJECT(ptr)	\
	if(NULL != (ptr))		\
	{					\
		::DeleteObject (ptr);		\
		(ptr) = NULL;		\
	}

///Destroy一个Window
//lint -emacro(774, DESTROYWINDOW)
#define DESTROYWINDOW(hWnd)	\
	if (IsWindow(hWnd)) \
	{ \
		DestroyWindow(hWnd); \
	}

///删除一个指针的宏定义
//lint -emacro(774, FREEP)
#undef  FREEP
#define FREEP(ptr)		\
	if(NULL != ptr)		\
	{					\
		free(ptr) ;		\
		ptr = NULL;		\
	}


/** 定义的根据输入类型来删除不同类型的指针的宏定义
*/
#define DELETE_TYPE_P(Type, ptrEvent) \
	{\
		Type *ptrEventLocal = (Type *)ptrEvent; \
		DELETEP(ptrEventLocal); \
		ptrEvent = NULL; \
	}


/** This macro is used to assert that a condition must be TRUE.
若condition条件不成立则执行statement语句，然后以return_value值return
*/
#define PAssert_ReturnWithValue(condition, return_value) \
	{  \
		if (!(condition)) \
		{ \
			return (return_value); \
		} \
	}

/** This macro is used to assert that a condition must be TRUE.
若condition条件不成立则执行statement语句，然后return
*/
#define PAssert_Return(condition) \
	{  \
		if (!(condition)) \
		{ \
			return ; \
		} \
	}

#ifndef VOS_DELETE_SEM
#define VOS_DELETE_SEM(semId)	\
	if (NULL != semId)			\
	{							\
		VOS_DeleteSem(semId);	\
		semId = NULL;			\
	}
#endif

/** This macro is used to assert that a condition must be TRUE.
若condition条件不成立则执行statement语句，然后以return_value值return
*/
#define PAssert_Statement_ReturnWithValue(condition, statement, return_value) \
	{  \
		if (!(condition)) \
		{ \
			statement; \
			return (return_value); \
		} \
	}

/** This macro is used to assert that a condition must be TRUE.
若condition条件不成立则执行statement语句，然后return
*/
#define PAssert_Statement_Return(condition, statement) \
	{  \
		if (!(condition)) \
		{ \
			statement; \
			return ; \
		} \
	}

/** This macro is used to assert that a pointer must be non-null.
若指针ptr为NULL则执行statement语句，然后以return_value值return
*/
#define PAssertNotNull_Statement_ReturnWithValue(ptr, statement, return_value) \
	{ \
		if( (ptr) == NULL) \
		{ \
			statement; \
			return (return_value); \
		} \
	}


/** This macro is used to assert that a pointer must be non-null.
若指针ptr为NULL则执行statement语句，然后return
*/
#define PAssertNotNull_Statement_Return(ptr, statement) \
	{ \
		if( (ptr) == NULL) \
		{ \
			statement; \
			return ; \
		} \
	}

/** This macro is used to assert that a pointer must be non-null.
若指针ptr为NULL则执行statement语句，然后以return_value值return
*/
#define PAssertNotNull_ReturnWithValue(ptr, return_value) \
	{ \
		if( (ptr) == NULL) \
		{ \
			return (return_value); \
		} \
	}


/** This macro is used to assert that a pointer must be non-null.
若指针ptr为NULL则执行statement语句，然后return
*/
#define PAssertNotNull_Return(ptr) \
	{ \
		if( (ptr) == NULL) \
		{ \
			return ; \
		} \
	}

/** This macro is used to do something and return 
执行一个语句statement，然后return return_value
*/
#define PStatement_Return(statement, return_value) \
{ \
	statement; \
	return return_value; \
}

/** This macro is used to assert that a condition must be TRUE.
若condition条件不成立则执行break语句
*/
#define PAssert_Break(condition) \
{  \
	if (!(condition)) \
	{ \
		break ; \
	} \
}

/** This macro is used to do something and break 
执行一个语句statement，然后break
*/
#define PStatement_Break(statement) \
{ \
	statement; \
	break; \
}

/** This macro is used to assert that a condition must be TRUE.
若condition条件不成立则执行statement语句，然后执行break语句
*/
#define PAssert_Statement_Break(condition, statement) \
{  \
	if (!(condition)) \
	{ \
		statement; \
		break ; \
	} \
}

/** 空操作
*/
#define NULL_OPERATION

// 获取数组的维数 
#define PARRAYSIZE(array) ((sizeof(array)/sizeof(array[0])))

/** Declare all the standard RTTI class information.
This macro is used to provide the basic run-time typing capability needed
by the library. All descendent classes from the #PObject# class require
these functions for correct operation. Either use ptrThis macro or the
#PDECLARE_CLASS# macro.

The use of the #PDECLARE_CLASS# macro is no longer recommended for reasons
of compatibility with documentation systems.
*/
#define CLASSINFO(cls, par) \
  public: \
	static const char * Class() \
	{ return #cls; } \
	virtual const char * GetClass(unsigned ancestor = 0) const \
	{ return ancestor > 0 ? par::GetClass(ancestor-1) : cls::Class(); } \
	virtual BOOL IsClass(const char * clsName) const \
	{ return strcmp(clsName, cls::Class()) == 0; } \
	virtual BOOL IsDescendant(const char * clsName) const \
	{ return strcmp(clsName, cls::Class()) == 0 || \
	par::IsDescendant(clsName); } 


///memset缺省构造函数
#ifndef MEMSET_CONSTRUCTOR
#define MEMSET_CONSTRUCTOR(ClassType) \
	ClassType() \
	{ \
		memset(this, 0, sizeof(ClassType)); \
	}
#endif

#if 0
#ifdef __cplusplus
/** 
按照特定数据类型删除该数据类型的数组指针
*/
#ifndef DELETE_ARRAY_TEMPLATE
#define DELETE_ARRAY_TEMPLATE
template <class classType>
void DeleteArray(void *&ptr)
{
	classType *ptrClassType = (classType *)ptr;
	DELETEA(ptrClassType);
	ptr = NULL;
}
#endif

/** 
按照特定数据类型删除该数据类型的指针
*/
#ifndef DELETE_TEMPLATE
#define DELETE_TEMPLATE
template <class classType>
void Delete(void *&ptr)
{
	classType *ptrClassType = (classType *)ptr;
	DELETEP(ptrClassType);
	ptr = NULL;
}
#endif
#endif
#endif


#endif // !defined(AFX_GLOBALMACRO_H__DD58A78D_C125_410F_B4C8_F0067B797121__INCLUDED_)

/************** End of GlobalMacro.h *******************************************/

/************** Begin of voscfg.h *******************************************/
/**********************************************************
* 版权所有 (C)2002, 深圳市中兴通讯股份有限公司。
*
* 文件名称： voscfg.h
* 文件标识：
* 内容摘要： VOS的系统配置文件
* 其它说明： 无
* 当前版本： v1.0
* 作    者： 谢鑫
* 完成日期： 2004.02.27
*
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容：
**********************************************************/

#ifndef _VOSCFG_H
#define _VOSCFG_H

#ifdef __cplusplus
extern "C" {
#endif

	/*******************************************************
	*                       基本配置
	*******************************************************/

	/* CPU类型 */
#define   CPU_X86             0x1
#define   CPU_PPC             0x2
#define   CPU_ARM             0x3
#define   CPU_TYPE            CPU_X86

#undef	OS_LINUX	
#undef  OS_WINNT
	/* 操作系统OS类型 */
#define   OS_VXWORKS          0x1
#define   OS_WINNT            0x2
#define   OS_PSOS             0x3
#define   OS_LINUX            0x4
#define   OS_KLINUX           0x5

	///added by wenhm in 2005.08.25
#ifdef _WIN32
#define   OS_TYPE             OS_WINNT
#else #ifdef   linux
#define   OS_TYPE			  OS_LINUX
#endif


	/* linux适配 */
#define    VXWORKS_TO_LINUX
#ifndef    VXWORKS_TO_LINUX
#define    PSOS_TO_LINUX
#endif
#if ( OS_TYPE == OS_KLINUX)
#define  _USE_TIMER_IRQ
#endif

	/*********************************************************
	基本包含文件                        
	**********************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#if OS_TYPE == OS_PSOS
#include <psos.h>
#include <phile.h>
#include <pna.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys_conf.h>
#include <types.h>
#include <socket.h>
#endif

#if  OS_TYPE == OS_VXWORKS
#include <vxWorks.h>
#include <sysLib.h>
#include <taskLib.h>    
#include <msgQLib.h>
#include <semLib.h>
#include <vmLib.h>
#include <dosfslib.h>
#include <iolib.h>
#include <dirent.h>
#include <stat.h>
#include <errnoLib.h>
#include <types.h>
#include <socket.h>
#include <socklib.h>
#include <logLib.h>
#include <assert.h>
#include <symlib.h>
#include <sysSymTbl.h>
#include <excLib.h>
#include <esf.h>
#include <memLib.h>
#include <tickLib.h>
#include <private\memPartLibP.h>
#include <in.h>
#include <ramDrv.h>
#include <ftpdLib.h>
#include <cachelib.h>
#include <signal.h>
#include <sigLib.h>
#include <time.h>
#include <wdLib.h>
#include <intLib.h>
#include <timers.h>
#include "inetLib.h"
#include "netinet\tcp.h"
#include "fcntl.h"
#include "netinet/in.h"
#include "end.h"
#include "zbufSockLib.h"
#include <routeLib.h>
#include <usrLib.h>
#endif

#if OS_TYPE == OS_WINNT
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <imagehlp.h>
#include <io.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <direct.h>
#include <Winsock.h>
#include <time.h>
	///#include <Winsock2.h>
#pragma comment(lib, "imagehlp.lib")
#pragma comment(lib,"Winmm.lib")
#endif

#if OS_TYPE == OS_LINUX
#ifdef VXWORKS_TO_LINUX
	///#include "vxw_hdrs.h"
#else
	///#include "psos_hdrs.h"
#endif
#include <time.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <asm/ioctls.h>
#include <netinet/tcp.h>
#include <sys/select.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <asm/errno.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <netinet/in.h>    
#include <signal.h>
#include <stdio.h>
#include <dirent.h>
#include <semaphore.h>    
#endif

#if OS_TYPE == OS_KLINUX
#include "kth.h"
	/*	#include "ksocket.h"*/
#include <stdio.h>
#include "ktm.h"
#include <netinet/tcp.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
	/*	#include "kfile.h"*/
	/*	#include <linux/vmalloc.h>*/
#endif


	/*********************************************************
	基本数据类型                        
	**********************************************************/
#if OS_TYPE != OS_WINNT
	typedef  unsigned char    BYTE;
#endif

	typedef  unsigned char    BOOLEAN;
	typedef  char             CHAR;
	typedef  void            *LPVOID;
	typedef  unsigned short   WORD16;
	typedef  unsigned long    WORD32;
	typedef  signed short     SWORD16;
	///typedef  signed long      SWORD32;

#ifndef SWORD32
#ifdef  WIN32
	typedef long                SWORD32; 
#else
#define SWORD32            long
#endif		
#endif

#define  INVALID_BYTE     (unsigned char)0xff
#define  INVALID_WORD     (unsigned short)0xffff
#define  INVALID_DWORD    (unsigned long)0xffffffff 

	typedef  long             OSS_STATUS;
#define  OSS_OK           0
#define  OSS_ERROR        -1

#ifdef __cplusplus
}
#endif


#endif

/************** End of voscfg.h *******************************************/

/************** Begin of vos.h *******************************************/
/**********************************************************
* 版权所有 (C)2002, 深圳市中兴通讯股份有限公司。
*
* 文件名称： vos.h
* 文件标识：
* 内容摘要： 操作系统封装层头文件（主要是所包含头文件、数据结构、接口等）
* 其它说明： 无
* 当前版本： V1.0
* 作    者： 王泽民
* 完成日期： 2003/08/10
*
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容：
**********************************************************/
#ifndef _VOS_H_
#define _VOS_H_

#ifdef __cplusplus
extern "C" {
#endif

///#include "voscfg.h"
	/**********************************************************
	*                          宏定义                         *
	**********************************************************/

#define    VOS_NULL                      0x0

#define    VOS_TRUE                      1
#define    VOS_FALSE                     0

#define    VOS_SUCCESS                   0     /* PSOS返回值                    */
#define    VOS_PCBINDEXNO                0     /* 保存pcbindex的便条寄存器号    */
#define    VOS_TASKPRINO                 1     /* 保存任务优先级的便条寄存器号  */
#define    VOS_TICKNUM                   1     /* 中断的tick数                  */
#define    TIMER_SCAN_EVENT              (WORD32)(1<<15)
#define    MEMLEAK_SCAN_EVENT            (WORD32)(1<<16)
#define    MAX_LENGTH_BUF                512

#define    VOS_NO_WAIT                   0x0
#define    VOS_WAIT_FOREVER              -1

#define    VOS_SEM_DELETE_SAFE           0x04
#define    VOS_SEM_INVERSION_SAFE        0x08

#define    VOS_VM_STATE_MASK_VALID       0x03
#define    VOS_VM_STATE_MASK_WRITABLE    0x0c
#define    VOS_VM_STATE_MASK_CACHEABLE   0x30
#define    VOS_VM_STATE_MASK_WBACK       0x40
#define    VOS_VM_STATE_MASK_GLOBAL      0x80
#define    VOS_VM_STATE_MASK_GUARDED     0x80

#define    VOS_VM_STATE_VALID            0x01
#define    VOS_VM_STATE_VALID_NOT        0x00
#define    VOS_VM_STATE_WRITABLE         0x04
#define    VOS_VM_STATE_WRITABLE_NOT     0x00
#define    VOS_VM_STATE_CACHEABLE        0x10
#define    VOS_VM_STATE_CACHEABLE_NOT    0x00
#define    VOS_VM_STATE_WBACK			 0x40
#define    VOS_VM_STATE_WBACK_NOT		 0x00
#define    VOS_VM_STATE_GLOBAL			 0x80
#define    VOS_VM_STATE_GLOBAL_NOT		 0x00
#define    VOS_VM_STATE_GUARDED			 0x80
#define    VOS_VM_STATE_GUARDED_NOT		 0x00

#define    MAXCOUNTSEM                   10000
#define    VOS_MAX_PATH_LEN              50
#define    VOS_MAX_FILENAME_LEN          60
#define    VOS_MAX_EXP_FILENAME_LEN      8

#if OS_TYPE == OS_VXWORKS
#define    NULL_TASKID               ERROR
#define    NULL_SEMID                NULL
#define    NULL_MSGQID               NULL
#define    NULL_MSGGET               0
#define    DIR_CODE                  0x2f    /* 定义符号 "/" */
#define    DIR_CONCATE_CODE            "/"
#endif

#if OS_TYPE == OS_WINNT
#define    NULL_TASKID               NULL
#define    NULL_SEMID                NULL
#define    NULL_MSGQID               NULL
#define    NULL_MSGGET               0
#define    DIR_CODE                  0x5c    /* 定义符号" \" */
#define    DIR_CONCATE_CODE            "\\"
#define    RDONLY                    0
#define    WRONLY                    1
#define    RDWR                      2
#define    WINNT_ERROR               -1    
#endif

#if OS_TYPE == OS_PSOS
#define    NULL_TASKID               0xffffffff
#define    NULL_SEMID                0xffffffff
#define    NULL_MSGQID               0xffffffff
#define    NULL_MSGGET               0xffffffff
#define    MSG_Q_FIFO                0x00
#define    MSG_Q_PRIORITY            0x01
#define    MSG_PRI_NORMAL            0x00
#define    MSG_PRI_URGENT            0x01
#define    RAM_BLOCKS                2*360  /* RAM disk块大小 */
#define    RAM_PATH_LENGTH           80
#define    MIN_EXPAN_BLOCKS          10
#endif

#if OS_TYPE == OS_LINUX
#ifdef VXWORKS_TO_LINUX
#define    NULL_TASKID               ERROR
#define    NULL_SEMID                NULL
#define    NULL_MSGQID               NULL
#else
#define    NULL_TASKID               0xffffffff
#define    NULL_SEMID                0xffffffff
#define    NULL_MSGQID               0xffffffff
#endif
#define    NULL_MSGGET               0
#define    DIR_CODE                  0x2f  /* 定义符号 "/" */

#endif

#if OS_TYPE == OS_KLINUX
#define    NULL_TASKID               ERROR
#define    NULL_SEMID                 NULL
#define    NULL_MSGQID              NULL
#define    TRUE   1
#define    FALSE 0
#define    DIR_CONCATE_CODE        "/"
#define    DIR_CODE                0x2f
#define    VOS_ISDIR(mode)    ((mode & S_IFMT) == S_IFDIR)    /* 判断是否是目录 */
	// #define    malloc(size) __vmalloc(size,GFP_KERNEL |__GFP_HIGHMEM, PAGE_KERNEL)
	//#define    free(buf)      vfree(buf)
#define    printf  printk
#endif


	/************** SOCKET & TCP ***************/
#define NELEMENTS(array)  (sizeof (array) / sizeof ((array) [0]))

#ifndef HASMAX
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif
#endif

#ifndef HASMIN
#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif
#endif 


#if (OS_TYPE == OS_VXWORKS)
#define SOCKET_ERROR     ERROR
#define SOMAXCONN        5
#define VOS_EWOULDBLOCK  EWOULDBLOCK
#define VOS_ECONNRESET   ECONNRESET
#endif

#if (OS_TYPE == OS_WINNT)
	/* 数组中元素个数 */
	///(pclint检测注释掉该行)#define NELEMENTS(array)  (sizeof (array) / sizeof ((array) [0]))
#define CloseSocket closesocket
#define bcopy(src,dst,size) memcpy(dst,src,size)
#define errnoGet         WSAGetLastError
	typedef long int STATUS ;
#define VOS_EWOULDBLOCK WSAEWOULDBLOCK
#define VOS_ECONNRESET WSAECONNRESET
#endif


#if ((OS_TYPE == OS_LINUX) ||(OS_TYPE == OS_KLINUX))
	typedef unsigned long ULONG;
#define errnoGet() errno
#define SOCKET_ERROR     ERROR
#define SOMAXCONN	128
#define VOS_EWOULDBLOCK  EWOULDBLOCK
#define VOS_ECONNRESET ECONNRESET

#endif

#if ((OS_TYPE == OS_VXWORKS) || (OS_TYPE == OS_LINUX)||(OS_TYPE == OS_KLINUX))
	typedef int SOCKET;
#endif

	/**************** VOS TIMER *******************/

	/* 时钟中断精度10ms */
#define  TIMER_RESOLUTION    10 


#if (OS_TYPE == OS_WINNT)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <mmsystem.h>
#define  VOS_TIMERCALLBACK     LPTIMECALLBACK  
#define  VOS_TIMER_ID          WORD32 
#define  INVALID_VOS_TIMERID   0
#endif

#if (OS_TYPE == OS_VXWORKS)
#define  VOS_TIMERCALLBACK     FUNCPTR  
#define  VOS_TIMER_ID          WDOG_ID 
#define  INVALID_VOS_TIMERID   NULL

#define  TIMER_ONESHOT         0
#define  TIMER_PERIODIC        1
#endif

#if (OS_TYPE == OS_PSOS)
#define  VOS_TIMERCALLBACK     LPVOID  
#define  VOS_TIMER_ID          WORD32 
#define  INVALID_VOS_TIMERID   0xffffffff
#endif

#if (OS_TYPE == OS_LINUX)
	typedef  void(*VOS_TIMERCALLBACK)(int);
#define  VOS_TIMER_ID          WORD32 
#define  INVALID_VOS_TIMERID   0
#endif

#if (OS_TYPE == OS_KLINUX)
#ifndef HZ
#define HZ 100
#endif     
	extern unsigned long volatile jiffies;

	typedef  void(*VOS_TIMERCALLBACK)(WORD32);
	typedef  struct timer_list    *VOS_TIMER_ID;
#define  INVALID_VOS_TIMERID   NULL    
#endif

	/**************** VOS VOLUME *******************/
#define        VOLNAME_LENGTH            10


	/**********************************************************
	*                          类型定义                       *
	**********************************************************/

#if    OS_TYPE == OS_VXWORKS
#define    VOS_ISDIR(mode)    ((mode & S_IFMT) == S_IFDIR)    /* 判断是否是目录 */
#define    VOS_ISCHR(mode)    ((mode & S_IFMT) == S_IFCHR)    /* 是否 是特殊字符 */
#define    VOS_ISBLK(mode)    ((mode & S_IFMT) == S_IFBLK)    /* 判断是否是特殊块 */
#define    VOS_ISREG(mode)    ((mode & S_IFMT) == S_IFREG)    /* 判断是否正规块 */
#define    VOS_ISFIFO(mode)   ((mode & S_IFMT) == S_IFIFO)    /* 判断是否fifo  */
#elif OS_TYPE== OS_WINNT
#define    VOS_ISDIR(mode)    ((mode & _S_IFMT) == _S_IFDIR)    /* 判断是否是目录 */
#define    VOS_ISCHR(mode)    ((mode & _S_IFMT) == _S_IFCHR)    /* 是否 是特殊字符 */
#define    VOS_ISBLK(mode)    ((mode & _S_IFMT) == _S_IFBLK)    /* 判断是否是特殊块 */
#define    VOS_ISREG(mode)    ((mode & _S_IFMT) == _S_IFREG)      /* 判断是否正规块 */
#define    VOS_ISFIFO(mode)   ((mode & _S_IFMT) == _S_IFIFO)    /* 判断是否fifo  */
#endif


	/* ID类型定义 */
#if OS_TYPE == OS_VXWORKS
	typedef SWORD32  TASK_ID;
	typedef PART_ID  MEMPART_ID;
	typedef FUNCPTR  VOS_FUNCPTR;
	typedef WIND_TCB TASK_TCB;	
#endif

#if OS_TYPE == OS_PSOS
	typedef WORD32  TASK_ID;
	typedef VOS_VOIDFUNCPTR  VOS_FUNCPTR;
	typedef WORD32  SEM_ID;
	typedef WORD32  MSG_Q_ID;
	typedef WORD32  MEMPART_ID;	
#endif

#if OS_TYPE == OS_WINNT
	typedef HANDLE   TASK_ID;
	typedef HANDLE   SEM_ID;
	typedef HANDLE   MEMPART_ID;
	typedef HANDLE   MSG_Q_ID;
	typedef LPTHREAD_START_ROUTINE VOS_FUNCPTR;	
#endif

#if OS_TYPE == OS_LINUX
	typedef void        VOID;
	typedef pthread_t	TASK_ID;
	typedef sem_t *		SEM_ID; 
#ifndef PART_ID
#define PART_ID int
#endif /*wenhm,050826*/
	typedef PART_ID     MEMPART_ID;
	typedef void*       VOS_FUNCPTR; 
	///typedef void (*AutoRunHandler)(void);
	typedef WORD32      MSG_RECEIVE;/*yangyp*/    
	typedef WORD32      MSG_Q_ID;

	///typedef FUNCPTR     VOS_FUNCPTR; 
	///typedef WIND_TCB    TASK_TCB;
	///typedef WORD16      VOS_TIMER_ID;/*yangyp*/
	///typedef WORD32		SEM_ID;
	///typedef SWORD32     TASK_ID;
#endif
#if OS_TYPE == OS_KLINUX
	typedef void        VOID;
	typedef pthread_t	TASK_ID;
	typedef sem_t*		SEM_ID; 
	/*typedef PART_ID     MEMPART_ID;
	typedef FUNCPTR     VOS_FUNCPTR;
	typedef WIND_TCB    TASK_TCB;*/
	typedef WORD32      MEMPART_ID;
	typedef void*       VOS_FUNCPTR;
	typedef WORD32      MSG_RECEIVE;/*yangyp*/
	typedef WORD16      VOS_TIMER_ID;/*yangyp*/
	typedef WORD32      MSG_Q_ID;
#endif


	/* VOS_STATUS: VOS层函数返回值 */
	typedef enum
	{
		VOS_ERROR = -1,
		VOS_OK = 0,
	}VOS_STATUS;

	/* VOS_SEM_STATE  二进制信号量初始状态 */
	typedef enum
	{
		VOS_SEM_EMPTY,
		VOS_SEM_FULL
	}VOS_SEM_STATE;

	/* 信号量队列类型:先进先出或优先级 */
	typedef enum
	{
		VOS_SEM_Q_FIFO,
		VOS_SEM_Q_PRIORITY
	}VOS_SEM_QUEUE_TYPE;

	/* 消息优先级 */
	typedef enum
	{
		VOS_MSG_PRI_NORMAL,
		VOS_MSG_PRI_URGENT
	}VOS_MSG_TYPE;

	/* 消息排队类型:先进先出或优先级 */
	typedef enum
	{
		VOS_MSG_Q_FIFO,
		VOS_MSG_Q_PRIORITY
	}VOS_MSGQUE_TYPE;

	/* 任务状态 */
	typedef enum
	{
		VOS_TASK_STATUS_NULL,
		VOS_TASK_STATUS_RUNNING,
		VOS_TASK_STATUS_READY,
		VOS_TASK_STATUS_PEND,
		VOS_TASK_STATUS_SUSPEND,
		VOS_TASK_STATUS_DEBUG,
		VOS_TASK_STATUS_DEAD
	}VOS_TASK_STATUS;

	/* 参数和返回值为VOID的函数定义 */
	typedef   VOID(*VOS_VOIDFUNCPTR)(VOID);

	/**********************************************************
	*                          数据结构定义                   *
	**********************************************************/

	/* 系统时钟 */
	typedef struct tagSYS_CLOCK
	{
		WORD16             wSysYear;
		WORD16             wSysMon;
		WORD16             wSysDay;
		WORD16             wSysHour;
		WORD16             wSysMin;
		WORD16             wSysSec;
		WORD16             wSysWeek;
		WORD16             wMilliSec;
	}T_SYS_CLOCK;

#undef st_atime
#undef st_mtime
#undef st_ctime
	/* 文件状态描述 */
	typedef struct tagFileStat
	{
		WORD32  st_dev;
		WORD32  st_ino;
		WORD16  st_mode;
		SWORD16 st_nlink;
		SWORD16 st_uid;
		SWORD16 st_gid;
		WORD32  st_rdev;
		SWORD32 st_size;
		SWORD32 st_atime;
		SWORD32 st_mtime;
		SWORD32 st_ctime;
	}T_FileStat;


	/* added by 温辉敏,文件的访问属性*/
	enum Permissions {
		/// File has world execute permission
		WorldExecute = 1,   
		/// File has world write permission
		WorldWrite = 2,     
		/// File has world read permission
		WorldRead = 4,      
		/// File has group execute permission
		GroupExecute = 8,   
		/// File has group write permission
		GroupWrite = 16,    
		/// File has group read permission
		GroupRead = 32,     
		/// File has owner execute permission
		UserExecute = 64,   
		/// File has owner write permission
		UserWrite = 128,    
		/// File has owner read permission
		UserRead = 256,     
		/// All possible permissions.
		AllPermissions = 0x1ff,   
		/// Owner read & write plus group and world read permissions.
		DefaultPerms = UserRead|UserWrite|GroupRead|WorldRead,
		/// Owner read & write & execute plus group and world read & exectute permissions.
		DefaultDirPerms = DefaultPerms|UserExecute|GroupExecute|WorldExecute		
	};

#if OS_TYPE == OS_WINNT
	/**
	下面结构当和MINIAce一起使用时,
	os_dirent.h中相应的结构产生的冲突,而os_dirent.h结构中采用了ACE_LACKS_STRUCT_DIR才会生效,
	因此可以设定vos.h中不采用ACE_LACKS_STRUCT_DIR宏定义时它的结构dirent才生效. 
	added by wenhm in 2007.05.16
	*/
#ifndef ACE_LACKS_STRUCT_DIR
	/* 路径入口 */
	struct  dirent
	{
		unsigned short d_ino;
		unsigned short d_off;
		unsigned short d_reclen;
		CHAR     d_name [VOS_MAX_FILENAME_LEN + 1];
	};
#endif


	/* 目录项的定义 */
	typedef struct
	{
		SWORD32       dd_fd;        /* 打开目录的文件描述 */
		SWORD32       dd_cookie;    /* 目录中的文件特定标示filesys-specific marker within dir */
		struct dirent dd_dirent;    /* 路径入口 */
	}DIR;


#endif



	/**********************************************************
	*                          函数原型                       *
	**********************************************************/

	/******************  任务管理模块 ************************/
	TASK_ID       VOS_CreateTask(CHAR *pTaskName, SWORD32 priority,
		SWORD32 options, SWORD32 stackSize,
		VOS_FUNCPTR pTaskEntry, SWORD32 arg1,
		SWORD32 arg2, SWORD32 arg3, SWORD32 arg4,
		SWORD32 arg5, SWORD32 arg6, SWORD32 arg7,
		SWORD32 arg8, SWORD32 arg9, SWORD32 arg10);

	VOS_STATUS    VOS_DeleteTask(TASK_ID taskId);
	VOS_STATUS    VOS_SuspendTask(TASK_ID taskId);
	VOS_STATUS    VOS_ResumeTask(TASK_ID  taskId);
	VOS_STATUS    VOS_SetPriority(TASK_ID TaskId, SWORD32 newPriority);
	SWORD32       VOS_GetPriority(TASK_ID TaskId);

	VOS_STATUS    VOS_DelayTask(SWORD32 delayTime);
	TASK_ID       VOS_GetSelfTaskID(VOID);
	VOS_STATUS    VOS_SuspendSelf(VOID);

	VOS_TASK_STATUS VOS_GetTaskStatus(TASK_ID taskId);
	VOID          VOS_CheckStack(TASK_ID taskId);


	/************** 二进制信号量与计数信号量 *****************/
	SEM_ID        VOS_CreateBSem(SWORD32 options, VOS_SEM_STATE initialState);
	SEM_ID        VOS_CreateCSem(SWORD32 options, SWORD32 initialState);
	SEM_ID        VOS_CreateMSem(SWORD32 options);
	VOS_STATUS    VOS_DeleteSem(SEM_ID semId);
	VOS_STATUS    VOS_TakeSem(SEM_ID semId, SWORD32 timeout);
	VOS_STATUS    VOS_GiveSem(SEM_ID semId);


	/**************** 内存管理模块 ***************************/
	MEMPART_ID    VOS_CreateMemPart(CHAR *pPool, WORD32 poolSize);
	VOID         *VOS_AllocMemPart(MEMPART_ID memPartId, WORD32 size);
	VOS_STATUS    VOS_FreeMemPart(MEMPART_ID memPartId, CHAR *pBlock);

	CHAR         *VOS_GetPhysMemTop(VOID);
	WORD32        VOS_GetRnFreeInfo(WORD32 dwRnId);

	/********************* 中断处理 ******* ******************/
	SWORD32       VOS_LockInt();
	VOID          VOS_UnlockInt(SWORD32 dwLevel);


	/********************* 消息队列 **************************/
	MSG_Q_ID      VOS_CreateMsgQue(WORD32 dwMaxMsgNum,
		WORD32 dwMaxMsgLength,
		BYTE ucOptions);
	VOS_STATUS    VOS_DeleteMsgQue(MSG_Q_ID wMsgId);
	VOS_STATUS    VOS_SendMsg(MSG_Q_ID wMsgId,
		CHAR *pcMsgData,
		WORD32 dwlen,
		SWORD32 dwtimeout,
		BYTE ucPrior);
	WORD32        VOS_ReceiveMsg(MSG_Q_ID wMsgId,
		CHAR  *pcMsgDataBuffer,
		WORD32 dwlen,
		SWORD32 iTimeout);
	WORD32        VOS_GetCurMsgs(MSG_Q_ID wMsgId);


	/********************* 时钟模块 **************************/
	VOS_STATUS    VOS_ConnectClk(VOS_VOIDFUNCPTR clkIntEntry);
	SWORD32       VOS_GetSysClkRate(VOID);
	WORD32        VOS_GetTick();
	VOS_STATUS    VOS_IniSysClk(T_SYS_CLOCK *pSysSoftClk);
	VOS_STATUS    VOS_SetSysClkRate(SWORD32 sdTicPerSend);

	VOS_STATUS    VOS_TimeSet(T_SYS_CLOCK *pSysSoftClk);
	VOS_STATUS    VOS_TimeGet(T_SYS_CLOCK *pSysSoftClk);

	VOS_TIMER_ID VOS_RelTimer(
		WORD32 dwTimeLength, 
		VOS_TIMERCALLBACK lpTimeProc,
		WORD32 dwUser,
		WORD32 dwEvents			 
		);

	VOS_TIMER_ID VOS_AbsTimer(
		T_SYS_CLOCK tRelTimerSet, 
		VOS_TIMERCALLBACK lpTimeProc,
		WORD32 dwUser,
		WORD32 dwEvents			 
		);

	VOS_TIMER_ID VOS_PerTimer(
		WORD32 dwTimeLength, 			 
		VOS_TIMERCALLBACK lpTimeProc,
		WORD32 dwUser,
		WORD32 dwEvents			 
		);

	VOS_STATUS   VOS_TimerKill(VOS_TIMER_ID TimerId);


	/********************* 错误异常 **************************/
	SWORD32       VOS_GetErrno(VOID);
	VOID          VOS_AddExcHook(VOS_FUNCPTR excHookEntry);

	/********************* 初始化VOS *************************/
	VOS_STATUS    VOS_InitVOS(VOID);


	/****************** 当前进程PCB操作 **********************/
	VOS_STATUS    VOS_SetCurPCBIndex(WORD16  wIndex);
	WORD16        VOS_GetCurPCBIndex(VOID);
	VOS_STATUS    VOS_FreeTlsData(VOID);

	/******************      事件模块   **********************/
	VOS_STATUS    VOS_SendEvent(TASK_ID taskId, WORD32 dwEvents);
	VOS_STATUS    VOS_ReceiveEvent(WORD32 dwEvents, WORD32 dwTimeout,
		WORD32 *ptEventsR);


	/******************  调试打印函数  **********************/
	VOID          VOS_Display(const CHAR *fmt, ... );


	/********************文件系统模块**********************/
	SWORD32       VOS_Create(CHAR *pcFileName);
	VOS_STATUS    VOS_Delete(CHAR *pcFileName);
	SWORD32       VOS_Open(CHAR *pcFileName,SWORD32 sdwFlag,SWORD32 sdwMode);
	VOS_STATUS    VOS_Close(SWORD32 sdwFileHandle);
	VOS_STATUS    VOS_Rename(CHAR *pcOldFileName,CHAR *pcNewFileName);
	SWORD32       VOS_Read(SWORD32 sdFileHandle,VOID *pBuffer,SWORD32 sdCount);
	SWORD32       VOS_Write(SWORD32 sdFileHandle,VOID *pBuffer,SWORD32 sdCount);
	SWORD32       VOS_FileLength(CHAR *pcFileName);
	SWORD32       VOS_Lseek(SWORD32 sdFileHandle,SWORD32 sdOffset,SWORD32 sdOrigin);
	VOS_STATUS    VOS_CreateDir(CHAR *pcDirName);
	VOS_STATUS    VOS_DeleteDir(CHAR *pcDirName);
	VOS_STATUS    VOS_RenameDir(CHAR *pcOldDirName,CHAR *pcNewDirName);
	DIR           *VOS_OpenDir(CHAR *pcDirName);
	struct dirent *VOS_ReadDir(DIR *pDir);
	VOS_STATUS    VOS_CloseDir(DIR *pDir);
	VOS_STATUS    VOS_Stat(CHAR *pcFileName, T_FileStat *pStat);
	VOS_STATUS    VOS_CreateMemDev(CHAR      *pcRamDiskName,
		CHAR      *pcRamAddr,
		SWORD32   sdwCHARsPerBlk,
		SWORD32   sdwBlksPerTrack,
		SWORD32   sdwNBlocks,
		SWORD32   sdwBlkOffset);
	VOS_STATUS    VOS_StartFtpServer(LPVOID   pLoginRtn,
		SWORD32  sdwStackSize);

	VOS_STATUS    VOS_StopFtpServer(VOID);

#if OS_TYPE == OS_PSOS
	VOS_STATUS    VOS_FileSystemInit(VOID);
#endif

	/****************** SOCKET **********************/
	VOS_STATUS  VOS_InitSocketLib(VOID);
	SOCKET      VOS_Socket(SWORD32 family, SWORD32 type,SWORD32 protocol );
	VOS_STATUS  VOS_Bind(SWORD32 s, const struct sockaddr * name,  SWORD32 namelen);
	VOS_STATUS  VOS_Accept(SOCKET s ,struct sockaddr * addr,SWORD32* addrlen );
	VOS_STATUS  VOS_Listen(SOCKET s ,SWORD32 backlog );
	SWORD32     VOS_Send(SOCKET s,const char * buffer,SWORD32 len, SWORD32 flags);
	SWORD32     VOS_Recv(SOCKET s,const char * buffer,SWORD32 len,SWORD32 flags);
	VOS_STATUS  VOS_CloseSocket(SOCKET s);
	VOS_STATUS  VOS_CleanUp(void);
	VOS_STATUS  VOS_ConnectWithTimeout(SOCKET s,  struct sockaddr * adrs,  int adrsLen,
	struct timeval *  timeVal );
	SWORD32     VOS_SendTo(SOCKET s,const char *buffer,SWORD32 len, SWORD32 flags,
	struct sockaddr *to, int tolen );
	SWORD32     VOS_SendSocketMsg(SOCKET s,  struct msghdr  *mp, SWORD32 flags);
	SWORD32     VOS_RecvFrom(SOCKET s,const char *buffer,SWORD32 len, SWORD32 flags,
	struct sockaddr *from, int  * pFromLen);
	SWORD32     VOS_RecvSocketMsg(SOCKET s,  struct msghdr  *mp, SWORD32 flags);
	VOS_STATUS  VOS_Shutdown(SOCKET s, int how);
	VOS_STATUS  VOS_SetSockOpt (SOCKET s,  int level,  int  optname, char * optval, int optlen );
	VOS_STATUS  VOS_GetSockOpt (SOCKET s,  int level,  int  optname, char * optval, int *optlen );
	VOS_STATUS  VOS_GetSockName(SOCKET s,   struct sockaddr * name,   int * namelen);
	VOS_STATUS  VOS_GetPeerName (SOCKET s, struct sockaddr * name, int * namelen);
	SWORD32     VOS_Select(int width, fd_set  *pReadFds, fd_set  * pWriteFds,
		fd_set * pExceptFds, struct timeval * pTimeOut);
	SWORD32     VOS_Ioctl(int fd, int function,int arg);

	/****************** Exec **********************/
	VOS_STATUS VOS_Exec(
		const CHAR * strFile,		///要执行的程序名称
		const CHAR * strArgs		///要传入的命令行参数
		);

	VOS_STATUS VOS_ExecByFork(
		const CHAR * strFile,	///要执行的程序名称
		const CHAR * strArgs	///要传入的命令行参数
		);

	VOS_STATUS VOS_ForceDelete(CHAR *pcFileName);

	SWORD32 VOS_Chmod(
		const CHAR * pcFileName, ///文件名
		int iPermissions         ///要进行设置的文件属性
		);

	VOS_STATUS VOS_SetRLimit(const int iCoreFileSize);

	VOS_STATUS VOS_GetTimeOfDay(struct timeval *tv, struct timezone *tz);

#ifdef __cplusplus
}
#endif


#endif
/************** End of vos.h *******************************************/

/************** Begin of config.h *******************************************/

/* $Id$
*
* config.h created by wenhm in 2006-11-9
*
* Copyright 2001-2002, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef log4c_config_h
#define log4c_config_h


///#ifdef _WIN32
#define LOG4C_RCPATH	"."
#define VERSION			"1.2.1"
///#endif

#define WITH_ROLLINGFILE 1
#endif



/************** End of config.h *******************************************/

/************** Begin of sd/defs.h *******************************************/
/* $Id$
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef __sd_defs_h
#define __sd_defs_h

#ifdef  __cplusplus
# define __SD_BEGIN_DECLS  extern "C" {
# define __SD_END_DECLS    }
#else
# define __SD_BEGIN_DECLS
# define __SD_END_DECLS
#endif

#endif


/************** End of sd/defs.h *******************************************/

/************** Begin of sd/malloc.h *******************************************/
/* $Id$
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef __sd_malloc_h
#define __sd_malloc_h

#include <stddef.h>
#include <stdlib.h>
///#include <sd/defs.h>

/**
* @file malloc.h
*/

__SD_BEGIN_DECLS

typedef void (*sd_malloc_handler_t)();

extern sd_malloc_handler_t sd_malloc_set_handler(void (*a_handler)());

#ifndef __SD_DEBUG__

extern void *sd_malloc(size_t n);
extern void *sd_calloc(size_t n, size_t s);
extern void *sd_realloc(void *p, size_t n);
extern char *sd_strdup (const char *__str);

#else

#define sd_malloc	malloc
#define sd_calloc	calloc
#define sd_realloc	realloc
#define sd_strdup	strdup

#endif

__SD_END_DECLS

#endif


/************** End of sd/malloc.h *******************************************/

/************** Begin of malloc.c *******************************************/
/* xmalloc.c -- malloc with out of memory checking
Copyright (C) 1990,91,92,93,94,95,96,97 Free Software Foundation, Inc.
This file is part of the GNU C Library.

The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with the GNU C Library; if not, write to the Free
Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307 USA.  */

#ifdef HAVE_CONFIG_H
///#include "config.h"
#endif
#include <stdio.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <string.h>
#include <stdlib.h>
///#include <sd/error.h>

#if defined(__APPLE__)
///# include <sys/time.h>
///# include <crt_externs.h>
# define environ (*_NSGetEnviron())
#endif /* __APPLE__ */

///typedef void (*sd_malloc_handler_t)();

static char*  first_break = NULL;
static sd_malloc_handler_t handler  = NULL;

//static void *
//fixup_null_alloc (n)
//size_t n;
static void * fixup_null_alloc (size_t n)
{
	void* p = 0;

#ifdef HAVE_SBRK
	if (n == 0)
		p = malloc ((size_t) 1);

	if (p == 0) {
		extern char **environ;
		size_t allocated;

		if (first_break != NULL)
			allocated = (char *) sbrk (0) - first_break;
		else
			allocated = (char *) sbrk (0) - (char *) &environ;
		sd_error("\nCannot allocate %lu bytes after allocating %lu bytes\n",
			(unsigned long) n, (unsigned long) allocated);

		if (handler) 
			handler();
		else {
			sd_error("\n\tMemory exhausted !! Aborting.\n");
			abort();
		}
	}
#endif
	return p;
}

//sd_malloc_handler_t
//sd_malloc_set_handler(a_handler)
//sd_malloc_handler_t a_handler;
sd_malloc_handler_t sd_malloc_set_handler(sd_malloc_handler_t a_handler)
{
	sd_malloc_handler_t previous = handler;

	handler = a_handler;
	return previous;
}

/* Allocate N bytes of memory dynamically, with error checking.  */

//void *
//sd_malloc (n)
//size_t n;
void *sd_malloc (size_t n)
{
	void *p;

	p = malloc (n);
	if (p == 0)
		p = fixup_null_alloc (n);
	return p;
}

/* Allocate memory for N elements of S bytes, with error checking.  */

//void *
//sd_calloc (n, s)
//size_t n, s;
void *sd_calloc (size_t n, size_t s)
{
	void *p;

	p = calloc (n, s);
	if (p == 0)
		p = fixup_null_alloc (n * s);
	return p;
}

/* Change the size of an allocated block of memory P to N bytes,
with error checking.
If P is NULL, run sd_malloc.  */

//void *
//sd_realloc (p, n)
//void *p;
//size_t n;
void *sd_realloc (void *p, size_t n)
{
	if (p == 0)
		return sd_malloc (n);
	p = realloc (p, n);
	if (p == 0)
		p = fixup_null_alloc (n);
	return p;
}

/* Return a newly allocated copy of STRING.  */

//char *
//sd_strdup (string)
//const char *string;
char *sd_strdup (const char *string)
{
	return strcpy ((char *)sd_malloc (strlen (string) + 1), string);
}

/************** End of malloc.c *******************************************/

/************** Begin of log4c/appender_type_stream.h *******************************************/
/* $Id$
*
* appender_type_stream.h
* 
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef log4c_appender_type_stream_h
#define log4c_appender_type_stream_h

/**
* @file appender_type_stream.h
*
* @brief Log4c stream appender interface.
*
* The stream appender uses a file handle @c FILE* for logging. The
* appender's name is used as the file name which will be opened at first
* log. An appender can also be associated to an opened file handle using
* the log4c_appender_set_udata() method to update the appender user data
* field. In ptrThis last case, the appender name has no meaning. 2 default
* stream appenders are defined: @c "stdout" and @c "stderr".
*
* The following examples shows how to define and use stream appenders.
* 
* @li the simple way
* @code
*
* log4c_appender_t* myappender;
*
* myappender = log4c_appender_get("myfile.log");
* log4c_appender_set_type(myappender, &log4c_appender_type_stream);
* 
* @endcode
*
* @li the sophisticated way
* @code
*
* log4c_appender_t* myappender;
*
* myappender = log4c_appender_get("myappender");
*    
* log4c_appender_set_type(myappender, &log4c_appender_type_stream);
* log4c_appender_set_udata(myappender, fopen("myfile.log", "w"));
*
* @endcode
*
**/

///#include <log4c/defs.h>
///#include <log4c/appender.h>

__LOG4C_BEGIN_DECLS

/**
* Stream appender type definition.
*
* This should be used as a parameter to the log4c_appender_set_type()
* routine to set the type of the appender.
*
**/
extern const log4c_appender_type_t log4c_appender_type_stream;

__LOG4C_END_DECLS

#endif


/************** End of log4c/appender_type_stream.h *******************************************/



/************** Begin of error.c *******************************************/
///static const char version[] = "$Id$";

/* 
* See the COPYING file for the terms of usage and distribution.
*/

#ifdef HAVE_CONFIG_H
///#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef HAVE_STDARG_H
#  include <stdarg.h>
#else
#  ifdef HAVE_VARARGS_H
#    include <varargs.h>
#  endif
#endif

///#include <sd/error.h>
///#include <sd_xplatform.h>

int sd_debug(const char *fmt, ...)
{
	va_list args;
	int r;

	if (!getenv("SD_DEBUG"))
		return 0;

	r = fprintf(stderr, "[DEBUG] ");
	va_start(args, fmt);
	r += vfprintf(stderr, fmt, args);
	va_end(args);
	r += fprintf(stderr, "\n");

	return r;
}

int sd_error(const char *fmt, ...)
{
	va_list args;
	int r;

	if (!getenv("SD_ERROR"))
		return 0;

	r = fprintf(stderr, "[ERROR] ");
	va_start(args, fmt);
	r += vfprintf(stderr, fmt, args);
	va_end(args);
	r += fprintf(stderr, "\n");

	return r;
}

/************** End of error.c *******************************************/



/************** Begin of sd/factory.h *******************************************/
/* $Id$
*
* factory.h
* 
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef __sd_factory_h
#define __sd_factory_h

/**
* @file factory.h
*/

#include <stdio.h>
///#include <sd/defs.h>

__SD_BEGIN_DECLS

struct __sd_factory;
typedef struct __sd_factory sd_factory_t;

struct __sd_factory_ops
{
	void* (*fac_new)	(const char*);
	void  (*fac_delete)	(void*);
	void  (*fac_print)	(void*, FILE*);
};
typedef struct __sd_factory_ops sd_factory_ops_t;

extern sd_factory_t* sd_factory_new(const char* a_name, 
									const sd_factory_ops_t* a_ops);
extern void	sd_factory_delete(sd_factory_t* a_this);
extern void*	sd_factory_get(sd_factory_t* a_this, const char* a_name);
extern void	sd_factory_destroy(sd_factory_t* a_this, void* a_pr);
extern void	sd_factory_print(const sd_factory_t* a_this, FILE* a_stream);
extern int	sd_factory_list(const sd_factory_t* a_this, void** a_items,
							int a_nitems);

__SD_END_DECLS

#endif


/************** End of sd/factory.h *******************************************/

/************** Begin of sd/hash.h *******************************************/
/* $Id$
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
* Author: Marc Vertes <mvertes@meiosys.com>
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef __sd_hash_h
#define __sd_hash_h

/**
* @file hash.h
*
* @brief Generic hash table. It is implemented as an array of doubly-linked
* lists of iterators. The index within the array is computed by a efficient
* hash function.
*/

#include <stddef.h>
///#include <sd/defs.h>

__SD_BEGIN_DECLS

struct __sd_hash_ops {
	unsigned int	(*hash)		(const void*);
	int			(*compare)	(const void*, const void*);
	void*		(*key_dup)	(const void*);
	void		(*key_free)	(void*);
	void*		(*data_dup)	(const void*);
	void		(*data_free)	(void*);
};

/**
* This structure holds hash table operations.
*/
typedef struct __sd_hash_ops sd_hash_ops_t;

/**
* This is the hash table.
*/
typedef struct __sd_hash sd_hash_t;

struct __sd_hash_iter {
	void*			key;
	void*			data;
	struct __sd_hash*		hash;
	unsigned int		__hkey;
	struct __sd_hash_iter*	__next;
	struct __sd_hash_iter*	__prev;
	int				__foreach;
};

/**
* This is the elementary container for storing data into the hash table.
*/
typedef struct __sd_hash_iter sd_hash_iter_t;

/**
* Signature of a "foreach" function.
*/
typedef unsigned int (*sd_hash_func_t)(void* a_key, void* a_data,
									   void* a_userdata);

/**
* Creates a new hash table. One can customize the memory (de)allocation
* policy for keys and data stored in the hash table.
* @param a_size the initial size of the array.
* @param a_ops the hash operations. If NULL, then string keys are assumed and
* no memory (de)allocation is performed for keys and data.
* @return a dynamicaly allocated hash table.
*/
extern sd_hash_t* sd_hash_new(size_t a_size, const sd_hash_ops_t* a_ops);

/**
* Destroys the hash table.
*/
extern void sd_hash_delete(sd_hash_t* a_this);

/**
* clears the hash table.
*/
extern void sd_hash_clear(sd_hash_t* a_this);

/**
* Looks for the iterator associated to the given key in the hash table.
* @param a_key the key associated to the iterator.
* @return a pointer to the found iterator or NULL.
*/
extern sd_hash_iter_t* sd_hash_lookup(sd_hash_t* a_this, const void* a_key);

/**
* Looks for the iterator associated to the given key in the hash table and
* creates it if doesn't exist.
* @param a_key the key associated to the iterator.
* @return a pointer to the found iterator or NULL.
*/
extern sd_hash_iter_t* sd_hash_lookadd(sd_hash_t* a_this, const void* a_key);

/**
* Adds data associated with the given key into the hash table. If the
* key already exists, the old iterator is freed according to the memory
* management operations passed to sd_hash_new().
* @param a_key the key associated to the iterator.
* @return a pointer to the created or found iterator.
*/
extern sd_hash_iter_t* sd_hash_add(sd_hash_t* a_this, const void* a_key,
								   void* a_data);

/**
* Removes an iterator from the hash table.
* @param a_key the key associated to the iterator.
*/
extern void sd_hash_del(sd_hash_t* a_this, const void* a_key);

/**
* Calls \a a_func for each element of the hash table, as long as \a a_func
* returns 0.
* @param a_func the "foreach" function.
* @param a_data the user data passed to \a a_func.
*/
extern void sd_hash_foreach(sd_hash_t* a_this, sd_hash_func_t a_func,
							void* a_data);

/**
* Gets the number of iterators.
*/
extern unsigned int sd_hash_get_nelem(sd_hash_t* a_this);

/**
* Gets the size of the array.
*/
extern unsigned int sd_hash_get_size(sd_hash_t* a_this);

/**
* Gets the first iterator.
*/
extern sd_hash_iter_t* sd_hash_begin(sd_hash_t* a_this);

/**
* Gets the last iterator.
*/
extern sd_hash_iter_t* sd_hash_end(sd_hash_t* a_this);

/**
* Gets a pointer to the next iterator.
*/
extern sd_hash_iter_t* sd_hash_iter_next(sd_hash_iter_t* a_this);

/**
* Gets a pointer to the previous iterator.
*/
extern sd_hash_iter_t* sd_hash_iter_prev(sd_hash_iter_t* a_this);

/**
* Gets a pointer to the previous iterator.
*/
extern void sd_hash_iter_del(sd_hash_iter_t* a_this);

/**
* Hashes strings.
*/
extern unsigned int sd_hash_hash_string(const char* a_string);

__SD_END_DECLS

#endif


/************** End of sd/hash.h *******************************************/

/************** Begin of sd/sd_xplatform.h *******************************************/
/* $Id$
*
* sd_xplatform.h
* 
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef __sd_xplatform_h
#define __sd_xplatform_h

#ifndef _WIN32
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#else
#include <time.h>
#include <io.h> /* needed for _access  */
#include <windows.h>
#include <winsock.h>
#include <process.h>
#endif


#ifdef HAVE_STDINT_H
#       include <stdint.h>
#define  XP_UINT64 uint64_t
#define  XP_INT64 int64_t
#else
#ifndef _WIN32
#define  XP_UINT64 unsigned long long
#define  XP_INT64 long long
#else
#define  XP_UINT64 DWORD64
#define  XP_INT64 __int64
#endif
#endif

///#include <log4c/defs.h>
///#include <sd/defs.h>


/*extern int sd_optind; */
LOG4C_DATA int sd_optind; 

extern void getopt_reset(void); 

extern int sd_getopt(int argc, char *const *argv, const char *opts);

#ifdef _WIN32
#define SD_GETOPT(a,b,c) sd_getopt(a,b,c)
#define SD_OPTIND sd_optind
#else
#define SD_GETOPT(a,b,c) getopt(a,b,c)
#define SD_OPTIND optind
#endif


#ifdef _WIN32
#define SD_GETTIMEOFDAY(a,b) sd_gettimeofday(a,b)
extern int sd_gettimeofday(LPFILETIME lpft, void* tzp);
#else
#define SD_GETTIMEOFDAY(a,b) gettimeofday(a,b)
extern int sd_gettimeofday(struct timeval* tp, void* tzp);
#endif

#ifdef _WIN32
#define FILE_SEP "\\"
#else
#define FILE_SEP "/"
#endif

#ifdef _WIN32
#define SD_ACCESS_READ(a) _access(a,04)
#else
#define SD_ACCESS_READ(a) access(a,R_OK)
#endif

int sd_stat_ctime(const char* path, time_t* time);
#define SD_STAT_CTIME(path, time) sd_stat_ctime(path, time)

#ifndef _WIN32
#define DIFF_CMD  "/usr/bin/diff -q"
#else
#define DIFF_CMD  "comp.exe"
#endif

#ifdef _WIN32
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#define alloca _alloca
#define _x_strncasecmp strnicmp
#define _x_strcasecmp stricmp
#define YY_NO_UNISTD_H
#define sleep(x) Sleep(x*1000)
#endif


/* Maybe should be using ptrThis for to mean
* MS compiler #if defined(_MSC_VER) 
*/
#ifdef _WIN32
#define pthread_t HANDLE
#define pthread_mutex_t HANDLE
#define pthread_attr_t DWORD
#define THREAD_FUNCTION DWORD (WINAPI *)(void *)

/*
* This one not obvious: you would have naturally thought of mapping to
* CreateThread()--turns out that to be safe using CRT functions
* you need to use _begintheadex().  
* cf. http://msdn2.microsoft.com/en-us/library/7t9ha0zh.aspx
*  http://groups.google.com/group/comp.os.ms-windows.programmer.win32/browse_thread/thread/86d8624e7ee38c5d/f947ac76cd10f397?lnk=st&q=when+to+use+_beginthreadex&rnum=1#f947ac76cd10f397
* 
*/
#define pthread_create(thhandle,attr,thfunc,tharg) \
	(int)((*thhandle=(HANDLE)_beginthreadex(NULL,0,(THREAD_FUNCTION)thfunc,tharg,0,NULL))==NULL)
#define pthread_join(thread, result) \
	((WaitForSingleObject((thread),INFINITE)!=WAIT_OBJECT_0) || !CloseHandle(thread))
#define pthread_exit() _endthreadex(0)
#define pthread_cancel(thread) TerminateThread(thread,0)

#define pthread_mutex_init(pobject,pattr) (*pobject=CreateMutex(NULL,FALSE,NULL))
#define pthread_mutex_lock(pobject) WaitForSingleObject(*pobject,INFINITE)
#define pthread_mutex_unlock(pobject) ReleaseMutex(*pobject)

#define pthread_mutex_destroy(pobject) CloseHandle(*pobject)

#endif


#ifdef __HP_cc
#define inline __inline
#endif 

#endif


/************** End of sd/sd_xplatform.h *******************************************/

/************** Begin file appender.c ***************************************/
static const char version[] = "$Id$";

/*
* appender.c
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifdef HAVE_CONFIG_H
///#include "config.h"
#endif

///#include <log4c/appender.h>
///#include <log4c/appender_type_stream.h>
#include <string.h>
///#include <sd/error.h>
///#include <sd/malloc.h>
///#include <sd/factory.h>
///#include <sd/hash.h>
///#include <sd/sd_xplatform.h>

struct __log4c_appender
{
	char*				app_name;
	const log4c_layout_t*		app_layout;
	const log4c_appender_type_t*	app_type;
	int					app_isopen;
	void*				app_udata;
};

sd_factory_t* log4c_appender_factory = NULL;

//////////////////////////////////////////////////////////////////////////
///以下为温辉敏修改的代码，将原有代码用#if 0...#endif注释掉
// 为解决log4c_layout_types中内存泄漏而将静态局部变量提升为全局局部变量 [9/8/2008 温辉敏]
static sd_hash_t* gs_types = NULL;

static sd_hash_t* log4c_appender_types(void)
{
	///static sd_hash_t* types = NULL;	
	if (!gs_types)
		gs_types = sd_hash_new(20, NULL);

	return gs_types;
}

/** 删除本appender.c文件中定义的全局和静态的指针指向的内存,防止内存泄漏
如：
1.gs_types.
2.
@return void.
作者：温辉敏 日期:2008.09.08
*/
extern void log4c_appender_delete_global()
{
	if (NULL != gs_types)
	{
		sd_hash_delete(gs_types);
		gs_types = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
#if 0
/**
* @bug log4c_appender_type hash is not freed in destructor
*/

/*******************************************************************************/
static sd_hash_t* log4c_appender_types(void)
{
	static sd_hash_t* types = NULL;

	if (!types)
		types = sd_hash_new(20, NULL);

	return types;
}
#endif

extern void log4c_appender_types_print(FILE *fp)
{
	sd_hash_iter_t* i;

	fprintf(fp, "appender types:");
	for (i = sd_hash_begin(log4c_appender_types());
		i != sd_hash_end(log4c_appender_types()); 
		i = sd_hash_iter_next(i) ) 
	{
		fprintf(fp, "'%s' ",((log4c_appender_type_t *)(i->data))->name );
	}
	fprintf(fp, "\n");
}

/*******************************************************************************/
extern const log4c_appender_type_t* log4c_appender_type_get(const char* a_name)
{
	sd_hash_iter_t* i;

	if (!a_name)
		return NULL;

	if ( (i = sd_hash_lookup(log4c_appender_types(), a_name)) != NULL)
		return (log4c_appender_type_t*)i->data;

	return NULL;
}

/*******************************************************************************/
extern const log4c_appender_type_t* log4c_appender_type_set(
	const log4c_appender_type_t* a_type)
{
	sd_hash_iter_t* i = NULL;
	void* previous = NULL;

	if (!a_type)
		return NULL;

	if ( (i = sd_hash_lookadd(log4c_appender_types(), a_type->name)) == NULL)
		return NULL;

	previous = i->data;
	i->data  = (void*) a_type;

	return (log4c_appender_type_t*)previous;
}

/*******************************************************************************/
extern log4c_appender_t* log4c_appender_get(const char* a_name)
{
	static const sd_factory_ops_t log4c_appender_factory_ops = {
		/*(void*) log4c_appender_new,
		(void*) log4c_appender_delete,
		(void*) log4c_appender_print,*/
		(void *( *)(const char *))log4c_appender_new,
		(void ( *)(void *))log4c_appender_delete,
		(void ( *)(void *,FILE *))log4c_appender_print
	};

	if (!log4c_appender_factory) {
		log4c_appender_factory = sd_factory_new("log4c_appender_factory", 
			&log4c_appender_factory_ops);

		/* build default appenders */
		log4c_appender_set_udata(log4c_appender_get("stderr"), stderr);
		log4c_appender_set_udata(log4c_appender_get("stdout"), stdout);
	}

	return (log4c_appender_t *)sd_factory_get(log4c_appender_factory, a_name);
}

/*******************************************************************************/
extern log4c_appender_t* log4c_appender_new(const char* a_name)
{
	log4c_appender_t* ptrThis;

	if (!a_name)
		return NULL;

	ptrThis	     = (log4c_appender_t*)sd_calloc(1, sizeof(log4c_appender_t));
	ptrThis->app_name   = sd_strdup(a_name);
	ptrThis->app_type   = &log4c_appender_type_stream;
	ptrThis->app_layout = log4c_layout_get("basic");
	ptrThis->app_isopen = 0;
	ptrThis->app_udata  = NULL;
	return ptrThis;
}

/*******************************************************************************/
extern void log4c_appender_delete(log4c_appender_t* ptrThis)
{
	sd_debug("log4c_appender_delete['%s'", 
		(ptrThis && ptrThis->app_name ? ptrThis->app_name: "(no name)"));
	if (!ptrThis){
		goto log4c_appender_delete_exit;
	}

	log4c_appender_close(ptrThis);
	if (ptrThis->app_name){
		free(ptrThis->app_name);  
	}
	free(ptrThis);

log4c_appender_delete_exit:
	sd_debug("]");
}

/*******************************************************************************/
extern const char* log4c_appender_get_name(const log4c_appender_t* ptrThis)
{
	return (ptrThis ? ptrThis->app_name : "(nil)");
}

/*******************************************************************************/
extern const log4c_appender_type_t* log4c_appender_get_type(
	const log4c_appender_t* ptrThis)
{
	return (ptrThis ? ptrThis->app_type : NULL);
}

/*******************************************************************************/
extern const log4c_layout_t* log4c_appender_get_layout(const log4c_appender_t* ptrThis)
{
	return (ptrThis ? ptrThis->app_layout : NULL);
}

/*******************************************************************************/
extern void* log4c_appender_get_udata(const log4c_appender_t* ptrThis)
{
	return (ptrThis ? ptrThis->app_udata : NULL);
}

/*******************************************************************************/
extern const log4c_appender_type_t* log4c_appender_set_type(
	log4c_appender_t*			ptrThis,
	const log4c_appender_type_t*	a_type)
{
	const log4c_appender_type_t* previous;

	if (!ptrThis)
		return NULL;

	previous = ptrThis->app_type;
	ptrThis->app_type = a_type;
	return previous;
}

/*******************************************************************************/
extern const log4c_layout_t* log4c_appender_set_layout(
	log4c_appender_t*	ptrThis, 
	const log4c_layout_t* a_layout)
{
	const log4c_layout_t* previous;

	if (!ptrThis)
		return NULL;

	previous = ptrThis->app_layout;
	ptrThis->app_layout = a_layout;
	return previous;
}

/*******************************************************************************/
extern void* log4c_appender_set_udata(log4c_appender_t* ptrThis, void* a_udata)
{
	void* previous;

	if (!ptrThis)
		return NULL;

	previous = ptrThis->app_udata;
	ptrThis->app_udata = a_udata;
	return previous;
}

/*******************************************************************************/
extern int log4c_appender_open(log4c_appender_t* ptrThis)
{
	int rc = 0;

	if (!ptrThis)
		return -1;

	if (ptrThis->app_isopen)
		return 0;

	if (!ptrThis->app_type)
		return 0;

	if (!ptrThis->app_type->open)
		return 0;

	if (ptrThis->app_type->open(ptrThis) == -1){
		rc = -1;
	}
	if (!rc) {
		ptrThis->app_isopen++;
	}

	return rc;
}

/**
* @bug is ptrThis the right place to open an appender ? 
*/

/*******************************************************************************/
extern int log4c_appender_append(
								 log4c_appender_t*		ptrThis, 
								 log4c_logging_event_t*	a_event)
{
	if (!ptrThis)
		return -1;

	if (!ptrThis->app_type)
		return 0;

	if (!ptrThis->app_type->append)
		return 0;

	if (!ptrThis->app_isopen)
		if (log4c_appender_open(ptrThis) == -1)
			return -1;

	if ( (a_event->evt_rendered_msg = 
		log4c_layout_format(ptrThis->app_layout, a_event)) == NULL)
		a_event->evt_rendered_msg = a_event->evt_msg;

	return ptrThis->app_type->append(ptrThis, a_event);
}


/*******************************************************************************/
extern int log4c_appender_append_no_file_num_no_layout(
	log4c_appender_t*		ptrThis, 
	log4c_logging_event_t*	a_event)
{
	if (!ptrThis)
		return -1;

	if (!ptrThis->app_type)
		return 0;

	if (!ptrThis->app_type->append)
		return 0;

	if (!ptrThis->app_isopen)
		if (log4c_appender_open(ptrThis) == -1)
			return -1;

#if 0
	if ( (a_event->evt_rendered_msg = 
		log4c_layout_format(ptrThis->app_layout, a_event)) == NULL)
		a_event->evt_rendered_msg = a_event->evt_msg;
#else
	a_event->evt_rendered_msg = a_event->evt_msg;
#endif

	return ptrThis->app_type->append(ptrThis, a_event);
}

/*******************************************************************************/
extern int log4c_appender_close(log4c_appender_t* ptrThis)
{
	if (!ptrThis)
		return -1;

	if (!ptrThis->app_isopen)
		return 0;

	if (!ptrThis->app_type)
		return 0;

	if (!ptrThis->app_type->close)
		return 0;

	if (ptrThis->app_type->close(ptrThis) == -1)
		return -1;

	ptrThis->app_isopen--;
	return 0;
}

/*******************************************************************************/
extern void log4c_appender_print(const log4c_appender_t* ptrThis, FILE* a_stream)
{
	if (!ptrThis) 
		return;

	fprintf(a_stream, "{ name:'%s' type:'%s' layout:'%s' isopen:%d udata:%p}",
		ptrThis->app_name, 
		ptrThis->app_type ? ptrThis->app_type->name : "(not set)",
		log4c_layout_get_name(ptrThis->app_layout),
		ptrThis->app_isopen, 
		ptrThis->app_udata);
}

/************** End of appender.c *******************************************/

/************** Begin of log4c/appender_type_rollingfile.h *******************************************/
/* $Id: appender_type_rollingfile.h
*
* appender_type_rollingfile.h
* 
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef log4c_appender_type_rollingfile_h
#define log4c_appender_type_rollingfile_h

/**
* @file appender_type_rollingfile.h
*
* @brief Log4c rolling file appender interface.
*
* The rolling file appender implements a logging mechanism of
* a list of files up to a maximum number.
*
* The files are written by default to the current directory with logging
* names folowing the pattern log.1, log.2 etc.  These parameters may
* be changed using the appropriate setter functions.
*
* If the appender fails to open logfiles for writing then the
* messages are logged to stderr--it will continue to try to open
* the zero-th file for writing at rollover events so if it succeeds
* at some point to open that file the messages will start to appear therein
* and will no longer be sent to stderr.
*
* Switching from logging from one file
* to the next is referred to as a 'rollover event'.
*
* The policy that determines when a rollover event should happen is
* called a 'rolling policy'.
*
* A mechanism is provided to allow different rolling policies to be defined.
*
* Log4c ships with (and defaults to) the classic size-window rollover policy:
* ptrThis triggers rollover when files reach a maximum size.  The first file in
* the list is
* always the current file; when a rollover event occurs files are shifted up
* by one position in the list--if the number of files in the list has already
* reached the max then the oldest file is rotated out of the window.
*
* See the documentation in the rollingpolicy_type_sizewin.h file for
* more details on the size-win rollover policy.
*
*/

///#include <log4c/defs.h>
///#include <log4c/appender.h>
///#include <log4c/rollingpolicy.h>

__LOG4C_BEGIN_DECLS

/**
* rollingfile appender type definition.
*
* This should be used as a parameter to the log4c_appender_set_type()
* routine to set the type of the appender.
*
**/
LOG4C_API const log4c_appender_type_t log4c_appender_type_rollingfile;

/**
* Get a new rolling file appender configuration object.
* @return a new rolling file appender configuration object, otherwise NULL.
*/
LOG4C_API rollingfile_udata_t *rollingfile_make_udata(void);

/**
* Set the logging directory in ptrThis rolling file appender configuration.
* @param rfudatap the rolling file appender configuration object.
* @param logdir the logging directory to set.
* @return zero if successful, non-zero otherwise.
*/
LOG4C_API int rollingfile_udata_set_logdir(
	rollingfile_udata_t *rfudatap,
	char* logdir);
/**
* Set the prefix string in ptrThis rolling file appender configuration.
* @param rfudatap the rolling file appender configuration object.
* @param prefix the logging files prfix to use.
* @return zero if successful, non-zero otherwise.
*/                            
LOG4C_API int rollingfile_udata_set_files_prefix(
	rollingfile_udata_t *rfudatap, char * prefix);
/**
* Set the rolling policy in ptrThis rolling file appender configuration.
* @param rfudatap the rolling file appender configuration object.
* @param policyp the logging files prfix to use.
* @return zero if successful, non-zero otherwise.
*/                          
LOG4C_API int rollingfile_udata_set_policy(rollingfile_udata_t* rfudatap,
										   log4c_rollingpolicy_t* policyp);                       
/**
* Get the logging directory in ptrThis rolling file appender configuration.
* @param rfudatap the rolling file appender configuration object.
* @return the logging directory.
*/                              
LOG4C_API const char* rollingfile_udata_get_logdir(rollingfile_udata_t* rfudatap);

/**
* Get the prefix string in ptrThis rolling file appender configuration.
* @param rfudatap the rolling file appender configuration object.
* @return the prefix.
*/ 
LOG4C_API const char* rollingfile_udata_get_files_prefix(
	rollingfile_udata_t* rfudatap);

/**
* Get the prefix string in ptrThis rolling file appender configuration.
* @param rfudatap the rolling file appender configuration object.
* @return the current size of the file being logged to.
*/ 
LOG4C_API long  rollingfile_get_current_file_size( rollingfile_udata_t* rfudatap);

__LOG4C_END_DECLS

#endif


/************** End of log4c/appender_type_rollingfile.h *******************************************/

/************** Begin of appender_type_rollingfile.c *******************************************/
/*
* appender_type_rollingfile.c
*
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifdef HAVE_CONFIG_H
///#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif
///#include <log4c/appender.h>
///#include <log4c/appender_type_rollingfile.h>
///#include <log4c/rollingpolicy.h>
///#include <sd/malloc.h>
///#include <sd/error.h>
///#include <sd/sd_xplatform.h>

/* Internal structs that defines the conf and the state info
* for an instance of the appender_type_rollingfile type.
*/    
struct __rollingfile_conf {
	const char* rfc_logdir;
	const char* rfc_files_prefix; 
	log4c_rollingpolicy_t* rfc_policy;
};

struct __rollingfile_udata {
	struct __rollingfile_conf rfu_conf;
	long rfu_current_file_size; 
	FILE *rfu_current_fp;
	char *rfu_base_filename;
	pthread_mutex_t rfu_mutex;
};

static int rollingfile_open_zero_file(char *filename, long *fsp, FILE **fpp);
static char *rollingfile_make_base_name(const char *log_dir, const char* prefix);

/***************************************************************************
Appender Interface functions: open, append, close

****************************************************************************/
static int rollingfile_open(log4c_appender_t* ptrThis)
{
	int rc = 0; 
	rollingfile_udata_t *rfup = (rollingfile_udata_t *)log4c_appender_get_udata(ptrThis);  

	sd_debug("rollingfile_appender_open[");

	/* xxx Make the init here more fine grained */

	if (rfup == NULL ){

		/* No info provided so set defaults */
		sd_debug("making new rollingfile conf object, with default logdir/logprefix");
		rfup = rollingfile_make_udata();

		rollingfile_udata_set_logdir(rfup, ROLLINGFILE_DEFAULT_LOG_DIR);
		rollingfile_udata_set_files_prefix(rfup, ROLLINGFILE_DEFAULT_LOG_PREFIX);

	} else {
		sd_debug("appender has udata already: logdir='%s' logprefix='%s'",
			rollingfile_udata_get_logdir(rfup),
			rollingfile_udata_get_files_prefix(rfup));
	}

	rfup->rfu_current_file_size = 0; 
	pthread_mutex_init(&rfup->rfu_mutex, NULL);

	/* ptrThis will open the right file and set the current fp */
	rfup->rfu_base_filename = rollingfile_make_base_name(
		rfup->rfu_conf.rfc_logdir,
		rfup->rfu_conf.rfc_files_prefix);

	/* xxx A policy exists, but is it initalised ?
	Do we need such a concept ?
	I think so because we need to be sure 
	*/

	/*
	* If a policy exists defer to it to open the first file:
	* it may wish to apply a policy to existing log files.
	*/
	if ( rfup->rfu_conf.rfc_policy ) {
		sd_debug("rollingfile udata has a policy '%s'--calling rollover",
			log4c_rollingpolicy_get_name( rfup->rfu_conf.rfc_policy)  );

		/*
		* If the policy is not yet initialized force it now to default values
		*/
		if (!log4c_rollingpolicy_is_initialized(rfup->rfu_conf.rfc_policy)){
			sd_debug("policy not initialized, calling init now");
			log4c_rollingpolicy_init(rfup->rfu_conf.rfc_policy,
				rfup);
		}

		if ( log4c_rollingpolicy_rollover(rfup->rfu_conf.rfc_policy,
			&rfup->rfu_current_fp)){
				rc = 1; /* rollover error */
		} else {
			rfup->rfu_current_file_size = 0;
		}
	} else {
		/* No policy defined, open it ourselves */
		rollingfile_open_zero_file( rfup->rfu_base_filename,
			&rfup->rfu_current_file_size,
			&rfup->rfu_current_fp);
	}

	sd_debug("]");

	return rc;

}

/***************************************************************************/

static int rollingfile_append(log4c_appender_t* ptrThis, 
							  const log4c_logging_event_t* a_event)
{
	rollingfile_udata_t* rfup = (rollingfile_udata_t *)log4c_appender_get_udata(ptrThis); 
	log4c_logging_event_t* my_event = 
		(log4c_logging_event_t*)a_event;
	int rc = 0;

	sd_debug("rollingfile_append[");

	pthread_mutex_lock(&rfup->rfu_mutex);  /***** LOCK ****/

	if ( rfup->rfu_conf.rfc_policy != NULL) {

		/* some policy set */
		sd_debug("check trigger, currfs=%ld",rfup->rfu_current_file_size);

		if( log4c_rollingpolicy_is_triggering_event(rfup->rfu_conf.rfc_policy,
			a_event,		    
			rfup->rfu_current_file_size)){
#ifdef __SD_DEBUG__
				sd_debug("non-buffered rotate event len=%ld, currfs=%ld",
					strlen(a_event->evt_rendered_msg), rfup->rfu_current_file_size);
#endif

				if ( (rc = log4c_rollingpolicy_rollover(rfup->rfu_conf.rfc_policy,
					&rfup->rfu_current_fp)) <= ROLLINGPOLICY_ROLLOVER_ERR_CAN_LOG){
						rfup->rfu_current_file_size = 0;
				}
		} else {
			/* no need to rotate up--stick with the current fp */
			/*sd_debug("non-buffered not rotate event");*/
		}
	}else {
		// no rotation policy, just continue using the current fp 
	}

	/* only attempt the write if the policy implem says I can */
	if ( rc <= ROLLINGPOLICY_ROLLOVER_ERR_CAN_LOG ) {	           
		rc = fprintf(rfup->rfu_current_fp, a_event->evt_rendered_msg);
		rfup->rfu_current_file_size += strlen(a_event->evt_rendered_msg);

		/*
		* the fprintf needs to be inside the lock 
		* because otherwise we might be writing to a file and another
		* thread could be renaming it in some rotation policy code
		* ...which wouldn't be nice
		*/
	} else {
		sd_error("not logging--something went wrong (trigger check or"
			" rollover failed)");
	}
	sd_debug("]");
	pthread_mutex_unlock(&rfup->rfu_mutex);  /****** UNLOCK *****/
	return (rc);

}
/****************************************************************************/
static int rollingfile_close(log4c_appender_t* ptrThis)
{  
	int rc = 0;
	rollingfile_udata_t* rfup = NULL; 

	sd_debug("rollingfile_close[");
	if(!ptrThis){
		rc = -1; 
	} else {

		rfup = (rollingfile_udata_t*)log4c_appender_get_udata(ptrThis);

		pthread_mutex_lock(&rfup->rfu_mutex);  /***** LOCK ****/  
		rc = (rfup->rfu_current_fp ? fclose(rfup->rfu_current_fp) : 0);
		rfup->rfu_current_fp = NULL;

		rfup->rfu_current_file_size = 0;
		if( rfup->rfu_base_filename) {
			free( (char *)rfup->rfu_base_filename);
			rfup->rfu_base_filename = NULL;
		}
		if( rfup->rfu_conf.rfc_logdir) {
			free( (char *)rfup->rfu_conf.rfc_logdir);
			rfup->rfu_conf.rfc_logdir = NULL;
		}
		if( rfup->rfu_conf.rfc_files_prefix) {
			free( (char *)rfup->rfu_conf.rfc_files_prefix);
			rfup->rfu_conf.rfc_files_prefix = NULL;
		}
		if ( rfup->rfu_conf.rfc_policy){
			if (!log4c_rollingpolicy_fini(rfup->rfu_conf.rfc_policy)){
				rfup->rfu_conf.rfc_policy = NULL;
			}else{ 
				sd_debug("rollingpolicy fini failed");
				rc = -1;
			}
		}

		pthread_mutex_unlock(&rfup->rfu_mutex);  /****** UNLOCK *****/

		//////////////////////////////////////////////////////////////////////////
		///解决资源泄漏问题[4/18/2008 温辉敏]
		pthread_mutex_destroy(&rfup->rfu_mutex);
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		///解决内存泄漏 [4/18/2009 温辉敏] 
		if (NULL != rfup)
		{
			free(rfup);
		}
		//////////////////////////////////////////////////////////////////////////

	}
	sd_debug("]");
	return(rc);
}

/****************************************************************************
rollingfile specific conf functions
****************************************************************************/

int rollingfile_udata_set_policy(rollingfile_udata_t * rfup, 
								 log4c_rollingpolicy_t *polp){

									 rfup->rfu_conf.rfc_policy = polp;
									 return(0);
}

/*******************************************************************************/

rollingfile_udata_t *rollingfile_make_udata(void){
	rollingfile_udata_t *rfup = NULL;
	rfup = (rollingfile_udata_t *)sd_calloc(1, sizeof(rollingfile_udata_t));

	return(rfup);
}

/*******************************************************************************/

LOG4C_API int rollingfile_udata_set_logdir(rollingfile_udata_t* rfup, char *logdir){

	rfup->rfu_conf.rfc_logdir = strdup(logdir);  

	return(0);
}
/*******************************************************************************/

LOG4C_API const char * rollingfile_udata_get_logdir(rollingfile_udata_t* rfup){

	return(rfup->rfu_conf.rfc_logdir); 

}
/*******************************************************************************/

LOG4C_API int rollingfile_udata_set_files_prefix( rollingfile_udata_t* rfup, char* fprefix){

	rfup->rfu_conf.rfc_files_prefix = strdup(fprefix);

	return(0);
}
/*******************************************************************************/

LOG4C_API const char*  rollingfile_udata_get_files_prefix( rollingfile_udata_t* rfup){

	return(rfup->rfu_conf.rfc_files_prefix);

}
/*******************************************************************************/

LOG4C_API long  rollingfile_get_current_file_size( rollingfile_udata_t* rfup){

	return(rfup->rfu_current_file_size);

}

/*****************************************************************************
Private functions
*****************************************************************************/
#if 0
/* ptrThis function currently unused but would be handy for sanity
* checking what we think is the file size against the actual size
*/  
static int rollingfile_get_system_filesize(FILE *fp){
	struct stat	info;
	int		rv;

	if ((rv = fstat(fileno(fp), &info)) != 0) {
		return -1;
	}
	return info.st_size;
}
#endif
/*******************************************************************************/

static int rollingfile_open_zero_file(char *filename, long *fsp, FILE **fpp ){

	sd_debug("rollingfile_open_zero_file[");
	if ( (*fpp = fopen(filename, "w+")) == NULL){
		*fpp = stderr;
	}
	*fsp = 0;

	/* unbuffered mode at the filesystem level
	xxx make ptrThis configurable from the outside ?
	*/
	setbuf(*fpp, NULL);    

	sd_debug("]");
	return(0);

}
/*******************************************************************************/

static char *rollingfile_make_base_name(const char *logdir, const char* prefix){

	int filename_len = 0;
	char* s = NULL;

	filename_len = strlen(logdir) + 1 +
		strlen(prefix) + 1 + 10; /* a margin */

	s = (char *)malloc(filename_len);      
	sprintf( s, "%s%s%s", logdir,
		FILE_SEP, prefix);

	return(s);
}

/****************************************************************************/
const log4c_appender_type_t log4c_appender_type_rollingfile = {
	"rollingfile",
	rollingfile_open,
	rollingfile_append,
	rollingfile_close
};


/************** End of appender_type_rollingfile.c *******************************************/

/************** Begin of appender_type_stream.c *******************************************/
///static const char version[] = "$Id$";

/*
* appender_stream.c
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

///#include <log4c/appender.h>
#include <stdio.h>
#include <string.h>

/*******************************************************************************/
static int stream_open(log4c_appender_t* ptrThis)
{
	FILE* fp = (FILE*)log4c_appender_get_udata(ptrThis);

	if (fp)
		return 0;

	if ( (fp = fopen(log4c_appender_get_name(ptrThis), "w+")) == NULL)
		fp = stderr;

	/* unbuffered mode */
	setbuf(fp, NULL);

	log4c_appender_set_udata(ptrThis, fp);
	return 0;
}

/*******************************************************************************/
static int stream_append(log4c_appender_t* ptrThis, 
						 const log4c_logging_event_t* a_event)
{
	FILE* fp = (FILE*)log4c_appender_get_udata(ptrThis);

	return fprintf(fp, "[%s] %s", log4c_appender_get_name(ptrThis),
		a_event->evt_rendered_msg);
}

/*******************************************************************************/
static int stream_close(log4c_appender_t* ptrThis)
{
	FILE* fp = (FILE*)log4c_appender_get_udata(ptrThis);


	if (!fp || fp == stdout || fp == stderr)
		return 0;

	return fclose(fp);
}

/*******************************************************************************/
const log4c_appender_type_t log4c_appender_type_stream = {
	"stream",
	stream_open,
	stream_append,
	stream_close,
};


/************** End of appender_type_stream.c *******************************************/

/************** Begin of log4c/appender_type_stream2.h *******************************************/

/* 
*
* appender_type_stream.h
* 
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef log4c_appender_type_stream2_h
#define log4c_appender_type_stream2_h

/**
* @file appender_type_stream2.h
*
* @brief Log4c stream2 appender interface.
*
* The stream2 appender uses a file handle @c FILE* for logging.
* It can be used with @c stdout, @c stderr or a normal file.
* It is pretty primitive as it does not do file rotation, or have a maximum
* configurable file size etc. It improves on the stream appender in a few
* ways that make it a better starting point for new stream based appenders.
*
* It enhances the stream appender by allowing
* the default file pointer to be used in buffered or unbuffered mode.
* Also when you set the file pointer stream2 will not attempt to close
* it on exit which avoids it fighting with the owner of the file pointer.
* stream2 is configured via setter functions--the udata is
* not exposed directly.  This means that new options (eg. configure the open
* mode ) could be added to stream2 while maintaining backward compatability.
*
* The appender can be used with default values, for example as follows:
*
* @code
* log4c_appender_t* myappender;
*
* myappender = log4c_appender_get("/var/logs/mylog.log");
* log4c_appender_set_type(myappender,log4c_appender_type_get("stream2"));
*
* @endcode
*
* In ptrThis case the appender will  be configured automatically with default 
* values: 
* @li the filename is the same as the name of the appender,
* @c "/var/logs/mymlog.log"
* @li the file is opened in "w+" mode
* @li the default system buffer is used (cf; @c setbuf() ) in buffered mode
*
* The stream2 appender can be configured by passing it a file pointer
* to use.  In ptrThis case you manage the file pointer yourself--open,
* option setting, closing.  If you set the file pointer log4c will
* not close the file on exiting--you must do ptrThis:
* 
* @code
* log4c_appender_t* myappender;
* FILE * fp = fopen("myfile.log", "w");
*
* myappender = log4c_appender_get("myappender");
* log4c_appender_set_type(myappender, log4c_appender_type_get("stream2"));
* log4c_stream2_set_fp(stream2_appender,myfp);
*
* @endcode
*
* The default file pointer can be configured to use unbuffered mode.
* Buffered mode is typically 25%-50% faster than unbuffered mode but
* unbuffered mode is useful if your preference is for a more synchronized 
* log file:
*
* @code log4c_appender_t* myappender;
*
* myappender = log4c_appender_get("/var/logs/mylog.log");
* log4c_appender_set_type(myappender,log4c_appender_type_get("stream2"));
* log4c_stream2_set_flags(myappender, LOG4C_STREAM2_UNBUFFERED);
*
* @endcode
*
**/

///#include <log4c/defs.h>
///#include <log4c/appender.h>

__LOG4C_BEGIN_DECLS

/**
* Stream2 appender type definition.
*
* This should be used as a parameter to the log4c_appender_set_type()
* routine to set the type of the appender.
*
**/
LOG4C_API const log4c_appender_type_t log4c_appender_type_stream2;

/**
* Set the file pointer for ptrThis appender.
* @param ptrThis a pointer to the appender
* @param fp the file pointer ptrThis appender will use.  The caller is
* responsible for managing the file pointer (open, option setting, closing).
*/      
LOG4C_API void log4c_stream2_set_fp(log4c_appender_t* a_this, FILE *fp);

/**
* Get the file pointer for ptrThis appender.
* @param ptrThis a pointer to the appender
* @return the file pointer for ptrThis appender.  If there's a problem
* returns NULL.
* 
*/ 
LOG4C_API FILE * log4c_stream2_get_fp(log4c_appender_t* a_this);


/**
* Set the flags for ptrThis appender.
* @param ptrThis a pointer to the appender
* @param flags ar teh flags to set. These will overwrite the existing flags.
* Currently supported flags:  LOG4C_STREAM2_UNBUFFERED
* 
*/
LOG4C_API void log4c_stream2_set_flags(log4c_appender_t* a_this, int flags);
#define LOG4C_STREAM2_UNBUFFERED 0x01

/**
* Get the flags for ptrThis appender.
* @param ptrThis a pointer to the appender
* @return the flags for ptrThis appender. returns -1 if there was a problem.
*/
LOG4C_API int log4c_stream2_get_flags(log4c_appender_t* a_this);

__LOG4C_END_DECLS

#endif

/************** End of log4c/appender_type_stream2.h *******************************************/

/************** Begin of appender_type_stream2.c *******************************************/
///static const char version[] = "$Id$";

/*
* appender_stream2.c
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/
#include <stdio.h>
#include <string.h>

///#include <sd/malloc.h>

///#include <log4c/appender.h>
///#include <log4c/appender_type_stream2.h>

typedef struct stream2_udata {
	FILE * s2u_fp;
	int  s2u_flags;
#define STREAM2_MY_FP 0x01
	int s2u_state;
} log4c_stream2_udata_t;

/* xxx would be nice to run-time check the type here */
#define stream2_get_udata(ptrThis) \
	(log4c_stream2_udata_t *)log4c_appender_get_udata(ptrThis)

/*******************************************************************************/
static log4c_stream2_udata_t* stream2_make_udata(void);
static void stream2_free_udata(log4c_stream2_udata_t* s2up);
static log4c_stream2_udata_t * stream2_get_or_make_udata(log4c_appender_t* ptrThis);
static int stream2_init(log4c_appender_t* ptrThis);

/*******************************************************************************/
static int stream2_init(log4c_appender_t* ptrThis){
	log4c_stream2_udata_t *s2up = stream2_make_udata();

	log4c_appender_set_udata(ptrThis, s2up);

	return(0);
}

/*******************************************************************************/
static int stream2_open(log4c_appender_t* ptrThis)
{
	log4c_stream2_udata_t *s2up = NULL;
	FILE * fp = NULL;
	int flags = 0;    

	if ( !ptrThis){
		return(-1);
	}
	s2up = stream2_get_or_make_udata(ptrThis);
	//s2up = stream2_get_udata(ptrThis);

	fp = s2up->s2u_fp;
	flags = s2up->s2u_flags;    

	if ( !fp ) {
		if ( (fp = fopen(log4c_appender_get_name(ptrThis), "w+")) == NULL){
			fp = stderr;
		} else {
			s2up->s2u_state |= STREAM2_MY_FP;
		}
		s2up->s2u_fp = fp;
	}    

	if ( flags &  LOG4C_STREAM2_UNBUFFERED){/* unbuffered mode by default */
		setbuf(fp, NULL);
	}  

	return 0;
}

/*******************************************************************************/
static int stream2_append(log4c_appender_t* ptrThis, 
						  const log4c_logging_event_t* a_event)
{
	log4c_stream2_udata_t *s2up = (log4c_stream2_udata_t *)log4c_appender_get_udata(ptrThis);

	if ( !s2up ) {
		return(-1);
	}      

	return fprintf(s2up->s2u_fp, "[%s] %s", log4c_appender_get_name(ptrThis),
		a_event->evt_rendered_msg);
}

/*******************************************************************************/
static int stream2_close(log4c_appender_t* ptrThis)
{
	log4c_stream2_udata_t *s2up = (log4c_stream2_udata_t *)log4c_appender_get_udata(ptrThis);
	int rc = -1;

	if ( !ptrThis){
		return rc;
	}
	s2up = stream2_get_udata(ptrThis);
	if ( !s2up){
		return(rc);
	}  

	if ( s2up->s2u_fp && (s2up->s2u_state & STREAM2_MY_FP) ){
		rc = fclose(s2up->s2u_fp);
	} else {
		rc = 0;
	}
	/* Free up and reset any data associated with ptrThis stream2 appender */
	stream2_free_udata(s2up);
	log4c_appender_set_udata(ptrThis, NULL);	

	return (rc);
}

/*******************************************************************************/

static log4c_stream2_udata_t* stream2_make_udata(){

	log4c_stream2_udata_t* s2up = 
		(log4c_stream2_udata_t*) sd_calloc(1, sizeof(log4c_stream2_udata_t));
	return(s2up);
}

/*******************************************************************************/

static void stream2_free_udata(log4c_stream2_udata_t* s2up){

	free(s2up);
}

/*******************************************************************************/

static log4c_stream2_udata_t * stream2_get_or_make_udata(log4c_appender_t* ptrThis){
	log4c_stream2_udata_t *s2up;
	int rc = 0;

	s2up = (log4c_stream2_udata_t *)log4c_appender_get_udata(ptrThis);

	if ( !s2up) {
		rc = stream2_init(ptrThis);
	}

	return(stream2_get_udata(ptrThis));
}

/*******************************************************************************/
extern void log4c_stream2_set_fp(log4c_appender_t* ptrThis, FILE *fp){
	log4c_stream2_udata_t *s2up;

	if ( !ptrThis){
		return;
	}
	s2up = stream2_get_or_make_udata(ptrThis);

	s2up->s2u_fp = fp;    
	s2up->s2u_state &= !(STREAM2_MY_FP);
}
/*******************************************************************************/
extern FILE* log4c_stream2_get_fp(log4c_appender_t* ptrThis){
	log4c_stream2_udata_t *s2up;

	if ( !ptrThis){
		return NULL;
	}
	s2up = stream2_get_udata(ptrThis);
	if ( s2up){
		return s2up->s2u_fp;
	} else {
		return NULL;
	}
}
/*******************************************************************************/
extern int log4c_stream2_get_flags(log4c_appender_t* ptrThis){
	log4c_stream2_udata_t *s2up;

	if ( !ptrThis){
		return -1;
	}
	s2up = stream2_get_udata(ptrThis);
	if ( s2up){
		return s2up->s2u_flags;
	} else {
		return -1;
	}
}
/*******************************************************************************/
extern void log4c_stream2_set_flags(log4c_appender_t* ptrThis, int flags){
	log4c_stream2_udata_t *s2up;

	if ( !ptrThis){
		return;
	}
	s2up = stream2_get_or_make_udata(ptrThis);
	if ( !s2up){
		return;
	}
	s2up->s2u_flags = flags;    
}

/*******************************************************************************/
const log4c_appender_type_t log4c_appender_type_stream2 = {
	"stream2",
	stream2_open,
	stream2_append,
	stream2_close,
};


/************** End of appender_type_stream2.c *******************************************/


/************** Begin of appender_type_syslog.c *******************************************/
///static const char version[] = "$Id$";

/*
* appender_syslog.c
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifdef HAVE_CONFIG_H
///#include <config.h>
#endif

///#include <log4c/appender.h>
///#include <log4c/priority.h>

#ifdef HAVE_SYSLOG_H
#include <syslog.h>

/*******************************************************************************/
static int log4c_to_syslog_priority(int a_priority)
{
	static int priorities[] = {
		LOG_EMERG,	
		LOG_ALERT,	
		LOG_CRIT, 
		LOG_ERR,	
		LOG_WARNING,	
		LOG_NOTICE, 
		LOG_INFO, 	
		LOG_DEBUG 
	};
	int result;

	a_priority++;
	a_priority /= 100;

	if (a_priority < 0) {
		result = LOG_EMERG;
	} else if (a_priority > 7) {
		result = LOG_DEBUG;
	} else {
		result = priorities[a_priority];
	}

	return result;
}

/*******************************************************************************/
static int syslog_open(log4c_appender_t* ptrThis)
{
	openlog(log4c_appender_get_name(ptrThis), LOG_PID, LOG_USER); 
	return 0;
}

/*******************************************************************************/
static int syslog_append(log4c_appender_t*	ptrThis, 
						 const log4c_logging_event_t* a_event)
{

	syslog(log4c_to_syslog_priority(a_event->evt_priority) | LOG_USER, 
		a_event->evt_rendered_msg); 
	return 0;
}

/*******************************************************************************/
static int syslog_close(log4c_appender_t*	ptrThis)
{
	closelog();
	return 0;
}

#else

/*******************************************************************************/
static int syslog_open(log4c_appender_t* ptrThis)
{
	return 0;
}

/*******************************************************************************/
static int syslog_append(log4c_appender_t*	ptrThis, 
						 const log4c_logging_event_t* a_event)
{
	return 0;
}

/*******************************************************************************/
static int syslog_close(log4c_appender_t*	ptrThis)
{
	return 0;
}
#endif


/*******************************************************************************/
const log4c_appender_type_t log4c_appender_type_syslog = {
	"syslog",
	syslog_open,
	syslog_append,
	syslog_close,
};

/************** End of appender_type_syslog.c *******************************************/

/************** Begin of sd/sprintf.h *******************************************/
/* $Id$
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef __sd_sprintf_h
#define __sd_sprintf_h

/**
* @file sprintf.h
*
* @brief Formatted output conversion
*
* These functions write the output under the control of a format
* string that specifies how subsequent arguments (or arguments
* accessed via the variable-length argument facilities of stdarg(2))
* are converted for output.
*
* They do not write more than \a size bytes, including the trailing
* \c '\0'.
*
* These functions return the number of characters printed (not
* including the trailing \c `\0' used to end output to strings). They
* return -1 if the output was truncated due to the @a size limit.
*
*/

#include <stdarg.h>
#include <stddef.h>
///#include <sd/defs.h>

__SD_BEGIN_DECLS

/**
* Same as fprintf(3) with auto-allocation of the resulting buffer,
* and output directly in a file, not a stream.
*/
extern int sd_fprintf(int fd, const char *fmt, ...);

/**
* Same as sprintf(3) with auto-allocation of the resulting buffer.
*/
extern char* sd_sprintf(const char* a_fmt, ...);

/**
* Same as vsprintf(3) with auto-allocation of the resulting buffer.
*/
extern char* sd_vsprintf(const char* a_fmt, va_list a_arg);

#if defined(__osf__)
extern int snprintf(char* str, size_t size, const char* fmt, ...);
extern int vsnprintf(char* str, size_t size, const char* fmt, va_list arg);
#endif

__SD_END_DECLS

#endif


/************** End of sd/sprintf.h *******************************************/

/************** Begin of category.c *******************************************/
///static const char version[] = "$Id$";

/*
* category.c
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/
#ifdef HAVE_CONFIG_H
///#include "config.h"
#endif

#include <stdlib.h>
#include <string.h>
#ifdef  HAVE_ALLOCA_H
#include <alloca.h>
#endif
///#include <sd/sprintf.h>
///#include <sd/malloc.h>
///#include <sd/factory.h>
///#include <log4c/appender.h>
///#include <log4c/priority.h>
///#include <log4c/logging_event.h>
///#include <log4c/category.h>
///#include <log4c/rc.h>
///#include <sd/error.h>
///#include <sd/sd_xplatform.h>

struct __log4c_category {
	char*			cat_name;
	int				cat_priority;
	int				cat_additive;
	const log4c_category_t*	cat_parent;
	log4c_appender_t*		cat_appender;
};

sd_factory_t* log4c_category_factory = NULL;

static const char LOG4C_CATEGORY_DEFAULT[] = "root";


/**
* @bug the root category name should be "" not "root". *
*/

/*******************************************************************************/
extern log4c_category_t* log4c_category_get(const char* a_name)
{
	static const sd_factory_ops_t log4c_category_factory_ops = {
		/*(void*) log4c_category_new,
		(void*) log4c_category_delete,
		(void*) log4c_category_print,*/
		(void *( *)(const char *))log4c_category_new,
		(void ( *)(void *))log4c_category_delete,
		(void ( *)(void *,FILE *))log4c_category_print
	};

	if (!log4c_category_factory) {
		log4c_category_factory = sd_factory_new("log4c_category_factory",
			&log4c_category_factory_ops);
	}

	return (log4c_category_t *)sd_factory_get(log4c_category_factory, a_name);
}

/*******************************************************************************/
extern int log4c_category_list(log4c_category_t** a_cats, int a_ncats)
{
	return sd_factory_list(log4c_category_factory, (void**) a_cats, a_ncats);
}

/*******************************************************************************/
static const char* dot_dirname(char* a_string);

extern log4c_category_t* log4c_category_new(const char* a_name)
{
	log4c_category_t* ptrThis;

	if (!a_name)
		return NULL;

	ptrThis		= (log4c_category_t *)sd_calloc(1, sizeof(log4c_category_t));
	ptrThis->cat_name	= sd_strdup(a_name);
	ptrThis->cat_priority	= LOG4C_PRIORITY_NOTSET;
	ptrThis->cat_additive	= 1;
	ptrThis->cat_appender	= NULL;
	ptrThis->cat_parent	= NULL;

	/* skip root category because it has a NULL parent */
	if (strcmp(LOG4C_CATEGORY_DEFAULT, a_name)) {
		char* tmp = sd_strdup(ptrThis->cat_name);

		ptrThis->cat_parent = log4c_category_get(dot_dirname(tmp));
		free(tmp);
	}
	return ptrThis;
}

/*******************************************************************************/
extern void log4c_category_delete(log4c_category_t* ptrThis)
{
	if (!ptrThis) 
		return;

	free(ptrThis->cat_name);
	free(ptrThis);
}

/*******************************************************************************/
extern const char* log4c_category_get_name(const log4c_category_t* ptrThis)
{
	return (ptrThis ? ptrThis->cat_name : "(nil)");
}

/*******************************************************************************/
extern int log4c_category_get_priority(const log4c_category_t* ptrThis)
{
	return (ptrThis ? ptrThis->cat_priority : LOG4C_PRIORITY_UNKNOWN);
}

/*******************************************************************************/
extern int log4c_category_get_chainedpriority(const log4c_category_t* ptrThis)
{
	const log4c_category_t* cat = ptrThis;

	if (!ptrThis) 
		return LOG4C_PRIORITY_UNKNOWN;

	while (cat->cat_priority == LOG4C_PRIORITY_NOTSET && cat->cat_parent)
		cat = cat->cat_parent;

	return cat->cat_priority;
}

/*******************************************************************************/
extern const log4c_appender_t* log4c_category_get_appender(const log4c_category_t* ptrThis)
{
	return (ptrThis ? ptrThis->cat_appender : NULL);
}

/*******************************************************************************/
extern int log4c_category_get_additivity(const log4c_category_t* ptrThis)
{
	return (ptrThis ? ptrThis->cat_additive : -1);
}

/*******************************************************************************/
extern int log4c_category_set_priority(log4c_category_t* ptrThis, int a_priority)
{
	int previous;

	if (!ptrThis) 
		return LOG4C_PRIORITY_UNKNOWN;

	previous = ptrThis->cat_priority;
	ptrThis->cat_priority = a_priority;
	return previous;
}

/**
* @todo need multiple appenders per category
*/

/*******************************************************************************/
extern const log4c_appender_t* log4c_category_set_appender(
	log4c_category_t* ptrThis, 
	log4c_appender_t* a_appender)
{
	log4c_appender_t* previous;

	if (!ptrThis) 
		return NULL;

	previous = ptrThis->cat_appender;
	ptrThis->cat_appender = a_appender;
	return previous;
}

/*******************************************************************************/
extern int log4c_category_set_additivity(log4c_category_t* ptrThis, int a_additivity)
{
	int previous;

	if (!ptrThis) 
		return -1;

	previous = ptrThis->cat_additive;
	ptrThis->cat_additive = a_additivity;
	return previous;
}

/*******************************************************************************/
extern void log4c_category_print(const log4c_category_t* ptrThis, FILE* a_stream)
{
	if (!ptrThis) 
		return;

	fprintf(a_stream, "{ name:'%s' priority:%s additive:%d appender:'%s' parent:'%s' }",
		ptrThis->cat_name,
		log4c_priority_to_string(ptrThis->cat_priority),
		ptrThis->cat_additive,
		log4c_appender_get_name(ptrThis->cat_appender),
		log4c_category_get_name(ptrThis->cat_parent)
		);
}

/*******************************************************************************/
extern void __log4c_category_vlog(const log4c_category_t* ptrThis, 
								  const log4c_location_info_t* a_locinfo, 
								  int a_priority,
								  const char* a_format, 
								  va_list a_args)
{
	char* message;
	log4c_logging_event_t evt;
	const log4c_category_t* cat;
	int yes = 0;

	if (!ptrThis)
		return;

	/* check if an appender is defined in the category hierarchy */
	for (cat = ptrThis; cat; cat = cat->cat_parent) {
		if (cat->cat_appender)
			yes++;
	}

	if (!yes)
		return;

	log4c_reread();

	/* when there is no limit on the buffer size, we use malloc() to
	* give the user the possiblity to reallocate if necessary. When
	* the buffer is limited in size, we use alloca() for more
	* efficiency.
	*/
	evt.evt_buffer.buf_maxsize = log4c_rc->config.bufsize;

	if (!evt.evt_buffer.buf_maxsize) {
		evt.evt_buffer.buf_size = LOG4C_BUFFER_SIZE_DEFAULT;
		evt.evt_buffer.buf_data = (char*)sd_malloc(evt.evt_buffer.buf_size);
		message = sd_vsprintf(a_format, a_args);
	}
	else {
		size_t n;

		evt.evt_buffer.buf_size = evt.evt_buffer.buf_maxsize;
		evt.evt_buffer.buf_data = (char*)alloca(evt.evt_buffer.buf_size);
		message = (char*)alloca(evt.evt_buffer.buf_size);

		if ( (n = (size_t)vsnprintf(message, evt.evt_buffer.buf_size, a_format, a_args))
			>= evt.evt_buffer.buf_size)
			sd_error("truncating message of %d bytes (bufsize = %d)", n, 
			evt.evt_buffer.buf_size);
	}

	evt.evt_category	= ptrThis->cat_name;
	evt.evt_priority	= a_priority;
	evt.evt_msg	        = message;
	evt.evt_loc	        = a_locinfo;
	SD_GETTIMEOFDAY(&evt.evt_timestamp, NULL);

	for (cat = ptrThis; cat; cat = cat->cat_parent) {
		if (cat->cat_appender)
			log4c_appender_append(cat->cat_appender, &evt);

		if (!cat->cat_additive) break;	
	}

	if (!evt.evt_buffer.buf_maxsize) {
		free(message);
		free(evt.evt_buffer.buf_data);
	}
}


/*******************************************************************************/
extern void __log4c_category_vlog_no_file_num_no_layout(
	const log4c_category_t* ptrThis, 
	const log4c_location_info_t* a_locinfo, 
	int a_priority,
	const char* a_format, 
	va_list a_args)
{
	char* message;
	log4c_logging_event_t evt;
	const log4c_category_t* cat;
	int yes = 0;

	if (!ptrThis)
		return;

	/* check if an appender is defined in the category hierarchy */
	for (cat = ptrThis; cat; cat = cat->cat_parent) {
		if (cat->cat_appender)
			yes++;
	}

	if (!yes)
		return;

	log4c_reread();

	/* when there is no limit on the buffer size, we use malloc() to
	* give the user the possiblity to reallocate if necessary. When
	* the buffer is limited in size, we use alloca() for more
	* efficiency.
	*/
	evt.evt_buffer.buf_maxsize = log4c_rc->config.bufsize;

	if (!evt.evt_buffer.buf_maxsize) {
		evt.evt_buffer.buf_size = LOG4C_BUFFER_SIZE_DEFAULT;
		evt.evt_buffer.buf_data = (char*)sd_malloc(evt.evt_buffer.buf_size);
		message = sd_vsprintf(a_format, a_args);
	}
	else {
		size_t n;

		evt.evt_buffer.buf_size = evt.evt_buffer.buf_maxsize;
		evt.evt_buffer.buf_data = (char*)alloca(evt.evt_buffer.buf_size);
		message = (char*)alloca(evt.evt_buffer.buf_size);

		if ( (n = (size_t)vsnprintf(message, evt.evt_buffer.buf_size, a_format, a_args))
			>= evt.evt_buffer.buf_size)
			sd_error("truncating message of %d bytes (bufsize = %d)", n, 
			evt.evt_buffer.buf_size);
	}

	evt.evt_category	= ptrThis->cat_name;
	evt.evt_priority	= a_priority;
	evt.evt_msg	        = message;
	evt.evt_loc	        = a_locinfo;
	SD_GETTIMEOFDAY(&evt.evt_timestamp, NULL);

	for (cat = ptrThis; cat; cat = cat->cat_parent) {
		if (cat->cat_appender)
			log4c_appender_append_no_file_num_no_layout(cat->cat_appender, &evt);

		if (!cat->cat_additive) break;	
	}

	if (!evt.evt_buffer.buf_maxsize) {
		free(message);
		free(evt.evt_buffer.buf_data);
	}
}

/*******************************************************************************/
static const char* dot_dirname(char* a_string)
{
	char* p;

	if (!a_string)
		return NULL;

	if ( (p = strrchr(a_string, '.')) == NULL)
		return LOG4C_CATEGORY_DEFAULT;

	*p = '\0';
	return a_string;
}



/************** End of category.c *******************************************/

/************** Begin of sd/list.h *******************************************/
	/* $Id$
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	* 
	* See the COPYING file for the terms of usage and distribution.
	*/

#ifndef __sd_list_h
#define __sd_list_h

	/**
	* @file list.h @ingroup sd
	*
	* @brief Generic list object. It is implemented as an array of doubly-linked
	* lists of iterators. The index within the array is computed by a efficient
	* list function.
	*/

#include <stddef.h>
///#include <sd/defs.h>

	__SD_BEGIN_DECLS

		/**
		* This is the list object.
		*/
		typedef struct __sd_list sd_list_t;

	struct __sd_list_iter {
		void*			data;
		struct __sd_list*		list;
		struct __sd_list_iter*	__next;
		struct __sd_list_iter*	__prev;
		int				__foreach;
	};

	/**
	* This is the elementary container for storing data into the list object.
	*/
	typedef struct __sd_list_iter sd_list_iter_t;

	/**
	* Signature of a "foreach" function.
	*/
	typedef unsigned int (*sd_list_func_t)(void* a_data, void* a_userdata);

	/**
	* Creates a list.
	* @param a_capacity initial number of preallocated iterators
	* @return the list object.
	*/
	extern sd_list_t* sd_list_new(size_t a_capacity);

	/**
	* Destroys the list object.
	* @todo need a function parameter to destroy list elements.
	*/
	extern void sd_list_delete(sd_list_t* a_this);

	/**
	* Adds the given_data at the head of the list.
	*/
	extern sd_list_iter_t* sd_list_prepend(sd_list_t* a_this, void* a_data);

	/**
	* Adds the given data at the tail of the list.
	*/
	extern sd_list_iter_t* sd_list_append(sd_list_t* a_this, void* a_data);

	/**
	* Looks for the iterator associated to the given data in the list object.
	* @param a_data the data to find
	* @return a pointer to the found iterator or NULL.
	*/
	extern sd_list_iter_t* sd_list_lookup(sd_list_t* a_this, void* a_data);

	/**
	* Looks for the iterator associated to the given data in the list object and
	* creates it if doesn't exist, using @c sd_list_add().
	* @param a_data the data to find/add
	* @return a pointer to the found iterator or NULL.
	*/
	extern sd_list_iter_t* sd_list_lookadd(sd_list_t* a_this, void* a_data);

	/**
	* Adds the given data into the list object. If the data already exists,
	* the associated iterator is returned.
	* @warning the element is added at the begining of the list.
	* @param a_data the data to add
	* @return a pointer to the created or found iterator.
	*/
	extern sd_list_iter_t* sd_list_add(sd_list_t* a_this, void* a_data);

	/**
	* Applies the given function to all list elements, starting from the
	* first one. As soon as the function returns a non-null value, the
	* given data is inserted in the list (before the element).
	* @param a_func the "sort" function.
	* @param a_data the data to add
	* @return a pointer to the created iterator.
	*/
	extern sd_list_iter_t* sd_list_sortadd(sd_list_t* a_this,
		sd_list_func_t a_func,
		void* a_data);

	/**
	* Removes an iterator from the list object.
	* @param a_data the data associated to the iterator.
	*/
	extern int sd_list_del(sd_list_t* a_this, void* a_data);

	/**
	* clears the list object.
	*/
	extern void sd_list_clear(sd_list_t* a_this);

	/**
	* Calls \a a_func for each element of the list object, as long as \a a_func
	* returns 0.
	* @param a_func the "foreach" function.
	* @param a_data the user data passed to \a a_func.
	*/
	extern void sd_list_foreach(sd_list_t* a_this, sd_list_func_t a_func,
		void* a_userdata);

	/**
	* Calls \a a_func for each element of the list object, as long as \a a_func
	* returns 0.
	* Same as sd_list_foreach but from tail to head of list.
	* @param a_func the "foreach" function.
	* @param a_data the user data passed to \a a_func.
	*/
	extern void sd_list_rforeach(sd_list_t* a_this, sd_list_func_t a_func,
		void* a_userdata);

	/**
	* Gets the number of iterators.
	*/
	extern size_t sd_list_get_nelem(sd_list_t* a_this);

	/**
	* Gets the iterator pointing to the first element of the list.
	*/
	extern sd_list_iter_t* sd_list_begin(sd_list_t* a_this);

	/**
	* Gets the past-the-last-element iterator of the list.
	*/
	extern sd_list_iter_t* sd_list_end(sd_list_t* a_this);

	/**
	* Gets the iterator pointing to the last element of the list.
	*/
	extern sd_list_iter_t* sd_list_rbegin(sd_list_t* a_this);

	/**
	* Gets the before-the-first-element iterator of the list.
	*/
	extern sd_list_iter_t* sd_list_rend(sd_list_t* a_this);

	/**
	* Gets a pointer to the next iterator.
	*/
	extern sd_list_iter_t* sd_list_iter_next(sd_list_iter_t* a_this);

	/**
	* Gets a pointer to the previous iterator.
	*/
	extern sd_list_iter_t* sd_list_iter_prev(sd_list_iter_t* a_this);

	/**
	* Deletes the iterator from the list.
	*/
	extern void sd_list_iter_del(sd_list_iter_t* a_this);

	/**
	* Deletes the iterator from the list.
	*/
	extern void sd_list_iter_del(sd_list_iter_t* a_this);

	/**
	* Creates a new iterator and inserts it before @a a_this.
	* @param a_data the data associated to the iterator.
	*/
	extern sd_list_iter_t* sd_list_iter_insert(sd_list_iter_t* a_this,
		void* a_data);

	__SD_END_DECLS

#endif


		/************** End of sd/list.h *******************************************/
/************** Begin of domnode.h *******************************************/
/* $Id$
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef __sd_domnode_h
#define __sd_domnode_h

/**
* @file domnode.h @ingroup sd
*
* @brief Generic DOM object.
*/

#include <stdio.h>
///#include <sd/list.h>

__SD_BEGIN_DECLS

typedef struct {
	const char*	name;
	const char*	value;
	sd_list_t*	children;
	sd_list_t*	attrs;
} sd_domnode_t;

extern sd_domnode_t*	sd_domnode_new(const char* a_name,
									   const char* a_value);

extern void		sd_domnode_delete(sd_domnode_t* ptrThis);

extern int		sd_domnode_read(sd_domnode_t* ptrThis,
								const char* a_buffer, size_t asize);
extern int		sd_domnode_write(sd_domnode_t* ptrThis, char** a_buffer,
								 size_t* asize);

extern int		sd_domnode_fread(sd_domnode_t* ptrThis, FILE* a_stream);
extern int		sd_domnode_fwrite(const sd_domnode_t* ptrThis,
								  FILE* a_stream);

extern int		sd_domnode_load(sd_domnode_t* ptrThis,
								const char* a_filename);

extern int		sd_domnode_store(const sd_domnode_t* ptrThis, 
								 const char* a_filename);

extern sd_domnode_t*	sd_domnode_search(const sd_domnode_t* ptrThis,
										  const char* a_name);

extern sd_domnode_t* 	sd_domnode_attrs_put(sd_domnode_t* ptrThis,
											 sd_domnode_t* a_attr);
extern sd_domnode_t*	sd_domnode_attrs_get(const sd_domnode_t* ptrThis,
											 const char* a_name);
extern sd_domnode_t*	sd_domnode_attrs_remove(sd_domnode_t* ptrThis,
												const char* a_name);

/** Creates a new node. */
extern sd_domnode_t* __sd_domnode_new(const char* name, const char* a_value,
									  int is_elem);

__SD_END_DECLS

#endif



/************** End of domnode.h *******************************************/

/************** Begin of sd/stack.h *******************************************/
/* $Id$
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef __sd_stack_h
#define __sd_stack_h

/**
* @file stack.h @ingroup sd
*
* @brief Generic stack object.
*
* @todo documentation
* @todo API homogeneity with sd_list and sd_hash
*/

#include <stddef.h>
///#include <sd/defs.h>

__SD_BEGIN_DECLS

typedef struct __sd_stack sd_stack_t;

extern sd_stack_t* sd_stack_new(size_t max);
extern void	sd_stack_delete(sd_stack_t* astack, void (*free_data_fn)(void *));
extern size_t	sd_stack_get_nelem(const sd_stack_t* astack);

extern void	sd_stack_clear(sd_stack_t* astack, void (*free_data_fn)(void *));
extern int	sd_stack_push(sd_stack_t* astack, void *data);
extern void*	sd_stack_pop(sd_stack_t* astack);
extern void*	sd_stack_begin(sd_stack_t* astack);
extern void*	sd_stack_next(sd_stack_t* astack);
extern void*	sd_stack_end(sd_stack_t* astack);
extern void*	sd_stack_peek(sd_stack_t* astack);

__SD_END_DECLS

#endif


/************** End of sd/stack.h *******************************************/

/************** Begin of domnode-xml.h *******************************************/
/* $Id$
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
* See the COPYING file for the terms of usage and distribution.
*/

#ifndef __sd_domnode_xml_h
#define __sd_domnode_xml_h

/**
* @file domnode-xml.h @ingroup sd
*
* @brief Private API for XML parsing.
*/

///#include "domnode.h"
///#include "stack.h"

struct __sd_domnode_xml_maker {
	void*		scanner;
	sd_stack_t*		elements;
	sd_domnode_t*	root;
};

extern int __sd_domnode_xml_fread(sd_domnode_t** a_node, FILE* a_stream);
extern int __sd_domnode_xml_fwrite(const sd_domnode_t* a_node, FILE* a_stream);

extern int __sd_domnode_xml_read(sd_domnode_t** a_node, const char* a_buffer,
								 size_t a_size);
extern int __sd_domnode_xml_write(const sd_domnode_t* a_node, char** a_buffer,
								  size_t* a_size);

#endif


/************** End of domnode-xml.h *******************************************/

/************** Begin of domnode-xml-parser.h *******************************************/
#ifndef BISON_DOMNODE_XML_PARSER_H
# define BISON_DOMNODE_XML_PARSER_H

#ifndef YYSTYPE
typedef union { char *s; } yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	ENDDEF	257
# define	EQ	258
# define	SLASH	259
# define	CLOSE	260
# define	END	261
# define	NAME	262
# define	VALUE	263
# define	DATA	264
# define	COMMENT	265
# define	START	266


#endif /* not BISON_DOMNODE_XML_PARSER_H */


/************** End of domnode-xml-parser.h *******************************************/

#define YY_HEADER_NO_UNDEFS 1
/************** Begin of domnode-xml-scanner.h *******************************************/
#ifndef __sd_domnode_xml_HEADER_H
#define __sd_domnode_xml_HEADER_H 1
#define __sd_domnode_xml_IN_HEADER 1

#define YY_REENTRANT 1
#define YY_BISON_BRIDGE 1
#ifndef YY_REENTRANT
#define yytext __sd_domnode_xml_text
#define yyleng __sd_domnode_xml_leng
#define yyin __sd_domnode_xml_in
#define yyout __sd_domnode_xml_out
#define yy_flex_debug __sd_domnode_xml__flex_debug
#endif
#define yy_create_buffer __sd_domnode_xml__create_buffer
#define yy_delete_buffer __sd_domnode_xml__delete_buffer
#define yy_scan_buffer __sd_domnode_xml__scan_buffer
#define yy_scan_string __sd_domnode_xml__scan_string
#define yy_scan_bytes __sd_domnode_xml__scan_bytes
#define yy_init_buffer __sd_domnode_xml__init_buffer
#define yy_flush_buffer __sd_domnode_xml__flush_buffer
#define yy_load_buffer_state __sd_domnode_xml__load_buffer_state
#define yy_switch_to_buffer __sd_domnode_xml__switch_to_buffer
#define yylex __sd_domnode_xml_lex
#define yyrestart __sd_domnode_xml_restart
#define yylex_init __sd_domnode_xml_lex_init
#define yylex_destroy __sd_domnode_xml_lex_destroy
#define yyget_debug __sd_domnode_xml_get_debug
#define yyset_debug __sd_domnode_xml_set_debug
#define yyget_extra __sd_domnode_xml_get_extra
#define yyset_extra __sd_domnode_xml_set_extra
#define yyget_in __sd_domnode_xml_get_in
#define yyset_in __sd_domnode_xml_set_in
#define yyget_out __sd_domnode_xml_get_out
#define yyset_out __sd_domnode_xml_set_out
#define yyget_leng __sd_domnode_xml_get_leng
#define yyget_text __sd_domnode_xml_get_text
#define yyget_lineno __sd_domnode_xml_get_lineno
#define yyset_lineno __sd_domnode_xml_set_lineno
#ifdef YY_BISON_BRIDGE
#define yyget_lval __sd_domnode_xml_get_lval
#define yyset_lval __sd_domnode_xml_set_lval
#define yyget_lloc __sd_domnode_xml_get_lloc
#define yyset_lloc __sd_domnode_xml_set_lloc
#endif
#define yyalloc __sd_domnode_xml_alloc
#define yyrealloc __sd_domnode_xml_realloc
#define yyfree __sd_domnode_xml_free

///#line 50 "domnode-xml-scanner.h"
#define  YY_INT_ALIGNED short int


/* A lexical scanner generated by flex */

#define FLEX_SCANNER
#define YY_FLEX_MAJOR_VERSION 2
#define YY_FLEX_MINOR_VERSION 5
#define YY_FLEX_SUBMINOR_VERSION 27
#if YY_FLEX_SUBMINOR_VERSION > 0
#define FLEX_BETA
#endif

/* First, we deal with  platform-specific or compiler-specific issues. */

/* begin standard C headers. */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

/* end standard C headers. */

///#include <sd/sd_xplatform.h>

/* flex integer type definitions */

#ifndef FLEXINT_H
#define FLEXINT_H

/* C99 systems have <inttypes.h>. Non-C99 systems may or may not. */

#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
typedef int8_t flex_int8_t;
typedef uint8_t flex_uint8_t;
typedef int16_t flex_int16_t;
typedef uint16_t flex_uint16_t;
typedef int32_t flex_int32_t;
typedef uint32_t flex_uint32_t;
#else
typedef signed char flex_int8_t;
typedef short int flex_int16_t;
typedef int flex_int32_t;
typedef unsigned char flex_uint8_t; 
typedef unsigned short int flex_uint16_t;
typedef unsigned int flex_uint32_t;
#endif /* ! C99 */

/* Limits of integral types. */
#ifndef INT8_MIN
#define INT8_MIN               (-128)
#endif
#ifndef INT16_MIN
#define INT16_MIN              (-32767-1)
#endif
#ifndef INT32_MIN
#define INT32_MIN              (-2147483647-1)
#endif
#ifndef INT8_MAX
#define INT8_MAX               (127)
#endif
#ifndef INT16_MAX
#define INT16_MAX              (32767)
#endif
#ifndef INT32_MAX
#define INT32_MAX              (2147483647)
#endif
#ifndef UINT8_MAX
#define UINT8_MAX              (255U)
#endif
#ifndef UINT16_MAX
#define UINT16_MAX             (65535U)
#endif
#ifndef UINT32_MAX
#define UINT32_MAX             (4294967295U)
#endif


#endif /* ! FLEXINT_H */



#ifdef __cplusplus

/* C++ compilers don't understand traditional function definitions. */
#ifdef YY_TRADITIONAL_FUNC_DEFS
#undef YY_TRADITIONAL_FUNC_DEFS
#endif

/* The "const" storage-class-modifier is valid. */
#define YY_USE_CONST

#else	/* ! __cplusplus */

/* We're not in a C++ compiler, so by default,
we generate C99 function defs, unless you explicitly ask
for traditional defs by defining YY_TRADITIONAL_FUNC_DEFS */

#if __STDC__

#define YY_USE_CONST

#endif	/* __STDC__ */
#endif	/* ! __cplusplus */

#ifdef YY_USE_CONST
#define yyconst const
#else
#define yyconst
#endif

/* For compilers that can't handle prototypes.
* e.g.,
* The function prototype
*    int foo(int x, char* y);
*
* ...should be written as
*    int foo YY_PARAMS((int x, char* y));
*
* ...which could possibly generate
*    int foo ();
*/
#ifdef YY_NO_PROTOS
#define YY_PARAMS(proto) ()
#else
#define YY_PARAMS(proto) proto
#endif


/* Returned upon end-of-file. */
#define YY_NULL 0

/* Promotes a possibly negative, possibly signed char to an unsigned
* integer for use as an array index.  If the signed char is negative,
* we want to instead treat it as an 8-bit unsigned char, hence the
* double cast.
*/
#define YY_SC_TO_UI(c) ((unsigned int) (unsigned char) c)


/* An opaque pointer. */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

/* For use wherever a Global is accessed or assigned. */
#define YY_G(var) (((struct yyguts_t*)yyscanner)->var)

/* For use in function prototypes to append the additional argument. */
#define YY_PROTO_LAST_ARG , yyscan_t yyscanner
#define YY_PROTO_ONLY_ARG    yyscan_t yyscanner

/* For use in function definitions to append the additional argument. */
#ifdef YY_TRADITIONAL_FUNC_DEFS
#define YY_DEF_LAST_ARG , yyscanner
#define YY_DEF_ONLY_ARG    yyscanner
#else
#define YY_DEF_LAST_ARG , yyscan_t yyscanner
#define YY_DEF_ONLY_ARG   yyscan_t yyscanner
#endif
#define YY_DECL_LAST_ARG yyscan_t yyscanner;

/* For use in function calls to pass the additional argument. */
#define YY_CALL_LAST_ARG  , yyscanner
#define YY_CALL_ONLY_ARG   yyscanner

/* For convenience, these vars (plus the bison vars far below)
are macros in the reentrant scanner. */
#define yyin YY_G(yyin_r)
#define yyout YY_G(yyout_r)
#define yyextra YY_G(yyextra_r)
#define yyleng YY_G(yyleng_r)
#define yytext YY_G(yytext_r)
#define yylineno YY_G(yylineno_r)
#define yy_flex_debug YY_G(yy_flex_debug_r)

int yylex_init YY_PARAMS((yyscan_t* scanner));



/* For compilers that need traditional function definitions.
* e.g.,
* The function prototype taking 2 arguments
*    int foo (int x, char* y)
*
* ...should be written as
*    int foo YYFARGS2(int,x, char*,y)
*
* ...which could possibly generate
*    int foo (x,y,yyscanner)
*        int x;
*        char * y;
*        yyscan_t yyscanner;
*/
#ifdef YY_TRADITIONAL_FUNC_DEFS
/* Generate traditional function defs */
#define YYFARGS0(v) (YY_DEF_ONLY_ARG) YY_DECL_LAST_ARG
#define YYFARGS1(t1,n1) (n1 YY_DEF_LAST_ARG) t1 n1; YY_DECL_LAST_ARG
#define YYFARGS2(t1,n1,t2,n2) (n1,n2 YY_DEF_LAST_ARG) t1 n1; t2 n2; YY_DECL_LAST_ARG
#define YYFARGS3(t1,n1,t2,n2,t3,n3) (n1,n2,n3 YY_DEF_LAST_ARG) t1 n1; t2 n2; t3 n3; YY_DECL_LAST_ARG
#else
/* Generate C99 function defs. */
#define YYFARGS0(v) (YY_DEF_ONLY_ARG)
#define YYFARGS1(t1,n1) (t1 n1 YY_DEF_LAST_ARG)
#define YYFARGS2(t1,n1,t2,n2) (t1 n1,t2 n2 YY_DEF_LAST_ARG)
#define YYFARGS3(t1,n1,t2,n2,t3,n3) (t1 n1,t2 n2,t3 n3 YY_DEF_LAST_ARG)
#endif

/* Enter a start condition.  This macro really ought to take a parameter,
* but we do it the disgusting crufty way forced on us by the ()-less
* definition of BEGIN.
*/
#define BEGIN YY_G(yy_start) = 1 + 2 *

/* Translate the current start state into a value that can be later handed
* to BEGIN to return to the state.  The YYSTATE alias is for lex
* compatibility.
*/
#define YY_START ((YY_G(yy_start) - 1) / 2)
#define YYSTATE YY_START

/* Action number for EOF rule of a given start state. */
#define YY_STATE_EOF(state) (YY_END_OF_BUFFER + state + 1)

/* Special action meaning "start processing a new file". */
#define YY_NEW_FILE yyrestart( yyin YY_CALL_LAST_ARG )

#define YY_END_OF_BUFFER_CHAR 0

/* Size of default input buffer. */
#ifndef YY_BUF_SIZE
#define YY_BUF_SIZE 16384
#endif


#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif



#define EOB_ACT_CONTINUE_SCAN 0
#define EOB_ACT_END_OF_FILE 1
#define EOB_ACT_LAST_MATCH 2

#ifdef YY_USE_LINENO
/* Note: We specifically omit the test for yy_rule_can_match_eol because it requires
*       access to the local variable yy_act. Since yyless() is a macro, it would break
*       existing scanners that call yyless() from OUTSIDE yylex. 
*       One obvious solution it to make yy_act a global. I tried that, and saw
*       a 5% performance hit in a non-yylineno scanner, because yy_act is
*       normally declared as a register variable-- so it's not worth it.
*/
#define  YY_LESS_LINENO(n) \
	do { \
	int yyl;\
	for ( yyl = n; yyl < yyleng; ++yyl )\
	if ( yytext[yyl] == '\n' )\
	--yylineno;\
	}while(0)
#else
#define YY_LESS_LINENO(n)
#endif

/* The funky do-while in the following #define is used to turn the definition
* int a single C statement (which needs a semi-colon terminator).  This
* avoids problems with code like:
*
* 	if ( condition_holds )
*		yyless( 5 );
*	else
*		do_something_else();
*
* Prior to using the do-while the compiler would get upset at the
* "else" because it interpreted the "if" statement as being all
* done when it reached the ';' after the yyless() call.
*/

/* Return all but the first 'n' matched characters back to the input stream. */

#define yyless(n) \
	do \
{ \
	/* Undo effects of setting up yytext. */ \
	int yyless_macro_arg = (n); \
	YY_LESS_LINENO(yyless_macro_arg);\
	*yy_cp = YY_G(yy_hold_char); \
	YY_RESTORE_YY_MORE_OFFSET \
	YY_G(yy_c_buf_p) = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
	YY_DO_BEFORE_ACTION; /* set up yytext again */ \
} \
	while ( 0 )

#define unput(c) yyunput( c, YY_G(yytext_ptr) YY_CALL_LAST_ARG )

/* The following is because we cannot portably get our hands on size_t
* (without autoconf's help, which isn't available because we want
* flex-generated scanners to compile on their own).
*/

#ifndef YY_TYPEDEF_YY_SIZE_T
#define YY_TYPEDEF_YY_SIZE_T
typedef unsigned int yy_size_t;
#endif

#ifndef YY_STRUCT_YY_BUFFER_STATE
#define YY_STRUCT_YY_BUFFER_STATE
struct yy_buffer_state
{
	FILE *yy_input_file;



	char *yy_ch_buf;		/* input buffer */
	char *yy_buf_pos;		/* current position in input buffer */

	/* Size of input buffer in bytes, not including room for EOB
	* characters.
	*/
	yy_size_t yy_buf_size;

	/* Number of characters read into yy_ch_buf, not including EOB
	* characters.
	*/
	int yy_n_chars;

	/* Whether we "own" the buffer - i.e., we know we created it,
	* and can realloc() it to grow it, and should free() it to
	* delete it.
	*/
	int yy_is_our_buffer;

	/* Whether ptrThis is an "interactive" input source; if so, and
	* if we're using stdio for input, then we want to use getc()
	* instead of fread(), to make sure we stop fetching input after
	* each newline.
	*/
	int yy_is_interactive;

	/* Whether we're considered to be at the beginning of a line.
	* If so, '^' rules will be active on the next match, otherwise
	* not.
	*/
	int yy_at_bol;

	/* Whether to try to fill the input buffer when we reach the
	* end of it.
	*/
	int yy_fill_buffer;

	int yy_buffer_status;
#define YY_BUFFER_NEW 0
#define YY_BUFFER_NORMAL 1
	/* When an EOF's been seen but there's still some text to process
	* then we mark the buffer as YY_EOF_PENDING, to indicate that we
	* shouldn't try reading from the input source any more.  We might
	* still have a bunch of tokens to match, though, because of
	* possible backing-up.
	*
	* When we actually see the EOF, we change the status to "new"
	* (via yyrestart()), so that the user can continue scanning by
	* just pointing yyin at a new input file.
	*/
#define YY_BUFFER_EOF_PENDING 2
};
#endif /* !YY_STRUCT_YY_BUFFER_STATE */


/* We provide macros for accessing buffer states in case in the
* future we want to put the buffer states in a more general
* "scanner state".
*/
#define YY_CURRENT_BUFFER yy_current_buffer



void yyrestart YY_PARAMS(( FILE *input_file YY_PROTO_LAST_ARG ));


void yy_switch_to_buffer YY_PARAMS(( YY_BUFFER_STATE new_buffer YY_PROTO_LAST_ARG ));
void yy_load_buffer_state YY_PARAMS(( YY_PROTO_ONLY_ARG ));
YY_BUFFER_STATE yy_create_buffer YY_PARAMS(( FILE *file, int size YY_PROTO_LAST_ARG ));
void yy_delete_buffer YY_PARAMS(( YY_BUFFER_STATE b YY_PROTO_LAST_ARG ));
void yy_init_buffer YY_PARAMS(( YY_BUFFER_STATE b, FILE *file YY_PROTO_LAST_ARG ));
void yy_flush_buffer YY_PARAMS(( YY_BUFFER_STATE b YY_PROTO_LAST_ARG ));

#define YY_FLUSH_BUFFER yy_flush_buffer( YY_G(yy_current_buffer) YY_CALL_LAST_ARG)

YY_BUFFER_STATE yy_scan_buffer YY_PARAMS(( char *base, yy_size_t size YY_PROTO_LAST_ARG ));
YY_BUFFER_STATE yy_scan_string YY_PARAMS(( yyconst char *yy_str YY_PROTO_LAST_ARG ));
YY_BUFFER_STATE yy_scan_bytes YY_PARAMS(( yyconst char *bytes, int len YY_PROTO_LAST_ARG ));


void *yyalloc YY_PARAMS(( yy_size_t YY_PROTO_LAST_ARG ));
void *yyrealloc YY_PARAMS(( void *, yy_size_t YY_PROTO_LAST_ARG ));
void yyfree YY_PARAMS(( void * YY_PROTO_LAST_ARG ));

#define yy_new_buffer yy_create_buffer

#define yy_set_interactive(is_interactive) \
{ \
	if ( ! YY_G(yy_current_buffer) ) \
	YY_G(yy_current_buffer) =    \
	yy_create_buffer( yyin, YY_BUF_SIZE YY_CALL_LAST_ARG); \
	YY_G(yy_current_buffer)->yy_is_interactive = is_interactive; \
}

#define yy_set_bol(at_bol) \
{ \
	if ( ! YY_G(yy_current_buffer) ) \
	YY_G(yy_current_buffer) =    \
	yy_create_buffer( yyin, YY_BUF_SIZE YY_CALL_LAST_ARG); \
	YY_G(yy_current_buffer)->yy_at_bol = at_bol; \
}

#define YY_AT_BOL() (YY_G(yy_current_buffer)->yy_at_bol)


#define yywrap(n) 1
#define YY_SKIP_YYWRAP
#define yytext_ptr yytext_r


/* Done after the current pattern has been matched and before the
* corresponding action - sets up yytext.
*/
#define YY_DO_BEFORE_ACTION \
	YY_G(yytext_ptr) = yy_bp; \
	yyleng = (size_t) (yy_cp - yy_bp); \
	YY_G(yy_hold_char) = *yy_cp; \
	*yy_cp = '\0'; \
	YY_G(yy_c_buf_p) = yy_cp;


/* Special case for "unistd.h", since it is non-ANSI. We include it way
* down here because we want the user's section 1 to have been scanned first.
* The user has a chance to override it with an option.
*/
#ifndef YY_NO_UNISTD_H
#include <unistd.h>
#endif /* !YY_NO_UNISTD_H */

#ifndef YY_EXTRA_TYPE
#define YY_EXTRA_TYPE void *
#endif






/* Accessor methods to globals.
These are made visible to non-reentrant scanners for convenience. */

#ifndef YY_NO_DESTROY
int yylex_destroy YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_GET_DEBUG
int yyget_debug YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_DEBUG
void yyset_debug YY_PARAMS(( int debug_flag YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_EXTRA
YY_EXTRA_TYPE yyget_extra YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_EXTRA
void yyset_extra YY_PARAMS(( YY_EXTRA_TYPE user_defined YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_IN
FILE *yyget_in YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_IN
void yyset_in  YY_PARAMS(( FILE * in_str YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_OUT
FILE *yyget_out YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_OUT
void yyset_out  YY_PARAMS(( FILE * out_str YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_LENG
int yyget_leng YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_GET_TEXT
char *yyget_text YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_GET_LINENO
int yyget_lineno YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_LINENO
void yyset_lineno YY_PARAMS(( int line_number YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_LVAL
YYSTYPE * yyget_lval YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif
void yyset_lval YY_PARAMS(( YYSTYPE * yylvalp YY_PROTO_LAST_ARG ));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YY_NO_GET_LLOC
YYLTYPE *yyget_lloc YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif
#ifndef YY_NO_SET_LLOC
void yyset_lloc YY_PARAMS(( YYLTYPE * yyllocp YY_PROTO_LAST_ARG ));
#endif
#endif /* YYLTYPE */

/* Macros after ptrThis point can all be overridden by user definitions in
* section 1.
*/

#ifndef YY_SKIP_YYWRAP
#ifdef __cplusplus
extern "C" int yywrap YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#else
extern int yywrap YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif
#endif


#ifndef yytext_ptr
static void yy_flex_strncpy YY_PARAMS(( char *, yyconst char *, int YY_PROTO_LAST_ARG));
#endif

#ifdef YY_NEED_STRLEN
static int yy_flex_strlen YY_PARAMS(( yyconst char * YY_PROTO_LAST_ARG));
#endif

#ifndef YY_NO_INPUT
#endif


#if YY_STACK_USED

#ifndef YY_NO_PUSH_STATE
static void yy_push_state YY_PARAMS(( int new_state YY_PROTO_LAST_ARG));
#endif
#ifndef YY_NO_POP_STATE
static void yy_pop_state YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif
#ifndef YY_NO_TOP_STATE
static int yy_top_state YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#else
#define YY_NO_PUSH_STATE 1
#define YY_NO_POP_STATE 1
#define YY_NO_TOP_STATE 1
#endif

/* Amount of stuff to slurp up with each read. */
#ifndef YY_READ_BUF_SIZE
#define YY_READ_BUF_SIZE 8192
#endif

/* Copy whatever the last rule matched to the standard output. */

#ifndef ECHO
/* This used to be an fputs(), but since the string might contain NUL's,
* we now use fwrite().
*/
#define ECHO (void) fwrite( yytext, yyleng, 1, yyout )
#endif

/* Gets input and stuffs it into "buf".  number of characters read, or YY_NULL,
* is returned in "result".
*/
#ifndef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	errno=0; \
	while ( (result = read( fileno(yyin), (char *) buf, max_size )) < 0 ) \
{ \
	if( errno != EINTR) \
{ \
	YY_FATAL_ERROR( "input in flex scanner failed" ); \
	break; \
} \
	errno=0; \
	clearerr(yyin); \
}
\
#endif

/* No semi-colon after return; correct usage is to write "yyterminate();" -
* we don't want an extra ';' after the "return" because that will cause
* some compilers to complain about unreachable statements.
*/
#ifndef yyterminate
#define yyterminate() return YY_NULL
#endif

/* Number of entries by which start-condition stack grows. */
#ifndef YY_START_STACK_INCR
#define YY_START_STACK_INCR 25
#endif

/* Report a fatal error. */
#ifndef YY_FATAL_ERROR
#define YY_FATAL_ERROR(msg) yy_fatal_error( msg YY_CALL_LAST_ARG)
#endif


/* Default declaration of generated scanner - a define so the user can
* easily add parameters.
*/
#ifndef YY_DECL

/* If the bison pure parser is used, then bison will provide
one or two additional arguments. */

#  if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#        define YY_LEX_PROTO YY_PARAMS((YYSTYPE * yylvalp, YYLTYPE * yyllocp YY_PROTO_LAST_ARG))
#        define YY_LEX_DECLARATION YYFARGS2(YYSTYPE *,yylvalp, YYLTYPE *,yyllocp)
#  else
#        define YY_LEX_PROTO YY_PARAMS((YYSTYPE * yylvalp YY_PROTO_LAST_ARG))
#        define YY_LEX_DECLARATION YYFARGS1(YYSTYPE *,yylvalp)
#  endif



extern int yylex YY_LEX_PROTO;

#define YY_DECL int yylex YY_LEX_DECLARATION
#endif


/* Code executed at the beginning of each rule, after yytext and yyleng
* have been set up.
*/
#ifndef YY_USER_ACTION
#define YY_USER_ACTION
#endif

/* Code executed at the end of each rule. */
#ifndef YY_BREAK
#define YY_BREAK break;
#endif

#define YY_RULE_SETUP \
	YY_USER_ACTION



/* yy_get_next_buffer - try to read in a new buffer
*
* Returns a code representing an action:
*	EOB_ACT_LAST_MATCH -
*	EOB_ACT_CONTINUE_SCAN - continue scanning from current position
*	EOB_ACT_END_OF_FILE - end of file
*/


/* yy_get_previous_state - get the state just before the EOB char was reached */

///#line 135 "../../../src/sd/domnode-xml-scanner.l"
///#line 719 "domnode-xml-scanner.h"
#ifdef YY_HEADER_EXPORT_START_CONDITIONS
/* Beware! Start conditions are not prefixed. */
#undef INITIAL
#define INITIAL 0
#define CONTENT 1
#endif /* YY_HEADER_EXPORT_START_CONDITIONS */

#ifndef YY_HEADER_NO_UNDEFS
/* Undefine all internal macros, etc., that do no belong in the header. */

#undef BEGIN
#undef ECHO
#undef EOB_ACT_CONTINUE_SCAN
#undef EOB_ACT_END_OF_FILE
#undef EOB_ACT_LAST_MATCH
#undef FLEX_SCANNER
#undef FLEX_STD
#undef REJECT
#undef YYLMAX
#undef YYSTATE
#undef YY_AT_BOL
#undef YY_BREAK
#undef YY_BUFFER_EOF_PENDING
#undef YY_BUFFER_NEW
#undef YY_BUFFER_NORMAL
#undef YY_BUF_SIZE
#undef YY_CALL_LAST_ARG
#undef YY_CALL_ONLY_ARG
#undef YY_CURRENT_BUFFER
#undef YY_DECL
#undef YY_DECL_LAST_ARG
#undef YY_DO_BEFORE_ACTION
#undef YY_END_OF_BUFFER
#undef YY_END_OF_BUFFER_CHAR
#undef YY_EXIT_FAILURE
#undef YY_EXTRA_TYPE
#undef YY_FATAL_ERROR
#undef YY_FLEX_DEFINED_ECHO
#undef YY_FLEX_LEX_COMPAT
#undef YY_FLEX_MAJOR_VERSION
#undef YY_FLEX_MINOR_VERSION
#undef YY_FLUSH_BUFFER
#undef YY_G
#undef YY_INPUT
#undef YY_INT_ALIGNED
#undef YY_INTERACTIVE
#undef YY_LAST_ARG
#undef YY_LEX_ARGS
#undef YY_MAIN
#undef YY_MORE_ADJ
#undef YY_NEED_STRLEN
#undef YY_NEW_FILE
#undef YY_NO_FLEX_ALLOC
#undef YY_NO_FLEX_REALLOC
#undef YY_NO_FLEX_FREE
#undef YY_NO_GET_DEBUG
#undef YY_NO_GET_EXTRA
#undef YY_NO_GET_IN
#undef YY_NO_GET_LENG
#undef YY_NO_GET_LINENO
#undef YY_NO_GET_LLOC
#undef YY_NO_GET_LVAL
#undef YY_NO_GET_OUT
#undef YY_NO_GET_TEXT
#undef YY_NO_INPUT
#undef YY_NO_POP_STATE
#undef YY_NO_PUSH_STATE
#undef YY_NO_SCAN_BUFFER
#undef YY_NO_SCAN_BYTES
#undef YY_NO_SCAN_STRING
#undef YY_NO_SET_DEBUG
#undef YY_NO_SET_EXTRA
#undef YY_NO_SET_IN
#undef YY_NO_SET_LINENO
#undef YY_NO_SET_LLOC
#undef YY_NO_SET_LVAL
#undef YY_NO_SET_OUT
#undef YY_NO_TOP_STATE
#undef YY_NO_UNISTD_H
#undef YY_NO_UNPUT
#undef YY_NULL
#undef YY_NUM_RULES
#undef YY_ONLY_ARG
#undef YY_PROTO
#undef YY_READ_BUF_SIZE
#undef YY_REENTRANT
#undef YY_BISON_BRIDGE
#undef YY_RESTORE_YY_MORE_OFFSET
#undef YY_RULE_SETUP
#undef YY_SC_TO_UI
#undef YY_SKIP_YYWRAP
#undef YY_STACK_USED
#undef YY_START
#undef YY_START_STACK_INCR
#undef YY_STATE_EOF
#undef YY_STDINIT
#undef YY_TEXT_IS_ARRAY
#undef YY_TRAILING_HEAD_MASK
#undef YY_TRAILING_MASK
#undef YY_USER_ACTION
#undef YY_USES_REJECT
#undef YY_USE_CONST
#undef YY_USE_LINENO
#undef YY_USE_PROTOS
#undef unput
#undef yy_create_buffer
#undef yy_delete_buffer
#undef yy_flex_debug
#undef yy_flush_buffer
#undef yy_init_buffer
#undef yy_load_buffer_state
#undef yy_new_buffer
#undef yy_scan_buffer
#undef yy_scan_bytes
#undef yy_scan_string
#undef yy_set_bol
#undef yy_set_interactive
#undef yy_switch_to_buffer
#undef yyconst
#undef yyextra
#undef yyget_debug
#undef yyset_debug
#undef yyget_extra
#undef yyget_in
#undef yyget_leng
#undef yyget_lineno
#undef yyget_lloc
#undef yyget_lval
#undef yyget_out
#undef yyget_text
#undef yyin
#undef yyleng
#undef yyless
#undef yylex
#undef yylex_destroy
#undef yylex_init
#undef yylineno
#undef yylloc
#undef yylval
#undef yymore
#undef yyout
#undef yyrestart
#undef yyset_extra
#undef yyset_in
#undef yyset_lineno
#undef yyset_lloc
#undef yyset_lval
#undef yyset_out
#undef yyterminate
#undef yytext
#undef yytext_ptr
#undef yywrap
#undef yyalloc
#undef yyrealloc
#undef yyfree
#undef YY_NEVER_INTERACTIVE
#undef YY_NO_UNPUT
#undef YY_TABLES_VERIFY
#endif /* !YY_HEADER_NO_UNDEFS */

#undef __sd_domnode_xml_IN_HEADER
#endif /* __sd_domnode_xml_HEADER_H */


/************** End of domnode-xml-scanner.h *******************************************/

/************** Begin of domnode-xml-parser.c *******************************************/
/* A Bison parser, made from ../../../src/sd/domnode-xml-parser.y
by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse __sd_domnode_xml_parse
#define yylex __sd_domnode_xml_lex
#define yyerror __sd_domnode_xml_error
#define yylval __sd_domnode_xml_lval
#define yychar __sd_domnode_xml_char
#define yydebug __sd_domnode_xml_debug
#define yynerrs __sd_domnode_xml_nerrs
# define	ENDDEF	257
# define	EQ	258
# define	SLASH	259
# define	CLOSE	260
# define	END	261
# define	NAME	262
# define	VALUE	263
# define	DATA	264
# define	COMMENT	265
# define	START	266

///#line 1 "../../../src/sd/domnode-xml-parser.y"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///#include "error.h"
///#include "malloc.h"
///#include "domnode-xml.h"

/* Generated by bison(1) */
///#include "domnode-xml-parser.h"

/* Generated by flex(1) */
#define YY_HEADER_NO_UNDEFS 1
///#include "domnode-xml-scanner.h"

#define YYPARSE_PARAM __a_maker
#define a_maker ((struct __sd_domnode_xml_maker*) YYPARSE_PARAM)
#define YYLEX_PARAM (a_maker->scanner)

#ifdef strdup
#	undef strdup
#endif
#define strdup sd_strdup
#ifdef malloc
#	undef malloc
#endif
#define malloc sd_malloc
#ifdef calloc
#	undef calloc
#endif
#define calloc sd_calloc
#ifdef realloc
#	undef realloc
#endif
#define realloc sd_realloc
#ifdef yyerror
#	undef yyerror
#endif
#define yyerror sd_error

static void domnode_attribute(struct __sd_domnode_xml_maker*, const char*,
							  const char*);

///#line 52 "../../../src/sd/domnode-xml-parser.y"
#ifndef YYSTYPE
typedef union { char *s; } yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 1
#endif



#define	YYFINAL		27
#define	YYFLAG		-32768
#define	YYNTBASE	13

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 266 ? yytranslate[x] : 23)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
	0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
	6,     7,     8,     9,    10,    11,    12
};

#if YYDEBUG
static const short yyprhs[] =
{
	0,     0,     4,     7,     8,    10,    11,    16,    19,    25,
	28,    31,    34,    35,    37,    40,    41,    43
};
static const short yyrhs[] =
{
	14,    16,    14,     0,    14,    15,     0,     0,    11,     0,
	0,    12,    17,    21,    18,     0,     5,     6,     0,     6,
	19,     7,    20,     6,     0,    19,    10,     0,    19,    16,
	0,    19,    15,     0,     0,     8,     0,    21,    22,     0,
	0,     8,     0,     8,     4,     9,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
	0,    61,    65,    66,    70,    84,    84,   118,   126,   146,
	156,   157,   158,   162,   169,   170,   174,   180
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
	"$", "error", "$undefined.", "ENDDEF", "EQ", "SLASH", "CLOSE", "END", 
	"NAME", "VALUE", "DATA", "COMMENT", "START", "document", "misc", 
	"comment", "element", "@1", "empty_or_content", "content", "name", 
	"attribute_seq_opt", "attribute", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
	0,    13,    14,    14,    15,    17,    16,    18,    18,    19,
	19,    19,    19,    20,    21,    21,    22,    22
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
	0,     3,     2,     0,     1,     0,     4,     2,     5,     2,
	2,     2,     0,     1,     2,     0,     1,     3
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
doesn't specify something else to do.  Zero means the default is an
error. */
static const short yydefact[] =
{
	3,     0,     4,     5,     2,     3,    15,     1,     0,     0,
	12,    16,     6,    14,     7,     0,     0,     0,     9,    11,
	10,    17,    13,     0,     8,     0,     0,     0
};

static const short yydefgoto[] =
{
	25,     1,     4,     5,     6,    12,    15,    23,     8,    13
};

static const short yypact[] =
{
	-32768,   -10,-32768,-32768,-32768,-32768,-32768,    -3,     1,     4,
	-32768,     7,-32768,-32768,-32768,    -7,     3,     5,-32768,-32768,
	-32768,-32768,-32768,     8,-32768,    15,    16,-32768
};

static const short yypgoto[] =
{
	-32768,    12,     6,     9,-32768,-32768,-32768,-32768,-32768,-32768
};


#define	YYLAST		24


static const short yytable[] =
{
	17,     2,     3,    18,     2,     3,     9,    10,     2,    11,
	14,    16,    21,    22,    24,    26,    27,     7,     0,     0,
	0,    19,     0,     0,    20
};

static const short yycheck[] =
{
	7,    11,    12,    10,    11,    12,     5,     6,    11,     8,
	6,     4,     9,     8,     6,     0,     0,     5,    -1,    -1,
	-1,    15,    -1,    -1,    15
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
///#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
Foundation, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ptrThis program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* As a special exception, when ptrThis file is copied by Bison into a
Bison output file, you may use that output file without restriction.
This special exception was added by the Free Software Foundation
in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
the %semantic_parser declaration is not specified in the grammar.
It was written by Richard Stallman by simplifying the hairy parser
used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
infringing on user name space.  This should be done even for local
variables, as they might otherwise be expanded by user macros.
There are some unavoidable exceptions within include files to
define necessary library symbols; they are noted "INFRINGES ON
USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
/* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
	&& (! defined (__cplusplus) \
	|| (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
	short yyss;
	YYSTYPE yyvs;
# if YYLSP_NEEDED
	YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
	((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
	+ 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
	((N) * (sizeof (short) + sizeof (YYSTYPE))				\
	+ YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
	__builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
	do					\
{					\
	register YYSIZE_T yyi;		\
	for (yyi = 0; yyi < (Count); yyi++)	\
	(To)[yyi] = (From)[yyi];		\
}					\
	while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
local variables YYSIZE and YYSTACKSIZE give the old and new number of
elements in the stack, and YYPTR gives the new location of the
stack.  Advance YYPTR to a properly aligned location for the next
stack.  */
# define YYSTACK_RELOCATE(Stack)					\
	do									\
{									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
}									\
	while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
to ease the transition to the new meaning of YYERROR, for GCC.
Once GCC version 2 has supplanted version 1, ptrThis can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
	do								\
	if (yychar == YYEMPTY && yylen == 1)				\
{								\
	yychar = (Token);						\
	yylval = (Value);						\
	yychar1 = YYTRANSLATE (yychar);				\
	YYPOPSTACK;						\
	goto yybackup;						\
}								\
  else								\
{ 								\
	yyerror ("syntax error: cannot back up");			\
	YYERROR;							\
}								\
	while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
are run).

When YYLLOC_DEFAULT is run, CURRENT is set the location of the
first token.  By default, to implement support for ranges, extend
its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
	Current.last_line   = Rhs[N].last_line;	\
	Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
	do {						\
	if (yydebug)					\
	YYFPRINTF Args;				\
	} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
if the built-in stack extension method is used).

Do not make ptrThis value too large; the results are undefined if
SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
const char *yystr;
#   endif
{
	register const char *yys = yystr;

	while (*yys++ != '\0')
		continue;

	return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
char *yydest;
const char *yysrc;
#   endif
{
	register char *yyd = yydest;
	register const char *yys = yysrc;

	while ((*yyd++ = *yys++) != '\0')
		continue;

	return yyd - 1;
}
#  endif
# endif
#endif

///#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
into yyparse.  The argument should have type void *.
It should actually point to an object.
Grammar actions can access the variable by casting it
to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
///int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
	/* The lookahead symbol.  */				\
	int yychar;						\
	\
	/* The semantic value of the lookahead symbol. */	\
	YYSTYPE yylval;						\
	\
	/* Number of parse errors so far.  */			\
	int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
	YY_DECL_NON_LSP_VARIABLES			\
	\
	/* Location data for the lookahead symbol.  */	\
	YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
	YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

//int
//yyparse (YYPARSE_PARAM_ARG)
//YYPARSE_PARAM_DECL
int yyparse(struct __sd_domnode_xml_maker*YYPARSE_PARAM)
{
	/* If reentrant, generate the variables here. */
#if YYPURE
	YY_DECL_VARIABLES
#endif  /* !YYPURE */

		register int yystate;
	register int yyn;
	int yyresult;
	/* Number of tokens to shift before error messages enabled.  */
	int yyerrstatus;
	/* Lookahead token as an internal (translated) token number.  */
	int yychar1 = 0;

	/* Three stacks and their tools:
	`yyss': related to states,
	`yyvs': related to semantic values,
	`yyls': related to locations.

	Refer to the stacks thru separate pointers, to allow yyoverflow
	to reallocate them elsewhere.  */

	/* The state stack. */
	short	yyssa[YYINITDEPTH];
	short *yyss = yyssa;
	register short *yyssp;

	/* The semantic value stack.  */
	YYSTYPE yyvsa[YYINITDEPTH];
	YYSTYPE *yyvs = yyvsa;
	register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
	/* The location stack.  */
	YYLTYPE yylsa[YYINITDEPTH];
	YYLTYPE *yyls = yylsa;
	YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

	YYSIZE_T yystacksize = YYINITDEPTH;


	/* The variables used to return semantic value and location from the
	action routines.  */
	YYSTYPE yyval;
#if YYLSP_NEEDED
	YYLTYPE yyloc;
#endif

	/* When reducing, the number of symbols on the RHS of the reduced
	rule. */
	int yylen;

	YYDPRINTF ((stderr, "Starting parse\n"));

	yystate = 0;
	yyerrstatus = 0;
	yynerrs = 0;
	yychar = YYEMPTY;		/* Cause a token to be read.  */

	/* Initialize stack pointers.
	Waste one element of value and location stack
	so that they stay on the same level as the state stack.
	The wasted elements are never initialized.  */

	yyssp = yyss;
	yyvsp = yyvs;
#if YYLSP_NEEDED
	yylsp = yyls;
#endif
	goto yysetstate;

	/*------------------------------------------------------------.
	| yynewstate -- Push a new state, which is found in yystate.  |
	`------------------------------------------------------------*/
yynewstate:
	/* In all cases, when you get here, the value and location stacks
	have just been pushed. so pushing a state here evens the stacks.
	*/
	yyssp++;

yysetstate:
	*yyssp = yystate;

	if (yyssp >= yyss + yystacksize - 1)
	{
		/* Get the current used size of the three stacks, in elements.  */
		YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
		{
			/* Give user a chance to reallocate the stack. Use copies of
			these so that the &'s don't force the real ones into
			memory.  */
			YYSTYPE *yyvs1 = yyvs;
			short *yyss1 = yyss;

			/* Each stack pointer address is followed by the size of the
			data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
			YYLTYPE *yyls1 = yyls;
			/* This used to be a conditional around just the two extra args,
			but that might be undefined if yyoverflow is a macro.  */
			yyoverflow ("parser stack overflow",
				&yyss1, yysize * sizeof (*yyssp),
				&yyvs1, yysize * sizeof (*yyvsp),
				&yyls1, yysize * sizeof (*yylsp),
				&yystacksize);
			yyls = yyls1;
# else
			yyoverflow ("parser stack overflow",
				&yyss1, yysize * sizeof (*yyssp),
				&yyvs1, yysize * sizeof (*yyvsp),
				&yystacksize);
# endif
			yyss = yyss1;
			yyvs = yyvs1;
		}
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
		goto yyoverflowlab;
# else
		/* Extend the stack our own way.  */
		if (yystacksize >= YYMAXDEPTH)
			goto yyoverflowlab;
		yystacksize *= 2;
		if (yystacksize > YYMAXDEPTH)
			yystacksize = YYMAXDEPTH;

		{
			short *yyss1 = yyss;
			union yyalloc *yyptr =
				(union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
			if (! yyptr)
				goto yyoverflowlab;
			YYSTACK_RELOCATE (yyss);
			YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
			YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
			if (yyss1 != yyssa)
				YYSTACK_FREE (yyss1);
		}
# endif
#endif /* no yyoverflow */

		yyssp = yyss + yysize - 1;
		yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
		yylsp = yyls + yysize - 1;
#endif

		YYDPRINTF ((stderr, "Stack size increased to %lu\n",
			(unsigned long int) yystacksize));

		if (yyssp >= yyss + yystacksize - 1)
			YYABORT;
	}

	YYDPRINTF ((stderr, "Entering state %d\n", yystate));

	goto yybackup;


	/*-----------.
	| yybackup.  |
	`-----------*/
yybackup:

	/* Do appropriate processing given the current state.  */
	/* Read a lookahead token if we need one and don't already have one.  */
	/* yyresume: */

	/* First try to decide what to do without reference to lookahead token.  */

	yyn = yypact[yystate];
	if (yyn == YYFLAG)
		goto yydefault;

	/* Not known => get a lookahead token if don't already have one.  */

	/* yychar is either YYEMPTY or YYEOF
	or a valid token in external form.  */

	if (yychar == YYEMPTY)
	{
		YYDPRINTF ((stderr, "Reading a token: "));
		yychar = YYLEX;
	}

	/* Convert token to internal form (in yychar1) for indexing tables with */

	if (yychar <= 0)		/* This means end of input. */
	{
		yychar1 = 0;
		yychar = YYEOF;		/* Don't call YYLEX any more */

		YYDPRINTF ((stderr, "Now at end of input.\n"));
	}
	else
	{
		yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
		/* We have to keep ptrThis `#if YYDEBUG', since we use variables
		which are defined only if `YYDEBUG' is set.  */
		if (yydebug)
		{
			YYFPRINTF (stderr, "Next token is %d (%s",
				yychar, yytname[yychar1]);
			/* Give the individual parser a way to print the precise
			meaning of a token, for further debugging info.  */
# ifdef YYPRINT
			YYPRINT (stderr, yychar, yylval);
# endif
			YYFPRINTF (stderr, ")\n");
		}
#endif
	}

	yyn += yychar1;
	if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
		goto yydefault;

	yyn = yytable[yyn];

	/* yyn is what to do for ptrThis token type in ptrThis state.
	Negative => reduce, -yyn is rule number.
	Positive => shift, yyn is new state.
	New state is final state => don't bother to shift,
	just return success.
	0, or most negative number => error.  */

	if (yyn < 0)
	{
		if (yyn == YYFLAG)
			goto yyerrlab;
		yyn = -yyn;
		goto yyreduce;
	}
	else if (yyn == 0)
		goto yyerrlab;

	if (yyn == YYFINAL)
		YYACCEPT;

	/* Shift the lookahead token.  */
	YYDPRINTF ((stderr, "Shifting token %d (%s), ",
		yychar, yytname[yychar1]));

	/* Discard the token being shifted unless it is eof.  */
	if (yychar != YYEOF)
		yychar = YYEMPTY;

	*++yyvsp = yylval;
#if YYLSP_NEEDED
	*++yylsp = yylloc;
#endif

	/* Count tokens shifted since error; after three, turn off error
	status.  */
	if (yyerrstatus)
		yyerrstatus--;

	yystate = yyn;
	goto yynewstate;


	/*-----------------------------------------------------------.
	| yydefault -- do the default action for the current state.  |
	`-----------------------------------------------------------*/
yydefault:
	yyn = yydefact[yystate];
	if (yyn == 0)
		goto yyerrlab;
	goto yyreduce;


	/*-----------------------------.
	| yyreduce -- Do a reduction.  |
	`-----------------------------*/
yyreduce:
	/* yyn is the number of a rule to reduce with.  */
	yylen = yyr2[yyn];

	/* If YYLEN is nonzero, implement the default value of the action:
	`$$ = $1'.

	Otherwise, the following line sets YYVAL to the semantic value of
	the lookahead token.  This behavior is undocumented and Bison
	users should not rely upon it.  Assigning to YYVAL
	unconditionally makes the parser a bit smaller, and it avoids a
	GCC warning that YYVAL may be used uninitialized.  */
	yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
	/* Similarly for the default location.  Let the user run additional
	commands if for instance locations are ranges.  */
	yyloc = yylsp[1-yylen];
	YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
	/* We have to keep ptrThis `#if YYDEBUG', since we use variables which
	are defined only if `YYDEBUG' is set.  */
	if (yydebug)
	{
		int yyi;

		YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
			yyn, yyrline[yyn]);

		/* Print the symbols being reduced, and their result.  */
		for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
			YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
		YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
	}
#endif

	switch (yyn) {

case 4:
///#line 71 "../../../src/sd/domnode-xml-parser.y"
	{
		sd_domnode_t* node = (sd_domnode_t*)sd_stack_peek(a_maker->elements);

		if (node) {
			sd_debug("COMMENT: add comment '%s' to node '%s'\n", yyvsp[0].s, node->name);
			sd_list_append(node->children, __sd_domnode_new("#comment", yyvsp[0].s, 0));
			/* $1 was obtain with strdup() */
			free(yyvsp[0].s);
		}
		;
		break;}
case 5:
///#line 85 "../../../src/sd/domnode-xml-parser.y"
	{
		sd_domnode_t* parent = (sd_domnode_t*)sd_stack_peek(a_maker->elements);
		sd_domnode_t* node = __sd_domnode_new(yyvsp[0].s, 0, 1);

#ifdef __SD_DEBUG__
		{
			static void* __debug = 0;
			if (! __debug) {
				__debug = getenv("SD_DEBUG");
				if (__debug)
					yydebug = 1;
				else
					__debug = (void*) 0x1;
			}
		}
#endif

		if (parent) {
			sd_debug("START: add child '%s' to node '%s'\n", yyvsp[0].s, parent->name);
			sd_list_append(parent->children, node);
		} else {
			sd_debug("START: add root'%s'\n", yyvsp[0].s);
			a_maker->root = node;
		}

		sd_stack_push(a_maker->elements, node);
		free(yyvsp[0].s);
		;
		break;}
case 7:
///#line 119 "../../../src/sd/domnode-xml-parser.y"
	{
		sd_domnode_t* node = (sd_domnode_t*)sd_stack_peek(a_maker->elements);
		assert(node != 0);

		sd_debug("END: simple node '%s'\n", node->name);
		sd_stack_pop(a_maker->elements);
		;
		break;}
case 8:
///#line 127 "../../../src/sd/domnode-xml-parser.y"
	{
		sd_domnode_t* node = (sd_domnode_t*)sd_stack_peek(a_maker->elements);
		assert(node != 0);

		sd_debug("END: node '%s'\n", yyvsp[-1].s);

		if (strcmp(node->name, yyvsp[-1].s)) {
			yyerror("got </%s> instead of </%s>\n", yyvsp[-1].s, node->name);
			YYERROR;
		}

		/* $4 was obtain with strdup() */
		free(yyvsp[-1].s);

		sd_stack_pop(a_maker->elements);
		;
		break;}
case 9:
///#line 147 "../../../src/sd/domnode-xml-parser.y"
	{
		sd_domnode_t* node = (sd_domnode_t*)sd_stack_peek(a_maker->elements);
		assert(node != 0);

		sd_debug("CONTENT: add cvalue '%s' to node '%s'\n", yyvsp[0].s, node->name);

		/* $2 was obtain with strdup() */
		node->value = yyvsp[0].s;
		;
		break;}
case 13:
///#line 163 "../../../src/sd/domnode-xml-parser.y"
	{
		yyval.s = yyvsp[0].s;
		;
		break;}
case 16:
///#line 175 "../../../src/sd/domnode-xml-parser.y"
	{
		domnode_attribute(a_maker, yyvsp[0].s, "");
		/* $1 was obtain with strdup() */
		free(yyvsp[0].s);
		;
		break;}
case 17:
///#line 181 "../../../src/sd/domnode-xml-parser.y"
	{
		domnode_attribute(a_maker, yyvsp[-2].s, yyvsp[0].s);
		/* $1 was obtain with strdup() */
		free(yyvsp[-2].s);
		/* $3 was obtain with strdup() */
		free(yyvsp[0].s);
		;
		break;}
	}

///#line 705 "/usr/share/bison/bison.simple"

	
	yyvsp -= yylen;
	yyssp -= yylen;
#if YYLSP_NEEDED
	yylsp -= yylen;
#endif

#if YYDEBUG
	if (yydebug)
	{
		short *yyssp1 = yyss - 1;
		YYFPRINTF (stderr, "state stack now");
		while (yyssp1 != yyssp)
			YYFPRINTF (stderr, " %d", *++yyssp1);
		YYFPRINTF (stderr, "\n");
	}
#endif

	*++yyvsp = yyval;
#if YYLSP_NEEDED
	*++yylsp = yyloc;
#endif

	/* Now `shift' the result of the reduction.  Determine what state
	that goes to, based on the state we popped back to and the rule
	number reduced by.  */

	yyn = yyr1[yyn];

	yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
	if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
		yystate = yytable[yystate];
	else
		yystate = yydefgoto[yyn - YYNTBASE];

	goto yynewstate;


	/*------------------------------------.
	| yyerrlab -- here on detecting error |
	`------------------------------------*/
yyerrlab:
	/* If not already recovering from an error, report ptrThis error.  */
	if (!yyerrstatus)
	{
		++yynerrs;

#ifdef YYERROR_VERBOSE
		yyn = yypact[yystate];

		if (yyn > YYFLAG && yyn < YYLAST)
		{
			YYSIZE_T yysize = 0;
			char *yymsg;
			int yyx, yycount;

			yycount = 0;
			/* Start YYX at -YYN if negative to avoid negative indexes in
			YYCHECK.  */
			for (yyx = yyn < 0 ? -yyn : 0;
				yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
				if (yycheck[yyx + yyn] == yyx)
					yysize += yystrlen (yytname[yyx]) + 15, yycount++;
			yysize += yystrlen ("parse error, unexpected ") + 1;
			yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
			yymsg = (char *) YYSTACK_ALLOC (yysize);
			if (yymsg != 0)
			{
				char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
				yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

				if (yycount < 5)
				{
					yycount = 0;
					for (yyx = yyn < 0 ? -yyn : 0;
						yyx < (int) (sizeof (yytname) / sizeof (char *));
						yyx++)
						if (yycheck[yyx + yyn] == yyx)
						{
							const char *yyq = ! yycount ? ", expecting " : " or ";
							yyp = yystpcpy (yyp, yyq);
							yyp = yystpcpy (yyp, yytname[yyx]);
							yycount++;
						}
				}
				yyerror (yymsg);
				YYSTACK_FREE (yymsg);
			}
			else
				yyerror ("parse error; also virtual memory exhausted");
		}
		else
#endif /* defined (YYERROR_VERBOSE) */
			yyerror ("parse error");
	}
	goto yyerrlab1;


	/*--------------------------------------------------.
	| yyerrlab1 -- error raised explicitly by an action |
	`--------------------------------------------------*/
yyerrlab1:
	if (yyerrstatus == 3)
	{
		/* If just tried and failed to reuse lookahead token after an
		error, discard it.  */

		/* return failure if at end of input */
		if (yychar == YYEOF)
			YYABORT;
		YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
			yychar, yytname[yychar1]));
		yychar = YYEMPTY;
	}

	/* Else will try to reuse lookahead token after shifting the error
	token.  */

	yyerrstatus = 3;		/* Each real token shifted decrements ptrThis */

	goto yyerrhandle;


	/*-------------------------------------------------------------------.
	| yyerrdefault -- current state does not do anything special for the |
	| error token.                                                       |
	`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
	/* This is wrong; only states that explicitly want error tokens
	should shift them.  */

	/* If its default is to accept any token, ok.  Otherwise pop it.  */
	yyn = yydefact[yystate];
	if (yyn)
		goto yydefault;
#endif


	/*---------------------------------------------------------------.
	| yyerrpop -- pop the current state because it cannot handle the |
	| error token                                                    |
	`---------------------------------------------------------------*/
yyerrpop:
	if (yyssp == yyss)
		YYABORT;
	yyvsp--;
	yystate = *--yyssp;
#if YYLSP_NEEDED
	yylsp--;
#endif

#if YYDEBUG
	if (yydebug)
	{
		short *yyssp1 = yyss - 1;
		YYFPRINTF (stderr, "Error: state stack now");
		while (yyssp1 != yyssp)
			YYFPRINTF (stderr, " %d", *++yyssp1);
		YYFPRINTF (stderr, "\n");
	}
#endif

	/*--------------.
	| yyerrhandle.  |
	`--------------*/
yyerrhandle:
	yyn = yypact[yystate];
	if (yyn == YYFLAG)
		goto yyerrdefault;

	yyn += YYTERROR;
	if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
		goto yyerrdefault;

	yyn = yytable[yyn];
	if (yyn < 0)
	{
		if (yyn == YYFLAG)
			goto yyerrpop;
		yyn = -yyn;
		goto yyreduce;
	}
	else if (yyn == 0)
		goto yyerrpop;

	if (yyn == YYFINAL)
		YYACCEPT;

	YYDPRINTF ((stderr, "Shifting error token, "));

	*++yyvsp = yylval;
#if YYLSP_NEEDED
	*++yylsp = yylloc;
#endif

	yystate = yyn;
	goto yynewstate;


	/*-------------------------------------.
	| yyacceptlab -- YYACCEPT comes here.  |
	`-------------------------------------*/
yyacceptlab:
	yyresult = 0;
	goto yyreturn;

	/*-----------------------------------.
	| yyabortlab -- YYABORT comes here.  |
	`-----------------------------------*/
yyabortlab:
	yyresult = 1;
	goto yyreturn;

	/*---------------------------------------------.
	| yyoverflowab -- parser overflow comes here.  |
	`---------------------------------------------*/
yyoverflowlab:
	yyerror ("parser stack overflow");
	yyresult = 2;
	/* Fall through.  */

yyreturn:
#ifndef yyoverflow
	if (yyss != yyssa)
		YYSTACK_FREE (yyss);
#endif
	return yyresult;
}
///#line 190 "../../../src/sd/domnode-xml-parser.y"

#undef a_maker

/******************************************************************************/
static void domnode_attribute(struct __sd_domnode_xml_maker* a_maker,
							  const char* a_name, const char* a_value)
{
	sd_domnode_t* node = (sd_domnode_t*)sd_stack_peek(a_maker->elements);
	assert(node != 0);

	sd_debug("ATTR: add atrribute '%s'='%s' to node '%s'\n", a_name, a_value,
		node->name);

	sd_list_append(node->attrs, __sd_domnode_new(a_name, a_value, 0));
}

/************** End of domnode-xml-parser.c *******************************************/


/************** begin of domnode-xml-scanner.c *******************************************/
#define YY_REENTRANT 1
#define YY_BISON_BRIDGE 1
#ifndef YY_REENTRANT
#define yytext __sd_domnode_xml_text
#define yyleng __sd_domnode_xml_leng
#define yyin __sd_domnode_xml_in
#define yyout __sd_domnode_xml_out
#define yy_flex_debug __sd_domnode_xml__flex_debug
#endif
#define yy_create_buffer __sd_domnode_xml__create_buffer
#define yy_delete_buffer __sd_domnode_xml__delete_buffer
#define yy_scan_buffer __sd_domnode_xml__scan_buffer
#define yy_scan_string __sd_domnode_xml__scan_string
#define yy_scan_bytes __sd_domnode_xml__scan_bytes
#define yy_init_buffer __sd_domnode_xml__init_buffer
#define yy_flush_buffer __sd_domnode_xml__flush_buffer
#define yy_load_buffer_state __sd_domnode_xml__load_buffer_state
#define yy_switch_to_buffer __sd_domnode_xml__switch_to_buffer
#define yylex __sd_domnode_xml_lex
#define yyrestart __sd_domnode_xml_restart
#define yylex_init __sd_domnode_xml_lex_init
#define yylex_destroy __sd_domnode_xml_lex_destroy
#define yyget_debug __sd_domnode_xml_get_debug
#define yyset_debug __sd_domnode_xml_set_debug
#define yyget_extra __sd_domnode_xml_get_extra
#define yyset_extra __sd_domnode_xml_set_extra
#define yyget_in __sd_domnode_xml_get_in
#define yyset_in __sd_domnode_xml_set_in
#define yyget_out __sd_domnode_xml_get_out
#define yyset_out __sd_domnode_xml_set_out
#define yyget_leng __sd_domnode_xml_get_leng
#define yyget_text __sd_domnode_xml_get_text
#define yyget_lineno __sd_domnode_xml_get_lineno
#define yyset_lineno __sd_domnode_xml_set_lineno
#ifdef YY_BISON_BRIDGE
#define yyget_lval __sd_domnode_xml_get_lval
#define yyset_lval __sd_domnode_xml_set_lval
#define yyget_lloc __sd_domnode_xml_get_lloc
#define yyset_lloc __sd_domnode_xml_set_lloc
#endif
#define yyalloc __sd_domnode_xml_alloc
#define yyrealloc __sd_domnode_xml_realloc
#define yyfree __sd_domnode_xml_free

///#line 46 "domnode-xml-scanner.c"
#define  YY_INT_ALIGNED short int


/* A lexical scanner generated by flex */

#define FLEX_SCANNER
#define YY_FLEX_MAJOR_VERSION 2
#define YY_FLEX_MINOR_VERSION 5
#define YY_FLEX_SUBMINOR_VERSION 27
#if YY_FLEX_SUBMINOR_VERSION > 0
#define FLEX_BETA
#endif

/* First, we deal with  platform-specific or compiler-specific issues. */

/* begin standard C headers. */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

/* end standard C headers. */

///#include <sd/sd_xplatform.h>

/* flex integer type definitions */

#ifndef FLEXINT_H
#define FLEXINT_H

/* C99 systems have <inttypes.h>. Non-C99 systems may or may not. */

#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
typedef int8_t flex_int8_t;
typedef uint8_t flex_uint8_t;
typedef int16_t flex_int16_t;
typedef uint16_t flex_uint16_t;
typedef int32_t flex_int32_t;
typedef uint32_t flex_uint32_t;
#else
typedef signed char flex_int8_t;
typedef short int flex_int16_t;
typedef int flex_int32_t;
typedef unsigned char flex_uint8_t; 
typedef unsigned short int flex_uint16_t;
typedef unsigned int flex_uint32_t;
#endif /* ! C99 */

/* Limits of integral types. */
#ifndef INT8_MIN
#define INT8_MIN               (-128)
#endif
#ifndef INT16_MIN
#define INT16_MIN              (-32767-1)
#endif
#ifndef INT32_MIN
#define INT32_MIN              (-2147483647-1)
#endif
#ifndef INT8_MAX
#define INT8_MAX               (127)
#endif
#ifndef INT16_MAX
#define INT16_MAX              (32767)
#endif
#ifndef INT32_MAX
#define INT32_MAX              (2147483647)
#endif
#ifndef UINT8_MAX
#define UINT8_MAX              (255U)
#endif
#ifndef UINT16_MAX
#define UINT16_MAX             (65535U)
#endif
#ifndef UINT32_MAX
#define UINT32_MAX             (4294967295U)
#endif


#endif /* ! FLEXINT_H */



#ifdef __cplusplus

/* C++ compilers don't understand traditional function definitions. */
#ifdef YY_TRADITIONAL_FUNC_DEFS
#undef YY_TRADITIONAL_FUNC_DEFS
#endif

/* The "const" storage-class-modifier is valid. */
#define YY_USE_CONST

#else	/* ! __cplusplus */

/* We're not in a C++ compiler, so by default,
we generate C99 function defs, unless you explicitly ask
for traditional defs by defining YY_TRADITIONAL_FUNC_DEFS */

#if __STDC__

#define YY_USE_CONST

#endif	/* __STDC__ */
#endif	/* ! __cplusplus */

#ifdef YY_USE_CONST
#define yyconst const
#else
#define yyconst
#endif

/* For compilers that can't handle prototypes.
* e.g.,
* The function prototype
*    int foo(int x, char* y);
*
* ...should be written as
*    int foo YY_PARAMS((int x, char* y));
*
* ...which could possibly generate
*    int foo ();
*/
#ifdef YY_NO_PROTOS
#define YY_PARAMS(proto) ()
#else
#define YY_PARAMS(proto) proto
#endif


/* Returned upon end-of-file. */
#define YY_NULL 0

/* Promotes a possibly negative, possibly signed char to an unsigned
* integer for use as an array index.  If the signed char is negative,
* we want to instead treat it as an 8-bit unsigned char, hence the
* double cast.
*/
#define YY_SC_TO_UI(c) ((unsigned int) (unsigned char) c)


/* An opaque pointer. */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

/* For use wherever a Global is accessed or assigned. */
#define YY_G(var) (((struct yyguts_t*)yyscanner)->var)

/* For use in function prototypes to append the additional argument. */
#define YY_PROTO_LAST_ARG , yyscan_t yyscanner
#define YY_PROTO_ONLY_ARG    yyscan_t yyscanner

/* For use in function definitions to append the additional argument. */
#ifdef YY_TRADITIONAL_FUNC_DEFS
#define YY_DEF_LAST_ARG , yyscanner
#define YY_DEF_ONLY_ARG    yyscanner
#else
#define YY_DEF_LAST_ARG , yyscan_t yyscanner
#define YY_DEF_ONLY_ARG   yyscan_t yyscanner
#endif
#define YY_DECL_LAST_ARG yyscan_t yyscanner;

/* For use in function calls to pass the additional argument. */
#define YY_CALL_LAST_ARG  , yyscanner
#define YY_CALL_ONLY_ARG   yyscanner

/* For convenience, these vars (plus the bison vars far below)
are macros in the reentrant scanner. */
#define yyin YY_G(yyin_r)
#define yyout YY_G(yyout_r)
#define yyextra YY_G(yyextra_r)
#define yyleng YY_G(yyleng_r)
#define yytext YY_G(yytext_r)
#define yylineno YY_G(yylineno_r)
#define yy_flex_debug YY_G(yy_flex_debug_r)

int yylex_init YY_PARAMS((yyscan_t* scanner));



/* For compilers that need traditional function definitions.
* e.g.,
* The function prototype taking 2 arguments
*    int foo (int x, char* y)
*
* ...should be written as
*    int foo YYFARGS2(int,x, char*,y)
*
* ...which could possibly generate
*    int foo (x,y,yyscanner)
*        int x;
*        char * y;
*        yyscan_t yyscanner;
*/
#ifdef YY_TRADITIONAL_FUNC_DEFS
/* Generate traditional function defs */
#define YYFARGS0(v) (YY_DEF_ONLY_ARG) YY_DECL_LAST_ARG
#define YYFARGS1(t1,n1) (n1 YY_DEF_LAST_ARG) t1 n1; YY_DECL_LAST_ARG
#define YYFARGS2(t1,n1,t2,n2) (n1,n2 YY_DEF_LAST_ARG) t1 n1; t2 n2; YY_DECL_LAST_ARG
#define YYFARGS3(t1,n1,t2,n2,t3,n3) (n1,n2,n3 YY_DEF_LAST_ARG) t1 n1; t2 n2; t3 n3; YY_DECL_LAST_ARG
#else
/* Generate C99 function defs. */
#define YYFARGS0(v) (YY_DEF_ONLY_ARG)
#define YYFARGS1(t1,n1) (t1 n1 YY_DEF_LAST_ARG)
#define YYFARGS2(t1,n1,t2,n2) (t1 n1,t2 n2 YY_DEF_LAST_ARG)
#define YYFARGS3(t1,n1,t2,n2,t3,n3) (t1 n1,t2 n2,t3 n3 YY_DEF_LAST_ARG)
#endif

/* Enter a start condition.  This macro really ought to take a parameter,
* but we do it the disgusting crufty way forced on us by the ()-less
* definition of BEGIN.
*/
#define BEGIN YY_G(yy_start) = 1 + 2 *

/* Translate the current start state into a value that can be later handed
* to BEGIN to return to the state.  The YYSTATE alias is for lex
* compatibility.
*/
#define YY_START ((YY_G(yy_start) - 1) / 2)
#define YYSTATE YY_START

/* Action number for EOF rule of a given start state. */
#define YY_STATE_EOF(state) (YY_END_OF_BUFFER + state + 1)

/* Special action meaning "start processing a new file". */
#define YY_NEW_FILE yyrestart( yyin YY_CALL_LAST_ARG )

#define YY_END_OF_BUFFER_CHAR 0

/* Size of default input buffer. */
#ifndef YY_BUF_SIZE
#define YY_BUF_SIZE 16384
#endif


#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif



#define EOB_ACT_CONTINUE_SCAN 0
#define EOB_ACT_END_OF_FILE 1
#define EOB_ACT_LAST_MATCH 2

#ifdef YY_USE_LINENO
/* Note: We specifically omit the test for yy_rule_can_match_eol because it requires
*       access to the local variable yy_act. Since yyless() is a macro, it would break
*       existing scanners that call yyless() from OUTSIDE yylex. 
*       One obvious solution it to make yy_act a global. I tried that, and saw
*       a 5% performance hit in a non-yylineno scanner, because yy_act is
*       normally declared as a register variable-- so it's not worth it.
*/
#define  YY_LESS_LINENO(n) \
	do { \
	int yyl;\
	for ( yyl = n; yyl < yyleng; ++yyl )\
	if ( yytext[yyl] == '\n' )\
	--yylineno;\
	}while(0)
#else
#define YY_LESS_LINENO(n)
#endif

/* The funky do-while in the following #define is used to turn the definition
* int a single C statement (which needs a semi-colon terminator).  This
* avoids problems with code like:
*
* 	if ( condition_holds )
*		yyless( 5 );
*	else
*		do_something_else();
*
* Prior to using the do-while the compiler would get upset at the
* "else" because it interpreted the "if" statement as being all
* done when it reached the ';' after the yyless() call.
*/

/* Return all but the first 'n' matched characters back to the input stream. */

#define yyless(n) \
	do \
{ \
	/* Undo effects of setting up yytext. */ \
	int yyless_macro_arg = (n); \
	YY_LESS_LINENO(yyless_macro_arg);\
	*yy_cp = YY_G(yy_hold_char); \
	YY_RESTORE_YY_MORE_OFFSET \
	YY_G(yy_c_buf_p) = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
	YY_DO_BEFORE_ACTION; /* set up yytext again */ \
} \
	while ( 0 )

#define unput(c) yyunput( c, YY_G(yytext_ptr) YY_CALL_LAST_ARG )

/* The following is because we cannot portably get our hands on size_t
* (without autoconf's help, which isn't available because we want
* flex-generated scanners to compile on their own).
*/

#ifndef YY_TYPEDEF_YY_SIZE_T
#define YY_TYPEDEF_YY_SIZE_T
typedef unsigned int yy_size_t;
#endif

#ifndef YY_STRUCT_YY_BUFFER_STATE
#define YY_STRUCT_YY_BUFFER_STATE
struct yy_buffer_state
{
	FILE *yy_input_file;



	char *yy_ch_buf;		/* input buffer */
	char *yy_buf_pos;		/* current position in input buffer */

	/* Size of input buffer in bytes, not including room for EOB
	* characters.
	*/
	yy_size_t yy_buf_size;

	/* Number of characters read into yy_ch_buf, not including EOB
	* characters.
	*/
	int yy_n_chars;

	/* Whether we "own" the buffer - i.e., we know we created it,
	* and can realloc() it to grow it, and should free() it to
	* delete it.
	*/
	int yy_is_our_buffer;

	/* Whether ptrThis is an "interactive" input source; if so, and
	* if we're using stdio for input, then we want to use getc()
	* instead of fread(), to make sure we stop fetching input after
	* each newline.
	*/
	int yy_is_interactive;

	/* Whether we're considered to be at the beginning of a line.
	* If so, '^' rules will be active on the next match, otherwise
	* not.
	*/
	int yy_at_bol;

	/* Whether to try to fill the input buffer when we reach the
	* end of it.
	*/
	int yy_fill_buffer;

	int yy_buffer_status;
#define YY_BUFFER_NEW 0
#define YY_BUFFER_NORMAL 1
	/* When an EOF's been seen but there's still some text to process
	* then we mark the buffer as YY_EOF_PENDING, to indicate that we
	* shouldn't try reading from the input source any more.  We might
	* still have a bunch of tokens to match, though, because of
	* possible backing-up.
	*
	* When we actually see the EOF, we change the status to "new"
	* (via yyrestart()), so that the user can continue scanning by
	* just pointing yyin at a new input file.
	*/
#define YY_BUFFER_EOF_PENDING 2
};
#endif /* !YY_STRUCT_YY_BUFFER_STATE */

#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */

/* We provide macros for accessing buffer states in case in the
* future we want to put the buffer states in a more general
* "scanner state".
*/
#define YY_CURRENT_BUFFER yy_current_buffer


#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */

void yyrestart YY_PARAMS(( FILE *input_file YY_PROTO_LAST_ARG ));


void yy_switch_to_buffer YY_PARAMS(( YY_BUFFER_STATE new_buffer YY_PROTO_LAST_ARG ));
void yy_load_buffer_state YY_PARAMS(( YY_PROTO_ONLY_ARG ));
YY_BUFFER_STATE yy_create_buffer YY_PARAMS(( FILE *file, int size YY_PROTO_LAST_ARG ));
void yy_delete_buffer YY_PARAMS(( YY_BUFFER_STATE b YY_PROTO_LAST_ARG ));
void yy_init_buffer YY_PARAMS(( YY_BUFFER_STATE b, FILE *file YY_PROTO_LAST_ARG ));
void yy_flush_buffer YY_PARAMS(( YY_BUFFER_STATE b YY_PROTO_LAST_ARG ));

#define YY_FLUSH_BUFFER yy_flush_buffer( YY_G(yy_current_buffer) YY_CALL_LAST_ARG)

YY_BUFFER_STATE yy_scan_buffer YY_PARAMS(( char *base, yy_size_t size YY_PROTO_LAST_ARG ));
YY_BUFFER_STATE yy_scan_string YY_PARAMS(( yyconst char *yy_str YY_PROTO_LAST_ARG ));
YY_BUFFER_STATE yy_scan_bytes YY_PARAMS(( yyconst char *bytes, int len YY_PROTO_LAST_ARG ));


void *yyalloc YY_PARAMS(( yy_size_t YY_PROTO_LAST_ARG ));
void *yyrealloc YY_PARAMS(( void *, yy_size_t YY_PROTO_LAST_ARG ));
void yyfree YY_PARAMS(( void * YY_PROTO_LAST_ARG ));

#define yy_new_buffer yy_create_buffer

#define yy_set_interactive(is_interactive) \
{ \
	if ( ! YY_G(yy_current_buffer) ) \
	YY_G(yy_current_buffer) =    \
	yy_create_buffer( yyin, YY_BUF_SIZE YY_CALL_LAST_ARG); \
	YY_G(yy_current_buffer)->yy_is_interactive = is_interactive; \
}

#define yy_set_bol(at_bol) \
{ \
	if ( ! YY_G(yy_current_buffer) ) \
	YY_G(yy_current_buffer) =    \
	yy_create_buffer( yyin, YY_BUF_SIZE YY_CALL_LAST_ARG); \
	YY_G(yy_current_buffer)->yy_at_bol = at_bol; \
}

#define YY_AT_BOL() (YY_G(yy_current_buffer)->yy_at_bol)


#define yywrap(n) 1
#define YY_SKIP_YYWRAP
#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
typedef unsigned char YY_CHAR;
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */
#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
#ifndef YY_REENTRANT
FILE *yyin = (FILE *) 0, *yyout = (FILE *) 0;
#endif
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */
#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
typedef yyconst struct yy_trans_info *yy_state_type;
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */
#define yytext_ptr yytext_r

#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
static yy_state_type yy_get_previous_state YY_PARAMS(( YY_PROTO_ONLY_ARG ));
static yy_state_type yy_try_NUL_trans YY_PARAMS(( yy_state_type current_state  YY_PROTO_LAST_ARG));
static int yy_get_next_buffer YY_PARAMS(( YY_PROTO_ONLY_ARG ));
static void yy_fatal_error YY_PARAMS(( yyconst char msg[] YY_PROTO_LAST_ARG ));
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */

/* Done after the current pattern has been matched and before the
* corresponding action - sets up yytext.
*/
#define YY_DO_BEFORE_ACTION \
	YY_G(yytext_ptr) = yy_bp; \
	yyleng = (size_t) (yy_cp - yy_bp); \
	YY_G(yy_hold_char) = *yy_cp; \
	*yy_cp = '\0'; \
	YY_G(yy_c_buf_p) = yy_cp;

#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
#define YY_NUM_RULES 15
#define YY_END_OF_BUFFER 16
struct yy_trans_info
{
	flex_int16_t yy_verify;
	flex_int16_t yy_nxt;
};
static yyconst struct yy_trans_info yy_transition[7736] =
{
	{   0,   0 }, {   0,7480 }, {   0,   0 }, {   0,7478 }, {   1,1032 },
	{   2,1032 }, {   3,1032 }, {   4,1032 }, {   5,1032 }, {   6,1032 },
	{   7,1032 }, {   8,1032 }, {   9,1034 }, {  10,1036 }, {  11,1032 },
	{  12,1032 }, {  13,1041 }, {  14,1032 }, {  15,1032 }, {  16,1032 },
	{  17,1032 }, {  18,1032 }, {  19,1032 }, {  20,1032 }, {  21,1032 },
	{  22,1032 }, {  23,1032 }, {  24,1032 }, {  25,1032 }, {  26,1032 },
	{  27,1032 }, {  28,1032 }, {  29,1032 }, {  30,1032 }, {  31,1032 },
	{  32,1034 }, {  33,1032 }, {  34,1103 }, {  35,1032 }, {  36,1032 },
	{  37,1032 }, {  38,1032 }, {  39,1361 }, {  40,1032 }, {  41,1032 },
	{  42,1032 }, {  43,1032 }, {  44,1032 }, {  45,1032 }, {  46,1032 },

	{  47,1038 }, {  48,1032 }, {  49,1032 }, {  50,1032 }, {  51,1032 },
	{  52,1032 }, {  53,1032 }, {  54,1032 }, {  55,1032 }, {  56,1032 },
	{  57,1032 }, {  58,1032 }, {  59,1032 }, {  60,1619 }, {  61,1053 },
	{  62,1061 }, {  63,1079 }, {  64,1032 }, {  65,1876 }, {  66,1876 },
	{  67,1876 }, {  68,1876 }, {  69,1876 }, {  70,1876 }, {  71,1876 },
	{  72,1876 }, {  73,1876 }, {  74,1876 }, {  75,1876 }, {  76,1876 },
	{  77,1876 }, {  78,1876 }, {  79,1876 }, {  80,1876 }, {  81,1876 },
	{  82,1876 }, {  83,1876 }, {  84,1876 }, {  85,1876 }, {  86,1876 },
	{  87,1876 }, {  88,1876 }, {  89,1876 }, {  90,1876 }, {  91,1032 },
	{  92,1032 }, {  93,1032 }, {  94,1032 }, {  95,1876 }, {  96,1032 },

	{  97,1876 }, {  98,1876 }, {  99,1876 }, { 100,1876 }, { 101,1876 },
	{ 102,1876 }, { 103,1876 }, { 104,1876 }, { 105,1876 }, { 106,1876 },
	{ 107,1876 }, { 108,1876 }, { 109,1876 }, { 110,1876 }, { 111,1876 },
	{ 112,1876 }, { 113,1876 }, { 114,1876 }, { 115,1876 }, { 116,1876 },
	{ 117,1876 }, { 118,1876 }, { 119,1876 }, { 120,1876 }, { 121,1876 },
	{ 122,1876 }, { 123,1032 }, { 124,1032 }, { 125,1032 }, { 126,1032 },
	{ 127,1032 }, { 128,1876 }, { 129,1876 }, { 130,1876 }, { 131,1876 },
	{ 132,1876 }, { 133,1876 }, { 134,1876 }, { 135,1876 }, { 136,1876 },
	{ 137,1876 }, { 138,1876 }, { 139,1876 }, { 140,1876 }, { 141,1876 },
	{ 142,1876 }, { 143,1876 }, { 144,1876 }, { 145,1876 }, { 146,1876 },

	{ 147,1876 }, { 148,1876 }, { 149,1876 }, { 150,1876 }, { 151,1876 },
	{ 152,1876 }, { 153,1876 }, { 154,1876 }, { 155,1876 }, { 156,1876 },
	{ 157,1876 }, { 158,1876 }, { 159,1876 }, { 160,1876 }, { 161,1876 },
	{ 162,1876 }, { 163,1876 }, { 164,1876 }, { 165,1876 }, { 166,1876 },
	{ 167,1876 }, { 168,1876 }, { 169,1876 }, { 170,1876 }, { 171,1876 },
	{ 172,1876 }, { 173,1876 }, { 174,1876 }, { 175,1876 }, { 176,1876 },
	{ 177,1876 }, { 178,1876 }, { 179,1876 }, { 180,1876 }, { 181,1876 },
	{ 182,1876 }, { 183,1876 }, { 184,1876 }, { 185,1876 }, { 186,1876 },
	{ 187,1876 }, { 188,1876 }, { 189,1876 }, { 190,1876 }, { 191,1876 },
	{ 192,1876 }, { 193,1876 }, { 194,1876 }, { 195,1876 }, { 196,1876 },

	{ 197,1876 }, { 198,1876 }, { 199,1876 }, { 200,1876 }, { 201,1876 },
	{ 202,1876 }, { 203,1876 }, { 204,1876 }, { 205,1876 }, { 206,1876 },
	{ 207,1876 }, { 208,1876 }, { 209,1876 }, { 210,1876 }, { 211,1876 },
	{ 212,1876 }, { 213,1876 }, { 214,1876 }, { 215,1876 }, { 216,1876 },
	{ 217,1876 }, { 218,1876 }, { 219,1876 }, { 220,1876 }, { 221,1876 },
	{ 222,1876 }, { 223,1876 }, { 224,1876 }, { 225,1876 }, { 226,1876 },
	{ 227,1876 }, { 228,1876 }, { 229,1876 }, { 230,1876 }, { 231,1876 },
	{ 232,1876 }, { 233,1876 }, { 234,1876 }, { 235,1876 }, { 236,1876 },
	{ 237,1876 }, { 238,1876 }, { 239,1876 }, { 240,1876 }, { 241,1876 },
	{ 242,1876 }, { 243,1876 }, { 244,1876 }, { 245,1876 }, { 246,1876 },

	{ 247,1876 }, { 248,1876 }, { 249,1876 }, { 250,1876 }, { 251,1876 },
	{ 252,1876 }, { 253,1876 }, { 254,1876 }, { 255,1876 }, { 256,1032 },
	{   0,   0 }, {   0,7220 }, {   1, 774 }, {   2, 774 }, {   3, 774 },
	{   4, 774 }, {   5, 774 }, {   6, 774 }, {   7, 774 }, {   8, 774 },
	{   9, 776 }, {  10, 778 }, {  11, 774 }, {  12, 774 }, {  13, 783 },
	{  14, 774 }, {  15, 774 }, {  16, 774 }, {  17, 774 }, {  18, 774 },
	{  19, 774 }, {  20, 774 }, {  21, 774 }, {  22, 774 }, {  23, 774 },
	{  24, 774 }, {  25, 774 }, {  26, 774 }, {  27, 774 }, {  28, 774 },
	{  29, 774 }, {  30, 774 }, {  31, 774 }, {  32, 776 }, {  33, 774 },
	{  34, 845 }, {  35, 774 }, {  36, 774 }, {  37, 774 }, {  38, 774 },

	{  39,1103 }, {  40, 774 }, {  41, 774 }, {  42, 774 }, {  43, 774 },
	{  44, 774 }, {  45, 774 }, {  46, 774 }, {  47, 780 }, {  48, 774 },
	{  49, 774 }, {  50, 774 }, {  51, 774 }, {  52, 774 }, {  53, 774 },
	{  54, 774 }, {  55, 774 }, {  56, 774 }, {  57, 774 }, {  58, 774 },
	{  59, 774 }, {  60,1361 }, {  61, 795 }, {  62, 803 }, {  63, 821 },
	{  64, 774 }, {  65,1618 }, {  66,1618 }, {  67,1618 }, {  68,1618 },
	{  69,1618 }, {  70,1618 }, {  71,1618 }, {  72,1618 }, {  73,1618 },
	{  74,1618 }, {  75,1618 }, {  76,1618 }, {  77,1618 }, {  78,1618 },
	{  79,1618 }, {  80,1618 }, {  81,1618 }, {  82,1618 }, {  83,1618 },
	{  84,1618 }, {  85,1618 }, {  86,1618 }, {  87,1618 }, {  88,1618 },

	{  89,1618 }, {  90,1618 }, {  91, 774 }, {  92, 774 }, {  93, 774 },
	{  94, 774 }, {  95,1618 }, {  96, 774 }, {  97,1618 }, {  98,1618 },
	{  99,1618 }, { 100,1618 }, { 101,1618 }, { 102,1618 }, { 103,1618 },
	{ 104,1618 }, { 105,1618 }, { 106,1618 }, { 107,1618 }, { 108,1618 },
	{ 109,1618 }, { 110,1618 }, { 111,1618 }, { 112,1618 }, { 113,1618 },
	{ 114,1618 }, { 115,1618 }, { 116,1618 }, { 117,1618 }, { 118,1618 },
	{ 119,1618 }, { 120,1618 }, { 121,1618 }, { 122,1618 }, { 123, 774 },
	{ 124, 774 }, { 125, 774 }, { 126, 774 }, { 127, 774 }, { 128,1618 },
	{ 129,1618 }, { 130,1618 }, { 131,1618 }, { 132,1618 }, { 133,1618 },
	{ 134,1618 }, { 135,1618 }, { 136,1618 }, { 137,1618 }, { 138,1618 },

	{ 139,1618 }, { 140,1618 }, { 141,1618 }, { 142,1618 }, { 143,1618 },
	{ 144,1618 }, { 145,1618 }, { 146,1618 }, { 147,1618 }, { 148,1618 },
	{ 149,1618 }, { 150,1618 }, { 151,1618 }, { 152,1618 }, { 153,1618 },
	{ 154,1618 }, { 155,1618 }, { 156,1618 }, { 157,1618 }, { 158,1618 },
	{ 159,1618 }, { 160,1618 }, { 161,1618 }, { 162,1618 }, { 163,1618 },
	{ 164,1618 }, { 165,1618 }, { 166,1618 }, { 167,1618 }, { 168,1618 },
	{ 169,1618 }, { 170,1618 }, { 171,1618 }, { 172,1618 }, { 173,1618 },
	{ 174,1618 }, { 175,1618 }, { 176,1618 }, { 177,1618 }, { 178,1618 },
	{ 179,1618 }, { 180,1618 }, { 181,1618 }, { 182,1618 }, { 183,1618 },
	{ 184,1618 }, { 185,1618 }, { 186,1618 }, { 187,1618 }, { 188,1618 },

	{ 189,1618 }, { 190,1618 }, { 191,1618 }, { 192,1618 }, { 193,1618 },
	{ 194,1618 }, { 195,1618 }, { 196,1618 }, { 197,1618 }, { 198,1618 },
	{ 199,1618 }, { 200,1618 }, { 201,1618 }, { 202,1618 }, { 203,1618 },
	{ 204,1618 }, { 205,1618 }, { 206,1618 }, { 207,1618 }, { 208,1618 },
	{ 209,1618 }, { 210,1618 }, { 211,1618 }, { 212,1618 }, { 213,1618 },
	{ 214,1618 }, { 215,1618 }, { 216,1618 }, { 217,1618 }, { 218,1618 },
	{ 219,1618 }, { 220,1618 }, { 221,1618 }, { 222,1618 }, { 223,1618 },
	{ 224,1618 }, { 225,1618 }, { 226,1618 }, { 227,1618 }, { 228,1618 },
	{ 229,1618 }, { 230,1618 }, { 231,1618 }, { 232,1618 }, { 233,1618 },
	{ 234,1618 }, { 235,1618 }, { 236,1618 }, { 237,1618 }, { 238,1618 },

	{ 239,1618 }, { 240,1618 }, { 241,1618 }, { 242,1618 }, { 243,1618 },
	{ 244,1618 }, { 245,1618 }, { 246,1618 }, { 247,1618 }, { 248,1618 },
	{ 249,1618 }, { 250,1618 }, { 251,1618 }, { 252,1618 }, { 253,1618 },
	{ 254,1618 }, { 255,1618 }, { 256, 774 }, {   0,   0 }, {   0,6962 },
	{   1,1617 }, {   2,1617 }, {   3,1617 }, {   4,1617 }, {   5,1617 },
	{   6,1617 }, {   7,1617 }, {   8,1617 }, {   9,1875 }, {  10,2133 },
	{  11,1617 }, {  12,1617 }, {  13,2195 }, {  14,1617 }, {  15,1617 },
	{  16,1617 }, {  17,1617 }, {  18,1617 }, {  19,1617 }, {  20,1617 },
	{  21,1617 }, {  22,1617 }, {  23,1617 }, {  24,1617 }, {  25,1617 },
	{  26,1617 }, {  27,1617 }, {  28,1617 }, {  29,1617 }, {  30,1617 },

	{  31,1617 }, {  32,1875 }, {  33,1617 }, {  34,1617 }, {  35,1617 },
	{  36,1617 }, {  37,1617 }, {  38, 516 }, {  39,1617 }, {  40,1617 },
	{  41,1617 }, {  42,1617 }, {  43,1617 }, {  44,1617 }, {  45,1617 },
	{  46,1617 }, {  47,1617 }, {  48,1617 }, {  49,1617 }, {  50,1617 },
	{  51,1617 }, {  52,1617 }, {  53,1617 }, {  54,1617 }, {  55,1617 },
	{  56,1617 }, {  57,1617 }, {  58,1617 }, {  59,1617 }, {  60,1103 },
	{  61,1617 }, {  62,1617 }, {  63,1617 }, {  64,1617 }, {  65,1617 },
	{  66,1617 }, {  67,1617 }, {  68,1617 }, {  69,1617 }, {  70,1617 },
	{  71,1617 }, {  72,1617 }, {  73,1617 }, {  74,1617 }, {  75,1617 },
	{  76,1617 }, {  77,1617 }, {  78,1617 }, {  79,1617 }, {  80,1617 },

	{  81,1617 }, {  82,1617 }, {  83,1617 }, {  84,1617 }, {  85,1617 },
	{  86,1617 }, {  87,1617 }, {  88,1617 }, {  89,1617 }, {  90,1617 },
	{  91,1617 }, {  92,1617 }, {  93,1617 }, {  94,1617 }, {  95,1617 },
	{  96,1617 }, {  97,1617 }, {  98,1617 }, {  99,1617 }, { 100,1617 },
	{ 101,1617 }, { 102,1617 }, { 103,1617 }, { 104,1617 }, { 105,1617 },
	{ 106,1617 }, { 107,1617 }, { 108,1617 }, { 109,1617 }, { 110,1617 },
	{ 111,1617 }, { 112,1617 }, { 113,1617 }, { 114,1617 }, { 115,1617 },
	{ 116,1617 }, { 117,1617 }, { 118,1617 }, { 119,1617 }, { 120,1617 },
	{ 121,1617 }, { 122,1617 }, { 123,1617 }, { 124,1617 }, { 125,1617 },
	{ 126,1617 }, { 127,1617 }, { 128,1617 }, { 129,1617 }, { 130,1617 },

	{ 131,1617 }, { 132,1617 }, { 133,1617 }, { 134,1617 }, { 135,1617 },
	{ 136,1617 }, { 137,1617 }, { 138,1617 }, { 139,1617 }, { 140,1617 },
	{ 141,1617 }, { 142,1617 }, { 143,1617 }, { 144,1617 }, { 145,1617 },
	{ 146,1617 }, { 147,1617 }, { 148,1617 }, { 149,1617 }, { 150,1617 },
	{ 151,1617 }, { 152,1617 }, { 153,1617 }, { 154,1617 }, { 155,1617 },
	{ 156,1617 }, { 157,1617 }, { 158,1617 }, { 159,1617 }, { 160,1617 },
	{ 161,1617 }, { 162,1617 }, { 163,1617 }, { 164,1617 }, { 165,1617 },
	{ 166,1617 }, { 167,1617 }, { 168,1617 }, { 169,1617 }, { 170,1617 },
	{ 171,1617 }, { 172,1617 }, { 173,1617 }, { 174,1617 }, { 175,1617 },
	{ 176,1617 }, { 177,1617 }, { 178,1617 }, { 179,1617 }, { 180,1617 },

	{ 181,1617 }, { 182,1617 }, { 183,1617 }, { 184,1617 }, { 185,1617 },
	{ 186,1617 }, { 187,1617 }, { 188,1617 }, { 189,1617 }, { 190,1617 },
	{ 191,1617 }, { 192,1617 }, { 193,1617 }, { 194,1617 }, { 195,1617 },
	{ 196,1617 }, { 197,1617 }, { 198,1617 }, { 199,1617 }, { 200,1617 },
	{ 201,1617 }, { 202,1617 }, { 203,1617 }, { 204,1617 }, { 205,1617 },
	{ 206,1617 }, { 207,1617 }, { 208,1617 }, { 209,1617 }, { 210,1617 },
	{ 211,1617 }, { 212,1617 }, { 213,1617 }, { 214,1617 }, { 215,1617 },
	{ 216,1617 }, { 217,1617 }, { 218,1617 }, { 219,1617 }, { 220,1617 },
	{ 221,1617 }, { 222,1617 }, { 223,1617 }, { 224,1617 }, { 225,1617 },
	{ 226,1617 }, { 227,1617 }, { 228,1617 }, { 229,1617 }, { 230,1617 },

	{ 231,1617 }, { 232,1617 }, { 233,1617 }, { 234,1617 }, { 235,1617 },
	{ 236,1617 }, { 237,1617 }, { 238,1617 }, { 239,1617 }, { 240,1617 },
	{ 241,1617 }, { 242,1617 }, { 243,1617 }, { 244,1617 }, { 245,1617 },
	{ 246,1617 }, { 247,1617 }, { 248,1617 }, { 249,1617 }, { 250,1617 },
	{ 251,1617 }, { 252,1617 }, { 253,1617 }, { 254,1617 }, { 255,1617 },
	{ 256,1617 }, {   0,   0 }, {   0,6704 }, {   1,1359 }, {   2,1359 },
	{   3,1359 }, {   4,1359 }, {   5,1359 }, {   6,1359 }, {   7,1359 },
	{   8,1359 }, {   9,1617 }, {  10,1875 }, {  11,1359 }, {  12,1359 },
	{  13,1937 }, {  14,1359 }, {  15,1359 }, {  16,1359 }, {  17,1359 },
	{  18,1359 }, {  19,1359 }, {  20,1359 }, {  21,1359 }, {  22,1359 },

	{  23,1359 }, {  24,1359 }, {  25,1359 }, {  26,1359 }, {  27,1359 },
	{  28,1359 }, {  29,1359 }, {  30,1359 }, {  31,1359 }, {  32,1617 },
	{  33,1359 }, {  34,1359 }, {  35,1359 }, {  36,1359 }, {  37,1359 },
	{  38, 258 }, {  39,1359 }, {  40,1359 }, {  41,1359 }, {  42,1359 },
	{  43,1359 }, {  44,1359 }, {  45,1359 }, {  46,1359 }, {  47,1359 },
	{  48,1359 }, {  49,1359 }, {  50,1359 }, {  51,1359 }, {  52,1359 },
	{  53,1359 }, {  54,1359 }, {  55,1359 }, {  56,1359 }, {  57,1359 },
	{  58,1359 }, {  59,1359 }, {  60, 845 }, {  61,1359 }, {  62,1359 },
	{  63,1359 }, {  64,1359 }, {  65,1359 }, {  66,1359 }, {  67,1359 },
	{  68,1359 }, {  69,1359 }, {  70,1359 }, {  71,1359 }, {  72,1359 },

	{  73,1359 }, {  74,1359 }, {  75,1359 }, {  76,1359 }, {  77,1359 },
	{  78,1359 }, {  79,1359 }, {  80,1359 }, {  81,1359 }, {  82,1359 },
	{  83,1359 }, {  84,1359 }, {  85,1359 }, {  86,1359 }, {  87,1359 },
	{  88,1359 }, {  89,1359 }, {  90,1359 }, {  91,1359 }, {  92,1359 },
	{  93,1359 }, {  94,1359 }, {  95,1359 }, {  96,1359 }, {  97,1359 },
	{  98,1359 }, {  99,1359 }, { 100,1359 }, { 101,1359 }, { 102,1359 },
	{ 103,1359 }, { 104,1359 }, { 105,1359 }, { 106,1359 }, { 107,1359 },
	{ 108,1359 }, { 109,1359 }, { 110,1359 }, { 111,1359 }, { 112,1359 },
	{ 113,1359 }, { 114,1359 }, { 115,1359 }, { 116,1359 }, { 117,1359 },
	{ 118,1359 }, { 119,1359 }, { 120,1359 }, { 121,1359 }, { 122,1359 },

	{ 123,1359 }, { 124,1359 }, { 125,1359 }, { 126,1359 }, { 127,1359 },
	{ 128,1359 }, { 129,1359 }, { 130,1359 }, { 131,1359 }, { 132,1359 },
	{ 133,1359 }, { 134,1359 }, { 135,1359 }, { 136,1359 }, { 137,1359 },
	{ 138,1359 }, { 139,1359 }, { 140,1359 }, { 141,1359 }, { 142,1359 },
	{ 143,1359 }, { 144,1359 }, { 145,1359 }, { 146,1359 }, { 147,1359 },
	{ 148,1359 }, { 149,1359 }, { 150,1359 }, { 151,1359 }, { 152,1359 },
	{ 153,1359 }, { 154,1359 }, { 155,1359 }, { 156,1359 }, { 157,1359 },
	{ 158,1359 }, { 159,1359 }, { 160,1359 }, { 161,1359 }, { 162,1359 },
	{ 163,1359 }, { 164,1359 }, { 165,1359 }, { 166,1359 }, { 167,1359 },
	{ 168,1359 }, { 169,1359 }, { 170,1359 }, { 171,1359 }, { 172,1359 },

	{ 173,1359 }, { 174,1359 }, { 175,1359 }, { 176,1359 }, { 177,1359 },
	{ 178,1359 }, { 179,1359 }, { 180,1359 }, { 181,1359 }, { 182,1359 },
	{ 183,1359 }, { 184,1359 }, { 185,1359 }, { 186,1359 }, { 187,1359 },
	{ 188,1359 }, { 189,1359 }, { 190,1359 }, { 191,1359 }, { 192,1359 },
	{ 193,1359 }, { 194,1359 }, { 195,1359 }, { 196,1359 }, { 197,1359 },
	{ 198,1359 }, { 199,1359 }, { 200,1359 }, { 201,1359 }, { 202,1359 },
	{ 203,1359 }, { 204,1359 }, { 205,1359 }, { 206,1359 }, { 207,1359 },
	{ 208,1359 }, { 209,1359 }, { 210,1359 }, { 211,1359 }, { 212,1359 },
	{ 213,1359 }, { 214,1359 }, { 215,1359 }, { 216,1359 }, { 217,1359 },
	{ 218,1359 }, { 219,1359 }, { 220,1359 }, { 221,1359 }, { 222,1359 },

	{ 223,1359 }, { 224,1359 }, { 225,1359 }, { 226,1359 }, { 227,1359 },
	{ 228,1359 }, { 229,1359 }, { 230,1359 }, { 231,1359 }, { 232,1359 },
	{ 233,1359 }, { 234,1359 }, { 235,1359 }, { 236,1359 }, { 237,1359 },
	{ 238,1359 }, { 239,1359 }, { 240,1359 }, { 241,1359 }, { 242,1359 },
	{ 243,1359 }, { 244,1359 }, { 245,1359 }, { 246,1359 }, { 247,1359 },
	{ 248,1359 }, { 249,1359 }, { 250,1359 }, { 251,1359 }, { 252,1359 },
	{ 253,1359 }, { 254,1359 }, { 255,1359 }, { 256,1359 }, {   0,  13 },
	{   0,6446 }, {   0,   1 }, {   0,6444 }, {   0,   1 }, {   0,6442 },
	{   0,   2 }, {   0,6440 }, {   0,   0 }, {   0,   1 }, {   0,6437 },
	{   0,   0 }, {   9,1935 }, {  10,1935 }, {   9,1933 }, {  10,1933 },

	{  13,1935 }, {   0,   0 }, {  13,1933 }, {   9,1928 }, {  10,2187 },
	{   0,   3 }, {   0,6425 }, {  13,1928 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   4 }, {   0,6417 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  32,1935 },
	{   0,   0 }, {  32,1933 }, {   0,   0 }, {   9, 560 }, {  10, 560 },
	{   0,   0 }, {  32,1928 }, {  13, 560 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,  13 }, {   0,6399 }, {   0,   6 }, {   0,6397 },
	{   0,   9 }, {   0,6395 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {  32, 560 }, {  60,1937 }, {   0,   0 }, {  60,1935 },

	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  60,1930 },
	{   0,  13 }, {   0,6375 }, {   1,2187 }, {   2,2187 }, {   3,2187 },
	{   4,2187 }, {   5,2187 }, {   6,2187 }, {   7,2187 }, {   8,2187 },
	{   9,2187 }, {  10,2187 }, {  11,2187 }, {  12,2187 }, {  13,2187 },
	{  14,2187 }, {  15,2187 }, {  16,2187 }, {  17,2187 }, {  18,2187 },
	{  19,2187 }, {  20,2187 }, {  21,2187 }, {  22,2187 }, {  23,2187 },
	{  24,2187 }, {  25,2187 }, {  26,2187 }, {  27,2187 }, {  28,2187 },
	{  29,2187 }, {  30,2187 }, {  31,2187 }, {  32,2187 }, {  33,2187 },
	{  34, -22 }, {  35,2187 }, {  36,2187 }, {  37,2187 }, {  62, 547 },
	{  39,2187 }, {  40,2187 }, {  41,2187 }, {  42,2187 }, {  43,2187 },

	{  44,2187 }, {  45,2187 }, {  46,2187 }, {  47,2187 }, {  48,2187 },
	{  49,2187 }, {  50,2187 }, {  51,2187 }, {  52,2187 }, {  53,2187 },
	{  54,2187 }, {  55,2187 }, {  56,2187 }, {  57,2187 }, {  58,2187 },
	{  59,2187 }, {  60,2187 }, {  61,2187 }, {  62,2187 }, {  63,2187 },
	{  64,2187 }, {  65,2187 }, {  66,2187 }, {  67,2187 }, {  68,2187 },
	{  69,2187 }, {  70,2187 }, {  71,2187 }, {  72,2187 }, {  73,2187 },
	{  74,2187 }, {  75,2187 }, {  76,2187 }, {  77,2187 }, {  78,2187 },
	{  79,2187 }, {  80,2187 }, {  81,2187 }, {  82,2187 }, {  83,2187 },
	{  84,2187 }, {  85,2187 }, {  86,2187 }, {  87,2187 }, {  88,2187 },
	{  89,2187 }, {  90,2187 }, {  91,2187 }, {  92,2187 }, {  93,2187 },

	{  94,2187 }, {  95,2187 }, {  96,2187 }, {  97,2187 }, {  98,2187 },
	{  99,2187 }, { 100,2187 }, { 101,2187 }, { 102,2187 }, { 103,2187 },
	{ 104,2187 }, { 105,2187 }, { 106,2187 }, { 107,2187 }, { 108,2187 },
	{ 109,2187 }, { 110,2187 }, { 111,2187 }, { 112,2187 }, { 113,2187 },
	{ 114,2187 }, { 115,2187 }, { 116,2187 }, { 117,2187 }, { 118,2187 },
	{ 119,2187 }, { 120,2187 }, { 121,2187 }, { 122,2187 }, { 123,2187 },
	{ 124,2187 }, { 125,2187 }, { 126,2187 }, { 127,2187 }, { 128,2187 },
	{ 129,2187 }, { 130,2187 }, { 131,2187 }, { 132,2187 }, { 133,2187 },
	{ 134,2187 }, { 135,2187 }, { 136,2187 }, { 137,2187 }, { 138,2187 },
	{ 139,2187 }, { 140,2187 }, { 141,2187 }, { 142,2187 }, { 143,2187 },

	{ 144,2187 }, { 145,2187 }, { 146,2187 }, { 147,2187 }, { 148,2187 },
	{ 149,2187 }, { 150,2187 }, { 151,2187 }, { 152,2187 }, { 153,2187 },
	{ 154,2187 }, { 155,2187 }, { 156,2187 }, { 157,2187 }, { 158,2187 },
	{ 159,2187 }, { 160,2187 }, { 161,2187 }, { 162,2187 }, { 163,2187 },
	{ 164,2187 }, { 165,2187 }, { 166,2187 }, { 167,2187 }, { 168,2187 },
	{ 169,2187 }, { 170,2187 }, { 171,2187 }, { 172,2187 }, { 173,2187 },
	{ 174,2187 }, { 175,2187 }, { 176,2187 }, { 177,2187 }, { 178,2187 },
	{ 179,2187 }, { 180,2187 }, { 181,2187 }, { 182,2187 }, { 183,2187 },
	{ 184,2187 }, { 185,2187 }, { 186,2187 }, { 187,2187 }, { 188,2187 },
	{ 189,2187 }, { 190,2187 }, { 191,2187 }, { 192,2187 }, { 193,2187 },

	{ 194,2187 }, { 195,2187 }, { 196,2187 }, { 197,2187 }, { 198,2187 },
	{ 199,2187 }, { 200,2187 }, { 201,2187 }, { 202,2187 }, { 203,2187 },
	{ 204,2187 }, { 205,2187 }, { 206,2187 }, { 207,2187 }, { 208,2187 },
	{ 209,2187 }, { 210,2187 }, { 211,2187 }, { 212,2187 }, { 213,2187 },
	{ 214,2187 }, { 215,2187 }, { 216,2187 }, { 217,2187 }, { 218,2187 },
	{ 219,2187 }, { 220,2187 }, { 221,2187 }, { 222,2187 }, { 223,2187 },
	{ 224,2187 }, { 225,2187 }, { 226,2187 }, { 227,2187 }, { 228,2187 },
	{ 229,2187 }, { 230,2187 }, { 231,2187 }, { 232,2187 }, { 233,2187 },
	{ 234,2187 }, { 235,2187 }, { 236,2187 }, { 237,2187 }, { 238,2187 },
	{ 239,2187 }, { 240,2187 }, { 241,2187 }, { 242,2187 }, { 243,2187 },

	{ 244,2187 }, { 245,2187 }, { 246,2187 }, { 247,2187 }, { 248,2187 },
	{ 249,2187 }, { 250,2187 }, { 251,2187 }, { 252,2187 }, { 253,2187 },
	{ 254,2187 }, { 255,2187 }, { 256,2187 }, {   0,  13 }, {   0,6117 },
	{   1,2187 }, {   2,2187 }, {   3,2187 }, {   4,2187 }, {   5,2187 },
	{   6,2187 }, {   7,2187 }, {   8,2187 }, {   9,2187 }, {  10,2187 },
	{  11,2187 }, {  12,2187 }, {  13,2187 }, {  14,2187 }, {  15,2187 },
	{  16,2187 }, {  17,2187 }, {  18,2187 }, {  19,2187 }, {  20,2187 },
	{  21,2187 }, {  22,2187 }, {  23,2187 }, {  24,2187 }, {  25,2187 },
	{  26,2187 }, {  27,2187 }, {  28,2187 }, {  29,2187 }, {  30,2187 },
	{  31,2187 }, {  32,2187 }, {  33,2187 }, {  34,2187 }, {  35,2187 },

	{  36,2187 }, {  37,2187 }, {   0,   0 }, {  39,-280 }, {  40,2187 },
	{  41,2187 }, {  42,2187 }, {  43,2187 }, {  44,2187 }, {  45,2187 },
	{  46,2187 }, {  47,2187 }, {  48,2187 }, {  49,2187 }, {  50,2187 },
	{  51,2187 }, {  52,2187 }, {  53,2187 }, {  54,2187 }, {  55,2187 },
	{  56,2187 }, {  57,2187 }, {  58,2187 }, {  59,2187 }, {  60,2187 },
	{  61,2187 }, {  62,2187 }, {  63,2187 }, {  64,2187 }, {  65,2187 },
	{  66,2187 }, {  67,2187 }, {  68,2187 }, {  69,2187 }, {  70,2187 },
	{  71,2187 }, {  72,2187 }, {  73,2187 }, {  74,2187 }, {  75,2187 },
	{  76,2187 }, {  77,2187 }, {  78,2187 }, {  79,2187 }, {  80,2187 },
	{  81,2187 }, {  82,2187 }, {  83,2187 }, {  84,2187 }, {  85,2187 },

	{  86,2187 }, {  87,2187 }, {  88,2187 }, {  89,2187 }, {  90,2187 },
	{  91,2187 }, {  92,2187 }, {  93,2187 }, {  94,2187 }, {  95,2187 },
	{  96,2187 }, {  97,2187 }, {  98,2187 }, {  99,2187 }, { 100,2187 },
	{ 101,2187 }, { 102,2187 }, { 103,2187 }, { 104,2187 }, { 105,2187 },
	{ 106,2187 }, { 107,2187 }, { 108,2187 }, { 109,2187 }, { 110,2187 },
	{ 111,2187 }, { 112,2187 }, { 113,2187 }, { 114,2187 }, { 115,2187 },
	{ 116,2187 }, { 117,2187 }, { 118,2187 }, { 119,2187 }, { 120,2187 },
	{ 121,2187 }, { 122,2187 }, { 123,2187 }, { 124,2187 }, { 125,2187 },
	{ 126,2187 }, { 127,2187 }, { 128,2187 }, { 129,2187 }, { 130,2187 },
	{ 131,2187 }, { 132,2187 }, { 133,2187 }, { 134,2187 }, { 135,2187 },

	{ 136,2187 }, { 137,2187 }, { 138,2187 }, { 139,2187 }, { 140,2187 },
	{ 141,2187 }, { 142,2187 }, { 143,2187 }, { 144,2187 }, { 145,2187 },
	{ 146,2187 }, { 147,2187 }, { 148,2187 }, { 149,2187 }, { 150,2187 },
	{ 151,2187 }, { 152,2187 }, { 153,2187 }, { 154,2187 }, { 155,2187 },
	{ 156,2187 }, { 157,2187 }, { 158,2187 }, { 159,2187 }, { 160,2187 },
	{ 161,2187 }, { 162,2187 }, { 163,2187 }, { 164,2187 }, { 165,2187 },
	{ 166,2187 }, { 167,2187 }, { 168,2187 }, { 169,2187 }, { 170,2187 },
	{ 171,2187 }, { 172,2187 }, { 173,2187 }, { 174,2187 }, { 175,2187 },
	{ 176,2187 }, { 177,2187 }, { 178,2187 }, { 179,2187 }, { 180,2187 },
	{ 181,2187 }, { 182,2187 }, { 183,2187 }, { 184,2187 }, { 185,2187 },

	{ 186,2187 }, { 187,2187 }, { 188,2187 }, { 189,2187 }, { 190,2187 },
	{ 191,2187 }, { 192,2187 }, { 193,2187 }, { 194,2187 }, { 195,2187 },
	{ 196,2187 }, { 197,2187 }, { 198,2187 }, { 199,2187 }, { 200,2187 },
	{ 201,2187 }, { 202,2187 }, { 203,2187 }, { 204,2187 }, { 205,2187 },
	{ 206,2187 }, { 207,2187 }, { 208,2187 }, { 209,2187 }, { 210,2187 },
	{ 211,2187 }, { 212,2187 }, { 213,2187 }, { 214,2187 }, { 215,2187 },
	{ 216,2187 }, { 217,2187 }, { 218,2187 }, { 219,2187 }, { 220,2187 },
	{ 221,2187 }, { 222,2187 }, { 223,2187 }, { 224,2187 }, { 225,2187 },
	{ 226,2187 }, { 227,2187 }, { 228,2187 }, { 229,2187 }, { 230,2187 },
	{ 231,2187 }, { 232,2187 }, { 233,2187 }, { 234,2187 }, { 235,2187 },

	{ 236,2187 }, { 237,2187 }, { 238,2187 }, { 239,2187 }, { 240,2187 },
	{ 241,2187 }, { 242,2187 }, { 243,2187 }, { 244,2187 }, { 245,2187 },
	{ 246,2187 }, { 247,2187 }, { 248,2187 }, { 249,2187 }, { 250,2187 },
	{ 251,2187 }, { 252,2187 }, { 253,2187 }, { 254,2187 }, { 255,2187 },
	{ 256,2187 }, {   0,  13 }, {   0,5859 }, {   0,   4 }, {   0,5857 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   7 }, {   0,5852 },
	{   0,   0 }, {   9,2187 }, {  10,2187 }, {   9,   0 }, {  10,   0 },
	{  13,2187 }, {   0,   0 }, {  13,   0 }, {   9,  20 }, {  10,  20 },
	{   0,   0 }, {   0,5840 }, {  13,  20 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   7 }, {   0,5832 },

	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  32,2187 },
	{  33,2444 }, {  32,   0 }, {   0,   0 }, {   9,   0 }, {  10,   0 },
	{   0,   0 }, {  32,  20 }, {  13,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  47,-536 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {  32,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{  63,2702 }, {  45,4808 }, {  65,2960 }, {  66,2960 }, {  67,2960 },
	{  68,2960 }, {  69,2960 }, {  70,2960 }, {  71,2960 }, {  72,2960 },
	{  73,2960 }, {  74,2960 }, {  75,2960 }, {  76,2960 }, {  77,2960 },

	{  78,2960 }, {  79,2960 }, {  80,2960 }, {  81,2960 }, {  82,2960 },
	{  83,2960 }, {  84,2960 }, {  85,2960 }, {  86,2960 }, {  87,2960 },
	{  88,2960 }, {  89,2960 }, {  90,2960 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {  95,2960 }, {   0,   0 }, {  97,2960 },
	{  98,2960 }, {  99,2960 }, { 100,2960 }, { 101,2960 }, { 102,2960 },
	{ 103,2960 }, { 104,2960 }, { 105,2960 }, { 106,2960 }, { 107,2960 },
	{ 108,2960 }, { 109,2960 }, { 110,2960 }, { 111,2960 }, { 112,2960 },
	{ 113,2960 }, { 114,2960 }, { 115,2960 }, { 116,2960 }, { 117,2960 },
	{ 118,2960 }, { 119,2960 }, { 120,2960 }, { 121,2960 }, { 122,2960 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },

	{ 128,2960 }, { 129,2960 }, { 130,2960 }, { 131,2960 }, { 132,2960 },
	{ 133,2960 }, { 134,2960 }, { 135,2960 }, { 136,2960 }, { 137,2960 },
	{ 138,2960 }, { 139,2960 }, { 140,2960 }, { 141,2960 }, { 142,2960 },
	{ 143,2960 }, { 144,2960 }, { 145,2960 }, { 146,2960 }, { 147,2960 },
	{ 148,2960 }, { 149,2960 }, { 150,2960 }, { 151,2960 }, { 152,2960 },
	{ 153,2960 }, { 154,2960 }, { 155,2960 }, { 156,2960 }, { 157,2960 },
	{ 158,2960 }, { 159,2960 }, { 160,2960 }, { 161,2960 }, { 162,2960 },
	{ 163,2960 }, { 164,2960 }, { 165,2960 }, { 166,2960 }, { 167,2960 },
	{ 168,2960 }, { 169,2960 }, { 170,2960 }, { 171,2960 }, { 172,2960 },
	{ 173,2960 }, { 174,2960 }, { 175,2960 }, { 176,2960 }, { 177,2960 },

	{ 178,2960 }, { 179,2960 }, { 180,2960 }, { 181,2960 }, { 182,2960 },
	{ 183,2960 }, { 184,2960 }, { 185,2960 }, { 186,2960 }, { 187,2960 },
	{ 188,2960 }, { 189,2960 }, { 190,2960 }, { 191,2960 }, { 192,2960 },
	{ 193,2960 }, { 194,2960 }, { 195,2960 }, { 196,2960 }, { 197,2960 },
	{ 198,2960 }, { 199,2960 }, { 200,2960 }, { 201,2960 }, { 202,2960 },
	{ 203,2960 }, { 204,2960 }, { 205,2960 }, { 206,2960 }, { 207,2960 },
	{ 208,2960 }, { 209,2960 }, { 210,2960 }, { 211,2960 }, { 212,2960 },
	{ 213,2960 }, { 214,2960 }, { 215,2960 }, { 216,2960 }, { 217,2960 },
	{ 218,2960 }, { 219,2960 }, { 220,2960 }, { 221,2960 }, { 222,2960 },
	{ 223,2960 }, { 224,2960 }, { 225,2960 }, { 226,2960 }, { 227,2960 },

	{ 228,2960 }, { 229,2960 }, { 230,2960 }, { 231,2960 }, { 232,2960 },
	{ 233,2960 }, { 234,2960 }, { 235,2960 }, { 236,2960 }, { 237,2960 },
	{ 238,2960 }, { 239,2960 }, { 240,2960 }, { 241,2960 }, { 242,2960 },
	{ 243,2960 }, { 244,2960 }, { 245,2960 }, { 246,2960 }, { 247,2960 },
	{ 248,2960 }, { 249,2960 }, { 250,2960 }, { 251,2960 }, { 252,2960 },
	{ 253,2960 }, { 254,2960 }, { 255,2960 }, {   0,   5 }, {   0,5602 },
	{   0,  11 }, {   0,5600 }, {   0,  11 }, {   0,5598 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   9,   2 }, {  10,   2 }, {   9,   0 }, {  10,   0 }, {  13,   2 },
	{   0,   0 }, {  13,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },

	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,5573 }, {   0,  10 },
	{   0,5571 }, {   0,   0 }, {   0,   0 }, {  32,   2 }, {   0,   0 },
	{  32,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   9, 744 },
	{  10, 744 }, {   0,   0 }, {   0,   0 }, {  13, 744 }, {  45,2960 },
	{  46,2960 }, {   0,   0 }, {  48,2960 }, {  49,2960 }, {  50,2960 },
	{  51,2960 }, {  52,2960 }, {  53,2960 }, {  54,2960 }, {  55,2960 },
	{  56,2960 }, {  57,2960 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {  32, 744 }, {   0,   0 }, {  65,2960 },
	{  66,2960 }, {  67,2960 }, {  68,2960 }, {  69,2960 }, {  70,2960 },

	{  71,2960 }, {  72,2960 }, {  73,2960 }, {  74,2960 }, {  75,2960 },
	{  76,2960 }, {  77,2960 }, {  78,2960 }, {  79,2960 }, {  80,2960 },
	{  81,2960 }, {  82,2960 }, {  83,2960 }, {  84,2960 }, {  85,2960 },
	{  86,2960 }, {  87,2960 }, {  88,2960 }, {  89,2960 }, {  90,2960 },
	{  62,   2 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  95,2960 },
	{   0,   0 }, {  97,2960 }, {  98,2960 }, {  99,2960 }, { 100,2960 },
	{ 101,2960 }, { 102,2960 }, { 103,2960 }, { 104,2960 }, { 105,2960 },
	{ 106,2960 }, { 107,2960 }, { 108,2960 }, { 109,2960 }, { 110,2960 },
	{ 111,2960 }, { 112,2960 }, { 113,2960 }, { 114,2960 }, { 115,2960 },
	{ 116,2960 }, { 117,2960 }, { 118,2960 }, { 119,2960 }, { 120,2960 },

	{ 121,2960 }, { 122,2960 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, { 128,2960 }, { 129,2960 }, { 130,2960 },
	{ 131,2960 }, { 132,2960 }, { 133,2960 }, { 134,2960 }, { 135,2960 },
	{ 136,2960 }, { 137,2960 }, { 138,2960 }, { 139,2960 }, { 140,2960 },
	{ 141,2960 }, { 142,2960 }, { 143,2960 }, { 144,2960 }, { 145,2960 },
	{ 146,2960 }, { 147,2960 }, { 148,2960 }, { 149,2960 }, { 150,2960 },
	{ 151,2960 }, { 152,2960 }, { 153,2960 }, { 154,2960 }, { 155,2960 },
	{ 156,2960 }, { 157,2960 }, { 158,2960 }, { 159,2960 }, { 160,2960 },
	{ 161,2960 }, { 162,2960 }, { 163,2960 }, { 164,2960 }, { 165,2960 },
	{ 166,2960 }, { 167,2960 }, { 168,2960 }, { 169,2960 }, { 170,2960 },

	{ 171,2960 }, { 172,2960 }, { 173,2960 }, { 174,2960 }, { 175,2960 },
	{ 176,2960 }, { 177,2960 }, { 178,2960 }, { 179,2960 }, { 180,2960 },
	{ 181,2960 }, { 182,2960 }, { 183,2960 }, { 184,2960 }, { 185,2960 },
	{ 186,2960 }, { 187,2960 }, { 188,2960 }, { 189,2960 }, { 190,2960 },
	{ 191,2960 }, { 192,2960 }, { 193,2960 }, { 194,2960 }, { 195,2960 },
	{ 196,2960 }, { 197,2960 }, { 198,2960 }, { 199,2960 }, { 200,2960 },
	{ 201,2960 }, { 202,2960 }, { 203,2960 }, { 204,2960 }, { 205,2960 },
	{ 206,2960 }, { 207,2960 }, { 208,2960 }, { 209,2960 }, { 210,2960 },
	{ 211,2960 }, { 212,2960 }, { 213,2960 }, { 214,2960 }, { 215,2960 },
	{ 216,2960 }, { 217,2960 }, { 218,2960 }, { 219,2960 }, { 220,2960 },

	{ 221,2960 }, { 222,2960 }, { 223,2960 }, { 224,2960 }, { 225,2960 },
	{ 226,2960 }, { 227,2960 }, { 228,2960 }, { 229,2960 }, { 230,2960 },
	{ 231,2960 }, { 232,2960 }, { 233,2960 }, { 234,2960 }, { 235,2960 },
	{ 236,2960 }, { 237,2960 }, { 238,2960 }, { 239,2960 }, { 240,2960 },
	{ 241,2960 }, { 242,2960 }, { 243,2960 }, { 244,2960 }, { 245,2960 },
	{ 246,2960 }, { 247,2960 }, { 248,2960 }, { 249,2960 }, { 250,2960 },
	{ 251,2960 }, { 252,2960 }, { 253,2960 }, { 254,2960 }, { 255,2960 },
	{   0,  12 }, {   0,5345 }, {   1,2960 }, {   2,2960 }, {   3,2960 },
	{   4,2960 }, {   5,2960 }, {   6,2960 }, {   7,2960 }, {   8,2960 },
	{   9,2960 }, {   0,   0 }, {  11,2960 }, {  12,2960 }, {  13,2960 },

	{  14,2960 }, {  15,2960 }, {  16,2960 }, {  17,2960 }, {  18,2960 },
	{  19,2960 }, {  20,2960 }, {  21,2960 }, {  22,2960 }, {  23,2960 },
	{  24,2960 }, {  25,2960 }, {  26,2960 }, {  27,2960 }, {  28,2960 },
	{  29,2960 }, {  30,2960 }, {  31,2960 }, {  32,2960 }, {  33,2960 },
	{  34,2960 }, {  35,2960 }, {  36,2960 }, {  37,2960 }, {   0,   0 },
	{  39,2960 }, {  40,2960 }, {  41,2960 }, {  42,2960 }, {  43,2960 },
	{  44,2960 }, {  45,2960 }, {  46,2960 }, {  47,2960 }, {  48,2960 },
	{  49,2960 }, {  50,2960 }, {  51,2960 }, {  52,2960 }, {  53,2960 },
	{  54,2960 }, {  55,2960 }, {  56,2960 }, {  57,2960 }, {  58,2960 },
	{  59,2960 }, {   0,   0 }, {  61,2960 }, {  62,2960 }, {  63,2960 },

	{  64,2960 }, {  65,2960 }, {  66,2960 }, {  67,2960 }, {  68,2960 },
	{  69,2960 }, {  70,2960 }, {  71,2960 }, {  72,2960 }, {  73,2960 },
	{  74,2960 }, {  75,2960 }, {  76,2960 }, {  77,2960 }, {  78,2960 },
	{  79,2960 }, {  80,2960 }, {  81,2960 }, {  82,2960 }, {  83,2960 },
	{  84,2960 }, {  85,2960 }, {  86,2960 }, {  87,2960 }, {  88,2960 },
	{  89,2960 }, {  90,2960 }, {  91,2960 }, {  92,2960 }, {  93,2960 },
	{  94,2960 }, {  95,2960 }, {  96,2960 }, {  97,2960 }, {  98,2960 },
	{  99,2960 }, { 100,2960 }, { 101,2960 }, { 102,2960 }, { 103,2960 },
	{ 104,2960 }, { 105,2960 }, { 106,2960 }, { 107,2960 }, { 108,2960 },
	{ 109,2960 }, { 110,2960 }, { 111,2960 }, { 112,2960 }, { 113,2960 },

	{ 114,2960 }, { 115,2960 }, { 116,2960 }, { 117,2960 }, { 118,2960 },
	{ 119,2960 }, { 120,2960 }, { 121,2960 }, { 122,2960 }, { 123,2960 },
	{ 124,2960 }, { 125,2960 }, { 126,2960 }, { 127,2960 }, { 128,2960 },
	{ 129,2960 }, { 130,2960 }, { 131,2960 }, { 132,2960 }, { 133,2960 },
	{ 134,2960 }, { 135,2960 }, { 136,2960 }, { 137,2960 }, { 138,2960 },
	{ 139,2960 }, { 140,2960 }, { 141,2960 }, { 142,2960 }, { 143,2960 },
	{ 144,2960 }, { 145,2960 }, { 146,2960 }, { 147,2960 }, { 148,2960 },
	{ 149,2960 }, { 150,2960 }, { 151,2960 }, { 152,2960 }, { 153,2960 },
	{ 154,2960 }, { 155,2960 }, { 156,2960 }, { 157,2960 }, { 158,2960 },
	{ 159,2960 }, { 160,2960 }, { 161,2960 }, { 162,2960 }, { 163,2960 },

	{ 164,2960 }, { 165,2960 }, { 166,2960 }, { 167,2960 }, { 168,2960 },
	{ 169,2960 }, { 170,2960 }, { 171,2960 }, { 172,2960 }, { 173,2960 },
	{ 174,2960 }, { 175,2960 }, { 176,2960 }, { 177,2960 }, { 178,2960 },
	{ 179,2960 }, { 180,2960 }, { 181,2960 }, { 182,2960 }, { 183,2960 },
	{ 184,2960 }, { 185,2960 }, { 186,2960 }, { 187,2960 }, { 188,2960 },
	{ 189,2960 }, { 190,2960 }, { 191,2960 }, { 192,2960 }, { 193,2960 },
	{ 194,2960 }, { 195,2960 }, { 196,2960 }, { 197,2960 }, { 198,2960 },
	{ 199,2960 }, { 200,2960 }, { 201,2960 }, { 202,2960 }, { 203,2960 },
	{ 204,2960 }, { 205,2960 }, { 206,2960 }, { 207,2960 }, { 208,2960 },
	{ 209,2960 }, { 210,2960 }, { 211,2960 }, { 212,2960 }, { 213,2960 },

	{ 214,2960 }, { 215,2960 }, { 216,2960 }, { 217,2960 }, { 218,2960 },
	{ 219,2960 }, { 220,2960 }, { 221,2960 }, { 222,2960 }, { 223,2960 },
	{ 224,2960 }, { 225,2960 }, { 226,2960 }, { 227,2960 }, { 228,2960 },
	{ 229,2960 }, { 230,2960 }, { 231,2960 }, { 232,2960 }, { 233,2960 },
	{ 234,2960 }, { 235,2960 }, { 236,2960 }, { 237,2960 }, { 238,2960 },
	{ 239,2960 }, { 240,2960 }, { 241,2960 }, { 242,2960 }, { 243,2960 },
	{ 244,2960 }, { 245,2960 }, { 246,2960 }, { 247,2960 }, { 248,2960 },
	{ 249,2960 }, { 250,2960 }, { 251,2960 }, { 252,2960 }, { 253,2960 },
	{ 254,2960 }, { 255,2960 }, { 256,2960 }, {   0,  12 }, {   0,5087 },
	{   1,2702 }, {   2,2702 }, {   3,2702 }, {   4,2702 }, {   5,2702 },

	{   6,2702 }, {   7,2702 }, {   8,2702 }, {   9,2960 }, {  10,3218 },
	{  11,2702 }, {  12,2702 }, {  13,2960 }, {  14,2702 }, {  15,2702 },
	{  16,2702 }, {  17,2702 }, {  18,2702 }, {  19,2702 }, {  20,2702 },
	{  21,2702 }, {  22,2702 }, {  23,2702 }, {  24,2702 }, {  25,2702 },
	{  26,2702 }, {  27,2702 }, {  28,2702 }, {  29,2702 }, {  30,2702 },
	{  31,2702 }, {  32,2960 }, {  33,2702 }, {  34,2702 }, {  35,2702 },
	{  36,2702 }, {  37,2702 }, {   0,   0 }, {  39,2702 }, {  40,2702 },
	{  41,2702 }, {  42,2702 }, {  43,2702 }, {  44,2702 }, {  45,2702 },
	{  46,2702 }, {  47,2702 }, {  48,2702 }, {  49,2702 }, {  50,2702 },
	{  51,2702 }, {  52,2702 }, {  53,2702 }, {  54,2702 }, {  55,2702 },

	{  56,2702 }, {  57,2702 }, {  58,2702 }, {  59,2702 }, {  60, 580 },
	{  61,2702 }, {  62,2702 }, {  63,2702 }, {  64,2702 }, {  65,2702 },
	{  66,2702 }, {  67,2702 }, {  68,2702 }, {  69,2702 }, {  70,2702 },
	{  71,2702 }, {  72,2702 }, {  73,2702 }, {  74,2702 }, {  75,2702 },
	{  76,2702 }, {  77,2702 }, {  78,2702 }, {  79,2702 }, {  80,2702 },
	{  81,2702 }, {  82,2702 }, {  83,2702 }, {  84,2702 }, {  85,2702 },
	{  86,2702 }, {  87,2702 }, {  88,2702 }, {  89,2702 }, {  90,2702 },
	{  91,2702 }, {  92,2702 }, {  93,2702 }, {  94,2702 }, {  95,2702 },
	{  96,2702 }, {  97,2702 }, {  98,2702 }, {  99,2702 }, { 100,2702 },
	{ 101,2702 }, { 102,2702 }, { 103,2702 }, { 104,2702 }, { 105,2702 },

	{ 106,2702 }, { 107,2702 }, { 108,2702 }, { 109,2702 }, { 110,2702 },
	{ 111,2702 }, { 112,2702 }, { 113,2702 }, { 114,2702 }, { 115,2702 },
	{ 116,2702 }, { 117,2702 }, { 118,2702 }, { 119,2702 }, { 120,2702 },
	{ 121,2702 }, { 122,2702 }, { 123,2702 }, { 124,2702 }, { 125,2702 },
	{ 126,2702 }, { 127,2702 }, { 128,2702 }, { 129,2702 }, { 130,2702 },
	{ 131,2702 }, { 132,2702 }, { 133,2702 }, { 134,2702 }, { 135,2702 },
	{ 136,2702 }, { 137,2702 }, { 138,2702 }, { 139,2702 }, { 140,2702 },
	{ 141,2702 }, { 142,2702 }, { 143,2702 }, { 144,2702 }, { 145,2702 },
	{ 146,2702 }, { 147,2702 }, { 148,2702 }, { 149,2702 }, { 150,2702 },
	{ 151,2702 }, { 152,2702 }, { 153,2702 }, { 154,2702 }, { 155,2702 },

	{ 156,2702 }, { 157,2702 }, { 158,2702 }, { 159,2702 }, { 160,2702 },
	{ 161,2702 }, { 162,2702 }, { 163,2702 }, { 164,2702 }, { 165,2702 },
	{ 166,2702 }, { 167,2702 }, { 168,2702 }, { 169,2702 }, { 170,2702 },
	{ 171,2702 }, { 172,2702 }, { 173,2702 }, { 174,2702 }, { 175,2702 },
	{ 176,2702 }, { 177,2702 }, { 178,2702 }, { 179,2702 }, { 180,2702 },
	{ 181,2702 }, { 182,2702 }, { 183,2702 }, { 184,2702 }, { 185,2702 },
	{ 186,2702 }, { 187,2702 }, { 188,2702 }, { 189,2702 }, { 190,2702 },
	{ 191,2702 }, { 192,2702 }, { 193,2702 }, { 194,2702 }, { 195,2702 },
	{ 196,2702 }, { 197,2702 }, { 198,2702 }, { 199,2702 }, { 200,2702 },
	{ 201,2702 }, { 202,2702 }, { 203,2702 }, { 204,2702 }, { 205,2702 },

	{ 206,2702 }, { 207,2702 }, { 208,2702 }, { 209,2702 }, { 210,2702 },
	{ 211,2702 }, { 212,2702 }, { 213,2702 }, { 214,2702 }, { 215,2702 },
	{ 216,2702 }, { 217,2702 }, { 218,2702 }, { 219,2702 }, { 220,2702 },
	{ 221,2702 }, { 222,2702 }, { 223,2702 }, { 224,2702 }, { 225,2702 },
	{ 226,2702 }, { 227,2702 }, { 228,2702 }, { 229,2702 }, { 230,2702 },
	{ 231,2702 }, { 232,2702 }, { 233,2702 }, { 234,2702 }, { 235,2702 },
	{ 236,2702 }, { 237,2702 }, { 238,2702 }, { 239,2702 }, { 240,2702 },
	{ 241,2702 }, { 242,2702 }, { 243,2702 }, { 244,2702 }, { 245,2702 },
	{ 246,2702 }, { 247,2702 }, { 248,2702 }, { 249,2702 }, { 250,2702 },
	{ 251,2702 }, { 252,2702 }, { 253,2702 }, { 254,2702 }, { 255,2702 },

	{ 256,2702 }, {   0,  14 }, {   0,4829 }, {   0,  10 }, {   0,4827 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   9,2960 }, {  10,2960 }, {   9,   0 }, {  10,   0 },
	{  13,2960 }, {   0,   0 }, {  13,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  32,2960 },
	{   0,   0 }, {  32,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },

	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {  60, 322 }, {   0,  12 }, {   0,4767 },
	{   1,2382 }, {   2,2382 }, {   3,2382 }, {   4,2382 }, {   5,2382 },
	{   6,2382 }, {   7,2382 }, {   8,2382 }, {   9,2640 }, {  10,2900 },
	{  11,2382 }, {  12,2382 }, {  13,2640 }, {  14,2382 }, {  15,2382 },
	{  16,2382 }, {  17,2382 }, {  18,2382 }, {  19,2382 }, {  20,2382 },
	{  21,2382 }, {  22,2382 }, {  23,2382 }, {  24,2382 }, {  25,2382 },
	{  26,2382 }, {  27,2382 }, {  28,2382 }, {  29,2382 }, {  30,2382 },
	{  31,2382 }, {  32,2640 }, {  33,2382 }, {  34,2382 }, {  35,2382 },

	{  36,2382 }, {  37,2382 }, {   0,   0 }, {  39,2382 }, {  40,2382 },
	{  41,2382 }, {  42,2382 }, {  43,2382 }, {  44,2382 }, {  45,2382 },
	{  46,2382 }, {  47,2382 }, {  48,2382 }, {  49,2382 }, {  50,2382 },
	{  51,2382 }, {  52,2382 }, {  53,2382 }, {  54,2382 }, {  55,2382 },
	{  56,2382 }, {  57,2382 }, {  58,2382 }, {  59,2382 }, {  60, 260 },
	{  61,2382 }, {  62,2382 }, {  63,2382 }, {  64,2382 }, {  65,2382 },
	{  66,2382 }, {  67,2382 }, {  68,2382 }, {  69,2382 }, {  70,2382 },
	{  71,2382 }, {  72,2382 }, {  73,2382 }, {  74,2382 }, {  75,2382 },
	{  76,2382 }, {  77,2382 }, {  78,2382 }, {  79,2382 }, {  80,2382 },
	{  81,2382 }, {  82,2382 }, {  83,2382 }, {  84,2382 }, {  85,2382 },

	{  86,2382 }, {  87,2382 }, {  88,2382 }, {  89,2382 }, {  90,2382 },
	{  91,2382 }, {  92,2382 }, {  93,2382 }, {  94,2382 }, {  95,2382 },
	{  96,2382 }, {  97,2382 }, {  98,2382 }, {  99,2382 }, { 100,2382 },
	{ 101,2382 }, { 102,2382 }, { 103,2382 }, { 104,2382 }, { 105,2382 },
	{ 106,2382 }, { 107,2382 }, { 108,2382 }, { 109,2382 }, { 110,2382 },
	{ 111,2382 }, { 112,2382 }, { 113,2382 }, { 114,2382 }, { 115,2382 },
	{ 116,2382 }, { 117,2382 }, { 118,2382 }, { 119,2382 }, { 120,2382 },
	{ 121,2382 }, { 122,2382 }, { 123,2382 }, { 124,2382 }, { 125,2382 },
	{ 126,2382 }, { 127,2382 }, { 128,2382 }, { 129,2382 }, { 130,2382 },
	{ 131,2382 }, { 132,2382 }, { 133,2382 }, { 134,2382 }, { 135,2382 },

	{ 136,2382 }, { 137,2382 }, { 138,2382 }, { 139,2382 }, { 140,2382 },
	{ 141,2382 }, { 142,2382 }, { 143,2382 }, { 144,2382 }, { 145,2382 },
	{ 146,2382 }, { 147,2382 }, { 148,2382 }, { 149,2382 }, { 150,2382 },
	{ 151,2382 }, { 152,2382 }, { 153,2382 }, { 154,2382 }, { 155,2382 },
	{ 156,2382 }, { 157,2382 }, { 158,2382 }, { 159,2382 }, { 160,2382 },
	{ 161,2382 }, { 162,2382 }, { 163,2382 }, { 164,2382 }, { 165,2382 },
	{ 166,2382 }, { 167,2382 }, { 168,2382 }, { 169,2382 }, { 170,2382 },
	{ 171,2382 }, { 172,2382 }, { 173,2382 }, { 174,2382 }, { 175,2382 },
	{ 176,2382 }, { 177,2382 }, { 178,2382 }, { 179,2382 }, { 180,2382 },
	{ 181,2382 }, { 182,2382 }, { 183,2382 }, { 184,2382 }, { 185,2382 },

	{ 186,2382 }, { 187,2382 }, { 188,2382 }, { 189,2382 }, { 190,2382 },
	{ 191,2382 }, { 192,2382 }, { 193,2382 }, { 194,2382 }, { 195,2382 },
	{ 196,2382 }, { 197,2382 }, { 198,2382 }, { 199,2382 }, { 200,2382 },
	{ 201,2382 }, { 202,2382 }, { 203,2382 }, { 204,2382 }, { 205,2382 },
	{ 206,2382 }, { 207,2382 }, { 208,2382 }, { 209,2382 }, { 210,2382 },
	{ 211,2382 }, { 212,2382 }, { 213,2382 }, { 214,2382 }, { 215,2382 },
	{ 216,2382 }, { 217,2382 }, { 218,2382 }, { 219,2382 }, { 220,2382 },
	{ 221,2382 }, { 222,2382 }, { 223,2382 }, { 224,2382 }, { 225,2382 },
	{ 226,2382 }, { 227,2382 }, { 228,2382 }, { 229,2382 }, { 230,2382 },
	{ 231,2382 }, { 232,2382 }, { 233,2382 }, { 234,2382 }, { 235,2382 },

	{ 236,2382 }, { 237,2382 }, { 238,2382 }, { 239,2382 }, { 240,2382 },
	{ 241,2382 }, { 242,2382 }, { 243,2382 }, { 244,2382 }, { 245,2382 },
	{ 246,2382 }, { 247,2382 }, { 248,2382 }, { 249,2382 }, { 250,2382 },
	{ 251,2382 }, { 252,2382 }, { 253,2382 }, { 254,2382 }, { 255,2382 },
	{ 256,2382 }, {   0,   1 }, {   0,4509 }, {   0,   0 }, {   0,4507 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   9,   0 }, {  10,   0 }, {   9, 835 }, {  10, 835 },
	{  13,   0 }, {   0,   0 }, {  13, 835 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },

	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  32,   0 },
	{   0,   0 }, {  32, 835 }, {  33,1092 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {  47,-1888 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {  60,   2 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {  63,1350 }, {   0,   0 }, {  65,1608 },
	{  66,1608 }, {  67,1608 }, {  68,1608 }, {  69,1608 }, {  70,1608 },
	{  71,1608 }, {  72,1608 }, {  73,1608 }, {  74,1608 }, {  75,1608 },

	{  76,1608 }, {  77,1608 }, {  78,1608 }, {  79,1608 }, {  80,1608 },
	{  81,1608 }, {  82,1608 }, {  83,1608 }, {  84,1608 }, {  85,1608 },
	{  86,1608 }, {  87,1608 }, {  88,1608 }, {  89,1608 }, {  90,1608 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  95,1608 },
	{   0,   0 }, {  97,1608 }, {  98,1608 }, {  99,1608 }, { 100,1608 },
	{ 101,1608 }, { 102,1608 }, { 103,1608 }, { 104,1608 }, { 105,1608 },
	{ 106,1608 }, { 107,1608 }, { 108,1608 }, { 109,1608 }, { 110,1608 },
	{ 111,1608 }, { 112,1608 }, { 113,1608 }, { 114,1608 }, { 115,1608 },
	{ 116,1608 }, { 117,1608 }, { 118,1608 }, { 119,1608 }, { 120,1608 },
	{ 121,1608 }, { 122,1608 }, {   0,   0 }, {   0,   0 }, {   0,   0 },

	{   0,   0 }, {   0,   0 }, { 128,1608 }, { 129,1608 }, { 130,1608 },
	{ 131,1608 }, { 132,1608 }, { 133,1608 }, { 134,1608 }, { 135,1608 },
	{ 136,1608 }, { 137,1608 }, { 138,1608 }, { 139,1608 }, { 140,1608 },
	{ 141,1608 }, { 142,1608 }, { 143,1608 }, { 144,1608 }, { 145,1608 },
	{ 146,1608 }, { 147,1608 }, { 148,1608 }, { 149,1608 }, { 150,1608 },
	{ 151,1608 }, { 152,1608 }, { 153,1608 }, { 154,1608 }, { 155,1608 },
	{ 156,1608 }, { 157,1608 }, { 158,1608 }, { 159,1608 }, { 160,1608 },
	{ 161,1608 }, { 162,1608 }, { 163,1608 }, { 164,1608 }, { 165,1608 },
	{ 166,1608 }, { 167,1608 }, { 168,1608 }, { 169,1608 }, { 170,1608 },
	{ 171,1608 }, { 172,1608 }, { 173,1608 }, { 174,1608 }, { 175,1608 },

	{ 176,1608 }, { 177,1608 }, { 178,1608 }, { 179,1608 }, { 180,1608 },
	{ 181,1608 }, { 182,1608 }, { 183,1608 }, { 184,1608 }, { 185,1608 },
	{ 186,1608 }, { 187,1608 }, { 188,1608 }, { 189,1608 }, { 190,1608 },
	{ 191,1608 }, { 192,1608 }, { 193,1608 }, { 194,1608 }, { 195,1608 },
	{ 196,1608 }, { 197,1608 }, { 198,1608 }, { 199,1608 }, { 200,1608 },
	{ 201,1608 }, { 202,1608 }, { 203,1608 }, { 204,1608 }, { 205,1608 },
	{ 206,1608 }, { 207,1608 }, { 208,1608 }, { 209,1608 }, { 210,1608 },
	{ 211,1608 }, { 212,1608 }, { 213,1608 }, { 214,1608 }, { 215,1608 },
	{ 216,1608 }, { 217,1608 }, { 218,1608 }, { 219,1608 }, { 220,1608 },
	{ 221,1608 }, { 222,1608 }, { 223,1608 }, { 224,1608 }, { 225,1608 },

	{ 226,1608 }, { 227,1608 }, { 228,1608 }, { 229,1608 }, { 230,1608 },
	{ 231,1608 }, { 232,1608 }, { 233,1608 }, { 234,1608 }, { 235,1608 },
	{ 236,1608 }, { 237,1608 }, { 238,1608 }, { 239,1608 }, { 240,1608 },
	{ 241,1608 }, { 242,1608 }, { 243,1608 }, { 244,1608 }, { 245,1608 },
	{ 246,1608 }, { 247,1608 }, { 248,1608 }, { 249,1608 }, { 250,1608 },
	{ 251,1608 }, { 252,1608 }, { 253,1608 }, { 254,1608 }, { 255,1608 },
	{   0,   1 }, {   0,4250 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   9,-259 }, {  10,-259 }, {   0,   0 }, {   0,   0 }, {  13,-259 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },

	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {  32,-259 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {  60,-257 }, {   0,   0 }, {   0,4188 }, {   1,   0 },
	{   2,   0 }, {   3,   0 }, {   4,   0 }, {   5,   0 }, {   6,   0 },

	{   7,   0 }, {   8,   0 }, {   9,   0 }, {  10,   0 }, {  11,   0 },
	{  12,   0 }, {  13,   0 }, {  14,   0 }, {  15,   0 }, {  16,   0 },
	{  17,   0 }, {  18,   0 }, {  19,   0 }, {  20,   0 }, {  21,   0 },
	{  22,   0 }, {  23,   0 }, {  24,   0 }, {  25,   0 }, {  26,   0 },
	{  27,   0 }, {  28,   0 }, {  29,   0 }, {  30,   0 }, {  31,   0 },
	{  32,   0 }, {  33,   0 }, {  34,-2209 }, {  35,   0 }, {  36,   0 },
	{  37,   0 }, {   0,   0 }, {  39,   0 }, {  40,   0 }, {  41,   0 },
	{  42,   0 }, {  43,   0 }, {  44,   0 }, {  45,   0 }, {  46,   0 },
	{  47,   0 }, {  48,   0 }, {  49,   0 }, {  50,   0 }, {  51,   0 },
	{  52,   0 }, {  53,   0 }, {  54,   0 }, {  55,   0 }, {  56,   0 },

	{  57,   0 }, {  58,   0 }, {  59,   0 }, {  60,   0 }, {  61,   0 },
	{  62,   0 }, {  63,   0 }, {  64,   0 }, {  65,   0 }, {  66,   0 },
	{  67,   0 }, {  68,   0 }, {  69,   0 }, {  70,   0 }, {  71,   0 },
	{  72,   0 }, {  73,   0 }, {  74,   0 }, {  75,   0 }, {  76,   0 },
	{  77,   0 }, {  78,   0 }, {  79,   0 }, {  80,   0 }, {  81,   0 },
	{  82,   0 }, {  83,   0 }, {  84,   0 }, {  85,   0 }, {  86,   0 },
	{  87,   0 }, {  88,   0 }, {  89,   0 }, {  90,   0 }, {  91,   0 },
	{  92,   0 }, {  93,   0 }, {  94,   0 }, {  95,   0 }, {  96,   0 },
	{  97,   0 }, {  98,   0 }, {  99,   0 }, { 100,   0 }, { 101,   0 },
	{ 102,   0 }, { 103,   0 }, { 104,   0 }, { 105,   0 }, { 106,   0 },

	{ 107,   0 }, { 108,   0 }, { 109,   0 }, { 110,   0 }, { 111,   0 },
	{ 112,   0 }, { 113,   0 }, { 114,   0 }, { 115,   0 }, { 116,   0 },
	{ 117,   0 }, { 118,   0 }, { 119,   0 }, { 120,   0 }, { 121,   0 },
	{ 122,   0 }, { 123,   0 }, { 124,   0 }, { 125,   0 }, { 126,   0 },
	{ 127,   0 }, { 128,   0 }, { 129,   0 }, { 130,   0 }, { 131,   0 },
	{ 132,   0 }, { 133,   0 }, { 134,   0 }, { 135,   0 }, { 136,   0 },
	{ 137,   0 }, { 138,   0 }, { 139,   0 }, { 140,   0 }, { 141,   0 },
	{ 142,   0 }, { 143,   0 }, { 144,   0 }, { 145,   0 }, { 146,   0 },
	{ 147,   0 }, { 148,   0 }, { 149,   0 }, { 150,   0 }, { 151,   0 },
	{ 152,   0 }, { 153,   0 }, { 154,   0 }, { 155,   0 }, { 156,   0 },

	{ 157,   0 }, { 158,   0 }, { 159,   0 }, { 160,   0 }, { 161,   0 },
	{ 162,   0 }, { 163,   0 }, { 164,   0 }, { 165,   0 }, { 166,   0 },
	{ 167,   0 }, { 168,   0 }, { 169,   0 }, { 170,   0 }, { 171,   0 },
	{ 172,   0 }, { 173,   0 }, { 174,   0 }, { 175,   0 }, { 176,   0 },
	{ 177,   0 }, { 178,   0 }, { 179,   0 }, { 180,   0 }, { 181,   0 },
	{ 182,   0 }, { 183,   0 }, { 184,   0 }, { 185,   0 }, { 186,   0 },
	{ 187,   0 }, { 188,   0 }, { 189,   0 }, { 190,   0 }, { 191,   0 },
	{ 192,   0 }, { 193,   0 }, { 194,   0 }, { 195,   0 }, { 196,   0 },
	{ 197,   0 }, { 198,   0 }, { 199,   0 }, { 200,   0 }, { 201,   0 },
	{ 202,   0 }, { 203,   0 }, { 204,   0 }, { 205,   0 }, { 206,   0 },

	{ 207,   0 }, { 208,   0 }, { 209,   0 }, { 210,   0 }, { 211,   0 },
	{ 212,   0 }, { 213,   0 }, { 214,   0 }, { 215,   0 }, { 216,   0 },
	{ 217,   0 }, { 218,   0 }, { 219,   0 }, { 220,   0 }, { 221,   0 },
	{ 222,   0 }, { 223,   0 }, { 224,   0 }, { 225,   0 }, { 226,   0 },
	{ 227,   0 }, { 228,   0 }, { 229,   0 }, { 230,   0 }, { 231,   0 },
	{ 232,   0 }, { 233,   0 }, { 234,   0 }, { 235,   0 }, { 236,   0 },
	{ 237,   0 }, { 238,   0 }, { 239,   0 }, { 240,   0 }, { 241,   0 },
	{ 242,   0 }, { 243,   0 }, { 244,   0 }, { 245,   0 }, { 246,   0 },
	{ 247,   0 }, { 248,   0 }, { 249,   0 }, { 250,   0 }, { 251,   0 },
	{ 252,   0 }, { 253,   0 }, { 254,   0 }, { 255,   0 }, { 256,   0 },

	{   0,   0 }, {   0,3930 }, {   1,   0 }, {   2,   0 }, {   3,   0 },
	{   4,   0 }, {   5,   0 }, {   6,   0 }, {   7,   0 }, {   8,   0 },
	{   9,   0 }, {  10,   0 }, {  11,   0 }, {  12,   0 }, {  13,   0 },
	{  14,   0 }, {  15,   0 }, {  16,   0 }, {  17,   0 }, {  18,   0 },
	{  19,   0 }, {  20,   0 }, {  21,   0 }, {  22,   0 }, {  23,   0 },
	{  24,   0 }, {  25,   0 }, {  26,   0 }, {  27,   0 }, {  28,   0 },
	{  29,   0 }, {  30,   0 }, {  31,   0 }, {  32,   0 }, {  33,   0 },
	{  34,   0 }, {  35,   0 }, {  36,   0 }, {  37,   0 }, {   0,   0 },
	{  39,-2467 }, {  40,   0 }, {  41,   0 }, {  42,   0 }, {  43,   0 },
	{  44,   0 }, {  45,   0 }, {  46,   0 }, {  47,   0 }, {  48,   0 },

	{  49,   0 }, {  50,   0 }, {  51,   0 }, {  52,   0 }, {  53,   0 },
	{  54,   0 }, {  55,   0 }, {  56,   0 }, {  57,   0 }, {  58,   0 },
	{  59,   0 }, {  60,   0 }, {  61,   0 }, {  62,   0 }, {  63,   0 },
	{  64,   0 }, {  65,   0 }, {  66,   0 }, {  67,   0 }, {  68,   0 },
	{  69,   0 }, {  70,   0 }, {  71,   0 }, {  72,   0 }, {  73,   0 },
	{  74,   0 }, {  75,   0 }, {  76,   0 }, {  77,   0 }, {  78,   0 },
	{  79,   0 }, {  80,   0 }, {  81,   0 }, {  82,   0 }, {  83,   0 },
	{  84,   0 }, {  85,   0 }, {  86,   0 }, {  87,   0 }, {  88,   0 },
	{  89,   0 }, {  90,   0 }, {  91,   0 }, {  92,   0 }, {  93,   0 },
	{  94,   0 }, {  95,   0 }, {  96,   0 }, {  97,   0 }, {  98,   0 },

	{  99,   0 }, { 100,   0 }, { 101,   0 }, { 102,   0 }, { 103,   0 },
	{ 104,   0 }, { 105,   0 }, { 106,   0 }, { 107,   0 }, { 108,   0 },
	{ 109,   0 }, { 110,   0 }, { 111,   0 }, { 112,   0 }, { 113,   0 },
	{ 114,   0 }, { 115,   0 }, { 116,   0 }, { 117,   0 }, { 118,   0 },
	{ 119,   0 }, { 120,   0 }, { 121,   0 }, { 122,   0 }, { 123,   0 },
	{ 124,   0 }, { 125,   0 }, { 126,   0 }, { 127,   0 }, { 128,   0 },
	{ 129,   0 }, { 130,   0 }, { 131,   0 }, { 132,   0 }, { 133,   0 },
	{ 134,   0 }, { 135,   0 }, { 136,   0 }, { 137,   0 }, { 138,   0 },
	{ 139,   0 }, { 140,   0 }, { 141,   0 }, { 142,   0 }, { 143,   0 },
	{ 144,   0 }, { 145,   0 }, { 146,   0 }, { 147,   0 }, { 148,   0 },

	{ 149,   0 }, { 150,   0 }, { 151,   0 }, { 152,   0 }, { 153,   0 },
	{ 154,   0 }, { 155,   0 }, { 156,   0 }, { 157,   0 }, { 158,   0 },
	{ 159,   0 }, { 160,   0 }, { 161,   0 }, { 162,   0 }, { 163,   0 },
	{ 164,   0 }, { 165,   0 }, { 166,   0 }, { 167,   0 }, { 168,   0 },
	{ 169,   0 }, { 170,   0 }, { 171,   0 }, { 172,   0 }, { 173,   0 },
	{ 174,   0 }, { 175,   0 }, { 176,   0 }, { 177,   0 }, { 178,   0 },
	{ 179,   0 }, { 180,   0 }, { 181,   0 }, { 182,   0 }, { 183,   0 },
	{ 184,   0 }, { 185,   0 }, { 186,   0 }, { 187,   0 }, { 188,   0 },
	{ 189,   0 }, { 190,   0 }, { 191,   0 }, { 192,   0 }, { 193,   0 },
	{ 194,   0 }, { 195,   0 }, { 196,   0 }, { 197,   0 }, { 198,   0 },

	{ 199,   0 }, { 200,   0 }, { 201,   0 }, { 202,   0 }, { 203,   0 },
	{ 204,   0 }, { 205,   0 }, { 206,   0 }, { 207,   0 }, { 208,   0 },
	{ 209,   0 }, { 210,   0 }, { 211,   0 }, { 212,   0 }, { 213,   0 },
	{ 214,   0 }, { 215,   0 }, { 216,   0 }, { 217,   0 }, { 218,   0 },
	{ 219,   0 }, { 220,   0 }, { 221,   0 }, { 222,   0 }, { 223,   0 },
	{ 224,   0 }, { 225,   0 }, { 226,   0 }, { 227,   0 }, { 228,   0 },
	{ 229,   0 }, { 230,   0 }, { 231,   0 }, { 232,   0 }, { 233,   0 },
	{ 234,   0 }, { 235,   0 }, { 236,   0 }, { 237,   0 }, { 238,   0 },
	{ 239,   0 }, { 240,   0 }, { 241,   0 }, { 242,   0 }, { 243,   0 },
	{ 244,   0 }, { 245,   0 }, { 246,   0 }, { 247,   0 }, { 248,   0 },

	{ 249,   0 }, { 250,   0 }, { 251,   0 }, { 252,   0 }, { 253,   0 },
	{ 254,   0 }, { 255,   0 }, { 256,   0 }, {   0,   0 }, {   0,3672 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   9,   0 }, {  10,   0 },
	{   0,   0 }, {   0,   0 }, {  13,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {  32,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },

	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {  47,-2723 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  65, 773 },
	{  66, 773 }, {  67, 773 }, {  68, 773 }, {  69, 773 }, {  70, 773 },
	{  71, 773 }, {  72, 773 }, {  73, 773 }, {  74, 773 }, {  75, 773 },
	{  76, 773 }, {  77, 773 }, {  78, 773 }, {  79, 773 }, {  80, 773 },
	{  81, 773 }, {  82, 773 }, {  83, 773 }, {  84, 773 }, {  85, 773 },
	{  86, 773 }, {  87, 773 }, {  88, 773 }, {  89, 773 }, {  90, 773 },

	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  95, 773 },
	{   0,   0 }, {  97, 773 }, {  98, 773 }, {  99, 773 }, { 100, 773 },
	{ 101, 773 }, { 102, 773 }, { 103, 773 }, { 104, 773 }, { 105, 773 },
	{ 106, 773 }, { 107, 773 }, { 108, 773 }, { 109, 773 }, { 110, 773 },
	{ 111, 773 }, { 112, 773 }, { 113, 773 }, { 114, 773 }, { 115, 773 },
	{ 116, 773 }, { 117, 773 }, { 118, 773 }, { 119, 773 }, { 120, 773 },
	{ 121, 773 }, { 122, 773 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, { 128, 773 }, { 129, 773 }, { 130, 773 },
	{ 131, 773 }, { 132, 773 }, { 133, 773 }, { 134, 773 }, { 135, 773 },
	{ 136, 773 }, { 137, 773 }, { 138, 773 }, { 139, 773 }, { 140, 773 },

	{ 141, 773 }, { 142, 773 }, { 143, 773 }, { 144, 773 }, { 145, 773 },
	{ 146, 773 }, { 147, 773 }, { 148, 773 }, { 149, 773 }, { 150, 773 },
	{ 151, 773 }, { 152, 773 }, { 153, 773 }, { 154, 773 }, { 155, 773 },
	{ 156, 773 }, { 157, 773 }, { 158, 773 }, { 159, 773 }, { 160, 773 },
	{ 161, 773 }, { 162, 773 }, { 163, 773 }, { 164, 773 }, { 165, 773 },
	{ 166, 773 }, { 167, 773 }, { 168, 773 }, { 169, 773 }, { 170, 773 },
	{ 171, 773 }, { 172, 773 }, { 173, 773 }, { 174, 773 }, { 175, 773 },
	{ 176, 773 }, { 177, 773 }, { 178, 773 }, { 179, 773 }, { 180, 773 },
	{ 181, 773 }, { 182, 773 }, { 183, 773 }, { 184, 773 }, { 185, 773 },
	{ 186, 773 }, { 187, 773 }, { 188, 773 }, { 189, 773 }, { 190, 773 },

	{ 191, 773 }, { 192, 773 }, { 193, 773 }, { 194, 773 }, { 195, 773 },
	{ 196, 773 }, { 197, 773 }, { 198, 773 }, { 199, 773 }, { 200, 773 },
	{ 201, 773 }, { 202, 773 }, { 203, 773 }, { 204, 773 }, { 205, 773 },
	{ 206, 773 }, { 207, 773 }, { 208, 773 }, { 209, 773 }, { 210, 773 },
	{ 211, 773 }, { 212, 773 }, { 213, 773 }, { 214, 773 }, { 215, 773 },
	{ 216, 773 }, { 217, 773 }, { 218, 773 }, { 219, 773 }, { 220, 773 },
	{ 221, 773 }, { 222, 773 }, { 223, 773 }, { 224, 773 }, { 225, 773 },
	{ 226, 773 }, { 227, 773 }, { 228, 773 }, { 229, 773 }, { 230, 773 },
	{ 231, 773 }, { 232, 773 }, { 233, 773 }, { 234, 773 }, { 235, 773 },
	{ 236, 773 }, { 237, 773 }, { 238, 773 }, { 239, 773 }, { 240, 773 },

	{ 241, 773 }, { 242, 773 }, { 243, 773 }, { 244, 773 }, { 245, 773 },
	{ 246, 773 }, { 247, 773 }, { 248, 773 }, { 249, 773 }, { 250, 773 },
	{ 251, 773 }, { 252, 773 }, { 253, 773 }, { 254, 773 }, { 255, 773 },
	{   0,   0 }, {   0,3415 }, {   1,1610 }, {   2,1610 }, {   3,1610 },
	{   4,1610 }, {   5,1610 }, {   6,1610 }, {   7,1610 }, {   8,1610 },
	{   9,1610 }, {  10,1610 }, {  11,1610 }, {  12,1610 }, {  13,1610 },
	{  14,1610 }, {  15,1610 }, {  16,1610 }, {  17,1610 }, {  18,1610 },
	{  19,1610 }, {  20,1610 }, {  21,1610 }, {  22,1610 }, {  23,1610 },
	{  24,1610 }, {  25,1610 }, {  26,1610 }, {  27,1610 }, {  28,1610 },
	{  29,1610 }, {  30,1610 }, {  31,1610 }, {  32,1610 }, {  33,1610 },

	{  34,1610 }, {  35,1610 }, {  36,1610 }, {  37,1610 }, {  38,1610 },
	{  39,1610 }, {  40,1610 }, {  41,1610 }, {  42,1610 }, {  43,1610 },
	{  44,1610 }, {  45,-2425 }, {  46,1610 }, {  47,1610 }, {  48,1610 },
	{  49,1610 }, {  50,1610 }, {  51,1610 }, {  52,1610 }, {  53,1610 },
	{  54,1610 }, {  55,1610 }, {  56,1610 }, {  57,1610 }, {  58,1610 },
	{  59,1610 }, {  60,1610 }, {  61,1610 }, {  62,1610 }, {  63,1610 },
	{  64,1610 }, {  65,1610 }, {  66,1610 }, {  67,1610 }, {  68,1610 },
	{  69,1610 }, {  70,1610 }, {  71,1610 }, {  72,1610 }, {  73,1610 },
	{  74,1610 }, {  75,1610 }, {  76,1610 }, {  77,1610 }, {  78,1610 },
	{  79,1610 }, {  80,1610 }, {  81,1610 }, {  82,1610 }, {  83,1610 },

	{  84,1610 }, {  85,1610 }, {  86,1610 }, {  87,1610 }, {  88,1610 },
	{  89,1610 }, {  90,1610 }, {  91,1610 }, {  92,1610 }, {  93,1610 },
	{  94,1610 }, {  95,1610 }, {  96,1610 }, {  97,1610 }, {  98,1610 },
	{  99,1610 }, { 100,1610 }, { 101,1610 }, { 102,1610 }, { 103,1610 },
	{ 104,1610 }, { 105,1610 }, { 106,1610 }, { 107,1610 }, { 108,1610 },
	{ 109,1610 }, { 110,1610 }, { 111,1610 }, { 112,1610 }, { 113,1610 },
	{ 114,1610 }, { 115,1610 }, { 116,1610 }, { 117,1610 }, { 118,1610 },
	{ 119,1610 }, { 120,1610 }, { 121,1610 }, { 122,1610 }, { 123,1610 },
	{ 124,1610 }, { 125,1610 }, { 126,1610 }, { 127,1610 }, { 128,1610 },
	{ 129,1610 }, { 130,1610 }, { 131,1610 }, { 132,1610 }, { 133,1610 },

	{ 134,1610 }, { 135,1610 }, { 136,1610 }, { 137,1610 }, { 138,1610 },
	{ 139,1610 }, { 140,1610 }, { 141,1610 }, { 142,1610 }, { 143,1610 },
	{ 144,1610 }, { 145,1610 }, { 146,1610 }, { 147,1610 }, { 148,1610 },
	{ 149,1610 }, { 150,1610 }, { 151,1610 }, { 152,1610 }, { 153,1610 },
	{ 154,1610 }, { 155,1610 }, { 156,1610 }, { 157,1610 }, { 158,1610 },
	{ 159,1610 }, { 160,1610 }, { 161,1610 }, { 162,1610 }, { 163,1610 },
	{ 164,1610 }, { 165,1610 }, { 166,1610 }, { 167,1610 }, { 168,1610 },
	{ 169,1610 }, { 170,1610 }, { 171,1610 }, { 172,1610 }, { 173,1610 },
	{ 174,1610 }, { 175,1610 }, { 176,1610 }, { 177,1610 }, { 178,1610 },
	{ 179,1610 }, { 180,1610 }, { 181,1610 }, { 182,1610 }, { 183,1610 },

	{ 184,1610 }, { 185,1610 }, { 186,1610 }, { 187,1610 }, { 188,1610 },
	{ 189,1610 }, { 190,1610 }, { 191,1610 }, { 192,1610 }, { 193,1610 },
	{ 194,1610 }, { 195,1610 }, { 196,1610 }, { 197,1610 }, { 198,1610 },
	{ 199,1610 }, { 200,1610 }, { 201,1610 }, { 202,1610 }, { 203,1610 },
	{ 204,1610 }, { 205,1610 }, { 206,1610 }, { 207,1610 }, { 208,1610 },
	{ 209,1610 }, { 210,1610 }, { 211,1610 }, { 212,1610 }, { 213,1610 },
	{ 214,1610 }, { 215,1610 }, { 216,1610 }, { 217,1610 }, { 218,1610 },
	{ 219,1610 }, { 220,1610 }, { 221,1610 }, { 222,1610 }, { 223,1610 },
	{ 224,1610 }, { 225,1610 }, { 226,1610 }, { 227,1610 }, { 228,1610 },
	{ 229,1610 }, { 230,1610 }, { 231,1610 }, { 232,1610 }, { 233,1610 },

	{ 234,1610 }, { 235,1610 }, { 236,1610 }, { 237,1610 }, { 238,1610 },
	{ 239,1610 }, { 240,1610 }, { 241,1610 }, { 242,1610 }, { 243,1610 },
	{ 244,1610 }, { 245,1610 }, { 246,1610 }, { 247,1610 }, { 248,1610 },
	{ 249,1610 }, { 250,1610 }, { 251,1610 }, { 252,1610 }, { 253,1610 },
	{ 254,1610 }, { 255,1610 }, { 256,1610 }, {   0,   0 }, {   0,3157 },
	{   1,1352 }, {   2,1352 }, {   3,1352 }, {   4,1352 }, {   5,1352 },
	{   6,1352 }, {   7,1352 }, {   8,1352 }, {   9,1352 }, {  10,1352 },
	{  11,1352 }, {  12,1352 }, {  13,1352 }, {  14,1352 }, {  15,1352 },
	{  16,1352 }, {  17,1352 }, {  18,1352 }, {  19,1352 }, {  20,1352 },
	{  21,1352 }, {  22,1352 }, {  23,1352 }, {  24,1352 }, {  25,1352 },

	{  26,1352 }, {  27,1352 }, {  28,1352 }, {  29,1352 }, {  30,1352 },
	{  31,1352 }, {  32,1352 }, {  33,1352 }, {  34,1352 }, {  35,1352 },
	{  36,1352 }, {  37,1352 }, {  38,1352 }, {  39,1352 }, {  40,1352 },
	{  41,1352 }, {  42,1352 }, {  43,1352 }, {  44,1352 }, {   0,   0 },
	{  46,1352 }, {  47,1352 }, {  48,1352 }, {  49,1352 }, {  50,1352 },
	{  51,1352 }, {  52,1352 }, {  53,1352 }, {  54,1352 }, {  55,1352 },
	{  56,1352 }, {  57,1352 }, {  58,1352 }, {  59,1352 }, {  60,1352 },
	{  61,1352 }, {  62,1352 }, {  63,1352 }, {  64,1352 }, {  65,1352 },
	{  66,1352 }, {  67,1352 }, {  68,1352 }, {  69,1352 }, {  70,1352 },
	{  71,1352 }, {  72,1352 }, {  73,1352 }, {  74,1352 }, {  75,1352 },

	{  76,1352 }, {  77,1352 }, {  78,1352 }, {  79,1352 }, {  80,1352 },
	{  81,1352 }, {  82,1352 }, {  83,1352 }, {  84,1352 }, {  85,1352 },
	{  86,1352 }, {  87,1352 }, {  88,1352 }, {  89,1352 }, {  90,1352 },
	{  91,1352 }, {  92,1352 }, {  93,1352 }, {  94,1352 }, {  95,1352 },
	{  96,1352 }, {  97,1352 }, {  98,1352 }, {  99,1352 }, { 100,1352 },
	{ 101,1352 }, { 102,1352 }, { 103,1352 }, { 104,1352 }, { 105,1352 },
	{ 106,1352 }, { 107,1352 }, { 108,1352 }, { 109,1352 }, { 110,1352 },
	{ 111,1352 }, { 112,1352 }, { 113,1352 }, { 114,1352 }, { 115,1352 },
	{ 116,1352 }, { 117,1352 }, { 118,1352 }, { 119,1352 }, { 120,1352 },
	{ 121,1352 }, { 122,1352 }, { 123,1352 }, { 124,1352 }, { 125,1352 },

	{ 126,1352 }, { 127,1352 }, { 128,1352 }, { 129,1352 }, { 130,1352 },
	{ 131,1352 }, { 132,1352 }, { 133,1352 }, { 134,1352 }, { 135,1352 },
	{ 136,1352 }, { 137,1352 }, { 138,1352 }, { 139,1352 }, { 140,1352 },
	{ 141,1352 }, { 142,1352 }, { 143,1352 }, { 144,1352 }, { 145,1352 },
	{ 146,1352 }, { 147,1352 }, { 148,1352 }, { 149,1352 }, { 150,1352 },
	{ 151,1352 }, { 152,1352 }, { 153,1352 }, { 154,1352 }, { 155,1352 },
	{ 156,1352 }, { 157,1352 }, { 158,1352 }, { 159,1352 }, { 160,1352 },
	{ 161,1352 }, { 162,1352 }, { 163,1352 }, { 164,1352 }, { 165,1352 },
	{ 166,1352 }, { 167,1352 }, { 168,1352 }, { 169,1352 }, { 170,1352 },
	{ 171,1352 }, { 172,1352 }, { 173,1352 }, { 174,1352 }, { 175,1352 },

	{ 176,1352 }, { 177,1352 }, { 178,1352 }, { 179,1352 }, { 180,1352 },
	{ 181,1352 }, { 182,1352 }, { 183,1352 }, { 184,1352 }, { 185,1352 },
	{ 186,1352 }, { 187,1352 }, { 188,1352 }, { 189,1352 }, { 190,1352 },
	{ 191,1352 }, { 192,1352 }, { 193,1352 }, { 194,1352 }, { 195,1352 },
	{ 196,1352 }, { 197,1352 }, { 198,1352 }, { 199,1352 }, { 200,1352 },
	{ 201,1352 }, { 202,1352 }, { 203,1352 }, { 204,1352 }, { 205,1352 },
	{ 206,1352 }, { 207,1352 }, { 208,1352 }, { 209,1352 }, { 210,1352 },
	{ 211,1352 }, { 212,1352 }, { 213,1352 }, { 214,1352 }, { 215,1352 },
	{ 216,1352 }, { 217,1352 }, { 218,1352 }, { 219,1352 }, { 220,1352 },
	{ 221,1352 }, { 222,1352 }, { 223,1352 }, { 224,1352 }, { 225,1352 },

	{ 226,1352 }, { 227,1352 }, { 228,1352 }, { 229,1352 }, { 230,1352 },
	{ 231,1352 }, { 232,1352 }, { 233,1352 }, { 234,1352 }, { 235,1352 },
	{ 236,1352 }, { 237,1352 }, { 238,1352 }, { 239,1352 }, { 240,1352 },
	{ 241,1352 }, { 242,1352 }, { 243,1352 }, { 244,1352 }, { 245,1352 },
	{ 246,1352 }, { 247,1352 }, { 248,1352 }, { 249,1352 }, { 250,1352 },
	{ 251,1352 }, { 252,1352 }, { 253,1352 }, { 254,1352 }, { 255,1352 },
	{ 256,1352 }, {   0,   8 }, {   0,2899 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },

	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {  45,1352 }, {  46,1352 }, {   0,   0 },
	{  48,1352 }, {  49,1352 }, {  50,1352 }, {  51,1352 }, {  52,1352 },
	{  53,1352 }, {  54,1352 }, {  55,1352 }, {  56,1352 }, {  57,1352 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {  65,1352 }, {  66,1352 }, {  67,1352 },

	{  68,1352 }, {  69,1352 }, {  70,1352 }, {  71,1352 }, {  72,1352 },
	{  73,1352 }, {  74,1352 }, {  75,1352 }, {  76,1352 }, {  77,1352 },
	{  78,1352 }, {  79,1352 }, {  80,1352 }, {  81,1352 }, {  82,1352 },
	{  83,1352 }, {  84,1352 }, {  85,1352 }, {  86,1352 }, {  87,1352 },
	{  88,1352 }, {  89,1352 }, {  90,1352 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {  95,1352 }, {   0,   0 }, {  97,1352 },
	{  98,1352 }, {  99,1352 }, { 100,1352 }, { 101,1352 }, { 102,1352 },
	{ 103,1352 }, { 104,1352 }, { 105,1352 }, { 106,1352 }, { 107,1352 },
	{ 108,1352 }, { 109,1352 }, { 110,1352 }, { 111,1352 }, { 112,1352 },
	{ 113,1352 }, { 114,1352 }, { 115,1352 }, { 116,1352 }, { 117,1352 },

	{ 118,1352 }, { 119,1352 }, { 120,1352 }, { 121,1352 }, { 122,1352 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{ 128,1352 }, { 129,1352 }, { 130,1352 }, { 131,1352 }, { 132,1352 },
	{ 133,1352 }, { 134,1352 }, { 135,1352 }, { 136,1352 }, { 137,1352 },
	{ 138,1352 }, { 139,1352 }, { 140,1352 }, { 141,1352 }, { 142,1352 },
	{ 143,1352 }, { 144,1352 }, { 145,1352 }, { 146,1352 }, { 147,1352 },
	{ 148,1352 }, { 149,1352 }, { 150,1352 }, { 151,1352 }, { 152,1352 },
	{ 153,1352 }, { 154,1352 }, { 155,1352 }, { 156,1352 }, { 157,1352 },
	{ 158,1352 }, { 159,1352 }, { 160,1352 }, { 161,1352 }, { 162,1352 },
	{ 163,1352 }, { 164,1352 }, { 165,1352 }, { 166,1352 }, { 167,1352 },

	{ 168,1352 }, { 169,1352 }, { 170,1352 }, { 171,1352 }, { 172,1352 },
	{ 173,1352 }, { 174,1352 }, { 175,1352 }, { 176,1352 }, { 177,1352 },
	{ 178,1352 }, { 179,1352 }, { 180,1352 }, { 181,1352 }, { 182,1352 },
	{ 183,1352 }, { 184,1352 }, { 185,1352 }, { 186,1352 }, { 187,1352 },
	{ 188,1352 }, { 189,1352 }, { 190,1352 }, { 191,1352 }, { 192,1352 },
	{ 193,1352 }, { 194,1352 }, { 195,1352 }, { 196,1352 }, { 197,1352 },
	{ 198,1352 }, { 199,1352 }, { 200,1352 }, { 201,1352 }, { 202,1352 },
	{ 203,1352 }, { 204,1352 }, { 205,1352 }, { 206,1352 }, { 207,1352 },
	{ 208,1352 }, { 209,1352 }, { 210,1352 }, { 211,1352 }, { 212,1352 },
	{ 213,1352 }, { 214,1352 }, { 215,1352 }, { 216,1352 }, { 217,1352 },

	{ 218,1352 }, { 219,1352 }, { 220,1352 }, { 221,1352 }, { 222,1352 },
	{ 223,1352 }, { 224,1352 }, { 225,1352 }, { 226,1352 }, { 227,1352 },
	{ 228,1352 }, { 229,1352 }, { 230,1352 }, { 231,1352 }, { 232,1352 },
	{ 233,1352 }, { 234,1352 }, { 235,1352 }, { 236,1352 }, { 237,1352 },
	{ 238,1352 }, { 239,1352 }, { 240,1352 }, { 241,1352 }, { 242,1352 },
	{ 243,1352 }, { 244,1352 }, { 245,1352 }, { 246,1352 }, { 247,1352 },
	{ 248,1352 }, { 249,1352 }, { 250,1352 }, { 251,1352 }, { 252,1352 },
	{ 253,1352 }, { 254,1352 }, { 255,1352 }, {   0,   5 }, {   0,2642 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },

	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  45,   0 },
	{  46,   0 }, {   0,   0 }, {  48,   0 }, {  49,   0 }, {  50,   0 },
	{  51,   0 }, {  52,   0 }, {  53,   0 }, {  54,   0 }, {  55,   0 },
	{  56,   0 }, {  57,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },

	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  65,   0 },
	{  66,   0 }, {  67,   0 }, {  68,   0 }, {  69,   0 }, {  70,   0 },
	{  71,   0 }, {  72,   0 }, {  73,   0 }, {  74,   0 }, {  75,   0 },
	{  76,   0 }, {  77,   0 }, {  78,   0 }, {  79,   0 }, {  80,   0 },
	{  81,   0 }, {  82,   0 }, {  83,   0 }, {  84,   0 }, {  85,   0 },
	{  86,   0 }, {  87,   0 }, {  88,   0 }, {  89,   0 }, {  90,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  95,   0 },
	{   0,   0 }, {  97,   0 }, {  98,   0 }, {  99,   0 }, { 100,   0 },
	{ 101,   0 }, { 102,   0 }, { 103,   0 }, { 104,   0 }, { 105,   0 },
	{ 106,   0 }, { 107,   0 }, { 108,   0 }, { 109,   0 }, { 110,   0 },

	{ 111,   0 }, { 112,   0 }, { 113,   0 }, { 114,   0 }, { 115,   0 },
	{ 116,   0 }, { 117,   0 }, { 118,   0 }, { 119,   0 }, { 120,   0 },
	{ 121,   0 }, { 122,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, { 128,   0 }, { 129,   0 }, { 130,   0 },
	{ 131,   0 }, { 132,   0 }, { 133,   0 }, { 134,   0 }, { 135,   0 },
	{ 136,   0 }, { 137,   0 }, { 138,   0 }, { 139,   0 }, { 140,   0 },
	{ 141,   0 }, { 142,   0 }, { 143,   0 }, { 144,   0 }, { 145,   0 },
	{ 146,   0 }, { 147,   0 }, { 148,   0 }, { 149,   0 }, { 150,   0 },
	{ 151,   0 }, { 152,   0 }, { 153,   0 }, { 154,   0 }, { 155,   0 },
	{ 156,   0 }, { 157,   0 }, { 158,   0 }, { 159,   0 }, { 160,   0 },

	{ 161,   0 }, { 162,   0 }, { 163,   0 }, { 164,   0 }, { 165,   0 },
	{ 166,   0 }, { 167,   0 }, { 168,   0 }, { 169,   0 }, { 170,   0 },
	{ 171,   0 }, { 172,   0 }, { 173,   0 }, { 174,   0 }, { 175,   0 },
	{ 176,   0 }, { 177,   0 }, { 178,   0 }, { 179,   0 }, { 180,   0 },
	{ 181,   0 }, { 182,   0 }, { 183,   0 }, { 184,   0 }, { 185,   0 },
	{ 186,   0 }, { 187,   0 }, { 188,   0 }, { 189,   0 }, { 190,   0 },
	{ 191,   0 }, { 192,   0 }, { 193,   0 }, { 194,   0 }, { 195,   0 },
	{ 196,   0 }, { 197,   0 }, { 198,   0 }, { 199,   0 }, { 200,   0 },
	{ 201,   0 }, { 202,   0 }, { 203,   0 }, { 204,   0 }, { 205,   0 },
	{ 206,   0 }, { 207,   0 }, { 208,   0 }, { 209,   0 }, { 210,   0 },

	{ 211,   0 }, { 212,   0 }, { 213,   0 }, { 214,   0 }, { 215,   0 },
	{ 216,   0 }, { 217,   0 }, { 218,   0 }, { 219,   0 }, { 220,   0 },
	{ 221,   0 }, { 222,   0 }, { 223,   0 }, { 224,   0 }, { 225,   0 },
	{ 226,   0 }, { 227,   0 }, { 228,   0 }, { 229,   0 }, { 230,   0 },
	{ 231,   0 }, { 232,   0 }, { 233,   0 }, { 234,   0 }, { 235,   0 },
	{ 236,   0 }, { 237,   0 }, { 238,   0 }, { 239,   0 }, { 240,   0 },
	{ 241,   0 }, { 242,   0 }, { 243,   0 }, { 244,   0 }, { 245,   0 },
	{ 246,   0 }, { 247,   0 }, { 248,   0 }, { 249,   0 }, { 250,   0 },
	{ 251,   0 }, { 252,   0 }, { 253,   0 }, { 254,   0 }, { 255,   0 },
	{   0,  12 }, {   0,2385 }, {   1,   0 }, {   2,   0 }, {   3,   0 },

	{   4,   0 }, {   5,   0 }, {   6,   0 }, {   7,   0 }, {   8,   0 },
	{   9,   0 }, {   0,   0 }, {  11,   0 }, {  12,   0 }, {  13,   0 },
	{  14,   0 }, {  15,   0 }, {  16,   0 }, {  17,   0 }, {  18,   0 },
	{  19,   0 }, {  20,   0 }, {  21,   0 }, {  22,   0 }, {  23,   0 },
	{  24,   0 }, {  25,   0 }, {  26,   0 }, {  27,   0 }, {  28,   0 },
	{  29,   0 }, {  30,   0 }, {  31,   0 }, {  32,   0 }, {  33,   0 },
	{  34,   0 }, {  35,   0 }, {  36,   0 }, {  37,   0 }, {   0,   0 },
	{  39,   0 }, {  40,   0 }, {  41,   0 }, {  42,   0 }, {  43,   0 },
	{  44,   0 }, {  45,   0 }, {  46,   0 }, {  47,   0 }, {  48,   0 },
	{  49,   0 }, {  50,   0 }, {  51,   0 }, {  52,   0 }, {  53,   0 },

	{  54,   0 }, {  55,   0 }, {  56,   0 }, {  57,   0 }, {  58,   0 },
	{  59,   0 }, {   0,   0 }, {  61,   0 }, {  62,   0 }, {  63,   0 },
	{  64,   0 }, {  65,   0 }, {  66,   0 }, {  67,   0 }, {  68,   0 },
	{  69,   0 }, {  70,   0 }, {  71,   0 }, {  72,   0 }, {  73,   0 },
	{  74,   0 }, {  75,   0 }, {  76,   0 }, {  77,   0 }, {  78,   0 },
	{  79,   0 }, {  80,   0 }, {  81,   0 }, {  82,   0 }, {  83,   0 },
	{  84,   0 }, {  85,   0 }, {  86,   0 }, {  87,   0 }, {  88,   0 },
	{  89,   0 }, {  90,   0 }, {  91,   0 }, {  92,   0 }, {  93,   0 },
	{  94,   0 }, {  95,   0 }, {  96,   0 }, {  97,   0 }, {  98,   0 },
	{  99,   0 }, { 100,   0 }, { 101,   0 }, { 102,   0 }, { 103,   0 },

	{ 104,   0 }, { 105,   0 }, { 106,   0 }, { 107,   0 }, { 108,   0 },
	{ 109,   0 }, { 110,   0 }, { 111,   0 }, { 112,   0 }, { 113,   0 },
	{ 114,   0 }, { 115,   0 }, { 116,   0 }, { 117,   0 }, { 118,   0 },
	{ 119,   0 }, { 120,   0 }, { 121,   0 }, { 122,   0 }, { 123,   0 },
	{ 124,   0 }, { 125,   0 }, { 126,   0 }, { 127,   0 }, { 128,   0 },
	{ 129,   0 }, { 130,   0 }, { 131,   0 }, { 132,   0 }, { 133,   0 },
	{ 134,   0 }, { 135,   0 }, { 136,   0 }, { 137,   0 }, { 138,   0 },
	{ 139,   0 }, { 140,   0 }, { 141,   0 }, { 142,   0 }, { 143,   0 },
	{ 144,   0 }, { 145,   0 }, { 146,   0 }, { 147,   0 }, { 148,   0 },
	{ 149,   0 }, { 150,   0 }, { 151,   0 }, { 152,   0 }, { 153,   0 },

	{ 154,   0 }, { 155,   0 }, { 156,   0 }, { 157,   0 }, { 158,   0 },
	{ 159,   0 }, { 160,   0 }, { 161,   0 }, { 162,   0 }, { 163,   0 },
	{ 164,   0 }, { 165,   0 }, { 166,   0 }, { 167,   0 }, { 168,   0 },
	{ 169,   0 }, { 170,   0 }, { 171,   0 }, { 172,   0 }, { 173,   0 },
	{ 174,   0 }, { 175,   0 }, { 176,   0 }, { 177,   0 }, { 178,   0 },
	{ 179,   0 }, { 180,   0 }, { 181,   0 }, { 182,   0 }, { 183,   0 },
	{ 184,   0 }, { 185,   0 }, { 186,   0 }, { 187,   0 }, { 188,   0 },
	{ 189,   0 }, { 190,   0 }, { 191,   0 }, { 192,   0 }, { 193,   0 },
	{ 194,   0 }, { 195,   0 }, { 196,   0 }, { 197,   0 }, { 198,   0 },
	{ 199,   0 }, { 200,   0 }, { 201,   0 }, { 202,   0 }, { 203,   0 },

	{ 204,   0 }, { 205,   0 }, { 206,   0 }, { 207,   0 }, { 208,   0 },
	{ 209,   0 }, { 210,   0 }, { 211,   0 }, { 212,   0 }, { 213,   0 },
	{ 214,   0 }, { 215,   0 }, { 216,   0 }, { 217,   0 }, { 218,   0 },
	{ 219,   0 }, { 220,   0 }, { 221,   0 }, { 222,   0 }, { 223,   0 },
	{ 224,   0 }, { 225,   0 }, { 226,   0 }, { 227,   0 }, { 228,   0 },
	{ 229,   0 }, { 230,   0 }, { 231,   0 }, { 232,   0 }, { 233,   0 },
	{ 234,   0 }, { 235,   0 }, { 236,   0 }, { 237,   0 }, { 238,   0 },
	{ 239,   0 }, { 240,   0 }, { 241,   0 }, { 242,   0 }, { 243,   0 },
	{ 244,   0 }, { 245,   0 }, { 246,   0 }, { 247,   0 }, { 248,   0 },
	{ 249,   0 }, { 250,   0 }, { 251,   0 }, { 252,   0 }, { 253,   0 },

	{ 254,   0 }, { 255,   0 }, { 256,   0 }, {   0,  12 }, {   0,2127 },
	{   1,-258 }, {   2,-258 }, {   3,-258 }, {   4,-258 }, {   5,-258 },
	{   6,-258 }, {   7,-258 }, {   8,-258 }, {   9,   0 }, {  10, 258 },
	{  11,-258 }, {  12,-258 }, {  13,   0 }, {  14,-258 }, {  15,-258 },
	{  16,-258 }, {  17,-258 }, {  18,-258 }, {  19,-258 }, {  20,-258 },
	{  21,-258 }, {  22,-258 }, {  23,-258 }, {  24,-258 }, {  25,-258 },
	{  26,-258 }, {  27,-258 }, {  28,-258 }, {  29,-258 }, {  30,-258 },
	{  31,-258 }, {  32,   0 }, {  33,-258 }, {  34,-258 }, {  35,-258 },
	{  36,-258 }, {  37,-258 }, {   0,   0 }, {  39,-258 }, {  40,-258 },
	{  41,-258 }, {  42,-258 }, {  43,-258 }, {  44,-258 }, {  45,-258 },

	{  46,-258 }, {  47,-258 }, {  48,-258 }, {  49,-258 }, {  50,-258 },
	{  51,-258 }, {  52,-258 }, {  53,-258 }, {  54,-258 }, {  55,-258 },
	{  56,-258 }, {  57,-258 }, {  58,-258 }, {  59,-258 }, {  60,-2380 },
	{  61,-258 }, {  62,-258 }, {  63,-258 }, {  64,-258 }, {  65,-258 },
	{  66,-258 }, {  67,-258 }, {  68,-258 }, {  69,-258 }, {  70,-258 },
	{  71,-258 }, {  72,-258 }, {  73,-258 }, {  74,-258 }, {  75,-258 },
	{  76,-258 }, {  77,-258 }, {  78,-258 }, {  79,-258 }, {  80,-258 },
	{  81,-258 }, {  82,-258 }, {  83,-258 }, {  84,-258 }, {  85,-258 },
	{  86,-258 }, {  87,-258 }, {  88,-258 }, {  89,-258 }, {  90,-258 },
	{  91,-258 }, {  92,-258 }, {  93,-258 }, {  94,-258 }, {  95,-258 },

	{  96,-258 }, {  97,-258 }, {  98,-258 }, {  99,-258 }, { 100,-258 },
	{ 101,-258 }, { 102,-258 }, { 103,-258 }, { 104,-258 }, { 105,-258 },
	{ 106,-258 }, { 107,-258 }, { 108,-258 }, { 109,-258 }, { 110,-258 },
	{ 111,-258 }, { 112,-258 }, { 113,-258 }, { 114,-258 }, { 115,-258 },
	{ 116,-258 }, { 117,-258 }, { 118,-258 }, { 119,-258 }, { 120,-258 },
	{ 121,-258 }, { 122,-258 }, { 123,-258 }, { 124,-258 }, { 125,-258 },
	{ 126,-258 }, { 127,-258 }, { 128,-258 }, { 129,-258 }, { 130,-258 },
	{ 131,-258 }, { 132,-258 }, { 133,-258 }, { 134,-258 }, { 135,-258 },
	{ 136,-258 }, { 137,-258 }, { 138,-258 }, { 139,-258 }, { 140,-258 },
	{ 141,-258 }, { 142,-258 }, { 143,-258 }, { 144,-258 }, { 145,-258 },

	{ 146,-258 }, { 147,-258 }, { 148,-258 }, { 149,-258 }, { 150,-258 },
	{ 151,-258 }, { 152,-258 }, { 153,-258 }, { 154,-258 }, { 155,-258 },
	{ 156,-258 }, { 157,-258 }, { 158,-258 }, { 159,-258 }, { 160,-258 },
	{ 161,-258 }, { 162,-258 }, { 163,-258 }, { 164,-258 }, { 165,-258 },
	{ 166,-258 }, { 167,-258 }, { 168,-258 }, { 169,-258 }, { 170,-258 },
	{ 171,-258 }, { 172,-258 }, { 173,-258 }, { 174,-258 }, { 175,-258 },
	{ 176,-258 }, { 177,-258 }, { 178,-258 }, { 179,-258 }, { 180,-258 },
	{ 181,-258 }, { 182,-258 }, { 183,-258 }, { 184,-258 }, { 185,-258 },
	{ 186,-258 }, { 187,-258 }, { 188,-258 }, { 189,-258 }, { 190,-258 },
	{ 191,-258 }, { 192,-258 }, { 193,-258 }, { 194,-258 }, { 195,-258 },

	{ 196,-258 }, { 197,-258 }, { 198,-258 }, { 199,-258 }, { 200,-258 },
	{ 201,-258 }, { 202,-258 }, { 203,-258 }, { 204,-258 }, { 205,-258 },
	{ 206,-258 }, { 207,-258 }, { 208,-258 }, { 209,-258 }, { 210,-258 },
	{ 211,-258 }, { 212,-258 }, { 213,-258 }, { 214,-258 }, { 215,-258 },
	{ 216,-258 }, { 217,-258 }, { 218,-258 }, { 219,-258 }, { 220,-258 },
	{ 221,-258 }, { 222,-258 }, { 223,-258 }, { 224,-258 }, { 225,-258 },
	{ 226,-258 }, { 227,-258 }, { 228,-258 }, { 229,-258 }, { 230,-258 },
	{ 231,-258 }, { 232,-258 }, { 233,-258 }, { 234,-258 }, { 235,-258 },
	{ 236,-258 }, { 237,-258 }, { 238,-258 }, { 239,-258 }, { 240,-258 },
	{ 241,-258 }, { 242,-258 }, { 243,-258 }, { 244,-258 }, { 245,-258 },

	{ 246,-258 }, { 247,-258 }, { 248,-258 }, { 249,-258 }, { 250,-258 },
	{ 251,-258 }, { 252,-258 }, { 253,-258 }, { 254,-258 }, { 255,-258 },
	{ 256,-258 }, {   0,   0 }, {   0,1869 }, {   0,  14 }, {   0,1867 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   9,   0 }, {  10,   0 }, {   9,  -2 }, {  10,  -2 },
	{  13,   0 }, {   0,   0 }, {  13,  -2 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  32,   0 },
	{   0,   0 }, {  32,  -2 }, {   0,   0 }, {   0,   0 }, {   0,   0 },

	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {  60,-2638 }, {   0,   0 }, {  60,-2640 },
	{   0,   0 }, {   0,1805 }, {   1, 515 }, {   2, 515 }, {   3, 515 },
	{   4, 515 }, {   5, 515 }, {   6, 515 }, {   7, 515 }, {   8, 515 },
	{   9, 515 }, {  10, 515 }, {  11, 515 }, {  12, 515 }, {  13, 515 },
	{  14, 515 }, {  15, 515 }, {  16, 515 }, {  17, 515 }, {  18, 515 },
	{  19, 515 }, {  20, 515 }, {  21, 515 }, {  22, 515 }, {  23, 515 },

	{  24, 515 }, {  25, 515 }, {  26, 515 }, {  27, 515 }, {  28, 515 },
	{  29, 515 }, {  30, 515 }, {  31, 515 }, {  32, 515 }, {  33, 515 },
	{  34, 515 }, {  35, 515 }, {  36, 515 }, {  37, 515 }, {  38, 515 },
	{  39, 515 }, {  40, 515 }, {  41, 515 }, {  42, 515 }, {  43, 515 },
	{  44, 515 }, {  45, 515 }, {  46, 515 }, {  47, 515 }, {  48, 515 },
	{  49, 515 }, {  50, 515 }, {  51, 515 }, {  52, 515 }, {  53, 515 },
	{  54, 515 }, {  55, 515 }, {  56, 515 }, {  57, 515 }, {  58, 515 },
	{  59, 515 }, {  60, 515 }, {  61, 515 }, {  62,-3795 }, {  63, 515 },
	{  64, 515 }, {  65, 515 }, {  66, 515 }, {  67, 515 }, {  68, 515 },
	{  69, 515 }, {  70, 515 }, {  71, 515 }, {  72, 515 }, {  73, 515 },

	{  74, 515 }, {  75, 515 }, {  76, 515 }, {  77, 515 }, {  78, 515 },
	{  79, 515 }, {  80, 515 }, {  81, 515 }, {  82, 515 }, {  83, 515 },
	{  84, 515 }, {  85, 515 }, {  86, 515 }, {  87, 515 }, {  88, 515 },
	{  89, 515 }, {  90, 515 }, {  91, 515 }, {  92, 515 }, {  93, 515 },
	{  94, 515 }, {  95, 515 }, {  96, 515 }, {  97, 515 }, {  98, 515 },
	{  99, 515 }, { 100, 515 }, { 101, 515 }, { 102, 515 }, { 103, 515 },
	{ 104, 515 }, { 105, 515 }, { 106, 515 }, { 107, 515 }, { 108, 515 },
	{ 109, 515 }, { 110, 515 }, { 111, 515 }, { 112, 515 }, { 113, 515 },
	{ 114, 515 }, { 115, 515 }, { 116, 515 }, { 117, 515 }, { 118, 515 },
	{ 119, 515 }, { 120, 515 }, { 121, 515 }, { 122, 515 }, { 123, 515 },

	{ 124, 515 }, { 125, 515 }, { 126, 515 }, { 127, 515 }, { 128, 515 },
	{ 129, 515 }, { 130, 515 }, { 131, 515 }, { 132, 515 }, { 133, 515 },
	{ 134, 515 }, { 135, 515 }, { 136, 515 }, { 137, 515 }, { 138, 515 },
	{ 139, 515 }, { 140, 515 }, { 141, 515 }, { 142, 515 }, { 143, 515 },
	{ 144, 515 }, { 145, 515 }, { 146, 515 }, { 147, 515 }, { 148, 515 },
	{ 149, 515 }, { 150, 515 }, { 151, 515 }, { 152, 515 }, { 153, 515 },
	{ 154, 515 }, { 155, 515 }, { 156, 515 }, { 157, 515 }, { 158, 515 },
	{ 159, 515 }, { 160, 515 }, { 161, 515 }, { 162, 515 }, { 163, 515 },
	{ 164, 515 }, { 165, 515 }, { 166, 515 }, { 167, 515 }, { 168, 515 },
	{ 169, 515 }, { 170, 515 }, { 171, 515 }, { 172, 515 }, { 173, 515 },

	{ 174, 515 }, { 175, 515 }, { 176, 515 }, { 177, 515 }, { 178, 515 },
	{ 179, 515 }, { 180, 515 }, { 181, 515 }, { 182, 515 }, { 183, 515 },
	{ 184, 515 }, { 185, 515 }, { 186, 515 }, { 187, 515 }, { 188, 515 },
	{ 189, 515 }, { 190, 515 }, { 191, 515 }, { 192, 515 }, { 193, 515 },
	{ 194, 515 }, { 195, 515 }, { 196, 515 }, { 197, 515 }, { 198, 515 },
	{ 199, 515 }, { 200, 515 }, { 201, 515 }, { 202, 515 }, { 203, 515 },
	{ 204, 515 }, { 205, 515 }, { 206, 515 }, { 207, 515 }, { 208, 515 },
	{ 209, 515 }, { 210, 515 }, { 211, 515 }, { 212, 515 }, { 213, 515 },
	{ 214, 515 }, { 215, 515 }, { 216, 515 }, { 217, 515 }, { 218, 515 },
	{ 219, 515 }, { 220, 515 }, { 221, 515 }, { 222, 515 }, { 223, 515 },

	{ 224, 515 }, { 225, 515 }, { 226, 515 }, { 227, 515 }, { 228, 515 },
	{ 229, 515 }, { 230, 515 }, { 231, 515 }, { 232, 515 }, { 233, 515 },
	{ 234, 515 }, { 235, 515 }, { 236, 515 }, { 237, 515 }, { 238, 515 },
	{ 239, 515 }, { 240, 515 }, { 241, 515 }, { 242, 515 }, { 243, 515 },
	{ 244, 515 }, { 245, 515 }, { 246, 515 }, { 247, 515 }, { 248, 515 },
	{ 249, 515 }, { 250, 515 }, { 251, 515 }, { 252, 515 }, { 253, 515 },
	{ 254, 515 }, { 255, 515 }, { 256, 515 }, {   0,   8 }, {   0,1547 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },

	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  45,   0 },
	{  46,   0 }, {   0,   0 }, {  48,   0 }, {  49,   0 }, {  50,   0 },
	{  51,   0 }, {  52,   0 }, {  53,   0 }, {  54,   0 }, {  55,   0 },
	{  56,   0 }, {  57,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  65,   0 },

	{  66,   0 }, {  67,   0 }, {  68,   0 }, {  69,   0 }, {  70,   0 },
	{  71,   0 }, {  72,   0 }, {  73,   0 }, {  74,   0 }, {  75,   0 },
	{  76,   0 }, {  77,   0 }, {  78,   0 }, {  79,   0 }, {  80,   0 },
	{  81,   0 }, {  82,   0 }, {  83,   0 }, {  84,   0 }, {  85,   0 },
	{  86,   0 }, {  87,   0 }, {  88,   0 }, {  89,   0 }, {  90,   0 },
	{   0,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 }, {  95,   0 },
	{   0,   0 }, {  97,   0 }, {  98,   0 }, {  99,   0 }, { 100,   0 },
	{ 101,   0 }, { 102,   0 }, { 103,   0 }, { 104,   0 }, { 105,   0 },
	{ 106,   0 }, { 107,   0 }, { 108,   0 }, { 109,   0 }, { 110,   0 },
	{ 111,   0 }, { 112,   0 }, { 113,   0 }, { 114,   0 }, { 115,   0 },

	{ 116,   0 }, { 117,   0 }, { 118,   0 }, { 119,   0 }, { 120,   0 },
	{ 121,   0 }, { 122,   0 }, {   0,   0 }, {   0,   0 }, {   0,   0 },
	{   0,   0 }, {   0,   0 }, { 128,   0 }, { 129,   0 }, { 130,   0 },
	{ 131,   0 }, { 132,   0 }, { 133,   0 }, { 134,   0 }, { 135,   0 },
	{ 136,   0 }, { 137,   0 }, { 138,   0 }, { 139,   0 }, { 140,   0 },
	{ 141,   0 }, { 142,   0 }, { 143,   0 }, { 144,   0 }, { 145,   0 },
	{ 146,   0 }, { 147,   0 }, { 148,   0 }, { 149,   0 }, { 150,   0 },
	{ 151,   0 }, { 152,   0 }, { 153,   0 }, { 154,   0 }, { 155,   0 },
	{ 156,   0 }, { 157,   0 }, { 158,   0 }, { 159,   0 }, { 160,   0 },
	{ 161,   0 }, { 162,   0 }, { 163,   0 }, { 164,   0 }, { 165,   0 },

	{ 166,   0 }, { 167,   0 }, { 168,   0 }, { 169,   0 }, { 170,   0 },
	{ 171,   0 }, { 172,   0 }, { 173,   0 }, { 174,   0 }, { 175,   0 },
	{ 176,   0 }, { 177,   0 }, { 178,   0 }, { 179,   0 }, { 180,   0 },
	{ 181,   0 }, { 182,   0 }, { 183,   0 }, { 184,   0 }, { 185,   0 },
	{ 186,   0 }, { 187,   0 }, { 188,   0 }, { 189,   0 }, { 190,   0 },
	{ 191,   0 }, { 192,   0 }, { 193,   0 }, { 194,   0 }, { 195,   0 },
	{ 196,   0 }, { 197,   0 }, { 198,   0 }, { 199,   0 }, { 200,   0 },
	{ 201,   0 }, { 202,   0 }, { 203,   0 }, { 204,   0 }, { 205,   0 },
	{ 206,   0 }, { 207,   0 }, { 208,   0 }, { 209,   0 }, { 210,   0 },
	{ 211,   0 }, { 212,   0 }, { 213,   0 }, { 214,   0 }, { 215,   0 },

	{ 216,   0 }, { 217,   0 }, { 218,   0 }, { 219,   0 }, { 220,   0 },
	{ 221,   0 }, { 222,   0 }, { 223,   0 }, { 224,   0 }, { 225,   0 },
	{ 226,   0 }, { 227,   0 }, { 228,   0 }, { 229,   0 }, { 230,   0 },
	{ 231,   0 }, { 232,   0 }, { 233,   0 }, { 234,   0 }, { 235,   0 },
	{ 236,   0 }, { 237,   0 }, { 238,   0 }, { 239,   0 }, { 240,   0 },
	{ 241,   0 }, { 242,   0 }, { 243,   0 }, { 244,   0 }, { 245,   0 },
	{ 246,   0 }, { 247,   0 }, { 248,   0 }, { 249,   0 }, { 250,   0 },
	{ 251,   0 }, { 252,   0 }, { 253,   0 }, { 254,   0 }, { 255,   0 },
	{   0,   0 }, {   0,1290 }, {   1,   0 }, {   2,   0 }, {   3,   0 },
	{   4,   0 }, {   5,   0 }, {   6,   0 }, {   7,   0 }, {   8,   0 },

	{   9,   0 }, {  10,   0 }, {  11,   0 }, {  12,   0 }, {  13,   0 },
	{  14,   0 }, {  15,   0 }, {  16,   0 }, {  17,   0 }, {  18,   0 },
	{  19,   0 }, {  20,   0 }, {  21,   0 }, {  22,   0 }, {  23,   0 },
	{  24,   0 }, {  25,   0 }, {  26,   0 }, {  27,   0 }, {  28,   0 },
	{  29,   0 }, {  30,   0 }, {  31,   0 }, {  32,   0 }, {  33,   0 },
	{  34,   0 }, {  35,   0 }, {  36,   0 }, {  37,   0 }, {  38,   0 },
	{  39,   0 }, {  40,   0 }, {  41,   0 }, {  42,   0 }, {  43,   0 },
	{  44,   0 }, {  45,   0 }, {  46,   0 }, {  47,   0 }, {  48,   0 },
	{  49,   0 }, {  50,   0 }, {  51,   0 }, {  52,   0 }, {  53,   0 },
	{  54,   0 }, {  55,   0 }, {  56,   0 }, {  57,   0 }, {  58,   0 },

	{  59,   0 }, {  60,   0 }, {  61,   0 }, {  62,-4310 }, {  63,   0 },
	{  64,   0 }, {  65,   0 }, {  66,   0 }, {  67,   0 }, {  68,   0 },
	{  69,   0 }, {  70,   0 }, {  71,   0 }, {  72,   0 }, {  73,   0 },
	{  74,   0 }, {  75,   0 }, {  76,   0 }, {  77,   0 }, {  78,   0 },
	{  79,   0 }, {  80,   0 }, {  81,   0 }, {  82,   0 }, {  83,   0 },
	{  84,   0 }, {  85,   0 }, {  86,   0 }, {  87,   0 }, {  88,   0 },
	{  89,   0 }, {  90,   0 }, {  91,   0 }, {  92,   0 }, {  93,   0 },
	{  94,   0 }, {  95,   0 }, {  96,   0 }, {  97,   0 }, {  98,   0 },
	{  99,   0 }, { 100,   0 }, { 101,   0 }, { 102,   0 }, { 103,   0 },
	{ 104,   0 }, { 105,   0 }, { 106,   0 }, { 107,   0 }, { 108,   0 },

	{ 109,   0 }, { 110,   0 }, { 111,   0 }, { 112,   0 }, { 113,   0 },
	{ 114,   0 }, { 115,   0 }, { 116,   0 }, { 117,   0 }, { 118,   0 },
	{ 119,   0 }, { 120,   0 }, { 121,   0 }, { 122,   0 }, { 123,   0 },
	{ 124,   0 }, { 125,   0 }, { 126,   0 }, { 127,   0 }, { 128,   0 },
	{ 129,   0 }, { 130,   0 }, { 131,   0 }, { 132,   0 }, { 133,   0 },
	{ 134,   0 }, { 135,   0 }, { 136,   0 }, { 137,   0 }, { 138,   0 },
	{ 139,   0 }, { 140,   0 }, { 141,   0 }, { 142,   0 }, { 143,   0 },
	{ 144,   0 }, { 145,   0 }, { 146,   0 }, { 147,   0 }, { 148,   0 },
	{ 149,   0 }, { 150,   0 }, { 151,   0 }, { 152,   0 }, { 153,   0 },
	{ 154,   0 }, { 155,   0 }, { 156,   0 }, { 157,   0 }, { 158,   0 },

	{ 159,   0 }, { 160,   0 }, { 161,   0 }, { 162,   0 }, { 163,   0 },
	{ 164,   0 }, { 165,   0 }, { 166,   0 }, { 167,   0 }, { 168,   0 },
	{ 169,   0 }, { 170,   0 }, { 171,   0 }, { 172,   0 }, { 173,   0 },
	{ 174,   0 }, { 175,   0 }, { 176,   0 }, { 177,   0 }, { 178,   0 },
	{ 179,   0 }, { 180,   0 }, { 181,   0 }, { 182,   0 }, { 183,   0 },
	{ 184,   0 }, { 185,   0 }, { 186,   0 }, { 187,   0 }, { 188,   0 },
	{ 189,   0 }, { 190,   0 }, { 191,   0 }, { 192,   0 }, { 193,   0 },
	{ 194,   0 }, { 195,   0 }, { 196,   0 }, { 197,   0 }, { 198,   0 },
	{ 199,   0 }, { 200,   0 }, { 201,   0 }, { 202,   0 }, { 203,   0 },
	{ 204,   0 }, { 205,   0 }, { 206,   0 }, { 207,   0 }, { 208,   0 },

	{ 209,   0 }, { 210,   0 }, { 211,   0 }, { 212,   0 }, { 213,   0 },
	{ 214,   0 }, { 215,   0 }, { 216,   0 }, { 217,   0 }, { 218,   0 },
	{ 219,   0 }, { 220,   0 }, { 221,   0 }, { 222,   0 }, { 223,   0 },
	{ 224,   0 }, { 225,   0 }, { 226,   0 }, { 227,   0 }, { 228,   0 },
	{ 229,   0 }, { 230,   0 }, { 231,   0 }, { 232,   0 }, { 233,   0 },
	{ 234,   0 }, { 235,   0 }, { 236,   0 }, { 237,   0 }, { 238,   0 },
	{ 239,   0 }, { 240,   0 }, { 241,   0 }, { 242,   0 }, { 243,   0 },
	{ 244,   0 }, { 245,   0 }, { 246,   0 }, { 247,   0 }, { 248,   0 },
	{ 249,   0 }, { 250,   0 }, { 251,   0 }, { 252,   0 }, { 253,   0 },
	{ 254,   0 }, { 255,   0 }, { 256,   0 }, {   0,   0 }, {   0,1032 },

	{   1, 258 }, {   2, 258 }, {   3, 258 }, {   4, 258 }, {   5, 258 },
	{   6, 258 }, {   7, 258 }, {   8, 258 }, {   9, 258 }, {  10, 258 },
	{  11, 258 }, {  12, 258 }, {  13, 258 }, {  14, 258 }, {  15, 258 },
	{  16, 258 }, {  17, 258 }, {  18, 258 }, {  19, 258 }, {  20, 258 },
	{  21, 258 }, {  22, 258 }, {  23, 258 }, {  24, 258 }, {  25, 258 },
	{  26, 258 }, {  27, 258 }, {  28, 258 }, {  29, 258 }, {  30, 258 },
	{  31, 258 }, {  32, 258 }, {  33, 258 }, {  34, 258 }, {  35, 258 },
	{  36, 258 }, {  37, 258 }, {  38, 258 }, {  39, 258 }, {  40, 258 },
	{  41, 258 }, {  42, 258 }, {  43, 258 }, {  44, 258 }, {  45, 516 },
	{  46, 258 }, {  47, 258 }, {  48, 258 }, {  49, 258 }, {  50, 258 },

	{  51, 258 }, {  52, 258 }, {  53, 258 }, {  54, 258 }, {  55, 258 },
	{  56, 258 }, {  57, 258 }, {  58, 258 }, {  59, 258 }, {  60, 258 },
	{  61, 258 }, {  62, 258 }, {  63, 258 }, {  64, 258 }, {  65, 258 },
	{  66, 258 }, {  67, 258 }, {  68, 258 }, {  69, 258 }, {  70, 258 },
	{  71, 258 }, {  72, 258 }, {  73, 258 }, {  74, 258 }, {  75, 258 },
	{  76, 258 }, {  77, 258 }, {  78, 258 }, {  79, 258 }, {  80, 258 },
	{  81, 258 }, {  82, 258 }, {  83, 258 }, {  84, 258 }, {  85, 258 },
	{  86, 258 }, {  87, 258 }, {  88, 258 }, {  89, 258 }, {  90, 258 },
	{  91, 258 }, {  92, 258 }, {  93, 258 }, {  94, 258 }, {  95, 258 },
	{  96, 258 }, {  97, 258 }, {  98, 258 }, {  99, 258 }, { 100, 258 },

	{ 101, 258 }, { 102, 258 }, { 103, 258 }, { 104, 258 }, { 105, 258 },
	{ 106, 258 }, { 107, 258 }, { 108, 258 }, { 109, 258 }, { 110, 258 },
	{ 111, 258 }, { 112, 258 }, { 113, 258 }, { 114, 258 }, { 115, 258 },
	{ 116, 258 }, { 117, 258 }, { 118, 258 }, { 119, 258 }, { 120, 258 },
	{ 121, 258 }, { 122, 258 }, { 123, 258 }, { 124, 258 }, { 125, 258 },
	{ 126, 258 }, { 127, 258 }, { 128, 258 }, { 129, 258 }, { 130, 258 },
	{ 131, 258 }, { 132, 258 }, { 133, 258 }, { 134, 258 }, { 135, 258 },
	{ 136, 258 }, { 137, 258 }, { 138, 258 }, { 139, 258 }, { 140, 258 },
	{ 141, 258 }, { 142, 258 }, { 143, 258 }, { 144, 258 }, { 145, 258 },
	{ 146, 258 }, { 147, 258 }, { 148, 258 }, { 149, 258 }, { 150, 258 },

	{ 151, 258 }, { 152, 258 }, { 153, 258 }, { 154, 258 }, { 155, 258 },
	{ 156, 258 }, { 157, 258 }, { 158, 258 }, { 159, 258 }, { 160, 258 },
	{ 161, 258 }, { 162, 258 }, { 163, 258 }, { 164, 258 }, { 165, 258 },
	{ 166, 258 }, { 167, 258 }, { 168, 258 }, { 169, 258 }, { 170, 258 },
	{ 171, 258 }, { 172, 258 }, { 173, 258 }, { 174, 258 }, { 175, 258 },
	{ 176, 258 }, { 177, 258 }, { 178, 258 }, { 179, 258 }, { 180, 258 },
	{ 181, 258 }, { 182, 258 }, { 183, 258 }, { 184, 258 }, { 185, 258 },
	{ 186, 258 }, { 187, 258 }, { 188, 258 }, { 189, 258 }, { 190, 258 },
	{ 191, 258 }, { 192, 258 }, { 193, 258 }, { 194, 258 }, { 195, 258 },
	{ 196, 258 }, { 197, 258 }, { 198, 258 }, { 199, 258 }, { 200, 258 },

	{ 201, 258 }, { 202, 258 }, { 203, 258 }, { 204, 258 }, { 205, 258 },
	{ 206, 258 }, { 207, 258 }, { 208, 258 }, { 209, 258 }, { 210, 258 },
	{ 211, 258 }, { 212, 258 }, { 213, 258 }, { 214, 258 }, { 215, 258 },
	{ 216, 258 }, { 217, 258 }, { 218, 258 }, { 219, 258 }, { 220, 258 },
	{ 221, 258 }, { 222, 258 }, { 223, 258 }, { 224, 258 }, { 225, 258 },
	{ 226, 258 }, { 227, 258 }, { 228, 258 }, { 229, 258 }, { 230, 258 },
	{ 231, 258 }, { 232, 258 }, { 233, 258 }, { 234, 258 }, { 235, 258 },
	{ 236, 258 }, { 237, 258 }, { 238, 258 }, { 239, 258 }, { 240, 258 },
	{ 241, 258 }, { 242, 258 }, { 243, 258 }, { 244, 258 }, { 245, 258 },
	{ 246, 258 }, { 247, 258 }, { 248, 258 }, { 249, 258 }, { 250, 258 },

	{ 251, 258 }, { 252, 258 }, { 253, 258 }, { 254, 258 }, { 255, 258 },
	{ 256, 258 }, {   0,   0 }, {   0, 774 }, {   1,   0 }, {   2,   0 },
	{   3,   0 }, {   4,   0 }, {   5,   0 }, {   6,   0 }, {   7,   0 },
	{   8,   0 }, {   9,   0 }, {  10,   0 }, {  11,   0 }, {  12,   0 },
	{  13,   0 }, {  14,   0 }, {  15,   0 }, {  16,   0 }, {  17,   0 },
	{  18,   0 }, {  19,   0 }, {  20,   0 }, {  21,   0 }, {  22,   0 },
	{  23,   0 }, {  24,   0 }, {  25,   0 }, {  26,   0 }, {  27,   0 },
	{  28,   0 }, {  29,   0 }, {  30,   0 }, {  31,   0 }, {  32,   0 },
	{  33,   0 }, {  34,   0 }, {  35,   0 }, {  36,   0 }, {  37,   0 },
	{  38,   0 }, {  39,   0 }, {  40,   0 }, {  41,   0 }, {  42,   0 },

	{  43,   0 }, {  44,   0 }, {  45, 516 }, {  46,   0 }, {  47,   0 },
	{  48,   0 }, {  49,   0 }, {  50,   0 }, {  51,   0 }, {  52,   0 },
	{  53,   0 }, {  54,   0 }, {  55,   0 }, {  56,   0 }, {  57,   0 },
	{  58,   0 }, {  59,   0 }, {  60,   0 }, {  61,   0 }, {  62,   0 },
	{  63,   0 }, {  64,   0 }, {  65,   0 }, {  66,   0 }, {  67,   0 },
	{  68,   0 }, {  69,   0 }, {  70,   0 }, {  71,   0 }, {  72,   0 },
	{  73,   0 }, {  74,   0 }, {  75,   0 }, {  76,   0 }, {  77,   0 },
	{  78,   0 }, {  79,   0 }, {  80,   0 }, {  81,   0 }, {  82,   0 },
	{  83,   0 }, {  84,   0 }, {  85,   0 }, {  86,   0 }, {  87,   0 },
	{  88,   0 }, {  89,   0 }, {  90,   0 }, {  91,   0 }, {  92,   0 },

	{  93,   0 }, {  94,   0 }, {  95,   0 }, {  96,   0 }, {  97,   0 },
	{  98,   0 }, {  99,   0 }, { 100,   0 }, { 101,   0 }, { 102,   0 },
	{ 103,   0 }, { 104,   0 }, { 105,   0 }, { 106,   0 }, { 107,   0 },
	{ 108,   0 }, { 109,   0 }, { 110,   0 }, { 111,   0 }, { 112,   0 },
	{ 113,   0 }, { 114,   0 }, { 115,   0 }, { 116,   0 }, { 117,   0 },
	{ 118,   0 }, { 119,   0 }, { 120,   0 }, { 121,   0 }, { 122,   0 },
	{ 123,   0 }, { 124,   0 }, { 125,   0 }, { 126,   0 }, { 127,   0 },
	{ 128,   0 }, { 129,   0 }, { 130,   0 }, { 131,   0 }, { 132,   0 },
	{ 133,   0 }, { 134,   0 }, { 135,   0 }, { 136,   0 }, { 137,   0 },
	{ 138,   0 }, { 139,   0 }, { 140,   0 }, { 141,   0 }, { 142,   0 },

	{ 143,   0 }, { 144,   0 }, { 145,   0 }, { 146,   0 }, { 147,   0 },
	{ 148,   0 }, { 149,   0 }, { 150,   0 }, { 151,   0 }, { 152,   0 },
	{ 153,   0 }, { 154,   0 }, { 155,   0 }, { 156,   0 }, { 157,   0 },
	{ 158,   0 }, { 159,   0 }, { 160,   0 }, { 161,   0 }, { 162,   0 },
	{ 163,   0 }, { 164,   0 }, { 165,   0 }, { 166,   0 }, { 167,   0 },
	{ 168,   0 }, { 169,   0 }, { 170,   0 }, { 171,   0 }, { 172,   0 },
	{ 173,   0 }, { 174,   0 }, { 175,   0 }, { 176,   0 }, { 177,   0 },
	{ 178,   0 }, { 179,   0 }, { 180,   0 }, { 181,   0 }, { 182,   0 },
	{ 183,   0 }, { 184,   0 }, { 185,   0 }, { 186,   0 }, { 187,   0 },
	{ 188,   0 }, { 189,   0 }, { 190,   0 }, { 191,   0 }, { 192,   0 },

	{ 193,   0 }, { 194,   0 }, { 195,   0 }, { 196,   0 }, { 197,   0 },
	{ 198,   0 }, { 199,   0 }, { 200,   0 }, { 201,   0 }, { 202,   0 },
	{ 203,   0 }, { 204,   0 }, { 205,   0 }, { 206,   0 }, { 207,   0 },
	{ 208,   0 }, { 209,   0 }, { 210,   0 }, { 211,   0 }, { 212,   0 },
	{ 213,   0 }, { 214,   0 }, { 215,   0 }, { 216,   0 }, { 217,   0 },
	{ 218,   0 }, { 219,   0 }, { 220,   0 }, { 221,   0 }, { 222,   0 },
	{ 223,   0 }, { 224,   0 }, { 225,   0 }, { 226,   0 }, { 227,   0 },
	{ 228,   0 }, { 229,   0 }, { 230,   0 }, { 231,   0 }, { 232,   0 },
	{ 233,   0 }, { 234,   0 }, { 235,   0 }, { 236,   0 }, { 237,   0 },
	{ 238,   0 }, { 239,   0 }, { 240,   0 }, { 241,   0 }, { 242,   0 },

	{ 243,   0 }, { 244,   0 }, { 245,   0 }, { 246,   0 }, { 247,   0 },
	{ 248,   0 }, { 249,   0 }, { 250,   0 }, { 251,   0 }, { 252,   0 },
	{ 253,   0 }, { 254,   0 }, { 255,   0 }, { 256,   0 }, {   0,   0 },
	{   0, 516 }, {   1,-258 }, {   2,-258 }, {   3,-258 }, {   4,-258 },
	{   5,-258 }, {   6,-258 }, {   7,-258 }, {   8,-258 }, {   9,-258 },
	{  10,-258 }, {  11,-258 }, {  12,-258 }, {  13,-258 }, {  14,-258 },
	{  15,-258 }, {  16,-258 }, {  17,-258 }, {  18,-258 }, {  19,-258 },
	{  20,-258 }, {  21,-258 }, {  22,-258 }, {  23,-258 }, {  24,-258 },
	{  25,-258 }, {  26,-258 }, {  27,-258 }, {  28,-258 }, {  29,-258 },
	{  30,-258 }, {  31,-258 }, {  32,-258 }, {  33,-258 }, {  34,-258 },

	{  35,-258 }, {  36,-258 }, {  37,-258 }, {  38,-258 }, {  39,-258 },
	{  40,-258 }, {  41,-258 }, {  42,-258 }, {  43,-258 }, {  44,-258 },
	{   0,   0 }, {  46,-258 }, {  47,-258 }, {  48,-258 }, {  49,-258 },
	{  50,-258 }, {  51,-258 }, {  52,-258 }, {  53,-258 }, {  54,-258 },
	{  55,-258 }, {  56,-258 }, {  57,-258 }, {  58,-258 }, {  59,-258 },
	{  60,-258 }, {  61,-258 }, {  62,-258 }, {  63,-258 }, {  64,-258 },
	{  65,-258 }, {  66,-258 }, {  67,-258 }, {  68,-258 }, {  69,-258 },
	{  70,-258 }, {  71,-258 }, {  72,-258 }, {  73,-258 }, {  74,-258 },
	{  75,-258 }, {  76,-258 }, {  77,-258 }, {  78,-258 }, {  79,-258 },
	{  80,-258 }, {  81,-258 }, {  82,-258 }, {  83,-258 }, {  84,-258 },

	{  85,-258 }, {  86,-258 }, {  87,-258 }, {  88,-258 }, {  89,-258 },
	{  90,-258 }, {  91,-258 }, {  92,-258 }, {  93,-258 }, {  94,-258 },
	{  95,-258 }, {  96,-258 }, {  97,-258 }, {  98,-258 }, {  99,-258 },
	{ 100,-258 }, { 101,-258 }, { 102,-258 }, { 103,-258 }, { 104,-258 },
	{ 105,-258 }, { 106,-258 }, { 107,-258 }, { 108,-258 }, { 109,-258 },
	{ 110,-258 }, { 111,-258 }, { 112,-258 }, { 113,-258 }, { 114,-258 },
	{ 115,-258 }, { 116,-258 }, { 117,-258 }, { 118,-258 }, { 119,-258 },
	{ 120,-258 }, { 121,-258 }, { 122,-258 }, { 123,-258 }, { 124,-258 },
	{ 125,-258 }, { 126,-258 }, { 127,-258 }, { 128,-258 }, { 129,-258 },
	{ 130,-258 }, { 131,-258 }, { 132,-258 }, { 133,-258 }, { 134,-258 },

	{ 135,-258 }, { 136,-258 }, { 137,-258 }, { 138,-258 }, { 139,-258 },
	{ 140,-258 }, { 141,-258 }, { 142,-258 }, { 143,-258 }, { 144,-258 },
	{ 145,-258 }, { 146,-258 }, { 147,-258 }, { 148,-258 }, { 149,-258 },
	{ 150,-258 }, { 151,-258 }, { 152,-258 }, { 153,-258 }, { 154,-258 },
	{ 155,-258 }, { 156,-258 }, { 157,-258 }, { 158,-258 }, { 159,-258 },
	{ 160,-258 }, { 161,-258 }, { 162,-258 }, { 163,-258 }, { 164,-258 },
	{ 165,-258 }, { 166,-258 }, { 167,-258 }, { 168,-258 }, { 169,-258 },
	{ 170,-258 }, { 171,-258 }, { 172,-258 }, { 173,-258 }, { 174,-258 },
	{ 175,-258 }, { 176,-258 }, { 177,-258 }, { 178,-258 }, { 179,-258 },
	{ 180,-258 }, { 181,-258 }, { 182,-258 }, { 183,-258 }, { 184,-258 },

	{ 185,-258 }, { 186,-258 }, { 187,-258 }, { 188,-258 }, { 189,-258 },
	{ 190,-258 }, { 191,-258 }, { 192,-258 }, { 193,-258 }, { 194,-258 },
	{ 195,-258 }, { 196,-258 }, { 197,-258 }, { 198,-258 }, { 199,-258 },
	{ 200,-258 }, { 201,-258 }, { 202,-258 }, { 203,-258 }, { 204,-258 },
	{ 205,-258 }, { 206,-258 }, { 207,-258 }, { 208,-258 }, { 209,-258 },
	{ 210,-258 }, { 211,-258 }, { 212,-258 }, { 213,-258 }, { 214,-258 },
	{ 215,-258 }, { 216,-258 }, { 217,-258 }, { 218,-258 }, { 219,-258 },
	{ 220,-258 }, { 221,-258 }, { 222,-258 }, { 223,-258 }, { 224,-258 },
	{ 225,-258 }, { 226,-258 }, { 227,-258 }, { 228,-258 }, { 229,-258 },
	{ 230,-258 }, { 231,-258 }, { 232,-258 }, { 233,-258 }, { 234,-258 },

	{ 235,-258 }, { 236,-258 }, { 237,-258 }, { 238,-258 }, { 239,-258 },
	{ 240,-258 }, { 241,-258 }, { 242,-258 }, { 243,-258 }, { 244,-258 },
	{ 245,-258 }, { 246,-258 }, { 247,-258 }, { 248,-258 }, { 249,-258 },
	{ 250,-258 }, { 251,-258 }, { 252,-258 }, { 253,-258 }, { 254,-258 },
	{ 255,-258 }, { 256,-258 }, {   0,   0 }, {   0, 258 }, {   1,-516 },
	{   2,-516 }, {   3,-516 }, {   4,-516 }, {   5,-516 }, {   6,-516 },
	{   7,-516 }, {   8,-516 }, {   9,-516 }, {  10,-516 }, {  11,-516 },
	{  12,-516 }, {  13,-516 }, {  14,-516 }, {  15,-516 }, {  16,-516 },
	{  17,-516 }, {  18,-516 }, {  19,-516 }, {  20,-516 }, {  21,-516 },
	{  22,-516 }, {  23,-516 }, {  24,-516 }, {  25,-516 }, {  26,-516 },

	{  27,-516 }, {  28,-516 }, {  29,-516 }, {  30,-516 }, {  31,-516 },
	{  32,-516 }, {  33,-516 }, {  34,-516 }, {  35,-516 }, {  36,-516 },
	{  37,-516 }, {  38,-516 }, {  39,-516 }, {  40,-516 }, {  41,-516 },
	{  42,-516 }, {  43,-516 }, {  44,-516 }, {  45,-5315 }, {  46,-516 },
	{  47,-516 }, {  48,-516 }, {  49,-516 }, {  50,-516 }, {  51,-516 },
	{  52,-516 }, {  53,-516 }, {  54,-516 }, {  55,-516 }, {  56,-516 },
	{  57,-516 }, {  58,-516 }, {  59,-516 }, {  60,-516 }, {  61,-516 },
	{  62,-516 }, {  63,-516 }, {  64,-516 }, {  65,-516 }, {  66,-516 },
	{  67,-516 }, {  68,-516 }, {  69,-516 }, {  70,-516 }, {  71,-516 },
	{  72,-516 }, {  73,-516 }, {  74,-516 }, {  75,-516 }, {  76,-516 },

	{  77,-516 }, {  78,-516 }, {  79,-516 }, {  80,-516 }, {  81,-516 },
	{  82,-516 }, {  83,-516 }, {  84,-516 }, {  85,-516 }, {  86,-516 },
	{  87,-516 }, {  88,-516 }, {  89,-516 }, {  90,-516 }, {  91,-516 },
	{  92,-516 }, {  93,-516 }, {  94,-516 }, {  95,-516 }, {  96,-516 },
	{  97,-516 }, {  98,-516 }, {  99,-516 }, { 100,-516 }, { 101,-516 },
	{ 102,-516 }, { 103,-516 }, { 104,-516 }, { 105,-516 }, { 106,-516 },
	{ 107,-516 }, { 108,-516 }, { 109,-516 }, { 110,-516 }, { 111,-516 },
	{ 112,-516 }, { 113,-516 }, { 114,-516 }, { 115,-516 }, { 116,-516 },
	{ 117,-516 }, { 118,-516 }, { 119,-516 }, { 120,-516 }, { 121,-516 },
	{ 122,-516 }, { 123,-516 }, { 124,-516 }, { 125,-516 }, { 126,-516 },

	{ 127,-516 }, { 128,-516 }, { 129,-516 }, { 130,-516 }, { 131,-516 },
	{ 132,-516 }, { 133,-516 }, { 134,-516 }, { 135,-516 }, { 136,-516 },
	{ 137,-516 }, { 138,-516 }, { 139,-516 }, { 140,-516 }, { 141,-516 },
	{ 142,-516 }, { 143,-516 }, { 144,-516 }, { 145,-516 }, { 146,-516 },
	{ 147,-516 }, { 148,-516 }, { 149,-516 }, { 150,-516 }, { 151,-516 },
	{ 152,-516 }, { 153,-516 }, { 154,-516 }, { 155,-516 }, { 156,-516 },
	{ 157,-516 }, { 158,-516 }, { 159,-516 }, { 160,-516 }, { 161,-516 },
	{ 162,-516 }, { 163,-516 }, { 164,-516 }, { 165,-516 }, { 166,-516 },
	{ 167,-516 }, { 168,-516 }, { 169,-516 }, { 170,-516 }, { 171,-516 },
	{ 172,-516 }, { 173,-516 }, { 174,-516 }, { 175,-516 }, { 176,-516 },

	{ 177,-516 }, { 178,-516 }, { 179,-516 }, { 180,-516 }, { 181,-516 },
	{ 182,-516 }, { 183,-516 }, { 184,-516 }, { 185,-516 }, { 186,-516 },
	{ 187,-516 }, { 188,-516 }, { 189,-516 }, { 190,-516 }, { 191,-516 },
	{ 192,-516 }, { 193,-516 }, { 194,-516 }, { 195,-516 }, { 196,-516 },
	{ 197,-516 }, { 198,-516 }, { 199,-516 }, { 200,-516 }, { 201,-516 },
	{ 202,-516 }, { 203,-516 }, { 204,-516 }, { 205,-516 }, { 206,-516 },
	{ 207,-516 }, { 208,-516 }, { 209,-516 }, { 210,-516 }, { 211,-516 },
	{ 212,-516 }, { 213,-516 }, { 214,-516 }, { 215,-516 }, { 216,-516 },
	{ 217,-516 }, { 218,-516 }, { 219,-516 }, { 220,-516 }, { 221,-516 },
	{ 222,-516 }, { 223,-516 }, { 224,-516 }, { 225,-516 }, { 226,-516 },

	{ 227,-516 }, { 228,-516 }, { 229,-516 }, { 230,-516 }, { 231,-516 },
	{ 232,-516 }, { 233,-516 }, { 234,-516 }, { 235,-516 }, { 236,-516 },
	{ 237,-516 }, { 238,-516 }, { 239,-516 }, { 240,-516 }, { 241,-516 },
	{ 242,-516 }, { 243,-516 }, { 244,-516 }, { 245,-516 }, { 246,-516 },
	{ 247,-516 }, { 248,-516 }, { 249,-516 }, { 250,-516 }, { 251,-516 },
	{ 252,-516 }, { 253,-516 }, { 254,-516 }, { 255,-516 }, { 256,-516 },
	{ 257,  16 }, {   1,   0 },    };

	static yyconst struct yy_trans_info *yy_start_state_list[5] =
	{
		&yy_transition[1],
		&yy_transition[3],
		&yy_transition[261],
		&yy_transition[519],
		&yy_transition[777],


	} ;

	/* The intent behind ptrThis definition is that it'll catch
	* any uses of REJECT which flex missed.
	*/
#define REJECT reject_used_but_not_detected
#define yymore() yymore_used_but_not_detected
#define YY_MORE_ADJ 0
#define YY_RESTORE_YY_MORE_OFFSET
#ifndef YY_REENTRANT
	char *yytext;
#endif
///#line 1 "../../../src/sd/domnode-xml-scanner.l"
#define INITIAL 0
#define YY_NEVER_INTERACTIVE 1
#define YY_NO_UNPUT 1
///#line 15 "../../../src/sd/domnode-xml-scanner.l"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
///#include "error.h"
///#include "malloc.h"
///#include "domnode-xml.h"

	/* Generated by bison(1) */
///#include "domnode-xml-parser.h"

#ifdef strdup
#	undef strdup
#endif
#define strdup sd_strdup
#ifdef malloc
#	undef malloc
#endif
#define malloc sd_malloc
#ifdef calloc
#	undef calloc
#endif
#define calloc sd_calloc
#ifdef realloc
#	undef realloc
#endif
#define realloc sd_realloc
#ifdef yyerror
#	undef yyerror
#endif
#define yyerror sd_error

	/******************************************************************************/
	/* Extract a single word */
	static char* word(const char *s)
	{
		char *buf;
		int i, k;

		for (k = 0; isspace(s[k]) || s[k] == '<'; k++);
		for (i = k; s[i] && ! isspace(s[i]); i++);

		buf = (char*)malloc((i - k + 1) * sizeof(char));
		strncpy(buf, &s[k], i - k);
		buf[i - k] = 0;

		return buf;
	}

	/******************************************************************************/
	/* Extract text between " " */
	static char* string(const char* s)
	{
		char* buf;
		int i;

		buf = strdup(s + 1);
		for (i = 0; buf[i] != '"'; i++);
		buf[i] = 0;

		return buf;
	}

	/******************************************************************************/
	/* Extract text between <!-- --> */
	static char* comment(const char* s)
	{
		char* buf;
		int i, k;

		for (k = 4; isspace(s[k]); k++);
		for (i = k; strncmp(&s[i], "-->", 3); i++);

		buf = (char*)malloc((i - k + 1) * sizeof(char));
		strncpy(buf, &s[k], i - k);
		buf[i - k] = 0;

		return buf;
	}

#define CONTENT 1

///#line 2268 "domnode-xml-scanner.c"
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */

	/* Special case for "unistd.h", since it is non-ANSI. We include it way
	* down here because we want the user's section 1 to have been scanned first.
	* The user has a chance to override it with an option.
	*/
#ifndef YY_NO_UNISTD_H
#include <unistd.h>
#endif /* !YY_NO_UNISTD_H */

#ifndef YY_EXTRA_TYPE
#define YY_EXTRA_TYPE void *
#endif


#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
	/* Holds the entire state of the reentrant scanner. */
	struct yyguts_t
	{

		/* User-defined. Not touched by flex. */
		YY_EXTRA_TYPE yyextra_r;

		/* The rest are the same as the globals declared in the non-reentrant scanner. */
		FILE *yyin_r, *yyout_r;
		YY_BUFFER_STATE yy_current_buffer;
		char yy_hold_char;
		int yy_n_chars;
		int yyleng_r;
		char *yy_c_buf_p;
		int yy_init;
		int yy_start;
		int yy_did_buffer_switch_on_eof;
		int yy_start_stack_ptr;
		int yy_start_stack_depth;
		int *yy_start_stack;
		yy_state_type yy_last_accepting_state;
		char* yy_last_accepting_cpos;

		int yylineno_r;
		int yy_flex_debug_r;

#ifdef YY_USES_REJECT
		yy_state_type *yy_state_buf;
		yy_state_type *yy_state_ptr;
		char *yy_full_match;
		int yy_lp;
#endif

#ifdef YY_TEXT_IS_ARRAY
		char yytext_r[YYLMAX];
		char *yytext_ptr;
		int yy_more_offset;
		int yy_prev_more_offset;
#else
		char *yytext_r;
		int yy_more_flag;
		int yy_more_len;
#endif

		YYSTYPE * yylval_r;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
		YYLTYPE * yylloc_r;
#endif

	};
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */

#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
	static int yy_init_globals YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */

#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
	/* This must go here because YYSTYPE and YYLTYPE are included
	* from bison output in section 1.*/
#undef yylval //  [7/18/2009 温辉敏]
#    define yylval YY_G(yylval_r)
#  if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#    define yylloc YY_G(yylloc_r)
#  endif

#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */


	/* Accessor methods to globals.
	These are made visible to non-reentrant scanners for convenience. */

#ifndef YY_NO_DESTROY
	int yylex_destroy YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_GET_DEBUG
	int yyget_debug YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_DEBUG
	void yyset_debug YY_PARAMS(( int debug_flag YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_EXTRA
	YY_EXTRA_TYPE yyget_extra YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_EXTRA
	void yyset_extra YY_PARAMS(( YY_EXTRA_TYPE user_defined YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_IN
	FILE *yyget_in YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_IN
	void yyset_in  YY_PARAMS(( FILE * in_str YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_OUT
	FILE *yyget_out YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_OUT
	void yyset_out  YY_PARAMS(( FILE * out_str YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_LENG
	int yyget_leng YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_GET_TEXT
	char *yyget_text YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_GET_LINENO
	int yyget_lineno YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_LINENO
	void yyset_lineno YY_PARAMS(( int line_number YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_LVAL
	YYSTYPE * yyget_lval YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif
	void yyset_lval YY_PARAMS(( YYSTYPE * yylvalp YY_PROTO_LAST_ARG ));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YY_NO_GET_LLOC
	YYLTYPE *yyget_lloc YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif
#ifndef YY_NO_SET_LLOC
	void yyset_lloc YY_PARAMS(( YYLTYPE * yyllocp YY_PROTO_LAST_ARG ));
#endif
#endif /* YYLTYPE */

	/* Macros after ptrThis point can all be overridden by user definitions in
	* section 1.
	*/

#ifndef YY_SKIP_YYWRAP
#ifdef __cplusplus
	extern "C" int yywrap YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#else
	extern int yywrap YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif
#endif

#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
#ifndef YY_NO_UNPUT
	static void yyunput YY_PARAMS(( int c, char *buf_ptr  YY_PROTO_LAST_ARG));
#endif
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */

#ifndef yytext_ptr
	static void yy_flex_strncpy YY_PARAMS(( char *, yyconst char *, int YY_PROTO_LAST_ARG));
#endif

#ifdef YY_NEED_STRLEN
	static int yy_flex_strlen YY_PARAMS(( yyconst char * YY_PROTO_LAST_ARG));
#endif

#ifndef YY_NO_INPUT
#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
#ifdef __cplusplus
	static int yyinput YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#else
	static int input YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */
#endif


#if YY_STACK_USED
#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */

#ifndef YY_NO_PUSH_STATE
	static void yy_push_state YY_PARAMS(( int new_state YY_PROTO_LAST_ARG));
#endif
#ifndef YY_NO_POP_STATE
	static void yy_pop_state YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif
#ifndef YY_NO_TOP_STATE
	static int yy_top_state YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#else
#define YY_NO_PUSH_STATE 1
#define YY_NO_POP_STATE 1
#define YY_NO_TOP_STATE 1
#endif

	/* Amount of stuff to slurp up with each read. */
#ifndef YY_READ_BUF_SIZE
#define YY_READ_BUF_SIZE 8192
#endif

	/* Copy whatever the last rule matched to the standard output. */

#ifndef ECHO
	/* This used to be an fputs(), but since the string might contain NUL's,
	* we now use fwrite().
	*/
#define ECHO (void) fwrite( yytext, yyleng, 1, yyout )
#endif

	/* Gets input and stuffs it into "buf".  number of characters read, or YY_NULL,
	* is returned in "result".
	*/
#ifndef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	errno=0; \
	while ( (result = read( fileno(yyin), (char *) buf, max_size )) < 0 ) \
	{ \
	if( errno != EINTR) \
	{ \
	YY_FATAL_ERROR( "input in flex scanner failed" ); \
	break; \
	} \
	errno=0; \
	clearerr(yyin); \
	}
	\
#endif

		/* No semi-colon after return; correct usage is to write "yyterminate();" -
		* we don't want an extra ';' after the "return" because that will cause
		* some compilers to complain about unreachable statements.
		*/
#ifndef yyterminate
#define yyterminate() return YY_NULL
#endif

		/* Number of entries by which start-condition stack grows. */
#ifndef YY_START_STACK_INCR
#define YY_START_STACK_INCR 25
#endif

		/* Report a fatal error. */
#ifndef YY_FATAL_ERROR
#define YY_FATAL_ERROR(msg) yy_fatal_error( msg YY_CALL_LAST_ARG)
#endif

#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */
#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
		/* end tables serialization structures and prototypes */

#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */

		/* Default declaration of generated scanner - a define so the user can
		* easily add parameters.
		*/
#ifndef YY_DECL

		/* If the bison pure parser is used, then bison will provide
		one or two additional arguments. */

#  if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#        define YY_LEX_PROTO YY_PARAMS((YYSTYPE * yylvalp, YYLTYPE * yyllocp YY_PROTO_LAST_ARG))
#        define YY_LEX_DECLARATION YYFARGS2(YYSTYPE *,yylvalp, YYLTYPE *,yyllocp)
#  else
#        define YY_LEX_PROTO YY_PARAMS((YYSTYPE * yylvalp YY_PROTO_LAST_ARG))
#        define YY_LEX_DECLARATION YYFARGS1(YYSTYPE *,yylvalp)
#  endif



		extern int yylex YY_LEX_PROTO;

#define YY_DECL int yylex YY_LEX_DECLARATION
#endif


	/* Code executed at the beginning of each rule, after yytext and yyleng
	* have been set up.
	*/
#ifndef YY_USER_ACTION
#define YY_USER_ACTION
#endif

	/* Code executed at the end of each rule. */
#ifndef YY_BREAK
#define YY_BREAK break;
#endif

#define YY_RULE_SETUP \
	YY_USER_ACTION

#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
	YY_DECL
	{
		register yy_state_type yy_current_state;
		register char *yy_cp, *yy_bp;
		register int yy_act;

///#line 112 "../../../src/sd/domnode-xml-scanner.l"
#define YY_TABLES_VERIFY 0


///#line 2585 "domnode-xml-scanner.c"

		yylval = yylvalp;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
		yylloc = yyllocp;
#endif

		if ( YY_G(yy_init) )
		{
			YY_G(yy_init) = 0;

#ifdef YY_USER_INIT
			YY_USER_INIT;
#endif

#ifdef YY_USES_REJECT
			if ( ! YY_G(yy_state_buf) )
				YY_G(yy_state_buf) = (yy_state_type *)yyalloc(YY_BUF_SIZE + 2  YY_CALL_LAST_ARG);
#endif

			if ( ! YY_G(yy_start) )
				YY_G(yy_start) = 1;	/* first start state */

			if ( ! yyin )
				yyin = stdin;

			if ( ! yyout )
				yyout = stdout;

			if ( ! YY_G(yy_current_buffer) )
				YY_G(yy_current_buffer) =
				yy_create_buffer( yyin, YY_BUF_SIZE YY_CALL_LAST_ARG);

			yy_load_buffer_state( YY_CALL_ONLY_ARG );
		}

		while ( 1 )		/* loops until end-of-file is reached */
		{
			yy_cp = YY_G(yy_c_buf_p);

			/* Support of yytext. */
			*yy_cp = YY_G(yy_hold_char);

			/* yy_bp points to the position in yy_ch_buf of the start of
			* the current run.
			*/
			yy_bp = yy_cp;

			yy_current_state = yy_start_state_list[YY_G(yy_start)];
yy_match:
			{
				register yyconst struct yy_trans_info *yy_trans_info;

				register YY_CHAR yy_c;

				for ( yy_c = YY_SC_TO_UI(*yy_cp);
					(yy_trans_info = &yy_current_state[(unsigned int) yy_c])->
					yy_verify == yy_c;
				yy_c = YY_SC_TO_UI(*++yy_cp) )
				{
					yy_current_state += yy_trans_info->yy_nxt;

					if ( yy_current_state[-1].yy_nxt )
					{
						YY_G(yy_last_accepting_state) = yy_current_state;
						YY_G(yy_last_accepting_cpos) = yy_cp;
					}
				}
			}

yy_find_action:
			yy_act = yy_current_state[-1].yy_nxt;

			YY_DO_BEFORE_ACTION;

#ifdef YY_USE_LINENO
			if ( yy_act != YY_END_OF_BUFFER && yy_rule_can_match_eol[yy_act] )
			{
				int yyl;
				for ( yyl = 0; yyl < yyleng; ++yyl )
					if ( yytext[yyl] == '\n' )
						++yylineno;
			}
#endif

do_action:	/* This label is used only to access EOF actions. */


			switch ( yy_act )
			{ /* beginning of action switch */
			case 0: /* must back up */
				/* undo the effects of YY_DO_BEFORE_ACTION */
				*yy_cp = YY_G(yy_hold_char);
				yy_cp = YY_G(yy_last_accepting_cpos) + 1;
				yy_current_state = YY_G(yy_last_accepting_state);
				goto yy_find_action;

			case 1:
				/* rule 1 can match eol */
				YY_RULE_SETUP
///#line 114 "../../../src/sd/domnode-xml-scanner.l"
				{/* skip */}
				YY_BREAK
			case 2:
				YY_RULE_SETUP
///#line 115 "../../../src/sd/domnode-xml-scanner.l"
				{ return SLASH; }
				YY_BREAK
			case 3:
				YY_RULE_SETUP
///#line 116 "../../../src/sd/domnode-xml-scanner.l"
				{ return EQ; }
				YY_BREAK
			case 4:
				/* rule 4 can match eol */
				YY_RULE_SETUP
///#line 117 "../../../src/sd/domnode-xml-scanner.l"
				{ BEGIN(CONTENT); return CLOSE; }
				YY_BREAK
			case 5:
				YY_RULE_SETUP
///#line 118 "../../../src/sd/domnode-xml-scanner.l"
				{ yylvalp->s = strdup(yytext); return NAME; }
				YY_BREAK
			case 6:
				/* rule 6 can match eol */
				YY_RULE_SETUP
///#line 119 "../../../src/sd/domnode-xml-scanner.l"
				{ yylvalp->s = string(yytext); return VALUE; }
				YY_BREAK
			case 7:
				/* rule 7 can match eol */
				YY_RULE_SETUP
///#line 120 "../../../src/sd/domnode-xml-scanner.l"
				{ return ENDDEF; }
				YY_BREAK
			case 8:
				/* rule 8 can match eol */
				YY_RULE_SETUP
///#line 122 "../../../src/sd/domnode-xml-scanner.l"
				{
					BEGIN(INITIAL);
					yylvalp->s = word(yytext);
					return START;
				}
				YY_BREAK
			case 9:
				/* rule 9 can match eol */
				YY_RULE_SETUP
///#line 127 "../../../src/sd/domnode-xml-scanner.l"
				{BEGIN(INITIAL); return END;}
				YY_BREAK
			case 10:
				/* rule 10 can match eol */
				YY_RULE_SETUP
///#line 128 "../../../src/sd/domnode-xml-scanner.l"
				{yylvalp->s = comment(yytext); return COMMENT;}
				YY_BREAK
			case 11:
				/* rule 11 can match eol */
				YY_RULE_SETUP
///#line 129 "../../../src/sd/domnode-xml-scanner.l"
				{/* skip */}
				YY_BREAK
			case 12:
				YY_RULE_SETUP
///#line 131 "../../../src/sd/domnode-xml-scanner.l"
				{yylvalp->s = strdup(yytext); return DATA;}
				YY_BREAK
			case 13:
				YY_RULE_SETUP
///#line 133 "../../../src/sd/domnode-xml-scanner.l"
				{ yyerror("wrong XML input '%c'", *yytext); }
				YY_BREAK
			case 14:
				/* rule 14 can match eol */
				YY_RULE_SETUP
///#line 134 "../../../src/sd/domnode-xml-scanner.l"
				{/* skip, must be an extra one at EOF */}
				YY_BREAK
			case 15:
				YY_RULE_SETUP
///#line 135 "../../../src/sd/domnode-xml-scanner.l"
					YY_FATAL_ERROR( "flex scanner jammed" );
				YY_BREAK
///#line 2770 "domnode-xml-scanner.c"
			case YY_STATE_EOF(INITIAL):
			case YY_STATE_EOF(CONTENT):
				yyterminate();

			case YY_END_OF_BUFFER:
				{
					/* Amount of text matched not including the EOB char. */
					int yy_amount_of_matched_text = (int) (yy_cp - YY_G(yytext_ptr)) - 1;

					/* Undo the effects of YY_DO_BEFORE_ACTION. */
					*yy_cp = YY_G(yy_hold_char);
					YY_RESTORE_YY_MORE_OFFSET

						if ( YY_G(yy_current_buffer)->yy_buffer_status == YY_BUFFER_NEW )
						{
							/* We're scanning a new file or input source.  It's
							* possible that ptrThis happened because the user
							* just pointed yyin at a new source and called
							* yylex().  If so, then we have to assure
							* consistency between yy_current_buffer and our
							* globals.  Here is the right place to do so, because
							* ptrThis is the first action (other than possibly a
							* back-up) that will match for the new input source.
							*/
							YY_G(yy_n_chars) = YY_G(yy_current_buffer)->yy_n_chars;
							YY_G(yy_current_buffer)->yy_input_file = yyin;
							YY_G(yy_current_buffer)->yy_buffer_status = YY_BUFFER_NORMAL;
						}

						/* Note that here we test for yy_c_buf_p "<=" to the position
						* of the first EOB in the buffer, since yy_c_buf_p will
						* already have been incremented past the NUL character
						* (since all states make transitions on EOB to the
						* end-of-buffer state).  Contrast ptrThis with the test
						* in input().
						*/
						if ( YY_G(yy_c_buf_p) <= &YY_G(yy_current_buffer)->yy_ch_buf[YY_G(yy_n_chars)] )
						{ /* This was really a NUL. */
							yy_state_type yy_next_state;

							YY_G(yy_c_buf_p) = YY_G(yytext_ptr) + yy_amount_of_matched_text;

							yy_current_state = yy_get_previous_state( YY_CALL_ONLY_ARG );

							/* Okay, we're now positioned to make the NUL
							* transition.  We couldn't have
							* yy_get_previous_state() go ahead and do it
							* for us because it doesn't know how to deal
							* with the possibility of jamming (and we don't
							* want to build jamming into it because then it
							* will run more slowly).
							*/

							yy_next_state = yy_try_NUL_trans( yy_current_state YY_CALL_LAST_ARG);

							yy_bp = YY_G(yytext_ptr) + YY_MORE_ADJ;

							if ( yy_next_state )
							{
								/* Consume the NUL. */
								yy_cp = ++YY_G(yy_c_buf_p);
								yy_current_state = yy_next_state;
								goto yy_match;
							}

							else
							{
								yy_cp = YY_G(yy_c_buf_p);
								goto yy_find_action;
							}
						}

						else switch ( yy_get_next_buffer( YY_CALL_ONLY_ARG ) )
						{
			case EOB_ACT_END_OF_FILE:
				{
					YY_G(yy_did_buffer_switch_on_eof) = 0;

					if ( yywrap( YY_CALL_ONLY_ARG ) )
					{
						/* Note: because we've taken care in
						* yy_get_next_buffer() to have set up
						* yytext, we can now set up
						* yy_c_buf_p so that if some total
						* hoser (like flex itself) wants to
						* call the scanner after we return the
						* YY_NULL, it'll still work - another
						* YY_NULL will get returned.
					 */
						YY_G(yy_c_buf_p) = YY_G(yytext_ptr) + YY_MORE_ADJ;

						yy_act = YY_STATE_EOF(YY_START);
						goto do_action;
					}

					else
					{
						if ( ! YY_G(yy_did_buffer_switch_on_eof) )
							YY_NEW_FILE;
					}
					break;
				}

			case EOB_ACT_CONTINUE_SCAN:
				YY_G(yy_c_buf_p) =
					YY_G(yytext_ptr) + yy_amount_of_matched_text;

				yy_current_state = yy_get_previous_state( YY_CALL_ONLY_ARG );

				yy_cp = YY_G(yy_c_buf_p);
				yy_bp = YY_G(yytext_ptr) + YY_MORE_ADJ;
				goto yy_match;

			case EOB_ACT_LAST_MATCH:
				YY_G(yy_c_buf_p) =
					&YY_G(yy_current_buffer)->yy_ch_buf[YY_G(yy_n_chars)];

				yy_current_state = yy_get_previous_state( YY_CALL_ONLY_ARG );

				yy_cp = YY_G(yy_c_buf_p);
				yy_bp = YY_G(yytext_ptr) + YY_MORE_ADJ;
				goto yy_find_action;
						}
						break;
				}

			default:
				YY_FATAL_ERROR(
					"fatal flex scanner internal error--no action found" );
			} /* end of action switch */
		} /* end of scanning one token */
	} /* end of yylex */
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */

#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */

	/* yy_get_next_buffer - try to read in a new buffer
	*
	* Returns a code representing an action:
	*	EOB_ACT_LAST_MATCH -
	*	EOB_ACT_CONTINUE_SCAN - continue scanning from current position
	*	EOB_ACT_END_OF_FILE - end of file
	*/

#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
	static int yy_get_next_buffer YYFARGS0(void)
	{
		register char *dest = YY_G(yy_current_buffer)->yy_ch_buf;
		register char *source = YY_G(yytext_ptr);
		register int number_to_move, i;
		int ret_val;

		if ( YY_G(yy_c_buf_p) > &YY_G(yy_current_buffer)->yy_ch_buf[YY_G(yy_n_chars) + 1] )
			YY_FATAL_ERROR(
			"fatal flex scanner internal error--end of buffer missed" );

		if ( YY_G(yy_current_buffer)->yy_fill_buffer == 0 )
		{ /* Don't try to fill the buffer, so ptrThis is an EOF. */
			if ( YY_G(yy_c_buf_p) - YY_G(yytext_ptr) - YY_MORE_ADJ == 1 )
			{
				/* We matched a single character, the EOB, so
				* treat ptrThis as a final EOF.
			 */
				return EOB_ACT_END_OF_FILE;
			}

			else
			{
				/* We matched some text prior to the EOB, first
				* process it.
			 */
				return EOB_ACT_LAST_MATCH;
			}
		}

		/* Try to read more data. */

		/* First move last chars to start of buffer. */
		number_to_move = (int) (YY_G(yy_c_buf_p) - YY_G(yytext_ptr)) - 1;

		for ( i = 0; i < number_to_move; ++i )
			*(dest++) = *(source++);

		if ( YY_G(yy_current_buffer)->yy_buffer_status == YY_BUFFER_EOF_PENDING )
			/* don't do the read, it's not guaranteed to return an EOF,
			* just force an EOF
			*/
			YY_G(yy_current_buffer)->yy_n_chars = YY_G(yy_n_chars) = 0;

		else
		{
			size_t num_to_read =
				YY_G(yy_current_buffer)->yy_buf_size - number_to_move - 1;

			while ( num_to_read <= 0 )
			{ /* Not enough room in the buffer - grow it. */
#ifdef YY_USES_REJECT
				YY_FATAL_ERROR(
					"input buffer overflow, can't enlarge buffer because scanner uses REJECT" );
#else

				/* just a shorter name for the current buffer */
				YY_BUFFER_STATE b = YY_G(yy_current_buffer);

				int yy_c_buf_p_offset =
					(int) (YY_G(yy_c_buf_p) - b->yy_ch_buf);

				if ( b->yy_is_our_buffer )
				{
					int new_size = b->yy_buf_size * 2;

					if ( new_size <= 0 )
						b->yy_buf_size += b->yy_buf_size / 8;
					else
						b->yy_buf_size *= 2;

					b->yy_ch_buf = (char *)
						/* Include room in for 2 EOB chars. */
						yyrealloc( (void *) b->yy_ch_buf,
						b->yy_buf_size + 2 YY_CALL_LAST_ARG );
				}
				else
					/* Can't grow it, we don't own it. */
					b->yy_ch_buf = 0;

				if ( ! b->yy_ch_buf )
					YY_FATAL_ERROR(
					"fatal error - scanner input buffer overflow" );

				YY_G(yy_c_buf_p) = &b->yy_ch_buf[yy_c_buf_p_offset];

				num_to_read = YY_G(yy_current_buffer)->yy_buf_size -
					number_to_move - 1;
#endif
			}

			if ( num_to_read > YY_READ_BUF_SIZE )
				num_to_read = YY_READ_BUF_SIZE;

			/* Read in more data. */
			YY_INPUT( (&YY_G(yy_current_buffer)->yy_ch_buf[number_to_move]),
				YY_G(yy_n_chars), num_to_read );

			YY_G(yy_current_buffer)->yy_n_chars = YY_G(yy_n_chars);
		}

		if ( YY_G(yy_n_chars) == 0 )
		{
			if ( number_to_move == YY_MORE_ADJ )
			{
				ret_val = EOB_ACT_END_OF_FILE;
				yyrestart( yyin  YY_CALL_LAST_ARG);
			}

			else
			{
				ret_val = EOB_ACT_LAST_MATCH;
				YY_G(yy_current_buffer)->yy_buffer_status =
					YY_BUFFER_EOF_PENDING;
			}
		}

		else
			ret_val = EOB_ACT_CONTINUE_SCAN;

		YY_G(yy_n_chars) += number_to_move;
		YY_G(yy_current_buffer)->yy_ch_buf[YY_G(yy_n_chars)] = YY_END_OF_BUFFER_CHAR;
		YY_G(yy_current_buffer)->yy_ch_buf[YY_G(yy_n_chars) + 1] = YY_END_OF_BUFFER_CHAR;

		YY_G(yytext_ptr) = &YY_G(yy_current_buffer)->yy_ch_buf[0];

		return ret_val;
	}
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */

	/* yy_get_previous_state - get the state just before the EOB char was reached */

#ifndef __sd_domnode_xml_IN_HEADER /* YY-DISCARD-FROM-HEADER */
	static yy_state_type yy_get_previous_state YYFARGS0(void)
	{
		register yy_state_type yy_current_state;
		register char *yy_cp;

		yy_current_state = yy_start_state_list[YY_G(yy_start)];

		for ( yy_cp = YY_G(yytext_ptr) + YY_MORE_ADJ; yy_cp < YY_G(yy_c_buf_p); ++yy_cp )
		{
			yy_current_state += yy_current_state[(*yy_cp ? YY_SC_TO_UI(*yy_cp) : 256)].yy_nxt;
			if ( yy_current_state[-1].yy_nxt )
			{
				YY_G(yy_last_accepting_state) = yy_current_state;
				YY_G(yy_last_accepting_cpos) = yy_cp;
			}
		}

		return yy_current_state;
	}


	/* yy_try_NUL_trans - try to make a transition on the NUL character
	*
	* synopsis
	*	next_state = yy_try_NUL_trans( current_state );
	*/
	static yy_state_type yy_try_NUL_trans  YYFARGS1( yy_state_type, yy_current_state)
	{
		register int yy_is_jam;
		register char *yy_cp = YY_G(yy_c_buf_p);

		register int yy_c = 256;
		register yyconst struct yy_trans_info *yy_trans_info;

		yy_trans_info = &yy_current_state[(unsigned int) yy_c];
		yy_current_state += yy_trans_info->yy_nxt;
		yy_is_jam = (yy_trans_info->yy_verify != yy_c);

		if ( ! yy_is_jam )
		{
			if ( yy_current_state[-1].yy_nxt )
			{
				YY_G(yy_last_accepting_state) = yy_current_state;
				YY_G(yy_last_accepting_cpos) = yy_cp;
			}
		}

		return yy_is_jam ? 0 : yy_current_state;
	}


#ifndef YY_NO_UNPUT
	static void yyunput YYFARGS2( int,c, register char *,yy_bp)
	{
		register char *yy_cp = YY_G(yy_c_buf_p);

		/* undo effects of setting up yytext */
		*yy_cp = YY_G(yy_hold_char);

		if ( yy_cp < YY_G(yy_current_buffer)->yy_ch_buf + 2 )
		{ /* need to shift things up to make room */
			/* +2 for EOB chars. */
			register int number_to_move = YY_G(yy_n_chars) + 2;
			register char *dest = &YY_G(yy_current_buffer)->yy_ch_buf[
				YY_G(yy_current_buffer)->yy_buf_size + 2];
				register char *source =
					&YY_G(yy_current_buffer)->yy_ch_buf[number_to_move];

				while ( source > YY_G(yy_current_buffer)->yy_ch_buf )
					*--dest = *--source;

				yy_cp += (int) (dest - source);
				yy_bp += (int) (dest - source);
				YY_G(yy_current_buffer)->yy_n_chars =
					YY_G(yy_n_chars) = YY_G(yy_current_buffer)->yy_buf_size;

				if ( yy_cp < YY_G(yy_current_buffer)->yy_ch_buf + 2 )
					YY_FATAL_ERROR( "flex scanner push-back overflow" );
		}

		*--yy_cp = (char) c;

#ifdef YY_USE_LINENO
		if ( c == '\n' )
			--yylineno;
#endif
		YY_G(yytext_ptr) = yy_bp;
		YY_G(yy_hold_char) = *yy_cp;
		YY_G(yy_c_buf_p) = yy_cp;
	}
#endif	/* ifndef YY_NO_UNPUT */

#ifndef YY_NO_INPUT
#ifdef __cplusplus
	static int yyinput YYFARGS0(void)
#else
	static int input  YYFARGS0(void)
#endif


	{
		int c;

		*YY_G(yy_c_buf_p) = YY_G(yy_hold_char);

		if ( *YY_G(yy_c_buf_p) == YY_END_OF_BUFFER_CHAR )
		{
			/* yy_c_buf_p now points to the character we want to return.
			* If ptrThis occurs *before* the EOB characters, then it's a
			* valid NUL; if not, then we've hit the end of the buffer.
			*/
			if ( YY_G(yy_c_buf_p) < &YY_G(yy_current_buffer)->yy_ch_buf[YY_G(yy_n_chars)] )
				/* This was really a NUL. */
				*YY_G(yy_c_buf_p) = '\0';

			else
			{ /* need more input */
				int offset = YY_G(yy_c_buf_p) - YY_G(yytext_ptr);
				++YY_G(yy_c_buf_p);

				switch ( yy_get_next_buffer( YY_CALL_ONLY_ARG ) )
				{
				case EOB_ACT_LAST_MATCH:
					/* This happens because yy_g_n_b()
					* sees that we've accumulated a
					* token and flags that we need to
					* try matching the token before
					* proceeding.  But for input(),
					* there's no matching to consider.
					* So convert the EOB_ACT_LAST_MATCH
					* to EOB_ACT_END_OF_FILE.
					*/

					/* Reset buffer status. */
					yyrestart( yyin YY_CALL_LAST_ARG);

					/*FALLTHROUGH*/

				case EOB_ACT_END_OF_FILE:
					{
						if ( yywrap( YY_CALL_ONLY_ARG ) )
							return EOF;

						if ( ! YY_G(yy_did_buffer_switch_on_eof) )
							YY_NEW_FILE;
#ifdef __cplusplus
						return yyinput(YY_CALL_ONLY_ARG);
#else
						return input(YY_CALL_ONLY_ARG);
#endif
					}

				case EOB_ACT_CONTINUE_SCAN:
					YY_G(yy_c_buf_p) = YY_G(yytext_ptr) + offset;
					break;
				}
			}
		}

		c = *(unsigned char *) YY_G(yy_c_buf_p);	/* cast for 8-bit char's */
		*YY_G(yy_c_buf_p) = '\0';	/* preserve yytext */
		YY_G(yy_hold_char) = *++YY_G(yy_c_buf_p);


		return c;
	}
#endif	/* ifndef YY_NO_INPUT */

	void yyrestart  YYFARGS1( FILE *,input_file)
	{
		if ( ! YY_G(yy_current_buffer) )
			YY_G(yy_current_buffer) =
			yy_create_buffer( yyin, YY_BUF_SIZE YY_CALL_LAST_ARG);

		yy_init_buffer( YY_G(yy_current_buffer), input_file YY_CALL_LAST_ARG);
		yy_load_buffer_state( YY_CALL_ONLY_ARG );
	}

	void yy_switch_to_buffer  YYFARGS1( YY_BUFFER_STATE ,new_buffer)
	{
		if ( YY_G(yy_current_buffer) == new_buffer )
			return;

		if ( YY_G(yy_current_buffer) )
		{
			/* Flush out information for old buffer. */
			*YY_G(yy_c_buf_p) = YY_G(yy_hold_char);
			YY_G(yy_current_buffer)->yy_buf_pos = YY_G(yy_c_buf_p);
			YY_G(yy_current_buffer)->yy_n_chars = YY_G(yy_n_chars);
		}

		YY_G(yy_current_buffer) = new_buffer;
		yy_load_buffer_state( YY_CALL_ONLY_ARG );

		/* We don't actually know whether we did ptrThis switch during
		* EOF (yywrap()) processing, but the only time ptrThis flag
		* is looked at is after yywrap() is called, so it's safe
		* to go ahead and always set it.
		*/
		YY_G(yy_did_buffer_switch_on_eof) = 1;
	}


	void yy_load_buffer_state  YYFARGS0(void)
	{
		YY_G(yy_n_chars) = YY_G(yy_current_buffer)->yy_n_chars;
		YY_G(yytext_ptr) = YY_G(yy_c_buf_p) = YY_G(yy_current_buffer)->yy_buf_pos;
		yyin = YY_G(yy_current_buffer)->yy_input_file;
		YY_G(yy_hold_char) = *YY_G(yy_c_buf_p);
	}

	YY_BUFFER_STATE yy_create_buffer  YYFARGS2( FILE *,file, int ,size)
	{
		YY_BUFFER_STATE b;

		b = (YY_BUFFER_STATE) yyalloc( sizeof( struct yy_buffer_state ) YY_CALL_LAST_ARG );
		if ( ! b )
			YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );

		b->yy_buf_size = size;

		/* yy_ch_buf has to be 2 characters longer than the size given because
		* we need to put in 2 end-of-buffer characters.
		*/
		b->yy_ch_buf = (char *) yyalloc( b->yy_buf_size + 2 YY_CALL_LAST_ARG );
		if ( ! b->yy_ch_buf )
			YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );

		b->yy_is_our_buffer = 1;

		yy_init_buffer( b, file YY_CALL_LAST_ARG);

		return b;
	}

	void yy_delete_buffer YYFARGS1( YY_BUFFER_STATE ,b)
	{
		if ( ! b )
			return;

		if ( b == YY_G(yy_current_buffer) )
			YY_G(yy_current_buffer) = (YY_BUFFER_STATE) 0;

		if ( b->yy_is_our_buffer )
			yyfree( (void *) b->yy_ch_buf YY_CALL_LAST_ARG );

		yyfree( (void *) b YY_CALL_LAST_ARG );
	}


#ifndef YY_ALWAYS_INTERACTIVE
#ifndef YY_NEVER_INTERACTIVE
#ifndef __cplusplus
	extern int isatty YY_PARAMS(( int ));
#endif /* __cplusplus */
#endif /* !YY_NEVER_INTERACTIVE */
#endif /* !YY_ALWAYS_INTERACTIVE */

	void yy_init_buffer  YYFARGS2( YY_BUFFER_STATE ,b, FILE *,file)

	{
		int oerrno = errno;

		yy_flush_buffer( b YY_CALL_LAST_ARG);

		b->yy_input_file = file;
		b->yy_fill_buffer = 1;

#if YY_ALWAYS_INTERACTIVE
		b->yy_is_interactive = 1;
#else
#if YY_NEVER_INTERACTIVE
		b->yy_is_interactive = 0;
#else
		b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;
#endif
#endif
		errno = oerrno;
	}

	void yy_flush_buffer YYFARGS1( YY_BUFFER_STATE ,b)
	{
		if ( ! b )
			return;

		b->yy_n_chars = 0;

		/* We always need two end-of-buffer characters.  The first causes
		* a transition to the end-of-buffer state.  The second causes
		* a jam in that state.
		*/
		b->yy_ch_buf[0] = YY_END_OF_BUFFER_CHAR;
		b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;

		b->yy_buf_pos = &b->yy_ch_buf[0];

		b->yy_at_bol = 1;
		b->yy_buffer_status = YY_BUFFER_NEW;

		if ( b == YY_G(yy_current_buffer) )
			yy_load_buffer_state( YY_CALL_ONLY_ARG );
	}


#ifndef YY_NO_SCAN_BUFFER
	YY_BUFFER_STATE yy_scan_buffer  YYFARGS2( char *,base, yy_size_t ,size)
	{
		YY_BUFFER_STATE b;

		if ( size < 2 ||
			base[size-2] != YY_END_OF_BUFFER_CHAR ||
			base[size-1] != YY_END_OF_BUFFER_CHAR )
			/* They forgot to leave room for the EOB's. */
			return 0;

		b = (YY_BUFFER_STATE) yyalloc( sizeof( struct yy_buffer_state ) YY_CALL_LAST_ARG );
		if ( ! b )
			YY_FATAL_ERROR( "out of dynamic memory in yy_scan_buffer()" );

		b->yy_buf_size = size - 2;	/* "- 2" to take care of EOB's */
		b->yy_buf_pos = b->yy_ch_buf = base;
		b->yy_is_our_buffer = 0;
		b->yy_input_file = 0;
		b->yy_n_chars = b->yy_buf_size;
		b->yy_is_interactive = 0;
		b->yy_at_bol = 1;
		b->yy_fill_buffer = 0;
		b->yy_buffer_status = YY_BUFFER_NEW;

		yy_switch_to_buffer( b YY_CALL_LAST_ARG );

		return b;
	}
#endif


#ifndef YY_NO_SCAN_STRING
	YY_BUFFER_STATE yy_scan_string YYFARGS1( yyconst char *,yy_str)
	{
		int len;
		for ( len = 0; yy_str[len]; ++len )
			;

		return yy_scan_bytes( yy_str, len YY_CALL_LAST_ARG);
	}
#endif


#ifndef YY_NO_SCAN_BYTES
	YY_BUFFER_STATE yy_scan_bytes  YYFARGS2( yyconst char *,bytes, int ,len)
	{
		YY_BUFFER_STATE b;
		char *buf;
		yy_size_t n;
		int i;

		/* Get memory for full buffer, including space for trailing EOB's. */
		n = len + 2;
		buf = (char *) yyalloc( n YY_CALL_LAST_ARG );
		if ( ! buf )
			YY_FATAL_ERROR( "out of dynamic memory in yy_scan_bytes()" );

		for ( i = 0; i < len; ++i )
			buf[i] = bytes[i];

		buf[len] = buf[len+1] = YY_END_OF_BUFFER_CHAR;

		b = yy_scan_buffer( buf, n YY_CALL_LAST_ARG);
		if ( ! b )
			YY_FATAL_ERROR( "bad buffer in yy_scan_bytes()" );

		/* It's okay to grow etc. ptrThis buffer, and we should throw it
		* away when we're done.
		*/
		b->yy_is_our_buffer = 1;

		return b;
	}
#endif


#ifndef YY_NO_PUSH_STATE
	static void yy_push_state YYFARGS1( int ,new_state)
	{
		if ( YY_G(yy_start_stack_ptr) >= YY_G(yy_start_stack_depth) )
		{
			yy_size_t new_size;

			YY_G(yy_start_stack_depth) += YY_START_STACK_INCR;
			new_size = YY_G(yy_start_stack_depth) * sizeof( int );

			if ( ! YY_G(yy_start_stack) )
				YY_G(yy_start_stack) = (int *) yyalloc( new_size YY_CALL_LAST_ARG );

			else
				YY_G(yy_start_stack) = (int *) yyrealloc(
				(void *) YY_G(yy_start_stack), new_size YY_CALL_LAST_ARG );

			if ( ! YY_G(yy_start_stack) )
				YY_FATAL_ERROR(
				"out of memory expanding start-condition stack" );
		}

		YY_G(yy_start_stack)[YY_G(yy_start_stack_ptr)++] = YY_START;

		BEGIN(new_state);
	}
#endif


#ifndef YY_NO_POP_STATE
	static void yy_pop_state  YYFARGS0(void)
	{
		if ( --YY_G(yy_start_stack_ptr) < 0 )
			YY_FATAL_ERROR( "start-condition stack underflow" );

		BEGIN(YY_G(yy_start_stack)[YY_G(yy_start_stack_ptr)]);
	}
#endif


#ifndef YY_NO_TOP_STATE
	static int yy_top_state  YYFARGS0(void)
	{
		return YY_G(yy_start_stack)[YY_G(yy_start_stack_ptr) - 1];
	}
#endif

#ifndef YY_EXIT_FAILURE
#define YY_EXIT_FAILURE 2
#endif

	static void yy_fatal_error YYFARGS1(yyconst char*, msg)
	{
		(void) fprintf( stderr, "%s\n", msg );
		exit( YY_EXIT_FAILURE );
	}

	/* Redefine yyless() so it works in section 3 code. */

#undef yyless
#define yyless(n) \
	do \
	{ \
	/* Undo effects of setting up yytext. */ \
	int yyless_macro_arg = (n); \
	YY_LESS_LINENO(yyless_macro_arg);\
	yytext[yyleng] = YY_G(yy_hold_char); \
	YY_G(yy_c_buf_p) = yytext + yyless_macro_arg; \
	YY_G(yy_hold_char) = *YY_G(yy_c_buf_p); \
	*YY_G(yy_c_buf_p) = '\0'; \
	yyleng = yyless_macro_arg; \
	} \
	while ( 0 )



	/* Accessor  methods (get/set functions) to struct members. */

#ifndef YY_NO_GET_EXTRA
	YY_EXTRA_TYPE yyget_extra  YYFARGS0(void)
	{
		return yyextra;
	}
#endif /* !YY_NO_GET_EXTRA */

#ifndef YY_NO_GET_LINENO
	int yyget_lineno  YYFARGS0(void)
	{
		return yylineno;
	}
#endif /* !YY_NO_GET_LINENO */

#ifndef YY_NO_GET_IN
	FILE *yyget_in  YYFARGS0(void)
	{
		return yyin;
	}
#endif /* !YY_NO_GET_IN */

#ifndef YY_NO_GET_OUT
	FILE *yyget_out  YYFARGS0(void)
	{
		return yyout;
	}
#endif /* !YY_NO_GET_OUT */

#ifndef YY_NO_GET_LENG
	int yyget_leng  YYFARGS0(void)
	{
		return yyleng;
	}
#endif /* !YY_NO_GET_LENG */

#ifndef YY_NO_GET_TEXT
	char *yyget_text  YYFARGS0(void)
	{
		return yytext;
	}
#endif /* !YY_NO_GET_TEXT */

#ifndef YY_NO_SET_EXTRA
	void yyset_extra YYFARGS1( YY_EXTRA_TYPE ,user_defined)
	{
		yyextra = user_defined ;
	}
#endif /* !YY_NO_SET_EXTRA */

#ifndef YY_NO_SET_LINENO
	void yyset_lineno YYFARGS1( int ,line_number)
	{
		yylineno = line_number;
	}
#endif /* !YY_NO_SET_LINENO */


#ifndef YY_NO_SET_IN
	void yyset_in YYFARGS1( FILE * ,in_str)
	{
		yyin = in_str ;
	}
#endif /* !YY_NO_SET_IN */

#ifndef YY_NO_SET_OUT
	void yyset_out YYFARGS1( FILE * ,out_str)
	{
		yyout = out_str ;
	}
#endif /* !YY_NO_SET_OUT */


#ifndef YY_NO_GET_DEBUG
	int yyget_debug  YYFARGS0(void)
	{
		return yy_flex_debug;
	}
#endif /* !YY_NO_GET_DEBUG */

#ifndef YY_NO_SET_DEBUG
	void yyset_debug YYFARGS1( int ,bdebug)
	{
		yy_flex_debug = bdebug ;
	}
#endif /* !YY_NO_SET_DEBUG */

	/* Accessor methods for yylval and yylloc */

#ifndef YY_NO_GET_LVAL
	YYSTYPE * yyget_lval  YYFARGS0(void)
	{
		return yylval;
	}
#endif /* !YY_NO_GET_LVAL */

#ifndef YY_NO_SET_LVAL
	void yyset_lval YYFARGS1( YYSTYPE * ,yylvalp)
	{
		yylval = yylvalp;
	}
#endif /* !YY_NO_SET_LVAL */

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YY_NO_GET_LLOC
	YYLTYPE *yyget_lloc  YYFARGS0(void)
	{
		return yylloc;
	}
#endif /* !YY_NO_GET_LLOC */

#ifndef YY_NO_SET_LLOC
	void yyset_lloc YYFARGS1( YYLTYPE * ,yyllocp)
	{
		yylloc = yyllocp;
	}
#endif /* !YY_NO_SET_LLOC */

#endif /* YYLTYPE */


	static int yy_init_globals YYFARGS0(void)
	{
		/* Initialization is the same as for the non-reentrant scanner.
		This function is called once per scanner lifetime. */

		/* We do not touch yylineno unless the option is enabled. */
#ifdef YY_USE_LINENO
		yylineno =  1;
#endif
		YY_G(yy_current_buffer) = 0;
		YY_G(yy_c_buf_p) = (char *) 0;
		YY_G(yy_init) = 1;
		YY_G(yy_start) = 0;
		YY_G(yy_start_stack_ptr) = 0;
		YY_G(yy_start_stack_depth) = 0;
		YY_G(yy_start_stack) = (int *) 0;

#ifdef YY_USES_REJECT
		YY_G(yy_state_buf) = 0;
		YY_G(yy_state_ptr) = 0;
		YY_G(yy_full_match) = 0;
		YY_G(yy_lp) = 0;
#endif

#ifdef YY_TEXT_IS_ARRAY
		YY_G(yytext_ptr) = 0;
		YY_G(yy_more_offset) = 0;
		YY_G(yy_prev_more_offset) = 0;
#endif

		/* Defined in main.c */
#ifdef YY_STDINIT
		yyin = stdin;
		yyout = stdout;
#else
		yyin = (FILE *) 0;
		yyout = (FILE *) 0;
#endif

		/* For future reference: Set errno on error, since we are called by
		* yylex_init()
		*/
		return 0;
	}

	/* User-visible API */

	/* yylex_init is special because it creates the scanner itself, so it is
	* the ONLY reentrant function that doesn't take the scanner as the last argument.
	* That's why we explicitly handle the declaration, instead of using our macros.
	*/
#ifndef YY_TRADITIONAL_FUNC_DEFS
	int yylex_init(yyscan_t* ptr_yy_globals)
#else
	int yylex_init( ptr_yy_globals )
		yyscan_t* ptr_yy_globals;
#endif
	{
		if (ptr_yy_globals == NULL){
			errno = EINVAL;
			return 1;
		}

		*ptr_yy_globals = (yyscan_t) yyalloc ( sizeof( struct yyguts_t ), NULL );

		if (*ptr_yy_globals == NULL){
			errno = ENOMEM;
			return 1;
		}

		memset(*ptr_yy_globals,0,sizeof(struct yyguts_t));

		return yy_init_globals ( *ptr_yy_globals );
	}


	/* yylex_destroy is for both reentrant and non-reentrant scanners. */
	int yylex_destroy  YYFARGS0(void)
	{
		/* Destroy the current (main) buffer. */
		yy_delete_buffer( YY_G(yy_current_buffer) YY_CALL_LAST_ARG );
		YY_G(yy_current_buffer) = NULL;

#if defined(YY_STACK_USED) || defined(YY_REENTRANT)
		/* Destroy the start condition stack. */
		if (YY_G(yy_start_stack) ){
			yyfree( YY_G(yy_start_stack) YY_CALL_LAST_ARG );
			YY_G(yy_start_stack) = NULL;
		}
#endif

#ifdef YY_USES_REJECT
		yyfree ( YY_G(yy_state_buf) YY_CALL_LAST_ARG);
#endif

		/* Destroy the main struct (reentrant only). */
		yyfree ( yyscanner YY_CALL_LAST_ARG );
		return 0;
	}


	/* Internal utility routines. */

#ifndef yytext_ptr
	static void yy_flex_strncpy YYFARGS3( char*,s1, yyconst char *,s2, int,n)
	{
		register int i;
		for ( i = 0; i < n; ++i )
			s1[i] = s2[i];
	}
#endif

#ifdef YY_NEED_STRLEN
	static int yy_flex_strlen YYFARGS1( yyconst char *,s)
	{
		register int n;
		for ( n = 0; s[n]; ++n )
			;

		return n;
	}
#endif

	/* You may override yyalloc by defining YY_NO_FLEX_ALLOC and linking to
	* your own version */
#ifndef YY_NO_FLEX_ALLOC
	void *yyalloc YYFARGS1( yy_size_t ,size)
	{
		return (void *) malloc( size );
	}
#endif

	/* You may override yyrealloc by defining YY_NO_FLEX_REALLOC and linking
	* to your own version. */
#ifndef YY_NO_FLEX_REALLOC
	void *yyrealloc  YYFARGS2( void *,ptr, yy_size_t ,size)
	{
		/* The cast to (char *) in the following accommodates both
		* implementations that use char* generic pointers, and those
		* that use void* generic pointers.  It works with the latter
		* because both ANSI C and C++ allow castless assignment from
		* any pointer type to void*, and deal with argument conversions
		* as though doing an assignment.
		*/
		return (void *) realloc( (char *) ptr, size );
	}
#endif

	/* You may override yyfree by defining YY_NO_FLEX_FREE and linking to
	* your own version.*/
#ifndef YY_NO_FLEX_FREE
	void yyfree YYFARGS1( void *,ptr)
	{
		free( (char *) ptr );	/* see yyrealloc() for (char *) cast */
	}
#endif

#define YYTABLES_NAME "yytables"

#if YY_MAIN
	int main YY_PARAMS((void));

	int main ()
	{

		yyscan_t lexer;
		yylex_init(&lexer);
		yylex( lexer );
		yylex_destroy( lexer);


		return 0;
	}
#endif
#endif /* !__sd_domnode_xml_IN_HEADER YY-END-DISCARD-FROM-HEADER */
///#line 135 "../../../src/sd/domnode-xml-scanner.l"

///#line 6741 "log4c_amalgamation.c"
/************** End of domnode-xml-scanner.c *******************************************/

/************** Begin of domnode-xml.c *******************************************/
///static const char version[] = "$Id$";

/* 
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#include <string.h>

#ifdef HAVE_LANGINFO_H
#   include <langinfo.h>
#endif

///#include "domnode-xml.h"

	/* Generated by bison(1) */
///#include "domnode-xml-parser.h"

	/* Generated by flex(1) */
#define YY_HEADER_NO_UNDEFS 1
///#include "domnode-xml-scanner.h"

	extern int __sd_domnode_xml_parse(struct __sd_domnode_xml_maker*);

	/******************************************************************************/
	static int xml_fwrite(const sd_domnode_t* ptrThis, FILE* a_stream, int a_indent)
	{
		sd_list_iter_t* iter;
		int i;

		if (!ptrThis || !ptrThis->name || !a_stream)
			return -1;

		for (i = 0; i < a_indent; i++)
			fprintf(a_stream, "    ");

		if (ptrThis->name && strcmp(ptrThis->name, "#comment") == 0) {
			fprintf(a_stream, "<!-- %s -->\n", ptrThis->value);
			return 0;
		} 

		fprintf(a_stream, "<%s", ptrThis->name);

		for (iter = sd_list_begin(ptrThis->attrs); iter != sd_list_end(ptrThis->attrs);
			iter = sd_list_iter_next(iter)) {
				sd_domnode_t* node = (sd_domnode_t*)iter->data;

				fprintf(a_stream, " %s=\"%s\"", node->name, node->value);
		}

		if (ptrThis->value || sd_list_get_nelem(ptrThis->children)) {
			fprintf(a_stream, ">\n");

			if (ptrThis->value) {
				for (i = 0; i < a_indent + 1; i++)
					fprintf(a_stream, "    ");
				fprintf(a_stream, "%s\n", ptrThis->value);
			}

			for (iter = sd_list_begin(ptrThis->children);
				iter != sd_list_end(ptrThis->children);
				iter = sd_list_iter_next(iter)) {
					sd_domnode_t* node = (sd_domnode_t*)iter->data;

					if (xml_fwrite(node, a_stream, a_indent + 1) == -1)
						return -1;
			}

			for (i = 0; i < a_indent; i++)
				fprintf(a_stream, "    ");	
			fprintf(a_stream, "</%s>\n", ptrThis->name);
		} else {
			fprintf(a_stream, "/>\n");
		}

		return 0;
	}

	/******************************************************************************/
	extern int __sd_domnode_xml_write(const sd_domnode_t* ptrThis, char** a_buffer,
		size_t* a_size)
	{
		/* TODO: to be implemented */
		return -1;
	}

	/******************************************************************************/
	extern int __sd_domnode_xml_fwrite(const sd_domnode_t* ptrThis, FILE* a_stream)
	{
#ifdef HAVE_NL_LANGINFO
		fprintf(a_stream, "<?xml version=\"1.0\" encoding=\"%s\"?>\n\n",
			nl_langinfo(CODESET));
#else
		fprintf(a_stream, "<?xml version=\"1.0\"?>\n\n");
#endif

		return xml_fwrite(ptrThis, a_stream, 0);
	}

	/******************************************************************************/
	static int xml_parse(sd_domnode_t** a_node, yyscan_t a_scanner)
	{
		int r;
		struct __sd_domnode_xml_maker maker;

		maker.scanner	= a_scanner;
		maker.elements	= sd_stack_new(0);
		maker.root		= 0;

		if (! (r = __sd_domnode_xml_parse(&maker))) *a_node = maker.root;

		sd_stack_delete(maker.elements, 0);

		return r;
	}

	/******************************************************************************/
	extern int __sd_domnode_xml_fread(sd_domnode_t** a_node, FILE* a_stream)
	{
		int r;
		yyscan_t scanner;

		yylex_init(&scanner);
		yyset_in(a_stream, scanner);

		r = xml_parse(a_node, scanner);

		yylex_destroy(scanner);

		return r;
	}

	/******************************************************************************/
	extern int __sd_domnode_xml_read(sd_domnode_t** a_node, const char* a_buffer,
		size_t a_size)
	{
		int r;
		yyscan_t scanner;

		yylex_init(&scanner);
		yy_switch_to_buffer(yy_scan_bytes(a_buffer, a_size, scanner), scanner);

		r = xml_parse(a_node, scanner);

		yylex_destroy(scanner);

		return r;
	}

/************** End of domnode-xml.c *******************************************/

/************** Begin of domnode.c *******************************************/
	///static const char version[] = "$Id$";

	/* 
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

#ifdef HAVE_CONFIG_H
///#include "config.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

///#include "malloc.h"
///#include "error.h"
///#include "domnode.h"

	/* TODO: generic format support */
///#include "domnode-xml.h"

	/******************************************************************************/
	extern sd_domnode_t* __sd_domnode_new(const char* a_name, const char* a_value,
		int is_elem)
	{
		sd_domnode_t* ptrThis;

		ptrThis = (sd_domnode_t*)sd_calloc(1, sizeof(*ptrThis));

		ptrThis->name     = a_name    ? sd_strdup(a_name) : 0;
		ptrThis->value    = a_value   ? sd_strdup(a_value): 0;
		ptrThis->children = is_elem ? sd_list_new(10) : 0;
		ptrThis->attrs    = is_elem ? sd_list_new(10) : 0;

		return ptrThis;
	}

	/******************************************************************************/
	extern sd_domnode_t* sd_domnode_new(const char* a_name, const char* a_value)
	{
		return __sd_domnode_new(a_name, a_value, 1);
	}

	/******************************************************************************/
	static int foreach_delete(sd_domnode_t* a_node, void* unused)
	{
		sd_domnode_delete(a_node);
		return 0;
	}

	/******************************************************************************/
	static void domnode_clear(sd_domnode_t* ptrThis)
	{
		free((void*) ptrThis->name);
		free((void*) ptrThis->value);

		sd_list_foreach(ptrThis->children, (sd_list_func_t) foreach_delete, 0);
		sd_list_delete(ptrThis->children);

		sd_list_foreach(ptrThis->attrs, (sd_list_func_t) foreach_delete, 0);
		sd_list_delete(ptrThis->attrs);
	}

	/******************************************************************************/
	extern void sd_domnode_delete(sd_domnode_t* ptrThis)
	{
		if (!ptrThis)
			return;

		domnode_clear(ptrThis);
		free(ptrThis);
	}

	/******************************************************************************/
	static void domnode_update(sd_domnode_t* ptrThis, sd_domnode_t* a_node)
	{
		domnode_clear(ptrThis);
		ptrThis->name	= a_node->name;
		ptrThis->value	= a_node->value;
		ptrThis->children = a_node->children;
		ptrThis->attrs	= a_node->attrs;

		/* Destroy ptrThis now empty node ! */
		free(a_node);
	}

	/******************************************************************************/
	extern int sd_domnode_fread(sd_domnode_t* ptrThis, FILE* a_stream)
	{
		int ret;
		sd_domnode_t* node;

		/* TODO: generic format support */
		if (! (ret = __sd_domnode_xml_fread(&node, a_stream)))
			domnode_update(ptrThis, node);

		return ret ? -1 : 0;
	}

	/******************************************************************************/
	extern int sd_domnode_read(sd_domnode_t* ptrThis, const char* a_buffer,
		size_t a_size)
	{
		int ret;
		sd_domnode_t* node;

		/* TODO: generic format support */
		if (! (ret = __sd_domnode_xml_read(&node, a_buffer, a_size)))
			domnode_update(ptrThis, node);

		return ret ? -1 : 0;
	}

	/******************************************************************************/
	extern int sd_domnode_write(sd_domnode_t* ptrThis, char** a_buffer,
		size_t* a_size)
	{
		/* TODO: generic format support */
		return __sd_domnode_xml_write(ptrThis, a_buffer, a_size);
	}

	/******************************************************************************/
	extern int sd_domnode_fwrite(const sd_domnode_t* ptrThis, FILE* a_stream)
	{
		/* TODO: generic format support */
		return __sd_domnode_xml_fwrite(ptrThis, a_stream);
	}

	/******************************************************************************/
	extern int sd_domnode_load(sd_domnode_t* ptrThis, const char* a_filename)
	{
		FILE* fp;
		int   ret = 0;

		if ( (fp = fopen(a_filename, "r")) == 0)
			return -1;

		ret = sd_domnode_fread(ptrThis, fp);

		fclose(fp);
		return ret;
	}

	/******************************************************************************/
	extern int sd_domnode_store(const sd_domnode_t* ptrThis, const char* afilename)
	{
		FILE* fp;
		int   ret = 0;

		if ( (fp = fopen(afilename, "w")) == 0)
			return -1;

		ret = sd_domnode_fwrite(ptrThis, fp);

		fclose(fp);
		return ret;
	}

	/******************************************************************************/
	extern sd_domnode_t* sd_domnode_search(const sd_domnode_t* ptrThis,
		const char* a_name)
	{
		sd_list_iter_t* i;

		for (i = sd_list_begin(ptrThis->children); i != sd_list_end(ptrThis->children); 
			i = sd_list_iter_next(i)) {
				sd_domnode_t* node = (sd_domnode_t*)i->data;

				if (strcmp(node->name, a_name) == 0)
					return node;
		}

		for (i = sd_list_begin(ptrThis->attrs); i != sd_list_end(ptrThis->attrs); 
			i = sd_list_iter_next(i)) {
				sd_domnode_t* node = (sd_domnode_t*)i->data;

				if (strcmp(node->name, a_name) == 0)
					return node;
		}

		for (i = sd_list_begin(ptrThis->children); i != sd_list_end(ptrThis->children); 
			i = sd_list_iter_next(i)) {
				sd_domnode_t* node = (sd_domnode_t*)i->data;

				if ((node = sd_domnode_search(node, a_name)) != 0)
					return node;
		}

		return 0;
	}

	/******************************************************************************/
	extern sd_domnode_t* sd_domnode_attrs_put(sd_domnode_t* ptrThis,
		sd_domnode_t* a_attr)
	{
		sd_list_iter_t* i;

		if (!ptrThis || !ptrThis->attrs || !a_attr || !a_attr->value)
			return 0;

		if ((i = sd_list_lookadd(ptrThis->attrs, a_attr)) == sd_list_end(ptrThis->attrs))
			return 0;

		return (sd_domnode_t*)i->data;
	}

	/******************************************************************************/
	extern sd_domnode_t* 
		sd_domnode_attrs_get(const sd_domnode_t* ptrThis, const char* a_name)
	{
		sd_list_iter_t* i;

		if (!ptrThis || !ptrThis->attrs || !a_name || !*a_name)
			return 0;

		for (i = sd_list_begin(ptrThis->attrs); i != sd_list_end(ptrThis->attrs); 
			i = sd_list_iter_next(i)) {
				sd_domnode_t* node = (sd_domnode_t*)i->data;

				if (strcmp(node->name, a_name) == 0)
					return node;
		}

		return 0;
	}

	/******************************************************************************/
	extern sd_domnode_t* 
		sd_domnode_attrs_remove(sd_domnode_t* ptrThis, const char* a_name)
	{
		sd_list_iter_t* i;

		if (!ptrThis || !ptrThis->attrs || !a_name || !*a_name)
			return 0;

		for (i = sd_list_begin(ptrThis->attrs); i != sd_list_end(ptrThis->attrs);
			i = sd_list_iter_next(i)) {
				sd_domnode_t* node = (sd_domnode_t*)i->data;

				if (strcmp(node->name, a_name) == 0) {
					sd_list_iter_del(i);
					return node;
				}
		}

		return 0;
	}

/************** End of domnode.c *******************************************/



/************** Begin of factory.c *******************************************/
	///static const char version[] = "$Id$";

	/*
	* factory.c
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	* See the COPYING file for the terms of usage and distribution.
	*/

///#include <sd/factory.h>
#include <stdlib.h>
#include <string.h>
///#include <sd/malloc.h>
///#include <sd/hash.h>
///#include <sd/error.h>

	struct __sd_factory
	{
		char*			fac_name;
		const sd_factory_ops_t*	fac_ops;
		sd_hash_t*			fac_hash;
	};

	/* xxx FIXME: unsafe hand made polymorphism ...
	* This is used to access the name field of objects created by
	* factories.  For example instances of appenders, layouts or
	* rollingpolicies.
	* So there's a supposition that the name field is always first--ptrThis is true
	* but should enforce that probably by extending a base 'name' struct.
	*/
	typedef struct {
		char* pr_name;
	} sd_factory_product_t;

	/*******************************************************************************/
	extern sd_factory_t* sd_factory_new(const char* a_name,
		const sd_factory_ops_t* a_ops)
	{
		sd_factory_t* ptrThis;

		if (!a_name || !a_ops)
			return NULL;

		ptrThis           = (sd_factory_t*)sd_calloc(1, sizeof(*ptrThis));
		ptrThis->fac_name = sd_strdup(a_name);
		ptrThis->fac_ops  = a_ops;
		ptrThis->fac_hash = sd_hash_new(20, NULL);
		return ptrThis;
	}

	/*******************************************************************************/
	extern void sd_factory_delete(sd_factory_t* ptrThis)
	{
		sd_hash_iter_t* i;

		sd_debug("sd_factory_delete['%s',",
			(ptrThis && (ptrThis->fac_name) ? ptrThis->fac_name: "(no name)"));

		if (!ptrThis){
			goto sd_factory_delete_exit;
		}

		if (ptrThis->fac_ops->fac_delete){
			for (i = sd_hash_begin(ptrThis->fac_hash); i != sd_hash_end(ptrThis->fac_hash); 
				i = sd_hash_iter_next(i)) {
					ptrThis->fac_ops->fac_delete(i->data);
			}
		}

		sd_hash_delete(ptrThis->fac_hash);
		free(ptrThis->fac_name);
		free(ptrThis);

sd_factory_delete_exit:
		sd_debug("]");
	}

	/*******************************************************************************/
	extern void* sd_factory_get(sd_factory_t* ptrThis, const char* a_name)
	{
		sd_hash_iter_t*		i;
		sd_factory_product_t*	pr;	

		if ( (i = sd_hash_lookup(ptrThis->fac_hash, a_name)) != NULL)
			return i->data;

		if (!ptrThis->fac_ops->fac_new)
			return NULL;

		if ( (pr = (sd_factory_product_t*)ptrThis->fac_ops->fac_new(a_name)) == NULL)
			return NULL;

		sd_hash_add(ptrThis->fac_hash, pr->pr_name, pr);
		return pr;

	}

	/*******************************************************************************/
	extern void sd_factory_destroy(sd_factory_t* ptrThis, void* a_pr)
	{
		sd_factory_product_t* pr = (sd_factory_product_t*) a_pr;

		sd_hash_del(ptrThis->fac_hash, pr->pr_name);
		if (ptrThis->fac_ops->fac_delete)
			ptrThis->fac_ops->fac_delete(pr);
	}

	/*******************************************************************************/
	extern void sd_factory_print(const sd_factory_t* ptrThis, FILE* a_stream)
	{
		sd_hash_iter_t* i;

		if (!ptrThis)
			return;

		if (!ptrThis->fac_ops->fac_print)
			return;

		fprintf(a_stream, "factory[%s]:\n", ptrThis->fac_name);
		for (i = sd_hash_begin(ptrThis->fac_hash); i != sd_hash_end(ptrThis->fac_hash); 
			i = sd_hash_iter_next(i)) 
		{
			ptrThis->fac_ops->fac_print(i->data, a_stream);
			fprintf(a_stream, "\n");
		}
	}

	/******************************************************************************/
	extern int sd_factory_list(const sd_factory_t* ptrThis, void** a_items,
		int a_nitems)
	{
		sd_hash_iter_t* i;
		int j;

		if (!ptrThis || !a_items || a_nitems <= 0)
			return -1;

		for (i = sd_hash_begin(ptrThis->fac_hash), j = 0;
			i != sd_hash_end(ptrThis->fac_hash);
			i = sd_hash_iter_next(i), j++)
		{
			if (j < a_nitems)
				a_items[j] = i->data;
		}

		return j;
	}

/************** End of factory.c *******************************************/


/************** Begin of hash.c *******************************************/
	///static const char version[] = "$Id$";

	/* 
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///#include <sd/hash.h>
///#include <sd/malloc.h>

#define SD_HASH_FULLTAB	2	/* rehash when table gets ptrThis x full */
#define SD_HASH_GROWTAB 4	/* grow table by ptrThis factor */
#define SD_HASH_DEFAULT_SIZE 10 /* self explenatory */

	struct __sd_hash {
		size_t			nelem;
		size_t			size;
		sd_hash_iter_t**		tab;
		const sd_hash_ops_t*	ops;
	};

#define hindex(h, n)	((h)%(n))

	/******************************************************************************/
	static void rehash(sd_hash_t* a_this)
	{
		size_t			i;
		int h, size;
		sd_hash_iter_t**	tab;
		sd_hash_iter_t*	p;
		sd_hash_iter_t*	q;

		size	= SD_HASH_GROWTAB * a_this->size;
		tab		= (sd_hash_iter_t**)sd_calloc(size, sizeof(*tab));

		if (tab == 0) return;

		for (i = 0; i < a_this->size; i++) {
			for (p = a_this->tab[i]; p; p = q) {
				q						= p->__next;
				h						= hindex(p->__hkey,
					size);
				p->__next					= tab[h];
				tab[h]					= p;
				if (p->__next != 0) p->__next->__prev	= p;
				p->__prev					= 0;
			}
		}
		free(a_this->tab);

		a_this->tab		= tab;
		a_this->size	= size;
	}

	/******************************************************************************/
	extern sd_hash_t* sd_hash_new(size_t a_size, const sd_hash_ops_t* a_ops)
	{
		const static sd_hash_ops_t default_ops = {
			/*(void*) &sd_hash_hash_string,
			(void*) &strcmp,*/
			(unsigned int ( *)(const void *))sd_hash_hash_string,
			(int ( *)(const void *,const void *))strcmp,
			0, 0, 0, 0
		};

		sd_hash_t*		hash;
		sd_hash_iter_t**	tab;

		if (a_size == 0) a_size = SD_HASH_DEFAULT_SIZE;

		hash	= (sd_hash_t*)sd_calloc(1, sizeof(*hash));
		tab		= (sd_hash_iter_t**)sd_calloc(a_size, sizeof(*tab));

		if (hash == 0 || tab == 0) {
			free(hash);
			free(tab);
			return 0;
		}

		hash->nelem	= 0;
		hash->size	= a_size;
		hash->tab	= tab;
		hash->ops	= a_ops != 0 ? a_ops : &default_ops;

		return hash;
	}

	/******************************************************************************/
	extern sd_hash_iter_t* sd_hash_lookup(sd_hash_t* a_this, const void* a_key)
	{
		int			h;
		sd_hash_iter_t*	p;

		if (a_this == 0 || a_key == 0) return 0;

		h = hindex(a_this->ops->hash(a_key), a_this->size);
		for (p = a_this->tab[h]; p != 0; p = p->__next)
			if (a_this->ops->compare(a_key, p->key) == 0) {
				return p;
			}

			return 0;
	}

	/******************************************************************************/
	extern sd_hash_iter_t* sd_hash_lookadd(sd_hash_t* a_this, const void* a_key)
	{
		int			h;
		sd_hash_iter_t*	p;

		if (a_this == 0 || a_key == 0)			return 0;
		if ((p = sd_hash_lookup(a_this, a_key)) != 0)	return p;
		if ((p = (sd_hash_iter_t*)sd_calloc(1, sizeof(*p))) == 0)		return 0;

		if (a_this->ops->key_dup != 0)
			p->key = a_this->ops->key_dup(a_key);
		else
			p->key = (void*) a_key;

		p->hash					= a_this;
		p->__hkey					= a_this->ops->hash(a_key);

		if (a_this->nelem > SD_HASH_FULLTAB * a_this->size) rehash(a_this);

		h						= hindex(p->__hkey,
			a_this->size);
		p->__next					= a_this->tab[h];
		a_this->tab[h]				= p;
		if (p->__next != 0) p->__next->__prev	= p;

		a_this->nelem++;

		return p;
	}

	/******************************************************************************/
	extern sd_hash_iter_t* sd_hash_add(sd_hash_t* a_this, const void* a_key,
		void* a_data)
	{
		sd_hash_iter_t* p;

		if ((p = sd_hash_lookadd(a_this, a_key)) == 0) return 0;

		if (a_this->ops->data_free != 0) a_this->ops->data_free(p->data);

		if (a_this->ops->data_dup != 0)
			p->data = a_this->ops->data_dup(a_data);
		else
			p->data = a_data;

		return p;
	}

	/******************************************************************************/
	extern void sd_hash_delete(sd_hash_t* a_this)
	{
		sd_hash_clear(a_this);
		free(a_this->tab);
		free(a_this);
	}

	/******************************************************************************/
	extern void sd_hash_clear(sd_hash_t* a_this)
	{
		size_t		h;
		sd_hash_iter_t*	p;
		sd_hash_iter_t*	q;

		if (a_this == 0) return;

		for (h = 0; h < a_this->size; h++) {
			for (p = a_this->tab[h]; p; p = q) {
				q = p->__next;
				if (a_this->ops->key_free) a_this->ops->key_free(p->key);
				if (a_this->ops->data_free) a_this->ops->data_free(p->data);
				free(p);
			}
			a_this->tab[h] = 0;
		}
		a_this->nelem = 0;
	}

	/******************************************************************************/
	extern void sd_hash_del(sd_hash_t* a_this, const void* a_key)
	{
		int			h;
		sd_hash_iter_t*	p;

		h = hindex(a_this->ops->hash(a_key), a_this->size);
		for (p = a_this->tab[h]; p != 0; p = p->__next)
			if (a_this->ops->compare(a_key, p->key) == 0) break;
		if (p == 0) return;

		sd_hash_iter_del(p);
	}

	/******************************************************************************/
	extern void sd_hash_foreach(sd_hash_t* a_this, sd_hash_func_t a_func,
		void* a_data)
	{
		size_t			h, ret;
		sd_hash_iter_t*	p;
		sd_hash_iter_t*	q;

		if (a_this == 0 || a_func == 0) return;

		for (h = 0; h < a_this->size; h++)
			for (p = a_this->tab[h]; p != 0; p = q) {
				p->__foreach		= 1;
				ret			= (*a_func)(p->key, p->data, a_data);
				q			= p->__next;

				if (p->__foreach == 0)
					sd_hash_iter_del(p);
				else
					p->__foreach	= 0;

				if (ret != 0) return;
			}
	}

	/******************************************************************************/
	extern unsigned int sd_hash_get_nelem(sd_hash_t* a_this)
	{
		if (a_this == 0) return 0;
		return a_this->nelem;
	}

	/******************************************************************************/
	extern unsigned int sd_hash_get_size(sd_hash_t* a_this)
	{
		if (a_this == 0) return 0;
		return a_this->size;
	}

	/******************************************************************************/
	extern sd_hash_iter_t* sd_hash_begin(sd_hash_t* a_this)
	{
		size_t h;

		if (a_this == 0) return 0;
		for (h = 0; h < a_this->size; h++)
			if (a_this->tab[h])
				return a_this->tab[h];

		return 0;
	}

	/******************************************************************************/
	extern sd_hash_iter_t* sd_hash_end(sd_hash_t* a_this)
	{
		return 0;
	}

	/******************************************************************************/
	extern sd_hash_iter_t* sd_hash_iter_next(sd_hash_iter_t* a_this)
	{
		int h;
		size_t i;

		if (a_this == 0)		return 0;
		if (a_this->__next != 0)	return a_this->__next;

		h = hindex(a_this->__hkey, a_this->hash->size);

		for (i = h + 1; i < a_this->hash->size; i++)
			if (a_this->hash->tab[i])
				return a_this->hash->tab[i];

		return 0;
	}

	/******************************************************************************/
	extern sd_hash_iter_t* sd_hash_iter_prev(sd_hash_iter_t* a_this)
	{
		int			h, i;
		sd_hash_iter_t*	p;

		if (a_this == 0)		return 0;
		if (a_this->__prev != 0)	return a_this->__prev;

		h = hindex(a_this->__hkey, a_this->hash->size);

		for (i = h - 1; i > 0; i--)
			for (p = a_this->hash->tab[i]; p; p = p->__next)
				if (p->__next == 0)
					return p;

		return 0;
	}

	/******************************************************************************/
	extern void sd_hash_iter_del(sd_hash_iter_t* a_this)
	{
		if (a_this == 0) return;

		if (a_this->hash->ops->data_free != 0)
			a_this->hash->ops->data_free(a_this->data);
		a_this->data	= 0;

		if (a_this->hash->ops->key_free != 0)
			a_this->hash->ops->key_free(a_this->key);
		a_this->key		= 0;

		if (a_this->__foreach == 1) {
			a_this->__foreach = 0;
			return;
		}

		if (a_this->__next != 0) a_this->__next->__prev = a_this->__prev;
		if (a_this->__prev != 0)
			a_this->__prev->__next = a_this->__next;
		else
			a_this->hash->tab[hindex(a_this->__hkey, a_this->hash->size)] =
			a_this->__next;

		a_this->hash->nelem--;

		free(a_this);
	}

	/******************************************************************************/
	extern unsigned int sd_hash_hash_string(const char* a_string)
	{
		register unsigned int h;

		for (h = 0; *a_string != '\0'; a_string++)
			h = *a_string + 31 * h;

		return h;
	}


/************** End of hash.c *******************************************/

	/************** Begin of appender_type_syslog.h *******************************************/
	/* $Id$
	*
	* appender_type_syslog.h
	* 
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

#ifndef log4c_appender_type_syslog_h
#define log4c_appender_type_syslog_h

	/**
	* @file appender_type_syslog.h
	*
	* @brief Log4c syslog(3) appender interface.
	*
	* The syslog appender uses the syslog(3) interface for logging. The log4c
	* priorities are mapped to the syslog priorities and the appender name is
	* used as a syslog identifier. 1 default syslog appender is defined: @c
	* "syslog".
	*
	* The following examples shows how to define and use syslog appenders.
	* 
	* @code
	*
	* log4c_appender_t* myappender;
	*
	* myappender = log4c_appender_get("myappender");
	* log4c_appender_set_type(myappender, &log4c_appender_type_syslog);
	* 
	* @endcode
	*
	**/

///#include <log4c/defs.h>
///#include <log4c/appender.h>

	__LOG4C_BEGIN_DECLS

		/**
		* Syslog appender type definition.
		*
		* This should be used as a parameter to the log4c_appender_set_type()
		* routine to set the type of the appender.
		*
		**/
		extern const log4c_appender_type_t log4c_appender_type_syslog;

	__LOG4C_END_DECLS

#endif


		/************** End of appender_type_syslog.h *******************************************/

		/************** Begin of appender_type_mmap.h *******************************************/
		/* $Id$
		*
		* appender_type_mmap.h
		* 
		* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
		*
		* See the COPYING file for the terms of usage and distribution.
		*/

#ifndef log4c_appender_type_mmap_h
#define log4c_appender_type_mmap_h

		/**
		* @file appender_type_mmap.h
		*
		* @brief Log4c mmap(2) appender interface.
		*
		* The mmap appender uses a fixed length memory mapped file for
		* logging. The appender's name is used as the file name which will be
		* opened and mapped to memory at first use. The memory mapped file is then
		* used as a rotating buffer in which logging events are written.
		*
		* The following examples shows how to define and use mmap appenders.
		* 
		* @code
		*
		* log4c_appender_t* myappender;
		*
		* myappender = log4c_appender_get("myfile.log");
		* log4c_appender_set_type(myappender, &log4c_appender_type_mmap);
		* 
		* @endcode
		*
		* @warning the file is not created at first use. It should already exist
		* and have a reasonable size, a mutilple of a page size.
		*
		**/
///#include <log4c/defs.h>
///#include <log4c/appender.h>

		__LOG4C_BEGIN_DECLS

		/**
		* Mmap appender type definition.
		*
		* This should be used as a parameter to the log4c_appender_set_type()
		* routine to set the type of the appender.
		*
		**/
		extern const log4c_appender_type_t log4c_appender_type_mmap;

	__LOG4C_END_DECLS

#endif


		/************** End of appender_type_mmap.h *******************************************/

		/************** Begin of rollingpolicy_type_sizewin.h *******************************************/

		/*
		* rollingpolicy_type_sizewin.h
		*
		* See the COPYING file for the terms of usage and distribution.
		*/

#ifndef log4c_policy_type_sizewin_h
#define log4c_policy_type_sizewin_h

		/**
		* @file rollingpolicy_type_sizewin.h
		*
		* @brief Log4c rolling file size-win interface.
		* Log4c ships with (and defaults to) the classic size-window rollover policy:
		* ptrThis triggers rollover when files reach a maximum size.  The first file in
		* the list is
		* always the current file; when a rollover event occurs files are shifted up
		* by one position in the list--if the number of files in the list has already
		* reached the max then the oldest file is rotated out of the window.
		*
		* If the max file size is set to zero, ptrThis means 'no-limit'.
		*
		* The default parameters for the size-win policy are 5 files of maximum
		* size of 20kilobytes each.  These parameters may be changed using the
		* appropriate setter functions.
		*/

///#include <log4c/defs.h>
///#include <log4c/rollingpolicy.h>

		__LOG4C_BEGIN_DECLS

		LOG4C_API const log4c_rollingpolicy_type_t log4c_rollingpolicy_type_sizewin;

	/**
	* log4c size-win rolling policy type 
	*/
	typedef struct __sizewin_udata rollingpolicy_sizewin_udata_t;

#define ROLLINGPOLICY_SIZE_DEFAULT_MAX_FILE_SIZE 1024*20
#define ROLLINGPOLICY_SIZE_DEFAULT_MAX_NUM_FILES 5

	/**
	* Get a new size-win rolling policy
	* @return a new size-win rolling policy, otherwise NULL.
	*/
	LOG4C_API rollingpolicy_sizewin_udata_t *sizewin_make_udata(void);

	/**
	* Set the maximum file size in ptrThis rolling policy configuration.
	* @param swup the size-win configuration object.
	* @param max_size the approximate maximum size any logging file will
	* attain.
	* If you set zero then it means 'no-limit' and so only one file
	* of unlimited size will be used for logging.
	* @return zero if successful, non-zero otherwise.
	*/
	LOG4C_API int sizewin_udata_set_file_maxsize(
		rollingpolicy_sizewin_udata_t * swup,
		long max_size);

	/**
	* Set the maximum number of filesin ptrThis rolling policy configuration.
	* @param swup the size-win configuration object.
	* @param max_num the maximum number of files in the list.
	* @return zero if successful, non-zero otherwise.
	*/                                                         
	LOG4C_API int sizewin_udata_set_max_num_files(
		rollingpolicy_sizewin_udata_t * swup,
		long max_num);

	/**
	* Set the rolling file appender in ptrThis rolling policy configuration.
	* @param swup the size-win configuration object.
	* @param app the rolling file appender to set.
	* @return zero if successful, non-zero otherwise.
	*/                                                            
	LOG4C_API int sizewin_udata_set_appender(
		rollingpolicy_sizewin_udata_t * swup,
		log4c_appender_t* app);

	__LOG4C_END_DECLS


#endif


		/************** End of rollingpolicy_type_sizewin.h *******************************************/

		/************** Begin of layout_type_basic.h *******************************************/
		/* $Id$
		*
		* layout_type_basic.h
		* 
		* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
		*
		* See the COPYING file for the terms of usage and distribution.
		*/

#ifndef log4c_layout_type_basic_h
#define log4c_layout_type_basic_h

		/**
		* @file layout_type_basic.h
		*
		* @brief Implement a basic layout.
		*
		* In @c log4j.PatternLayout conventions, the basic layout has the following
		* conversion pattern: @c "%P %c - %m\n".
		*
		* Where 
		* @li @c "%P" is the priority of the logging event
		* @li @c "%c" is the category of the logging event
		* @li @c "%m" is the application supplied message associated with the
		* logging event
		* 
		**/

///#include <log4c/defs.h>
///#include <log4c/layout.h>

		__LOG4C_BEGIN_DECLS

		extern const log4c_layout_type_t log4c_layout_type_basic;

	__LOG4C_END_DECLS

#endif


		/************** End of layout_type_basic.h *******************************************/


	/************** Begin of log4c/layout_type_dated.h *******************************************/
	/* $Id$
	*
	* layout_type_dated.h
	* 
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

#ifndef log4c_layout_type_dated_h
#define log4c_layout_type_dated_h

	/**
	* @file layout_type_dated.h
	*
	* @brief Implement a dated layout.
	*
	* In @c log4j.PatternLayout conventions, the dated layout has the following
	* conversion pattern: @c "%d %P %c - %m\n".
	*
	* Where 
	* @li @c "%d" is the date of the logging event
	* @li @c "%P" is the priority of the logging event
	* @li @c "%c" is the category of the logging event
	* @li @c "%m" is the application supplied message associated with the
	* logging event
	*
	* 
	* 
	**/

///#include <log4c/defs.h>
///#include <log4c/layout.h>

	__LOG4C_BEGIN_DECLS

		extern const log4c_layout_type_t log4c_layout_type_dated;

	__LOG4C_END_DECLS

#endif


		/************** End of log4c/layout_type_dated.h *******************************************/
		/************** Begin of layout_type_basic_r.h *******************************************/
		/* $Id$
		*
		* layout_type_basic_r.h
		*
		* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
		*
		* See the COPYING file for the terms of usage and distribution.
		*/

#ifndef log4c_layout_type_basic_r_h
#define log4c_layout_type_basic_r_h

		/**
		* @file layout_type_basic_r.h
		*
		* @brief Implement a basic_r layout.
		*
		* In @c log4j.PatternLayout conventions, the basic_r layout has the following
		* conversion pattern: @c "%P %c - %m\n".
		*
		* Where
		* @li @c "%P" is the priority of the logging event
		* @li @c "%c" is the category of the logging event
		* @li @c "%m" is the application supplied message associated with the
		* logging event
		*
		**/

///#include <log4c/defs.h>
///#include <log4c/layout.h>

		__LOG4C_BEGIN_DECLS

		extern const log4c_layout_type_t log4c_layout_type_basic_r;

	__LOG4C_END_DECLS

#endif


		/************** End of layout_type_basic_r.h *******************************************/
		/************** Begin of log4c/layout_type_dated_r.h *******************************************/
		/* $Id$
		*
		* layout_type_dated_r.h
		*
		* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
		*
		* See the COPYING file for the terms of usage and distribution.
		*/

#ifndef log4c_layout_type_dated_r_h
#define log4c_layout_type_dated_r_h

		/**
		* @file layout_type_dated_r.h
		*
		* @brief Implement a dated_r layout.
		*
		* In @c log4j.PatternLayout conventions, the dated_r layout has the following
		* conversion pattern: @c "%d %P %c - %m\n".
		*
		* Where
		* @li @c "%d" is the date of the logging event
		* @li @c "%P" is the priority of the logging event
		* @li @c "%c" is the category of the logging event
		* @li @c "%m" is the application supplied message associated with the
		* logging event
		*
		*
		*
		**/

		///#include <log4c/defs.h>
		///#include <log4c/layout.h>

		__LOG4C_BEGIN_DECLS

		extern const log4c_layout_type_t log4c_layout_type_dated_r;

	__LOG4C_END_DECLS

#endif


		/************** End of log4c/layout_type_dated_r.h *******************************************/
/************** Begin of init.c *******************************************/
	///static const char version[] = "$Id$";

	/*
	* init.c
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/
#ifdef HAVE_CONFIG_H
///#include "config.h"
#endif

///#include <log4c/init.h>
///#include <log4c/category.h>
///#include <log4c/appender.h>
///#include <log4c/layout.h>
///#include <log4c/rollingpolicy.h>
///#include <log4c/rc.h>
///#include <sd/error.h>
///#include <sd/sprintf.h>
///#include <sd/factory.h>
///#include <sd/sd_xplatform.h>
#include <stdlib.h>

///#include <appender_type_stream.h>
///#include <appender_type_stream2.h>
///#include <appender_type_syslog.h>
///#include <appender_type_mmap.h>
///#include <appender_type_rollingfile.h>
///#include <rollingpolicy_type_sizewin.h>
///#include <layout_type_basic.h>
///#include <layout_type_dated.h>
///#include <layout_type_basic_r.h>
///#include <layout_type_dated_r.h>

#if defined(__LOG4C_DEBUG__) && defined(__GLIBC__)
#include <mcheck.h>
#endif

	static const log4c_layout_type_t * const layout_types[] = {
		&log4c_layout_type_basic,
		&log4c_layout_type_dated,
		/* These appenders are not yet ported with msvc */
#ifndef _WIN32
		&log4c_layout_type_basic_r,
		&log4c_layout_type_dated_r    
#endif
	};
	static size_t nlayout_types = sizeof(layout_types) / sizeof(layout_types[0]);

	static const log4c_appender_type_t * const appender_types[] = {
		&log4c_appender_type_stream,
		&log4c_appender_type_stream2,
#ifdef HAVE_MMAP
		&log4c_appender_type_mmap,
#endif    
#ifdef HAVE_SYSLOG_H
		&log4c_appender_type_syslog,    
#endif
#ifdef WITH_ROLLINGFILE
		&log4c_appender_type_rollingfile
#endif
	};
	static size_t nappender_types = sizeof(appender_types) / sizeof(appender_types[0]);

#ifdef WITH_ROLLINGFILE
	static const log4c_rollingpolicy_type_t * const rollingpolicy_types[] = {
		&log4c_rollingpolicy_type_sizewin
	};
	static size_t nrollingpolicy_types = 
		sizeof(rollingpolicy_types) / sizeof(rollingpolicy_types[0]);
#endif

	static int log4c_is_init = 0;
	typedef struct rcfile
	{
		char name[256];
		time_t ctime;
		int    exists;
	} rcfile_t;

	static rcfile_t rcfiles[] = {
		{ "$LOG4C_RCPATH/log4crc" },
		{  "$HOME/.log4crc" },
		{ "./log4crc" }
	};

	static const int nrcfiles = sizeof(rcfiles) / sizeof(rcfiles[0]);


	/******************************************************************************/
	extern int log4c_init(void)
	{    
		size_t i;
		int ret = 0;

		sd_debug("log4c_init[");

		/* activate GLIBC allocation debugging */
#if defined(__LOG4C_DEBUG__) && defined(__GLIBC__)
		mtrace();
#endif

		if (log4c_is_init){
			sd_debug("log4c already initialized ]");
			return 0;
		}

		log4c_is_init++;

		/* Initialize default types: layouts, appenders, rollingpolicies */
		sd_debug("intializing default types: appenders, layouts, rollingpolicies");
		for (i = 0; i < nlayout_types; i++) 
			log4c_layout_type_set(layout_types[i]);

		for (i = 0; i < nappender_types; i++) 
			log4c_appender_type_set(appender_types[i]);
#ifdef WITH_ROLLINGFILE
		for (i = 0; i < nrollingpolicy_types; i++) 
			log4c_rollingpolicy_type_set(rollingpolicy_types[i]);
#endif

		/* load configuration files */
		{
			int i;
			sd_debug("looking for conf files...");
			snprintf(rcfiles[0].name, sizeof(rcfiles[0].name) - 1, "%s/log4crc", 
				getenv("LOG4C_RCPATH") ? getenv("LOG4C_RCPATH") : LOG4C_RCPATH);
			snprintf(rcfiles[1].name, sizeof(rcfiles[1].name) - 1, "%s/.log4crc",
				getenv("HOME") ? getenv("HOME") : "");

			for (i = 0; i < nrcfiles; i++) {
				sd_debug("checking for conf file at '%s'", rcfiles[i].name);
				if (SD_ACCESS_READ(rcfiles[i].name)) continue;
				if (SD_STAT_CTIME(rcfiles[i].name,&rcfiles[i].ctime) != 0)
					sd_error("sd_stat_ctime %s failed", rcfiles[i].name);
				rcfiles[i].exists=1;
				if (log4c_load(rcfiles[i].name) == -1) {
					sd_error("loading %s failed", rcfiles[i].name);
					ret = -1;
				}
				else
					sd_debug("loading %s succeeded", rcfiles[i].name);		
			}
		}

		/* override configuration with environment variables */
		{
			const char* priority;
			const char* appender;

			sd_debug("checking environment variables...");
			if ( (priority = getenv("LOG4C_PRIORITY")) != NULL){
				sd_debug("setting priority of root category to '%s'",
					priority);
				log4c_category_set_priority(log4c_category_get("root"), 
					log4c_priority_to_int(priority)); 
			}

			if ( (appender = getenv("LOG4C_APPENDER")) != NULL){
				sd_debug("setting appender of root category to '%s'",
					appender);
				log4c_category_set_appender(log4c_category_get("root"), 
					log4c_appender_get(appender));
			}
		}

		/*
		*   For debug dump current types and instances:
		*   ptrThis allows the caller of log4c_init() to see:
		*   1. all types currently registered, including perhaps his own.
		*   2. all instances instantiated via the configuration file.
		*   
		*   If the caller goes on to programmatically create instaces then he
		*   can call log4c_dump_all_instances() later himself to
		*   verify that they were created as expected.
		*  
		*/    
#ifdef __SD_DEBUG__
		if( getenv("SD_DEBUG")){
			log4c_dump_all_types(stderr);
			log4c_dump_all_instances(stderr);
		}
#endif


		sd_debug("]");
		return ret;
	}

	/******************************************************************************/
	void __log4c_reread(void)
	{
		time_t file_ctime;
		int i;

		for (i = 0; i < nrcfiles; i++){
			/* only reread files that existed when we first initialized */
			if (rcfiles[i].exists && SD_STAT_CTIME(rcfiles[i].name,&file_ctime) == 0){
				/* time_t is number of second since epoch, just compare for == */
				if (file_ctime != rcfiles[i].ctime){
					sd_debug("Need reread on file %s\n",rcfiles[i].name);
					SD_STAT_CTIME(rcfiles[i].name,&rcfiles[i].ctime);
					if (log4c_rc_load(log4c_rc, rcfiles[i].name) == -1){
						sd_error("re-loading config file %s failed", rcfiles[i].name);
					}
				}
			}
		}
	}

	/******************************************************************************/
	/*
	* Rereads any log4crc files that have changed
	*/
	void log4c_reread(void)
	{
#ifdef __ENABLE_REREAD__
		if (0 != log4c_rc->config.reread){
			__log4c_reread();
		}
#endif
	}



	/******************************************************************************/
	extern int log4c_fini(void)
	{
		int rc = 0;

		/* Some acceptable use of goto here to avoid lots of nested ifs
		* when we need a quick exit
		*/
		sd_debug("log4c_fini[");
		if (log4c_rc->config.nocleanup){
			sd_debug("not cleaning up--nocleanup specified in conf");
			rc = -1;
			goto log4c_fini_exit;
		}

		if (!log4c_is_init){
			rc = 0;
			sd_debug("not cleaning up--log4c not initialized");
			goto log4c_fini_exit;
		}

		log4c_is_init--;

		sd_debug("cleaning up category, appender, layout and"
			"rollingpolicy instances");
		if (log4c_category_factory) {
			sd_factory_delete(log4c_category_factory);
			log4c_category_factory = NULL;
		}

		if (log4c_appender_factory) {
			sd_factory_delete(log4c_appender_factory);
			log4c_appender_factory = NULL;
		}

		if (log4c_layout_factory) {
			sd_factory_delete(log4c_layout_factory);
			log4c_layout_factory = NULL;
		}

		if (log4c_rollingpolicy_factory) {
			sd_factory_delete(log4c_rollingpolicy_factory);
			log4c_rollingpolicy_factory = NULL;
		}

		///////////////////////////////////////////////////////////////////////////
		// 检测出来需要额外释放的内存 [9/8/2008 温辉敏]
		log4c_layout_delete_global();
		log4c_appender_delete_global();
		log4c_rollingpolicy_delete_global();

#ifdef __SD_DEBUG__
		if( getenv("SD_DEBUG")){
			sd_debug("Instance dump after cleanup:");
			log4c_dump_all_instances(stderr);
		}
#endif
#if defined(__LOG4C_DEBUG__) && defined(__GLIBC__)
		muntrace();
#endif

log4c_fini_exit:
		sd_debug("]");

		return 0;
	}

	/******************************************************************************/
#ifdef __GNUC__
	extern void __attribute__ ((constructor)) __log4c_init(void)
	{    
#ifdef WITH_CONSTRUCTORS
		log4c_init();
#endif
	}

	extern void __attribute__ ((destructor)) __log4c_fini(void)
	{    
#ifdef WITH_CONSTRUCTORS
		log4c_fini();
#endif
	}
#endif

	/******************************************************************************/

	extern void log4c_dump_all_types(FILE *fp){      
		/*
		*    
		* For debug, dump all the types that have been registered during init. We just
		* display the name of the the type for the moment--the rest of the type info 
		* right now consists of functions to call, so not really printable.
		*/

		log4c_appender_types_print(fp);
		log4c_layout_types_print(fp);
#ifdef WITH_ROLLINGFILE
		log4c_rollingpolicy_types_print(fp);
#endif
	}

	extern void log4c_dump_all_instances(FILE *fp){      

		/*
		* Also dump any instances that were created during init by 
		* reading the conf file. 
		*
		* An instances of a type consists of the base
		* type information (name plus function table) and an instance name and
		* configuration.  For example one can have an instance of the rollingfile
		* appender which logs to /var/tmp and another instance which logs to 
		* /usr/tmp.  They are both of type rollingfile, but are distinct instances of
		* it
		*/
		fprintf(fp, "instance dump follows (may be empty):\n");
		sd_factory_print(log4c_category_factory, fp);
		sd_factory_print(log4c_appender_factory, fp);
		sd_factory_print(log4c_layout_factory, fp);
#ifdef WITH_ROLLINGFILE
		sd_factory_print(log4c_rollingpolicy_factory, fp);
#endif
	}

	//////////////////////////////////////////////////////////////////////////
	///下面函数为自己写的一些函数，为使用log4c起来方便而设置的
	/** 带有配置文件名的初始化函数
	完成功能和log4c_init完全一致，只是这里的配置文件名以参数形式传入的
	@returns 0 for success .
	作者:温辉敏 日期:2008-9-6
	*/
	extern int log4c_init_with_cfg_file(const char *strCfgFileName)
	{    
		size_t i;
		int ret = 0;

		sd_debug("log4c_init[");

		/* activate GLIBC allocation debugging */
#if defined(__LOG4C_DEBUG__) && defined(__GLIBC__)
		mtrace();
#endif

		if (log4c_is_init)
		{
			sd_debug("log4c already initialized ]");
			return 0;
		}

		log4c_is_init++;

		/* Initialize default types: layouts, appenders, rollingpolicies */
		sd_debug("intializing default types: appenders, layouts, rollingpolicies");
		for (i = 0; i < nlayout_types; i++) 
		{
			log4c_layout_type_set(layout_types[i]);
		}

		for (i = 0; i < nappender_types; i++) 
		{
			log4c_appender_type_set(appender_types[i]);
		}
#ifdef WITH_ROLLINGFILE
		for (i = 0; i < nrollingpolicy_types; i++) 
		{
			log4c_rollingpolicy_type_set(rollingpolicy_types[i]);
		}
#endif

		/* load configuration files */
		{
			///int i;
			sd_debug("looking for conf files...");

			if(NULL == strCfgFileName)
			{
				sd_debug("log4c_init[ERROR:strCfgFileName==NULL");
				ret = -1;
			}
			else
			{
				time_t timeFile;

				sd_debug("checking for conf file at '%s'", strCfgFileName);
				if (SD_ACCESS_READ(strCfgFileName)) 
				{
					sd_error("loading %s failed", strCfgFileName);
					ret = -1;
				}
				else
				{
					if (SD_STAT_CTIME(strCfgFileName, &timeFile) != 0)
					{
						sd_error("sd_stat_ctime %s failed", strCfgFileName);
					}

					///rcfiles[i].exists=1;
					if (log4c_load(strCfgFileName) == -1) 
					{
						sd_error("loading %s failed", strCfgFileName);
						ret = -1;
					}
					else
					{
						sd_debug("loading %s succeeded", strCfgFileName);	
					}
				}
			}
		}

		/* override configuration with environment variables */
		{
			const char* priority;
			const char* appender;

			sd_debug("checking environment variables...");
			if ( (priority = getenv("LOG4C_PRIORITY")) != NULL){
				sd_debug("setting priority of root category to '%s'",
					priority);
				log4c_category_set_priority(log4c_category_get("root"), 
					log4c_priority_to_int(priority)); 
			}

			if ( (appender = getenv("LOG4C_APPENDER")) != NULL){
				sd_debug("setting appender of root category to '%s'",
					appender);
				log4c_category_set_appender(log4c_category_get("root"), 
					log4c_appender_get(appender));
			}
		}

		/*
		*   For debug dump current types and instances:
		*   ptrThis allows the caller of log4c_init() to see:
		*   1. all types currently registered, including perhaps his own.
		*   2. all instances instantiated via the configuration file.
		*   
		*   If the caller goes on to programmatically create instaces then he
		*   can call log4c_dump_all_instances() later himself to
		*   verify that they were created as expected.
		*  
		*/    
#ifdef __SD_DEBUG__
		if( getenv("SD_DEBUG")){
			log4c_dump_all_types(stderr);
			log4c_dump_all_instances(stderr);
		}
#endif  

		sd_debug("]");
		return ret;
	}
/************** End of init.c *******************************************/

		
		/************** Begin of log4c/layout_type_dated_threadid.h *******************************************/
		/* $Id$
		*
		* layout_type_dated_threadid.h
		* 
		* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
		*
		* See the COPYING file for the terms of usage and distribution.
		*/

#ifndef log4c_layout_type_dated_threadid_h
#define log4c_layout_type_dated_threadid_h

		/**
		* @file layout_type_dated_threadid.h
		*
		* @brief Implement a dated layout.
		*
		* In @c log4j.PatternLayout conventions, the dated layout has the following
		* conversion pattern: @c "%d %P %c - %m\n".
		*
		* Where 
		* @li @c "%d" is the date of the logging event
		* @li @c "%P" is the priority of the logging event
		* @li @c "%c" is the category of the logging event
		* @li @c "%m" is the application supplied message associated with the
		* logging event
		*
		* 
		* 
		**/

///#include <log4c/defs.h>
///#include <log4c/layout.h>

		__LOG4C_BEGIN_DECLS

		extern const log4c_layout_type_t log4c_layout_type_dated_threadid;

	__LOG4C_END_DECLS

#endif


		/************** End of log4c/layout_type_dated_threadid.h *******************************************/
/************** Begin of layout.c *******************************************/
	///static const char version[] = "$Id$";

	/*
	* layout.c
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

///#include <log4c/layout.h>
///#include <log4c/layout_type_basic.h>
///#include <log4c/layout_type_dated.h>
///#include <log4c/layout_type_dated_r.h>
///#include <log4c/layout_type_dated_threadid.h>
///#include <log4c/priority.h>
///#include <sd/hash.h>
///#include <sd/malloc.h>
///#include <sd/factory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	struct __log4c_layout
	{
		char*			lo_name;
		const log4c_layout_type_t*	lo_type;
		void*			lo_udata;
	};

	sd_factory_t* log4c_layout_factory = NULL;

	//////////////////////////////////////////////////////////////////////////
	///以下为温辉敏修改的代码，将原有代码用#if 0...#endif注释掉
	// 为解决log4c_layout_types中内存泄漏而将静态局部变量提升为全局局部变量 [9/8/2008 温辉敏]
	static sd_hash_t* layout_c_gs_types = NULL;

	static sd_hash_t* log4c_layout_types(void)
	{
		///static sd_hash_t* types = NULL;	
		if (!layout_c_gs_types)
			layout_c_gs_types = sd_hash_new(20, NULL);

		return layout_c_gs_types;
	}

	/** 删除本layout.c文件中定义的全局和静态的指针指向的内存,防止内存泄漏
	如：
	1.layout_c_gs_types.
	2.
	@return void.
	作者：温辉敏 日期:2008.09.08
	*/
	extern void log4c_layout_delete_global()
	{
		if (NULL != layout_c_gs_types)
		{
			sd_hash_delete(layout_c_gs_types);
			layout_c_gs_types = NULL;
		}
	}

	//////////////////////////////////////////////////////////////////////////

#if 0
	/**
	* @bug log4c_appender_type hash is not freed in destructor
	*/

	/*******************************************************************************/
	static sd_hash_t* log4c_layout_types(void)
	{
		static sd_hash_t* types = NULL;

		if (!types)
			types = sd_hash_new(20, NULL);

		return types;
	}
#endif

	extern void log4c_layout_types_print(FILE *fp)
	{
		sd_hash_iter_t* i;

		fprintf(fp, "layout types:");
		for (i = sd_hash_begin(log4c_layout_types());
			i != sd_hash_end(log4c_layout_types()); 
			i = sd_hash_iter_next(i) ) 
		{
			fprintf(fp, "'%s' ",((log4c_layout_type_t *)(i->data))->name );
		}
		fprintf(fp, "\n");
	}

	/*******************************************************************************/
	extern const log4c_layout_type_t* log4c_layout_type_get(const char* a_name)
	{
		sd_hash_iter_t* i;

		if (!a_name)
			return NULL;

		if ( (i = (sd_hash_iter_t*)sd_hash_lookup(log4c_layout_types(), a_name)) != NULL)
			return (log4c_layout_type_t*)i->data;

		return NULL;
	}

	/*******************************************************************************/
	extern const log4c_layout_type_t* log4c_layout_type_set(
		const log4c_layout_type_t* a_type)
	{
		sd_hash_iter_t* i = NULL;
		void* previous = NULL;

		if (!a_type)
			return NULL;

		if ( (i = sd_hash_lookadd(log4c_layout_types(), a_type->name)) == NULL)
			return NULL;

		previous = i->data;
		i->data  = (void*) a_type;

		return (log4c_layout_type_t*)previous;
	}
	/*******************************************************************************/
	extern log4c_layout_t* log4c_layout_get(const char* a_name)
	{
		static const sd_factory_ops_t log4c_layout_factory_ops = {
			/*(void*) log4c_layout_new,
			(void*) log4c_layout_delete,
			(void*) log4c_layout_print,*/
			(void *( *)(const char *))log4c_layout_new,
			(void ( *)(void *))log4c_layout_delete,
			(void ( *)(void *,FILE *))log4c_layout_print
		};

		if (!log4c_layout_factory) {
			log4c_layout_factory = sd_factory_new("log4c_layout_factory", 
				&log4c_layout_factory_ops);
			/* build default layouts */
			log4c_layout_set_type(log4c_layout_get("dated"), &log4c_layout_type_dated);
			log4c_layout_set_type(log4c_layout_get("basic"), &log4c_layout_type_basic);

			// 添加新的layouts [2/3/2008 温辉敏]
			log4c_layout_set_type(log4c_layout_get("dated_r"), &log4c_layout_type_dated_r);
			log4c_layout_set_type(log4c_layout_get("dated_threadid"), &log4c_layout_type_dated_threadid);
		}

		return (log4c_layout_t *)sd_factory_get(log4c_layout_factory, a_name);
	}

	/*******************************************************************************/
	extern log4c_layout_t* log4c_layout_new(const char* a_name)
	{
		log4c_layout_t* ptrThis;

		if (!a_name)
			return NULL;

		ptrThis	    = (log4c_layout_t*)sd_calloc(1, sizeof(log4c_layout_t));
		ptrThis->lo_name   = sd_strdup(a_name);
		ptrThis->lo_type   = &log4c_layout_type_basic;
		ptrThis->lo_udata  = NULL;

		return ptrThis;
	}

	/*******************************************************************************/
	extern void log4c_layout_delete(log4c_layout_t* ptrThis)
	{
		if (!ptrThis)
			return;

		free(ptrThis->lo_name);
		free(ptrThis);
	}

	/*******************************************************************************/
	extern const char* log4c_layout_get_name(const log4c_layout_t* ptrThis)
	{
		return (ptrThis ? ptrThis->lo_name : NULL);
	}

	/*******************************************************************************/
	extern const log4c_layout_type_t* log4c_layout_get_type(const log4c_layout_t* ptrThis)
	{
		return (ptrThis ? ptrThis->lo_type : NULL);
	}

	/*******************************************************************************/
	extern const log4c_layout_type_t* log4c_layout_set_type(
		log4c_layout_t*		ptrThis, 
		const log4c_layout_type_t*	a_type)
	{
		const log4c_layout_type_t* previous;

		if (!ptrThis)
			return NULL;

		previous = ptrThis->lo_type;
		ptrThis->lo_type = a_type;
		return previous;
	}

	/*******************************************************************************/
	extern void* log4c_layout_get_udata(const log4c_layout_t* ptrThis)
	{
		return (ptrThis ? ptrThis->lo_udata : NULL);
	}

	/*******************************************************************************/
	extern void* log4c_layout_set_udata(log4c_layout_t* ptrThis, void* a_udata)
	{
		void* previous;

		if (!ptrThis)
			return NULL;

		previous = ptrThis->lo_udata;
		ptrThis->lo_udata = a_udata;
		return previous;
	}

	/*******************************************************************************/
	extern const char* log4c_layout_format(
		const log4c_layout_t*		ptrThis, 
		const log4c_logging_event_t*a_event)
	{
		if (!ptrThis)
			return NULL;

		if (!ptrThis->lo_type)
			return NULL;

		if (!ptrThis->lo_type->format)
			return NULL;

		return ptrThis->lo_type->format(ptrThis, a_event);
	}

	/*******************************************************************************/
	extern void log4c_layout_print(const log4c_layout_t* ptrThis, FILE* a_stream)
	{
		if (!ptrThis) 
			return;

		fprintf(a_stream, "{ name:'%s' type:'%s' udata:%p }", 
			ptrThis->lo_name, 
			ptrThis->lo_type ? ptrThis->lo_type->name : "(no set)", 
			ptrThis->lo_udata);
	}


/************** End of layout.c *******************************************/



/************** Begin of layout_type_basic.c *******************************************/
	///static const char version[] = "$Id$";

	/*
	* layout.c
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

///#include <log4c/layout.h>
///#include <log4c/priority.h>
///#include <sd/sprintf.h>
///#include <sd/sd_xplatform.h>
#include <stdio.h>

	/*******************************************************************************/
	static const char* basic_format(
		const log4c_layout_t*	  	a_layout,
		const log4c_logging_event_t*	a_event)
	{
		static char buffer[1024];

		snprintf(buffer, sizeof(buffer), "%-6s %s: %s\n", /*"%-8s %s - %s\n"*/
			log4c_priority_to_string(a_event->evt_priority),
			a_event->evt_category, a_event->evt_msg);

		return buffer;
	}

	/*******************************************************************************/
	const log4c_layout_type_t log4c_layout_type_basic = {
		"basic",
		basic_format,
	};
/************** End of layout_type_basic.c *******************************************/



/************** Begin of layout_type_basic_r.c *******************************************/
	///static const char version[] = "$Id$";

	/*
	* layout.c
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

///#include <log4c/layout.h>
///#include <log4c/priority.h>
///#include <sd/sprintf.h>
#include <stdio.h>

	/*******************************************************************************/
	static const char* basic_r_format(
		const log4c_layout_t*	  	a_layout,
		const log4c_logging_event_t*	a_event)
	{
		int n, i;

		n = snprintf(a_event->evt_buffer.buf_data, a_event->evt_buffer.buf_size,
			"%-6s %s: %s\n", /* "%-8s %s - %s\n" */
			log4c_priority_to_string(a_event->evt_priority),
			a_event->evt_category, a_event->evt_msg);

		if (n >= a_event->evt_buffer.buf_size) {
			/*
			* append '...' at the end of the message to show it was
			* trimmed
			*/
			for (i = 0; i < 3; i++)
				a_event->evt_buffer.buf_data[a_event->evt_buffer.buf_size - 4 + i] = '.';
		}

		return a_event->evt_buffer.buf_data;
	}

	/*******************************************************************************/
	const log4c_layout_type_t log4c_layout_type_basic_r = {
		"basic_r",
		basic_r_format,
	};


/************** End of layout_type_basic_r.c *******************************************/


/************** Begin of layout_type_dated.c *******************************************/
	///static const char version[] = "$Id$";

	/*
	* layout.c
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

///#include <log4c/layout.h>
///#include <log4c/priority.h>
///#include <sd/sprintf.h>
///#include <sd/sd_xplatform.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

	/*******************************************************************************/
	static const char* dated_format(
		const log4c_layout_t*  	a_layout,
		const log4c_logging_event_t*a_event)
	{
		static char buffer[1024];

#ifndef _WIN32
#ifndef __HP_cc
#warning gmtime() routine should be defined in sd_xplatform
#endif
		struct tm   tm;
		gmtime_r(&a_event->evt_timestamp.tv_sec, &tm);
		/*
		snprintf(buffer, sizeof(buffer), "%04d%02d%02d %02d:%02d:%02d.%03ld %-8s %s- %s\n",
			tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
			tm.tm_hour, tm.tm_min, tm.tm_sec,
			a_event->evt_timestamp.tv_usec / 1000,
			log4c_priority_to_string(a_event->evt_priority),
			a_event->evt_category, a_event->evt_msg);
		*/
		snprintf(buffer, sizeof(buffer), "%04d%02d%02d %02d:%02d:%02d %-6s %s: %s\n",
			tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
			tm.tm_hour, tm.tm_min, tm.tm_sec,
			log4c_priority_to_string(a_event->evt_priority),
			a_event->evt_category, a_event->evt_msg);

#else
		SYSTEMTIME stime;

		if ( FileTimeToSystemTime(&a_event->evt_timestamp, &stime)){

			/// 下面将UTC时间转换为本地时间 [1/31/2008 温辉敏]
#if 1
			{
				TIME_ZONE_INFORMATION timeZone;
				///SYSTEMTIME sysTimeLocal;
				///SYSTEMTIME sysTimeUTC;

				DWORD dwResult = GetTimeZoneInformation(&timeZone);
				BOOL bResult = SystemTimeToTzSpecificLocalTime(
					&timeZone,
					&stime,
					&stime
					);
			}
#endif
			/*
			snprintf(buffer, sizeof(buffer), "%04d%02d%02d %02d:%02d:%02d.%03ld %-8s %s- %s\n",
				stime.wYear, stime.wMonth , stime.wDay,
				stime.wHour, stime.wMinute, stime.wSecond,
				stime.wMilliseconds,
				log4c_priority_to_string(a_event->evt_priority),
				a_event->evt_category, a_event->evt_msg);
			*/
			snprintf(buffer, sizeof(buffer), "%04d%02d%02d %02d:%02d:%02d %-6s %s: %s\n",
				stime.wYear, stime.wMonth , stime.wDay,
				stime.wHour, stime.wMinute, stime.wSecond,
				log4c_priority_to_string(a_event->evt_priority),
				a_event->evt_category, a_event->evt_msg);

		}
#endif
		return buffer;
	}

	/*******************************************************************************/
	const log4c_layout_type_t log4c_layout_type_dated = {
		"dated",
		dated_format,
	};


/************** End of layout_type_dated.c *******************************************/


/************** Begin of layout_type_dated_r.c *******************************************/
	///static const char version[] = "$Id$";

	/*
	* layout.c
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

///#include <log4c/layout.h>
///#include <log4c/priority.h>
///#include <sd/sprintf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

	/*******************************************************************************/
	static const char* dated_r_format(
		const log4c_layout_t*  	a_layout,
		const log4c_logging_event_t*a_event)
	{
		int n, i;

#ifndef _WIN32
#ifndef __HP_cc
#warning gmtime() routine should be defined in sd_xplatform
#endif
		struct tm	tm;
		gmtime_r(&a_event->evt_timestamp.tv_sec, &tm);
#else
		// 下面代码有问题，暂时注释掉 [2/3/2008 温辉敏]
#if (0)
		/* xxx Need a CreateMutex/ReleaseMutex or something here
		*/
		{ 
			struct tm *tmp = NULL;
			tmp = gmtime(&a_event->evt_timestamp.tv_sec);
			tm = *tmp; /* struct copy */
		}
#endif
#endif

		/// 下面将UTC时间转换为本地时间 [1/31/2008 温辉敏]
#ifdef _WIN32
		{
			SYSTEMTIME stime;

			if ( FileTimeToSystemTime(&a_event->evt_timestamp, &stime)){
				/// 下面将UTC时间转换为本地时间 [1/31/2008 温辉敏]
				{
					TIME_ZONE_INFORMATION timeZone;
					///SYSTEMTIME sysTimeLocal;
					///SYSTEMTIME sysTimeUTC;

					DWORD dwResult = GetTimeZoneInformation(&timeZone);
					BOOL bResult = SystemTimeToTzSpecificLocalTime(
						&timeZone,
						&stime,
						&stime
						);
				}
			}
			/*
			n = snprintf(a_event->evt_buffer.buf_data, a_event->evt_buffer.buf_size, 
				"%04d%02d%02d %02d:%02d:%02d.%03ld %-8s %s - %s\n",
				stime.wYear, stime.wMonth , stime.wDay,
				stime.wHour, stime.wMinute, stime.wSecond,
				stime.wMilliseconds,
				log4c_priority_to_string(a_event->evt_priority),
				a_event->evt_category, a_event->evt_msg);
			*/
			n = snprintf(a_event->evt_buffer.buf_data, a_event->evt_buffer.buf_size, 
				"%04d%02d%02d %02d:%02d:%02d %-6s %s: %s\n",
				stime.wYear, stime.wMonth , stime.wDay,
				stime.wHour, stime.wMinute, stime.wSecond,
				log4c_priority_to_string(a_event->evt_priority),
				a_event->evt_category, a_event->evt_msg);

		}
#endif

#if (0)
		/*
		n = snprintf(a_event->evt_buffer.buf_data, a_event->evt_buffer.buf_size,
			"%04d%02d%02d %02d:%02d:%02d.%03ld %-8s %s - %s\n",
			tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
			tm.tm_hour, tm.tm_min, tm.tm_sec,
			a_event->evt_timestamp.tv_usec / 1000,
			log4c_priority_to_string(a_event->evt_priority),
			a_event->evt_category, a_event->evt_msg);
		*/
		n = snprintf(a_event->evt_buffer.buf_data, a_event->evt_buffer.buf_size,
			"%04d%02d%02d %02d:%02d:%02d %-6s %s: %s\n",
			tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
			tm.tm_hour, tm.tm_min, tm.tm_sec,
			log4c_priority_to_string(a_event->evt_priority),
			a_event->evt_category, a_event->evt_msg);

#endif

		if (n >= a_event->evt_buffer.buf_size) {
			/*
			* append '...' at the end of the message to show it was
			* trimmed
			*/
			for (i = 0; i < 3; i++)
				a_event->evt_buffer.buf_data[a_event->evt_buffer.buf_size - 4 + i] = '.';
		}

		return a_event->evt_buffer.buf_data;
	}

	/*******************************************************************************/
	const log4c_layout_type_t log4c_layout_type_dated_r = {
		"dated_r",
		dated_r_format,
	};


/************** End of layout_type_dated_r.c *******************************************/

/************** Begin of layout_type_dated_threadid.c *******************************************/
	///static const char version[] = "$Id$";

	/*
	* layout.c
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

///#include <log4c/layout.h>
///#include <log4c/priority.h>
///#include <sd/sprintf.h>
///#include <sd/sd_xplatform.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

	/*******************************************************************************/
	static const char* dated_threadid_format(
		const log4c_layout_t*  	a_layout,
		const log4c_logging_event_t*a_event)
	{
		static char buffer[LOG4C_BUFFER_SIZE_MAX];
#ifdef _WIN32
		SYSTEMTIME stime;
		DWORD dwThreadID = 0;

		if ( FileTimeToSystemTime(&a_event->evt_timestamp, &stime)){
			/// 下面将UTC时间转换为本地时间 [1/31/2008 温辉敏]
			{
				TIME_ZONE_INFORMATION timeZone;
				///SYSTEMTIME sysTimeLocal;
				///SYSTEMTIME sysTimeUTC;

				DWORD dwResult = GetTimeZoneInformation(&timeZone);
				BOOL bResult = SystemTimeToTzSpecificLocalTime(
					&timeZone,
					&stime,
					&stime
					);
			}

			/// 将线程ID也打印到日志中去
			dwThreadID = GetCurrentThreadId();
			/*
			snprintf(buffer, sizeof(buffer), "%04d%02d%02d %02d:%02d:%02d.%03ld ThreadID:%-8u %-8s %s- %s\n",
				stime.wYear, stime.wMonth , stime.wDay,
				stime.wHour, stime.wMinute, stime.wSecond,
				stime.wMilliseconds,
				dwThreadID,
				log4c_priority_to_string(a_event->evt_priority),
				a_event->evt_category, a_event->evt_msg);
			*/
			snprintf(buffer, sizeof(buffer), "%04d%02d%02d %02d:%02d:%02d tid:%u %-6s %s: %s\n",
				stime.wYear, stime.wMonth , stime.wDay,
				stime.wHour, stime.wMinute, stime.wSecond,
				dwThreadID,
				log4c_priority_to_string(a_event->evt_priority),
				a_event->evt_category, a_event->evt_msg);

		}
#else #ifndef _WIN32
		struct tm   tm;
		pthread_t threadID = pthread_self();

		///gmtime_r(&a_event->evt_timestamp.tv_sec, &tm);
		localtime_r(&a_event->evt_timestamp.tv_sec, &tm);
		/*
		snprintf(buffer, sizeof(buffer), "%04d%02d%02d %02d:%02d:%02d.%03ld ThreadID:%-8u %-8s %s- %s\n",
			tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
			tm.tm_hour, tm.tm_min, tm.tm_sec,
			a_event->evt_timestamp.tv_usec / 1000,
			threadID,
			log4c_priority_to_string(a_event->evt_priority),
			a_event->evt_category, a_event->evt_msg);
		*/
		snprintf(buffer, sizeof(buffer), "%04d%02d%02d %02d:%02d:%02d tid:%u %-6s %s: %s\n",
			tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
			tm.tm_hour, tm.tm_min, tm.tm_sec,
			threadID,
			log4c_priority_to_string(a_event->evt_priority),
			a_event->evt_category, a_event->evt_msg);

#endif

		return buffer;
	}

	/*******************************************************************************/
	const log4c_layout_type_t log4c_layout_type_dated_threadid = {
		"dated_threadid",
		dated_threadid_format,
	};



/************** End of layout_type_dated_threadid.c *******************************************/

	

/************** Begin of list.c *******************************************/
	///static const char version[] = "$Id$";

	/* 
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

///#include <sd/list.h>
///#include <sd/malloc.h>
#include <stdlib.h>

	struct __sd_list {
		sd_list_iter_t*	head;
		sd_list_iter_t*	tail;
		size_t 		nelem;
	};

	/******************************************************************************/
	extern sd_list_t* sd_list_new(size_t a_capacity)
	{
		sd_list_t* ptrThis;

		ptrThis	= (sd_list_t*)sd_calloc(1, sizeof(sd_list_t));
		ptrThis->head	= 0;
		ptrThis->tail	= 0;
		ptrThis->nelem	= 0;
		return ptrThis;
	}

	/******************************************************************************/
	extern void sd_list_delete(sd_list_t* a_this)
	{
		sd_list_iter_t *a_next;
		sd_list_iter_t *a_current;

		if (!a_this)
			return;

		/* Free the iterators */
		if (a_this->nelem > 0){
			a_current = a_this->head;
			do {
				a_next = a_current->__next;
				free(a_current);
				a_current = a_next;
			} while (a_current);
		}

		free(a_this);
	}

	/******************************************************************************/
	extern void sd_list_clear(sd_list_t* a_this)
	{
		a_this->head    = 0;
		a_this->tail    = 0;
		a_this->nelem   = 0;
	}

	/******************************************************************************/
	extern size_t sd_list_get_nelem(sd_list_t* a_this)
	{
		return (a_this ? a_this->nelem : 0);
	}

	/******************************************************************************/
	extern sd_list_iter_t* sd_list_begin(sd_list_t* a_this)
	{
		return (a_this ? a_this->head : 0);
	}

	/******************************************************************************/
	extern sd_list_iter_t* sd_list_end(sd_list_t* a_this)
	{
		return 0;
	}

	/******************************************************************************/
	extern sd_list_iter_t* sd_list_rbegin(sd_list_t* a_this)
	{
		return (a_this ? a_this->tail : 0);
	}

	/******************************************************************************/
	extern sd_list_iter_t* sd_list_rend(sd_list_t* a_this)
	{
		return 0;
	}

	/******************************************************************************/
	extern sd_list_iter_t* sd_list_lookup(sd_list_t* a_this, void* a_data)
	{
		sd_list_iter_t* i;

		if (! a_this) return 0;

		for (i = a_this->head; i; i = i->__next)
			if (a_data == i->data)
				return i;

		return 0;
	}

	/******************************************************************************/
	extern sd_list_iter_t* sd_list_lookadd(sd_list_t* a_this, void* a_data)
	{
		sd_list_iter_t* i;

		if (! a_this) return 0;

		if ((i = sd_list_lookup(a_this, a_data)) != 0)
			return i;

		return sd_list_add(a_this, a_data);
	}

	/******************************************************************************/
	extern sd_list_iter_t* sd_list_add(sd_list_t* a_this, void* a_data)
	{
		sd_list_iter_t* i;

		if (! a_this) return 0;


		if ((i = (sd_list_iter_t*)sd_calloc(1, sizeof(*i))) == 0)
			return 0;

		i->data		= a_data;
		i->list		= a_this;    
		i->__next		= a_this->head;
		i->__prev		= 0;
		a_this->head	= i;

		if (i->__next) i->__next->__prev	= i;
		if (!a_this->tail) a_this->tail	= i;

		a_this->nelem++;

		return i;
	}

	/******************************************************************************/
	extern sd_list_iter_t* sd_list_sortadd(sd_list_t* a_this,
		sd_list_func_t a_func, void* a_data)
	{
		sd_list_iter_t* i;

		if (! a_this || ! a_func) return 0;

		for (i = a_this->head; i; i = i->__next)
			if ((*a_func)(i->data, a_data) > 0)
				break;

		if (i)
			return sd_list_iter_insert(i, a_data);
		else
			return sd_list_append(a_this, a_data);
	}

	/******************************************************************************/
	extern int sd_list_del(sd_list_t* a_this, void* a_data)
	{
		sd_list_iter_t* i;

		if (!a_this)
			return -1;

		for (i = a_this->head; i; i = i->__next)
			if (a_data == i->data)
				break;

		if (!i)
			return -1;

		sd_list_iter_del(i);
		return 0;
	}

	/******************************************************************************/
	extern void sd_list_foreach(sd_list_t* a_this, sd_list_func_t a_func,
		void* a_userdata)
	{
		sd_list_iter_t* i;
		sd_list_iter_t* j;

		if (!a_this || !a_func)
			return;

		for (i = a_this->head; i; i = j) {
			int ret;

			i->__foreach	= 1;
			ret		= (*a_func)(i->data, a_userdata);
			j		= i->__next;

			if (i->__foreach == 0)
				sd_list_iter_del(i);
			else
				i->__foreach = 0;

			if (ret) return;
		}
	}

	/******************************************************************************/
	extern void sd_list_rforeach(sd_list_t* a_this, sd_list_func_t a_func,
		void* a_userdata)
	{
		sd_list_iter_t* i;
		sd_list_iter_t* j;

		if (!a_this || !a_func)
			return;

		for (i = a_this->tail; i; i = j) {
			int ret;

			i->__foreach	= 1;
			ret		= (*a_func)(i->data, a_userdata);
			j		= i->__prev;

			if (i->__foreach == 0)
				sd_list_iter_del(i);
			else
				i->__foreach = 0;

			if (ret) return;
		}
	}

	/******************************************************************************/
	extern sd_list_iter_t* sd_list_iter_next(sd_list_iter_t* a_this)
	{
		return (a_this ? a_this->__next : 0);
	}

	/******************************************************************************/
	extern sd_list_iter_t* sd_list_iter_prev(sd_list_iter_t* a_this)
	{
		return (a_this ? a_this->__prev : 0);
	}

	/******************************************************************************/
	extern void sd_list_iter_del(sd_list_iter_t* a_this)
	{
		if (!a_this)
			return;

		if (a_this->__foreach == 1) {
			a_this->__foreach = 0;
			return;
		}

		if (a_this->__next)
			a_this->__next->__prev = a_this->__prev;
		else
			a_this->list->tail = a_this->__prev;

		if (a_this->__prev)
			a_this->__prev->__next = a_this->__next;
		else
			a_this->list->head = a_this->__next;

		a_this->list->nelem--;

		free(a_this);
	}

	/******************************************************************************/
	extern sd_list_iter_t* sd_list_iter_insert(sd_list_iter_t* a_this,
		void* a_data)
	{
		sd_list_iter_t* i;

		if (! a_this) return 0;

		if (a_this->list->head == a_this)
			return sd_list_prepend(a_this->list, a_data);

		if ((i = (sd_list_iter_t*)sd_calloc(1, sizeof(*i))) == 0)
			return 0;

		i->data			= a_data;
		i->list			= a_this->list;
		i->__prev			= a_this->__prev;
		i->__next			= a_this;

		/* CAUTION: always exists since a_this is not the head */
		a_this->__prev->__next	= i;    
		a_this->__prev		= i;

		a_this->list->nelem++;

		return i;
	}

	/******************************************************************************/
	extern sd_list_iter_t* sd_list_prepend(sd_list_t* a_this, void* a_data)
	{
		sd_list_iter_t* i;

		if (! a_this) return 0;

		if ((i = (sd_list_iter_t*)sd_calloc(1, sizeof(*i))) == 0)
			return 0;

		i->list		= a_this;
		i->data		= a_data;
		i->__prev		= 0;
		i->__next		= a_this->head;
		a_this->head	= i;

		if (i->__next)
			i->__next->__prev	= i;
		else
			a_this->tail		= i;

		a_this->nelem++;

		return i;
	}

	/******************************************************************************/
	extern sd_list_iter_t* sd_list_append(sd_list_t* a_this, void* a_data)
	{
		sd_list_iter_t* i;

		if (! a_this) return 0;

		if ((i = (sd_list_iter_t*)sd_calloc(1, sizeof(*i))) == 0)
			return 0;

		i->list		= a_this;
		i->data		= a_data;
		i->__prev		= a_this->tail;
		i->__next		= 0;
		a_this->tail	= i;

		if (i->__prev)
			i->__prev->__next	= i;
		else
			a_this->head		= i;

		a_this->nelem++;

		return i;
	}

/************** End of list.c *******************************************/

/************** Begin of log.c *******************************************/
/*
* log.cpp
*
* added by 温辉敏 in 2008-2-3
* 日志相关代码的定义文件
*/

#ifdef HAVE_CONFIG_H
///#include "config.h"
#endif

#include <stdlib.h>
#include <string.h>
#ifdef  HAVE_ALLOCA_H
#include <alloca.h>
#endif
///#include <sd/sprintf.h>
///#include <sd/malloc.h>
///#include <sd/factory.h>
///#include <log4c/appender.h>
///#include <log4c/priority.h>
///#include <log4c/logging_event.h>
///#include <log4c/category.h>
///#include <log4c/rc.h>
///#include <sd/error.h>
///#include <sd/sd_xplatform.h>
///#include <sd/sd_xplatform.h>

///#include "../vos/include/vos.h"
///#include "log.h"
///#include "GlobalMacro.h"

	//////////////////////////////////////////////////////////////////////////
	///下面括起来代码和log_check拷贝自init.c
	typedef struct log_c_rcfile
	{
		char name[256];
		time_t ctime;
		int    exists;
	} log_c_rcfile_t;

	static log_c_rcfile_t log_c_rcfiles[] = 
	{
#if 1
		{ "$LOG4C_RCPATH/log4crc" },
		{  "$HOME/.log4crc" },
#endif 
		{ "./log4crc" }
	};

	static const int log_c_nrcfiles = sizeof(log_c_rcfiles) / sizeof(log_c_rcfiles[0]);
	//////////////////////////////////////////////////////////////////////////
	static SEM_ID gs_semphore = NULL;
	static int gs_iModuleUsage_shmid = 0;

	//////////////////////////////////////////////////////////////////////////


	/** 日志模块初始化
	@return int:return 0 for success 
	作者:温辉敏  日期:2008-2-3
	*/
	int log_init()
	{
		///设置两个环境变量SD_DEBUG和SD_ERROR,使sd_debug和sd_error两个函数起作用
		///putenv("SD_DEBUG=SD_DEBUG");
		///putenv("SD_ERROR=SD_ERROR");
		log_check();
		return(log4c_init());
	}

	/** 日志模块初始化,指定配置文件名称
	@return int:return 0 for success 
	作者:温辉敏  日期:2008-9-5
	*/
	int log_init_with_cfg_file(const char *strCfgFileName)
	{
		log_check_with_cfg_file(strCfgFileName);
		return(log4c_init_with_cfg_file(strCfgFileName));
	}

	extern void ReleaseModuleUsage();
	/** 日志模块清理
	@return int:return 0 for success 
	作者:温辉敏  日期:2008-2-3
	*/
	int log_fini()
	{
		int iResult = log4c_fini();

		// 解决资源泄漏 [4/18/2009 温辉敏]
		VOS_DELETE_SEM(gs_semphore);
		ReleaseModuleUsage();

		return iResult;
	}

	/**检测配置文件是否存在
	@return const int : iPriority.
	作者:温辉敏  日期:2008-2-18
	*/
	const int log_check(void)
	{ 
		int iReturn = 0;
		BOOL bCfgFileExist = FALSE;
		int i = 0;

		printf("check configuration files...\n");

		/* check configuration files */		
		printf("looking for conf files...\n");

#if 1
		snprintf(log_c_rcfiles[0].name, sizeof(log_c_rcfiles[0].name) - 1, "%s/log4crc", 
			getenv("LOG4C_RCPATH") ? getenv("LOG4C_RCPATH") : LOG4C_RCPATH);
		snprintf(log_c_rcfiles[1].name, sizeof(log_c_rcfiles[1].name) - 1, "%s/.log4crc",
			getenv("HOME") ? getenv("HOME") : "");
#endif

		for (i = 0; i < log_c_nrcfiles; i++) 
		{
			printf("checking for conf file at '%s'\n", log_c_rcfiles[i].name);
			if (SD_ACCESS_READ(log_c_rcfiles[i].name))
			{
				continue;
			}
			if (SD_STAT_CTIME(log_c_rcfiles[i].name,&log_c_rcfiles[i].ctime) != 0)
			{
				sd_error("sd_stat_ctime %s failed", log_c_rcfiles[i].name);
			}
			log_c_rcfiles[i].exists=1;
			bCfgFileExist = TRUE;

#if 0
			if (log4c_load(log_c_rcfiles[i].name) == -1)
			{
				sd_error("loading %s failed", log_c_rcfiles[i].name);
				iReturn = -1;
			}
			else
			{
				printf("loading %s succeeded\n", log_c_rcfiles[i].name);
				break;
			}
#endif

		}


		if (TRUE == bCfgFileExist)
		{
			printf("find configuration file\n");
		}
		else
		{
			printf("can't find configuration file,\nplease put you conf file in the same dir of execute file.\n");
		}

		return iReturn;
	}

	/**检测配置文件是否存在,只检测传入的配置文件名
	@return const int : iPriority.
	作者:温辉敏  日期:2008-9-4
	*/
	const int log_check_with_cfg_file(const char *strCfgFileName)
	{ 
		int iReturn = 0;
		BOOL bCfgFileExist = FALSE;
		int i = 0;

		printf("check configuration files...\n");

		/* check configuration files */		
		printf("looking for conf files...\n");

#if 1
		snprintf(log_c_rcfiles[0].name, sizeof(log_c_rcfiles[0].name) - 1, "%s/log4crc", 
			getenv("LOG4C_RCPATH") ? getenv("LOG4C_RCPATH") : LOG4C_RCPATH);
		snprintf(log_c_rcfiles[1].name, sizeof(log_c_rcfiles[1].name) - 1, "%s/.log4crc",
			getenv("HOME") ? getenv("HOME") : "");
#endif

		if(NULL == strCfgFileName)
		{
			iReturn = -1;
		}
		else
		{
			printf("checking for conf file at '%s'\n", strCfgFileName);
			if (SD_ACCESS_READ(strCfgFileName))
			{
				iReturn = -1;
			}
			else
			{
				if (SD_STAT_CTIME(strCfgFileName,&log_c_rcfiles[i].ctime) != 0)
				{
					sd_error("sd_stat_ctime %s failed", strCfgFileName);
				}

				bCfgFileExist = TRUE;
#if 0
				if (log4c_load(strCfgFileName) == -1)
				{
					sd_error("loading %s failed", strCfgFileName);
					iReturn = -1;
				}
				else
				{
					printf("loading %s succeeded\n", strCfgFileName);
				}
#endif
			}		
		}

		if (TRUE == bCfgFileExist)
		{
			printf("find configuration file\n");
		}
		else
		{
			printf("can't find configuration file,\nplease put you conf file in the same dir of execute file.\n");
		}

		return iReturn;
	}

	/** 日志记录
	日志记录为一个字符串指针指向的内容
	@return void
	作者:温辉敏  日期:2008-2-3
	*/
	void log_msg(
		const char *strFile,	///文件名
		const int iLineNum,		///行号
		const char *strCatName,	///category名
		const int iPriority,	///日志记录级别
		const char *strFormat,	///日志内容格式
		...						///日志内容
		)
	{
		const log4c_category_t* a_category = log4c_category_get(strCatName);
		if (log4c_category_is_priority_enabled(a_category, iPriority)) 
		{		
			va_list va;
			va_start(va, strFormat);

			///下面从带路径的文件名解析出不带路径的纯文件名
			{
				///static SEM_ID semphore = NULL;
				const char * strFilePath = strFile;
				const char * strFileName = strrchr(strFilePath, '/');
				char strMsgBuffer[LOG4C_BUFFER_SIZE_MAX] = {0};

				///为线程安全这里加锁，[2/15/2008 温辉敏]
				if (NULL == gs_semphore)
				{
					gs_semphore = VOS_CreateMSem(VOS_SEM_Q_FIFO);
				}
				VOS_TakeSem(gs_semphore, VOS_WAIT_FOREVER);

				if (strFileName != NULL)
				{
					strFileName++;
				}
				else
				{
					strFileName = strrchr(strFilePath, '\\');
					if (strFileName != NULL)
					{
						strFileName++;
					}
					else
					{
						strFileName = strFilePath;
					}
				}

				snprintf(strMsgBuffer, sizeof(strMsgBuffer)-1, "%-8s(%d) %s\n", strFileName, iLineNum, strFormat);
				log4c_category_vlog(a_category, iPriority, strMsgBuffer, va);

				// 解锁 [2/15/2008 温辉敏]
				VOS_GiveSem(gs_semphore);
			}

			va_end(va);		
		}
	}


	/** 日志记录,不记录文件名和行号
	日志记录为一个字符串指针指向的内容
	@return void
	作者:温辉敏  日期:2008-2-3
	*/
	void log_msg_no_file_num(
		const char *strCatName,	///category名
		const int iPriority,		///日志记录级别
		const char *strFormat,		///日志内容格式
		...						///日志内容
		)
	{
		const log4c_category_t* a_category = log4c_category_get(strCatName);
		if (log4c_category_is_priority_enabled(a_category, iPriority)) 
		{		
			va_list va;
			va_start(va, strFormat);

			{
				///static SEM_ID semphore = NULL;
				char strMsgBuffer[1024] = {0};

				///为线程安全这里加锁，[2/15/2008 温辉敏]
				if (NULL == gs_semphore)
				{
					gs_semphore = VOS_CreateMSem(VOS_SEM_Q_FIFO);
				}
				VOS_TakeSem(gs_semphore, VOS_WAIT_FOREVER);			

				snprintf(strMsgBuffer, sizeof(strMsgBuffer)-1, "%s\n",  strFormat);
				log4c_category_vlog(a_category, iPriority, strMsgBuffer, va);

				// 解锁 [2/15/2008 温辉敏]
				VOS_GiveSem(gs_semphore);
			}

			va_end(va);		
		}
	}


	/** 日志记录,不记录文件名和行号,没有任何layout转换，直接输出相应的字符文本到日志中
	此条记录没有行号，也没有线程号，也没有回车等
	日志记录为一个字符串指针指向的内容
	@return void
	作者:温辉敏  日期:2008-9-14
	*/
	void log_msg_no_file_num_no_layout(
		const char *strCatName,	///category名
		const int iPriority,		///日志记录级别
		const char *strFormat,		///日志内容格式
		...						///日志内容
		)
	{
		const log4c_category_t* a_category = log4c_category_get(strCatName);
		if (log4c_category_is_priority_enabled(a_category, iPriority)) 
		{		
			va_list va;
			va_start(va, strFormat);

			{
				///static SEM_ID semphore = NULL;
				char strMsgBuffer[1024] = {0};

				///为线程安全这里加锁，[2/15/2008 温辉敏]
				if (NULL == gs_semphore)
				{
					gs_semphore = VOS_CreateMSem(VOS_SEM_Q_FIFO);
				}
				VOS_TakeSem(gs_semphore, VOS_WAIT_FOREVER);			

				snprintf(strMsgBuffer, sizeof(strMsgBuffer)-1, "%s",  strFormat);
				log4c_category_vlog_no_file_num_no_layout(a_category, iPriority, strMsgBuffer, va);

				// 解锁 [2/15/2008 温辉敏]
				VOS_GiveSem(gs_semphore);
			}

			va_end(va);		
		}
	}

	/** 设置appender
	@return int:
	作者:温辉敏  日期:2008-2-3
	*/
	int log_setappender(
		const char *strCatName,		///category名
		const char *strAppenderName ///appender名
		)
	{
		log4c_category_set_appender(log4c_category_get(strCatName), log4c_appender_get(strAppenderName));
		return(0);                     
	}

	/** 日志记录
	支持类似printf函数的带格式输出
	@return void
	作者:温辉敏  日期:2008-2-3
	*/
	void log_log(
		const char *strCatName,	///category名
		const int iPriority,	///日志记录级别
		const char* strFormat,	///日志内容格式
		...						///日志内容
		)
	{
		const log4c_category_t* a_category = log4c_category_get(strCatName);
		if (log4c_category_is_priority_enabled(a_category, iPriority)) 
		{
			va_list va;
			va_start(va, strFormat);
			log4c_category_vlog(a_category, iPriority, strFormat, va);
			va_end(va);
		}
	}


#if 0
	/** 日志记录Wrapper函数
	日志记录为一个字符串指针指向的内容
	@return int:return 0 for success 
	作者:温辉敏  日期:2008-2-4
	*/
	void log_msg_wrapper (
		const int iPriority,	///日志记录级别
		const char *strFormat,	///日志内容格式
		...						///日志内容
		)
	{
		const log4c_category_t* a_category = log4c_category_get(DEFAULT_LOG_CATEGORY_NAME);

		///log_msg(__FILE__, __LINE__, DEFAULT_LOG_CATEGORY_NAME, iPriority, strFormat);
		if (log4c_category_is_priority_enabled(a_category, iPriority)) 
		{
			char strMsg[1024] = {0};
			va_list va;
			va_start(va, strFormat);
			{			
				int iSprintSize = 0;
				iSprintSize = vsnprintf(strMsg, sizeof(strMsg), strFormat, va);
				if ( iSprintSize >= sizeof(strMsg))
				{
					sd_error("truncating message of %d bytes (bufsize = %d)", iSprintSize, sizeof(strMsg));
				}
			}
			va_end(va);

			log4c_category_vlog(a_category, iPriority, strMsg, va);		
		}	
	}
#endif

	const struct ST_LogParam log_vsnprintf_wrapper(
		const int iPriority,	///日志记录级别
		const char* strFormat,	///日志内容格式
		...						///日志内容
		)
	{
		struct ST_LogParam st_LogParam = {0};
		va_list va;
		va_start(va, strFormat);
		{	
			st_LogParam.strMsg = sd_vsprintf( strFormat, va);		
		}
		va_end(va);

		st_LogParam.iPriority = iPriority;
		return st_LogParam;
	}

/*by liigo*/
LOG4C_API const struct ST_LogParam log_category_vsnprintf_wrapper(
	const char* category,	///category名
	const int iPriority,	///日志记录级别
	const char* strFormat,	///日志内容格式
	...						///日志内容
	)
{
	struct ST_LogParam st_LogParam = {0};
	va_list va;
	va_start(va, strFormat);
	{	
		st_LogParam.strMsg = sd_vsprintf( strFormat, va);		
	}
	va_end(va);

	st_LogParam.strCategory = category;
	st_LogParam.iPriority = iPriority;
	return st_LogParam;
}

const struct ST_LogParam log_condition_vsnprintf_wrapper(
	const int iCondition,	///条件
	const int iPriority,	///日志记录级别
	const char* strFormat,	///日志内容格式
	...						///日志内容
	)
{
	struct ST_LogParam st_LogParam = {0};
	va_list va;
	va_start(va, strFormat);
	{	
		st_LogParam.strMsg = sd_vsprintf( strFormat, va);		
	}
	va_end(va);

	st_LogParam.iPriority = iPriority;
	st_LogParam.iCondition = iCondition;

	return st_LogParam;
}

const struct ST_LogParam log_hex_dump_vsnprintf_wrapper(
	const int iPriority,	///日志记录级别
	const char* strHexBuf,	///缓冲区首地址
	const int iHexBufLen,	///缓冲区长度
	...						///日志内容
	)
{
	struct ST_LogParam st_LogParam = {0};

	st_LogParam.iPriority = iPriority;
	st_LogParam.strHexBuf = (char *)strHexBuf;
	st_LogParam.iHexBufLen = iHexBufLen;

	return st_LogParam;
}

const struct ST_LogParam log_vsnprintf_wrapper_msg(
	const char* strFormat,	///日志内容格式
	...						///日志内容
	)
{
	struct ST_LogParam st_LogParam = {0};
	va_list va;
	va_start(va, strFormat);
	{	
		st_LogParam.strMsg = sd_vsprintf( strFormat, va);		
	}
	va_end(va);
	return st_LogParam;
}

const char * log_vsnprintf_wrapper_fun_msg(
	const char* strFunName,	///函数名
	const char* strFormat,	///日志内容格式
	...						///日志内容
	)
{
	char *ptrStrMsg = NULL;
	char *ptrStrMsg2 = NULL;

	struct ST_LogParam st_LogParam = {0};
	va_list va;
	va_start(va, strFormat);
	{	
		ptrStrMsg = sd_vsprintf( strFormat, va);
	}
	va_end(va);
	
	ptrStrMsg2 = sd_sprintf("FUN<%s>:%s", strFunName, ptrStrMsg);

	free(ptrStrMsg);

	return ptrStrMsg2;
}

	void log_msg_wrapper(
		const char *strFileName,///文件名
		const int iLineNum,		///行号
		const char *strCatName,	///category名
		const int iPriority,	///日志记录级别
		const char *strFormat,	///日志内容格式
		...						///日志内容
		)
	{
		const log4c_category_t* a_category = log4c_category_get(strCatName);
		if (log4c_category_is_priority_enabled(a_category, iPriority)) 
		{
			va_list va;
			va_start(va, strFormat);
			log4c_category_vlog(a_category, iPriority, strFormat, va);
			va_end(va);
		}	
	}


	/**宏参数抽取format函数
	本函数接受LOG_DEBUG(X)的参数，并从该宏定义的参数中返回format的值
	@return const char* : strFormat
	作者:温辉敏  日期:2008-2-4
	*/
	const char* log_get_format_wrapper(
		const int iPriority,	///日志记录级别
		const char* strFormat,	///日志内容格式
		...						///日志内容
		)
	{
		return strFormat;
#if 0
		char* buffer  = strdup(strFormat);
		return buffer;
#endif
	}

	/**宏参数抽取priority函数
	本函数接受LOG_DEBUG(X)的参数，并从该宏定义的参数中返回priority的值
	@return const int : iPriority.
	作者:温辉敏  日期:2008-2-4
	*/
	const int log_get_priority_wrapper(
		const int iPriority,	///日志记录级别
		const char* strFormat,	///日志内容格式
		...						///日志内容
		)
	{
		return iPriority;
	}

void _x_strncat(char* buffer, unsigned int buffsize, const char* str)
{
	strcat(buffer, str); //FIXME(liigo)
}

void _x_strncpy(char* buffer, unsigned int buffsize, const char* str)
{
	strcpy(buffer, str); //FIXME(liigo)
}

/**
将大小为count的缓冲区中内容按字节以16进制字符串打印出来,
返回值即为指向相应的字符串，
该返回指向的存储区域要调用本函数的用户显示的进行删除
*/
char * log4c_sprintf_data(char *buff, int count)
{
	int i,j,c;
	int printnext=1;
	char str[10] = {0};///由于这里要进行格式输出如"%.4x "等，这里给出10个字符作为格式输出冗余
	char *strBuffer = (char *)malloc(LOG4C_BUFFER_SIZE_MAX);
	memset(strBuffer, 0, LOG4C_BUFFER_SIZE_MAX);
	
	if(count)
	{
		if(count%16)
		{
			c=count+(16-count%16);
		}
		else 
		{
			c=count;
		}
	}
	else
	{
		c=count;
	}

	for(i=0;i<c;i++)
	{
		if(printnext) 
		{ 
			printnext--; 
#ifdef WIN32
			_snprintf(str, sizeof(str), "%.4x ",i&0xffff);
			_x_strncat(strBuffer, LOG4C_BUFFER_SIZE_MAX, str);
#else
			snprintf(str, sizeof(str), "%.4x ",i&0xffff);
			strncat(strBuffer, str, LOG4C_BUFFER_SIZE_MAX);
#endif
			///ostr << str;
		}

		if(i<count)
		{
#ifdef WIN32
			_snprintf(str, sizeof(str),"%3.2x",buff[i]&0xff);
			_x_strncat(strBuffer, LOG4C_BUFFER_SIZE_MAX, str);
#else
			snprintf(str, sizeof(str),"%3.2x",buff[i]&0xff);
			strncat(strBuffer, str, LOG4C_BUFFER_SIZE_MAX);
#endif
			///ostr << str;
		}
		else
		{
#ifdef WIN32
			_snprintf(str, sizeof(str), "   ");
			_x_strncat(strBuffer, LOG4C_BUFFER_SIZE_MAX, str);
#else
			snprintf(str, sizeof(str), "   ");
			strncat(strBuffer, str, LOG4C_BUFFER_SIZE_MAX);
#endif
			///ostr << str;
		}

		if(!((i+1)%8))
		{
			if((i+1)%16)
			{
#ifdef WIN32
				_snprintf(str,  sizeof(str), " -");
				_x_strncat(strBuffer, LOG4C_BUFFER_SIZE_MAX, str);
#else
				snprintf(str,  sizeof(str), " -");
				strncat(strBuffer, str, LOG4C_BUFFER_SIZE_MAX);
#endif
				///ostr << str;
			}
			else
			{
#ifdef WIN32
				_snprintf(str, sizeof(str), "   ");
				_x_strncat(strBuffer, LOG4C_BUFFER_SIZE_MAX, str);
#else
				snprintf(str, sizeof(str), "   ");
				strncat(strBuffer, str, LOG4C_BUFFER_SIZE_MAX);
#endif
				///ostr << str;
				for(j=i-15;j<=i;j++)
				{
					if(j<count) 
					{
						if( (buff[j]&0xff) >= 0x20 && 
							(buff[j]&0xff)<=0x7e)
						{
#ifdef WIN32
							_snprintf(str, sizeof(str), "%c",buff[j]&0xff);
							_x_strncat(strBuffer, LOG4C_BUFFER_SIZE_MAX, str);
#else
							snprintf(str, sizeof(str), "%c",buff[j]&0xff);
							strncat(strBuffer, str, LOG4C_BUFFER_SIZE_MAX);
#endif
							///ostr << str;
						}
						else 
						{
#ifdef WIN32
							_snprintf(str, sizeof(str), ".");
							_x_strncat(strBuffer, LOG4C_BUFFER_SIZE_MAX, str);
#else
							snprintf(str, sizeof(str), ".");
							strncat(strBuffer, str, LOG4C_BUFFER_SIZE_MAX);
#endif
							///ostr << str;
						}
					} 
					else 
					{
#ifdef WIN32
						_snprintf(str, sizeof(str), " ");
						_x_strncat(strBuffer, LOG4C_BUFFER_SIZE_MAX, str);
#else
						snprintf(str, sizeof(str), " ");
						strncat(strBuffer, str, LOG4C_BUFFER_SIZE_MAX);
#endif
						///ostr << str;
					}
				}
#ifdef WIN32
				_snprintf(str, sizeof(str), "\n"); 
				_x_strncat(strBuffer, LOG4C_BUFFER_SIZE_MAX, str); 
#else
				snprintf(str, sizeof(str), "\n"); 
				strncat(strBuffer, str, LOG4C_BUFFER_SIZE_MAX); 
#endif
				///ostr << str; 
				printnext=1;      
			}
		}
	}

	return strBuffer;
}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	static char gs_strFileContent_InC[] = 
		"<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
		"<!DOCTYPE log4c SYSTEM \"\">\n"
		"\n"
		"<log4c version=\"1.2.1\">\n"
		"	<config>\n"
		"		<bufsize>0</bufsize>\n"
		"		<debug level=\"2\"/>\n"
		"		<nocleanup>0</nocleanup>\n"
		"		<reread>1</reread>\n"
		"	</config>\n"
		"\n"
		"	<category name=\"root\" priority=\"notice\"  appender=\"aname\"/>\n"
		"\n"
		"	<rollingpolicy name=\"a_policy_name\" type=\"sizewin\" maxsize=\"1048576\" maxnum=\"15\" />\n"
		"	<appender name=\"aname\" type=\"rollingfile\"  logdir=\".\" prefix=\"log\" layout=\"dated_threadid\" rollingpolicy=\"a_policy_name\" />\n"
		"\n"
		"	<appender name=\"stdout\" type=\"stream\" layout=\"dated_threadid\"/>\n"
		"	<appender name=\"stderr\" type=\"stream\" layout=\"dated\"/>\n"
		"	<appender name=\"syslog\" type=\"syslog\" layout=\"basic\"/>\n"
		"</log4c>\n";

	static char gs_strDefualtFileName[] = "log4crc";

	int log_init_with_string(
		const char *strFileContent,
		const char *strFileName 
		)
	{
		int iResult = LOG4C_FAILURE;
		const char * strLocalFileContent = NULL;
		const char * strLocalFileName = NULL;

		PAssertNotNull_ReturnWithValue(strFileContent, LOG4C_FAILURE);
		PAssertNotNull_ReturnWithValue(strFileName, LOG4C_FAILURE);

		strLocalFileContent = (strlen(strFileContent) > 0 ? strFileContent:gs_strFileContent_InC);
		strLocalFileName = (strlen(strFileName) > 0 ? strFileName:gs_strDefualtFileName);

		/**
		若文件已存在则不重新生成配置文件了
		否则生成新的配置文件
		*/
		if (LOG4C_OK != SD_ACCESS_READ(strLocalFileName))
		{
			///文件不存在新建
			FILE *file = fopen(strLocalFileName, "wb");	
			if (NULL != file)
			{
				fwrite(strLocalFileContent, 1, strlen(strLocalFileContent), file);
				fclose(file);
			}		
		}
		else
		{
			///文件存在,do nothing，使用原来的配置文件就OK了。
		}	

		//////////////////////////////////////////////////////////////////////////	
		///调用Init函数进行实际的日志模块初始化工作
		iResult = log_init_with_cfg_file_wrapper(strLocalFileName);

		return iResult;
	}

	int log_init_with_cfg_file_wrapper(const char * strConfigFile)
	{
		int iResult = LOG4C_FAILURE;

		PAssertNotNull_ReturnWithValue(strConfigFile, LOG4C_FAILURE);

		///调用log4c的函数来初始化日志
		if (strlen(strConfigFile) > 0)
		{
			iResult = log_init_with_cfg_file(strConfigFile);
		}

		if ( LOG4C_OK != iResult)
		{
			iResult = log_init();
		}

		return iResult;
	}

	/*****************************新增的一些日志模块配置属性设置类****************/
	#define MAX_FILE_NAME_LEN 512
	struct ST_LogProperty
	{
		char m_strLogCfgFileName[MAX_FILE_NAME_LEN];
		char m_strLogFileName[MAX_FILE_NAME_LEN];
		int m_iLogFileSize;
		char m_strLogLevel[128];
		int m_iLogFileNum;
		BOOL m_bReReadLogCfgFile;
	};
	typedef struct ST_LogProperty LogProperty;

	static LogProperty gs_st_LogProperty = 
	{
		"log4crc",
		"log",
		1048576,
		"notice",
		15,
		TRUE
	};

	static char gs_strFileContentFormat[] = 
		"<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
		"<!DOCTYPE log4c SYSTEM \"\">\n"
		"\n"
		"<log4c version=\"1.2.1\">\n"
		"	<config>\n"
		"		<bufsize>0</bufsize>\n"
		"		<debug level=\"2\"/>\n"
		"		<nocleanup>0</nocleanup>\n"
		"		<reread>%d</reread>\n"
		"	</config>\n"
		"\n"
		"	<category name=\"root\" priority=\"%s\"  appender=\"aname\"/>\n"
		"\n"
		"	<rollingpolicy name=\"a_policy_name\" type=\"sizewin\" maxsize=\"%d\" maxnum=\"%d\" />\n"
		"	<appender name=\"aname\" type=\"rollingfile\"  logdir=\".\" prefix=\"%s\" layout=\"dated_threadid\" rollingpolicy=\"a_policy_name\" />\n"
		"\n"
		"	<appender name=\"stdout\" type=\"stream\" layout=\"dated_threadid\"/>\n"
		"	<appender name=\"stderr\" type=\"stream\" layout=\"dated\"/>\n"
		"	<appender name=\"syslog\" type=\"syslog\" layout=\"basic\"/>\n"
		"</log4c>\n";

	static char gs_strFileContentBuffer[4096] = {0};

	void log_set_log_cfg_file_name(const char *strFileName)
	{
		PAssertNotNull_Return(strFileName);
#ifdef WIN32
		_x_strncpy(gs_st_LogProperty.m_strLogCfgFileName, sizeof(gs_st_LogProperty.m_strLogCfgFileName), strFileName);
#else
		strncpy(gs_st_LogProperty.m_strLogCfgFileName, strFileName, sizeof(gs_st_LogProperty.m_strLogCfgFileName));
#endif
	}

	void log_set_log_file_name(const char *strFileName)
	{
		PAssertNotNull_Return(strFileName);
#ifdef WIN32
		_x_strncpy(gs_st_LogProperty.m_strLogFileName, sizeof(gs_st_LogProperty.m_strLogFileName), strFileName);
#else
		strncpy(gs_st_LogProperty.m_strLogFileName, strFileName, sizeof(gs_st_LogProperty.m_strLogFileName));
#endif
	}

	void log_set_log_level(const char *strLogLevel)
	{
#ifdef WIN32
		_x_strncpy(gs_st_LogProperty.m_strLogLevel, 
			sizeof(gs_st_LogProperty.m_strLogLevel), strLogLevel);
#else
		strncpy(gs_st_LogProperty.m_strLogLevel, strLogLevel, 
			sizeof(gs_st_LogProperty.m_strLogLevel));
#endif
	}

	void log_set_log_file_size(const int iFileSize)
	{
		gs_st_LogProperty.m_iLogFileSize = iFileSize;
	}

	void log_set_log_file_num(const int iFileNum)
	{
		gs_st_LogProperty.m_iLogFileNum = iFileNum;
	}

	void log_set_reread_log_cfg_file(const BOOL bReReadLogCfgFile)
	{
		gs_st_LogProperty.m_bReReadLogCfgFile = bReReadLogCfgFile;
	}

	int log_init_with_param()
	{
#ifdef WIN32
		_snprintf(gs_strFileContentBuffer, sizeof(gs_strFileContentBuffer),
			gs_strFileContentFormat, 
			gs_st_LogProperty.m_bReReadLogCfgFile,
			gs_st_LogProperty.m_strLogLevel,
			gs_st_LogProperty.m_iLogFileSize,
			gs_st_LogProperty.m_iLogFileNum,
			gs_st_LogProperty.m_strLogFileName
			);
#else
		snprintf(gs_strFileContentBuffer, sizeof(gs_strFileContentBuffer),
			gs_strFileContentFormat, 
			gs_st_LogProperty.m_bReReadLogCfgFile,
			gs_st_LogProperty.m_strLogLevel,
			gs_st_LogProperty.m_iLogFileSize,
			gs_st_LogProperty.m_iLogFileNum,
			gs_st_LogProperty.m_strLogFileName
			);
#endif

		return log_init_with_string(gs_strFileContentBuffer, gs_st_LogProperty.m_strLogCfgFileName);
	}
	/************************************************************************/

	/************************************************************************/
	// Instruct the compiler to put the g_lModuleUsage data
	// variable in its own data section, called Shared. We
	// then instruct the linker that we want the data in this
	// section to be shared by all instances of this application.
#ifdef WIN32
#pragma data_seg("LogShared")
	/** 数据库日志模块运行的实例个数
	避免多个日志模块的运行实例使用同一个配置文件，避免使用同一个log文件来记录日志而产生冲突
	*/
	long g_lLogModuleUsage = -1;
#pragma data_seg()
	// Instruct the linker to make the Shared section 
	// readable, writable, and shared.
#pragma comment(linker, "/section:LogShared,rws")
#else 
	// long g_lLogModuleUsage __attribute__((section ("shared"), shared)) = -1;
	// int g_lLogModuleUsage __attribute__((section ("shared"), shared)) = -1;
	// extern long GetModuleUsage();
	// long g_lLogModuleUsage = GetModuleUsage();
	long g_lLogModuleUsage = -1;
#endif

	int log_init_with_param_multi_process()
	{
		char strLogCfgFileName[MAX_FILE_NAME_LEN] = {0};
		char strLogFileName[MAX_FILE_NAME_LEN] = {0};
		char strLogModuleUsageNum[MAX_FILE_NAME_LEN] = {0};

		IncreaseLogModuleUsage();
#ifdef WIN32
		_snprintf(gs_st_LogProperty.m_strLogCfgFileName, sizeof(gs_st_LogProperty.m_strLogCfgFileName), 
			"%s%d", gs_st_LogProperty.m_strLogCfgFileName, g_lLogModuleUsage);
		_snprintf(gs_st_LogProperty.m_strLogFileName, sizeof(gs_st_LogProperty.m_strLogFileName), 
			"%s%d", gs_st_LogProperty.m_strLogFileName, g_lLogModuleUsage);
#else
		//snprintf(gs_st_LogProperty.m_strLogCfgFileName, sizeof(gs_st_LogProperty.m_strLogCfgFileName), 
		//	"%s%d", gs_st_LogProperty.m_strLogCfgFileName, g_lLogModuleUsage);
		//snprintf(gs_st_LogProperty.m_strLogFileName, sizeof(gs_st_LogProperty.m_strLogFileName), 
		//	"%s%d", gs_st_LogProperty.m_strLogFileName, g_lLogModuleUsage);
		snprintf(strLogModuleUsageNum, sizeof(strLogModuleUsageNum), "%d", g_lLogModuleUsage);
		strcat(gs_st_LogProperty.m_strLogCfgFileName, strLogModuleUsageNum);
		strcat(gs_st_LogProperty.m_strLogFileName, strLogModuleUsageNum);
#endif

		return log_init_with_param();
	}
	
	extern long GetModuleUsage();
	extern void SetModuleUsage(long lModuleUsage);
	void IncreaseLogModuleUsage()
	{
#ifdef WIN32
		InterlockedIncrement((long*) &g_lLogModuleUsage);
#else
		g_lLogModuleUsage = GetModuleUsage();
		g_lLogModuleUsage ++;
		SetModuleUsage(g_lLogModuleUsage);
#endif
	}

	/************************************************************************/


	/************************************************************************/
	///下面为LOG4C_BLOCK_XXX相关宏定义的实现代码
	///进行LOG4C_BLOCK_BEGIN和LOG4C_BLOCK_END宏定义使用的Block结构
	struct ST_Block
	{
#define BLOCK_FREE 0
#define BLOCK_BUSY 1
		///标志是否被使用
		int iUseStatus;
		///线程ID
		TASK_ID threadId;
		///Block的层次
		int iBlockLevel;

		void (*Init)(struct ST_Block *ptrThis);
		void (*Reset)(struct ST_Block *ptrThis);

		int (*GetUseStatus)(struct ST_Block *ptrThis);
		TASK_ID (*GetThreadId)(struct ST_Block *ptrThis);
		int (*GetBlockLevel)(struct ST_Block *ptrThis);

		void (*SetUseStatus)(struct ST_Block *ptrThis, int iUseStatus);
		void (*SetThreadId)(struct ST_Block *ptrThis, TASK_ID threadId);
		void (*SetBlockLevel)(struct ST_Block *ptrThis, int iBlockLevel);
	};
	typedef struct ST_Block Block;

	/**一个ST_BlockGroup包含5个ST_Block
	ST_BlockGroup中作为ST_BlockManager中管理的节点
	*/
	struct ST_BlockGroup
	{
#define BLOCK_GROUP_BLOCK_NUM (5)
		Block aBlock[BLOCK_GROUP_BLOCK_NUM];
		struct ST_BlockGroup *ptrBlockGroupPre;
		struct ST_BlockGroup *ptrBlockGroupNext;

		void (*Init)(struct ST_BlockGroup *ptrThis);
		Block *(*GetThreadBlock)(struct ST_BlockGroup *ptrThis, TASK_ID threadId);
		Block *(*GetFreeBlock)(struct ST_BlockGroup *ptrThis);
	};
	typedef struct ST_BlockGroup BlockGroup;

	struct ST_BlockManager
	{	
		BlockGroup *ptrBlockGroupHeader;
		BlockGroup *ptrBlockGroupTail;

		Block *(*GetThreadBlock)(struct ST_BlockManager *ptrThis, TASK_ID threadId);
		Block *(*GetFreeBlock)(struct ST_BlockManager *ptrThis);
	};
	typedef struct ST_BlockManager BlockManager;

	extern Block *BlockManager_GetThreadBlock(BlockManager *ptrThis, TASK_ID threadId);
	extern Block *BlockManager_GetFreeBlock(BlockManager *ptrThis);

	BlockManager g_blockManager = 
	{
		NULL,
		NULL,
		BlockManager_GetThreadBlock,
		BlockManager_GetFreeBlock
	};

	extern void Block_Reset(Block *ptrThis);
	extern int Block_GetUseStatus(Block *ptrThis);
	extern TASK_ID Block_GetThreadId(Block *ptrThis);
	extern int Block_GetBlockLevel(Block *ptrThis);
	extern void Block_SetUseStatus(Block *ptrThis, int iUseStatus);
	extern void Block_SetThreadId(Block *ptrThis, TASK_ID threadId);
	extern void Block_SetBlockLevel(Block *ptrThis, int iBlockLevel);

	/**ST_Block的初始化代码
	@param :Block *ptrThis
	@rerurn void.
	*/
	void Block_Init(Block *ptrThis)
	{
		PAssert_Return(ptrThis);
		memset(ptrThis, 0, sizeof(*ptrThis));

		///设置本结构的成员函数
		ptrThis->Init = Block_Init;
		ptrThis->Reset = Block_Reset;

		ptrThis->SetBlockLevel = Block_SetBlockLevel;
		ptrThis->GetBlockLevel = Block_GetBlockLevel;
		ptrThis->SetThreadId = Block_SetThreadId;
		ptrThis->GetThreadId = Block_GetThreadId;
		ptrThis->SetUseStatus = Block_SetUseStatus;
		ptrThis->GetUseStatus = Block_GetUseStatus;
		return;
	}

	/**ST_Block的重置代码
	@param :Block *ptrThis
	@rerurn void.
	*/
	void Block_Reset(Block *ptrThis)
	{
		PAssert_Return(ptrThis);
		Block_Init(ptrThis);
		return;
	}

	/**ST_Block的获取成员变量iUseStatus的函数
	其实直接引用成员变量就可以了，这里为了练习C实现C++而特意实现的
	@param :int
	@rerurn void.
	*/
	int Block_GetUseStatus(Block *ptrThis)
	{
		PAssert_ReturnWithValue(ptrThis, 0);
		return ptrThis->iUseStatus;
	}

	/**ST_Block的获取成员变量threadId的函数
	其实直接引用成员变量就可以了，这里为了练习C实现C++而特意实现的
	@param :TASK_ID.
	@rerurn void.
	*/
	TASK_ID Block_GetThreadId(Block *ptrThis)
	{
		PAssert_ReturnWithValue(ptrThis, 0);
		return ptrThis->threadId;
	}

	/**ST_Block的获取成员变量iBlockLevel的函数
	其实直接引用成员变量就可以了，这里为了练习C实现C++而特意实现的
	@param :int.
	@rerurn void.
	*/
	int Block_GetBlockLevel(Block *ptrThis)
	{
		PAssert_ReturnWithValue(ptrThis, 0);
		return ptrThis->iBlockLevel;
	}

	/**ST_Block的设置成员变量iUseStatus的函数
	其实直接引用成员变量就可以了，这里为了练习C实现C++而特意实现的
	@param :Block *ptrThis
	@param :int
	@rerurn void.
	*/
	void Block_SetUseStatus(Block *ptrThis, int iUseStatus)
	{
		PAssert_Return(ptrThis);
		ptrThis->iUseStatus = iUseStatus;
	}

	/**ST_Block的设置成员变量threadId的函数
	其实直接引用成员变量就可以了，这里为了练习C实现C++而特意实现的
	@param :Block *ptrThis
	@param :TASK_ID.
	@rerurn void.
	*/
	void Block_SetThreadId(Block *ptrThis, TASK_ID threadId)
	{
		PAssert_Return(ptrThis);
		ptrThis->threadId = threadId;
	}

	/**ST_Block的设置成员变量iBlockLevel的函数
	其实直接引用成员变量就可以了，这里为了练习C实现C++而特意实现的
	@param :Block *ptrThis
	@param :int.
	@rerurn void.
	*/
	void Block_SetBlockLevel(Block *ptrThis, int iBlockLevel)
	{
		PAssert_Return(ptrThis);
		ptrThis->iBlockLevel = iBlockLevel;
	}

	extern Block *BlockGroup_GetThreadBlock(BlockGroup *ptrThis, TASK_ID threadId);
	extern Block *BlockGroup_GetFreeBlock(BlockGroup *ptrThis);

	/**ST_BlockGroup的初始化代码
	@param :Block *ptrThis
	@rerurn void.
	*/
	void BlockGroup_Init(BlockGroup *ptrThis)
	{
		int i = 0;
		PAssert_Return(ptrThis);
		memset(ptrThis, 0, sizeof(*ptrThis));

		ptrThis->Init = BlockGroup_Init;
		ptrThis->GetThreadBlock = BlockGroup_GetThreadBlock;
		ptrThis->GetFreeBlock = BlockGroup_GetFreeBlock;

		///初始化每个Block
		for (i = 0; i < BLOCK_GROUP_BLOCK_NUM; i++)
		{
			Block *ptrBlock = &ptrThis->aBlock[i];
			ptrBlock->Init = Block_Init;

			ptrBlock->Init(ptrBlock);
		}

		return;
	}

	/**从ST_BlockGroup中获取给定线程的Block的指针
	@param :Block *ptrThis
	@param :TASK_ID threadId
	@rerurn Block *.
	*/
	Block *BlockGroup_GetThreadBlock(BlockGroup *ptrThis, TASK_ID threadId)
	{
		Block *ptrBlockReturn = NULL;
		int i = 0;
		PAssert_ReturnWithValue(ptrThis, NULL);

		for (i = 0; i < BLOCK_GROUP_BLOCK_NUM; i++)
		{
			Block *ptrBlock = &ptrThis->aBlock[i];

			if (ptrBlock->GetThreadId(ptrBlock) == threadId)
			{
				ptrBlockReturn = ptrBlock;
				break;
			}
		}	

		return ptrBlockReturn;
	}

	/**从ST_BlockGroup中获取空闲的Block的指针
	@param :BlockGroup *ptrThis
	@rerurn Block *.
	*/
	Block *BlockGroup_GetFreeBlock(BlockGroup *ptrThis)
	{
		Block *ptrBlockReturn = NULL;
		int i = 0;
		PAssert_ReturnWithValue(ptrThis, NULL);

		for (i = 0; i < BLOCK_GROUP_BLOCK_NUM; i++)
		{
			Block *ptrBlock = &ptrThis->aBlock[i];

			if (ptrBlock->GetUseStatus(ptrBlock) == BLOCK_FREE)
			{
				ptrBlockReturn = ptrBlock;
				break;
			}
		}	

		return ptrBlockReturn;
	}

	Block *BlockManager_GetThreadBlock(BlockManager *ptrThis, TASK_ID threadId)
	{
		Block *ptrBlockReturn = NULL;
		BlockGroup *ptrBlockGroup = NULL;
		PAssert_ReturnWithValue(ptrThis, NULL);

		if (NULL == ptrThis->ptrBlockGroupHeader)
		{
			BlockGroup *ptrGroupBlock = (BlockGroup *)malloc(sizeof(BlockGroup)); 
			ptrGroupBlock->Init = BlockGroup_Init;
			ptrGroupBlock->Init(ptrGroupBlock);
			ptrThis->ptrBlockGroupHeader = ptrGroupBlock;
			ptrThis->ptrBlockGroupTail = ptrGroupBlock;
		}

		PAssert_ReturnWithValue(ptrThis->ptrBlockGroupHeader, NULL);

		ptrBlockGroup = ptrThis->ptrBlockGroupHeader;
		do 
		{
			ptrBlockReturn = ptrBlockGroup->GetThreadBlock(ptrBlockGroup, threadId);
			if (NULL != ptrBlockReturn)
			{
				break;
			}
			else
			{
				ptrBlockGroup = ptrBlockGroup->ptrBlockGroupNext;
			}
		} while (NULL != ptrBlockGroup);

		///此时找遍所有的链表都没有找到相应的Block，则重新找块没用的Block
		if (NULL == ptrBlockReturn)
		{
			ptrBlockReturn = ptrThis->GetFreeBlock(ptrThis);
		}

		return ptrBlockReturn;
	}

	Block *BlockManager_GetFreeBlock(BlockManager *ptrThis)
	{
		Block *ptrBlockReturn = NULL;
		PAssert_ReturnWithValue(ptrThis, NULL);

		if(NULL == ptrThis->ptrBlockGroupHeader)
		{
			///原来没有空间则动态分配
			BlockGroup *ptrGroupBlock = (BlockGroup *)malloc(sizeof(BlockGroup)); 
			ptrGroupBlock->Init = BlockGroup_Init;
			ptrGroupBlock->Init(ptrGroupBlock);
			ptrThis->ptrBlockGroupHeader = ptrGroupBlock;
			ptrThis->ptrBlockGroupTail = ptrGroupBlock;

			ptrBlockReturn = ptrGroupBlock->GetFreeBlock(ptrGroupBlock);
		}
		else
		{
			BlockGroup *ptrBlockGroup = ptrThis->ptrBlockGroupHeader;
			do 
			{
				ptrBlockReturn = ptrBlockGroup->GetFreeBlock(ptrBlockGroup);
				if (NULL != ptrBlockReturn)
				{
					break;
				}
				else
				{
					ptrBlockGroup = ptrBlockGroup->ptrBlockGroupNext;
				}
			} while (NULL != ptrBlockGroup);

			///此时找遍所有的链表都没有找到空闲空间,则进行动态分配
			if(NULL == ptrBlockReturn)
			{
				BlockGroup *ptrBlockGroup = (BlockGroup *)malloc(sizeof(BlockGroup)); 
				ptrBlockGroup->Init = BlockGroup_Init;
				ptrBlockGroup->Init(ptrBlockGroup);

				ptrThis->ptrBlockGroupTail->ptrBlockGroupNext = ptrBlockGroup;
				ptrBlockGroup->ptrBlockGroupPre = ptrThis->ptrBlockGroupTail;
				ptrThis->ptrBlockGroupTail = ptrBlockGroup;

				ptrBlockReturn = ptrBlockGroup->GetFreeBlock(ptrBlockGroup);
			}
		}

		return ptrBlockReturn;
	}

	void log4c_block_begin(const char * fileName, int lineNum, const char * traceName)
	{
		TASK_ID threadId = VOS_GetSelfTaskID();
		int i = 0;
		Block *ptrBlock = NULL;
		PAssert_Return(fileName);
		PAssert_Return(traceName);

		ptrBlock = g_blockManager.GetThreadBlock(&g_blockManager, threadId);
		if (NULL != ptrBlock)
		{
			int iBlockLevel = 0;
			char strMsgBuffer[LOG4C_BUFFER_SIZE_MAX] = {0};

			if (ptrBlock->GetUseStatus(ptrBlock) == BLOCK_FREE)
			{
				ptrBlock->SetUseStatus(ptrBlock, BLOCK_BUSY);
				ptrBlock->SetThreadId(ptrBlock, threadId);
				ptrBlock->SetBlockLevel(ptrBlock, 0);
			}

			if (ptrBlock->GetThreadId(ptrBlock) != threadId)
			{
				ptrBlock->SetThreadId(ptrBlock, threadId);
				ptrBlock->SetBlockLevel(ptrBlock, 0);
			}

			///ptrBlock->SetThreadId(ptrBlock, threadId);
			///ptrBlock->SetBlockLevel(ptrBlock, 0);

			iBlockLevel = ++(ptrBlock->iBlockLevel) ;
#ifdef WIN32
			_x_strncat(strMsgBuffer, sizeof(strMsgBuffer), "B-Entry\t");
			for (i = 0; i < iBlockLevel; i++)
			{
				_x_strncat(strMsgBuffer, sizeof(strMsgBuffer), "==");
			}
			_x_strncat(strMsgBuffer, sizeof(strMsgBuffer), "> ");
			_x_strncat(strMsgBuffer, sizeof(strMsgBuffer), traceName);
#else
			strncat(strMsgBuffer, "B-Entry\t", sizeof(strMsgBuffer));
			for (i = 0; i < iBlockLevel; i++)
			{
				strncat(strMsgBuffer, "==", sizeof(strMsgBuffer));
			}
			strncat(strMsgBuffer, "> ", sizeof(strMsgBuffer));
			strncat(strMsgBuffer, traceName, sizeof(strMsgBuffer));
#endif

			///调用log4c的函数来记录日志
			log_msg(fileName, lineNum, "", LOG4C_PRIORITY_TRACE, strMsgBuffer);
		}
	}

	void log4c_block_end(const char * fileName, int lineNum, const char * traceName)
	{
		TASK_ID threadId = VOS_GetSelfTaskID();
		int i = 0;
		Block *ptrBlock = NULL;
		PAssert_Return(fileName);
		PAssert_Return(traceName);

		ptrBlock = g_blockManager.GetThreadBlock(&g_blockManager, threadId);
		if (NULL != ptrBlock)
		{
			int iBlockLevel = ptrBlock->GetBlockLevel(ptrBlock);
			char strMsgBuffer[LOG4C_BUFFER_SIZE_MAX] = {0};

#ifdef WIN32
			_x_strncat(strMsgBuffer, sizeof(strMsgBuffer), "B-Exit\t");
			_x_strncat(strMsgBuffer, sizeof(strMsgBuffer), "<");
			for (i = 0; i < iBlockLevel; i++)
			{
				_x_strncat(strMsgBuffer, sizeof(strMsgBuffer), "==");
			}
			_x_strncat(strMsgBuffer, sizeof(strMsgBuffer), " ");
			_x_strncat(strMsgBuffer, sizeof(strMsgBuffer), traceName);
#else
			strncat(strMsgBuffer, "B-Exit\t", sizeof(strMsgBuffer));
			strncat(strMsgBuffer, "<", sizeof(strMsgBuffer));
			for (i = 0; i < iBlockLevel; i++)
			{
				strncat(strMsgBuffer, "==", sizeof(strMsgBuffer));
			}
			strncat(strMsgBuffer, " ", sizeof(strMsgBuffer));
			strncat(strMsgBuffer, traceName, sizeof(strMsgBuffer));
#endif
			///调用log4c的函数来记录日志
			log_msg(fileName, lineNum, "", LOG4C_PRIORITY_TRACE, strMsgBuffer);

			iBlockLevel = --ptrBlock->iBlockLevel ;
			if (ptrBlock->iBlockLevel == 0)
			{
				ptrBlock->SetThreadId(ptrBlock, 0);
				ptrBlock->SetBlockLevel(ptrBlock, 0);
				ptrBlock->SetUseStatus(ptrBlock, BLOCK_FREE);
			}
		}
	}
	/************************************************************************/
/************** End of log.c *******************************************/

/************** Begin of logging_event.c *******************************************/
	///static const char version[] = "$Id$";

	/*
	* logging_event.c
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

///#include <log4c/logging_event.h>
///#include <log4c/category.h>
#include <stdlib.h>
///#include <sd/malloc.h>
///#include <sd/sd_xplatform.h>

	/*******************************************************************************/
	extern log4c_logging_event_t* log4c_logging_event_new(
		const char* a_category,
		int		a_priority,
		const char*	a_message)
	{
		log4c_logging_event_t* evt;

		evt 		= (log4c_logging_event_t*)sd_calloc(1, sizeof(log4c_logging_event_t));    
		evt->evt_category	= a_category;
		evt->evt_priority	= a_priority;
		evt->evt_msg	= a_message;

		SD_GETTIMEOFDAY(&evt->evt_timestamp, NULL);

		return evt;
	}

	/*******************************************************************************/
	extern void log4c_logging_event_delete(log4c_logging_event_t* ptrThis)
	{
		if (!ptrThis)
			return;

		free(ptrThis);
	}


/************** End of logging_event.c *******************************************/


/************** Begin of priority.c *******************************************/
	///static const char version[] = "$Id$";

	/*
	* priority.c
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

#include <string.h>
///#include <log4c/priority.h>
///#include <sd/sd_xplatform.h>

	static const char* const priorities[] = {
		"FATAL", 
		"ALERT",
		"CRIT",
		"ERROR",
		"WARN",
		"NOTICE",
		"INFO",
		"DEBUG",
		"TRACE",
		"NOTSET",
		"UNKNOWN"
	};

	static const size_t npriorities = sizeof(priorities) / sizeof(priorities[0]);

	/*******************************************************************************/
	extern const char* log4c_priority_to_string(int a_priority)
	{
		a_priority /= 100;
		if ( (a_priority < 0) || (a_priority > 10) ) 
			a_priority = 10;

		return priorities[a_priority];
	}    

	/*******************************************************************************/
	extern int log4c_priority_to_int(const char* a_priority_name)
	{
		size_t i; 

		if (a_priority_name) {
			for (i = 0; i < npriorities; i++) {
				if (!_x_strncasecmp(priorities[i], a_priority_name, strlen(priorities[i])))
					return i * 100;
			}
		}

		return LOG4C_PRIORITY_UNKNOWN;
	}    


/************** End of priority.c *******************************************/

	/************** Begin of sd/domnode.h *******************************************/

	/* $Id$
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	* See the COPYING file for the terms of usage and distribution.
	*/

#ifndef __sd_domnode_h
#define __sd_domnode_h

	/**
	* @file domnode.h @ingroup sd
	*
	* @brief Generic DOM object.
	*/

#include <stdio.h>
///#include <sd/list.h>

	__SD_BEGIN_DECLS

		typedef struct {
			const char*	name;
			const char*	value;
			sd_list_t*	children;
			sd_list_t*	attrs;
	} sd_domnode_t;

	extern sd_domnode_t*	sd_domnode_new(const char* a_name,
		const char* a_value);

	extern void		sd_domnode_delete(sd_domnode_t* ptrThis);

	extern int		sd_domnode_read(sd_domnode_t* ptrThis,
		const char* a_buffer, size_t asize);
	extern int		sd_domnode_write(sd_domnode_t* ptrThis, char** a_buffer,
		size_t* asize);

	extern int		sd_domnode_fread(sd_domnode_t* ptrThis, FILE* a_stream);
	extern int		sd_domnode_fwrite(const sd_domnode_t* ptrThis,
		FILE* a_stream);

	extern int		sd_domnode_load(sd_domnode_t* ptrThis,
		const char* a_filename);

	extern int		sd_domnode_store(const sd_domnode_t* ptrThis, 
		const char* a_filename);

	extern sd_domnode_t*	sd_domnode_search(const sd_domnode_t* ptrThis,
		const char* a_name);

	extern sd_domnode_t* 	sd_domnode_attrs_put(sd_domnode_t* ptrThis,
		sd_domnode_t* a_attr);
	extern sd_domnode_t*	sd_domnode_attrs_get(const sd_domnode_t* ptrThis,
		const char* a_name);
	extern sd_domnode_t*	sd_domnode_attrs_remove(sd_domnode_t* ptrThis,
		const char* a_name);

	/** Creates a new node. */
	extern sd_domnode_t* __sd_domnode_new(const char* name, const char* a_value,
		int is_elem);

	__SD_END_DECLS

#endif


		/************** End of sd/domnode.h *******************************************/

/************** Begin of rc.c *******************************************/
	///static const char version[] = "$Id$";

	/*
	* rc.c
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

#ifdef HAVE_CONFIG_H
///#include "config.h"
#endif

///#include <log4c/rc.h>
///#include <log4c/category.h>
///#include <log4c/appender.h>
///#include <log4c/layout.h>
///#include <log4c/appender_type_rollingfile.h>
///#include <log4c/rollingpolicy.h>
///#include <log4c/rollingpolicy_type_sizewin.h>
///#include <sd/error.h>
///#include <sd/domnode.h>
///#include <sd/malloc.h>
///#include <sd/sd_xplatform.h>
///#include <sd/factory.h>
#include <stdlib.h>
#include <string.h>


	static log4c_rc_t __log4c_rc = { { 0, 0, 0, 0 } };

	log4c_rc_t* const log4c_rc = &__log4c_rc;

	/******************************************************************************/
	static long parse_byte_size (const char *astring)
	{
		/* Parse size in bytes depending on the suffix.   Valid suffixes are KB, MB and GB */
		size_t sz = strlen (astring);
		long res = strtol(astring, (char **) NULL, 10);

		if (res <= 0)
			return 0;

		if (astring[ sz - 1 ] == 'B') {
			switch (astring[ sz - 2 ]) {
		case 'K':
			res *= 1024;
			break;
		case 'M':
			res *= 1024 * 1024;
			break;
		case 'G':
			res *= 1024 * 1024 * 1024;
			break;
		default:
			sd_debug("Wrong suffix parsing size in bytes for string %s, ignoring suffix", 
				astring);
			}
		}
		sd_debug("Parsed size parameter %s to value %ld",astring, res);
		return (res);
	}

	/******************************************************************************/
	static int config_load(log4c_rc_t* ptrThis, sd_domnode_t* anode)
	{
		sd_list_iter_t* i = NULL;

		for (i = sd_list_begin(anode->children); i != sd_list_end(anode->children); 
			i = sd_list_iter_next(i)) 
		{
			sd_domnode_t* node = (sd_domnode_t*)i->data;

			if (!strcmp(node->name, "nocleanup")) {
				ptrThis->config.nocleanup = atoi(node->value);
				if (ptrThis->config.nocleanup)
					sd_debug("deactivating log4c cleanup");		
			}

			if (!strcmp(node->name, "bufsize")) {	    
				ptrThis->config.bufsize = parse_byte_size(node->value);

				if (ptrThis->config.bufsize)
					sd_debug("using fixed buffer size of %d bytes", 
					ptrThis->config.bufsize);
				else
					sd_debug("using dynamic allocated buffer");
			}

			if (!strcmp(node->name, "debug")) {
				sd_domnode_t* level = sd_domnode_attrs_get(node, "level");

				if (level) {
					ptrThis->config.debug = atoi(level->value);
					sd_debug("activating log4c debugging. level = %d", ptrThis->config.debug);
				}
			}
			if (!strcmp(node->name, "reread")) {
				ptrThis->config.reread = atoi(node->value);
				sd_debug("log4crc reread is %d",ptrThis->config.reread);
				if (0 == ptrThis->config.reread)
					sd_debug("deactivating log4crc reread");
			}
		}

		return 0;
	}

	/******************************************************************************/
	static int category_load(log4c_rc_t* ptrThis, sd_domnode_t* anode)
	{
		sd_domnode_t*     name     = sd_domnode_attrs_get(anode, "name");
		sd_domnode_t*     priority = sd_domnode_attrs_get(anode, "priority");
		sd_domnode_t*     additivity = sd_domnode_attrs_get(anode, "additivity");
		sd_domnode_t*     appender = sd_domnode_attrs_get(anode, "appender");
		log4c_category_t* cat      = NULL;

		if (!name) {
			sd_error("attribute \"name\" is missing");
			return -1;
		}

		cat = log4c_category_get(name->value);

		if (priority)
			log4c_category_set_priority(
			cat, log4c_priority_to_int(priority->value));

		if (additivity) {
			if (!_x_strcasecmp(additivity->value, "false")) {
				log4c_category_set_additivity(cat, 0);
			} else if (!_x_strcasecmp(additivity->value, "true")) {
				log4c_category_set_additivity(cat, 1);
			} else {
				sd_error("additivity value is invalid : %s", additivity->value);
			}
		}

		if (appender)
			log4c_category_set_appender(
			cat, log4c_appender_get(appender->value));

		return 0;
	}

	/******************************************************************************/
	static int appender_load(log4c_rc_t* ptrThis, sd_domnode_t* anode)
	{
		sd_domnode_t*     name   = sd_domnode_attrs_get(anode, "name");
		sd_domnode_t*     type   = sd_domnode_attrs_get(anode, "type");
		sd_domnode_t*     layout = sd_domnode_attrs_get(anode, "layout");
		log4c_appender_t* app    = NULL;

		if (!name) {
			sd_error("attribute \"name\" is missing");
			return -1;
		}

		sd_debug("appender_load[name='%s'", 
			(name->value ? name->value :"(not set)"));

		app = log4c_appender_get(name->value);

		if (type){
			sd_debug("appender type is '%s'",
				(type->value ? type->value: "(not set)"));
			log4c_appender_set_type(app, log4c_appender_type_get(type->value));

#ifdef WITH_ROLLINGFILE
			if ( !_x_strcasecmp(type->value, "rollingfile")) {
				rollingfile_udata_t *rfup = NULL;
				log4c_rollingpolicy_t *rollingpolicyp = NULL;
				sd_domnode_t*  logdir = sd_domnode_attrs_get(anode,
					"logdir");
				sd_domnode_t*  logprefix = sd_domnode_attrs_get(anode,
					"prefix");
				sd_domnode_t*  rollingpolicy_name = sd_domnode_attrs_get(anode,
					"rollingpolicy");

				sd_debug("logdir='%s', prefix='%s', rollingpolicy='%s'",
					(logdir && logdir->value ? name->value :"(not set)"),
					(logprefix && logprefix->value ? logprefix->value :"(not set)"),
					(rollingpolicy_name && rollingpolicy_name->value ?
					rollingpolicy_name->value :"(not set)"));

				rfup = rollingfile_make_udata();              
				rollingfile_udata_set_logdir(rfup, (char *)logdir->value);
				rollingfile_udata_set_files_prefix(rfup, (char *)logprefix->value);

				if (rollingpolicy_name){
					/* recover a rollingpolicy instance with ptrThis name */
					rollingpolicyp = log4c_rollingpolicy_get(rollingpolicy_name->value);

					/* connect that policy to ptrThis rollingfile appender conf */
					rollingfile_udata_set_policy(rfup, rollingpolicyp);
					log4c_appender_set_udata(app, rfup);

					/* allow the policy to initialize itself */
					log4c_rollingpolicy_init(rollingpolicyp, rfup);
				} else {
					/* no rollingpolicy specified, default to default sizewin */
					sd_debug("no rollingpolicy name specified--will default");
				}
			}
#endif
		}

		if (layout)
			log4c_appender_set_layout(app, log4c_layout_get(layout->value));

		sd_debug("]");

		return 0;
	}

	/******************************************************************************/
	static int layout_load(log4c_rc_t* ptrThis, sd_domnode_t* anode)
	{
		sd_domnode_t*   name   = sd_domnode_attrs_get(anode, "name");
		sd_domnode_t*   type   = sd_domnode_attrs_get(anode, "type");
		log4c_layout_t* layout = NULL;

		if (!name) {
			sd_error("attribute \"name\" is missing");
			return -1;
		}

		layout = log4c_layout_get(name->value);

		if (type)
			log4c_layout_set_type(layout, log4c_layout_type_get(type->value));

		return 0;
	}

#ifdef WITH_ROLLINGFILE
	/******************************************************************************/
	static int rollingpolicy_load(log4c_rc_t* ptrThis, sd_domnode_t* anode)
	{
		sd_domnode_t*   name   = sd_domnode_attrs_get(anode, "name");
		sd_domnode_t*   type   = sd_domnode_attrs_get(anode, "type");
		log4c_rollingpolicy_t* rpolicyp = NULL;
		long a_maxsize;

		sd_debug("rollingpolicy_load[");
		if (!name) {
			sd_error("attribute \"name\" is missing");
			return -1;
		}

		rpolicyp = log4c_rollingpolicy_get(name->value);    

		if (type){
			log4c_rollingpolicy_set_type(rpolicyp,
				log4c_rollingpolicy_type_get(type->value));

			if (!_x_strcasecmp(type->value, "sizewin")){
				sd_domnode_t*   maxsize   = sd_domnode_attrs_get(anode, "maxsize");
				sd_domnode_t*   maxnum  = sd_domnode_attrs_get(anode, "maxnum");
				rollingpolicy_sizewin_udata_t *sizewin_udatap = NULL;

				sd_debug("type='sizewin', maxsize='%s', maxnum='%s', "
					"rpolicyname='%s'",
					(maxsize && maxsize->value ? maxsize->value :"(not set)"),
					(maxnum && maxnum->value ? maxnum->value :"(not set)"),
					(name && name->value ? name->value :"(not set)"));
				/*
				* Get a new sizewin policy type and configure it.
				* Then attach it to the policy object.
				* Check to see if ptrThis policy already has a
				sw udata object.  If so, leave as is except update
				the params
				*/
				if ( !(sizewin_udatap = (rollingpolicy_sizewin_udata_t *)log4c_rollingpolicy_get_udata(rpolicyp))){ 
					sd_debug("creating new sizewin udata for ptrThis policy");
					sizewin_udatap = sizewin_make_udata();
					log4c_rollingpolicy_set_udata(rpolicyp,sizewin_udatap);   
					a_maxsize = parse_byte_size(maxsize->value);
					if (a_maxsize)
						sizewin_udata_set_file_maxsize(sizewin_udatap, a_maxsize);
					else{
						sd_debug("When parsing %s a size of 0 was returned. Default size %d will be used",
							maxsize->value, ROLLINGPOLICY_SIZE_DEFAULT_MAX_FILE_SIZE);
						sizewin_udata_set_file_maxsize(sizewin_udatap, ROLLINGPOLICY_SIZE_DEFAULT_MAX_FILE_SIZE); 
					}

					sizewin_udata_set_max_num_files(sizewin_udatap, atoi(maxnum->value));
				}else{
					sd_debug("policy already has a sizewin udata--just updating params");
					sizewin_udata_set_file_maxsize(sizewin_udatap, parse_byte_size(maxsize->value));
					sizewin_udata_set_max_num_files(sizewin_udatap, atoi(maxnum->value));
					/* allow the policy to initialize itself */
					log4c_rollingpolicy_init(rpolicyp, 
						log4c_rollingpolicy_get_rfudata(rpolicyp));
				}        

			}

		}
		sd_debug("]");

		return 0;
	}
#endif

	/******************************************************************************/
	extern int log4c_rc_load(log4c_rc_t* ptrThis, const char* a_filename)
	{    
		sd_list_iter_t* i = NULL;
		sd_domnode_t*   node = NULL;        
		sd_domnode_t*   root_node = NULL;

		sd_debug("parsing file '%s'\n", a_filename);

		if (!ptrThis)
			return -1;

		root_node = sd_domnode_new(NULL, NULL);

		if (sd_domnode_load(root_node, a_filename) == -1) {
			sd_domnode_delete(root_node);
			return -1;
		}

		/* Check configuration file root node */
		if (strcmp(root_node->name, "log4c")) {
			sd_error("invalid root name %s", root_node->name);
			sd_domnode_delete(root_node);
			return -1;
		}

		/* Check configuration file revision */
		if ( (node = sd_domnode_attrs_get(root_node, "version")) != NULL)
			if (strcmp(VERSION, node->value)) {
				sd_error("version mismatch: %s != %s", VERSION, node->value);
				sd_domnode_delete(root_node);
				return -1;
			}

			/* backward compatibility. */
			if ( (node = sd_domnode_attrs_get(root_node, "cleanup")) != NULL) {
				sd_debug("attribute \"cleanup\" is deprecated");
				ptrThis->config.nocleanup = !atoi(node->value);
			}

			/* load configuration elements */
			for (i = sd_list_begin(root_node->children);
				i != sd_list_end(root_node->children); 
				i = sd_list_iter_next(i)) 
			{
				sd_domnode_t* node = (sd_domnode_t*)i->data;

				if (!strcmp(node->name, "category")) category_load(ptrThis, node);
				if (!strcmp(node->name, "appender")) appender_load(ptrThis, node);
#ifdef WITH_ROLLINGFILE
				if (!strcmp(node->name, "rollingpolicy"))rollingpolicy_load(ptrThis, node);
#endif
				if (!strcmp(node->name, "layout"))   layout_load(ptrThis, node);
				if (!strcmp(node->name, "config"))   config_load(ptrThis, node);
			}

			sd_domnode_delete(root_node);

			return 0;
	}

	/******************************************************************************/
	extern int log4c_load(const char* a_filename)
	{
		return log4c_rc_load(&__log4c_rc, a_filename);
	}

/************** End of rc.c *******************************************/

/************** Begin of rollingpolicy.c *******************************************/
	/*
	* rollingpolicy.c
	*
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

///#include <log4c/appender.h>
///#include <log4c/appender_type_rollingfile.h>
///#include <log4c/rollingpolicy.h>
///#include <log4c/rollingpolicy_type_sizewin.h>
#include <string.h>
///#include <sd/malloc.h>
///#include <sd/factory.h>
///#include <sd/hash.h>
///#include <sd/factory.h>
///#include <sd/error.h>
///#include <sd/defs.h>

	/* Internal struct that defines the conf and the state info
	* for an instance of the appender_type_fileroller type.
	*/    
	struct __log4c_rollingpolicy
	{
		char*				        policy_name;
		const log4c_rollingpolicy_type_t*     policy_type;
		void *                                policy_udata;
		rollingfile_udata_t*                  policy_rfudatap;
#define PFLAGS_IS_INITIALIZED 0x0001
		int					policy_flags;
	};

	sd_factory_t* log4c_rollingpolicy_factory = NULL;


	//////////////////////////////////////////////////////////////////////////
	///以下为温辉敏修改的代码，将原有代码用#if 0...#endif注释掉
	// 为解决log4c_layout_types中内存泄漏而将静态局部变量提升为全局局部变量 [9/8/2008 温辉敏]
	static sd_hash_t* rollingpolicy_c_gs_types = NULL;

	static sd_hash_t* log4c_rollingpolicy_types(void)
	{
		///static sd_hash_t* types = NULL;	
		if (!rollingpolicy_c_gs_types)
			rollingpolicy_c_gs_types = sd_hash_new(20, NULL);

		return rollingpolicy_c_gs_types;
	}

	/** 删除本rollingpolicy.c文件中定义的全局和静态的指针指向的内存,防止内存泄漏
	如：
	1.rollingpolicy_c_gs_types.
	2.
	@return void.
	作者：温辉敏 日期:2008.09.08
	*/
	extern void log4c_rollingpolicy_delete_global()
	{
		if (NULL != rollingpolicy_c_gs_types)
		{
			sd_hash_delete(rollingpolicy_c_gs_types);
			rollingpolicy_c_gs_types = NULL;
		}
	}

	//////////////////////////////////////////////////////////////////////////
#if 0
	/*******************************************************************************/
	static sd_hash_t* log4c_rollingpolicy_types(void){
		static sd_hash_t* types = NULL;

		if (!types)
			types = sd_hash_new(20, NULL);

		return types;
	}
#endif

	extern void log4c_rollingpolicy_types_print(FILE *fp)
	{
		sd_hash_iter_t* i;

		fprintf(fp, "rollingpolicy types:");
		for (i = sd_hash_begin(log4c_rollingpolicy_types());
			i != sd_hash_end(log4c_rollingpolicy_types()); 
			i = sd_hash_iter_next(i) ) 
		{
			fprintf(fp, "'%s' ",((log4c_rollingpolicy_type_t *)(i->data))->name );
		}
		fprintf(fp, "\n");
	}

	/*******************************************************************************/
	LOG4C_API log4c_rollingpolicy_t* log4c_rollingpolicy_get(const char* a_name)
	{
		static const sd_factory_ops_t log4c_rollingpolicy_factory_ops = {
			/*(void*) log4c_rollingpolicy_new,
			(void*) log4c_rollingpolicy_delete,
			(void*) log4c_rollingpolicy_print,*/
			(void *( *)(const char *))log4c_rollingpolicy_new,
			(void ( *)(void *))log4c_rollingpolicy_delete,
			(void ( *)(void *,FILE *))log4c_rollingpolicy_print
		};

		if (!log4c_rollingpolicy_factory) {
			log4c_rollingpolicy_factory = 
				sd_factory_new("log4c_rollingpolicy_factory", 
				&log4c_rollingpolicy_factory_ops);

			/* build default rollingpolicy 
			log4c_rollingpolicy_set_udata(log4c_appender_get("stderr"), stderr);
			log4c_appender_set_udata(log4c_appender_get("stdout"), stdout);*/
		}

		return (log4c_rollingpolicy_t*)sd_factory_get(log4c_rollingpolicy_factory, a_name);
	}

	/****************************************************************************/
	LOG4C_API log4c_rollingpolicy_t* log4c_rollingpolicy_new(const char* a_name){
		log4c_rollingpolicy_t* ptrThis;

		sd_debug("log4c_rollingpolicy_new[ ");
		if (!a_name)
			return NULL;
		sd_debug("new policy name='%s'", a_name);
		ptrThis	          = (log4c_rollingpolicy_t*)sd_calloc(1, sizeof(log4c_rollingpolicy_t));
		ptrThis->policy_name     = sd_strdup(a_name);
		ptrThis->policy_type     = &log4c_rollingpolicy_type_sizewin;
		ptrThis->policy_udata    = NULL;
		ptrThis->policy_rfudatap  = NULL;
		ptrThis->policy_flags = 0; 

		sd_debug("]");

		return ptrThis;
	}

	/*******************************************************************************/
	LOG4C_API void log4c_rollingpolicy_delete(log4c_rollingpolicy_t* ptrThis)
	{

		sd_debug("log4c_rollingpolicy_delete['%s'", 
			(ptrThis && ptrThis->policy_name ? ptrThis->policy_name: "(no name)"));
		if (!ptrThis){
			goto log4c_rollingpolicy_delete_exit;
		}

		if (log4c_rollingpolicy_fini(ptrThis)){
			sd_error("failed to fini rollingpolicy");
			goto log4c_rollingpolicy_delete_exit;
		}

		if (ptrThis->policy_name){
			sd_debug("freeing policy name");
			free(ptrThis->policy_name);
			ptrThis->policy_name = NULL;
		};
		sd_debug("freeing ptrThis rolling policy instance");
		free(ptrThis);

log4c_rollingpolicy_delete_exit:
		sd_debug("]");
	}

	/*******************************************************************************/

	LOG4C_API int log4c_rollingpolicy_init(log4c_rollingpolicy_t *ptrThis, rollingfile_udata_t* rfup){

		int rc = 0;

		if (!ptrThis)
			return -1;

		ptrThis->policy_rfudatap = rfup;

		if (!ptrThis->policy_type)
			return 0;

		if (!ptrThis->policy_type->init)
			return 0;

		rc = ptrThis->policy_type->init(ptrThis, rfup);

		ptrThis->policy_flags |= PFLAGS_IS_INITIALIZED;

		return rc;  

	}

	LOG4C_API int log4c_rollingpolicy_fini(log4c_rollingpolicy_t *ptrThis){

		int rc = 0;

		sd_debug("log4c_rollingpolicy_fini['%s'", 
			(ptrThis && ptrThis->policy_name ? ptrThis->policy_name: "(no name")) ;

		if (!ptrThis){
			rc = 0;
		} else {
			if (ptrThis->policy_flags & PFLAGS_IS_INITIALIZED){
				if (ptrThis->policy_type){
					rc = ptrThis->policy_type->fini(ptrThis);
				}
			}

			if (!rc){
				ptrThis->policy_flags &= ~PFLAGS_IS_INITIALIZED;
			}else{
				sd_debug("Call to rollingpolicy fini failed");
			}
		}

		sd_debug("]");
		return rc;  
	}

	/*******************************************************************************/

	LOG4C_API int log4c_rollingpolicy_is_triggering_event(log4c_rollingpolicy_t* ptrThis, const log4c_logging_event_t* a_event, long current_fs){
		if (!ptrThis)
			return -1;

		if (!ptrThis->policy_type)
			return 0;

		if (!ptrThis->policy_type->is_triggering_event)
			return 0;

		return ptrThis->policy_type->is_triggering_event(ptrThis, a_event, current_fs);  
	}
	/*******************************************************************************/

	LOG4C_API int log4c_rollingpolicy_rollover(log4c_rollingpolicy_t* ptrThis, FILE **fpp){

		if (!ptrThis)
			return -1;

		if (!ptrThis->policy_type)
			return 0;

		if (!ptrThis->policy_type->rollover)
			return 0;

		return ptrThis->policy_type->rollover(ptrThis, fpp);
	}
	/*******************************************************************************/

	LOG4C_API void* log4c_rollingpolicy_get_udata(const log4c_rollingpolicy_t* ptrThis){
		return (ptrThis ? ptrThis->policy_udata : NULL);
	}
	/*******************************************************************************/

	LOG4C_API void* log4c_rollingpolicy_get_name(const log4c_rollingpolicy_t* ptrThis){
		return (ptrThis ? ptrThis->policy_name : NULL);
	}
	/*******************************************************************************/

	LOG4C_API rollingfile_udata_t* log4c_rollingpolicy_get_rfudata(const log4c_rollingpolicy_t* ptrThis){
		return (ptrThis ? ptrThis->policy_rfudatap : NULL);
	}

	/*******************************************************************************/

	LOG4C_API const log4c_rollingpolicy_type_t* log4c_rollingpolicy_type_set( const log4c_rollingpolicy_type_t* a_type){

		sd_hash_iter_t* i = NULL;
		void* previous = NULL;

		if (!a_type)
			return NULL;

		if ( (i = sd_hash_lookadd(log4c_rollingpolicy_types(), a_type->name)) == NULL)
			return NULL;

		previous = i->data;
		i->data  = (void*) a_type;

		return (log4c_rollingpolicy_type_t*)previous;
	}
	/*****************************************************************************/
	LOG4C_API const log4c_rollingpolicy_type_t* log4c_rollingpolicy_type_get( const char* a_name){
		sd_hash_iter_t* i;

		if (!a_name)
			return NULL;

		if ( (i = sd_hash_lookup(log4c_rollingpolicy_types(), a_name)) != NULL)
			return (log4c_rollingpolicy_type_t*)i->data;

		return NULL;
	}
	/*******************************************************************************/

	LOG4C_API void log4c_rollingpolicy_set_udata(log4c_rollingpolicy_t* ptrThis, void *udatap){
		if ( ptrThis) {
			ptrThis->policy_udata = udatap;
		}
	}

	/*******************************************************************************/
	LOG4C_API const log4c_rollingpolicy_type_t* log4c_rollingpolicy_set_type( log4c_rollingpolicy_t* a_rollingpolicy, const log4c_rollingpolicy_type_t* a_type){

		const log4c_rollingpolicy_type_t* previous;

		if (!a_rollingpolicy)
			return NULL;

		previous = a_rollingpolicy->policy_type;
		a_rollingpolicy->policy_type = a_type;
		return previous;
	}

	/*******************************************************************************/
	LOG4C_API void log4c_rollingpolicy_print(const log4c_rollingpolicy_t* ptrThis, FILE* a_stream)
	{
		if (!ptrThis) 
			return;

		fprintf(a_stream, "{ name:'%s' udata:%p}",
			ptrThis->policy_name, 	     
			ptrThis->policy_udata);
	}


	LOG4C_API int log4c_rollingpolicy_is_initialized(log4c_rollingpolicy_t* ptrThis){

		if (!ptrThis) 
			return(0);	

		return( ptrThis->policy_flags & PFLAGS_IS_INITIALIZED);

	}

/************** End of rollingpolicy.c *******************************************/

/************** Begin of rollingpolicy_type_sizewin.c *******************************************/

	/*
	* rollingpolicy_type_sizewin.c
	*
	* 
	* See the COPYING file for the terms of usage and distribution.
	*/

#ifdef HAVE_CONFIG_H
///#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif
///#include <log4c/appender.h>
///#include <log4c/rollingpolicy.h>
///#include <log4c/rollingpolicy_type_sizewin.h>

///#include "appender_type_rollingfile.h"
///#include <sd/malloc.h>
///#include <sd/error.h>
///#include <sd/sd_xplatform.h>

	/* Internal structs that defines the conf and the state info
	* for an instance of the appender_type_rollingfile type.
	*/    
	struct __sizewin_conf {  
		long swc_file_maxsize;
		long swc_file_max_num_files;
	};

	struct __sizewin_udata {
		struct __sizewin_conf sw_conf;
		rollingfile_udata_t *sw_rfudata;
		const char *sw_logdir;
		const char *sw_files_prefix;
		char **sw_filenames; 
		long sw_last_index;
#define SW_LAST_FOPEN_FAILED 0x0001
		int sw_flags;
	};

	/***************************************************************************/

	static int sizewin_init(log4c_rollingpolicy_t *ptrThis, rollingfile_udata_t* rfup);
	static int sizewin_rollover(log4c_rollingpolicy_t *ptrThis, FILE **current_fpp );
	static int sizewin_is_triggering_event(
		log4c_rollingpolicy_t *ptrThis,
		const log4c_logging_event_t* a_event,
		long current_file_size);

	static char **sizewin_make_filename_array(rollingpolicy_sizewin_udata_t *swup);
	static int sizewin_get_last_index(rollingpolicy_sizewin_udata_t * swup);
	static char* sizewin_get_filename_by_index(rollingpolicy_sizewin_udata_t * swup,
		long i);
	static int sizewin_open_zero_file(char *filename, FILE **fpp );

	/*******************************************************************************
	Policy interface: init, is_triggering_event, rollover
	*******************************************************************************/

	static int sizewin_is_triggering_event(
		log4c_rollingpolicy_t *ptrThis,
		const log4c_logging_event_t* a_event,
		long current_file_size){
			long len = 0;
			int decision = 0;
			rollingpolicy_sizewin_udata_t *swup = (rollingpolicy_sizewin_udata_t *)log4c_rollingpolicy_get_udata(ptrThis);
			/*rollingfile_udata_t *rfup = log4c_rollingpolicy_get_udata(ptrThis);  */

			sd_debug("sizewin_is_triggering_event[");

			/* find the len of ptrThis message
			xxx ptrThis should be provided by the logging_event class
			*/
			len = strlen(a_event->evt_rendered_msg);
			sd_debug("fsize=%ld max=%ld len=%ld", current_file_size,
				swup->sw_conf.swc_file_maxsize, len  );
			if ( swup->sw_conf.swc_file_maxsize > 0 &&
				len + current_file_size > swup->sw_conf.swc_file_maxsize ) {
					sd_debug("triggering event");
					decision = 1;
			} else {
				sd_debug("not triggering event");
			}

			sd_debug("]");  
			return(decision);
	}

	/*******************************************************************************/

	static int sizewin_rollover(log4c_rollingpolicy_t *ptrThis, FILE ** current_fpp ){
		int rc = 0;
		rollingpolicy_sizewin_udata_t *swup = (rollingpolicy_sizewin_udata_t *)log4c_rollingpolicy_get_udata(ptrThis);
		int k = 0;
		int i = 0;

		sd_debug("sizewin_rollover[");
		/* Starting at the last_index work back renaming the files and
		leaving space for the .0 file.
		If the last index is negative then it means the file doesn't exist
		so we create the first file
		*/

		if ( !swup || !swup->sw_logdir){
			sd_error("rollingpolicy '%s' not yet configured (logdir,prefix etc.)",
				log4c_rollingpolicy_get_name(ptrThis));
		} else {

			k = swup->sw_last_index;

			if ( k < 0 ) {
				sd_debug("creating first file");
				if (sizewin_open_zero_file(swup->sw_filenames[0], current_fpp)){
					swup->sw_flags |= SW_LAST_FOPEN_FAILED;
					sd_error("open zero file failed");
				} else{
					swup->sw_flags &= !SW_LAST_FOPEN_FAILED;
				}
				swup->sw_last_index = 0;
			} else {
				sd_debug("rolling up existing files");

				if ( k == swup->sw_conf.swc_file_max_num_files-1) {    
					if(unlink(swup->sw_filenames[k])){
						sd_error("unlink failed"); 
						rc = 1;
					} else {
						k = swup->sw_conf.swc_file_max_num_files-2;
					}
				} else {
					/* not yet reached the max num of files
					* so there's still room to rotate the list up */    
				}

				/* If there's a current open fp, close it.*/
				if ( !(swup->sw_flags & SW_LAST_FOPEN_FAILED) && *current_fpp) {
					if(fclose(*current_fpp)){
						sd_error("failed to close current log file");
						rc = 1;
					}
				} else {
					if( (swup->sw_flags & SW_LAST_FOPEN_FAILED)){
						sd_debug("Not closing log file...last open failed");
					} else if (*current_fpp == 0) {
						sd_debug("No log file currentlty open...so not closing it");
					}else {
						sd_debug("Not closing current log file...not sure why");
					}
				}
				/* Now, rotate the list up if all seems ok, otherwise 
				* don't mess with teh files if something seems to have gone wrong
				*/
				if ( !rc){
					sd_debug("rotate up , last index is %d", k); 
					i = k;
					while ( i >= 0 ) {
						sd_debug("Renaming %s to %s",
							swup->sw_filenames[i], swup->sw_filenames[i+1]);
						if(rename( swup->sw_filenames[i], swup->sw_filenames[i+1])){
							sd_error("rename failed"); 
							rc = 1;
							break;
						}
						i--;
					}
					if ( !rc){
						swup->sw_last_index = k + 1;
					}
				} else {
					sd_debug("not rotating up--some file access error");
				}

				/* Now open up the 0'th file for writing */
				if (sizewin_open_zero_file(swup->sw_filenames[0], current_fpp)){
					swup->sw_flags |= SW_LAST_FOPEN_FAILED;
					sd_error("open zero file failed");
					rc = 1;
				} else{
					swup->sw_flags &= !SW_LAST_FOPEN_FAILED;
					rc = 0;
				}

			}
			sd_debug("current file descriptor '%d'", fileno(*current_fpp));
		}
		sd_debug("]");
		return(rc);
	}

	/*******************************************************************************/

	static int sizewin_init(log4c_rollingpolicy_t *ptrThis, rollingfile_udata_t *rfup){
		rollingpolicy_sizewin_udata_t *swup =  NULL;
		int i = 0;

		sd_debug("sizewin_init[");
		if (!ptrThis){
			goto sizewin_init_exit;
		}

		swup = (rollingpolicy_sizewin_udata_t *)log4c_rollingpolicy_get_udata(ptrThis);
		if ( swup == NULL ){
			swup = sizewin_make_udata();
			log4c_rollingpolicy_set_udata(ptrThis, swup);
		}

		/* initialize the filename array and last index */
		swup->sw_logdir = rollingfile_udata_get_logdir(rfup);
		swup->sw_files_prefix = rollingfile_udata_get_files_prefix(rfup);

		swup->sw_filenames = sizewin_make_filename_array(swup);
		for ( i = 0; i<swup->sw_conf.swc_file_max_num_files; i++){
			sd_debug("%s", swup->sw_filenames[i]);
		}
		swup->sw_last_index = sizewin_get_last_index(swup);  
		sd_debug("last index '%d'", swup->sw_last_index);

sizewin_init_exit:
		sd_debug("]"); 

		return(0);
	}

	/*******************************************************************************/

	static int sizewin_fini(log4c_rollingpolicy_t *ptrThis){
		rollingpolicy_sizewin_udata_t *swup =  NULL;
		int i = 0;
		int rc = 0;

		sd_debug("sizewin_fini[ ");
		if (!ptrThis){
			goto sizewin_fini_exit;
		}

		swup = (rollingpolicy_sizewin_udata_t *)log4c_rollingpolicy_get_udata(ptrThis);
		if (!swup){
			goto sizewin_fini_exit;
		}

		for ( i = 0; i<swup->sw_conf.swc_file_max_num_files; i++){
			if ( swup->sw_filenames[i]){
				free(swup->sw_filenames[i]);
			}
		}
		free(swup->sw_filenames);

		/* logdir and files_prefix are just pointers into the rollingfile udata
		* so they are not ours to free--that will be done by the free call to
		* the rollingfile appender
		*/
		sd_debug("freeing sizewin udata from rollingpolicy instance");
		free(swup);
		log4c_rollingpolicy_set_udata(ptrThis,NULL);

sizewin_fini_exit:
		sd_debug("]");

		return(rc);
	}

	/*******************************************************************************
	sizewin specific conf functions
	*******************************************************************************/

	LOG4C_API rollingpolicy_sizewin_udata_t *sizewin_make_udata(void){
		rollingpolicy_sizewin_udata_t *swup = NULL;
		swup = (rollingpolicy_sizewin_udata_t *)sd_calloc(1, 
			sizeof(rollingpolicy_sizewin_udata_t));
		sizewin_udata_set_file_maxsize(swup,
			ROLLINGPOLICY_SIZE_DEFAULT_MAX_FILE_SIZE);
		sizewin_udata_set_max_num_files(swup,
			ROLLINGPOLICY_SIZE_DEFAULT_MAX_NUM_FILES);

		return(swup);

	}

	/*******************************************************************************/

	LOG4C_API int sizewin_udata_set_file_maxsize(rollingpolicy_sizewin_udata_t * swup,
		long max_size){

			swup->sw_conf.swc_file_maxsize = max_size;

			return(0);

	}

	/****************************************************************************/

	LOG4C_API int sizewin_udata_set_max_num_files(rollingpolicy_sizewin_udata_t *swup, 
		long max_num){

			swup->sw_conf.swc_file_max_num_files = max_num;

			return(0);
	}

	/****************************************************************************/

	LOG4C_API int sizewin_udata_set_rfudata(rollingpolicy_sizewin_udata_t *swup,
		rollingfile_udata_t *rfup ){

			swup->sw_rfudata = rfup;

			return(0);
	}

	/*****************************************************************************
	private functions
	*****************************************************************************/


	static char **sizewin_make_filename_array(rollingpolicy_sizewin_udata_t *swup){

		int i = 0;
		char **filenames = NULL;

		filenames = (char **)sd_calloc(swup->sw_conf.swc_file_max_num_files,
			sizeof(char *));
		while ( i <  swup->sw_conf.swc_file_max_num_files){

			filenames[i] = sizewin_get_filename_by_index(swup,i);
			i++;
		}
		return(filenames);
	}

	/****************************************************************************/

	static char* sizewin_get_filename_by_index(rollingpolicy_sizewin_udata_t* swup,
		long i){
			char tmp[100];
			long filename_len = 0;
			char *s = NULL;

			sprintf(tmp, "%ld", i);
			filename_len = strlen(swup->sw_logdir) + 1 +
				strlen(swup->sw_files_prefix) + 1 +
				strlen(tmp) + 1 + 10; /* a margin */
			s = (char *)malloc(filename_len);      
			sprintf( s, "%s%s%s%s%s", swup->sw_logdir,
				FILE_SEP, swup->sw_files_prefix, ".", tmp);	      
			return(s); 
	}

	/****************************************************************************/

	static int sizewin_get_last_index(rollingpolicy_sizewin_udata_t *swup){

		/* Walk the filelist to find the last one that exists to
		initialize last_index
		*/

		int i = 0;
		struct stat	info;

		while( i <swup->sw_conf.swc_file_max_num_files &&
			stat(swup->sw_filenames[i], &info) == 0  ) {
				i++;
		}

		if ( i == 0 ){
			if ( stat(swup->sw_filenames[i], &info) == 0 ) {
				return(0);
			} else {
				return(-1);
			}
		} else {
			return(i-1);
		}

	}

	/*******************************************************************************/

	static int sizewin_open_zero_file(char *filename, FILE **fpp ){
		int rc = 0;
		sd_debug("sizewin_open_zero_file['%s'", filename);

		if ( (*fpp = fopen(filename, "w+")) == NULL){
			sd_error("failed to open zero file '%s'--defaulting to stderr--error='%s'",
				filename, strerror(errno));    
			*fpp = stderr;
			rc = 1;
		}  

		/* unbuffered mode at the filesystem level
		xxx make ptrThis configurable from the outside ?
		*/
		setbuf(*fpp, NULL);    

		sd_debug("]");  
		return(rc);

	}

	/****************************************************************************/

	const log4c_rollingpolicy_type_t log4c_rollingpolicy_type_sizewin = {
		"sizewin",
		sizewin_init,
		sizewin_is_triggering_event,
		sizewin_rollover,
		sizewin_fini
	};

/************** End of rollingpolicy_type_sizewin.c *******************************************/

/************** Begin of sd_xplatform.c *******************************************/
	///static const char version[] = "$Id$";

	/*
	* sd_xplatform.c
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

#include <stdio.h>
#include <string.h>
///#include "log4c/defs.h"

///#include "sd_xplatform.h"

	/****************** getopt *******************************/

#define	EOF	(-1)

	int sd_opterr = 1;
	int sd_optind = 1;
	int sd_optopt = 0;
	char *sd_optarg = NULL;
	int _sp = 1;

#define warn(a,b,c)fprintf(stderr,a,b,c)

	void
		getopt_reset(void)
	{
		sd_opterr = 1;
		sd_optind = 1;
		sd_optopt = 0;
		sd_optarg = NULL;
		_sp = 1;
	}

	int
		sd_getopt(int argc, char *const *argv, const char *opts)
	{
		char c;
		const char *cp;

		if (_sp == 1) {
			if (sd_optind >= argc || argv[sd_optind][0] != '-' ||
				argv[sd_optind] == NULL || argv[sd_optind][1] == '\0')
				return (EOF);
			else if (strcmp(argv[sd_optind], "--") == 0) {
				sd_optind++;
				return (EOF);
			}
		}
		sd_optopt = c = (unsigned char)argv[sd_optind][_sp];
		if (c == ':' || (cp = strchr(opts, c)) == NULL) {
			if (opts[0] != ':')
				warn("%s: illegal option -- %c\n", argv[0], c);
			if (argv[sd_optind][++_sp] == '\0') {
				sd_optind++;
				_sp = 1;
			}
			return ('?');
		}

		if (*(cp + 1) == ':') {
			if (argv[sd_optind][_sp+1] != '\0')
				sd_optarg = &argv[sd_optind++][_sp+1];
			else if (++sd_optind >= argc) {
				if (opts[0] != ':') {
					warn("%s: option requires an argument"
						" -- %c\n", argv[0], c);
				}
				_sp = 1;
				sd_optarg = NULL;
				return (opts[0] == ':' ? ':' : '?');
			} else
				sd_optarg = argv[sd_optind++];
			_sp = 1;
		} else {
			if (argv[sd_optind][++_sp] == '\0') {
				_sp = 1;
				sd_optind++;
			}
			sd_optarg = NULL;
		}
		return (c);
	}

	/*****************************  gettimeofday *******************/


#ifdef _WIN32

#if 0 /* also in winsock[2].h */
#define _TIMEVAL_DEFINED
	struct timeval {
		long tv_sec;
		long tv_usec;
		long tv_usec;
	};
#endif /* _TIMEVAL_DEFINED */

	int sd_gettimeofday(LPFILETIME lpft, void* tzp) {

		if (lpft) {
			GetSystemTimeAsFileTime(lpft);
		}
		/* 0 indicates that the call succeeded. */
		return 0;
	}
#endif /* _WIN32 */

	/*
	* Placeholder for WIN32 version to get last changetime of a file
	*/
#ifdef WIN32
	int sd_stat_ctime(const char* path, time_t* time)
	{ return -1; }
#else
	int sd_stat_ctime(const char* path, time_t* time)
	{
		struct stat astat;
		int statret=stat(path,&astat);
		if (0 != statret)
		{
			return statret;
		}
#ifdef __USE_MISC
		*time=astat.st_ctim.tv_sec;
#else
		*time=astat.st_ctime;
#endif
		return statret;
	}
#endif



/************** End of sd_xplatform.c *******************************************/

/************** Begin of sprintf.c *******************************************/
	///static const char version[] = "$Id$";

	/* 
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
///#include <sd/sprintf.h>
///#include <sd/malloc.h>
///#include <sd/sd_xplatform.h>

	/******************************************************************************/
	extern char* sd_sprintf(const char* a_fmt, ...)
	{
		char*	buffer;
		va_list	args;

		va_start(args, a_fmt);
		buffer = sd_vsprintf(a_fmt, args);
		va_end(args);

		return buffer;
	}

	/******************************************************************************/
	extern char* sd_vsprintf(const char* a_fmt, va_list a_args)
	{
		int		size	= 1024;
		char*	buffer  = (char*)sd_calloc(size, sizeof(char));

		while (1) {
			int n = vsnprintf(buffer, size, a_fmt, a_args);

			/* If that worked, return */
			if (n > -1 && n < size)
				return buffer;

			/* Else try again with more space. */
			if (n > -1)     /* ISO/IEC 9899:1999 */
				size = n + 1;    
			else            /* twice the old size */
				size *= 2;      

			buffer = (char*)sd_realloc(buffer, size);
		}
	}

#if defined(__osf__)
#	ifndef snprintf
#		include "sprintf.osf.c"
#	endif
#endif


/************** End of sprintf.c *******************************************/

	

/************** Begin of stack.c *******************************************/
	/* stack - a dynamically resizing stack
	* Copyright (c) 2001 Michael B. Allen <mballen@erols.com>
	*
	* The MIT License
	* 
	* Permission is hereby granted, free of charge, to any person obtaining a
	* copy of ptrThis software and associated documentation files (the "Software"),
	* to deal in the Software without restriction, including without limitation
	* the rights to use, copy, modify, merge, publish, distribute, sublicense,
	* and/or sell copies of the Software, and to permit persons to whom the
	* Software is furnished to do so, subject to the following conditions:
	* 
	* The above copyright notice and ptrThis permission notice shall be included
	* in all copies or substantial portions of the Software.
	* 
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
	* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
	* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	* OTHER DEALINGS IN THE SOFTWARE.
	*/ 

///#include <sd/stack.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

///#include <sd/malloc.h>

#define SD_STACK_INIT_SIZE 32

	struct __sd_stack {
		size_t max;
		size_t sp;
		size_t size;
		size_t iter;
		void **array;
	};

	/******************************************************************************/
	sd_stack_t* sd_stack_new(size_t max)
	{
		sd_stack_t* ptrThis;

		ptrThis        = (sd_stack_t*)sd_calloc(1, sizeof(sd_stack_t));
		ptrThis->max   = max == 0 ? INT_MAX : max;
		ptrThis->size  = SD_STACK_INIT_SIZE;
		ptrThis->sp    = 0;
		ptrThis->array = (void **)sd_calloc(ptrThis->size, sizeof(*ptrThis->array));

		return ptrThis;
	}

	/******************************************************************************/
	void sd_stack_delete(sd_stack_t* ptrThis, void (*free_data_fn)(void *))
	{
		if (!ptrThis)
			return;

		sd_stack_clear(ptrThis, free_data_fn);

		free(ptrThis->array);
		free(ptrThis);
	}

	/******************************************************************************/
	size_t sd_stack_get_nelem(const sd_stack_t* ptrThis)
	{
		return ptrThis ? ptrThis->sp : -1;
	}

	/******************************************************************************/
	void sd_stack_clear(sd_stack_t* ptrThis, void (*free_data_fn)(void *))
	{
		if (!ptrThis)
			return;

		if (free_data_fn) {
			while (ptrThis->sp > 0) {
				free_data_fn(ptrThis->array[--(ptrThis->sp)]);
			}
		}
	}

	/******************************************************************************/
	void* sd_stack_begin(sd_stack_t* ptrThis)
	{
		if (!ptrThis)
			return NULL;

		ptrThis->iter = 0;
		return ptrThis->array[ptrThis->iter];
	}

	/******************************************************************************/
	void* sd_stack_next(sd_stack_t* ptrThis)
	{
		if (ptrThis && ptrThis->iter < ptrThis->sp) 
			return ptrThis->array[ptrThis->iter++];

		return NULL;
	}

	/******************************************************************************/
	void* sd_stack_end(sd_stack_t* ptrThis)
	{
		return sd_stack_peek(ptrThis);
	}

	/******************************************************************************/
	void* sd_stack_peek(sd_stack_t* ptrThis)
	{
		if (!ptrThis || !ptrThis->sp) 
			return NULL;

		return ptrThis->array[ptrThis->sp - 1];
	}

	/******************************************************************************/
	int sd_stack_push(sd_stack_t* ptrThis, void *data)
	{
		if (ptrThis == NULL)
			return -1;

		if (ptrThis->sp == ptrThis->size) {
			size_t new_size;

			if (ptrThis->size == ptrThis->max)
				return -1;

			if (ptrThis->size * 2 > ptrThis->max) {
				new_size = ptrThis->max;
			} else {
				new_size = ptrThis->size * 2;
			}

			ptrThis->size = new_size;
			ptrThis->array = (void **)sd_realloc(ptrThis->array, sizeof(*ptrThis->array) * ptrThis->size);
		}

		assert(ptrThis->sp <= ptrThis->size);
		ptrThis->array[ptrThis->sp++] = data;
		return 0;
	}

	/******************************************************************************/
	void* sd_stack_pop(sd_stack_t* ptrThis)
	{
		if (ptrThis == NULL || ptrThis->sp == 0) 
			return NULL;

		if (ptrThis->size >= SD_STACK_INIT_SIZE * 4 && ptrThis->sp < ptrThis->size / 4) {
			size_t new_size = ptrThis->size / 2;

			ptrThis->size = new_size;
			ptrThis->array = (void **)sd_realloc(ptrThis->array, sizeof(*ptrThis->array) * ptrThis->size);
		}

		assert(ptrThis->sp > 0 && ptrThis->sp <= ptrThis->size);
		return ptrThis->array[--(ptrThis->sp)];
	}

/************** End of stack.c *******************************************/

	/************** Begin of sd/test.h *******************************************/

	/* $Id$
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

#ifndef __sd_test_h
#define __sd_test_h

	/**
	* @file test.h
	*/

#include <stdio.h>
///#include <sd/defs.h>

	__SD_BEGIN_DECLS

#define SD_TEST_MAX_NFUNC  100

	struct __sd_test;

	typedef struct __sd_test sd_test_t;

	typedef int (sd_test_func_t)(sd_test_t* a_test, int argc, char* argv[]);

	extern sd_test_t*	sd_test_new(int a_argc, char* a_argv[]);
	extern void sd_test_delete(sd_test_t* a_this);

	extern const char* sd_test_get_name(const sd_test_t* a_this);
	extern int sd_test_get_verbose(const sd_test_t* a_test);
	extern int sd_test_set_verbose(sd_test_t* a_this, int a_verbose);

	extern FILE* sd_test_in(sd_test_t* a_this);
	extern FILE* sd_test_out(sd_test_t* a_this);
	extern FILE* sd_test_err(sd_test_t* a_this);

	extern int sd_test_run(sd_test_t* a_this, int argc, char* argv[]);
	extern int sd_test_add(sd_test_t* a_this, sd_test_func_t a_func);

	__SD_END_DECLS

#endif

		/************** End of sd/test.h *******************************************/

/************** Begin of test.c *******************************************/
	///static const char version[] = "$Id$";

	/* 
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

#ifdef HAVE_CONFIG_H
///#       include "config.h"
#endif
///#include <sd/test.h>
///#include <sd/malloc.h>
///#include <sd/sprintf.h>
///#include <sd/sd_xplatform.h>

#include <stdlib.h>
#include <string.h>

	typedef XP_UINT64 usec_t;

#define MAX_NFUNC 100

	struct __sd_test
	{
		const char*         name;
		char                in_filename[128];
		char                ref_filename[128];
		char                out_filename[128];
		FILE*               in;
		FILE*               out;
		FILE*               err;
		int                 verbose;
		int                 timed;
		sd_test_func_t**    funcs;
		int                 size;
		int			argc;
		char**		argv;
	};


	/******************************************************************************/
	static usec_t now(void)
	{

#ifdef _WIN32
		FILETIME tv;
		ULARGE_INTEGER   li;
#else
		struct timeval tv;
#endif

		SD_GETTIMEOFDAY(&tv, NULL);

#ifdef _WIN32
		memcpy(&li, &tv, sizeof(FILETIME));
		li.QuadPart /= 10;                /* In microseconds */
		/* printf("timestampstamp usec %I64u\n", li.QuadPart);*/
		return li.QuadPart;
#else
		return (usec_t) (tv.tv_sec * 1000000 + tv.tv_usec);
#endif
	}

	/******************************************************************************/
	static int test_compare(sd_test_t* ptrThis, int a_argc, char* a_argv[])
	{
		char cmd[1024];

		if (SD_ACCESS_READ(ptrThis->ref_filename) ||
			SD_ACCESS_READ(ptrThis->out_filename))
			return 1;

		snprintf(cmd, sizeof(cmd), "%s %s %s 1>/dev/null 2>&1", DIFF_CMD,
			ptrThis->ref_filename, ptrThis->out_filename);

		return ! system(cmd);
	}

	/******************************************************************************/
	extern sd_test_t* sd_test_new(int a_argc, char* a_argv[])
	{
		sd_test_t* ptrThis;
		int c;
		char* ptr;

		ptrThis        = (sd_test_t*)sd_calloc(1, sizeof(sd_test_t));
		ptrThis->funcs = (sd_test_func_t**)sd_calloc(MAX_NFUNC, sizeof(sd_test_func_t *));

		/*
		* get rid of libtool frontend script
		*/
		ptr = strstr(a_argv[0], "lt-");
		if (ptr)
			ptrThis->name = ptr + 3;
		else
			ptrThis->name = a_argv[0];    

		snprintf(ptrThis->ref_filename, sizeof(ptrThis->ref_filename), "%s.ref",
			ptrThis->name);
		snprintf(ptrThis->in_filename,  sizeof(ptrThis->in_filename),  "%s.in",
			ptrThis->name);
		snprintf(ptrThis->out_filename, sizeof(ptrThis->out_filename), "%s.out",
			ptrThis->name);

		ptrThis->in    = fopen(ptrThis->in_filename,  "r");
		ptrThis->out   = fopen(ptrThis->out_filename, "w");
		ptrThis->err   = 0;
		ptrThis->verbose= 0;
		ptrThis->size  = 0;

		while ((c = SD_GETOPT(a_argc, a_argv, "vt")) != EOF) {
			switch(c) {
	case 'v': ptrThis->verbose = 1; break;
	case 't': ptrThis->timed   = 1; break;
	default:                     break; 
			}
		}

		ptrThis->argc = a_argc - (SD_OPTIND - 1);
		ptrThis->argv = a_argv + (SD_OPTIND - 1);
		return ptrThis;
	}

	/******************************************************************************/
	extern void sd_test_delete(sd_test_t* ptrThis)
	{
		if (!ptrThis)
			return;

		if (ptrThis->in) fclose(ptrThis->in);
		if (ptrThis->out) fclose(ptrThis->out);
		free(ptrThis->funcs);
		free(ptrThis);
	}

	/******************************************************************************/
	extern const char* sd_test_get_name(const sd_test_t* ptrThis)
	{
		return ptrThis ? ptrThis->name : NULL;
	}

	/******************************************************************************/
	extern int sd_test_get_verbose(const sd_test_t* ptrThis)
	{
		return ptrThis ? ptrThis->verbose: 0;
	}

	/******************************************************************************/
	extern int sd_test_set_verbose(sd_test_t* ptrThis, int a_verbose)
	{
		if (!ptrThis)
			return 0;

		return ptrThis->verbose = a_verbose;
	}

	/******************************************************************************/
	extern FILE* sd_test_in(sd_test_t* ptrThis)
	{
		if (!ptrThis)
			return NULL;

		return ptrThis->in ? ptrThis->in : stdin;
	}

	/******************************************************************************/
	extern FILE* sd_test_out(sd_test_t* ptrThis)
	{
		if (!ptrThis)
			return NULL;

		if (ptrThis->verbose)
			return stdout;

		return ptrThis->out ? ptrThis->out : stdout;
	}

	/******************************************************************************/
	extern FILE* sd_test_err(sd_test_t* ptrThis)
	{
		if (!ptrThis)
			return NULL;

		return ptrThis->err ? ptrThis->err : stderr;
	}

	/******************************************************************************/
	extern int sd_test_run(sd_test_t* ptrThis, int argc, char* argv[])
	{
		int i, passed = 0;

		if (!ptrThis)
			return -1;

		sd_test_add(ptrThis, test_compare);

		fprintf(sd_test_err(ptrThis), "%s: ", ptrThis->name);

		for (i = 0; i < ptrThis->size; i++) {
			int t;
			usec_t elapsed;

			fprintf(sd_test_out(ptrThis), "=> test #%d :\n", i);

			elapsed = now();
			t = (*ptrThis->funcs[i])(ptrThis, ptrThis->argc, ptrThis->argv);
			elapsed = now() - elapsed;

			fprintf(sd_test_out(ptrThis), "=> test #%d : %s\n", i, t ? " passed" : " failed");
			fflush(sd_test_out(ptrThis));

			passed += (t != 0);

			fprintf(sd_test_err(ptrThis), "%c", t ? '+' : '-');
			if (ptrThis->timed)
				fprintf(sd_test_err(ptrThis), "%lld ", elapsed);
		}

		fprintf(sd_test_err(ptrThis), " %d/%d %s.\n", passed, ptrThis->size,
			passed == ptrThis->size ? " passed" : " failed");

		return passed == ptrThis->size;
	}

	/******************************************************************************/
	extern int sd_test_add(sd_test_t* ptrThis, sd_test_func_t a_func)
	{
		if (!ptrThis)
			return -1;

		if (ptrThis->size == MAX_NFUNC)
			return ptrThis->size;

		ptrThis->funcs[ptrThis->size] = a_func;

		return ptrThis->size++;
	}

/************** End of test.c *******************************************/

/************** Begin of version.c *******************************************/
	///static const char version[] = "$Id$";

	/*
	* version.c
	*
	* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
	*
	* See the COPYING file for the terms of usage and distribution.
	*/

#ifdef HAVE_CONFIG_H
///#include "config.h"
#endif

///#include <log4c/version.h>

	const int log4c_major_version = LOG4C_MAJOR_VERSION;
	const int log4c_minor_version = LOG4C_MINOR_VERSION;
	const int log4c_micro_version = LOG4C_MICRO_VERSION;

	/*******************************************************************************/
	extern const char* log4c_version(void)
	{
		return VERSION;
	}

/************** End of version.c *******************************************/
	/************** Begin of vosnt.c *******************************************/
	/**********************************************************
	* 版权所有 (C)2001, 深圳市中兴通讯股份有限公司
	*
	* 文件名称： vosnt.c
	* 文件标识：
	* 内容摘要： VOS在WINNT下的实现，包括调度模块、通信模块、
	定时器模块、内存模块,主要实现NT下相应API函
	数的封装
	* 其它说明： 无
	* 当前版本： V 0.1
	* 作    者： 杨新
	* 完成日期： 2002年6月1日
	*
	* 修改记录1：
	*    修改日期：2003年8月20日
	*    版 本 号：V 1.0
	*    修 改 人：王泽民
	*    修改内容：VOS在NT下的适配版本整理,补充一些接口；
	* 修改记录2：…
	*    修改日期：2004年1月2日
	*    版 本 号：V 1.0
	*    修 改 人：谢鑫
	*    修改内容：VOS在NT下的消息队列适配的修改；
	* 修改记录3：…
	*    修改日期：2007年1月20日
	*    版 本 号：V 1.0
	*    修 改 人：温辉敏
	*    修改内容：增加新的VOS接口；
	**********************************************************/
	/**********************************************************
	* 函数名称： VOS_DeleteSem
	* 功能描述： 删除二进制或计数信号量
	* 输入参数： semId : 信号量标识符
	* 输出参数： 无
	* 返 回 值： VOS_OK       成功
	VOS_ERROR    失败
	* 其它说明： 无
	* 修改日期    版本号     修改人      修改内容
	* -----------------------------------------------
	* 02/08/01     V0.1       杨新        XXXX
	* 03/08/20     V1.0       王泽民      版本整合
	**********************************************************/
#ifdef WIN32
	VOS_STATUS VOS_DeleteSem(SEM_ID semId)
	{
		BOOLEAN status;

		status = CloseHandle(semId);
		if(status != 0)
		{
			return VOS_OK;
		}
		else
		{
			return VOS_ERROR;
		}
	}

	/**********************************************************
	* 函数名称： VOS_GiveSem
	* 功能描述： 释放信号量
	* 输入参数： semId : 信号量标识符
	* 输出参数： 无
	* 返 回 值： VOS_OK       成功
	VOS_ERROR    失败
	* 其它说明： 无
	* 修改日期    版本号     修改人      修改内容
	* -----------------------------------------------
	* 02/08/01     V0.1       杨新        XXXX
	* 03/08/20     V1.0       王泽民      版本整合
	**********************************************************/
	VOS_STATUS VOS_GiveSem(SEM_ID semId)
	{
		BOOLEAN status;

		status = ReleaseSemaphore(semId, 1, NULL);

		if(status != 0)
		{
			return VOS_OK;
		}
		else
		{
			return VOS_ERROR;
		}
	}

	/**********************************************************
	* 函数名称： VOS_TakeSem
	* 功能描述： 获得信号量
	* 输入参数： semId    : 信号量标识符
	timeout  : 超时毫秒数
	* 输出参数： 无
	* 返 回 值： VOS_OK       成功
	VOS_ERROR    失败
	* 其它说明： 无
	* 修改日期    版本号     修改人      修改内容
	* -----------------------------------------------
	* 02/08/01     V0.1       杨新        XXXX
	* 03/08/20     V1.0       王泽民      版本整合
	**********************************************************/
	VOS_STATUS VOS_TakeSem(SEM_ID semId, SWORD32 timeout)
	{
		WORD32 status;
		WORD32 timeLimit;

		if(timeout == -1)
		{
			timeLimit = INFINITE;
		}
		else
		{
			timeLimit = (WORD32)timeout;
		}

		status = WaitForSingleObject(semId, timeLimit);

		if(status == WAIT_OBJECT_0)
		{
			return VOS_OK;
		}
		else
		{
			return VOS_ERROR;
		}
	}

	/**********************************************************
	* 函数名称： VOS_CreateMSem
	* 功能描述： 创建互斥信号量
	* 输入参数： 阻塞任务移出阻塞队列方式
	VOS_SEM_Q_PRIORITY
	VOS_SEM_Q_FIFO
	VOS_SEM_DELETE_SAFE
	VOS_SEM_INVERSION_SAFE
	* 输出参数： 无
	* 返 回 值： MSEM_ID        成功，返回互斥信号量标识符
	NULL           失败，返回NULL
	* 其它说明： 无
	* 修改日期    版本号     修改人      修改内容
	* -----------------------------------------------
	* 02/08/01     V0.1       杨新        XXXX
	* 03/08/20     V1.0       王泽民      版本整合
	**********************************************************/
	SEM_ID VOS_CreateMSem(SWORD32 options)
	{
		SEM_ID semId;

		semId = VOS_CreateBSem(0, (VOS_SEM_STATE)1);

		return semId;
	}

	/**********************************************************
	* 函数名称： VOS_CreateBSem
	* 功能描述： 创建二进制信号量
	* 输入参数： options       : 阻塞任务移出阻塞队列方式
	VOS_SEM_Q_PRIORITY
	VOS_SEM_Q_FIFO
	initialState  : 信号量的初始状态
	VOS_SEM_FULL
	VOS_SEM_EMPTY
	* 输出参数： 无
	* 返 回 值： SEM_ID   成功，返回信号量标识符
	VOS_ERROR    失败，返回NULL
	* 其它说明： 无
	* 修改日期    版本号     修改人      修改内容
	* -----------------------------------------------
	* 02/08/01     V0.1       杨新        XXXX
	* 03/08/20     V1.0       王泽民      版本整合
	**********************************************************/
	SEM_ID VOS_CreateBSem(SWORD32 options, VOS_SEM_STATE initialState)
	{
		HANDLE semId;

		semId = CreateSemaphore(NULL, (int)initialState, 1, NULL);

		return semId;
	}

	/**********************************************************
	* 函数名称： VOS_GetSelfTaskID
	* 功能描述： 获得当前任务ID
	* 输入参数： 无
	* 输出参数： 无
	* 返 回 值： TASK_ID － 任务号
	* 其它说明： 无
	* 修改日期    版本号     修改人      修改内容
	* -----------------------------------------------
	* 03/08/20     V1.0       王泽民      XXXX
	**********************************************************/
	TASK_ID      VOS_GetSelfTaskID(VOID)
	{
		return (TASK_ID)GetCurrentThreadId();
		//return GetCurrentThread();
	}
#else
	/**********************************************************
	* 函数名称： VOS_DeleteSem
	* 功能描述： 删除二进制或计数信号量
	* 输入参数： semId : 信号量标识符
	* 输出参数： 无
	* 返 回 值： VOS_OK       成功
	VOS_ERROR    失败
	* 其它说明： 无
	* 修改日期    版本号     修改人      修改内容
	* -----------------------------------------------
	* 02/08/01     V0.1       杨新        XXXX  
	* 03/08/20     V1.0       王泽民      版本整合
	**********************************************************/
	VOS_STATUS VOS_DeleteSem(SEM_ID semId)
	{
		VOS_STATUS iResult = VOS_OK;
#ifdef PTHREAD
		if (semId != NULL)
		{
			iResult = (VOS_STATUS)sem_destroy(semId);
			free(semId);
		}
#endif

		return iResult;
	}

	/**********************************************************
	* 函数名称： VOS_GiveSem
	* 功能描述： 释放信号量
	* 输入参数： semId : 信号量标识符           
	* 输出参数： 无
	* 返 回 值： VOS_OK       成功
	VOS_ERROR    失败
	* 其它说明： 无
	* 修改日期    版本号     修改人      修改内容
	* -----------------------------------------------
	* 02/08/01     V0.1       杨新        XXXX  
	* 03/08/20     V1.0       王泽民      版本整合
	**********************************************************/
	VOS_STATUS VOS_GiveSem(SEM_ID semId)
	{
#ifdef PTHREAD
		if(sem_post(semId) == 0)
		{
			return VOS_OK;
		}
		else
		{
			return VOS_ERROR;
		}
#else
		return VOS_OK;
#endif
	}

	/**********************************************************
	* 函数名称： VOS_TakeSem
	* 功能描述： 获得信号量
	* 输入参数： semId    : 信号量标识符
	timeout  : 超时毫秒数
	* 输出参数： 无
	* 返 回 值： VOS_OK       成功
	VOS_ERROR    失败
	* 其它说明： 无
	* 修改日期    版本号     修改人      修改内容
	* -----------------------------------------------
	* 02/08/01     V0.1       杨新        XXXX  
	* 03/08/20     V1.0       王泽民      版本整合
	**********************************************************/
	VOS_STATUS VOS_TakeSem(SEM_ID semId, SWORD32 timeout)
	{
#ifdef PTHREAD
		WORD32 timeLimit;

		///printf("VOS_TakeSem begin semId:%u, timeout:%d \n", semId,  timeout);

		if(timeout == VOS_WAIT_FOREVER)
		{
			sem_wait(semId);
			return VOS_OK;
		}
		else if (timeout == 0)
		{
			if(0==sem_trywait(semId))
			{
				return VOS_OK;
			}
			else
			{
				return VOS_ERROR;
			} 
		}
		else
		{
			// use proper timed spinlocks if supported.
			// http://www.opengroup.org/onlinepubs/007904975/functions/sem_timedwait.html
			struct timeval tv;	      
			struct timespec absTime;
			gettimeofday (&tv, 0);
			absTime.tv_sec  = tv.tv_sec + timeout / 1000;
			absTime.tv_nsec = tv.tv_usec * 1000 + (timeout % 1000) * 1000000 ;          

			///printf("VOS_TakeSem semId: %u, absTime.tv_sec:%d absTime.tv_nsec:%d \n", semId, absTime.tv_sec, absTime.tv_nsec);

			if (sem_timedwait(semId, &absTime) == 0)
			{
				printf("VOS_OK \n");
				return VOS_OK;
			}
			else 
			{
				printf("VOS_ERROR \n");
				return VOS_ERROR;
			}

			printf("VOS_TakeSem semId: %u, absTime.tv_sec:%d absTime.tv_nsec:%d \n", semId, absTime.tv_sec, absTime.tv_nsec);
		}
#else
		return VOS_OK;
#endif
	}

	/**********************************************************
	* 函数名称： VOS_CreateMSem
	* 功能描述： 创建互斥信号量
	* 输入参数： 阻塞任务移出阻塞队列方式
	VOS_SEM_Q_PRIORITY
	VOS_SEM_Q_FIFO 
	VOS_SEM_DELETE_SAFE
	VOS_SEM_INVERSION_SAFE
	* 输出参数： 无
	* 返 回 值： MSEM_ID 	成功，返回互斥信号量标识符
	NULL       失败，返回NULL
	* 其它说明： 无
	* 修改日期    版本号     修改人	     修改内容
	* -----------------------------------------------
	* 02/08/01	   V1.0	      杨新	       XXXX
	**********************************************************/
	SEM_ID VOS_CreateMSem(SWORD32 options)
	{
#ifdef PTHREAD
		SEM_ID semId = (SEM_ID)malloc (sizeof(sem_t));

		if ( 0 != sem_init(semId,0,1))
		{
			return NULL;
		}

		return semId;	
#else
		return 1;
#endif
	}


	/**********************************************************
	* 函数名称： VOS_CreateBSem
	* 功能描述： 创建二进制信号量
	* 输入参数： options       : 阻塞任务移出阻塞队列方式
	VOS_SEM_Q_PRIORITY  
	VOS_SEM_Q_FIFO
	initialState  : 信号量的初始状态
	VOS_SEM_FULL
	VOS_SEM_EMPTY
	* 输出参数： 无
	* 返 回 值： SEM_ID   成功，返回信号量标识符
	VOS_ERROR    失败，返回NULL
	* 其它说明： 无
	* 修改日期    版本号     修改人      修改内容
	* -----------------------------------------------
	* 02/08/01     V0.1       杨新        XXXX  
	* 03/08/20     V1.0       王泽民      版本整合
	**********************************************************/
	SEM_ID VOS_CreateBSem(SWORD32 options, VOS_SEM_STATE initialState)
	{
		SEM_ID semId = (SEM_ID)malloc (sizeof(sem_t));

		if ( 0 != sem_init(semId,0,initialState))
		{
			return NULL;
		}

		return semId;
	}

	/**********************************************************
	* 函数名称： VOS_GetSelfTaskID
	* 功能描述： 获得任务ID
	* 输入参数： 无
	* 输出参数： 无
	* 返 回 值： TASK_ID － 任务号
	* 其它说明： 无
	* 修改日期    版本号     修改人	     修改内容
	* -----------------------------------------------
	* 02/11/21	   V1.0	      谢鑫	       XXXX
	**********************************************************/
	TASK_ID    VOS_GetSelfTaskID(VOID)
	{
		TASK_ID  dwID;

		dwID = pthread_self();    

		return dwID;
	}
#endif

/************** End of vosnt.c *******************************************/	

/************** Begin of sharedmemory.h *******************************************/
#if defined(linux)  && defined(HAVE_SHM)
	/***************************************************************************
	|sharedmemory.h|  -  sharedmemory类的头文件-声明sharedmemory类
	-------------------
	begin                : |03-6-20|
	modify               : |03-6-20|
	copyright            : (C) |YEAR| by |wenhm(温辉敏)|
	email                : |EMAIL|
	***************************************************************************/

#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#include <sys/types.h>

	//创建或关键字为Key的含有大小为size的共享内存对象，并将共享内存对象id放于shmid中返回。
	//若共享内存对象已存在则取得该对象
	extern int create_sharedmemory(key_t key, int size);

	//创建关键字Key为IPC_PRIVATE(即关键字由系统选定)的含有大小为size的共享内存对象，并将共享内存对象id放于shmid中返回。
	//因使用IPC_PRIVATE创建的共享内存的key都一样，所以key就不要了。
	extern int create_sharedmemory_private(int size);

	//将共享内存attach到进程自己得空间内，函数返回指向映射内存的指针。
	extern void *attach_sharedmemory(int shmid );

	//将共享内存disattach，唯一的参数是共享内存映射的指针
	//返回值： -1 on error: errno = EINVAL (Invalid attach address passed)
	extern int disattach_sharedmemory(void* shm);

	//获取共享内存对象shmid的大小
	extern int getsize_sharedmemory(int shmid);

	//删除共享内存对象
	extern int del_sharedmemory(int shmid);
#endif	/* SHAREDMEMORY_H */  

#endif
/************** Begin of sharedmemory.h *******************************************/

/************** Begin of sharedmemory.c *******************************************/
#if defined(linux)  && defined(HAVE_SHM)
	/***************************************************************************
	|saharedmemory.c|  -  saharedmemory共享内存对象 自己定义的一些操作函数的实现文件
	-------------------
	begin                : |03-6-20|
	modify               : |03-6-20|
	copyright            : (C) |YEAR| by |wenhm(温辉敏)|
	email                : |EMAIL|
	***************************************************************************/
	#include <stdio.h>
	#include <ctype.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/sem.h>
	#include <sys/shm.h>
	#include <errno.h>
	#include <string.h>
	///#include "sharedmemory.h"

	//创建或关键字为Key的含有大小为size的共享内存对象，并将共享内存对象id放于shmid中返回。
	//若共享内存对象已存在则取得该对象
	int create_sharedmemory(key_t key, int size)
	{
		int shmid;

		printf("Attempting to create new sharde memory object whose size is %d\n",size);
		
		//int shmget(key_t key,int size,int shmflg); 
		if((shmid = shmget(key,size,IPC_CREAT|0666)) == -1)
		{
			fprintf(stderr, "shared memory object apply error:%s!\n",strerror(errno));
		}

		return shmid;
	}

	//创建关键字Key为IPC_PRIVATE(即关键字由系统选定)的含有大小为size的共享内存对象，并将共享内存对象id放于shmid中返回。
	//因使用IPC_PRIVATE创建的共享内存的key都一样，所以key就不要了。
	int create_sharedmemory_private(int size)
	{
		int shmid;
		struct shmid_ds buf;

		printf("Attempting to create new sharde memory object whose size is %d\n",size);
		
		//int shmget(key_t key,int size,int shmflg); 
		if((shmid = shmget(IPC_PRIVATE,size,IPC_CREAT|0666)) == -1)
		{
			fprintf(stderr, "sharde memory object already exists!\n");
		}

		if(shmctl(shmid,IPC_STAT, &buf) == -1)
		{
			fprintf(stderr, "shmctl(shmid, IPC_STAT, buf) error!\n");//int shmget(key_t key,int size,int shmflg); 
		};

		return shmid;
	}

	//将共享内存attach到进程自己得空间内，函数返回指向映射内存的指针。
	void *attach_sharedmemory(int shmid )
	{
		return(shmat(shmid, 0, 0));
	}

	//将共享内存disattach，唯一的参数是共享内存映射的指针
	//返回值： -1 on error: errno = EINVAL (Invalid attach address passed)
	int disattach_sharedmemory(void* shm)
	{
		return(shmdt((char*)shm));
	}

	//获取共享内存对象shmid的大小
	int getsize_sharedmemory(int shmid)
	{
		struct shmid_ds buf;

		if(shmctl(shmid,IPC_STAT, &buf) == -1)
		{
			fprintf(stderr, "shmctl(shmid, IPC_STAT, buf) error!\n");
		};

		return buf.shm_segsz;    
	}

	//删除共享内存对象
	int del_sharedmemory(int shmid)
	{ 
		/* 共享内存对象并不随程序的结束而被删除,如果我们没删除的话(将1改为0) 
		可以用ipcs命令查看到信号灯,用ipcrm可以删除共享内存对象的*/ 
		return shmctl(shmid,IPC_RMID,0); 
	} 
#endif
	/** 获取模块使用次数
	@return long.
	*/
	long GetModuleUsage()
	{
		long lModuleUsage = -1;
#if defined(linux ) && defined(HAVE_SHM)
		//以8个8来作为共享内存的key
#define  MODULE_USAGE_SHMKEY    88888888
		gs_iModuleUsage_shmid = create_sharedmemory(MODULE_USAGE_SHMKEY, sizeof(long));
		void *ptrModuleUsageBuffer = attach_sharedmemory(gs_iModuleUsage_shmid);

		if (NULL != ptrModuleUsageBuffer)
		{
			lModuleUsage = *(long *)ptrModuleUsageBuffer;

			///释放共享内存
			disattach_sharedmemory(ptrModuleUsageBuffer);
			///del_sharedmemory(gs_iModuleUsage_shmid);
		}		
#endif
		return lModuleUsage;
	}

	/** 设置模块使用次数
	@return void.
	*/
	void SetModuleUsage(long lModuleUsage)
	{
#if defined(linux ) && defined(HAVE_SHM)
		gs_iModuleUsage_shmid = create_sharedmemory(MODULE_USAGE_SHMKEY, sizeof(long));
		void *ptrModuleUsageBuffer = attach_sharedmemory(gs_iModuleUsage_shmid);

		if (NULL != ptrModuleUsageBuffer)
		{
			*(long *)ptrModuleUsageBuffer = lModuleUsage;

			///释放共享内存
			disattach_sharedmemory(ptrModuleUsageBuffer);
			///del_sharedmemory(gs_iModuleUsage_shmid);
		}
#endif
	}

	/** 释放使用的共享内存
	@return void.
	*/
	void ReleaseModuleUsage()
	{
#if defined(linux ) && defined(HAVE_SHM)
		long lModuleUsage = 0;
		gs_iModuleUsage_shmid = create_sharedmemory(MODULE_USAGE_SHMKEY, sizeof(long));
		void *ptrModuleUsageBuffer = attach_sharedmemory(gs_iModuleUsage_shmid);

		if (NULL != ptrModuleUsageBuffer)
		{
			lModuleUsage = *(long *)ptrModuleUsageBuffer;

			///释放共享内存
			disattach_sharedmemory(ptrModuleUsageBuffer);

			if (lModuleUsage == 0)
			{
				del_sharedmemory(gs_iModuleUsage_shmid);
			}
		}
#endif
	}
/************** Begin of sharedmemory.c *******************************************/



#pragma   warning(pop) 
#endif ///  (defined(LOG_USELOG4CXX) && defined(__cplusplus) )|| defined(LOG4C_ENABLE)) && defined(IMPLEMENT_LOG4C)

/************** Begin of example.c *******************************************/
/************** End of example.c *******************************************/
__LOG4C_END_DECLS

#if (defined(LOG_USELOG4CXX) && defined(__cplusplus))
#pragma   warning(push)  
#pragma   warning(disable:4996 4090 4018) 
///#pragma   warning(once:4996) 
/************** Begin of log4c_cxxWrapper.h *******************************************/
/*
* log4c_cxxWrapper.h
*
* added by 温辉敏 in 2008-07-20
* 日志相关代码的头文件,CLog类的声明头文件
*/
#if !defined(AFX_LOG4C_CXXWRAPPER_H__4735DC75_04BF_445A_9FB0_4146D6333F85__INCLUDED_)
#define AFX_LOG4C_CXXWRAPPER_H__4735DC75_04BF_445A_9FB0_4146D6333F85__INCLUDED_


#if defined(_MSC_VER)
#pragma warning ( push )
#pragma warning ( disable: 4231 4251 4275 4786 )
#endif

///#include "config-win32.h"
///#include "log.h"
///#include "..\src\log.h"
#include <vector>
#include <wtypes.h>

/** 下面的宏定义参考自 "..\src\log4c\config-win32.h"
本来要#include "..\src\log4c\config-win32.h"
为避免包含该都文件，使用起来方便定义config-win32.h中下面的一系列宏定义
*/
#if defined(LOG4C_BUILD_DLL)
#undef LOG4C_DATA
#undef LOG4C_API
#undef LOG4C_CLASS_API

#define LOG4C_DATA			extern __declspec(dllexport)
#define LOG4C_API			__declspec(dllexport)
#define LOG4C_CLASS_API     __declspec(dllexport)

#elif defined(LOG4C_DLL)
#undef LOG4C_DATA
#undef LOG4C_API
#undef LOG4C_CLASS_API

#define LOG4C_DATA      	__declspec(dllimport)
#define LOG4C_API       	extern __declspec(dllimport)
#define LOG4C_CLASS_API 	__declspec(dllimport)
#else
#ifndef LOG4C_DATA
#define LOG4C_DATA
#endif

#ifndef LOG4C_API
#define LOG4C_API
#endif

#ifndef LOG4C_CLASS_API
#define LOG4C_CLASS_API
#endif
#endif

#include <strstream>

/**记录日志的宏定义    
*/

/**本宏定义由于无法输出对象如PTIME和CORBA::Exception& e等到输出流中，所以该用下面的宏定义
#define PTRACE(level, message) \
LOG4CXX_LOG(CLog4c::m_logger, CLog4c::toLevel(level), message)
*/

/**
日志类
为了在不同的日志记录系统之间切换定义了本日志类   
*/
///class LOG4C_CLASS_API CLog
class LOG4C_CLASS_API CLog4c
{
public:
	/** 实现Singleton模式的方法
	@return CLog4c*;	
	*/
	static CLog4c* Instance();

	/** 销毁单态对象
	@return void	
	*/
	static void DestroyInstance();

	/** CLog扫尾函数
	@return bool,true:成功,false:失败。
	*/
	bool Fini();

	/** CLog初始化函数
	这里传入一个日志配置文件名来进行初始化
	@return bool,true:成功,false:失败。
	*/
	bool Init(const std::string& strConfigFile);

	/** 静态函数,判断当前日志系统是否OK
	是否可以正常记录日志,
	1.正常进行了初始化返回true
	2.没有进行初始化返回false
	3.进行了初始化但又调用了Fini函数将返回false
	@return bool,true:成功,false:失败。
	*/
	static bool IsOK();

	/** CLog初始化函数
	这里传入一个字符串内容，根据这字符串内容来进行日志模块的初始化
	本函数的初始化过程如下：
	1.首先根据strFileContent内容生成一个日志配置文件。
	1.1.若同名配置文件存在则不作任何操作使用原来的配置文件。
	1.2.strFileName为生成的日志配置文件的名字，用户可以指定也可以采用缺省的文件名。
	2.然后调用Init函数来读取日志配置文件进行日志模块初始化工作。	
	@return bool,true:成功,false:失败。
	*/
	bool InitWithString(
		const std::string &strFileContent = "",
		const std::string &strFileName = "log4crc"
		);

	/** 将Unicode字符转换为Ansi字符
	这个指定源和目的的长度,是安全版本
	@return int.errcode of wcsncpy_s
	*/
	static int Unicode2Ansi( 
		const WCHAR *strSrc,
		const UINT &uiSrcLen,	///size in words
		char *strDst,
		const UINT &uiDstLen	///size in byte
		);

	/** 将Unicode字符转换为std::string
	这个指定源的长度,是安全版本
	@return int.errcode of wcsncpy_s
	*/
	static int Unicode2AnsiString( 
		const WCHAR *strSrc,
		const UINT &uiSrcLen,	///size in words
		std::string &strDst
		);

	/**
	将大小为count的缓冲区中内容按字节以16进制字符串打印出来,
	返回值即为指向相应的字符串，
	该返回指向的存储区域要调用本函数的用户显示的进行删除
	@return char *.
	*/
	static char * sprintf_data(char *buff, int count);

	/**将大小为count的缓冲区中内容按字节以16进制字符串打印出来,
	str缓冲区的大小应大于等于count+1,因为还要一个字节存放字符串结束符
	@return void.
	*/
	static void sprintf_data(char *str,char *buff, int count);

public:
	/**@name Construction */
	//@{
	/** CLog类中定义的枚举常量。
	*/

	///用来存储logLevel数组的最大小标值，在init()函数中初始化
	static int m_iLogLevelMaxIndex;

	///ostratream对象,PTRACE宏定义中用
	static std::ostrstream m_ostrs;

	/** 日志记录
	日志记录为一个字符串指针指向的内容
	@return void
	作者:温辉敏  日期:2008-7-20
	*/
	void LogMsg( 
		const char *strFile, 
		const int &iLineNum, 
		const int &iPriority, 
		const char *strMsg, 
		const char *strCatName
		);

	/** 日志记录,不带文件名和行号的
	日志记录为一个字符串指针指向的内容
	@return void
	作者:温辉敏  日期:2008-7-20
	*/
	void LogMsg( 
		const int &iPriority, 
		const char *strMsg, 
		const char *strCatName
		);

	/** 日志记录,不带文件名和行号的同时不附加回车换行，字符串原样输出到日志中去
	日志记录为一个字符串指针指向的内容
	@return void
	作者:温辉敏  日期:2008-7-20
	*/
	void LogMsgNoFileNumAndNoLayout( 
		const int &iPriority, 
		const char *strMsg, 
		const char *strCatName
		);

	/**获取宏定义中传入的参数形如(int , const char *, ...)的第一个iPriority的参数
	作者:温辉敏  日期:2009-4-20
	*/
	const int GetPriorityWrapper(
		const int iPriority,		///日志记录级别
		const char* strFormat,	///日志内容格式
		...						///日志内容
		);

	/**vsnprintf函数的wrapper函数
	本函数只使用第二个及以后的参数,使用vsnprintf函数将strFormat和后面的不定参数va_list va;以
	vsnprintf(strMsg, sizeof(strMsg), strFormat, va);
	形式格式化输出到一缓冲区中并以字符串的形式返回
	作者:温辉敏  日期:2009-4-20
	*/
	const char *LogVsnprintfWrapper(
		const int iPriority,	///日志记录级别
		const char* strFormat,///日志内容格式
		...					///日志内容
		);

	//////////////////////////////////////////////////////////////////////////
	///CLog4c类中的内部定义类
#ifndef TASK_ID
#ifdef _WIN32
#define TASK_ID HANDLE
#else
#define TASK_ID pthread_t
#endif
#endif
	/** Class to trace Execution blocks.
	This class is used for tracing the entry and exit of program blocks. Upon
	construction it outputs an entry trace message and on destruction outputs an
	exit trace message. This is normally only used from in the PTRACE_BLOCK macro.
	*/
	class LOG4C_CLASS_API CBlock {
	public:

		struct ST_BlockInfo
		{
			TASK_ID threadId;
			int iBlockLevel;
		};
		typedef ST_BlockInfo BlockInfo;

		///存储各线程的Block层次的Vector
		typedef std::vector<BlockInfo> BlockInfoVector;	 

		/**BlockInfo类的比较函数对象，以成员变量threadId作为比较标准
		重载的()运算符接收两个BlockInfo类的对象,比较两对象大小，
		若第一个参数小余第二个参数则返回TRUE，否则返回FALSE。  
		@return
		TRUE                         :第一个参数小余第二个参数
		FALSE						:第一个参数大于、等于第二个参数
		*/
		class CBLockInfoComparedByThreadId 
		{
		public:
			/**CContactManAscendingSortByTerState类的重载()运算符接收两个CSSModule::ContactMan的结构,比较两结构大小，
			若第一个参数等于第二个参数则返回TRUE，否则返回FALSE。  
			@return
			TRUE							:第一个参数等于第二个参数
			FALSE							:第一个参数大于、等于第二个参数
			*/
			bool operator()(
				const BlockInfo rpStart,
				const TASK_ID threadId) const
			{		
				return (rpStart.threadId == threadId);
			}

			typedef BlockInfo first_argument_type;
			typedef bool result_type;
			typedef const TASK_ID second_argument_type;
		};

	public:
		/** Output entry trace message. */
		CBlock(
			const char * fileName, /// Filename of source m_strFileName being traced
			int lineNum,           /// Line number of source m_strFileName being traced.
			const char * traceName
			/// String to be output with trace, typically it is the function m_strBlockName.
			);
		/// Output exit trace message.
		~CBlock();
	private:
		///检测threadId是的Block是否已经存在了
		BlockInfoVector::iterator FindThreadBLockInfo(TASK_ID  threadId)  ;
	private:
		const char * m_strFileName;
		int          m_iLineNum;
		const char * m_strBlockName;

		///存储各线程的Block层次的Vector
		static BlockInfoVector m_blockVector;

		///用于进行访问m_lockedInfoVector线程互斥用的
		///static CSyncPoint_Thread m_sync;
	};
	//////////////////////////////////////////////////////////////////////////

	/**日志记录函数，
	记录日志
	为了提高记录日志的效率本函数为内联函数
	*/ 
	/*目前无法使用由于message参数可能为 ("string1" << "string2")的形式而函数参数不支持这种形式
	inline static void log( const int& iLevel, ostrstream ostrs)
	{
	//ostrstream ostrs; 
	ostrs << message << ends; 
	LOG4CXX_LOG(CLog4c::m_logger, CLog4c::toLevel(iLevel), ostrs.str() ) 
	ostrs.rdbuf()->freeze(0); 
	}
	*/
private: 
	/**私有缺省构造函数。
	本缺省构造函数不让使用
	*/
	CLog4c(){};

	/**@name Access functions */
	//@{

	/**构造函数
	创建一个CLog对象。       
	*/
	CLog4c(const std::string& strConfigFile);
	//@}

	/**析构函数
	CLog对象销毁时调用。       
	*/
	~CLog4c();

	static CLog4c* m_ptrInstance;
	//@}    
};

//////////////////////////////////////////////////////////////////////////
///要导出的全局函数
LOG4C_API std::ostream & operator <<( std::ostream &stream, const WCHAR *ptrWCHAR);
LOG4C_API std::ostream & operator <<( std::ostream &stream, const std::string &strMsgUnicode);
LOG4C_API std::ostream & operator <<( std::ostream &stream, const std::wstring &strMsgUnicode);

#if defined(_MSC_VER)
#pragma warning ( pop )
#endif

#endif // !defined(AFX_LOG4C_CXXWRAPPER_H__4735DC75_04BF_445A_9FB0_4146D6333F85__INCLUDED_)
/************** End of log4c_cxxWrapper.h *******************************************/
#endif // (defined(LOG_USELOG4CXX) && defined(__cplusplus))

#if (defined(LOG_USELOG4CXX) && defined(__cplusplus))&& defined(IMPLEMENT_LOG4C)
/************** Begin of log4c_cxxWrapper.cpp *******************************************/
/*
* log4c_cxxWrapper.cpp
*
* added by 温辉敏 in 2008-07-20
* 日志相关代码的定义文件,CLog类的实现文件
*/
///#include "config_log.h"

///#include "GlobalMacro.h"
///#include "../vos/include/vos.h"
///#include "log.h"
///#include "log4c_cxxWrapper.h"
///#include "sd\sd_xplatform.h"
///#include "sd\sprintf.h"
#include <algorithm>
#include <functional>
#include <assert.h>

static SEM_ID g_semphore = VOS_CreateMSem(VOS_SEM_Q_FIFO);

///静态成员变量定义
std::ostrstream CLog4c::m_ostrs;

///存储各线程的Block层次的Vector
CLog4c::CBlock::BlockInfoVector CLog4c::CBlock::m_blockVector;

CLog4c* CLog4c::m_ptrInstance = NULL;

CLog4c* CLog4c::Instance()
{
	/// Perform Double-Checked Locking Optimization.懒汉模式
	if (NULL != m_ptrInstance)
	{
		return m_ptrInstance;
	}
	else
	{
		///static SEM_ID semphore = NULL;

		///为线程安全这里加锁，[2/15/2008 温辉敏]
		VOS_TakeSem(g_semphore, VOS_WAIT_FOREVER);

		///CLockMgr<CCSWrapper> guard(m_lock, FALSE);
		if (NULL != m_ptrInstance)
		{
			// 解锁 [2/15/2008 温辉敏]
			VOS_GiveSem(g_semphore);
			return m_ptrInstance;			
		}
		else
		{			
			m_ptrInstance = new CLog4c();
			// m_ptrInstance->Init("");
			// 解锁 [2/15/2008 温辉敏]
			VOS_GiveSem(g_semphore);
			return m_ptrInstance;
		}
	}
}

void CLog4c::DestroyInstance()
{
	///CLockMgr<CCSWrapper> guard(m_lock, TRUE);
	///为线程安全这里加锁，[2/15/2008 温辉敏]
	VOS_TakeSem(g_semphore, VOS_WAIT_FOREVER);

	DELETEP(m_ptrInstance);

	// 解锁 [2/15/2008 温辉敏]
	VOS_GiveSem(g_semphore);

	// 删除资源 [4/18/2009 温辉敏]
	VOS_DELETE_SEM(g_semphore)
		///VOS_DeleteSem(g_semphore);
}

void CLog4c::LogMsg( 
					const char *strFile, 
					const int &iLineNum, 
					const int &iPriority, 
					const char *strMsg, 
					const char *strCatName
					)
{
	///调用log4c的函数来记录日志
	log_msg(strFile, iLineNum, strCatName, iPriority, strMsg);
}

void CLog4c::LogMsg( 
					const int &iPriority, 
					const char *strMsg, 
					const char *strCatName
					)
{
	///调用log4c的函数来记录日志
	log_msg_no_file_num(strCatName, iPriority, strMsg);
}

void CLog4c::LogMsgNoFileNumAndNoLayout( 
										const int &iPriority, 
										const char *strMsg, 
										const char *strCatName
										)
{
	///调用log4c的函数来记录日志
	log_msg_no_file_num_no_layout(strCatName, iPriority, strMsg);
}

CLog4c::CLog4c(const std::string& strConfigFile)
{
	Init(strConfigFile);	
}

bool CLog4c::Init(const std::string& strConfigFile)
{
	bool bResult = false;
	int iResult = -1;

	///调用log4c的函数来初始化日志
	if (strConfigFile.length() > 0)
	{
		iResult = log_init_with_cfg_file(strConfigFile.c_str());
	}

	if ( 0 != iResult)
	{
		iResult = log_init();
	}

	bResult = (0 == iResult);

	return bResult;
}

bool CLog4c::Fini()
{
	int iResult = log_fini();

	return (0 == iResult);
}

CLog4c::~CLog4c()
{
	Fini();
}

bool CLog4c::IsOK()
{
	bool bResult = (NULL != m_ptrInstance);

	return bResult;
}

//////////////////////////////////////////////////////////////////////////
static char gs_strFileContentInCxx[] = 
"<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
"<!DOCTYPE log4c SYSTEM \"\">\n"
"\n"
"<log4c version=\"1.2.1\">\n"
"	<config>\n"
"		<bufsize>0</bufsize>\n"
"		<debug level=\"2\"/>\n"
"		<nocleanup>0</nocleanup>\n"
"		<reread>1</reread>\n"
"	</config>\n"
"\n"
"	<category name=\"root\" priority=\"notice\"  appender=\"aname\"/>\n"
"\n"
"	<rollingpolicy name=\"a_policy_name\" type=\"sizewin\" maxsize=\"1048576\" maxnum=\"15\" />\n"
"	<appender name=\"aname\" type=\"rollingfile\"  logdir=\".\" prefix=\"log\" layout=\"dated_threadid\" rollingpolicy=\"a_policy_name\" />\n"
"\n"
"	<appender name=\"stdout\" type=\"stream\" layout=\"dated_threadid\"/>\n"
"	<appender name=\"stderr\" type=\"stream\" layout=\"dated\"/>\n"
"	<appender name=\"syslog\" type=\"syslog\" layout=\"basic\"/>\n"
"</log4c>\n";

static char gs_strDefualtFileNameInCxx[] = "log4crc";

bool CLog4c::InitWithString(
							const std::string &strFileContent,
							const std::string &strFileName 
							)
{
	std::string strLocalFileContent = (strFileContent.length() > 0 ? strFileContent:gs_strFileContentInCxx);
	std::string strLocalFileName = (strFileName.length() > 0 ? strFileName:gs_strDefualtFileNameInCxx);

	/**
	若文件已存在则不重新生成配置文件了
	否则生成新的配置文件
	*/
	if (LOG4C_OK != SD_ACCESS_READ(strLocalFileName.c_str()))
	{
		///文件不存在新建
		FILE *file = fopen(strLocalFileName.c_str(), "wb");	
		if (NULL != file)
		{
			fwrite(strLocalFileContent.c_str(), 1, strLocalFileContent.length(), file);
			fclose(file);
		}		
	}
	else
	{
		///文件存在,do nothing，使用原来的配置文件就OK了。
	}	

	//////////////////////////////////////////////////////////////////////////	
	///调用Init函数进行实际的日志模块初始化工作
	bool bResult = Init(strLocalFileName.c_str());

	return bResult;
}

int CLog4c::Unicode2Ansi( 
						 const WCHAR *strSrc,
						 const UINT &uiSrcLen,	///size in words
						 char *strDst,
						 const UINT &uiDstLen	///size in byte
						 )
{
	///输入参数有效性检查
	PAssertNotNull_Statement_ReturnWithValue(strSrc, assert(0), LOG4C_FAILURE);
	PAssertNotNull_Statement_ReturnWithValue(strDst, assert(0), LOG4C_FAILURE);

	///清零先
	memset(strDst, 0, uiDstLen);

	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, 
		strSrc, uiSrcLen,  strDst, uiDstLen, NULL, NULL);

	return LOG4C_OK;
}

int CLog4c::Unicode2AnsiString( 
							   const WCHAR *strSrc,
							   const UINT &uiSrcLen,	///size in words
							   std::string &strDst
							   )
{
	///输入参数有效性检查
	PAssertNotNull_Statement_ReturnWithValue(strSrc, assert(0), LOG4C_FAILURE);

	///unicode一个字符转换为UTF8时最多可能转换为6个字节,这里虽然转换为Ansi但也采用6个字节
	UINT uiDstLen = 6*uiSrcLen + 1;
	char *ptrBuffer = new char[uiDstLen];
	memset(ptrBuffer, 0, uiDstLen);

	Unicode2Ansi(strSrc, uiSrcLen, ptrBuffer, uiDstLen);

	strDst = ptrBuffer;

	DELETEA(ptrBuffer);

	return LOG4C_OK;
}

/**
将大小为count的缓冲区中内容按字节以16进制字符串打印出来,
返回值即为指向相应的字符串，
该返回指向的存储区域要调用本函数的用户显示的进行删除
*/
char * CLog4c::sprintf_data(char *buff, int count)
{
	int i,j,c;
	int printnext=1;
	char str[10] = {0};///由于这里要进行格式输出如"%.4x "等，这里给出10个字符作为格式输出冗余
	//使用ostrstream的代码，但ostrstream.str()传出去要使用者负责清除ostrstream.str()指向的内存了
	std::ostrstream ostr;	
	if(count)
	{
		if(count%16)
		{
			c=count+(16-count%16);
		}
		else 
		{
			c=count;
		}
	}
	else
	{
		c=count;
	}

	for(i=0;i<c;i++)
	{
		if(printnext) 
		{ 
			printnext--;
#ifdef WIN32
			_snprintf(str, sizeof(str), "%.4x ",i&0xffff); 
#else
			snprintf(str, sizeof(str), "%.4x ",i&0xffff); 
#endif
			ostr << str;
		}

		if(i<count)
		{
#ifdef WIN32
			_snprintf(str, sizeof(str),"%3.2x",buff[i]&0xff);
#else
			snprintf(str, sizeof(str),"%3.2x",buff[i]&0xff);
#endif
			ostr << str;
		}
		else
		{
#ifdef WIN32
			_snprintf(str, sizeof(str), "   ");
#else
			snprintf(str, sizeof(str), "   ");
#endif
			ostr << str;
		}

		if(!((i+1)%8))
		{
			if((i+1)%16)
			{
#ifdef WIN32
				_snprintf(str,  sizeof(str), " -");
#else
				snprintf(str,  sizeof(str), " -");
#endif
				ostr << str;
			}
			else
			{
#ifdef WIN32
				_snprintf(str, sizeof(str), "   ");
#else
				snprintf(str, sizeof(str), "   ");
#endif
				ostr << str;
				for(j=i-15;j<=i;j++)
				{
					if(j<count) 
					{
						if( (buff[j]&0xff) >= 0x20 && 
							(buff[j]&0xff)<=0x7e)
						{
#ifdef WIN32
							_snprintf(str, sizeof(str), "%c",buff[j]&0xff);
#else
							snprintf(str, sizeof(str), "%c",buff[j]&0xff);
#endif
							ostr << str;
						}
						else 
						{
#ifdef WIN32
							_snprintf(str, sizeof(str), ".");
#else
							snprintf(str, sizeof(str), ".");
#endif
							ostr << str;
						}
					} 
					else 
					{
#ifdef WIN32
						_snprintf(str, sizeof(str), " ");
#else
						snprintf(str, sizeof(str), " ");
#endif
						ostr << str;
					}
				}
#ifdef WIN32
				_snprintf(str, sizeof(str), "\n");     
#else
				snprintf(str, sizeof(str), "\n");   
#endif
				ostr << str; 
				printnext=1;      
			}
		}
	}


	/**
	ostrstreams 没有为我们插入一般在字符数组末尾所需要的零终止符，
	当我们准备好零终止符时，用特别操作算子ends。
	*/
	ostr << std::ends;
	return ostr.str();
	/*
	strncpy(str, ostr.str(), count );
	str[count ] = '\0';
	ostr.rdbuf()->freeze(0);
	*/
}

//将大小为count的缓冲区中内容按字节以16进制字符串打印出来,str缓冲区的大小应大于等于count+1,因为还要一个字节存放字符串结束符
void CLog4c::sprintf_data(char *str,char *buff, int count)
{
	char *ptrStr = sprintf_data(buff, count);

	strncpy_s(str, count, ptrStr, count );
	str[count ] = '\0';
	DELETEA(ptrStr);
}

const int CLog4c::GetPriorityWrapper(
									 const int iPriority,		///日志记录级别
									 const char* strFormat,	///日志内容格式
									 ...						///日志内容
									 )
{
	return iPriority;
}

const char *CLog4c::LogVsnprintfWrapper(
										const int iPriority,	///日志记录级别
										const char* strFormat,///日志内容格式
										...					///日志内容
										)
{
	const char * strMsg = NULL;
	va_list va;
	va_start(va, strFormat);
	{	
		strMsg = sd_vsprintf( strFormat, va);		
	}
	va_end(va);

	return strMsg;
}

//////////////////////////////////////////////////////////////////////////
///CLog4c::CBlock的实现方法:
CLog4c::CBlock::CBlock(const char * fileName, int lineNum, const char * traceName)
{
	/*要访问m_BlockInfoVector了，要加锁进行互斥访问,
	由于下面可能有wait操作可能会堵住，为防止死锁，
	所以这里只能分两部进行局部加锁，将wait的语句放于该锁管辖范围之外
	*/
	///CWaitAndSignal sync(m_sync);
	///为线程安全这里加锁，[9/15/2008 温辉敏]
	VOS_TakeSem(g_semphore, VOS_WAIT_FOREVER);

	m_strFileName = fileName;
	m_iLineNum = lineNum;
	m_strBlockName = traceName;

	///if ((PTraceOptions&Blocks) != 0) 
	{
		TASK_ID threadId = VOS_GetSelfTaskID();
		int iBlockId;

		///查找waitThread线程是否已经对本信号量加过锁了
		BlockInfoVector::iterator iter =  FindThreadBLockInfo(threadId);

		if(iter != m_blockVector.end())
		{	///本线程Block层次加2
			iter->iBlockLevel += 2;
			iBlockId = iter->iBlockLevel;
		}
		else
		{
			///本线程Block层次还没有
			BlockInfo blockInfo = {0};
			blockInfo.threadId = threadId;
			blockInfo.iBlockLevel += 2;

			m_blockVector.push_back(blockInfo);

			iBlockId = blockInfo.iBlockLevel;
		}

		std::ostrstream ostrs;
		ostrs << "B-Entry\t";
		for (int i = 0; i < iBlockId; i++)
		{
			ostrs << "=";
		}

		ostrs << "> " << m_strBlockName /*<< " ThreadId:" << threadId*/ << std::ends;

		///调用log4c的函数来记录日志
		log_msg(m_strFileName, m_iLineNum, "", LOG4C_PRIORITY_TRACE, ostrs.str());

		///释放内存
		ostrs.rdbuf()->freeze(0);
	}

	///释放信号量
	VOS_GiveSem(g_semphore);
}

CLog4c::CBlock::~CBlock()
{
	/**当在全局或main函数中定义的CBlock对象时
	执行CBlock析构函数时可能是在退出main函数时,而此时可能已经销毁了日志系统
	此时再执行log_msg函数将导致内存泄漏所以这里加上日志系统是否正常的判断代码
	*/
	if (true == CLog4c::IsOK())
	{
		/*要访问m_BlockInfoVector了，要加锁进行互斥访问,
		由于下面可能有wait操作可能会堵住，为防止死锁，
		所以这里只能分两部进行局部加锁，将wait的语句放于该锁管辖范围之外
		*/
		///CWaitAndSignal sync(m_sync);
		///为线程安全这里加锁，[9/15/2008 温辉敏]
		VOS_TakeSem(g_semphore, VOS_WAIT_FOREVER);

		///if ((PTraceOptions&Blocks) != 0)
		{
			//    PThread * thread = PThread::Current();
			TASK_ID   threadId = VOS_GetSelfTaskID();

			///查找waitThread线程是否已经对本信号量加过锁了
			BlockInfoVector::iterator iter =  FindThreadBLockInfo(threadId);

			if(iter != m_blockVector.end())
			{	

				std::ostrstream ostrs;
				ostrs << "B-Exit\t<";

				for (int i = 0; i < iter->iBlockLevel; i++)
				{
					ostrs << "=";
				}

				ostrs << " "<< m_strBlockName /*<< " ThreadId:" << threadId */ << std::ends;

				///调用log4c的函数来记录日志
				log_msg(m_strFileName, m_iLineNum, "", LOG4C_PRIORITY_TRACE, ostrs.str());

				///释放内存
				ostrs.rdbuf()->freeze(0);

				///本线程Block层次加2
				iter->iBlockLevel -= 2;

				///Block层次为0将该线程相关的Block信息删除
				if(iter->iBlockLevel == 0)
				{
					m_blockVector.erase(iter);
				}
			}
		}

		///释放信号量
		VOS_GiveSem(g_semphore);
	}	
}

///检测threadId是的Block是否已经存在了
CLog4c::CBlock::BlockInfoVector::iterator CLog4c::CBlock::FindThreadBLockInfo(TASK_ID  threadId)  
{
	BlockInfoVector::iterator iter =
		std::find_if(m_blockVector.begin(), m_blockVector.end(),
		std::bind2nd(CBLockInfoComparedByThreadId(), threadId));

	return iter;
}

///////////////////////////////////////////////////////////////////////////
///对流输出ostream的<<运算符重载函数
std::ostream & operator <<( std::ostream &stream, const WCHAR *ptrWCHAR)
{
	PAssertNotNull_ReturnWithValue(ptrWCHAR, stream);

	std::string strMsg;

	CLog4c::Unicode2AnsiString(ptrWCHAR, wcslen(ptrWCHAR), strMsg);

	stream << strMsg.c_str();

	return stream;
}

std::ostream & operator <<( std::ostream &stream, const std::string &strMsg)
{	
	stream << strMsg.c_str();

	return stream;
}

std::ostream & operator <<( std::ostream &stream, const std::wstring &strMsgUnicode)
{
	std::string strMsg;

	CLog4c::Unicode2AnsiString(strMsgUnicode.c_str(), strMsgUnicode.length(), strMsg);

	stream << strMsg.c_str();

	return stream;
}
///#endif

/************** End of log4c_cxxWrapper.cpp *******************************************/
#pragma   warning(pop) 
#endif ///(defined(LOG_USELOG4CXX) && defined(__cplusplus))&& defined(IMPLEMENT_LOG4C)

#endif ///(defined(LOG_USELOG4CXX) && defined(__cplusplus)) || defined(LOG4C_ENABLE)

#endif // !defined(AFX_LOG4C_AMALGAMATION_H__DD58A78D_C125_410F_B4C8_F0067B797121__INCLUDED_)



