#include "esp_errors.h"
#include "esp_objects.h"
#include "esp_serverapi.h"

#define ESP_INTERNAL_ERROR  514  // ������/��Ҫ�� ����˼���ǳ�Ӧ��������

//����ESP����ʱ����(����������Ҫ������ֹ)
void ESP_RuntimeError(ESPPage* page, const char* type, const char* description)
{
	if(type)
		page->server_api->SetHttpHeaderErr("esp-runtime-error-type", type);
	if(description)
		page->server_api->SetHttpHeaderErr("esp-runtime-error-description", description);

	page->server_api->SetHttpStatusCode(ESP_INTERNAL_ERROR);
	page->server_api->InternalRedirect("/esp-runtime-error");

	ESPRuntimeError esp_runtime_error;
	throw esp_runtime_error;
}

//�ж��Ƿ��ѷ���ESP����ʱ����
bool ESP_IsRuntimeErrorOccurred(ESPPage* page)
{
	return (page->server_api->GetHttpStatusCode() == ESP_INTERNAL_ERROR); //see ESP_RuntimeError()
}

//����ESP����ʱ����
bool ESP_ProcessRuntimeError(ESPServerAPI* server_api)
{
	server_api->SetContentType("text/html");

	const char* type = NULL; bool needFreeType = false;
	const char* description = NULL; bool needFreeDescription = false;
	server_api->GetHttpHeaderErr("esp-runtime-error-type", &type, needFreeType);
	server_api->GetHttpHeaderErr("esp-runtime-error-description", &description, needFreeDescription);

	if(type == NULL) type = "Unkown ESP Runtime Error"; //todo: config it?
	if(description == NULL) description = "no description";

	server_api->WriteResponeData("<html><body><h1>", -1);
	server_api->WriteResponeData(type, -1);
	server_api->WriteResponeData("</h1><p>", -1);
	server_api->WriteResponeData(description, -1);
	server_api->WriteResponeData("</p></body></html>", -1);

	if(type && needFreeType)
		server_api->FreeData((void*)type);
	if(description && needFreeDescription)
		server_api->FreeData((void*)description);

	return true;
}
