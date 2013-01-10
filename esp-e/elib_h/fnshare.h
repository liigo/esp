/*
    版权声明：
    本文件版权为易语言作者吴涛所有，仅授权给第三方用作开发易语言支持库，禁止用于其他任何场合。
*/

//本单元不使用MFC类, 可供编写跨平台的支持库或非窗口组件支持库使用

#ifndef __FN_SHARE_H
#define __FN_SHARE_H

#include "lib2.h"
#include <assert.h>
#include <memory.h>
#include <string.h>


#define ASSERT(f)	assert(f)

#ifdef __cplusplus
extern "C" {
#endif

INT WINAPI ProcessNotifyLib (INT nMsg, DWORD dwParam1, DWORD dwParam2);
INT WINAPI NotifySys (INT nMsg, DWORD dwParam1, DWORD dwParam2);

char* CloneTextData (char* ps);
char* CloneTextDataLen (char* ps, INT nTextLen);
LPBYTE CloneBinData (LPBYTE pData, INT nDataSize);
void GReportError (char* szErrText);
void* MMalloc (INT nSize);
void MFree (void* p);
LPBYTE GetAryElementInf (void* pAryData, LPINT pnElementCount);
INT GetDataTypeType (DATA_TYPE dtDataType);
BOOL RunWhereStatment (PMDATA_INF pStatmentInf);
//void RunCalcStatment (PMDATA_INF pStatmentInf, CFreqMem& memCalc, LPDWORD pdwaryData,
//                      PDATA_TYPE pdtDataType, LPBYTE* ppData, LPINT pnDataSize);
INT GetSysDataTypeDataSize (DATA_TYPE dtSysDataType);
void SetMDataValue (PMDATA_INF pRetData, LPBYTE pData, INT nDataSize);
void ZeroMem (LPBYTE pDest, DWORD dwLength);
void CopyMem (LPBYTE pDest, LPBYTE pSrc, DWORD dwLength);
void MoveMem (LPBYTE pDest, LPBYTE pSrc, DWORD dwLength);
INT FindWord (LPWORD pwTable, INT count, WORD wFind);
INT FindDWord (LPDWORD pdwTable, INT count, DWORD dwFind);
INT FindInt (LPINT pnTable, INT nCount, INT nFind);
INT FindByte (LPBYTE pTable, INT count, BYTE btFind);

#ifdef __cplusplus
}
#endif

//add by liigo
//typedef INT (cdecl *PFN_ON_SYS_NOTIFY) (INT nMsg, DWORD dwParam1, DWORD dwParam2);
//end add

#define IS_CC(ch)             ((ch & 0x80) != 0)
#define GET_HZ(btLow,btHigh)  (MAKEWORD (btHigh, btLow))

#define MIN_DATE            (-657434L)  // about year 100
#define MAX_DATE            2958465L    // about year 9999

// 此宏在编译配置中设置
#ifdef __COMPILE_FNR
    #define _WT(text)	                    _T("")
    #define _CMDS_COUNT(CmdsCount)          0
    #define _CMDS_PTR(CmdsPtr)              NULL
    #define _EVENTS_COUNT(EventsCount)      0
    #define _EVENTS_PTR(EventsPtr)          NULL
    #define _ELEMENTS_COUNT(ElementsCount)  0
    #define _ELEMENTS_PTR(ElementsPtr)      NULL
    #define _FORM_BASE_CLASS	            CWnd
#else
    #define _WT(text)	                    _T(text)
    #define _CMDS_COUNT(CmdsCount)          CmdsCount
    #define _CMDS_PTR(CmdsPtr)              CmdsPtr
    #define _EVENTS_COUNT(EventsCount)      EventsCount
    #define _EVENTS_PTR(EventsPtr)          ((PEVENT_INFO2)EventsPtr)
    #define _ELEMENTS_COUNT(ElementsCount)  ElementsCount
    #define _ELEMENTS_PTR(ElementsPtr)      ElementsPtr
    #define _FORM_BASE_CLASS	            CFrameWnd
#endif

//命令信息占位符
#define CMD_INFO_MASK_1 \
		{\
		/*ccname*/	_T("???"),\
		/*egname*/	_T("???"),\
		/*explain*/	NULL,\
		/*category*/-1,\
		/*state*/	CT_IS_HIDED,\
		/*ret*/		_SDT_NULL,\
		/*reserved*/0,\
		/*level*/	LVL_SIMPLE,\
		/*bmp inx*/	0,\
		/*bmp num*/	0,\
		/*ArgCount*/0,\
		/*arg lp*/	NULL,\
		}
#define CMD_INFO_MASK_2		CMD_INFO_MASK_1,CMD_INFO_MASK_1
#define CMD_INFO_MASK_3		CMD_INFO_MASK_2,CMD_INFO_MASK_1
#define CMD_INFO_MASK_4		CMD_INFO_MASK_3,CMD_INFO_MASK_1
#define CMD_INFO_MASK_5		CMD_INFO_MASK_4,CMD_INFO_MASK_1
#define CMD_INFO_MASK_6		CMD_INFO_MASK_5,CMD_INFO_MASK_1
#define CMD_INFO_MASK_7		CMD_INFO_MASK_6,CMD_INFO_MASK_1
#define CMD_INFO_MASK_8		CMD_INFO_MASK_7,CMD_INFO_MASK_1
#define CMD_INFO_MASK_9		CMD_INFO_MASK_8,CMD_INFO_MASK_1
#define CMD_INFO_MASK_10	CMD_INFO_MASK_9,CMD_INFO_MASK_1

#define MASK_CMD_INFO_1		CMD_INFO_MASK_1
#define MASK_CMD_INFO_2		CMD_INFO_MASK_2
#define MASK_CMD_INFO_3		CMD_INFO_MASK_3
#define MASK_CMD_INFO_4		CMD_INFO_MASK_4
#define MASK_CMD_INFO_5		CMD_INFO_MASK_5
#define MASK_CMD_INFO_6		CMD_INFO_MASK_6
#define MASK_CMD_INFO_7		CMD_INFO_MASK_7
#define MASK_CMD_INFO_8		CMD_INFO_MASK_8
#define MASK_CMD_INFO_9		CMD_INFO_MASK_9
#define MASK_CMD_INFO_10	CMD_INFO_MASK_10


//数据类型占位符
#define DATATYPE_INFO_MASK_1 \
    {\
	/*m_szName*/			_T(""),\
	/*m_szEgName*/			_T(""),\
	/*m_szExplain*/			NULL,\
	/*m_nCmdCount*/			0,\
	/*m_pnCmdsIndex*/		NULL,\
	/*m_dwState*/			NULL,\
	/*m_dwUnitBmpID*/		0,\
	/*m_nEventCount*/		0,\
	/*m_pEventBegin*/		NULL,\
	/*m_nPropertyCount*/	0,\
	/*m_pPropertyBegin*/	NULL,\
	/*m_pfnGetInterface*/	NULL,\
	/*m_nElementCount*/		0,\
	/*m_pElementBegin*/		NULL,\
	}
#define DATATYPE_INFO_MASK_2	DATATYPE_INFO_MASK_1,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_3	DATATYPE_INFO_MASK_2,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_4	DATATYPE_INFO_MASK_3,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_5	DATATYPE_INFO_MASK_4,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_6	DATATYPE_INFO_MASK_5,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_7	DATATYPE_INFO_MASK_6,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_8	DATATYPE_INFO_MASK_7,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_9	DATATYPE_INFO_MASK_8,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_10	DATATYPE_INFO_MASK_9,DATATYPE_INFO_MASK_1

#define MASK_DATATYPE_INFO_1	DATATYPE_INFO_MASK_1
#define MASK_DATATYPE_INFO_2	DATATYPE_INFO_MASK_2
#define MASK_DATATYPE_INFO_3	DATATYPE_INFO_MASK_3
#define MASK_DATATYPE_INFO_4	DATATYPE_INFO_MASK_4
#define MASK_DATATYPE_INFO_5	DATATYPE_INFO_MASK_5
#define MASK_DATATYPE_INFO_6	DATATYPE_INFO_MASK_6
#define MASK_DATATYPE_INFO_7	DATATYPE_INFO_MASK_7
#define MASK_DATATYPE_INFO_8	DATATYPE_INFO_MASK_8
#define MASK_DATATYPE_INFO_9	DATATYPE_INFO_MASK_9
#define MASK_DATATYPE_INFO_10	DATATYPE_INFO_MASK_10


//数据类型成员占位符
#define DATATYPE_ELEMENT_MASK_1 \
	{\
/*m_dtType*/	SDT_INT,\
/*m_pArySpec*/	NULL,\
/*m_szName*/	_WT(""),\
/*m_szEgName*/	_WT(""),\
/*m_szExplain*/	NULL,\
/*m_dwState*/	LES_HIDED,\
/*m_nDefault*/	0,\
	}

#define DATATYPE_ELEMENT_MASK_2		DATATYPE_ELEMENT_MASK_1,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_3		DATATYPE_ELEMENT_MASK_2,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_4		DATATYPE_ELEMENT_MASK_3,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_5		DATATYPE_ELEMENT_MASK_4,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_6		DATATYPE_ELEMENT_MASK_5,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_7		DATATYPE_ELEMENT_MASK_6,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_8		DATATYPE_ELEMENT_MASK_7,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_9		DATATYPE_ELEMENT_MASK_8,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_10	DATATYPE_ELEMENT_MASK_9,DATATYPE_ELEMENT_MASK_1

#define MASK_DATATYPE_ELEMENT_1		DATATYPE_ELEMENT_MASK_1
#define MASK_DATATYPE_ELEMENT_2		DATATYPE_ELEMENT_MASK_2
#define MASK_DATATYPE_ELEMENT_3		DATATYPE_ELEMENT_MASK_3
#define MASK_DATATYPE_ELEMENT_4		DATATYPE_ELEMENT_MASK_4
#define MASK_DATATYPE_ELEMENT_5		DATATYPE_ELEMENT_MASK_5
#define MASK_DATATYPE_ELEMENT_6		DATATYPE_ELEMENT_MASK_6
#define MASK_DATATYPE_ELEMENT_7		DATATYPE_ELEMENT_MASK_7
#define MASK_DATATYPE_ELEMENT_8		DATATYPE_ELEMENT_MASK_8
#define MASK_DATATYPE_ELEMENT_9		DATATYPE_ELEMENT_MASK_9
#define MASK_DATATYPE_ELEMENT_10	DATATYPE_ELEMENT_MASK_10


//空白函数指针占位符
#define NULL_1	 NULL
#define NULL_2	 NULL,NULL
#define NULL_3	 NULL_2,NULL_1
#define NULL_4	 NULL_3,NULL_1
#define NULL_5	 NULL_4,NULL_1
#define NULL_6	 NULL_5,NULL_1
#define NULL_7	 NULL_6,NULL_1
#define NULL_8	 NULL_7,NULL_1
#define NULL_9	 NULL_8,NULL_1
#define NULL_10	 NULL_9,NULL_1

#define	MASK_NULL_1		NULL_1
#define MASK_NULL_2		NULL_2
#define MASK_NULL_3		NULL_3
#define MASK_NULL_4		NULL_4
#define MASK_NULL_5		NULL_5
#define MASK_NULL_6		NULL_6
#define MASK_NULL_7		NULL_7
#define MASK_NULL_8		NULL_8
#define MASK_NULL_9		NULL_9
#define MASK_NULL_10	NULL_10


#endif //__FN_SHARE_H