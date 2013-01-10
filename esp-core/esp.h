#ifndef __ESP_H__
#define __ESP_H__

#include "esp_clientapi.h"
#include "esp_errors.h"
#include "esp_globals.h"
#include "esp_log.h"
#include "esp_managers.h"
#include "esp_objects.h"
#include "esp_prop.h"
#include "esp_serverapi.h"
#include "esp_session.h"
#include "esp_template.h"
#include "esp_utils.h"

void ESP_Initialize();
void ESP_Finalize();

ESPPage* ESP_AcquirePage(const char* typeName, const char* instanceName, ESPServerAPI* serverApi);
void ESP_ReleasePage(ESPPage* page);


#endif //__ESP_H__
