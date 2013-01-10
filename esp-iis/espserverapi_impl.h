#ifndef __IMPL_ESP_SERVER_API__
#define __IMPL_ESP_SERVER_API__

#include <assert.h>
#include <string>
#include <httpext.h>
#include <apr_tables.h>
#include <apr_strings.h>
#include <apr_time.h>
#include "../esp-core/esp_serverapi.h"

static output2(EXTENSION_CONTROL_BLOCK* pECB, const char* szText)
{
	DWORD x = strlen(szText);
	pECB->WriteClient(pECB->ConnID, (char*)szText, &x, 0);
	x = 2;
	pECB->WriteClient(pECB->ConnID, "\r\n", &x, 0);
}


// by Liigo, 2012-6-2
class IISESPServerAPI_Impl : public ESPServerAPI
{
private:
	EXTENSION_CONTROL_BLOCK* pECB;
	apr_pool_t* pool;
public:
	IISESPServerAPI_Impl(EXTENSION_CONTROL_BLOCK* _pECB) : pECB(_pECB), pool(NULL) {}
	virtual ~IISESPServerAPI_Impl() { if(pool) apr_pool_destroy(pool); }

public:
	std::string cookie;
public:
	virtual int  GetAPIVersion() { return 1; }
	virtual bool GetServerVariable(const char* szName, const char** pszValue, bool& needFree)
	{
		DWORD dwBufferLen = 256;
		char* pBuffer = (char*) malloc(dwBufferLen); assert(pBuffer);
		if(pECB->GetServerVariable(pECB->ConnID, (char*)szName, pBuffer, &dwBufferLen))
		{
			*pszValue = pBuffer; needFree = true;
			return true;
		} else {
			if(GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				pBuffer = (char*) realloc(pBuffer, dwBufferLen); assert(pBuffer);
				if(pECB->GetServerVariable(pECB->ConnID, (char*)szName, pBuffer, &dwBufferLen))
				{
					*pszValue = pBuffer; needFree = true;
					return true;
				}
			}
		}
		free(pBuffer);
		*pszValue = NULL;
		return false;
	}
	virtual bool GetServerVariable(ESPCGIVarType varCGI, const char** pszValue, bool& needFree)
	{
		return false; //FIXME
	}
	virtual bool GetHttpHeaderIn(const char* szName, const char** pszValue, bool& needFree)
	{
		return GetServerVariable(szName, pszValue, needFree);
	}
	virtual bool SetHttpHeaderOut(const char* szName, const char* szValue)
	{
		//FIXME
		//apr_table_set(r->headers_out, szName, szValue);
		return true;
	}
	virtual bool GetHttpHeaderErr(const char* szName, const char** pszValue, bool& needFree)
	{
		//FIXME
		//*pszValue = (char*) apr_table_get(r->err_headers_out, szName);
		needFree = false;
		return true;
	}
	virtual bool SetHttpHeaderErr(const char* szName, const char* szValue)
	{
		//apr_table_set(r->err_headers_out, szName, szValue);
		return true;
	}
	virtual void GetRequestURI(const char** pszURI, bool& needFree)
	{
		GetServerVariable("URL", pszURI, needFree);
	}
	virtual void GetScriptName(const char** pszScriptName, bool& needFree)
	{
		GetServerVariable("SCRIPT_NAME", pszScriptName, needFree);
	}
	virtual void GetPathInfo(const char** pszPathInfo, bool& needFree)
	{
		//*pszPathInfo = pECB->lpszPathInfo; //�Ҳ�! pECB->lpszPathInfo ������PATH_INFOѽ! MSDN��

		*pszPathInfo = NULL;
		needFree = false;
		char* pDot = strchr(pECB->lpszPathInfo, '.');
		if(pDot)
		{
			char* pSlash = strchr(pDot + 1, '/');
			if(pSlash)
				*pszPathInfo = pSlash;
		}
	}
	virtual void GetQueryString(const char** pszQueryString, bool& needFree)
	{
		*pszQueryString = pECB->lpszQueryString;
		needFree = false;
	}
	virtual int  GetHttpStatusCode()
	{
		return (int) pECB->dwHttpStatusCode;
	}
	virtual void SetHttpStatusCode(int status)
	{
		pECB->dwHttpStatusCode = (DWORD)status;
	}
	virtual bool GetContentType(const char** pszContentType, bool& needFree)
	{
		*pszContentType = pECB->lpszContentType;
		needFree = false;
		return true;
	}
	virtual bool SetContentType(const char* szContentType)
	{
		//FIXME: ��ô���϶���������ģ���Ϊ���ͻظ�ͷֻ��һ�λ��ᣬ��Ӧ����SetContentType��ռ
		std::string headers("Content-Type: ");
		headers += szContentType;
		headers += "\r\n\r\n";
		return SendResponseHeader(std::string(), headers);
	}
	virtual bool SetContentLength(int length)
	{
		return false; //FIXME
	}
	virtual bool Redirect(const char* szURI, int code)
	{
		std::string status(code == 301 ? "301 Moved Permanently" : "302 Moved Temporarily");
		std::string headers("Location: ");
		headers += szURI; headers += "\r\n";
		if(cookie.size() > 0)
		{
			headers += "Set-Cookie: "; headers += cookie; headers += "\r\n";
		}
		headers += "\r\n";
		return SendResponseHeader(status, headers);
	}
	virtual bool InternalRedirect(const char* szURI)
	{
		//https://github.com/apache/httpd/blob/f7c1dbf9401a76bd4710c6685a2fbf4de30be3d3/APACHE_1_3_42/src/os/win32/mod_isapi.c
		if(szURI == NULL || *szURI == '\0') return false;
		DWORD size = strlen(szURI);
		return pECB->ServerSupportFunction(pECB->ConnID, HSE_REQ_SEND_URL, (void*)szURI, &size, NULL) == TRUE;
	}
	virtual int ReadRequestData(int maxReadLength, ESPDataWriter& writer) //maxReadLength==-1��ʾ��ȡȫ��
	{
		if(maxReadLength == 0)
			return 0;
		if(maxReadLength == -1)
		{
			if(pECB->cbAvailable == pECB->cbTotalBytes)
			{
				//�������ݶ���pECB->lpbData���������ReadClient()
				writer.WriteData(pECB->lpbData, pECB->cbAvailable);
				return pECB->cbAvailable;
			}
			maxReadLength = pECB->cbTotalBytes; //content length
		}
		if(maxReadLength != -1) //pECB->cbTotalBytes maybe -1(0xffffffff)
		{
			const int bufferSize = 512;
			char buffer[bufferSize]; 
			DWORD dwReadSize = 0; //��¼�Ѿ���ȡ�����ݳ���
			
			while(1)
			{
				DWORD dwSize;
				if(maxReadLength - dwReadSize >= bufferSize)
					dwSize = bufferSize;
				else
					dwSize = maxReadLength - dwReadSize; //��֤��ȡ���Ȳ�����maxReadLength
				if(dwSize == 0)
					return dwReadSize;
				if(pECB->ReadClient(pECB->ConnID, buffer, &dwSize))
				{
					if(dwSize > 0)
					{
						writer.WriteData(buffer, dwSize);
						dwReadSize += dwSize;
					} else {
						return dwReadSize; //�������
					}
				} else {
					return dwReadSize; //��ȡ�������Ѷ�����󣬺󷵻��Ѿ���ȡ�����ݳ���
				}
			}

		} else {
			//��֧��һ���Զ�ȡ����4G����(pECB->cbTotalBytes==-1)��ESPDataWriter����Ҳ���ɲ�����ô�ࡣ
			//��ε���ReadRequestData()ÿ�����ƶ�ȡ���ȼ��ɽ�����⡣
			return 0;
		}
		return 0;
	}
	virtual bool WriteResponeData(const void* data, int length) //length==-1��ʾ����Ϊstrlen((char*)data)
	{
		if(length > 0)
		{
			return pECB->WriteClient(pECB->ConnID, (void*)data, (DWORD*)&length, HSE_IO_SYNC) == TRUE;
		}
		else if(length == -1)
		{
			length = strlen((char*)data);
			return pECB->WriteClient(pECB->ConnID, (void*)data, (DWORD*)&length, HSE_IO_SYNC) == TRUE;
		}
		return false;
	}
	virtual ESPRequestMethod GetRequestMethod()
	{
		//TODO: �����Ż�����ϣ�����Ա�洢
		if(strcmp(pECB->lpszMethod, "GET") == 0)
			return ESPRequestMethod_GET;
		else if(strcmp(pECB->lpszMethod, "POST") == 0)
			return ESPRequestMethod_POST;
		else if(strcmp(pECB->lpszMethod, "PUT") == 0)
			return ESPRequestMethod_PUT;
		//others...
		return (ESPRequestMethod_UNKNOWN);
	}
	virtual bool GetCookie(const char** pszCookie, bool& needFree)
	{
		return GetServerVariable("HTTP_COOKIE", pszCookie, needFree);
	}
	virtual bool SetCookie(const char* szCookie)
	{
		cookie = (szCookie ? szCookie : "");
		return true;
	}
	virtual apr_time_t GetRequestTime()
	{
		return apr_time_now();
	}
	virtual apr_pool_t* GetRequestPool()
	{
		if(pool == NULL)
			apr_pool_create(&pool, NULL);
		assert(pool);
		return pool;
	}
	virtual void FreeData(const void* p)
	{
		free((void*)p);
	}

public:
	//ʾ����SendResponseHeader("301 Moved Permanently", "Location: URL\r\n\r\n");
	bool SendResponseHeader(std::string& status, std::string& headers)
	{
		HSE_SEND_HEADER_EX_INFO s;
		s.pszStatus = status.c_str();
		s.pszHeader = headers.c_str();
		s.cchStatus = status.size();
		s.cchHeader = headers.size();
		s.fKeepConn = FALSE;
		return pECB->ServerSupportFunction(pECB->ConnID, HSE_REQ_SEND_RESPONSE_HEADER_EX, &s, 0, 0) == TRUE;
	}
};


#endif //__IMPL_ESP_SERVER_API__
