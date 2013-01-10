#ifndef __ESP_SESSION_H__
#define __ESP_SESSION_H__

#include <string>
#include "stl_hash_map.h"

struct  ESPObject;
typedef ESPObject ESPPage;

namespace esp_session
{
	typedef STL_HASH_MAP(std::string, std::string) session_kv;
	session_kv* session(ESPPage* page);
}

#endif //__ESP_SESSION_H__
