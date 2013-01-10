#ifndef __ESP_TEMPLATE_H__
#define __ESP_TEMPLATE_H__

#include <string>
#include <time.h>
#include "stl_hash_map.h"
#include "../other/html-parser/HtmlParser.h"

struct ESPObject;
typedef ESPObject  ESPComponent, ESPPage;

class ESPTemplateParser : public liigo::HtmlParser
{
public:
	virtual liigo::HtmlTagType onIdentifyHtmlTag(const char* szTagName, liigo::HtmlNodeType nodeType);
	virtual void onParseAttributes(liigo::HtmlNode* pNode);
};

enum ESPRenderResult
{
	ESPRenderResult_OK = 0,
	ESPRenderResult_REDIRECTED,
};

struct _ESPPageEventInfo;

class ESPTemplate
{
public:
	ESPTemplate();
	~ESPTemplate();

public:
	bool LoadFile(const char* szFile); //����ģ���ļ�
	bool LoadText(const char* szText); //����ģ���ı�
	bool LoadByObject(ESPObject* pObject); //����ESP�����ģ��
	void Reload();
	void CheckForReload(); //����Ƿ���Ҫ���¼���(�Ա��ļ�����޸�ʱ��)�������Ҫ���Զ����¼���ģ���ļ�
	bool IsLoaded();
	void dumpNodes(FILE* f);

	enum ESPRenderResult RenderPageTemplate(ESPPage* page, liigo::MemBuffer* pRenderBuffer);
	static void RenderComponentTemplate(ESPComponent* component, liigo::MemBuffer* pRenderBuffer, _ESPPageEventInfo* pPageEvent);

private:
	void RedoNodes();
	void CleanNodes();

private:
	bool m_IsLoaded;
	std::string m_TemplateFile;
	ESPTemplateParser m_Parser;
	liigo::MemBuffer m_Nodes;
	time_t m_FileLastModifyTime;
};


#endif //__ESP_TEMPLATE_H__
