#if !defined(__CMEM_H)
#define __CMEM_H

#ifdef __OS_LINUX_VER
	#include <strings.h>
	#include "mtypes.h"
#else
	#include <wtypes.h>
#endif  /*__OS_LINUX_VER*/

#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>
#include "fnshare.h"

/*CMem*/

#define	PAGE_SIZE			256		/*页尺寸*/
#define	PAGE_COUNT			32		/*页数目*/
#define	PAGE_BUF_SIZE		PAGE_COUNT * PAGE_SIZE

typedef struct
{
	int m_nPageUsedCount;			/*页当前已经被使用的数目*/
	BYTE m_btaryUsed [PAGE_COUNT];	/*记录每一页是否已被使用*/
	BYTE m_buf [PAGE_BUF_SIZE];
}
MEM_BUF;
typedef MEM_BUF* PMEM_BUF;

#define	FM_MAX_FREE_BUF_SIZE	128
#define	FM_GROW_SIZE			128

typedef struct
{
	LPBYTE m_pData;
	int m_nAllocedSize;
	int m_nSize;

	PMEM_BUF m_pMemBuf;
}
CMem;


typedef CMem XString;
typedef CMem CDWordArray;

#define CMem_destroy_(pThis)  CMem_Free (pThis)

#define XString_init_(pThis)  CMem_init_((CMem*)pThis)
#define XString_destroy_(pThis)  CMem_destroy_(pThis)

#define CDWordArray_init_(pThis)  CMem_init_(pThis)
#define CDWordArray_destroy_(pThis)  CMem_destroy_(pThis)

/************************************************************************/
#ifdef __cplusplus
extern "C" {
#if 0
}
#endif
#endif

void CMem_init_ (CMem* pThis);
LPBYTE CMem_GetPtr (CMem* pThis);
int CMem_GetSize (CMem* pThis);
BOOL CMem_IsEmpty (CMem* pThis);
void CMem_Empty (CMem* pThis);
BOOL CMem_CopyFrom (CMem* pThis, LPBYTE pData, int nSize);
LPBYTE CMem_Alloc (CMem* pThis, int nSize);
LPBYTE CMem_Realloc (CMem* pThis, int nSize);
void CMem_Free (CMem* pThis);
void CMem_AddDouble (CMem* pThis, double db);
void CMem_AddFloat (CMem* pThis, float flt);
void CMem_AddLong (CMem* pThis, long lVal);
void CMem_AddDWord (CMem* pThis, DWORD dw);
void CMem_AddInt (CMem* pThis, int n);
void CMem_AddWord (CMem* pThis, WORD w);
void CMem_AddShort (CMem* pThis, short sht);
void CMem_AddByte (CMem* pThis, BYTE bt);
void CMem_AddStr (CMem* pThis, char* pstr);
void CMem_AddText (CMem* pThis, char* pstr);
void CMem_XchgMem (CMem* pThis, CMem* pMem);
int CMem_ReadFile (CMem* pThis, char* szFileName, int nReadLength);
BOOL CMem_WriteFile (CMem* pThis, char* szFileName, int nWriteLength);
BOOL CMem_Insert (CMem* pThis, int nOffset, LPBYTE pData, int nSize);
BOOL CMem_Append (CMem* pThis, LPBYTE pData, int nSize);
BOOL CMem_Replace (CMem* pThis, int nOffset, int nSize,
					LPBYTE pReplaceData, int nReplaceSize);
BOOL CMem_Remove (CMem* pThis, int nOffset, int nSize);


/*XString*/
#define FORMAT_BUFFER_LENGTH	1024 /*use by XString_SetTextF(...) and other*/

void XString_init_str_ (XString* pThis, XString* pStrSrc);
void XString_init_text_ (XString* pThis, char* ps);
void XString_init_textF_ (XString* pThis, char* pFormat, ...);
char* XString_GetText (XString* pThis);
int XString_GetLength (XString* pThis);
BOOL XString_IsEmpty (XString* pThis);
void XString_Empty (XString* pThis);
void XString_SetStr (XString* pThis, XString* pStrSrc);
void XString_SetChar (XString* pThis, char ch);
void XString_SetText (XString* pThis, char* ps);
void XString_SetTextF (XString* pThis, char* pFormat, ...);
void XString_SetTextPart (XString* pThis, char* ps, int nLength);
void XString_AddStr (XString* pThis, XString* pStrSrc);
void XString_AddChar (XString* pThis, char ch);
void XString_AddText (XString* pThis, char* ps);
void XString_AddTextF (XString* pThis, char* pFormat, ...);
void XString_GetLeft (XString* pThis, int nCount, XString* pDest);
void XString_GetRight (XString* pThis, int nCount, XString* pDest);
void XString_MakeUpper (XString* pThis);
void XString_MakeLower (XString* pThis);
void XString_TrimRight (XString* pThis);
void XString_TrimLeft (XString* pThis);
BOOL XString_EndOfText (XString* pThis, char* ps);
BOOL XString_EndOfChar (XString* pThis, char ch);
void XString_Delete (XString* pThis, int nIndex, int nCount);
void XString_Insert (XString* pThis, int nIndex, char* szText);

/*CDWordArray*/
int CDWordArray_GetSize (CDWordArray* pThis);
BOOL CDWordArray_SetSize (CDWordArray* pThis, int nNewSize);
int CDWordArray_GetUpperBound (CDWordArray* pThis);
void CDWordArray_RemoveAll (CDWordArray* pThis);
LPDWORD CDWordArray_GetPtr (CDWordArray* pThis);
DWORD CDWordArray_GetAt (CDWordArray* pThis, int nIndex);
void CDWordArray_SetAt (CDWordArray* pThis, int nIndex, DWORD dwElement);
int CDWordArray_Append (CDWordArray* pThis, CDWordArray* pSrc);
void CDWordArray_Copy (CDWordArray* pThis, CDWordArray* pSrc);
void CDWordArray_Add (CDWordArray* pThis, DWORD dwElement);
void CDWordArray_InsertAt (CDWordArray* pThis, int nIndex, DWORD dwElement);
void CDWordArray_RemoveAt (CDWordArray* pThis, int nIndex, int nCount);
INT CDWordArray_Find (CDWordArray* pThis, DWORD dwFind);

#ifdef __cplusplus
}
#endif

#endif /*__CMEM_H*/

