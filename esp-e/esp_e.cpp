#include "elib_h/elib.h"
#include "../esp-core/esp_clientapi.h"
#include "Global_functions.hpp"
#include "os.h"

/*
	��֧�ֿ⽫��̬���� mod_esp.so �������䵼������������ɺ��Ĺ��ܡ�
�������Ա�֤��֧�ֿⲻֱ������ mod_esp.so, libhttpd.dll, libapr.dll��
����ڿ����ڿɱ���IDE�������أ����������ڣ�������������Apache�����У�
������̬�ⶼ��Ȼ���ڡ�

	�� mod_esp.so ������ʱ������д�����̻������� "ESP_MOD_FILE_PATH"��
�Ա��ڱ�֧�ֿⶨλ�����������������ڷ�Apache������ʱ����֧�ֿ⽫��Ϊ
�Ҳ��� mod_esp.so ����ִ���κι��ܣ����˱�����

*/

//=============================================================================
// ֧�ֿⶨ�忪ʼ

#ifndef __E_STATIC_LIB

LIB_DATA_TYPE_ELEMENT s_ESPPropTypes_Elements[] = 
{
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("��"),
		/*m_szEgName*/	_WT("null"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_NULL,
	},
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("�߼�"),
		/*m_szEgName*/	_WT("bool"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_BOOL,
	},
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("����"),
		/*m_szEgName*/	_WT("int"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_INT,
	},
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("������"),
		/*m_szEgName*/	_WT("int64"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_INT64,
	},
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("С��"),
		/*m_szEgName*/	_WT("float"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_FLOAT,
	},
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("˫����С��"),
		/*m_szEgName*/	_WT("double"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_DOUBLE,
	},
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("�ı�"),
		/*m_szEgName*/	_WT("text"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_TEXT,
	},
	{
		/*m_dtType*/	SDT_INT,
		/*m_pArySpec*/	NULL,
		/*m_szName*/	_WT("�ֽڼ�"),
		/*m_szEgName*/	_WT("binary"),
		/*m_szExplain*/	_WT(""),
		/*m_dwState*/	LES_HAS_DEFAULT_VALUE,
		/*m_nDefault*/	ESPPropType_BINARY,
	},
};

//���������б�
LIB_DATA_TYPE_INFO s_DataType[]=
{
    {
	/*m_szName*/			_T("ESP_��������"),
	/*m_szEgName*/			_T("ESP_PropTypes"),
	/*m_szExplain*/			_WT("������ʾ���Ե���������"),
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
//*** ����������Ϣ:
// !!! ע�ⳣ��ֵ�����Ѿ����õ������У�����˳��ֵ���Բ��ܸĶ���

LIB_CONST_INFO s_ConstInfo [] =
{
	{_WT("֧�ֿ����"),_WT("LibAlias"),NULL,LVL_SIMPLE,CT_TEXT,_T("modesp"),0,},

};


///////////////////////////////////////////////////////////////////////////////
// ���е���������б�

static CMD_INFO s_CmdInfo[] =
{
	ESP_All_CmdInfos
};


///////////////////////////////////////////////////////////////////////////////
// ���е��������ִ�к�����

PFN_EXECUTE_CMD s_RunFunc [] =	// ����Ӧ��s_CmdInfo�е������˳���Ӧ
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
// �ⶨ�忪ʼ
static char* s_szInfo = "This is a runtime library file for EPL applications. The EPL is a software development environment. For details please visit www.dywt.com.cn/info";

LIB_INFO s_LibInfo =
{
/*Lib Format Ver*/		LIB_FORMAT_VER,		// ����δ�á�

// ��֧�ֿ��GUID��
#define		LI_LIB_GUID_STR	"{86411A2C-F0F2-41fa-9359-61DD39B83367}"
/*guid str*/			_T (LI_LIB_GUID_STR),

/*m_nMajorVersion*/		1,
/*m_nMinorVersion*/		0,
/*m_nBuildNumber*/		0,

/*m_nRqSysMajorVer*/		3,
/*m_nRqSysMinorVer*/		8,
/*m_nRqSysKrnlLibMajorVer*/	3,
/*m_nRqSysKrnlLibMinorVer*/	0,

/*name*/				_T ("ESP֧�ֿ�"),
/*lang*/				__COMPILE_LANG_VER,
/*explain*/				_WT("���WEB�������ġ�ESPģ��/�������ϣ����ڿ���B/S�ܹ�WEBӦ�ó���"),
/*dwState*/				_LIB_OS(__OS_WIN|__OS_LINUX),

/*szAuthor*/	_WT("������������������������޹�˾"),
/*szZipCode*/	_WT("116001"),
/*szAddress*/	_WT("����ʡ��������ɽ������·55����̫���ʽ�������"),
/*szPhoto*/		_WT("+86(0411)39895831"),
/*szFax*/		_WT("+86(0411)39895834"),
/*szEmail*/		_WT("service@dywt.com.cn"),
/*szHomePage*/	_WT("http://esp.eyuyan.com"),
/*szOther*/		_WT("ף��һ����˳�������³ɣ�"),

/*type count*/			sizeof(s_DataType) / sizeof(s_DataType[0]),
/*PLIB_DATA_TYPE_INFO*/	s_DataType,

/*CategoryCount*/ 6,	// ���������Ӵ�ֵ��
/*category*/// ���˵����ÿ��Ϊһ�ַ���,ǰ��λ���ֱ�ʾͼ��������(��1��ʼ,0��).
			_T(
            "0000����\0"
			"0000����\0"
			"0000�Ự\0"
            "0000����\0"
            "0000��Ⱦ\0"
			"0000����\0"
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


// ֧�ֿⶨ�����
//=============================================================================

#endif

/////////////////////////////////////////////////////////////////////////////
//��������

#ifndef __E_STATIC_LIB

PLIB_INFO WINAPI GetNewInf ()
{
	return &s_LibInfo;
}

#endif

//ȫ�ֱ���
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
			OS_FreeLibrary(modespHandle); //��Ϊmod_esp.so��Ȼ�ѱ�Apache���أ��������ﲻ�ᵼ����������ж��
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

//������ȫ�ֱ����Ĺ��캯���ڱ������֮����ʼ��ESP Client API
class InitESPLib
{
public:
	InitESPLib() { LoadESPClientAPI(); }
} initer;
