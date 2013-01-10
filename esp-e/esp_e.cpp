#include "elib_h/elib.h"
#include "../esp-core/esp_clientapi.h"
#include "Global_functions.hpp"
#include "os.h"

/*
	本支持库将动态加载 mod_esp.so 并调用其导出函数，以完成核心功能。
这样可以保证本支持库不直接依赖 mod_esp.so, libhttpd.dll, libapr.dll，
因而在开发期可被易IDE正常加载，而在运行期，由于是运行于Apache进程中，
上述动态库都必然存在。

	在 mod_esp.so 被加载时，它将写本进程环境变量 "ESP_MOD_FILE_PATH"，
以便于本支持库定位并加载它。在运行于非Apache环境中时，本支持库将因为
找不到 mod_esp.so 而不执行任何功能（除了报错）。

*/

//=============================================================================
// 支持库定义开始

#ifndef __E_STATIC_LIB

LIB_DATA_TYPE_ELEMENT s_ESPPropTypes_Elements[] = 
{
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("空"),
		/*m_szEgName*/	_WT("null"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_NULL,
	},
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("逻辑"),
		/*m_szEgName*/	_WT("bool"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_BOOL,
	},
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("整数"),
		/*m_szEgName*/	_WT("int"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_INT,
	},
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("长整数"),
		/*m_szEgName*/	_WT("int64"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_INT64,
	},
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("小数"),
		/*m_szEgName*/	_WT("float"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_FLOAT,
	},
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("双精度小数"),
		/*m_szEgName*/	_WT("double"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_DOUBLE,
	},
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("文本"),
		/*m_szEgName*/	_WT("text"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_TEXT,
	},
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("字节集"),
		/*m_szEgName*/	_WT("binary"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_BINARY,
	},
};

//数据类型列表
LIB_DATA_TYPE_INFO s_DataType[]=
{
    {
	/*m_szName*/			_T("ESP_属性类型"),
	/*m_szEgName*/			_T("ESP_PropTypes"),
	/*m_szExplain*/			_WT("用作表示属性的数据类型"),
	/*m_nCmdCount*/			0,
	/*m_pnCmdsIndex*/		NULL,
	/*m_dwState*/			LDT_ENUM | _DT_OS(__OS_WIN|__OS_LINUX),
	/*m_dwUnitBmpID*/		0,
	/*m_nEventCount*/		0,
	/*m_pEventBegin*/		NULL,
	/*m_nPropertyCount*/	0,
	/*m_pPropertyBegin*/	NULL,
	/*m_pfnGetInterface*/	NULL,
	/*m_nElementCount*/		sizeof(s_ESPPropTypes_Elements) / sizeof(s_ESPPropTypes_Elements[0]),
	/*m_pElementBegin*/		s_ESPPropTypes_Elements,
	},
};



///////////////////////////////////////////////////////////////////////////////
//*** 常量定义信息:
// !!! 注意常量值由于已经运用到程序中，所以顺序及值绝对不能改动。

LIB_CONST_INFO s_ConstInfo [] =
{
	{_WT("支持库代号"),_WT("LibAlias"),NULL,LVL_SIMPLE,CT_TEXT,_T("modesp"),0,},

};


///////////////////////////////////////////////////////////////////////////////
// 所有的命令及方法列表

static CMD_INFO s_CmdInfo[] =
{
	ESP_All_CmdInfos
};


///////////////////////////////////////////////////////////////////////////////
// 所有的命令及方法执行函数表

PFN_EXECUTE_CMD s_RunFunc [] =	// 索引应与s_CmdInfo中的命令定义顺序对应
{
	ESP_All_functions
};

#endif

EXTERN_C INT WINAPI esp_ProcessNotifyLib (INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
#ifndef __E_STATIC_LIB
	if(nMsg == NL_GET_CMD_FUNC_NAMES)
		return (INT) _GetCmdNames();
	else if(nMsg == NL_GET_NOTIFY_LIB_FUNC_NAME)
		return (INT) "esp_ProcessNotifyLib";
	else if(nMsg == NL_GET_DEPENDENT_LIBS)
		return (INT) NULL;
#endif
	return ProcessNotifyLib(nMsg, dwParam1, dwParam2);
}

#ifndef __E_STATIC_LIB

///////////////////////////////////////////////////////////////////////////////
// 库定义开始
static char* s_szInfo = "This is a runtime library file for EPL applications. The EPL is a software development environment. For details please visit www.dywt.com.cn/info";

LIB_INFO s_LibInfo =
{
/*Lib Format Ver*/		LIB_FORMAT_VER,		// 保留未用。

// 本支持库的GUID串
#define		LI_LIB_GUID_STR	"{86411A2C-F0F2-41fa-9359-61DD39B83367}"
/*guid str*/			_T (LI_LIB_GUID_STR),

/*m_nMajorVersion*/		1,
/*m_nMinorVersion*/		0,
/*m_nBuildNumber*/		0,

/*m_nRqSysMajorVer*/		3,
/*m_nRqSysMinorVer*/		8,
/*m_nRqSysKrnlLibMajorVer*/	3,
/*m_nRqSysKrnlLibMinorVer*/	0,

/*name*/				_T ("ESP支持库"),
/*lang*/				__COMPILE_LANG_VER,
/*explain*/				_WT("与各WEB服务器的“ESP模块/插件”配合，用于开发B/S架构WEB应用程序。"),
/*dwState*/				_LIB_OS(__OS_WIN|__OS_LINUX),

/*szAuthor*/	_WT("大有吴涛易语言软件开发有限公司"),
/*szZipCode*/	_WT("116001"),
/*szAddress*/	_WT("辽宁省大连市中山区人民路55号亚太国际金融中心"),
/*szPhoto*/		_WT("+86(0411)39895831"),
/*szFax*/		_WT("+86(0411)39895834"),
/*szEmail*/		_WT("service@dywt.com.cn"),
/*szHomePage*/	_WT("http://esp.eyuyan.com"),
/*szOther*/		_WT("祝您一帆风顺，心想事成！"),

/*type count*/			sizeof(s_DataType) / sizeof(s_DataType[0]),
/*PLIB_DATA_TYPE_INFO*/	s_DataType,

/*CategoryCount*/ 6,	// 加了类别需加此值。
/*category*/// 类别说明表每项为一字符串,前四位数字表示图象索引号(从1开始,0无).
			_T(
            "0000对象\0"
			"0000属性\0"
			"0000会话\0"
            "0000请求\0"
            "0000渲染\0"
			"0000其它\0"
            "\0"),
/*CmdCount*/				sizeof (s_CmdInfo) / sizeof (s_CmdInfo [0]),
/*BeginCmd*/				s_CmdInfo,
/*m_pCmdsFunc*/             s_RunFunc,
/*pfnRunAddInFn*/			NULL,
/*szzAddInFnInfo*/			"",

/*pfnNotify*/				esp_ProcessNotifyLib,

/*pfnRunSuperTemplate*/		NULL,
/*szzSuperTemplateInfo*/	NULL,

/*nLibConstCount*/			0, //sizeof (s_ConstInfo) / sizeof (s_ConstInfo [0]),
/*pLibConst*/				NULL, //s_ConstInfo,

/*szzDependFiles*/			NULL,
};


// 支持库定义结束
//=============================================================================

#endif

/////////////////////////////////////////////////////////////////////////////
//导出函数

#ifndef __E_STATIC_LIB

PLIB_INFO WINAPI GetNewInf ()
{
	return &s_LibInfo;
}

#endif

//全局变量
static const ESPClientAPI* g_pESPFuncs = NULL;

static void LoadESPClientAPI()
{
	if(g_pESPFuncs) return;

	char* szESPModuleFilePath = getenv(ENV_NAME_OF_ESP_MOD_FILE_PATH);
	if(szESPModuleFilePath)
	{
		int modespHandle = OS_LoadLibrary(szESPModuleFilePath);
		if(modespHandle != 0)
		{
			PFN_ESP_GetClientAPI pfnGetESPClientAPI = NULL;
			pfnGetESPClientAPI = (PFN_ESP_GetClientAPI) OS_GetProcAddress(modespHandle, FUNC_NAME_OF_ESP_GetClientAPI);
			if(pfnGetESPClientAPI)
			{
				g_pESPFuncs = pfnGetESPClientAPI();
			}
			OS_FreeLibrary(modespHandle); //因为mod_esp.so必然已被Apache加载，所以这里不会导致它被真正卸载
		}
	}

#ifdef _DEBUG
	const char* errmsg = "***[error]: ESP runtime is NOT available! Are the web server and it's esp module working?\r\n";
	#ifdef _WIN32 
		if(g_pESPFuncs == NULL)
			::OutputDebugStringA(errmsg);
	#endif
	if(g_pESPFuncs == NULL)
		fprintf(stderr, "%s", errmsg);
#endif
}

bool IsESPRuntimeAvailable()
{
	return (g_pESPFuncs != NULL);
}

//借助于全局变量的构造函数在本库加载之初初始化ESP Client API
class InitESPLib
{
public:
	InitESPLib() { LoadESPClientAPI(); }
} initer;
