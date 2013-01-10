#ifndef __IMPL_ESP_SERVER_API__
#define __IMPL_ESP_SERVER_API__

#include <apr_tables.h>
#include <apr_strings.h>
#include "../esp-core/esp_serverapi.h"

#include <httpd.h>
#include <http_config.h>
#include <http_core.h>
#include <http_main.h>
#include <http_protocol.h>
#include <http_request.h>
#include <http_connection.h>
#include <http_log.h>

class ApacheESPServerAPI_Impl : public ESPServerAPI
{
private:
	request_rec* r;
public:
	ApacheESPServerAPI_Impl(request_rec* _r) : r(_r) {}
	virtual ~ApacheESPServerAPI_Impl() {}

public:
	virtual int  GetAPIVersion() { return 1; }
	virtual bool GetServerVariable(const char* szName, const char** pszValue, bool& needFree)
	{
		return false; //FIXME
	}
	virtual bool GetServerVariable(ESPCGIVarType varCGI, const char** pszValue, bool& needFree)
	{
		return false; //FIXME
	}
	virtual bool GetHttpHeaderIn(const char* szName, const char** pszValue, bool& needFree)
	{
		*pszValue = apr_table_get(r->headers_in, szName);
		needFree = false;
		return true;
	}
	virtual bool SetHttpHeaderOut(const char* szName, const char* szValue)
	{
		apr_table_set(r->headers_out, szName, szValue);
		return true;
	}
	virtual bool GetHttpHeaderErr(const char* szName, const char** pszValue, bool& needFree)
	{
		*pszValue = (char*) apr_table_get(r->err_headers_out, szName);
		needFree = false;
		return true;
	}
	virtual bool SetHttpHeaderErr(const char* szName, const char* szValue)
	{
		apr_table_set(r->err_headers_out, szName, szValue);
		return true;
	}
	virtual void GetRequestURI(const char** pszURI, bool& needFree)
	{
		if(r->args == NULL || r->args[0] == '\0')
		{
			*pszURI = r->uri;
			needFree = false;
			return;
		}
		int lenURI  = strlen(r->uri);
		int lenArgs = strlen(r->args);
		char* p = (char*) malloc(lenURI + lenArgs + 2);
		memcpy(p, r->uri, lenURI); //inlucde pathinfo in r->uri
		memcpy(p + lenURI, "?", 1);
		memcpy(p + lenURI + 1, r->args, lenArgs + 1); //add query string
		*pszURI = p;
		needFree = true;
	}
	virtual void GetScriptName(const char** pszScriptName, bool& needFree)
	{
		//r->uri结尾有path_info需去除
		if(r->path_info == NULL || r->path_info[0] == '\0')
		{
			*pszScriptName = r->uri;
			needFree = false;
			return;
		} else {
			int lenPathInfo = strlen(r->path_info);
			int lenScriptName = strlen(r->uri) - lenPathInfo;
			char* p = (char*) malloc(lenScriptName + 1);
			memcpy(p, r->uri, lenScriptName);
			p[lenScriptName] = '\0';
			*pszScriptName = p;
			needFree = true;
		}
	}
	virtual void GetPathInfo(const char** pszPathInfo, bool& needFree)
	{
		*pszPathInfo = r->path_info;
		needFree = false;
	}
	virtual void GetQueryString(const char** pszQueryString, bool& needFree)
	{
		*pszQueryString = r->args;
		needFree = false;
	}
	virtual int  GetHttpStatusCode()
	{
		return r->status;
	}
	virtual void SetHttpStatusCode(int status)
	{
		r->status = status;
	}
	virtual bool GetContentType(const char** pszContentType, bool& needFree)
	{
		*pszContentType = (char*) r->content_type;
		needFree = false;
		return false;
	}
	virtual bool SetContentType(const char* szContentType)
	{
		r->content_type = apr_pstrdup(r->pool, szContentType);
		return true;
	}
	virtual bool SetContentLength(int length)
	{
		return false; //FIXME
	}
	virtual bool Redirect(const char* szURI, int code)
	{
		r->status = code;
		apr_table_set(r->headers_out, "Location", szURI);
		return true;
	}
	virtual bool InternalRedirect(const char* szURI)
	{
		ap_internal_redirect(szURI, r);
		return true;
	}
	virtual int ReadRequestData(int maxReadLength, ESPDataWriter& writer) //maxReadLength==-1表示读取全部
	{
		return 0; //FIXME
	}
	virtual bool WriteResponeData(const void* data, int length) //length==-1表示长度为strlen((char*)data)
	{
		if(length > 0)
			ap_rwrite(data, length, r);
		else if(length == -1)
			ap_rputs((char*)data, r);
		else
			return false;
		return true;
	}
	virtual ESPRequestMethod GetRequestMethod()
	{
		static ESPRequestMethod x[] = {
			/*0 M_GET*/  ESPRequestMethod_GET,
			/*1 M_PUT*/  ESPRequestMethod_PUT,
			/*2 M_POST*/ ESPRequestMethod_POST,
			/*3 M_DELETE*/  ESPRequestMethod_DELETE,
			/*4 M_CONNECT*/ ESPRequestMethod_CONNECT,
			/*5 M_OPTIONS*/ ESPRequestMethod_OPTIONS,
			/*6 M_TRACE*/   ESPRequestMethod_TRACE,
			/*7 M_PATCH*/   ESPRequestMethod_PATCH,
		};
		return (r->method_number <= M_PATCH ? x[r->method_number] : ESPRequestMethod_UNKNOWN);
	}
	virtual bool GetCookie(const char** pszCookie, bool& needFree)
	{
		*pszCookie = apr_table_get(r->headers_in, "cookie");
		needFree = false;
		return true;
	}
	virtual bool SetCookie(const char* szCookie)
	{
		apr_table_set(r->headers_out, "set-cookie", szCookie);
		return true;
	}
	virtual apr_time_t GetRequestTime()
	{
		return r->request_time;
	}
	virtual apr_pool_t* GetRequestPool()
	{
		return r->pool;
	}
	virtual void FreeData(const void* p)
	{
		free((void*)p);
	}
};


#endif //__IMPL_ESP_SERVER_API__
