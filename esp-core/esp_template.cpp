#include "esp_template.h"
#include <string>
#include <stack>
#include <assert.h>
#include <apr_pools.h>
#include <apr_strings.h>
#include "esp_objects.h"
#include "esp_dollarexpr.h"
#include "esp_globals.h"
#include "esp_serverapi.h"
#include "esp_internal.h"
#include "string_util.h"

// ESPģ�����桢��Ⱦ����
// by Liigo, 2012-5 (��д)

using namespace liigo;

//virtual
void ESPTemplateParser::onParseAttributes(HtmlNode* pNode)
{
	if(pNode->text && strstr(pNode->text, "esp"))
	{
		parseAttributes(pNode);

		//֧�������﷨��<div esp="type=for from=1 to=10"> ... </div>
		//�Զ�չ��Ϊ��esp:��ͷ�����ԣ���Ч�ڣ�<div esp:type="for" esp:from="1" esp:to="10"> ... </div>
		const HtmlAttribute* pAttr = getAttribute(pNode, "esp");
		if(pAttr && pAttr->value)
			parseExtraAttributes(pAttr->value, pNode, "esp:");
	}
}

//virtual
HtmlTagType ESPTemplateParser::onIdentifyHtmlTag(const char* szTagName, HtmlNodeType nodeType)
{
	return TAG_UNKNOWN;
}

//-----------------------------------------------------------------------------

ESPTemplate::ESPTemplate()
{
	m_IsLoaded = false;
	m_FileLastModifyTime = 0;
}

ESPTemplate::~ESPTemplate()
{
	CleanNodes();
}

static inline HtmlNode* _AddNewNode(MemBuffer& nodes, int nodeType, const HtmlNode* copyFrom);

bool ESPTemplate::LoadFile(const char* szFile)
{
	CleanNodes();
	liigo::MemBuffer buffer;
	const char* fileData = NULL;
	if(buffer.loadFromFile(szFile))
	{
		m_TemplateFile = szFile;
		m_FileLastModifyTime = GetFileLastModifyTime(szFile);
		buffer.appendChar('\0'); //����ı�������
		fileData = (const char*)buffer.getData();
		if(buffer.getDataSize() >= 3 && fileData[0] == 0xef && fileData[1] == 0xbb && fileData[2] == 0xbf)
			fileData += 3; //����UTF-8 BOM
	} else {
		m_IsLoaded = false;
		_AddNewNode(m_Nodes, NODE_NULL, NULL);
		return false;
	}
	m_Parser.parseHtml(fileData, true);
	RedoNodes();
	m_Parser.cleanHtmlNodes();
	m_IsLoaded = true;
	return true;
}

bool ESPTemplate::LoadText(const char* szText)
{
	CleanNodes();
	m_TemplateFile.empty();
	m_Parser.parseHtml(szText, true);
	RedoNodes();
	m_Parser.cleanHtmlNodes();
	m_IsLoaded = true;
	return true;
}

// ESP_LIB_PATH: ESP���ļ�����Ŀ¼
// TODO (liigo): ���Զ���
#ifdef WIN32
	const char* ESP_LIB_PATH = "C:\\esplib\\";
	const char  _OS_PATH_SLASH_ = '\\';
#else
	const char* ESP_LIB_PATH = "/usr/local/esplib/";
	const char  _OS_PATH_SLASH_ = '/';
#endif

bool ESPTemplate::LoadByObject(ESPObject* pObject)
{
	assert(pObject != NULL);
	const char* szLibName  = ESPObject_GetLibraryName(pObject);
	const char* szTypeName = ESPObject_GetTypeName(pObject);
	
	std::string file = ESP_LIB_PATH;
	file += szLibName;
	file += _OS_PATH_SLASH_;
	file += szTypeName;
	file += ".esp";

	if(LoadFile(file.c_str()))
		return true;

	//todo: invoke type_template() or type_template_gb18030(), type_template_utf16le() etc.

	return false;
}

void ESPTemplate::Reload()
{
	assert(m_IsLoaded == false);
	if(m_TemplateFile.empty())
		return;
	CleanNodes();
	LoadFile(m_TemplateFile.c_str());
}

void ESPTemplate::CheckForReload()
{
	if(!m_TemplateFile.empty())
	{
		time_t t = GetFileLastModifyTime(m_TemplateFile.c_str());
		if(t > m_FileLastModifyTime)
			Reload();
	}
}

bool ESPTemplate::IsLoaded()
{
	return m_IsLoaded;
}

const int NODE_ESP_COMPONENT_START = _NODE_USER_ + 1;
const int NODE_ESP_COMPONENT_END   = _NODE_USER_ + 2;
const int NODE_ESP_DOLLAR_EXPR     = _NODE_USER_ + 3;

static inline HtmlNode* _AddNewNode(MemBuffer& nodes, int nodeType, const HtmlNode* copyFrom = NULL)
{
	size_t offset = nodes.appendZeroBytes(sizeof(HtmlNode));
	HtmlNode* pNewNode = (HtmlNode*) nodes.getOffsetData(offset);
	if(copyFrom)
		HtmlParser::cloneHtmlNode(copyFrom, pNewNode);
	pNewNode->type = (HtmlNodeType) nodeType;
	return pNewNode;
}

static void _AddMergedContentNode(MemBuffer& txtBuffer, MemBuffer& nodes)
{
	if(txtBuffer.getDataSize() > 0)
	{
		txtBuffer.appendChar('\0'); //end the text
		HtmlNode* pNewNode = _AddNewNode(nodes, NODE_CONTENT);
		pNewNode->text = (char*) txtBuffer.detach();
		pNewNode->flags = FLAG_NEED_FREE_TEXT;
		txtBuffer.empty();
	}
}

static bool _MatchHtmlTag(const HtmlNode* pNode1, const HtmlNode* pNode2)
{
	assert(pNode1 && pNode2 && pNode2->type == NODE_END_TAG);
	if(pNode1->tagType != TAG_UNKNOWN || pNode2->tagType != TAG_UNKNOWN)
		return (pNode1->tagType == pNode2->tagType);
	else
		return (stricmp(pNode1->tagName, pNode2->tagName) == 0);
}

class HtmlNodeWrapper
{
public:
	HtmlNodeWrapper(HtmlNode* node) { m_context = node; m_index = -1; m_type = 0; }
	HtmlNodeWrapper(MemBuffer* buffer, int index) { m_context = buffer; m_index = index; m_type = 1; }

	HtmlNode* GetHtmlNode() const
	{
		assert(m_context);
		if(m_type == 0) {
			return (HtmlNode*) m_context;
		} else {
			return (HtmlNode*) ((MemBuffer*)m_context)->getOffsetData(m_index * sizeof(HtmlNode));
		}
	}
	int GetIndex() const { assert(m_type == 1); return m_index; }

private:
	void* m_context; //maybe MemBuffer* or HtmlNode*
	int m_index;
	int m_type;
};

static void _BindComponentStartEndNode(HtmlNode* pFirstNode, int startNodeIndex, int endNodeIndex)
{
	assert((pFirstNode + startNodeIndex)->type == NODE_ESP_COMPONENT_START);
	assert((pFirstNode + endNodeIndex)->type == NODE_ESP_COMPONENT_END);
	(pFirstNode + startNodeIndex)->pUser = (void*) endNodeIndex;
	(pFirstNode + endNodeIndex)->pUser = (void*) startNodeIndex;
}

bool _IsComponentNode(HtmlNode* pNode)
{
	assert(pNode->type == NODE_START_TAG);
	return (HtmlParser::getAttribute(pNode, "esp:type") != NULL);

	/*
	for(int i = 0; i < pNode->attributeCount; ++i)
	{
		const HtmlAttribute* pAttr = HtmlParser::getAttribute(pNode, i);
		if(strstr(pAttr->name, "esp:") == pAttr->name)
			return true;
	}
	*/
	return false;
}

//������Ŀ�ʼ�ڵ�ͽ����ڵ�����������������öԷ����������������Ľڵ�����Ϊһ��
void ESPTemplate::RedoNodes()
{
	MemBuffer txtBuffer;
	std::stack<HtmlNodeWrapper> nodeStack; //����ƥ�俪ʼ�ڵ����֮��Ӧ�Ľ����ڵ�

	m_Nodes.resetDataSize(sizeof(HtmlNode) * 100);
	m_Nodes.empty();

	for(int i = 0, n = m_Parser.getHtmlNodeCount(); i < n; ++i)
	{
		HtmlNode* pNode = m_Parser.getHtmlNode(i);

		switch(pNode->type)
		{
		case NODE_CONTENT:
			{
				//��ֳ���Ԫ���ʽ$x{y}�ڵ�
				const char* szText = pNode->text;
				ESPDollarExpr expr;
				int leftRemoveLen = 0;
				if(ESP_DollarExpr_Search(szText, expr, leftRemoveLen) == false)
				{
					txtBuffer.appendText(pNode->text);
				} else {
					do {
						txtBuffer.appendText(szText, expr.pDollar - szText - leftRemoveLen);
						if(expr.NotEval)
						{
							txtBuffer.appendText(expr.pDollar, expr.pClosingBrace - expr.pDollar + 1);
						} else {
							//��ǰ����۵��ı�����һ���ڵ����m_Nodes
							_AddMergedContentNode(txtBuffer, m_Nodes);
							//������Ԫ���ʽ�ڵ����m_Nodes
							HtmlNode* pDollarExprNode = _AddNewNode(m_Nodes, NODE_ESP_DOLLAR_EXPR);
							pDollarExprNode->text = mallocstr(expr.pDollar, expr.pClosingBrace - expr.pDollar + 1);
							pDollarExprNode->flags |= FLAG_NEED_FREE_TEXT;
							pDollarExprNode->pUser = malloc(sizeof(ESPDollarExpr)); //free it in CleanNodes()
							ESPDollarExpr* pNewExpr = (ESPDollarExpr*) pDollarExprNode->pUser;
							pNewExpr->pDollar = pDollarExprNode->text;
							pNewExpr->pOpeningBrace  = pDollarExprNode->text + (expr.pOpeningBrace - expr.pDollar);
							pNewExpr->pClosingBrace = pDollarExprNode->text + (expr.pClosingBrace - expr.pDollar);
							pNewExpr->NotEval = false;
						}
						szText = expr.pClosingBrace + 1;
					} while (ESP_DollarExpr_Search(szText, expr, leftRemoveLen));
					txtBuffer.appendText(szText);
				}
			}
			break;
		case NODE_REMARKS:
			{
				const char* s = pNode->text;
				bool isEspRemarks = (s[0] == '/' && s[1] == '/') || (s[0] == '*' && s[1] == '*');
				if(!isEspRemarks)
					txtBuffer.appendText(pNode->text);
			}
			break;
		case NODE_START_TAG:
			{
				bool isEspComponent = _IsComponentNode(pNode);
				bool isSelfClosing = (pNode->flags & FLAG_SELF_CLOSING_TAG) ? true : false;
				if(isEspComponent)
				{
					//��ǰ����۵��ı�����һ���ڵ����m_Nodes
					_AddMergedContentNode(txtBuffer, m_Nodes);
					//��ESP�����ʼ�ڵ㸴�Ƶ�m_Nodes
					HtmlNode* pStartCompNode = _AddNewNode(m_Nodes, NODE_ESP_COMPONENT_START, pNode);
					if(isSelfClosing)
					{	//������Է������ڵ㣬ƾ������һ�������ڵ㣬�Է���������Ⱦ����
						int startNodeIndex = pStartCompNode - (HtmlNode*) m_Nodes.getData();
						HtmlNode* pEndCompNode = _AddNewNode(m_Nodes, NODE_ESP_COMPONENT_END);
						_BindComponentStartEndNode((HtmlNode*) m_Nodes.getData(), startNodeIndex, pEndCompNode - (HtmlNode*) m_Nodes.getData());
					} else {
						nodeStack.push( HtmlNodeWrapper(&m_Nodes, pStartCompNode - (HtmlNode*)m_Nodes.getData()) );
					}
				} else {
					HtmlParser::outputHtmlNode(txtBuffer, pNode);
					if(!isSelfClosing)
						nodeStack.push(HtmlNodeWrapper(pNode));
				}
			}
			break;
		case NODE_END_TAG:
			{
				//�ڽڵ�ջ��Ѱ�Ҷ�Ӧ�Ŀ�ʼ�ڵ�
				while(!nodeStack.empty())
				{
					if((nodeStack.top().GetHtmlNode()->type != NODE_ESP_COMPONENT_START)
							&& !_MatchHtmlTag(nodeStack.top().GetHtmlNode(), pNode))
						nodeStack.pop();
					else
						break;
				}
				assert(!nodeStack.empty() && "��ʼ��ǩ�������ǩ���ز�ƥ��");
				if(!nodeStack.empty())
				{
					HtmlNode* pTop = nodeStack.top().GetHtmlNode();
					bool matched = _MatchHtmlTag(pTop, pNode);
					if(matched && pTop->type == NODE_ESP_COMPONENT_START)
					{
						//��ǰ����۵��ı�����һ���ڵ����m_Nodes
						_AddMergedContentNode(txtBuffer, m_Nodes);
						//��ESP��������ڵ㸴�Ƶ�m_Nodes
						HtmlNode* pEndCompNode = _AddNewNode(m_Nodes, NODE_ESP_COMPONENT_END, pNode);
						//��ʼ�ڵ�ͽ����ڵ㻥���¼�Է���������ʱ����ֱ�Ӽ�¼ָ�룬��Ϊm_Nodes���������У�ָ�������ʱʧЧ��
						_BindComponentStartEndNode((HtmlNode*) m_Nodes.getData(), nodeStack.top().GetIndex(), pEndCompNode - (HtmlNode*)m_Nodes.getData());
					} else {
						HtmlParser::outputHtmlNode(txtBuffer, pNode);
					}
					if(matched)
						nodeStack.pop(); //��ջ
				}
			}
			break;
		default:
			assert(false && "unknown node");
			break;
		} // end switch
	}
	
	//��ǰ����۵��ı�����һ���ڵ����m_Nodes
	_AddMergedContentNode(txtBuffer, m_Nodes);
	//�����������һ��NODE_NULL�ڵ�
	_AddNewNode(m_Nodes, NODE_NULL);
	m_Nodes.shrink();

#ifdef _DEBUG
	//dumpNodes(stdout); //only for test
#endif
}

void ESPTemplate::CleanNodes()
{
	int n = m_Nodes.getDataSize() / sizeof(HtmlNode);
	HtmlNode* pNodes = (HtmlNode*) m_Nodes.getData();
	for(int i = 0; i < n; ++i)
	{
		HtmlNode* pNode = pNodes + i;
		HtmlParser::cleanHtmlNode(pNode);
		if(pNode->type == NODE_ESP_DOLLAR_EXPR)
		{
			assert(pNode->pUser);
			free(pNode->pUser); //free ESPDollarExpr*, see RedoNodes (case NODE_CONTENT)
		}
	}
	m_Nodes.clean();
}

void ESPTemplate::dumpNodes(FILE* f)
{
	HtmlNode* pNodes = (HtmlNode*) m_Nodes.getData();
	for(int i = 0, n = m_Nodes.getDataSize() / sizeof(HtmlNode) - 1; i < n; i++)
	{
		HtmlNode* pNode = pNodes + i;

		switch(pNode->type)
		{
		case NODE_CONTENT:
			fprintf(f, "#%d) NODE_CONTENT: %s\r\n", i, pNode->text);
			break;
		case NODE_ESP_DOLLAR_EXPR:
			fprintf(f, "#%d) NODE_ESP_DOLLAR_EXPR: %s\r\n", i, pNode->text);
			break;
		case NODE_ESP_COMPONENT_START:
			{
				fprintf(f, "#%d) NODE_ESP_COMPONENT_START (#%d - #%d): <%s\r\n", i, pNode - pNodes, pNode->pUser, pNode->tagName);
				HtmlParser::dumpHtmlNode(pNode, -1, f);
			}
			break;
		case NODE_ESP_COMPONENT_END:
			fprintf(f, "#%d) NODE_ESP_COMPONENT_END (#%d - #%d): </%s>\r\n", i, pNode->pUser, pNode - pNodes, pNode->tagName);
			break;
		default:
			fprintf(f, "!!UNEXPECTED.NODE!!\r\n: ");
			HtmlParser::dumpHtmlNode(pNode, -1, f);
		}
	}
}

//���������д�����ͬ�������У��ѽڵ����ƺ��������Էֱ�д���������$tag_name��$tag_attributes
static void _SetComponentParametersAndTagAttributes(ESPComponent* component, const HtmlNode* pNode)
{
	std::string tag_attributes;
	for(int i = 0, n = pNode->attributeCount; i < n; ++i)
	{
		const HtmlAttribute* pAttr = HtmlParser::getAttribute(pNode, i);
		assert(pAttr);
		if(pAttr->name == NULL) continue;

		if((pAttr->name[0] == 'e') && (pAttr->name[1] == 's') && (pAttr->name[2] == 'p'))
		{
			if(pAttr->name[3] == '\0')
				continue; //���Ե�����Ϊesp�����ԣ��μ�ESPTemplateParser::onParseAttributes()

			//���������� esp: ��ͷ�ģ���Ϊ�������д�����ͬ��������
			if(pAttr->name[3] == ':')
			{
				const char* szAttrName  = pAttr->name + 4;
				bool ispublic = false; //���������Ƿ񱻶���Ϊpublic����ֹд���public����
				if(ESPObject_GetPropertyInfos(component, szAttrName, NULL, NULL, NULL, &ispublic, NULL) && ispublic)
				{
					std::string attrValue = ESP_DollarExpr_Eval(pAttr->value, component);
					ESPObject_SetProperty(component, szAttrName, attrValue.c_str());
				}
				continue;
			}
		}

		//����HTML�������Ϻ�д��������� $tag_attributes �У�������Ⱦ����ȡ�ã�
		if(tag_attributes.length() > 0)
			tag_attributes.push_back(' ');
		tag_attributes.append(pAttr->name);
		if(pAttr->value)
		{
			tag_attributes.push_back('=');
			tag_attributes.push_back('"');
			tag_attributes.append(ESP_DollarExpr_Eval(pAttr->value, component));
			tag_attributes.push_back('"');
		}
	}

	ESPObject_SetTextProperty(component, "$tag_name", pNode->tagName);
	ESPObject_SetTextProperty(component, "$tag_attributes", tag_attributes.c_str());
}

//��ȡ��path_info, �μ�_ParsePageEventInfoFromPathInfo()
struct _ESPPageEventInfo
{
	const char* szComponentName; // �����¼���������ƣ�instance name��
	const char* szEventName;     // �¼�����
	const char* szEventParam;    // �¼�����
};

enum RenderPhase
{
	RENDER_PHASE_UNSTART = 0,
	RENDER_PHASE_SETUP_RENDER,
	RENDER_PHASE_BEFORE_RENDER,
	RENDER_PHASE_BEFORE_RENDER_TEMPLATE,
	RENDER_PHASE_BEFORE_RENDER_BODY,
	RENDER_PHASE_RENDER_BODY,
	RENDER_PHASE_AFTER_RENDER_BODY,
	RENDER_PHASE_AFTER_RENDER_TEMPLATE,
	RENDER_PHASE_AFTER_RENDER,
	RENDER_PHASE_CLEANUP_RENDER,
};

struct RenderState
{
	ESPComponent* component;
	RenderPhase currentRenderPhase;
	int endNodeIndex;
};

static inline RenderState* _GetRenderState_OnStartNode(HtmlNode* pStartNode, HtmlNode* pFirstNode, RenderState* pRenderStates)
{
	assert(pStartNode->type == NODE_ESP_COMPONENT_START);
	return pRenderStates + (pStartNode - pFirstNode); //see _BindComponentStartEndNode()
}

static inline RenderState* _GetRenderState_OnEndNode(HtmlNode* pEndNode, HtmlNode* pFirstNode, RenderState* pRenderStates)
{
	assert(pEndNode->type == NODE_ESP_COMPONENT_END);
	assert((pFirstNode + (int)pEndNode->pUser)->type == NODE_ESP_COMPONENT_START); 
	return pRenderStates + (int) pEndNode->pUser; //see _BindComponentStartEndNode()
}

struct RenderNodeArgs
{
	HtmlNode* pFirstNode;
	MemBuffer* pRenderBuffer;
	RenderState* pRenderStates;
	std::stack<ESPObject*>* pParentStack;
	_ESPPageEventInfo* pPageEvent;
};

//�˺���������֮�󷵻���һ��Ҫ����Ľڵ�
static HtmlNode* _OnRenderNode(HtmlNode* pNode, RenderNodeArgs& args)
{
	ESPRenderContext* pRenderContext = (ESPRenderContext*) args.pRenderBuffer;
	switch(pNode->type)
	{
	case NODE_CONTENT:
		args.pRenderBuffer->appendText(pNode->text);
		return (pNode + 1);
	case NODE_ESP_DOLLAR_EXPR:
		{
			//see ReNodes() case NODE_CONTENT
			const ESPDollarExpr* pDollarExpr = (const ESPDollarExpr*) pNode->pUser;
			assert(pDollarExpr);
			std::string strValue = ESP_DollarExpr_Eval(*pDollarExpr, args.pParentStack->top());
			args.pRenderBuffer->appendText(strValue.c_str(), strValue.length());
			return (pNode + 1);
		}
	case NODE_ESP_COMPONENT_START:
		{
			RenderState* pRS = _GetRenderState_OnStartNode(pNode, args.pFirstNode, args.pRenderStates);
			HtmlNode* pEndNode = args.pFirstNode + (int) pNode->pUser;

			switch(pRS->currentRenderPhase)
			{
			case RENDER_PHASE_UNSTART:
				{
					const HtmlAttribute* pAttribute = HtmlParser::getAttribute(pNode, "esp:type");
					assert(pAttribute && pAttribute->value);
					const char* typeName = pAttribute->value;
					const char* instanceName = HtmlParser::getAttributeStringValue(pNode, "esp:name", NULL);
					ESPObject* parent = args.pParentStack->top();
					ESPComponent* pComponent = 
						ESPGlobals::GetInstance()->GetObjectManager().AcquireComponent(typeName, instanceName, parent);
					assert(pComponent);
					if(pComponent == NULL)
					{
						return (pEndNode + 1); //������Ⱦ���������ģ���BODY
					}
					_SetComponentParametersAndTagAttributes(pComponent, pNode); //д����������ͽڵ�����
					args.pParentStack->push(pComponent);
					pRS->component = pComponent;
					pRS->currentRenderPhase = RENDER_PHASE_SETUP_RENDER;
					//fall through to case RENDER_PHASE_SETUP_RENDER
				}
			case RENDER_PHASE_SETUP_RENDER:
				if(ESPRenderable_SetupRender(pRS->component, pRenderContext))
				{
					pRS->currentRenderPhase = RENDER_PHASE_BEFORE_RENDER;
					//fall through to case RENDER_PHASE_BEFORE_RENDER
				} else {
					pRS->currentRenderPhase = RENDER_PHASE_CLEANUP_RENDER;
					return pEndNode; //���������ڵ�
				}
			case RENDER_PHASE_BEFORE_RENDER:
				if(ESPRenderable_BeforeRender(pRS->component, pRenderContext))
				{
					//TODO: �����Ƿ���ģ���BODYȷ���Ƿ�ִ����Ӧ����Ⱦ�׶�
					pRS->currentRenderPhase = RENDER_PHASE_BEFORE_RENDER_TEMPLATE;
					//fall through to case RENDER_PHASE_BEFORE_RENDER_TEMPLATE
				} else {
					pRS->currentRenderPhase = RENDER_PHASE_AFTER_RENDER;
					return pEndNode; //���������ڵ�
				}
			case RENDER_PHASE_BEFORE_RENDER_TEMPLATE:
				if(ESPRenderable_BeforeRenderTemplate(pRS->component, pRenderContext))
				{
					ESPTemplate::RenderComponentTemplate(pRS->component, args.pRenderBuffer, args.pPageEvent);
					if(pEndNode - pNode > 1) //has body?
					{
						pRS->currentRenderPhase = RENDER_PHASE_BEFORE_RENDER_BODY;
						//fall through to case RENDER_PHASE_BEFORE_RENDER_BODY
					} else {
						pRS->currentRenderPhase = RENDER_PHASE_AFTER_RENDER_TEMPLATE;
						return pEndNode;
					}
				} else {
					pRS->currentRenderPhase = RENDER_PHASE_AFTER_RENDER_TEMPLATE;
					return pEndNode; //���������ڵ�
				}
			case RENDER_PHASE_BEFORE_RENDER_BODY:
				if(ESPRenderable_BeforeRenderBody(pRS->component, pRenderContext))
				{
					pRS->currentRenderPhase = RENDER_PHASE_RENDER_BODY;
					assert((pNode+1)->type != NODE_ESP_COMPONENT_END);
					return (pNode + 1); //render body
				} else {
					pRS->currentRenderPhase = RENDER_PHASE_AFTER_RENDER_BODY;
					return pEndNode; //���������ڵ�
				}
			default:
				assert(false && "unexpected render phase on component start node");
				return (pNode + 1);
			}
			//end switch(pRS->currentRenderPhase)
		}
		break;
	case NODE_ESP_COMPONENT_END:
		{
			RenderState* pRS = _GetRenderState_OnEndNode(pNode, args.pFirstNode, args.pRenderStates);
			HtmlNode* pStartNode = args.pFirstNode + (int) pNode->pUser;

			switch(pRS->currentRenderPhase)
			{
			case RENDER_PHASE_RENDER_BODY:
			case RENDER_PHASE_AFTER_RENDER_BODY:
				if(ESPRenderable_AfterRenderBody(pRS->component, pRenderContext))
				{
					pRS->currentRenderPhase = RENDER_PHASE_AFTER_RENDER_TEMPLATE;
					//fall through to case RENDER_PHASE_AFTER_RENDER_TEMPLATE
				} else {
					pRS->currentRenderPhase = RENDER_PHASE_BEFORE_RENDER_BODY;
					return pStartNode; //������ʼ�ڵ�
				}
			case RENDER_PHASE_AFTER_RENDER_TEMPLATE:
				if(ESPRenderable_AfterRenderTemplate(pRS->component, pRenderContext))
				{
					pRS->currentRenderPhase = RENDER_PHASE_AFTER_RENDER;
					//fall through to case RENDER_PHASE_AFTER_RENDER
				} else {
					pRS->currentRenderPhase = RENDER_PHASE_BEFORE_RENDER_TEMPLATE;
					return pStartNode; //������ʼ�ڵ�
				}
			case RENDER_PHASE_AFTER_RENDER:
				if(ESPRenderable_AfterRender(pRS->component, pRenderContext))
				{
					pRS->currentRenderPhase = RENDER_PHASE_CLEANUP_RENDER;
					//fall through to case RENDER_PHASE_CLEANUP_RENDER
				} else {
					pRS->currentRenderPhase = RENDER_PHASE_BEFORE_RENDER;
					return pStartNode; //������ʼ�ڵ�
				}
			case RENDER_PHASE_CLEANUP_RENDER:
				ESPRenderable_CleanupRender(pRS->component, pRenderContext);
				//����ҳ���¼����μ�_ParsePageEventInfoFromPathInfo()��
				{
					_ESPPageEventInfo* pPageEvent = args.pPageEvent;
					if(pPageEvent && pPageEvent->szComponentName && pRS->component->instance_name)
					{
						if(strcmp(pRS->component->instance_name, pPageEvent->szComponentName) == 0)
						{
							ESPObject_FireEvent(pRS->component, pPageEvent->szEventName, pPageEvent->szEventParam);
							pPageEvent->szComponentName = NULL; //��־�¼��Ѿ�����
						}
					}
				}
				//����
				args.pParentStack->pop();
				ESPGlobals::GetInstance()->GetObjectManager().ReleaseComponent(pRS->component, false);
				pRS->component = NULL;
				pRS->currentRenderPhase = RENDER_PHASE_UNSTART;
				return (pNode + 1); //�������Ⱦ������������Ⱦ�����NODE
			default:
				assert(false && "unexpected render phase on component end node");
				return (pNode + 1);
			}
		}
		break;
	default:
		assert(false && "!!UNEXPECTED NODE!!");
		return (pNode + 1);
	}
	//end switch(pNode->type)
}

//��path_info����ȡ �������,�¼�����,�¼���������ȡ�ɹ�����true����������¼����ƾ���ΪNULL��
//_ESPPageEventInfo�е�ָ���ָ��strContainer�ڲ�, strContainer�����洢�ı�����
static bool _ParsePageEventInfoFromPathInfo(ESPPage* page, _ESPPageEventInfo& eventInfo, std::string& strContainer)
{
	memset(&eventInfo, 0, sizeof(_ESPPageEventInfo));

	const char* path_info = NULL; bool needfreePathInfo = false;
	page->server_api->GetPathInfo(&path_info, needfreePathInfo);

	if(path_info == NULL)
		return false;

	strContainer = path_info;

	if(needfreePathInfo)
		page->server_api->FreeData(path_info);

	char* szComponentName = (char*) strContainer.c_str();
	if(*szComponentName == '/')
		szComponentName++;
	if(*szComponentName != '\0')
		eventInfo.szComponentName = szComponentName;
	else
		return false;

	char* pSlash = strchr(szComponentName, '/');
	if(pSlash)
	{
		*pSlash = '\0';
		eventInfo.szEventName = pSlash + 1;

		pSlash = strchr(eventInfo.szEventName, '/');
		if(pSlash)
		{
			*pSlash = '\0';
			eventInfo.szEventParam = pSlash + 1;
		}
		return true;
	} else {
		eventInfo.szComponentName = NULL;
		return false;
	}
}

enum ESPRenderResult ESPTemplate::RenderPageTemplate(ESPPage* page, liigo::MemBuffer* pRenderBuffer)
{
	HtmlNode* pNode = (HtmlNode*) m_Nodes.getData();
	ESPRenderContext* pRenderContext = (ESPRenderContext*) pRenderBuffer;

	_ESPPageEventInfo  pageEvent;
	_ESPPageEventInfo* pPageEvent = NULL;
	std::string strDummy;
	if(_ParsePageEventInfoFromPathInfo(page, pageEvent, strDummy))
		pPageEvent = &pageEvent;

	if(ESPRenderable_SetupRender(page, pRenderContext))
	{
		if(ESPRenderable_BeforeRender(page, pRenderContext))
		{
			if(ESPRenderable_BeforeRenderTemplate(page, pRenderContext))
			{
				if(pNode->type != NODE_NULL)
				{
					if(ESPRenderable_BeforeRenderBody(page, pRenderContext))
					{
						int bytes = m_Nodes.getDataSize() / sizeof(HtmlNode) * sizeof(RenderState);
						RenderState* pRenderStates = (RenderState*) malloc(bytes);
						memset(pRenderStates, 0, bytes);

						std::stack<ESPObject*> parentStack;
						parentStack.push(page);

						RenderNodeArgs args;
						args.pFirstNode = (HtmlNode*) m_Nodes.getData();
						args.pRenderBuffer = pRenderBuffer;
						args.pRenderStates = pRenderStates;
						args.pParentStack = &parentStack;
						args.pPageEvent = pPageEvent;

						while(pNode->type != NODE_NULL)
							pNode = _OnRenderNode(pNode, args);

						free(pRenderStates);
					} else {
						ESPRenderable_AfterRenderBody(page, pRenderContext);
					}
				}
			} else {
				ESPRenderable_AfterRenderTemplate(page, pRenderContext);
			}
		} else {
			ESPRenderable_AfterRender(page, pRenderContext);
		}
	} else {
		ESPRenderable_CleanupRender(page, pRenderContext);
	}

	if(pPageEvent)
	{
		//�ض���, ȥ��path_info, ����query_string

		const char* szURI = NULL; bool needfreeURI = false;
		page->server_api->GetRequestURI(&szURI, needfreeURI);

		std::string uri = szURI;

		if(szURI && needfreeURI)
			page->server_api->FreeData(szURI);

		const char* path_info = NULL; bool needfreePathInfo = false;
		page->server_api->GetPathInfo(&path_info, needfreePathInfo);
		assert(path_info);

		std::string new_uri = uri;
		int pathinfoIndex = uri.rfind(path_info);
		if(pathinfoIndex > 0)
			new_uri = uri.substr(0, pathinfoIndex); //��URI��ȥ��path_info������еĻ���

		if(path_info && needfreePathInfo)
			page->server_api->FreeData(path_info);

		const char* args = NULL; bool needfreeArgs = false;
		page->server_api->GetQueryString(&args, needfreeArgs);
		if(args && *args)
		{
			new_uri.push_back('?');
			new_uri += args; //����query-string
			if(needfreeArgs)
				page->server_api->FreeData(args);
		}

		//???�����ض���(301)����PathInfo��ҳ�棬������ֹ��������������PathInfo�����ӣ��������ⴥ��ESP�¼�.
		//!!!ò�������ض���ᵼ����ESP�¼�������Cookie��Ч! ֻ�ø�����ʱ�ض���(302).
		page->server_api->Redirect(new_uri.c_str(), 302);

		return ESPRenderResult_REDIRECTED;
	}

	return ESPRenderResult_OK;
}

void ESPTemplate::RenderComponentTemplate(ESPComponent* component, MemBuffer* pRenderBuffer, _ESPPageEventInfo* pPageEvent)
{
	ESPTemplate* pTemplate = component->type_info->esp_template;
	assert(pTemplate != NULL);
	if(!pTemplate->IsLoaded())
	{
		pTemplate->LoadByObject(component);
	} else {
		pTemplate->CheckForReload();
	}

	if(pTemplate->m_Nodes.getDataSize() <= sizeof(HtmlNode))
		return;

	HtmlNode* pNode = (HtmlNode*) pTemplate->m_Nodes.getData();

	int rsBytes = pTemplate->m_Nodes.getDataSize() / sizeof(HtmlNode) * sizeof(RenderState);
	RenderState* pRenderStates = (RenderState*) malloc(rsBytes);
	memset(pRenderStates, 0, rsBytes);

	std::stack<ESPObject*> parentStack;
	parentStack.push(component);

	RenderNodeArgs args;
	args.pFirstNode = (HtmlNode*) pTemplate->m_Nodes.getData();
	args.pRenderBuffer = pRenderBuffer;
	args.pRenderStates = pRenderStates;
	args.pParentStack = &parentStack;
	args.pPageEvent = pPageEvent;

	while(pNode->type != NODE_NULL)
		pNode = _OnRenderNode(pNode, args);

	free(pRenderStates);
}
