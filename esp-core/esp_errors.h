#ifndef __ESP_ERRORS_H__
#define __ESP_ERRORS_H__

#include "esp_serverapi.h"

struct ESPObject;
typedef ESPObject ESPPage;

void ESP_RuntimeError(ESPPage* page, const char* type, const char* description);
bool ESP_IsRuntimeErrorOccurred(ESPPage* page);
bool ESP_ProcessRuntimeError(ESPServerAPI* server_api);

struct ESPRuntimeError 
{
};
typedef struct ESPRuntimeError ESPRuntimeError;


#endif //__ESP_ERRORS_H__
