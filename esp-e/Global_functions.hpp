#ifndef GLOBAL_FUNCTION_HPP
#define GLOBAL_FUNCTION_HPP

#include <assert.h>
#include "esp_e.h"

#define CMD_SUPPORT_OS  _CMD_OS(__OS_WIN|__OS_LINUX)
#define LIB_TYPE(i) (i)

//-----------------------------------------------------------------------------
// ��̬�������

class CFreqMem
{
private:
	unsigned char* m_pdata;
	size_t m_datalen, m_bufferlen;
public:
	CFreqMem()
	{
		m_pdata = NULL; m_datalen = m_bufferlen = 0;
	}
	void* GetPtr()
	{
		return (m_datalen == 0 ? NULL : m_pdata);
	}
	void AddDWord(DWORD dw)
	{
		AppendData(&dw, sizeof(dw));
	}
	void AppendData(void* pdata, size_t size)
	{
		if(m_bufferlen - m_datalen < size)
		{
			if(m_pdata == NULL)
			{
				m_bufferlen = 128;
				m_pdata = (unsigned char*) malloc(m_bufferlen);
				//assert(m_datalen == 0);
			}
			while(m_bufferlen - m_datalen < size)
			{
				m_bufferlen *= 2;
			};
			m_pdata = (unsigned char*) realloc(m_pdata, m_bufferlen);
		}
		memcpy(m_pdata + m_datalen, pdata, size);
		m_datalen += size;
	}
};

#ifdef __cplusplus
	#define EXTERN_C extern "C" 
#else
	#define EXTERN_C 
#endif

#define DEFINE_ESP_EXECUTE_CMD(fnName) \
	EXTERN_C void esp##_##fnName (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)


#if defined(__E_STATIC_LIB) || defined(__COMPILE_FNR)

	#define ESP_CMD(name)  esp_##name  // ���ڲ�ͬ�Ŀ�, ������Ӧ�������޸�
	#define ESP_NULL_CMD(name)  NULL

#else if defined(__cplusplus)

    static CFreqMem _g_CmdNames;

    static PFN_EXECUTE_CMD _RecordCmdName (PFN_EXECUTE_CMD func, const TCHAR* szFuncName)
    {
        _g_CmdNames.AddDWord ((DWORD)szFuncName);
        return func;
    }

    static const TCHAR** _GetCmdNames ()
    {
        return (const TCHAR**)_g_CmdNames.GetPtr ();
    }

    #define ESP_CMD(name)  _RecordCmdName (esp_##name, "esp_" #name)  // ���ڲ�ͬ�Ŀ�, ������Ӧ�������޸�
    #define ESP_NULL_CMD(name)  _RecordCmdName(NULL, NULL)

#endif

#define ESP_MASK_NULL    ESP_NULL_CMD(NULL)
#define ESP_MASK_NULL_1  ESP_MASK_NULL
#define ESP_MASK_NULL_2  ESP_MASK_NULL_1, ESP_MASK_NULL_1
#define ESP_MASK_NULL_3  ESP_MASK_NULL_2, ESP_MASK_NULL_1
#define ESP_MASK_NULL_4  ESP_MASK_NULL_3, ESP_MASK_NULL_1
#define ESP_MASK_NULL_5  ESP_MASK_NULL_4, ESP_MASK_NULL_1
#define ESP_MASK_NULL_6  ESP_MASK_NULL_5, ESP_MASK_NULL_1
#define ESP_MASK_NULL_7  ESP_MASK_NULL_6, ESP_MASK_NULL_1
#define ESP_MASK_NULL_8  ESP_MASK_NULL_7, ESP_MASK_NULL_1
#define ESP_MASK_NULL_9  ESP_MASK_NULL_8, ESP_MASK_NULL_1
#define ESP_MASK_NULL_10 ESP_MASK_NULL_9, ESP_MASK_NULL_1

//-----------------------------------------------------------------------------

#ifndef __E_STATIC_LIB

///////////////////////////////////////////////////////////////////////////////
// ����ʵ�ֺ���

#define ESP_All_functions \
	ESP_MASK_NULL_10,\
	ESP_CMD (fn_GetTypeName),\
	ESP_CMD (fn_GetInstanceName),\
	ESP_CMD (fn_GetPage),\
	ESP_CMD (fn_GetParent),\
	ESP_CMD (fn_GetLibraryName),\
	ESP_CMD (fn_GetLibraryFile),\
	ESP_CMD (fn_IsPage),\
	ESP_MASK_NULL_10,\
	ESP_CMD (fn_GetProperty),\
	ESP_CMD (fn_SetProperty),\
	ESP_CMD (fn_RemoveAllProperties),\
	ESP_CMD (fn_GetAllPropertyCount),\
	ESP_CMD (fn_GetPropertyNames),\
	ESP_CMD (fn_IsPropertyExist),\
	ESP_CMD (fn_GetPropertyType),\
	ESP_CMD (fn_GetPropertyInfos),\
	ESP_MASK_NULL_10,\
	ESP_CMD (fn_GetRequestURI),\
	ESP_MASK_NULL_10,\
	ESP_CMD (fn_GetSession),\
	ESP_CMD (fn_SetSession),\
	ESP_MASK_NULL_10,\
	ESP_CMD (fn_Output),\
	ESP_CMD (fn_OutputComponentTagHeader),\
	ESP_CMD (fn_OutputComponentTagTail),\
	ESP_CMD (fn_OutputBinary),\
	ESP_MASK_NULL_9,\
	ESP_CMD (fn_RuntimeError),\
	ESP_MASK_NULL_10,\


///////////////////////////////////////////////////////////////////////////////
// �������Ϣ

#define ESP_All_CmdInfos \
	MASK_CMD_INFO_10,\
	cmdInfo_GetTypeName,\
	cmdInfo_GetInstanceName,\
	cmdInfo_GetPage,\
	cmdInfo_GetParent,\
	cmdInfo_GetLibraryName,\
	cmdInfo_GetLibraryFile,\
	cmdInfo_IsPage,\
	MASK_CMD_INFO_10,\
	cmdInfo_GetProperty,\
	cmdInfo_SetProperty,\
	cmdInfo_RemoveAllProperties,\
	cmdInfo_GetAllPropertyCount,\
	cmdInfo_GetPropertyNames,\
	cmdInfo_IsPropertyExist,\
	cmdInfo_GetPropertyType,\
	cmdInfo_GetPropertyInfos,\
	MASK_CMD_INFO_10,\
	cmdInfo_GetRequestURI,\
	MASK_CMD_INFO_10,\
	cmdInfo_GetSession, \
	cmdInfo_SetSession, \
	MASK_CMD_INFO_10,\
	cmdInfo_Output,\
	cmdInfo_OutputComponentTagHeader, \
	cmdInfo_OutputComponentTagTail, \
	cmdInfo_OutputBinary,\
	MASK_CMD_INFO_9,\
	cmdInfo_RuntimeError,\
	MASK_CMD_INFO_10,\

#endif

///////////////////////////////////////////////////////////////////////////////
// ȫ������֮������ʵ�� (ͬһ�������Ĳ�������Ϣ��ʵ�ִ������һ�𣬱��ڲ��Ҽ��ο�)

#ifndef __E_STATIC_LIB

#define  ARG_ObjectID \
	{\
/*name*/	_WT("����ID"),\
/*explain*/	_WT(""),\
/*bmp inx*/	0,\
/*bmp num*/	0,\
/*type*/	SDT_INT,\
/*default*/	0,\
/*state*/	0,\
	}\

ARG_INFO argInfo_ObjectID[] =
{
	ARG_ObjectID,
};

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#define cmdInfo_GetInstanceName \
{\
	/*ccname*/	_WT("ESP_ȡ��������"),\
	/*egname*/	_WT("ESP_GetInstanceName"),\
	/*explain*/	_WT("���ض����ʵ������"),\
	/*category*/1,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		SDT_TEXT,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_ObjectID) / sizeof(argInfo_ObjectID[0]),\
	/*arg lp*/	argInfo_ObjectID,\
	}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_GetInstanceName)
{
	pRetData->m_pText = NULL;
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
	pRetData->m_pText = CloneTextData((char*) g_pESPFuncs->pfn_ESPObject_GetInstanceName(oid));
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

#define cmdInfo_GetTypeName \
{\
	/*ccname*/	_WT("ESP_ȡ��������"),\
	/*egname*/	_WT("ESP_GetTypeName"),\
	/*explain*/	_WT("���ض������������"),\
	/*category*/1,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		SDT_TEXT,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_ObjectID) / sizeof(argInfo_ObjectID[0]),\
	/*arg lp*/	argInfo_ObjectID,\
}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_GetTypeName)
{
	pRetData->m_pText = NULL;
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
	pRetData->m_pText = CloneTextData((char*) g_pESPFuncs->pfn_ESPObject_GetTypeName(oid));
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

#define cmdInfo_GetLibraryName \
{\
	/*ccname*/	_WT("ESP_ȡ���ڿ�����"),\
	/*egname*/	_WT("ESP_GetLibraryName"),\
	/*explain*/	_WT("���ض������ڿ�Ŀ�����"),\
	/*category*/1,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		SDT_TEXT,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_ObjectID) / sizeof(argInfo_ObjectID[0]),\
	/*arg lp*/	argInfo_ObjectID,\
}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_GetLibraryName)
{
	pRetData->m_pText = NULL;
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
	pRetData->m_pText = CloneTextData((char*) g_pESPFuncs->pfn_ESPObject_GetLibraryName(oid));
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

#define cmdInfo_GetLibraryFile \
{\
	/*ccname*/	_WT("ESP_ȡ���ڿ��ļ�"),\
	/*egname*/	_WT("ESP_GetLibraryFile"),\
	/*explain*/	_WT("���ض������ڿ������·���ļ���"),\
	/*category*/1,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		SDT_TEXT,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_ObjectID) / sizeof(argInfo_ObjectID[0]),\
	/*arg lp*/	argInfo_ObjectID,\
}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_GetLibraryFile)
{
	pRetData->m_pText = NULL;
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
	pRetData->m_pText = CloneTextData((char*) g_pESPFuncs->pfn_ESPObject_GetLibraryFile(oid));
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

#define cmdInfo_IsPage \
{\
	/*ccname*/	_WT("ESP_�Ƿ�Ϊҳ��"),\
	/*egname*/	_WT("ESP_IsPage"),\
	/*explain*/	_WT("�ж�ָ�������Ƿ�Ϊҳ�������ESP�У�������ҳ����������"),\
	/*category*/1,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		SDT_TEXT,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_ObjectID) / sizeof(argInfo_ObjectID[0]),\
	/*arg lp*/	argInfo_ObjectID,\
}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_IsPage)
{
	pRetData->m_pText = NULL;
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
	pRetData->m_pText = CloneTextData((char*) g_pESPFuncs->pfn_ESPObject_IsPage(oid));
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO argInfo_GetProperty[] =
{
	ARG_ObjectID,
	{
		/*name*/	_WT("��������"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_TEXT,
		/*default*/	0,
		/*state*/	0,
	},
	{
		/*name*/	_WT("Ĭ������ֵ"),
		/*explain*/	_WT("�����Բ����ڵ�����£�������ֵ����ΪĬ������ֵ�����ء�������Բ����ڶ���δ�ṩ�������������ؿ�ֵ������һ��ESP����ʱ���󣨶�ȡ�����ڵ����ԣ���"),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	_SDT_ALL,
		/*default*/	0,
		/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
	},
};

#define cmdInfo_GetProperty \
	{\
	/*ccname*/	_WT("ESP_ȡ����ֵ"),\
	/*egname*/	_WT("ESP_GetProperty"),\
	/*explain*/	_WT("����ָ�����Ե�ֵ������ֵ�����ɸ����Ե����;��������ָ�������Բ����ڣ������ز�����Ĭ������ֵ����ָ����ֵ���򷵻ؿ�ֵ������һ��ESP����ʱ����"),\
	/*category*/2,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		_SDT_ALL,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_GetProperty) / sizeof(argInfo_GetProperty[0]),\
	/*arg lp*/	argInfo_GetProperty,\
	}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_GetProperty)
{
	pRetData->m_dtDataType = SDT_TEXT;
	pRetData->m_pText = NULL;
	if(IsESPRuntimeAvailable() == false) return;

	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
	char* szPropName = pArgInf[1].m_pText;

	ESPPropType type = g_pESPFuncs->pfn_ESPObject_GetPropertyType(oid, szPropName);

	switch(type)
	{
	case ESPPropType_BOOL:
		pRetData->m_dtDataType = SDT_BOOL;
		pRetData->m_bool = (g_pESPFuncs->pfn_ESPObject_GetBoolProperty(oid, szPropName) ? TRUE : FALSE);
		break;
	case ESPPropType_INT:
		pRetData->m_dtDataType = SDT_INT;
		pRetData->m_int = g_pESPFuncs->pfn_ESPObject_GetIntProperty(oid, szPropName);
		break;
	case ESPPropType_INT64:
		pRetData->m_dtDataType = SDT_INT64;
		pRetData->m_int64 = (INT64) g_pESPFuncs->pfn_ESPObject_GetInt64Property(oid, szPropName);
		break;
	case ESPPropType_FLOAT:
		pRetData->m_dtDataType = SDT_FLOAT;
		pRetData->m_float = g_pESPFuncs->pfn_ESPObject_GetFloatProperty(oid, szPropName);
		break;
	case ESPPropType_DOUBLE:
		pRetData->m_dtDataType = SDT_DOUBLE;
		pRetData->m_double = g_pESPFuncs->pfn_ESPObject_GetDoubleProperty(oid, szPropName);
		break;
	case ESPPropType_TEXT:
		pRetData->m_dtDataType = SDT_TEXT;
		pRetData->m_pText = CloneTextData((char*) g_pESPFuncs->pfn_ESPObject_GetTextProperty(oid, szPropName));
		break;
	case ESPPropType_BINARY:
		{
			size_t len = 0;
			const void* p = g_pESPFuncs->pfn_ESPObject_GetBinaryProperty(oid, szPropName, &len);
			pRetData->m_dtDataType = SDT_BIN;
			pRetData->m_pBin = CloneBinData((LPBYTE)p, len);
			break;
		}

	case ESPPropType_NULL:
	default:
		{
			//�������Բ����ڵ����: �����û�ָ����Ĭ������ֵ�������ESP����ʱ����

			PMDATA_INF pDefaultValue = &pArgInf[2];

			if(pDefaultValue->m_dtDataType != _SDT_NULL)
			{
				//����Ĭ������ֵ
				*pRetData = *pDefaultValue;
				if(pDefaultValue->m_dtDataType == SDT_TEXT)
				{
					pRetData->m_pText = CloneTextData(pDefaultValue->m_pText);
				}
				else if(pDefaultValue->m_dtDataType == SDT_BIN)
				{
					DWORD* pBinData = (DWORD*) pDefaultValue->m_pBin;
					if(pBinData)
					{
						pRetData->m_pBin = CloneBinData((LPBYTE)&pBinData[2], pBinData[1]);
					}
				}
			}
			else
			{
				//����ESP����ʱ����
				pRetData->m_dtDataType = _SDT_NULL;
				XString s; XString_init_(&s);
				XString_SetTextF(&s, "�������ƣ�%s���������ƣ�%s�������������ƣ�%s������ҳ�棺%s��\n",
								 szPropName, g_pESPFuncs->pfn_ESPObject_GetInstanceName(oid),
								 g_pESPFuncs->pfn_ESPObject_GetTypeName(oid),
								 g_pESPFuncs->pfn_ESPObject_GetTypeName(g_pESPFuncs->pfn_ESPObject_GetPage(oid)));
				g_pESPFuncs->pfn_ESPObject_RuntimeError(oid, "��ȡ�����ڵ�����", XString_GetText(&s));
				XString_destroy_(&s);
			}
			break;
		} //end default
	} //end switch
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO argInfo_SetProperty[] =
{
	ARG_ObjectID,
	{
		/*name*/	_WT("��������"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_TEXT,
		/*default*/	0,
		/*state*/	0,
	},
	{
		/*name*/	_WT("����ֵ"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	_SDT_ALL,
		/*default*/	0,
		/*state*/	0,
	},
};

#define cmdInfo_SetProperty \
	{\
	/*ccname*/	_WT("ESP_������ֵ"),\
	/*egname*/	_WT("ESP_SetProperty"),\
	/*explain*/	_WT("���ö������Ե�ֵ����������Ѿ����ڣ�ֻ���������������������ֵ������ƥ���������л�д��ɹ���"\
					"������Բ����ڣ������ݲ���������ֵ�������Զ�������Ӧ���͵����ԣ���д������ֵ��ִ�гɹ������棬ʧ�ܷ��ؼ١�"),\
	/*category*/2,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		SDT_BOOL,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_SetProperty) / sizeof(argInfo_SetProperty[0]),\
	/*arg lp*/	argInfo_SetProperty,\
	}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_SetProperty)
{
	pRetData->m_bool = FALSE;
	if(IsESPRuntimeAvailable() == false) return;

	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
	char* szPropName = pArgInf[1].m_pText;
	
	MDATA_INF* pValue = &pArgInf[2];
    bool bOK = false;

	ESPPropType propType = g_pESPFuncs->pfn_ESPObject_GetPropertyType(oid, szPropName);

	switch(pValue->m_dtDataType)
	{
	case SDT_BOOL:
		if(propType == ESPPropType_BOOL || propType == ESPPropType_NULL)
			bOK = g_pESPFuncs->pfn_ESPObject_SetBoolProperty(oid, szPropName, (pValue->m_bool ? true : false));
		break;
	case SDT_BYTE:
		pValue->m_int = pValue->m_byte; //no break
	case SDT_SHORT:
		pValue->m_int = pValue->m_short; //no break
	case SDT_INT:
		if(propType == ESPPropType_INT || propType == ESPPropType_NULL)
			bOK = g_pESPFuncs->pfn_ESPObject_SetIntProperty(oid, szPropName, pValue->m_int);
		else if(propType == ESPPropType_INT64)
			bOK = g_pESPFuncs->pfn_ESPObject_SetInt64Property(oid, szPropName, (ESP_INT64)pValue->m_int);
		else if(propType == ESPPropType_FLOAT)
			bOK = g_pESPFuncs->pfn_ESPObject_SetFloatProperty(oid, szPropName, (float)pValue->m_int);
		else if(propType == ESPPropType_DOUBLE)
			bOK = g_pESPFuncs->pfn_ESPObject_SetDoubleProperty(oid, szPropName, (double)pValue->m_int);
		break;
	case SDT_INT64:
		if(propType == ESPPropType_INT64 || propType == ESPPropType_NULL)
			bOK = g_pESPFuncs->pfn_ESPObject_SetInt64Property(oid, szPropName, (ESP_INT64)pValue->m_int64);
		break;
	case SDT_FLOAT:
		if(propType == ESPPropType_FLOAT || propType == ESPPropType_NULL)
			bOK = g_pESPFuncs->pfn_ESPObject_SetFloatProperty(oid, szPropName, pValue->m_float);
		else if(propType == ESPPropType_INT)
			bOK = g_pESPFuncs->pfn_ESPObject_SetIntProperty(oid, szPropName, (int)pValue->m_float);
		else if(propType == ESPPropType_INT64)
			bOK = g_pESPFuncs->pfn_ESPObject_SetInt64Property(oid, szPropName, (ESP_INT64)pValue->m_float);
		break;
	case SDT_DATE_TIME:
		pValue->m_double = (DOUBLE) pValue->m_date; //no break
	case SDT_DOUBLE:
		if(propType == ESPPropType_DOUBLE || propType == ESPPropType_NULL)
			bOK = g_pESPFuncs->pfn_ESPObject_SetDoubleProperty(oid, szPropName, pValue->m_double);
		else if(propType == ESPPropType_INT)
			bOK = g_pESPFuncs->pfn_ESPObject_SetIntProperty(oid, szPropName, (int)pValue->m_double);
		else if(propType == ESPPropType_INT64)
			bOK = g_pESPFuncs->pfn_ESPObject_SetInt64Property(oid, szPropName, (ESP_INT64)pValue->m_double);
		break;
	case SDT_TEXT:
		if(propType == ESPPropType_TEXT || propType == ESPPropType_NULL)
			bOK = g_pESPFuncs->pfn_ESPObject_SetTextProperty(oid, szPropName, pValue->m_pText);
		break;
	case SDT_BIN:
		if(propType == ESPPropType_BINARY || propType == ESPPropType_NULL)
		{
			void* pData = NULL;
			size_t nDataLen = 0;
			DWORD* pEBinData = (DWORD*) pValue->m_pBin;
			if(pEBinData)
			{
				pData = &(pEBinData[2]);
				nDataLen = (size_t) pEBinData[1];
			}
			bOK = g_pESPFuncs->pfn_ESPObject_SetBinaryProperty(oid, szPropName, pData, nDataLen);
		}
	default:
		break;
	}

	pRetData->m_bool = (bOK ? TRUE : FALSE);
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

#define cmdInfo_RemoveAllProperties \
{\
	/*ccname*/	_WT("ESP_ɾ����������"),\
	/*egname*/	_WT("ESP_RemoveAllProperties"),\
	/*explain*/	_WT("��������ɾ�����Ƚ�Σ��"),\
	/*category*/2,\
	/*state*/	CMD_SUPPORT_OS|CT_IS_HIDED,\
	/*ret*/		_SDT_NULL,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/1,\
	/*arg lp*/	argInfo_ObjectID,\
	}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_RemoveAllProperties)
{
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
    g_pESPFuncs->pfn_ESPObject_RemoveAllPropeties(oid);
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

#define cmdInfo_GetAllPropertyCount \
{\
	/*ccname*/	_WT("ESP_ȡ���Ը���"),\
	/*egname*/	_WT("ESP_GetAllPropertyCount"),\
	/*explain*/	_WT("����ָ�������е��������Ը���������������˽�е��Լ���ʱ�����ԡ�"),\
	/*category*/2,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		SDT_INT,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/1,\
	/*arg lp*/	argInfo_ObjectID,\
}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_GetAllPropertyCount)
{
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
    pRetData->m_int = g_pESPFuncs->pfn_ESPObject_GetAllPropertyCount(oid);
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO argInfo_GetPropertyNames[] =
{
	ARG_ObjectID,
	{
		/*name*/	_WT("����������"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_BOOL,
		/*default*/	1,
		/*state*/	AS_HAS_DEFAULT_VALUE,
	},
	{
		/*name*/	_WT("��˽������"),
		/*explain*/	_WT("��������ʽ�����˽�����ԣ���������ʱ����"),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_BOOL,
		/*default*/	1,
		/*state*/	AS_HAS_DEFAULT_VALUE,
	},
	{
		/*name*/	_WT("����ʱ����"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_BOOL,
		/*default*/	1,
		/*state*/	AS_HAS_DEFAULT_VALUE,
	},
};

#define cmdInfo_GetPropertyNames \
{\
	/*ccname*/	_WT("ESP_ȡ��������"),\
	/*egname*/	_WT("ESP_GetPropertyNames"),\
	/*explain*/	_WT("����һά�ı����飬���а������з����������������ơ�"),\
	/*category*/2,\
	/*state*/	CMD_SUPPORT_OS|CT_RETRUN_ARY_TYPE_DATA,\
	/*ret*/		SDT_TEXT,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_GetPropertyNames) / sizeof(argInfo_GetPropertyNames[0]),\
	/*arg lp*/	argInfo_GetPropertyNames,\
}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_GetPropertyNames)
{
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
	bool includePublic   = (pArgInf[1].m_bool ? true : false);
	bool includePrivate  = (pArgInf[2].m_bool ? true : false);
	bool includeInformal = (pArgInf[3].m_bool ? true : false);

	size_t propCount = 0;
    char** pszNames = g_pESPFuncs->pfn_ESPObject_GetPropertyNames(oid, includePublic, includePrivate, includeInformal, &propCount);

	DWORD* pArrayData = (DWORD*) NotifySys(NRS_MALLOC, sizeof(DWORD) * (propCount+2), 0);
	pArrayData[0] = 1;
	pArrayData[1] = propCount;
	assert(pArrayData);
	for(size_t i = 0; i < propCount; i++)
		pArrayData[i+2] = (DWORD) CloneTextData(pszNames[i]);
	pRetData->m_pAryData = pArrayData;

	g_pESPFuncs->pfn_FreeData(pszNames);
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO argInfo_IsPropertyExist[] =
{
	ARG_ObjectID,
	{
		/*name*/	_WT("��������"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_TEXT,
		/*default*/	0,
		/*state*/	0,
	},
	{
		/*name*/	_WT("��������"),
		/*explain*/	_WT("����˲�����ʡ�Ի�Ϊ��#ESP_��������.�ա�����ֻ�������������ж������Ƿ���ڣ����򣬻���ͬʱ�ж������Ƿ�һ�£����Ͳ�һ��Ҳ��Ϊ�����Բ����ڡ�"),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	LIB_TYPE(1), //ESP_��������
		/*default*/	0,
		/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
	},
};

#define cmdInfo_IsPropertyExist \
{\
	/*ccname*/	_WT("ESP_�����Ƿ����"),\
	/*egname*/	_WT("ESP_IsPropertyExist"),\
	/*explain*/	_WT("�ж�ָ�����ƺ�ָ�����͵������Ƿ���ڡ�"),\
	/*category*/2,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		SDT_BOOL,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_IsPropertyExist) / sizeof(argInfo_IsPropertyExist[0]),\
	/*arg lp*/	argInfo_IsPropertyExist,\
	}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_IsPropertyExist)
{
	pRetData->m_pText = NULL;
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
	char* szPropName = pArgInf[1].m_pText;
	
	ESPPropType type = ESPPropType_NULL;
	if(pArgInf[2].m_dtDataType != _SDT_NULL)
		type = (ESPPropType) pArgInf[2].m_int;
	
	bool bIsExist = g_pESPFuncs->pfn_ESPObject_IsPropertyExist(oid, szPropName, type);
	pRetData->m_bool = (bIsExist ? TRUE : FALSE);
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO argInfo_GetPropertyType[] =
{
	ARG_ObjectID,
	{
		/*name*/	_WT("��������"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_TEXT,
		/*default*/	0,
		/*state*/	0,
	},
};

#define cmdInfo_GetPropertyType \
{\
	/*ccname*/	_WT("ESP_ȡ��������"),\
	/*egname*/	_WT("ESP_GetPropertyType"),\
	/*explain*/	_WT("����ָ�����Ե��������͡���������Բ����ڣ������ء�ESP_��������.�ա���"),\
	/*category*/2,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		LIB_TYPE(1),\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_GetPropertyType) / sizeof(argInfo_GetPropertyType[0]),\
	/*arg lp*/	argInfo_GetPropertyType,\
	}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_GetPropertyType)
{
	pRetData->m_pText = NULL;
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
	char* szPropName = pArgInf[1].m_pText;

	pRetData->m_int = g_pESPFuncs->pfn_ESPObject_GetPropertyType(oid, szPropName);
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO argInfo_GetPropertyInfos[] =
{
	ARG_ObjectID,
	{
		/*name*/	_WT("��������"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_TEXT,
		/*default*/	0,
		/*state*/	0,
	},
	{
		/*name*/	_WT("����"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	LIB_TYPE(1),
		/*default*/	0,
		/*state*/	AS_RECEIVE_VAR|AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/	_WT("˵��"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_TEXT,
		/*default*/	0,
		/*state*/	AS_RECEIVE_VAR|AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/	_WT("��ʼֵ"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_TEXT,
		/*default*/	0,
		/*state*/	AS_RECEIVE_VAR|AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/	_WT("�Ƿ񹫿�"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_BOOL,
		/*default*/	0,
		/*state*/	AS_RECEIVE_VAR|AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/	_WT("�Ƿ���ʱ"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_BOOL,
		/*default*/	0,
		/*state*/	AS_RECEIVE_VAR|AS_DEFAULT_VALUE_IS_EMPTY,
	},
};

#define cmdInfo_GetPropertyInfos \
{\
	/*ccname*/	_WT("ESP_ȡ������Ϣ"),\
	/*egname*/	_WT("ESP_GetPropertyInfos"),\
	/*explain*/	_WT("����ָ�����Եĸ��ֻ�����Ϣ��������Բ����ڽ����ؼ١�"),\
	/*category*/2,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		SDT_BOOL,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_GetPropertyInfos) / sizeof(argInfo_GetPropertyInfos[0]),\
	/*arg lp*/	argInfo_GetPropertyInfos,\
	}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_GetPropertyInfos)
{
	pRetData->m_pText = NULL;
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
	char* szPropName = pArgInf[1].m_pText;

	ESPPropType type = ESPPropType_NULL;
	char* desc = NULL;
	char* initial = NULL;
	bool ispublic = false, istemp = false;

	pRetData->m_bool = g_pESPFuncs->pfn_ESPObject_GetPropertyInfos(oid, szPropName, 
										&type, &desc, &initial, &ispublic, &istemp);

	if(pArgInf[2].m_dtDataType != _SDT_NULL) *(pArgInf[2].m_pInt)   = (INT)type;
	if(pArgInf[3].m_dtDataType != _SDT_NULL) *(pArgInf[3].m_ppText) = CloneTextData(desc);
	if(pArgInf[4].m_dtDataType != _SDT_NULL) *(pArgInf[4].m_ppText) = CloneTextData(initial);
	if(pArgInf[5].m_dtDataType != _SDT_NULL) *(pArgInf[5].m_pBool)  = ispublic;
	if(pArgInf[6].m_dtDataType != _SDT_NULL) *(pArgInf[6].m_pBool)  = istemp;
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

#define cmdInfo_GetPage \
{\
	/*ccname*/	_WT("ESP_ȡ����ҳ��"),\
	/*egname*/	_WT("ESP_GetPage"),\
	/*explain*/	_WT("������������ҳ�棬��ֱ�ӷ��ظ�ҳ�����"),\
	/*category*/1,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		SDT_INT,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/1,\
	/*arg lp*/	argInfo_ObjectID,\
	}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_GetPage)
{
	pRetData->m_int = 0;
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
    pRetData->m_int = g_pESPFuncs->pfn_ESPObject_GetPage(oid);
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

#define cmdInfo_GetParent \
{\
	/*ccname*/	_WT("ESP_ȡ������"),\
	/*egname*/	_WT("ESP_GetParent"),\
	/*explain*/	_WT(""),\
	/*category*/1,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		SDT_INT,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/1,\
	/*arg lp*/	argInfo_ObjectID,\
}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_GetParent)
{
	pRetData->m_int = 0;
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
    pRetData->m_int = g_pESPFuncs->pfn_ESPObject_GetParent(oid);
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

#define cmdInfo_GetRequestURI \
{\
	/*ccname*/	_WT("ESP_ȡ�����ַ"),\
	/*egname*/	_WT("ESP_GetRequestURI"),\
	/*explain*/	_WT(""),\
	/*category*/4,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		SDT_TEXT,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/1,\
	/*arg lp*/	argInfo_ObjectID,\
}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_GetRequestURI)
{
	pRetData->m_pText = NULL;
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
	const char* uri = g_pESPFuncs->pfn_ESPObject_GetRequestInfo(oid, ESPRequestInfoIndex_URI);
    pRetData->m_pText = CloneTextData((char*)uri);
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO argInfo_RuntimeError[] =
{
	ARG_ObjectID,
	{
		/*name*/	_WT("��������"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_TEXT,
		/*default*/	0,
		/*state*/	0,
	},
	{
		/*name*/	_WT("��������"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_TEXT,
		/*default*/	0,
		/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
	},
};

#define cmdInfo_RuntimeError \
{\
	/*ccname*/	_WT("ESP_����ʱ����"),\
	/*egname*/	_WT("ESP_RuntimeError"),\
	/*explain*/	_WT("��ϵͳ��������ʱ����"),\
	/*category*/6,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		_SDT_NULL,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_RuntimeError) / sizeof(argInfo_RuntimeError[0]),\
	/*arg lp*/	argInfo_RuntimeError,\
	}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_RuntimeError)
{
	pRetData->m_pText = NULL;
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPObjectID oid = (ESPObjectID) pArgInf[0].m_int;
	char* type = pArgInf[1].m_pText;
	char* description = NULL;
	if(pArgInf[2].m_dtDataType != _SDT_NULL)
	{
		description = pArgInf[2].m_pText;
		if(*description == '\0')
			description = NULL;
	}
    g_pESPFuncs->pfn_ESPObject_RuntimeError(oid, type, description);
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO argInfo_ESPRenderContext_Output[] =
{
	{
		/*name*/	_WT("�����ID"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_INT,
		/*default*/	0,
		/*state*/	0,
	},
	{
		/*name*/	_WT("��������ı�"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_TEXT,
		/*default*/	0,
		/*state*/	0,
	},
};

#define cmdInfo_Output \
{\
	/*ccname*/	_WT("ESP_����ı�"),\
	/*egname*/	_WT("RenderContext_Output"),\
	/*explain*/	_WT(""),\
	/*category*/5,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		_SDT_NULL,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_ESPRenderContext_Output) / sizeof(argInfo_ESPRenderContext_Output[0]),\
	/*arg lp*/	argInfo_ESPRenderContext_Output,\
	}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_Output)
{
	if(IsESPRuntimeAvailable() == false) return;
	
    g_pESPFuncs->pfn_ESPRenderContext_Output((ESPObjectID)pArgInf[0].m_int, pArgInf[1].m_pText, strlen(pArgInf[1].m_pText));
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO argInfo_ESPRenderContext_OutputComponentTagHeader[] =
{
	{
		/*name*/	_WT("�����ID"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_INT,
		/*default*/	0,
		/*state*/	0,
	},
	{
		/*name*/	_WT("���ID"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_INT,
		/*default*/	0,
		/*state*/	0,
	},
	{
		/*name*/	_WT("�����û���������"),
		/*explain*/	_WT("����\"esp:\"��ͷ������Ϊ�û���������"),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_BOOL,
		/*default*/	BL_TRUE,
		/*state*/	AS_HAS_DEFAULT_VALUE,
	},
	{
		/*name*/	_WT("���������ı�"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_TEXT,
		/*default*/	0,
		/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
	},
};

#define cmdInfo_OutputComponentTagHeader \
{\
	/*ccname*/	_WT("ESP_��������ǩͷ"),\
	/*egname*/	_WT("ESPRenderContext_OutputComponentTagHeader"),\
	/*explain*/	_WT("���ָ�������ģ����������ǩͷ��HTML�ı����磬��ģ���У�<span esp:type=\"if\" esp:value=\"...\" ...>...</span>��if����������ڵ�Ϊspan������<span ...>����Ϊ��ǩͷ��</span>����Ϊ��ǩβ��" \
					"Ĭ������²�������ñ�ǩ�������������ñ����Ӧ�롰ESP_��������ǩβ()���������ʹ�á�"),\
	/*category*/5,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		_SDT_NULL,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_ESPRenderContext_OutputComponentTagHeader) / sizeof(argInfo_ESPRenderContext_OutputComponentTagHeader[0]),\
	/*arg lp*/	argInfo_ESPRenderContext_OutputComponentTagHeader,\
}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_OutputComponentTagHeader)
{
	if(IsESPRuntimeAvailable() == false) return;

	ESPRenderContextID rcid = (ESPRenderContextID) pArgInf[0].m_int;
	ESPObjectID cid = (ESPObjectID) pArgInf[1].m_int;
	if(rcid == 0 || cid == 0) return;

	BOOL bOutputUserAttributes = pArgInf[2].m_bool;

	char* other_attributes = (pArgInf[3].m_dtDataType == _SDT_NULL ? NULL : pArgInf[2].m_pText);
	size_t other_attributes_len = (other_attributes ? strlen(other_attributes) : 0);

	const char* tag_name = g_pESPFuncs->pfn_ESPObject_GetProperty(cid, "$tag_name");
	size_t tag_name_len = (tag_name ? strlen(tag_name) : 0);
	if(tag_name_len > 0)
	{
		const char* tag_attributes = g_pESPFuncs->pfn_ESPObject_GetProperty(cid, "$tag_attributes");
		size_t tag_attributes_len = (tag_attributes ? strlen(tag_attributes) : 0);

		g_pESPFuncs->pfn_ESPRenderContext_Output(rcid, "<", 1);
		g_pESPFuncs->pfn_ESPRenderContext_Output(rcid, tag_name, tag_name_len);
		if(bOutputUserAttributes && (tag_attributes_len > 0))
		{
			g_pESPFuncs->pfn_ESPRenderContext_Output(rcid, " ", 1);
			g_pESPFuncs->pfn_ESPRenderContext_Output(rcid, tag_attributes, tag_attributes_len);
		}
		if(other_attributes_len > 0)
		{
			g_pESPFuncs->pfn_ESPRenderContext_Output(rcid, " ", 1);
			g_pESPFuncs->pfn_ESPRenderContext_Output(rcid, other_attributes, other_attributes_len);
		}
		g_pESPFuncs->pfn_ESPRenderContext_Output(rcid, ">", 1);
	}
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO argInfo_ESPRenderContext_OutputComponentTagTail[] =
{
	{
		/*name*/	_WT("�����ID"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_INT,
		/*default*/	0,
		/*state*/	0,
	},
	{
		/*name*/	_WT("���ID"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_INT,
		/*default*/	0,
		/*state*/	0,
	},
};

#define cmdInfo_OutputComponentTagTail \
{\
	/*ccname*/	_WT("ESP_��������ǩβ"),\
	/*egname*/	_WT("ESPRenderContext_OutputComponentTagTail"),\
	/*explain*/	_WT("�μ���ESP_��������ǩͷ()����˵��"),\
	/*category*/5,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		_SDT_NULL,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_ESPRenderContext_OutputComponentTagTail) / sizeof(argInfo_ESPRenderContext_OutputComponentTagTail[0]),\
	/*arg lp*/	argInfo_ESPRenderContext_OutputComponentTagTail,\
	}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_OutputComponentTagTail)
{
	if(IsESPRuntimeAvailable() == false) return;
	
	ESPRenderContextID rcid = (ESPRenderContextID) pArgInf[0].m_int;
	ESPObjectID cid = (ESPObjectID) pArgInf[1].m_int;
	if(rcid == 0 || cid == 0) return;
	
	const char* tag_name = g_pESPFuncs->pfn_ESPObject_GetProperty(cid, "$tag_name");
	size_t tag_name_len = (tag_name ? strlen(tag_name) : 0);
	if(tag_name_len > 0)
	{
		g_pESPFuncs->pfn_ESPRenderContext_Output(rcid, "</", 2);
		g_pESPFuncs->pfn_ESPRenderContext_Output(rcid, tag_name, tag_name_len);
		g_pESPFuncs->pfn_ESPRenderContext_Output(rcid, ">", 1);
	}
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO argInfo_ESPRenderContext_OutputBinary[] =
{
	{
		/*name*/	_WT("�����ID"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_INT,
		/*default*/	0,
		/*state*/	0,
	},
	{
		/*name*/	_WT("��������ֽڼ�"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_BIN,
		/*default*/	0,
		/*state*/	0,
	},
};

#define cmdInfo_OutputBinary \
{\
	/*ccname*/	_WT("ESP_����ֽڼ�"),\
	/*egname*/	_WT("RenderContext_OutputBinary"),\
	/*explain*/	_WT("ע��������Ӧ��Content-Type"),\
	/*category*/5,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		_SDT_NULL,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_ESPRenderContext_OutputBinary) / sizeof(argInfo_ESPRenderContext_OutputBinary[0]),\
	/*arg lp*/	argInfo_ESPRenderContext_OutputBinary,\
	}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_OutputBinary)
{
	if(IsESPRuntimeAvailable() == false) return;

	size_t* p = (size_t*) pArgInf[1].m_pBin; if(p == NULL) return;
    g_pESPFuncs->pfn_ESPRenderContext_Output((ESPObjectID)pArgInf[0].m_int, (void*)(p + 2), *(p + 1));
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO argInfo_GetSession[] =
{
	ARG_ObjectID,
	{
		/*name*/	_WT("����"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_TEXT,
		/*default*/	0,
		/*state*/	0,
	},
};

#define cmdInfo_GetSession \
{\
	/*ccname*/	_WT("ESP_ȡ�Ự"),\
	/*egname*/	_WT("ESP_GetSession"),\
	/*explain*/	_WT(""),\
	/*category*/3,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		SDT_TEXT,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_GetSession) / sizeof(argInfo_GetSession[0]),\
	/*arg lp*/	argInfo_GetSession,\
	}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_GetSession)
{
	if(IsESPRuntimeAvailable() == false) return;
	
    pRetData->m_pText = CloneTextData((char*)g_pESPFuncs->pfn_ESPObject_GetSession((ESPObjectID)pArgInf[0].m_int, pArgInf[1].m_pText));
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO argInfo_SetSession[] =
{
	ARG_ObjectID,
	{
		/*name*/	_WT("����"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_TEXT,
		/*default*/	0,
		/*state*/	0,
	},
	{
		/*name*/	_WT("ֵ"),
		/*explain*/	_WT(""),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_TEXT,
		/*default*/	0,
		/*state*/	0,
	},
};

#define cmdInfo_SetSession \
{\
	/*ccname*/	_WT("ESP_�ûỰ"),\
	/*egname*/	_WT("ESP_SetSession"),\
	/*explain*/	_WT(""),\
	/*category*/3,\
	/*state*/	CMD_SUPPORT_OS,\
	/*ret*/		SDT_BOOL,\
	/*reserved*/0,\
	/*level*/	LVL_HIGH,\
	/*bmp inx*/	0,\
	/*bmp num*/	0,\
	/*ArgCount*/sizeof(argInfo_SetSession) / sizeof(argInfo_SetSession[0]),\
	/*arg lp*/	argInfo_SetSession,\
	}

#endif

DEFINE_ESP_EXECUTE_CMD (fn_SetSession)
{
	if(IsESPRuntimeAvailable() == false) return;

	pRetData->m_bool = g_pESPFuncs->pfn_ESPObject_SetSession((ESPObjectID)pArgInf[0].m_int, pArgInf[1].m_pText, pArgInf[2].m_pText);
}

#endif //#ifndef GLOBAL_FUNCTION_HPP
