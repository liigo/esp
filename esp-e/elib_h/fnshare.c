/*
    ��Ȩ������
    ���ļ���ȨΪ�����������������У�����Ȩ����������������������֧�ֿ⣬��ֹ���������κγ��ϡ�
*/
#include "fnshare.h"

INT g_nLastNotifyResult;
PFN_NOTIFY_SYS g_fnNotifySys = NULL;

//add by liigo
//PFN_ON_SYS_NOTIFY g_fn_OnSysNotify = NULL;
/*
�û���ʹ�����´��뼴�ɱ�֤���޸ı��ļ������ﵽ��ʱ����ϵͳͨѶ��Ŀ�ģ�

void My_OnSysNotify (INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
}

extern PFN_ON_SYS_NOTIFY g_fn_OnSysNotify;
g_fn_OnSysNotify = (PFN_ON_SYS_NOTIFY) My_OnSysNotify;

*/
//end add

INT WINAPI ProcessNotifyLib (INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
	INT nRet = NR_OK;
	switch (nMsg)
	{
	case NL_SYS_NOTIFY_FUNCTION:
		g_fnNotifySys = (PFN_NOTIFY_SYS)dwParam1;
		break;
	case NL_FREE_LIB_DATA:
		break;
	default:
		nRet = NR_ERR;
		break;
	}

	/*
	//�����û�����
	if(g_fn_OnSysNotify) 
		nRet = g_fn_OnSysNotify(nMsg,dwParam1,dwParam2);
	*/

	return nRet;
}

INT WINAPI NotifySys (INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
	ASSERT (g_fnNotifySys != NULL);
	if (g_fnNotifySys != NULL)
		return g_nLastNotifyResult = g_fnNotifySys (nMsg, dwParam1, dwParam2);
	else
		return g_nLastNotifyResult = 0;
}

// ʹ��ָ���ı����ݽ����׳�����ʹ�õ��ı����ݡ�
char* CloneTextData (char* ps)
{
    INT nTextLen=0;
	char* pd=NULL;

	if (ps == NULL || *ps == '\0')
        return NULL;

    nTextLen = strlen (ps);
    pd = (char*)NotifySys (NRS_MALLOC, (DWORD)(nTextLen + 1), 0);
    memcpy (pd, ps, nTextLen);
    pd [nTextLen] = '\0';
    return pd;
}

// ʹ��ָ���ı����ݽ����׳�����ʹ�õ��ı����ݡ�
//   nTextLen����ָ���ı����ֵĳ��ȣ������������㣩��
// ���Ϊ-1����ȡps��ȫ�����ȡ�
char* CloneTextDataLen (char* ps, INT nTextLen)
{
    char* pd=NULL;
	if (nTextLen <= 0)
        return NULL;

    pd = (char*)NotifySys (NRS_MALLOC, (DWORD)(nTextLen + 1), 0);
    memcpy (pd, ps, nTextLen);
    pd [nTextLen] = '\0';
    return pd;
}

// ʹ��ָ�����ݽ����׳�����ʹ�õ��ֽڼ����ݡ�
LPBYTE CloneBinData (LPBYTE pData, INT nDataSize)
{
    LPBYTE pd=NULL;
	if (nDataSize == 0)
        return NULL;

    pd = (LPBYTE)NotifySys (NRS_MALLOC, (DWORD)(sizeof (INT) * 2 + nDataSize), 0);
    *(LPINT)pd = 1;
    *(LPINT)(pd + sizeof (INT)) = nDataSize;
    memcpy (pd + sizeof (INT) * 2, pData, nDataSize);
    return pd;
}

// ��������ʱ����
void GReportError (char* szErrText)
{
    NotifySys (NRS_RUNTIME_ERR, (DWORD)szErrText, 0);
}

void* MMalloc (INT nSize)
{
	return (void*)NotifySys (NRS_MALLOC, (DWORD)nSize, 0);
}

void MFree (void* p)
{
	NotifySys (NRS_MFREE, (DWORD)p, 0);
}

// ������������ݲ����׵�ַ����Ա��Ŀ��
LPBYTE GetAryElementInf (void* pAryData, LPINT pnElementCount)
{
	LPINT pnData = (LPINT)pAryData;
	INT nArys = *pnData++;  // ȡ��ά����
	// �����Ա��Ŀ��
	INT nElementCount = 1;
	while (nArys > 0)
	{
		nElementCount *= *pnData++;
		nArys--;
	}

	if (pnElementCount != NULL)
		*pnElementCount = nElementCount;
	return (LPBYTE)pnData;
}

#define DTT_IS_NULL_DATA_TYPE   0
#define DTT_IS_SYS_DATA_TYPE    1
#define DTT_IS_USER_DATA_TYPE   2
#define DTT_IS_LIB_DATA_TYPE    3
// ȡ���������͵����
INT GetDataTypeType (DATA_TYPE dtDataType)
{
	DWORD dw=0;
	if (dtDataType == _SDT_NULL)
		return DTT_IS_NULL_DATA_TYPE;

	dw = dtDataType & 0xC0000000;
	return dw == DTM_SYS_DATA_TYPE_MASK ? DTT_IS_SYS_DATA_TYPE :
			dw == DTM_USER_DATA_TYPE_MASK ? DTT_IS_USER_DATA_TYPE :
			DTT_IS_LIB_DATA_TYPE;
}


// �������������棬���򷵻ؼ١�
BOOL RunWhereStatment (PMDATA_INF pStatmentInf)
{
    if (pStatmentInf->m_dtDataType == SDT_BOOL)
        return pStatmentInf->m_bool;

    if (pStatmentInf->m_dtDataType == SDT_STATMENT)
    {
        DWORD dwEBP = pStatmentInf->m_statment.m_dwSubEBP;
        DWORD dwSubAdr = pStatmentInf->m_statment.m_dwStatmentSubCodeAdr;
        DWORD dwECX, dwEAX;

#ifdef __OS_LINUX_VER
		//todo:

#else
        __asm 
        {
            mov eax, dwEBP
            call dwSubAdr
            mov dwECX, ecx
            mov dwEAX, eax
        }
#endif

        if (dwECX == SDT_BOOL)
            return dwEAX != 0;

        // �ͷ��ı����ֽڼ�������������ڴ档
        if (dwECX == SDT_TEXT || dwECX == SDT_BIN)
            MFree ((void*)dwEAX);
    }

    GReportError ("�������������жϵ���������ֻ�ܽ����߼�������");
    return FALSE;
}

// pdwaryDataΪָ������DWORD�����顣
/*void RunCalcStatment (PMDATA_INF pStatmentInf, CFreqMem& memCalc, LPDWORD pdwaryData,
                      PDATA_TYPE pdtDataType, LPBYTE* ppData, LPINT pnDataSize)
{
    memCalc.Empty ();

    if (pStatmentInf->m_dtDataType != SDT_STATMENT)
    {
        // �ڱ���ʱ�Ѿ�������
        ASSERT ((pStatmentInf->m_dtDataType & DT_IS_ARY) == 0 &&
                GetDataTypeType (pStatmentInf->m_dtDataType) == DTT_IS_SYS_DATA_TYPE);

        *ppData = (LPBYTE)pdwaryData;
        *pdtDataType = pStatmentInf->m_dtDataType;

        switch (pStatmentInf->m_dtDataType)
        {
        case SDT_BYTE:
            *(LPBYTE)pdwaryData = pStatmentInf->m_byte;
            *pnDataSize = sizeof (BYTE);
            break;
        case SDT_SHORT:
            *(SHORT*)pdwaryData = pStatmentInf->m_short;
            *pnDataSize = sizeof (SHORT);
            break;
        case SDT_INT:
            *(INT*)pdwaryData = pStatmentInf->m_int;
            *pnDataSize = sizeof (INT);
            break;
        case SDT_INT64:
            *(INT64*)pdwaryData = pStatmentInf->m_int64;
            *pnDataSize = sizeof (INT64);
            break;
        case SDT_FLOAT:
            *(FLOAT*)pdwaryData = pStatmentInf->m_float;
            *pnDataSize = sizeof (FLOAT);
            break;
        case SDT_DOUBLE:
            *(DOUBLE*)pdwaryData = pStatmentInf->m_double;
            *pnDataSize = sizeof (DOUBLE);
            break;
        case SDT_BOOL:
            *(BOOL*)pdwaryData = pStatmentInf->m_bool;
            *pnDataSize = sizeof (BOOL);
            break;
        case SDT_DATE_TIME:
            *(DATE*)pdwaryData = pStatmentInf->m_date;
            *pnDataSize = sizeof (DATE);
            break;
        case SDT_SUB_PTR:
            *pdwaryData = pStatmentInf->m_dwSubCodeAdr;
            *pnDataSize = sizeof (DWORD);
            break;
        case SDT_TEXT:
            *ppData = (LPBYTE)pStatmentInf->m_pText;
            *pnDataSize = strlen (pStatmentInf->m_pText) + 1;
            break;
        case SDT_BIN:
            *ppData = pStatmentInf->m_pBin + sizeof (INT) * 2;
            *pnDataSize = *(LPINT)(*ppData - sizeof (INT));
            break;
        }
    }
    else
    {
        DWORD dwEBP = pStatmentInf->m_statment.m_dwSubEBP;
        DWORD dwSubAdr = pStatmentInf->m_statment.m_dwStatmentSubCodeAdr;

#ifdef __OS_LINUX_VER
		//todo:

#else
        __asm
        {
            mov eax, dwEBP
            call dwSubAdr
            mov ebx, pdwaryData
            mov dword ptr [ebx], eax
            mov dword ptr [ebx + 4], edx
            mov ebx, pdtDataType
            mov dword ptr [ebx], ecx
        }
#endif

        if (*pdtDataType == SDT_TEXT)
        {
            // �������ص��ı�����ת�Ƶ�memCalc�к����ͷš�
            LPTSTR ps = (LPTSTR)pdwaryData [0];
            if (ps == NULL)
            {
                pdwaryData [0] = 0;
                *ppData = (LPBYTE)pdwaryData;
                *pnDataSize = 1;
            }
            else
            {
                *pnDataSize = strlen (ps) + 1;
                *ppData = memCalc.Alloc (*pnDataSize);
                memcpy (*ppData, ps, *pnDataSize);
                MFree (ps);
            }
        }
        else if (*pdtDataType == SDT_BIN)
        {
            // �������ص��ֽڼ�����ת�Ƶ�memCalc�к����ͷš�
            LPBYTE pb = (LPBYTE)pdwaryData [0];
            if (pb == NULL)
            {
                *ppData = NULL;
                *pnDataSize = 0;
            }
            else
            {
                LPBYTE p = pb + sizeof (INT) * 2;
                *pnDataSize = *(LPINT)(p - sizeof (INT));
                *ppData = memCalc.Alloc (*pnDataSize);
                memcpy (*ppData, p, *pnDataSize);
                MFree (pb);
            }
        }
        else
        {
            *ppData = (LPBYTE)pdwaryData;
            *pnDataSize = GetSysDataTypeDataSize (*pdtDataType);
        }
    }
}
*/

INT GetSysDataTypeDataSize (DATA_TYPE dtSysDataType)
{
    ASSERT (sizeof (DWORD) == 4);
    switch (dtSysDataType)
    {
    case SDT_BYTE:
        ASSERT (sizeof (BYTE) == 1);
        return sizeof (BYTE);
    case SDT_SHORT:
        ASSERT (sizeof (SHORT) == 2);
        return sizeof (SHORT);
    case SDT_BOOL:
        ASSERT (sizeof (BOOL) == 4);
        return sizeof (BOOL);
    case SDT_INT:
        ASSERT (sizeof (INT) == 4);
        return sizeof (INT);
    case SDT_FLOAT:
        ASSERT (sizeof (FLOAT) == 4);
        return sizeof (FLOAT);
    case SDT_SUB_PTR:    // ��¼�ӳ������ĵ�ַָ��
        return sizeof (DWORD);
    case SDT_TEXT:    // �ı��ͺ��ֽڼ���Ϊһ��ָ��,���Ϊ�ĸ��ֽ�.
    case SDT_BIN:
        return sizeof (DWORD);
    case SDT_INT64:
        ASSERT (sizeof (INT64) == 8);
        return sizeof (INT64);
    case SDT_DOUBLE:
        ASSERT (sizeof (DOUBLE) == 8);
        return sizeof (DOUBLE);
    case SDT_DATE_TIME:
        ASSERT (sizeof (DATE) == 8);
        return sizeof (DATE);
    default:
        ASSERT (FALSE);
        return 0;
    }
    return 0;
}


void SetMDataValue (PMDATA_INF pRetData, LPBYTE pData, INT nDataSize)
{
    switch (pRetData->m_dtDataType)
    {
    case SDT_BYTE:
        pRetData->m_byte = *pData;
        break;
    case SDT_SHORT:
        pRetData->m_short = *(SHORT*)pData;
        break;
    case SDT_INT:
        pRetData->m_int = *(INT*)pData;
        break;
    case SDT_INT64:
        pRetData->m_int64 = *(INT64*)pData;
        break;
    case SDT_FLOAT:
        pRetData->m_float = *(FLOAT*)pData;
        break;
    case SDT_DOUBLE:
        pRetData->m_double = *(DOUBLE*)pData;
        break;
    case SDT_BOOL:
        pRetData->m_bool = (*(BOOL*)pData != FALSE);
        break;
    case SDT_DATE_TIME:
        pRetData->m_date = max (MIN_DATE, min (MAX_DATE, *(DATE*)pData));
        break;
    case SDT_SUB_PTR:
        pRetData->m_dwSubCodeAdr = *(LPDWORD)pData;
        break;
    case SDT_TEXT: {
        INT nEndPos = FindByte (pData, nDataSize, 0);
        pRetData->m_pText = CloneTextDataLen ((char*)pData,
                (nEndPos != -1 ? nEndPos : nDataSize));
        break; }
    case SDT_BIN:
        pRetData->m_pBin = CloneBinData (pData, nDataSize);
        break;
    DEFAULT_FAILD;
    }
}

void ZeroMem (LPBYTE pDest, DWORD dwLength)
{
	if (dwLength == 0)
		return;
	else if (dwLength == 1)
		*pDest = 0;
	else if (dwLength == sizeof (WORD))
		*(LPWORD)pDest = 0;
	else if (dwLength == sizeof (DWORD))
		*(LPDWORD)pDest = 0;
	else
		memset(pDest, 0, dwLength);
}

void MoveMem (LPBYTE pDest, LPBYTE pSrc, DWORD dwLength)
{
	if (dwLength == 0)
		return;
	else if (dwLength == 1)
		*pDest = *pSrc;
	else if (dwLength == sizeof (WORD))
		*(LPWORD)pDest = *(LPWORD)pSrc;
	else if (dwLength == sizeof (DWORD))
		*(LPDWORD)pDest = *(LPDWORD)pSrc;
	else
		memmove(pDest, pSrc, dwLength);
}

void CopyMem (LPBYTE pDest, LPBYTE pSrc, DWORD dwLength)
{
	if (dwLength == 0)
		return;
	else if (dwLength == 1)
		*pDest = *pSrc;
	else if (dwLength == sizeof (WORD))
		*(LPWORD)pDest = *(LPWORD)pSrc;
	else if (dwLength == sizeof (DWORD))
		*(LPDWORD)pDest = *(LPDWORD)pSrc;
	else
		memcpy(pDest, pSrc, dwLength);
}

// ���ص����ֽ�ƫ������
INT FindByte (LPBYTE pTable, INT count, BYTE btFind)
{ 
	INT nRetOffset = -1;

	if (count > 0)
	{
		ASSERT (pTable != NULL);
		if (*pTable == btFind)  return 0;

#ifdef __OS_LINUX_VER
		//todo:

#else
		__asm
		{
			push edi
			push eax
			push ecx

			mov al, btFind
			mov ecx, count
			push ecx
			mov edi, dword ptr [pTable]

	        cld
			repne scasb
			pop eax
			jnz quit

			inc ecx
			sub eax, ecx
			mov dword ptr [nRetOffset], eax
quit:
			pop ecx
			pop eax
			pop edi
		}
#endif
	}

	return nRetOffset;
}

// ���صĲ����ֽ���������DWORDƫ������
INT FindDWord (LPDWORD pdwTable, INT count, DWORD dwFind)
{ 
	INT nRetOffset = -1;

	if (count > 0)
	{
		if (*pdwTable == dwFind)  return 0;

		ASSERT (pdwTable != NULL);
#ifdef __OS_LINUX_VER
		//todo:

#else
		__asm
		{
			push edi
			push eax
			push ecx

			mov eax, dwFind
			mov ecx, count
			push ecx
			mov edi, dword ptr [pdwTable]

	        cld
			repne scasd
			pop eax
			jnz quit

			inc ecx
			sub eax, ecx
			mov dword ptr [nRetOffset], eax
quit:
			pop ecx
			pop eax
			pop edi
		}
#endif
	}

	return nRetOffset;
}

// ���صĲ����ֽ���������WORDƫ������
INT FindWord (LPWORD pwTable, INT count, WORD wFind)
{ 
	INT nRetOffset = -1;

	if (count > 0)
	{
		ASSERT (pwTable != NULL);
#ifdef __OS_LINUX_VER
		//todo:

#else
		__asm
		{
			push edi
			push eax
			push ecx

			mov ax, wFind
			mov ecx, count
			push ecx
			mov edi, dword ptr [pwTable]

	        cld
			repne scasw
			pop eax
			jnz quit

			inc ecx
			sub eax, ecx
			mov dword ptr [nRetOffset], eax
quit:
			pop ecx
			pop eax
			pop edi
		}
#endif
	}

	return nRetOffset;
}
