#ifndef __HtmlParser_H__
#define __HtmlParser_H__

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

// HtmlParser�࣬���ڽ���HTML�ı�
// http://blog.csdn.net/liigo/article/details/6153829 (��Ҫ)
// by liigo, @2010-2012

namespace liigo
{

//MemBuffer: �ڴ滺�����࣬���������������洢������
#define MEM_DEFAULT_BUFFER_SIZE  256
class MemBuffer
{
public:
	//nBufferSizeָ����������ʼ��С(�ֽ���), Ϊ-1��ʾʹ��Ĭ�ϳ�ʼ��С(MEM_DEFAULT_BUFFER_SIZE)
	//nBufferSizeΪ0ʱ�ݲ����仺�����ڴ棬�ӳٵ���һ��д������ʱ�ٷ���
	MemBuffer(size_t nBufferSize = -1);
	MemBuffer(const MemBuffer& other); //��other���������ݣ������������з����
	virtual ~MemBuffer(); //����ʱ���������ͷ��ڴ棬�����Ѿ�detach()
	const MemBuffer& operator= (const MemBuffer& other); //������ݺ��ٰ�other�ڵ����ݸ��ƽ���

public:
	//�򻺴����������ݿ飬д���������ݵ�ĩβ����Ҫʱ���Զ����仺����
	//������д������ݿ��׵�ַ�ڻ������е�ƫ����
	size_t appendData(const void* pData, size_t nSize);
	//��ָ������offset������ָ������nSize�����ݣ�pDataΪNULLʱ��������ݾ�Ϊ0�ֽ�ֵ��ԭ�������Զ����ƣ���Ҫʱ���Զ����仺����
	void insertData(size_t offset, const void* pData, size_t nSize);
	//��ָ������offset��ɾ��ָ������size�����ݣ�ԭ�������Զ�ǰ��
	void deleteData(size_t offset, size_t size);
	//ȡ�����׵�ַ(�����ݳ���Ϊ0ʱ����NULL)
	//��appendXXX()��insertData()��resetSize()��shrink()��exchange()��operator=����֮����ܻᵼ�������׵�ַ�����ı�
	inline void* getData() const { return (m_nDataSize == 0 ? NULL : m_pBuffer); }
	//ȡָ��ƫ�ƴ����ݵ�ַ��ƫ��offsetӦС��getDataSize()�����򲻱�֤���صĵ�ַ��Ч
	inline void* getOffsetData(int offset) const { return (m_nDataSize == 0 ? NULL : ((unsigned char*)m_pBuffer + offset)); }
	//ȡ���ݳ���
	inline size_t getDataSize() const { return m_nDataSize; }
	//�������ݳ��ȣ��³��ȿ���Ϊ����ֵ����Ҫʱ���Զ����仺�����������ӵ����ݾ�Ϊ0�ֽ�ֵ
	void resetDataSize(size_t size = 0);
	//������ݣ���Ч��resetDataSize(0)
	inline void empty() { resetDataSize(0); }
	//���������������ⳤʱ��ռ�ò���ʹ�õ��ڴ棬���������е�����������Ȼ��������
	void shrink();
	//�����������ͷ��ڴ�
	void clean();
	//�����������������е����ݣ��û�Ӧ���и�����free()�ͷ�detach()�������:
	//���������׵�ַ�����ݳ���Ϊdetach()ǰgetDataSize()���صĳ���
	//detach()ʱָ������bShrinkΪtrue����Ч�����˷�δ��ʹ�õĻ������ڴ�
	void* detach(bool bShrink = true);
	//������������(this & other)���Թ�����������ݣ��������ݺͻ�������
	void exchange(MemBuffer& other);

	//��ӻ�����������
	inline size_t appendInt(int i) { return appendData(&i, sizeof(i)); }
	inline size_t appendChar(char c) { return appendData(&c, sizeof(c)); }
	//��ָ��p�����ֵ������pָ������ݣ���ӵ�������
	inline size_t appendPointer(const void* p) { return appendData(&p, sizeof(p)); }
	//���ı�������ӵ�������, lenΪд����ֽ�����-1��ʾstrlen(szText)����appendZeroChar��ʾ�Ƿ�������'\0'
	size_t appendText(const char* szText, size_t len = -1, bool appendZeroChar = false);
	//��ָ��������0�ֽ�ֵ��ӵ�������
	size_t appendZeroBytes(int count);

	//��ȡ�ļ�ȫ�����ݣ����keepExistData=true������������ԭ�����ݣ��������ԭ������
	//����appendZeroChar��ʾ�Ƿ��������ַ�'\0'������pReadBytesr�����NULL��д����ļ��ж�ȡ���ֽ���
	//�ڴ��̶�д����δ������ȡ�ļ����ݵ�����£�������false�����Ѿ���ȡ�Ĳ���������Ȼ������pReadBytesr�л�д���ȡ���ֽ���
	bool loadFromFile(const char* szFileName, bool keepExistData = false, bool appendZeroChar = false, size_t* pReadBytes = NULL);
	//�����ݱ��浽�ļ�������������(pBOM,bomLen)Ϊ��д���ļ�ͷ����BOM(Byte Order Mark)
	//����ļ��Ѿ����ڣ���ֱ�Ӹ��ǵ�ԭ���ļ�����
	bool saveToFile(const char* szFileName, const void* pBOM = NULL, size_t bomLen = 0);

private:
	//Ҫ�󻺴�����������������Ϊsize��δʹ�ÿռ�
	//����δʹ�ÿռ���׵�ַ�����������ݵ�ĩβ
	void* require(size_t size);

private:
	unsigned char* m_pBuffer; //�������׵�ַ
	size_t m_nDataSize, m_nBufferSize; //���ݳ��ȣ�����������
};

enum HtmlNodeType
{
	NODE_NULL = 0,  //��Ϊ���нڵ���ս���
	NODE_START_TAG, //��ʼ��ǩ���� <a href="liigo.com"> �� <br/>
	NODE_END_TAG,   //������ǩ���� </a>
	NODE_CONTENT,   //����: ���ڿ�ʼ��ǩ��/�������ǩ֮�����ͨ�ı�
	NODE_REMARKS,   //ע��: <!-- -->
	NODE_UNKNOWN,   //δ֪�Ľڵ�����
	_NODE_USER_,    //�û�����������ڵ�����ֵӦ����_NODE_USER_����ȷ���������涨��ĳ���ֵ�ظ�
};

enum HtmlTagType
{
	TAG_UNKNOWN = 0, //��ʾδ��ʶ��ı�ǩ���ͣ��μ�HtmlParser.onIdentifyHtmlTag()
	TAG_SCRIPT, TAG_STYLE, TAG_TEXTAREA, //���ڽ�����Ҫ����ʶ��<script>,<style>��<textarea>���ڲ��ر���
	//���°���ǩ��ĸ˳������, ��Դ��http://www.w3.org/TR/html4/index/elements.html (HTML4)
	//and http://www.w3.org/TR/html5/section-index.html#elements-1 (HTML5)
	//�˴�����������ֵ�������������һ��ʶ������ǣ��μ�HtmlParser.onIdentifyHtmlTag()
	TAG_A, TAG_ABBR, TAG_ACRONYM, TAG_ADDRESS, TAG_APPLET, TAG_AREA, TAG_ARTICLE, TAG_ASIDE, TAG_AUDIO, 
	TAG_B, TAG_BASE, TAG_BASEFONT, TAG_BDI, TAG_BDO, TAG_BIG, TAG_BLOCKQUOTE, TAG_BODY, TAG_BR, TAG_BUTTON, 
	TAG_CAPTION, TAG_CENTER, TAG_CITE, TAG_CODE, TAG_COL, TAG_COLGROUP, TAG_COMMAND, 
	TAG_DATALIST, TAG_DD, TAG_DEL, TAG_DETAILS, TAG_DFN, TAG_DIR, TAG_DIV, TAG_DL, TAG_DT, TAG_EM, TAG_EMBED, 
	TAG_FIELDSET, TAG_FIGCAPTION, TAG_FIGURE, TAG_FONT, TAG_FOOTER, TAG_FORM, TAG_FRAME, TAG_FRAMESET, 
	TAG_H1, TAG_H2, TAG_H3, TAG_H4, TAG_H5, TAG_H6, TAG_HEAD, TAG_HEADER, TAG_HGROUP, TAG_HR, TAG_HTML, 
	TAG_I, TAG_IFRAME, TAG_IMG, TAG_INPUT, TAG_INS, TAG_ISINDEX, TAG_KBD, TAG_KEYGEN, 
	TAG_LABEL, TAG_LEGEND, TAG_LI, TAG_LINK, TAG_MAP, TAG_MARK, TAG_MENU, TAG_META, TAG_METER, TAG_NAV, TAG_NOFRAMES, TAG_NOSCRIPT, 
	TAG_OBJECT, TAG_OL, TAG_OPTGROUP, TAG_OPTION, TAG_P, TAG_PARAM, TAG_PRE, TAG_PROGRESS, TAG_Q, TAG_RP, TAG_RT, TAG_RUBY, 
	TAG_S, TAG_SAMP, TAG_SECTION, TAG_SELECT, TAG_SMALL, TAG_SOURCE, TAG_SPAN, TAG_STRIKE, TAG_STRONG, TAG_SUB, TAG_SUMMARY, TAG_SUP, 
	TAG_TABLE, TAG_TBODY, TAG_TD, TAG_TFOOT, TAG_TH, TAG_THEAD, TAG_TIME, TAG_TITLE, TAG_TR, TAG_TRACK, TAG_TT, 
	TAG_U, TAG_UL, TAG_VAR, TAG_VIDEO, TAG_WBR, 
	_TAG_USER_TAG_, //�û������������ǩ����ֵӦ����_TAG_USER_TAG_����ȷ���������涨��ĳ���ֵ�ظ�
};

enum HtmlNodeFlag
{
	//flags used in HtmlNode.flags
	FLAG_SELF_CLOSING_TAG = 1 << 0, //���Է�ձ�ǩ: <br/>
	FLAG_CDATA_BLOCK      = 1 << 1, //��CDATA����
	FLAG_NEED_FREE_TEXT   = 1 << 2, //��free(HtmlNode.text)

	//flags used in HtmlAttribute.flags
	FLAG_NEED_FREE_NAME   = 1 << 0, //��free(HtmlAttribute.name)
	FLAG_NEED_FREE_VALUE  = 1 << 1, //��free(HtmlAttribute.value)
};

struct HtmlAttribute
{
	char* name;   //��������
	char* value;  //����ֵ
	size_t flags; //bit OR of HtmlNodeFlag
};

#define MAX_HTML_TAG_LENGTH  15 //�ڵ����Ƶ�����ַ�����,���������ض�

struct HtmlNode
{
	HtmlNodeType type;    //�ڵ�����
	HtmlTagType  tagType; //��ǩ���ͣ������ڵ�����ΪNODE_START_TAG��NODE_END_TAGʱ�����壩
	char tagName[MAX_HTML_TAG_LENGTH+1]; //��ǩ���ƣ���<A href="...">��Ӧ�ı�ǩ����Ϊ"A"��
	char* text; //�ı����ӱ�ǩ����(tagType)��ͬ����Ҳ��ͬ������ΪNULL
				//���type==NODE_START_TAG, textָ���ǩ���ƺ���������ı�
				//���type==NODE_CONTENT��NODE_REMARKS, textָ�����ݻ�ע���ı�
	int attributeCount;    //���Ը������������Ա���������Ч���μ�HtmlParser.parseAttributes()����ͬ��
	MemBuffer* attributes; //���ԣ�����=ֵ�����μ�HtmlParser.getAttribute()���������Զ�̬������ԡ�
	size_t flags;    //bit OR of HtmlNodeFlag
	void* pUser;     //user customized, default to NULL
};


//HtmlParser: HTML�ı�������
class HtmlParser
{
public:
	HtmlParser() {}
	virtual ~HtmlParser() { cleanHtmlNodes(); }

private:
	//disallow copy and assign: only declare, no implementation
	HtmlParser(const HtmlParser&);
	void operator=(const HtmlParser&);

public:
	//����HTML�����������һϵ�������洢��HtmlNode�ڵ㣨��ͨ��getHtmlNode(index)��ȡ��
	//����Ȼ��������һ��NODE_NULL�ڵ�(HtmlNode.type==NODE_NULL)��Ϊ���нڵ���ս���
	//����parseAttributesΪtrueʱ���麯��onParseAttributes()��Ҫʱ�������ã��û��л�������Ƿ��������
	//����parseAttributesΪfalse��ʾ�������κ����ԣ�������onParseAttributes()Ҳ�������
	void parseHtml(const char* szHtml, bool parseAttributes = true);

	//ȡ�ڵ���������������һ��������ӵ�NODE_NULL�ڵ㣩
	int getHtmlNodeCount();
	//ȡָ���������Ľڵ㣬��������Ϸ�: 0 <= index <= getHtmlNodeCount()
	//�������һ���ڵ㣨��index==getHtmlNodeCount()����Ϊ������ӵ�NODE_NULL�ڵ�
	HtmlNode* getHtmlNode(int index);

	static bool cloneHtmlNode(const HtmlNode* pSrcNode, HtmlNode* pDestNode); //��ʹ��cleanHtmlNode()����
	static void cleanHtmlNode(HtmlNode* pNode); //ֻ����ڵ��ж�̬��������ݣ�����type,tagType,tagName,flags,pUser
	void cleanHtmlNodes(); //�������нڵ㲢�ͷ���ռ���ڴ�

	//attributes
	static const HtmlAttribute* getAttribute(const HtmlNode* pNode, size_t index); //must: 0 <= index < pNode->attributeCount
	static const HtmlAttribute* getAttribute(const HtmlNode* pNode, const char* szAttributeName); //return NULL if attribute not exist
	static const char* getAttributeStringValue(const HtmlNode* pNode, const char* szAttributeName, const char* szDefaultValue = NULL);
	static int getAttributeIntValue(const HtmlNode* pNode, const char* szAttributeName, int defaultValue = 0);
	static void parseAttributes(HtmlNode* pNode); //����pNode->text���������, ͨ����onParseAttributes()��ʹ��
	static void parseExtraAttributes(const char* szAttributesText, HtmlNode* pTargetNode, const char* szNamePrefix = NULL); //�����ı�szAttributesText������Բ�����pTargetNode������ԭ�����ԣ�, ����szNamePrefix����ָ��������ӵ���������ǰ׺���Է��½�����������ԭ���������Ƴ�ͻ��
	//output
	void outputHtml(MemBuffer& buffer, bool keepBufferData = false);
	static void outputHtmlNode(MemBuffer& buffer, const HtmlNode* pNode);
	void dumpHtmlNodes(FILE* f = stdout); //for debug or test
	static void dumpHtmlNode(const HtmlNode* pNode, int nodeIndex = -1, FILE* f = stdout);

protected:
	//�������า��, �Ա�ʶ������ǩ(��߽�������), ����ʶ����ٱ�ǩ(��߽����ٶ�)
	//Ĭ�Ͻ�ʶ���漰HTML�����ṹ����Ϣ�����޼�����ʼ��ǩ: A,IMG,META,BODY,TITLE,FRAME,IFRAME
	//onIdentifyHtmlTag()����onParseAttributes()������
	virtual HtmlTagType onIdentifyHtmlTag(const char* szTagName, HtmlNodeType nodeType);
	//�������า��, �Ա���õĽ����ڵ�����, ���߲��ֽ��������ɴ಻�����ڵ�����(��߽����ٶ�)
	//���Ը��ݱ�ǩ����(pNode->tagName)���ǩ����(pNode->tagType)�ж��Ƿ���Ҫ�������ԣ�parseAttributes()��
	//Ĭ�Ͻ�����"��ʶ�����ǩ����"�ı�ǩ���ԣ���pNode->tagType != TAG_UNKNOWN��
	virtual void onParseAttributes(HtmlNode* pNode);
	//�������า��, ��ĳ�ڵ������ɺ󱻵���, �������false������ֹͣ����HTML
	//����Ҳ����һ��ǡ����ʱ����ʼ��pNode->pUser
	virtual bool onNodeReady(HtmlNode* pNode) { return true; }

private:
	HtmlNode* appendHtmlNode();

private:
	MemBuffer m_HtmlNodes;
};

} //namespace liigo

#endif //__HtmlParser_H__
