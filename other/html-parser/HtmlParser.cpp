#include "HtmlParser.h"
#include <memory.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

//HtmlParser�࣬���ڽ���HTML�ı�
//by liigo, @2010-2012

#ifndef WIN32
	#include <strings.h>
	#define stricmp strcasecmp
#endif

using namespace liigo;

const char* strnchr(const char* pStr, int len, char c)
{
	if(pStr == NULL || len <= 0)
		return NULL;
	const char *p = pStr;
	while(1)
	{
		if(*p == c) return p;
		p++;
		if((p - pStr) == len) break;
	}
	return NULL;
}

inline bool matchchar(char c1, char c2, bool bCaseSensitive)
{
	return bCaseSensitive ? (c1 == c2) : (tolower(c1) == tolower(c2));
}

const char* findFirstUnquotedChar(const char* pStr, char endchar)
{
	char c;
	const char* p = pStr;
	bool inQuote1 = false, inQuote2 = false; //'inQuote1', "inQuote2"
	while(c = *p)
	{
		if(c == '\'')
		{
			inQuote1 = !inQuote1;
		}
		else if(c == '\"')
		{
			inQuote2 = !inQuote2;
		}

		if(!inQuote1 && !inQuote2)
		{
			if(c == endchar) return p;
		}
		p++;
	}
	return NULL;
}

const char* findFirstUnquotedChars(const char* pStr, char* endchars, int nchars, bool bCaseSensitive)
{
	char c;
	const char* p = pStr;
	bool inQuote1 = false, inQuote2 = false; //'inQuote1', "inQuote2"
	while(c = *p)
	{
		if(c == '\'')
		{
			inQuote1 = !inQuote1;
		}
		else if(c == '\"')
		{
			inQuote2 = !inQuote2;
		}

		if(!inQuote1 && !inQuote2)
		{
			for(int i = 0; i < nchars; i++)
			{
				if(matchchar(c, endchars[i], bCaseSensitive))
					return p;
			}
		}
		p++;
	}
	return NULL;
}

// return true if pStr1 starts with pStr2. pStr1 not NULL, pStr2 not NULL, lenStr2 > 0.
static bool strStartWith(const char* pStr1, const char* pStr2, int lenStr2, bool bCaseSensitive)
{
	for(int i = 0; i < lenStr2; i++)
	{
		if(pStr1[i] == '\0') return false;
		if(!matchchar(pStr1[i], pStr2[i], bCaseSensitive))
			return false;
	}
	return true;
}

const char* findFirstUnquotedStr(const char* pSourceStr, const char* pDestStr, bool bCaseSensitive)
{
	if(pDestStr == NULL || *pDestStr == '\0') return NULL;

	char c;
	const char* p = pSourceStr;
	bool inQuote1 = false, inQuote2 = false; //'inQuote1', "inQuote2"
	int lenDestStr = strlen(pDestStr);
	while(c = *p)
	{
		if(c == '\'')
		{
			inQuote1 = !inQuote1;
		}
		else if(c == '\"')
		{
			inQuote2 = !inQuote2;
		}

		if(!inQuote1 && !inQuote2)
		{
			if(strStartWith(p, pDestStr, lenDestStr, bCaseSensitive))
				return p;
		}
		p++;
	}
	return NULL;
}

const char* findFirstStr(const char* pSourceStr, const char* pDestStr, bool bCaseSensitive)
{
	if(pDestStr == NULL || *pDestStr == '\0') return NULL;

	char c;
	const char* p = pSourceStr;
	int lenDestStr = strlen(pDestStr);
	while(c = *p)
	{
		if(strStartWith(p, pDestStr, lenDestStr, bCaseSensitive))
			return p;
		p++;
	}
	return NULL;
}

//nDest and nChar can by -1
size_t copyStr(char* pDest, size_t nDest, const char* pSrc, size_t nChar)
{
	if(pDest == NULL || nDest == 0)
		return 0;
	if(pSrc == NULL)
	{
		pDest[0] = '\0';
		return 0;
	}
	if(nChar == (size_t)-1)
		nChar = strlen(pSrc);
	if(nChar > nDest)
		nChar = nDest;
	memcpy(pDest, pSrc, nChar * sizeof(char));
	pDest[nChar] = '\0';
	return nChar;
}

int copyStrUtill(char* pDest, size_t nDest, const char* pSrc, char endchar, bool ignoreEndCharInQuoted)
{
	if(nDest == 0) return 0;
	pDest[0] = '\0';
	const char* pSearched = (ignoreEndCharInQuoted ? findFirstUnquotedChar(pSrc,endchar) : strchr(pSrc, endchar));
	if(pSearched <= pSrc) return 0;
	return copyStr(pDest, nDest, pSrc, pSearched - pSrc);
}

//nChar can be -1
char* duplicateStr(const char* pSrc, size_t nChar, const char* pPrefix = NULL)
{
	if(nChar == (size_t)-1)
		nChar = strlen(pSrc);
	int lenPrefix = pPrefix ? strlen(pPrefix) : 0;
	char* pNew = (char*) malloc( (lenPrefix + nChar + 1) * sizeof(char) );
	if(lenPrefix > 0)
	{
		copyStr(pNew, -1, pPrefix, lenPrefix);
		copyStr(pNew + lenPrefix, -1, pSrc, nChar);
	} else {
		copyStr(pNew, -1, pSrc, nChar);
	}
	return pNew;
}

char* duplicateStrUtill(const char* pSrc, char endchar, bool ignoreEndCharInQuoted)
{
	const char* pSearched = (ignoreEndCharInQuoted ? findFirstUnquotedChar(pSrc,endchar) : strchr(pSrc, endchar));;
	if(pSearched <= pSrc) return NULL;
	int n = pSearched - pSrc;
	return duplicateStr(pSrc, n);
}

void freeDuplicatedStr(char* p)
{
	if(p) free(p);
}

void skipSpaceChars(char*& p)
{
	if(p)
	{
		while(isspace(*p)) p++;
	}
}

inline const char* nextUnqotedSpaceChar(const char* p)
{
	return findFirstUnquotedChars(p, " \n\r\t\f", 5, true);
}

char* duplicateStrAndUnquote(const char* str, size_t nChar, const char* prefix = NULL)
{
	if( nChar > 1 && (str[0] == '\"' && str[nChar-1] == '\"') || (str[0] == '\'' && str[nChar-1] == '\'') )
	{
		str++; nChar-=2;
	}
	return duplicateStr(str, nChar, prefix);
}

//-----------------------------------------------------------------------------

// TagName & TagType
struct N2T { const char* name; HtmlTagType type; };

static HtmlTagType identifyHtmlTagInTable(const char* szTagName, N2T* table, int count)
{
	for(int i = 0; i < count; i++)
	{
		N2T* p = table + i;
		if(stricmp(p->name, szTagName) == 0)
			return p->type;
	}
	return TAG_UNKNOWN;
}

//���ڽ�����Ҫ����ʶ���HtmlTagType
static HtmlTagType identifyHtmlTag_Internal(const char* szTagName)
{
	static N2T n2tTable[] = 
	{
		{ "SCRIPT",   TAG_SCRIPT   },
		{ "STYLE",    TAG_STYLE    },
		{ "TEXTAREA", TAG_TEXTAREA },
	};

	return identifyHtmlTagInTable(szTagName, n2tTable, sizeof(n2tTable)/sizeof(n2tTable[0]));
}

//[virtual]
HtmlTagType HtmlParser::onIdentifyHtmlTag(const char* szTagName, HtmlNodeType nodeType)
{
	//Ĭ�Ͻ�ʶ���漰HTML�����ṹ����Ϣ�����޼���TAG
	//�����û�������չ�Ա�ʶ���������

	if(nodeType != NODE_START_TAG)
		return TAG_UNKNOWN;

	static N2T n2tTable[] = 
	{
		{ "A",      TAG_A      },
		{ "IMG",    TAG_IMG    },
		{ "META",   TAG_META   },
		{ "BODY",   TAG_BODY   },
		{ "TITLE",  TAG_TITLE  },
		{ "FRAME",  TAG_FRAME  },
		{ "IFRAME", TAG_IFRAME },
	};

	return identifyHtmlTagInTable(szTagName, n2tTable, sizeof(n2tTable)/sizeof(n2tTable[0]));
}

HtmlNode* HtmlParser::appendHtmlNode()
{
	static char staticHtmlNodeTemplate[sizeof(HtmlNode)] = {0};
	size_t offset = m_HtmlNodes.appendData(staticHtmlNodeTemplate, sizeof(HtmlNode));
	HtmlNode* pNode = (HtmlNode*) m_HtmlNodes.getOffsetData(offset);
	pNode->type = NODE_UNKNOWN;
	return pNode;
}

static void setNodeAttributeText(HtmlNode* pNode, const char* pStart)
{
	while(isspace(*pStart)) pStart++;

	if(pStart[0] == '>') return; //no attribute text
	if(pStart[0] == '/' && pStart[1] == '>')
	{
		pNode->flags |= FLAG_SELF_CLOSING_TAG; //�Է�ձ�ǩ
		return; //no attribute text
	}

	char* attributeText = duplicateStrUtill(pStart, '>', true);
	if(attributeText)
	{
		int len = strlen(attributeText);
		if(attributeText[len-1] == '/') //ȥ�������ܻ��е�'/'�ַ�, ���������: <img src="..." />
		{
			attributeText[len-1] = '\0';
			pNode->flags |= FLAG_SELF_CLOSING_TAG; //�Է�ձ�ǩ
		}
		pNode->text = attributeText;
		pNode->flags |= FLAG_NEED_FREE_TEXT; //������ͷ��ı�
	}
}

static const char* s_LF   = "\n";   //Unix,Linux
static const char* s_CR   = "\r";   //Mac
static const char* s_CRLF = "\r\n"; //Windows

// pNode != NULL, pStart != NULL, len > 0
static void setNodeText(HtmlNode* pNode, const char* pStart, int len)
{
	//���ڿ����ı��Ƚϳ�����ÿ�����ױ�ǩ��ǰ�涼������һ�������ı�
	//�˴��Ż�ֱ�ӷ��س����ı����Լ��ٲ���Ҫ���ڴ����
	//��Ϊû���趨FLAG_NEED_FREE_TEXT��ǣ�freeHtmlNode(pNode)�ﲻ���ͷ����ೣ���ı�
	if(len == 1 && pStart[0] == '\n') { pNode->text = (char*)s_LF; return; }

	if(pStart[0] == '\r')
	{
		if(len == 1) { pNode->text = (char*)s_CR; return; }
		if(len == 2 && pStart[1] == '\n') { pNode->text = (char*)s_CRLF; return; }
	}

	char* text = duplicateStr(pStart, len); //TODO: �����Ż��������ٸ����ı�
	if(text)
	{
		pNode->text = text;
		pNode->flags |= FLAG_NEED_FREE_TEXT; //������ͷ��ı�
	}
}

void HtmlParser::parseHtml(const char* szHtml, bool parseAttributes)
{
	cleanHtmlNodes();
	if(szHtml == NULL || *szHtml == '\0')
	{
		HtmlNode* pNode = appendHtmlNode();
		pNode->type = NODE_NULL;
		return; //�������һ��NODE_NULL�ڵ�
	}

	char* p = (char*) szHtml;
	char* s = (char*) szHtml;
	HtmlNode* pNode = NULL;
	char c;
	bool bInQuote1   = false; //between ' and '
	bool bInQuote2   = false; //between " and "
	bool bInScript   = false; //between <scripte> and </script>
	bool bInStyle    = false; //between <style> and </style>
	bool bInTextArea = false; //between <textarea> and </textarea>
	bool bInsideTag  = false; //between < and >

	while( c = *p )
	{
		if(bInsideTag)
		{
			//�� < �� > ֮�䣬���������Ż�˫�����ڵ��κ��ı�������<��>��
			if(c == '\'')
			{
				bInQuote1 = !bInQuote1;
				p++; continue;
			}
			else if(c == '\"')
			{
				bInQuote2 = !bInQuote2;
				p++; continue;
			}
			if(bInQuote1 || bInQuote2)
			{
				p++; continue;
			}
		}

		if(bInScript)
		{
			//����<script>��</script>֮����κ��ı�
			const char* pEndScript = findFirstStr(p, "</script>", false);
			if(pEndScript)
			{
				bInScript = false;
				p = (char*)pEndScript;
				c = *p;
			}
			else
				goto onerror; //error: no </script>
		}
		else if(bInStyle)
		{
			//����<style>��</style>֮����κ��ı�
			const char* pEndStyle = findFirstStr(p, "</style>", false);
			if(pEndStyle)
			{
				bInStyle = false;
				p = (char*)pEndStyle;
				c = *p;
			}
			else
				goto onerror; //error: no </style>
		}
		else if(bInTextArea)
		{
			//����<textarea>��</textarea>֮����κ��ı�
			const char* pEndTextArea = findFirstStr(p, "</textarea>", false);
			if(pEndTextArea)
			{
				bInTextArea = false;
				p = (char*)pEndTextArea;
				c = *p;
			}
			else
				goto onerror; //error: no </textarea>
		}


		if(c == '<') // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		{
			if(p > s)
			{
				//Add Content Node
				pNode = appendHtmlNode();
				pNode->type = NODE_CONTENT;
				setNodeText(pNode, s, p - s);
				if(onNodeReady(pNode) == false) goto onuserend;
			}

			//����HTMLע�ͻ�CDATA
			if(p[1] == '!')
			{
				if(p[2] == '-' && p[3] == '-')
				{
					//ע��: <!-- ... -->
					const char* pEndRemarks = findFirstStr(p + 4, "-->", true);
					if(pEndRemarks)
					{
						//Add Remarks Node
						pNode = appendHtmlNode();
						pNode->type = NODE_REMARKS;
						setNodeText(pNode, p + 4, pEndRemarks - (p + 4));
						if(onNodeReady(pNode) == false) goto onuserend;
						s = p = (char*)pEndRemarks + 3;
						bInsideTag = bInQuote1 = bInQuote2 = false;
						continue;
					}
					//else: no -->, not very bad, try continue parsing
				}
				else if(p[2] == '[' && strStartWith(p+3, "CDATA[", 5, false))
				{
					//CDATA: <![CDATA[ ... ]]>
					const char* pEndCData = findFirstStr(p + 9, "]]>", true);
					if(pEndCData)
					{
						//Add Content Node with CDATA flag
						pNode = appendHtmlNode();
						pNode->type = NODE_CONTENT;
						setNodeText(pNode, p + 9, pEndCData - (p + 9));
						pNode->flags |= FLAG_CDATA_BLOCK; //���CDATA, used by outputHtml() and dumpHtml()
						if(onNodeReady(pNode) == false) goto onuserend;
						s = p = (char*)pEndCData + 3;
						bInsideTag = bInQuote1 = bInQuote2 = false;
						continue;
					}
					//else: no ]]>, not very bad, try contiune parsing
				}
			}


			s = p + 1;
			bInsideTag = true; bInQuote1 = bInQuote2 = false;
		}
		else if(c == '>') // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		{
			if(p > s)
			{
				//�����½ڵ�(HtmlNode)���õ��ڵ�����(NodeType)������(TagName)
				pNode = appendHtmlNode();
				while(isspace(*s)) s++;
				pNode->type = (*s == '/' ? NODE_END_TAG : NODE_START_TAG);
				if(*s == '/') s++;
				//����õ���tagName���ܰ���һ���������ı���������������
				//tagNameҲ������������� a href="///////////////// ����������������,���һ��/������ֵ�е��ַ���
				copyStrUtill(pNode->tagName, MAX_HTML_TAG_LENGTH, s, '>', true);
				int tagNameLen = strlen(pNode->tagName);
				if(tagNameLen < MAX_HTML_TAG_LENGTH && pNode->tagName[tagNameLen-1] == '/')
				{
					//�����Է�յı�ǩ, ��<br/>, ɾ��tagName�п��ܻ��е�'/'�ַ�
					//�Է�յĽ���type����ΪNODE_START_TAGӦ�ÿ��Խ���(����Ҫ�����µĽڵ�����NODE_STARTCLOSE_TAG)
					pNode->flags |= FLAG_SELF_CLOSING_TAG; //used by outputHtml() and dumpHtml()
					pNode->tagName[tagNameLen-1] = '\0';
					tagNameLen--;
				}
				//�����ڵ����ƣ���ȡ�����ı�(����pNode->text)
				int i;
				for(i = 0; i < tagNameLen; i++)
				{
					if(isspace(pNode->tagName[i])    //��һ���հ��ַ���������������ı�
						|| pNode->tagName[i] == '=') //��չ֧�����ָ�ʽ: <tagName=value>, ��Ч��<tagName tagName=value>
					{
						char* attributes = (pNode->tagName[i] == '=' ? s : s + i + 1);
						setNodeAttributeText(pNode, attributes); //�˴�Ҳ�������Է�ձ�ǩ
						pNode->tagName[i] = '\0';
						break;
					}
				}
				if(i == tagNameLen)
				{
					//parse error, tag name is too long, MAX_HTML_TAG_LENGTH is too small
				}

				//ʶ��ڵ�����(HtmlTagType) - �ڲ�����
				pNode->tagType = identifyHtmlTag_Internal(pNode->tagName); //�ڲ�ʶ��SCRIPT,STYLE
				if(pNode->tagType == TAG_STYLE)
					bInStyle = (pNode->type == NODE_START_TAG);
				else if(pNode->tagType == TAG_SCRIPT)
					bInScript = (pNode->type == NODE_START_TAG);
				else if(pNode->tagType == TAG_TEXTAREA)
					bInTextArea = (pNode->type == NODE_START_TAG);

				//ʶ��ڵ�����(HtmlTagType) - �û�����
				if(pNode->tagType == TAG_UNKNOWN)
					pNode->tagType = onIdentifyHtmlTag(pNode->tagName, pNode->type);

				//�����ڵ�����
				if(pNode->type == NODE_START_TAG && parseAttributes && pNode->text)
					onParseAttributes(pNode);

				if(onNodeReady(pNode) == false) goto onuserend;
			}

			s = p + 1;
			bInsideTag = bInQuote1 = bInQuote2 = false;
		}

		p++;
	}

	if(p > s)
	{
		//Add Content Node
		pNode = appendHtmlNode();
		pNode->type = NODE_CONTENT;
		setNodeText(pNode, s, strlen(s));
		if(onNodeReady(pNode) == false) goto onuserend;
	}

	goto endnodes;
	return;

onerror:
	pNode = appendHtmlNode();
	pNode->type = NODE_CONTENT;
	setNodeText(pNode, s, strlen(s));
	goto endnodes;
	return;

onuserend:
	goto endnodes;
	return;

endnodes:
	//ȷ�������нڵ����������һ��NODE_NULL�ڵ�
	pNode = appendHtmlNode();
	pNode->type = NODE_NULL;

#ifdef _DEBUG
	//dumpHtmlNodes(); //just for test
#endif
}

int HtmlParser::getHtmlNodeCount()
{
	//���������һ��������ӵ�NODE_NULL�ڵ㣬�μ�parseHtml()
	return (int)(m_HtmlNodes.getDataSize() / sizeof(HtmlNode)) - 1;
}

HtmlNode* HtmlParser::getHtmlNode(int index)
{
	assert(index >= 0 && index <= getHtmlNodeCount());
	return (HtmlNode*)m_HtmlNodes.getData() + index;
}

void HtmlParser::cleanHtmlNodes()
{
	for(int i = 0, count = getHtmlNodeCount(); i < count; i++)
	{
		HtmlNode* pNode = getHtmlNode(i);
		cleanHtmlNode(pNode);
	}
	m_HtmlNodes.clean();
}

void HtmlParser::cleanHtmlNode(HtmlNode* pNode)
{
	if(pNode == NULL) return;

	if(pNode->text && (pNode->flags & FLAG_NEED_FREE_TEXT))
	{
		freeDuplicatedStr(pNode->text);
	}
	pNode->text = NULL;

	if(pNode->attributes)
	{
		for(int attributeIndex = 0; attributeIndex < pNode->attributeCount; attributeIndex++)
		{
			HtmlAttribute* pAttribute = (HtmlAttribute*) getAttribute(pNode, attributeIndex);
			if(pAttribute->name && (pAttribute->flags & FLAG_NEED_FREE_NAME))
				freeDuplicatedStr(pAttribute->name);
			if(pAttribute->value && (pAttribute->flags & FLAG_NEED_FREE_VALUE))
				freeDuplicatedStr(pAttribute->value);
			pAttribute->name = NULL;
			pAttribute->value = NULL;
			pAttribute->flags = 0;
		}
		delete(pNode->attributes); //see: HtmlParser.parseAttributes()
		pNode->attributes = NULL;
	}
	pNode->attributeCount = 0;
}

bool HtmlParser::cloneHtmlNode(const HtmlNode* pSrcNode, HtmlNode* pDestNode)
{
	if(pDestNode == NULL)
		return false;

	memcpy(pDestNode, pSrcNode, sizeof(HtmlNode)); //��ǳ���������������

	if(pSrcNode->text)
	{
		pDestNode->text = duplicateStr(pSrcNode->text, -1);
		pDestNode->flags |= FLAG_NEED_FREE_TEXT;
	}

	if(pSrcNode->attributes)
	{
		pDestNode->attributes = new MemBuffer(*pSrcNode->attributes);
		HtmlAttribute* pAttributes = (HtmlAttribute*) pDestNode->attributes->getData();
		for(int i = 0; i < pSrcNode->attributeCount; ++i)
		{
			HtmlAttribute* pAttribute = pAttributes + i;
			if(pAttribute->name)
			{
				pAttribute->name = duplicateStr(pAttribute->name, -1);
				pAttribute->flags |= FLAG_NEED_FREE_NAME;
			}
			if(pAttribute->value)
			{
				pAttribute->value = duplicateStr(pAttribute->value, -1);
				pAttribute->flags |= FLAG_NEED_FREE_VALUE;
			}
		}
	}
	return true;
}

//[virtual]
void HtmlParser::onParseAttributes(HtmlNode* pNode)
{
	if(pNode->tagType != TAG_UNKNOWN)
		parseAttributes(pNode);
}

void HtmlParser::parseExtraAttributes(const char* szAttributesText, HtmlNode* pTargetNode, const char* szNamePrefix)
{
	assert(pTargetNode);
	const char* p = szAttributesText;
	const char* ps = NULL;
	MemBuffer mem;

	bool inQuote1 = false, inQuote2 = false;
	char c;
	while(c = *p)
	{
		if(c == '\'')
			inQuote1 = !inQuote1;
		else if(c == '\"')
			inQuote2 = !inQuote2;

		bool notInQuote = (!inQuote1 && !inQuote2);

		if(notInQuote && (c == '\"' || c == '\'') && !isspace(p[1]))
		{
			//��������ֵ���ź���û�пհ׷ָ����������a="v1"b=v2 �����ִ���д�����ټ���Ӧ����֮��
			if(ps)
			{
				mem.appendPointer(duplicateStrAndUnquote(ps, p - ps + 1));
				ps = NULL;
			}
			p++;
			continue;
		}

		if(notInQuote && (c == '=' || isspace(c)))
		{
			if(ps)
			{
				mem.appendPointer(duplicateStrAndUnquote(ps, p - ps));
				ps = NULL;
			}
			if(c == '=')
				mem.appendPointer(NULL);
		}
		else
		{
			if(ps == NULL)
				ps = p;
		}

		p++;
	}

	if(ps)
		mem.appendPointer(duplicateStrAndUnquote(ps, p - ps));

	mem.appendPointer(NULL);
	mem.appendPointer(NULL);

	char** pp = (char**) mem.getData();

	//����ѽ�������������ֵ����pTargetNode->attributes

	MemBuffer* attributes = pTargetNode->attributes;
	if(attributes == NULL)
	{
		attributes = new MemBuffer();
		pTargetNode->attributes = attributes;
	}

	for(int i = 0, n = mem.getDataSize() / sizeof(char*) - 2; i < n; i++)
	{
		if(!szNamePrefix)
		{
			attributes->appendPointer(pp[i]); //attribute name
		} else {
			char* newAttributeName = duplicateStr(pp[i], -1, szNamePrefix);
			attributes->appendPointer(newAttributeName); //attribute name
			freeDuplicatedStr(pp[i]);
		}

		if(pp[i+1] == NULL)
		{
			attributes->appendPointer(pp[i+2]); //attribute value
			i += 2;
		}
		else
			attributes->appendPointer(NULL); //attribute vlalue

		//�����free�������ƺ�����ֵ�ı�
		//TODO: �����Ż��������ٸ����ı�
		attributes->appendInt(FLAG_NEED_FREE_NAME | FLAG_NEED_FREE_VALUE); //attribute flags
	}

	attributes->shrink();
	pTargetNode->attributeCount = attributes->getDataSize() / sizeof(HtmlAttribute);
}

void HtmlParser::parseAttributes(HtmlNode* pNode)
{
	if(pNode == NULL || pNode->attributeCount > 0 || pNode->text == NULL)
		return;
	if(pNode->tagName[0] == '!' && stricmp(pNode->tagName+1, "DOCTYPE") == 0)
		return; //don't parse <!DOCTYPE ...>'s text: not name=value syntax
	HtmlParser::parseExtraAttributes(pNode->text, pNode, NULL);
}

const HtmlAttribute* HtmlParser::getAttribute(const HtmlNode* pNode, size_t index)
{
	return ((HtmlAttribute*) pNode->attributes->getData()) + index;
}

const HtmlAttribute* HtmlParser::getAttribute(const HtmlNode* pNode, const char* szAttributeName)
{
	if(pNode == NULL || pNode->attributeCount <= 0)
		return NULL;

	for(int i = 0; i < pNode->attributeCount; i++)
	{
		const HtmlAttribute* attribute = getAttribute(pNode, i);
		if(stricmp(attribute->name, szAttributeName) == 0)
			return attribute;
	}
	return NULL;
}

const char* HtmlParser::getAttributeStringValue(const HtmlNode* pNode, const char* szAttributeName, const char* szDefaultValue /*= NULL*/)
{
	const HtmlAttribute* pAttribute = getAttribute(pNode, szAttributeName);
	if(pAttribute)
		return pAttribute->value;
	else
		return szDefaultValue;
}

int HtmlParser::getAttributeIntValue(const HtmlNode* pNode, const char* szAttributeName, int defaultValue /*= 0*/)
{
	const HtmlAttribute* pAttribute = getAttribute(pNode, szAttributeName);
	if(pAttribute && pAttribute->value)
		return atoi(pAttribute->value);
	else
		return defaultValue;
}

void HtmlParser::dumpHtmlNodes(FILE* f)
{
	fprintf(f, "\r\n-------- begin HtmlParser.dumpHtmlNodes() --------\r\n");
	for(int i = 0, count = getHtmlNodeCount(); i < count; i++)
	{
		HtmlNode* pNode = getHtmlNode(i);
		dumpHtmlNode(pNode, i, f);
	}
	fprintf(f, "-------- end of HtmlParser.dumpHtmlNodes() --------\r\n");
}

void HtmlParser::dumpHtmlNode(const HtmlNode* pNode, int nodeIndex, FILE* f)
{
	assert(pNode);
	char buffer[256] = {0};

	switch(pNode->type)
	{
	case NODE_CONTENT:
		sprintf(buffer, "%2d) type: NODE_CONTENT", nodeIndex);
		break;
	case NODE_START_TAG:
		sprintf(buffer, "%2d) type: NODE_START_TAG, tagName: %s (%d)", nodeIndex, pNode->tagName, pNode->tagType);
		break;
	case NODE_END_TAG:
		sprintf(buffer, "%2d) type: NODE_END_TAG, tagName: %s (%d)", nodeIndex, pNode->tagName, pNode->tagType);
		break;
	case NODE_REMARKS:
		sprintf(buffer, "%2d) type: NODE_REMARKS", nodeIndex);
		break;
	case NODE_UNKNOWN:
	default:
		sprintf(buffer, "%2d) type: UNKNOWN NODE (type = %d)", nodeIndex, pNode->type);
		break;
	}
	fprintf(f, "%s", buffer);
	if(pNode->text)
		fprintf(f, ", text: %s", pNode->text);
	if(pNode->flags & FLAG_SELF_CLOSING_TAG)
		fprintf(f, ", flags: />"); //�Է��
	if(pNode->flags & FLAG_CDATA_BLOCK)
		fprintf(f, ", flags: CDATA"); //CDATA
	fprintf(f, "\r\n");

	if(pNode->attributeCount > 0)
	{
		fprintf(f, "    attributes: ");
		for(int i = 0; i < pNode->attributeCount; i++)
		{
			const HtmlAttribute* pAttribute = getAttribute(pNode, i);
			if(pAttribute->value)
				fprintf(f, "%s = \"%s\"", pAttribute->name, pAttribute->value);
			else
				fprintf(f, "%s", pAttribute->name);
			if(i < pNode->attributeCount - 1)
			{
				fprintf(f, ", ");
			}
		}
		fprintf(f, "\r\n");
	}
}

void HtmlParser::outputHtml(MemBuffer& buffer, bool keepBufferData)
{
	if(!keepBufferData) buffer.empty();
	for(int nodeIndex = 0, count = getHtmlNodeCount(); nodeIndex < count; nodeIndex++)
	{
		HtmlNode* pNode = getHtmlNode(nodeIndex);
		outputHtmlNode(buffer, pNode);
	}
}

void HtmlParser::outputHtmlNode(MemBuffer& buffer, const HtmlNode* pNode)
{
	int attributeIndex = 0;

	if(pNode == NULL)
		return;

	switch(pNode->type)
	{
	case NODE_CONTENT:
		if(pNode->flags & FLAG_CDATA_BLOCK)
		{
			buffer.appendText("<![CDATA[", 9);
			buffer.appendText(pNode->text);
			buffer.appendText("]]>", 3);
		}
		else
			buffer.appendText(pNode->text);
		break;
	case NODE_START_TAG:
		buffer.appendChar('<');
		buffer.appendText(pNode->tagName);
		if(pNode->attributeCount > 0)
			buffer.appendChar(' ');
		for(attributeIndex = 0; attributeIndex < pNode->attributeCount; attributeIndex++)
		{
			const HtmlAttribute* pAttribute = getAttribute(pNode, attributeIndex);
			buffer.appendText(pAttribute->name);
			if(pAttribute->value)
			{
				bool hasQuoteChar = (strchr(pAttribute->value, '\"') != NULL);
				buffer.appendChar('=');
				buffer.appendChar(hasQuoteChar ? '\'' : '\"');
				buffer.appendText(pAttribute->value);
				buffer.appendChar(hasQuoteChar ? '\'' : '\"');
			}
			if(attributeIndex < pNode->attributeCount - 1)
				buffer.appendChar(' ');
		}
		if(pNode->attributeCount == 0 && pNode->text) //���� <!DOCTYPE ...>
		{
			buffer.appendChar(' ');
			buffer.appendText(pNode->text);
		}
		if(pNode->flags & FLAG_SELF_CLOSING_TAG)
			buffer.appendText(" /"); //�Է��
		buffer.appendChar('>');
		break;
	case NODE_END_TAG:
		buffer.appendText("</");
		buffer.appendText(pNode->tagName);
		buffer.appendChar('>');
		break;
	case NODE_REMARKS:
		buffer.appendText("<!--");
		buffer.appendText(pNode->text);
		buffer.appendText("-->");
		break;
	case NODE_UNKNOWN:
	default:
		fprintf(stderr, "HtmlParser.outputHtmlNode(): NODE_UNKNOWN\n");
		break;
	} //end switch
}

//-----------------------------------------------------------------------------
// class MemBuffer

MemBuffer::MemBuffer(size_t nBufferSize) : m_pBuffer(NULL), m_nDataSize(0), m_nBufferSize(0)
{
	if(nBufferSize == (size_t)-1)
		nBufferSize = MEM_DEFAULT_BUFFER_SIZE;
	if(nBufferSize > 0)
		require(nBufferSize);
}

MemBuffer::MemBuffer(const MemBuffer& other) : m_pBuffer(NULL), m_nDataSize(0), m_nBufferSize(0)
{
	*this = other; // invoke operator=()
}

MemBuffer::~MemBuffer()
{
	clean();
}

const MemBuffer& MemBuffer::operator= (const MemBuffer& other)
{
	if(&other != this)
	{
		resetDataSize(0);
		appendData(other.getData(), other.getDataSize());
	}
	return *this;
}

void MemBuffer::clean()
{
	if(m_pBuffer) free(m_pBuffer);
	m_pBuffer = NULL;
	m_nDataSize = m_nBufferSize = 0;
}

void* MemBuffer::detach(bool bShrink)
{
	if(bShrink) shrink();
	void* pReturn = m_pBuffer;
	//���ݳ���Ϊ0ʱ����NULL,�ڲ��ͷ�m_pBuffer
	if(m_pBuffer && m_nDataSize == 0)
	{
		free(m_pBuffer);
		pReturn = NULL;
	}
	m_pBuffer = NULL;
	m_nDataSize = m_nBufferSize = 0;
	return pReturn;
}

void* MemBuffer::require(size_t size)
{
	if(size == 0 || (m_nBufferSize - m_nDataSize) >= size)
		return (m_pBuffer + m_nDataSize); //���л������㹻ʹ�ã�����Ҫ���仺����

	//�����µĻ�������С
	size_t newBufferSize;
	if(m_nBufferSize == 0)
	{
		newBufferSize = size; //��������ʼ��С
	}
	else
	{
		//���仺����
		newBufferSize = (m_nBufferSize == 0 ? MEM_DEFAULT_BUFFER_SIZE : m_nBufferSize);
		do {
			newBufferSize <<= 1; //ÿ������һ��
		}while(newBufferSize - m_nDataSize < size);
	}

	//���仺�����ڴ�
	if(m_pBuffer == NULL)
	{
		m_pBuffer = (unsigned char*) malloc(newBufferSize);
		memset(m_pBuffer, 0, newBufferSize);
	}
	else
	{
		m_pBuffer = (unsigned char*) realloc(m_pBuffer, newBufferSize);
		memset(m_pBuffer + m_nBufferSize, 0, newBufferSize - m_nBufferSize);
	}

	m_nBufferSize = newBufferSize; //�����µĻ�������С

	return (m_pBuffer + m_nDataSize); //����
}

void MemBuffer::shrink()
{
	if(m_pBuffer == NULL || m_nBufferSize == m_nDataSize)
		return;
	//assert(m_nBufferSize > m_nDataSize);
	m_nBufferSize = (m_nDataSize > 0 ? m_nDataSize : MEM_DEFAULT_BUFFER_SIZE);
	m_pBuffer = (unsigned char*) realloc(m_pBuffer, m_nBufferSize);
}

size_t MemBuffer::appendData(const void* pData, size_t nSize)
{
	if(pData == NULL) return m_nDataSize;
	void* p = require(nSize);
	memcpy(p, pData, nSize);
	m_nDataSize += nSize;
	return (m_nDataSize - nSize);
}

void MemBuffer::insertData(size_t offset, const void* pData, size_t nSize)
{
	assert(offset < m_nDataSize);
	if(nSize == 0) return;
	void* pEnd = require(nSize);
	memmove(m_pBuffer + offset + nSize, m_pBuffer + offset, m_nDataSize - nSize - offset);
	if(pData)
		memcpy(m_pBuffer + offset, pData, nSize);
	else
		memset(m_pBuffer + offset, 0, nSize);
	m_nDataSize += nSize;
}

void MemBuffer::deleteData(size_t offset, size_t size)
{
	assert(offset < m_nDataSize);
	if(size == 0) return;
	memmove(m_pBuffer + offset, m_pBuffer + offset + size, m_nDataSize - size - offset);
	memset(m_pBuffer + offset + size, 0, size);
	m_nDataSize -= size;
}

void MemBuffer::resetDataSize(size_t size)
{
	size_t oldDataSize = m_nDataSize;

	if(size <= m_nBufferSize)
	{
		m_nDataSize = size;
	}
	else
	{
		m_nDataSize = 0;
		require(size);
		m_nDataSize = size;
	}

	if(m_nDataSize < oldDataSize)
	{
		//������ݳ��ȱ�ѹ�����ѱ��õ��Ĳ�����������
		memset(m_pBuffer + m_nDataSize, 0, oldDataSize - m_nDataSize);
	}
}

void MemBuffer::exchange(MemBuffer& other)
{
	unsigned char* pBuffer = m_pBuffer;
	size_t nBufferSize = m_nBufferSize;
	size_t nDataSize = m_nDataSize;

	m_pBuffer = other.m_pBuffer;
	m_nBufferSize = other.m_nBufferSize;
	m_nDataSize = other.m_nDataSize;

	other.m_pBuffer = pBuffer;
	other.m_nBufferSize = nBufferSize;
	other.m_nDataSize = nDataSize;
}

size_t MemBuffer::appendText(const char* szText, size_t len, bool appendZeroChar)
{
	if(szText == NULL)
		return m_nDataSize;
	if(len == (size_t)-1)
		len = strlen(szText);
	size_t offset = appendData(szText, len);
	if(appendZeroChar)
		appendChar('\0');
	return offset;
}

size_t MemBuffer::appendZeroBytes(int count)
{
	if(count > 0)
	{
		resetDataSize(m_nDataSize + count);
		return m_nDataSize - count;
	}
	else
	{
		return m_nDataSize;
	}
}

bool MemBuffer::loadFromFile(const char* szFileName, bool keepExistData, bool appendZeroChar, size_t* pReadBytes)
{
	if(!keepExistData) empty();
	if(pReadBytes) *pReadBytes = 0;
	if(szFileName == NULL) return false;
	FILE* pfile = fopen(szFileName, "rb");
	if(pfile)
	{
		fseek(pfile, 0, SEEK_END);
		long filelen = ftell(pfile);
		fseek(pfile, 0, SEEK_SET);
		size_t n = 0;
		if(filelen > 0)
		{
			size_t oldDataSize = getDataSize();
			resetDataSize(oldDataSize + filelen);
			n = fread(getOffsetData(oldDataSize), 1, filelen, pfile);
			resetDataSize(oldDataSize + n);
		}
		if(appendZeroChar) appendChar('\0');
		if(pReadBytes) *pReadBytes = n;

		fclose(pfile);
		return (n == (size_t)filelen); // n != filelen ������£�����false��ͬʱ�����˲����������ݡ���ȷ�����ִ������ò��á�
	}
	
	return false;
}

bool MemBuffer::saveToFile(const char* szFileName, const void* pBOM, size_t bomLen)
{
	FILE* pfile = fopen(szFileName, "wb+");
	if(pfile)
	{
		if(pBOM)
			fwrite(pBOM, 1, bomLen, pfile);
		if(getDataSize() > 0)
			fwrite(getData(), 1, getDataSize(), pfile);
		fclose(pfile);
	}
	return false;
}


//-----------------------------------------------------------------------------

