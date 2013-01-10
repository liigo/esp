#ifndef __ESP_SERVERAPI_H__
#define __ESP_SERVERAPI_H__

#include <apr_pools.h>
#include <apr_time.h>

//此文件中定义“WEB服务器的ESP插件”应该提供的接口

enum ESPRequestMethod
{
	ESPRequestMethod_UNKNOWN = 0,
	ESPRequestMethod_HEAD,
	ESPRequestMethod_GET,
	ESPRequestMethod_POST,
	ESPRequestMethod_PUT,
	ESPRequestMethod_DELETE,
	ESPRequestMethod_TRACE,
	ESPRequestMethod_OPTIONS,
	ESPRequestMethod_CONNECT,
	ESPRequestMethod_PATCH,
};

enum ESPCGIVarType
{
	ESP_CGI_QUERY_STRING = 0,
	ESP_CGI_REMOTE_ADDR,
};

class ESPDataWriter
{
public:
	virtual ~ESPDataWriter() {}
	virtual void WriteData(void* pData, int nLength) = 0;
};

class ESPServerAPI
{
public:
	ESPServerAPI() {}
	virtual ~ESPServerAPI() {}
public:
	virtual int  GetAPIVersion() = 0;
	virtual bool GetServerVariable(const char* szName, const char** pszValue, bool& needFree) = 0;
	virtual bool GetServerVariable(ESPCGIVarType varCGI, const char** pszValue, bool& needFree) = 0;
	virtual bool GetHttpHeaderIn(const char* szName, const char** pszValue, bool& needFree) = 0;
	virtual bool SetHttpHeaderOut(const char* szName, const char* szValue) = 0;
	virtual bool GetHttpHeaderErr(const char* szName, const char** pszValue, bool& needFree) = 0;
	virtual bool SetHttpHeaderErr(const char* szName, const char* szValue) = 0;
	virtual void GetRequestURI(const char** pszURI, bool& needFree) = 0; //with path_info and query_string, if any
	virtual void GetScriptName(const char** pszScriptName, bool& needFree) = 0;
	virtual void GetPathInfo(const char** pszPathInfo, bool& needFree) = 0;
	virtual void GetQueryString(const char** pszQueryString, bool& needFree) = 0;
	virtual int  GetHttpStatusCode() = 0;
	virtual void SetHttpStatusCode(int status) = 0;
	virtual bool GetContentType(const char** pszContentType, bool& needFree) = 0;
	virtual bool SetContentType(const char* szContentType) = 0;
	virtual bool SetContentLength(int length) = 0;
	virtual bool Redirect(const char* szURI, int code) = 0; //code: 301 or 302
	virtual bool InternalRedirect(const char* szURI) = 0;
	virtual int  ReadRequestData(int maxReadLength, ESPDataWriter& writer) = 0; //maxReadLength==-1表示读取全部
	virtual bool WriteResponeData(const void* data, int length) = 0; //length==-1表示长度为strlen((char*)data)
	virtual ESPRequestMethod GetRequestMethod() = 0;
	virtual bool GetCookie(const char** pszCookie, bool& needFree) = 0;
	virtual bool SetCookie(const char* szCookie) = 0;
	virtual apr_time_t GetRequestTime() = 0;
	virtual apr_pool_t* GetRequestPool() = 0;
	virtual void FreeData(const void* p) = 0;
};


#endif //__ESP_SERVERAPI_H__
