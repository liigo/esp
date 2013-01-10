#include "esp_session.h"
#include <stdlib.h>
#include <apr_strings.h>
#include <apr_pools.h>
#include <apr_time.h>
#include "esp_objects.h"
#include "esp_serverapi.h"
#include "md5.h"
#include "string_util.h"

using namespace std;

namespace esp_session
{
	typedef STL_HASH_MAP(string, string) session_kv;

	struct session_data
	{
		session_data(apr_time_t tm = 0) :last_request_time(tm) {}
		apr_time_t last_request_time;
		session_kv session;
	};

	typedef STL_HASH_MAP(string, session_data) session_table;

	static session_table g_sessions;

	static string get_next_session_id(void)
	{
		char buf[20] = {0};
		char result[32] = {0};
		sprintf(buf, "%d", (int)apr_time_now());
		string str_now = buf; //itoa((int)apr_time_now(), buf, 10);
		int retry_times = 1;
		do 
		{
			sprintf(buf, "%d", retry_times++); //itoa(retry_times, buf, 10);
			str_now.append(buf);
			GetMD5((BYTE*)str_now.c_str(), str_now.length(), result);
		} while(g_sessions.find(result) != g_sessions.end());

		return result;
	}

	static apr_time_t g_last_check_time = 0;

	const static char* ESP_SESSION_COOKIE_NAME = "espsid";
	const static int ESP_SESSION_EXPRIATION_PERIOD_SEC = 60 * 30; // seconds

	static void check_for_expiration(apr_time_t request_time)
	{
		if(g_last_check_time == 0)
		{
			g_last_check_time = request_time;
		}
		else
		{
			apr_time_t time_now = apr_time_now(); 
			if(apr_time_sec(time_now) - apr_time_sec(g_last_check_time) >= ESP_SESSION_EXPRIATION_PERIOD_SEC)
			{
				bool erased = true;
				while(erased)
				{
					erased = false;
					for(session_table::iterator it = g_sessions.begin(); it != g_sessions.end(); ++it)
					{
						session_data& sd = (*it).second;
						if(apr_time_sec(request_time) - apr_time_sec(sd.last_request_time) >= ESP_SESSION_EXPRIATION_PERIOD_SEC)
						{
							g_sessions.erase(it);
							erased = true;
							break;
						}
					}
				}
			}
			g_last_check_time = request_time;
		}
	}

	static const char* get_session_id_form_cookie(char* cookie)
	{
		if(!cookie) return NULL;
		char* state = NULL;
		char* kv = apr_strtok(cookie, ";", &state);
		while(kv)
		{
			while(*kv == ' ')
				kv++;
			char* state2 = NULL;
			char* key = apr_strtok(kv, "=", &state2);
			while(*key == ' ')
				key++;
			char* value = NULL;
			if(key)
			{
				value = apr_strtok(NULL, "=", &state2);
				while(*value == ' ')
					value++;
			}
			while(key && value)
			{
				if(stricmp(key, ESP_SESSION_COOKIE_NAME) == 0)
				{
					return value;
				}
				key = apr_strtok(NULL, "=", &state2);
				if(key)
					value = apr_strtok(NULL, "=", &state2);
			}
			kv = apr_strtok(NULL, ";", &state);
		}
		return NULL;
	}

	static session_kv* new_session(ESPPage* page, apr_time_t request_time)
	{
		string session_id = get_next_session_id();
		session_kv* pResult = &((g_sessions[session_id] = session_data(request_time)).session);
		apr_time_t expries_time = apr_time_from_sec(apr_time_sec(request_time) + ESP_SESSION_EXPRIATION_PERIOD_SEC);
		char time_buf[APR_RFC822_DATE_LEN] = {0};
		apr_rfc822_date(time_buf, expries_time);
		apr_pool_t* pool = page->server_api->GetRequestPool();
		char* cookie_str = apr_psprintf(pool, "%s=%s;expires=%s", ESP_SESSION_COOKIE_NAME, session_id.c_str(), time_buf);
		page->server_api->SetCookie(cookie_str);
		return pResult;
	}

	session_kv* session(ESPPage* page)
	{
		apr_time_t request_time = page->server_api->GetRequestTime();
		check_for_expiration(request_time);
		session_kv* pResult = NULL;
		const char* cookie = NULL; bool needFreeCookie = false;
		page->server_api->GetCookie(&cookie, needFreeCookie);
		char* cookie_str = NULL;
		const char* espsid = NULL;
		if(cookie)
		{
			cookie_str = (char*)malloc(strlen(cookie) + sizeof(char));
			strcpy(cookie_str, cookie);
			espsid = get_session_id_form_cookie(cookie_str);
		}
		if(!espsid)
		{
			pResult = new_session(page, request_time);
		}
		else
		{
			session_table::iterator ssn = g_sessions.find(espsid);
			if(ssn != g_sessions.end())
			{
				pResult = &((*ssn).second.session);
				(*ssn).second.last_request_time = request_time;
			}
			else
				pResult = new_session(page, request_time);
		}

		if(cookie_str) free(cookie_str);
		if(cookie && needFreeCookie)
			page->server_api->FreeData((char*)cookie);

		return pResult;
	}

}