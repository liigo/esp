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
	bool LoadFile(const char* szFile); //加载模板文件
	bool LoadText(const char* szText); //加载模板文本
	bool LoadByObject(ESPObject* pObject); //加载ESP对象的模板
	void Reload();
	void CheckForReload(); //检查是否需要重新加载(对比文件最后修改时间)，如果必要将自动重新加载模板文件
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
