#include "esp_prop.h"
#include <stdio.h>
#include <assert.h>
#include "string_util.h"

// ����ESP�������Զ����ı��������ά�������������Ϣ������ֵ
// by Liigo, before 2009.

using namespace std;

static const char _EscapeChar_ = '!'; //���Զ����ı����ת���ַ� see: remove_single_quoted_and_escape_chars()

//�ж�szCurrentCharָ����ַ��Ƿ�ת��, Ҫ��szFirstCharָ���ı��������
//���ͳ��szCurrentChar�����������!�ַ�, ����true
static bool IsEscapedChar(const char* szCurrentChar, const char* szFirstChar)
{
	assert(szCurrentChar && szFirstChar && szFirstChar <= szCurrentChar);
	if(szCurrentChar == szFirstChar)
		return false;

	size_t nCount = 0;
	while(--szCurrentChar >= szFirstChar && *szCurrentChar == _EscapeChar_)
		nCount++;
	return (nCount % 2 == 1);
}

//���ı�����szInfos�н��������Զ�����Ϣ���洢��ESPPropInfos������
//���Զ�ε��ñ�����, �Ѷ��szInfos������ͬһ��ESPPropInfos������
//����0��ʾ�ɹ�, ����ֵ>0��ʾ�����ַ�λ��
//used by ESPTypeInfoManager::LoadTypeInfo() in esp_managers.cpp
int ParsePropInfos(const char* szInfos, bool defaultAsPublic, ESPPropInfos* pInfos, char** pszError)
{
	if(szInfos == NULL || *szInfos == '\0')
		return 0;

	const char* p = szInfos;
	const char* from = szInfos;
	char c = *p;
	bool inParens = false; //С������, (...)
	bool inQuotes = false; //��������, '...'

	while(c != '\0')
	{
		if(c == '\'')
		{
			assert(inParens); //only accept in brackets
			if(!IsEscapedChar(p, szInfos))
				inQuotes = !inQuotes;
		}

		if(!inQuotes)
		{
			if(c == '(')
			{
				assert(!inParens);
				inParens = true;
			}
			else if(c == ')')
			{
				assert(inParens);
				inParens = false;
			}
		}

		if(!inParens && !inQuotes && (c == ',' || c == ';' || *(p+1) == '\0'))
		{
			const char* to = ((*(p+1) == '\0') ? p + 1 : p);
			while(*from == ' ' && from < to) from++; //ȥ��ǰ��Ŀո�

			if(to > from)
			{
				ESPPropInfo* pPropInfo = new ESPPropInfo();
				int r = pPropInfo->ParsePropInfo(from, to - from, defaultAsPublic, NULL);
				if(r == 0)
					pInfos->AddPropInfo(pPropInfo); //�ѽ������д��ESPPropInfos������
				else
					delete pPropInfo;
			}

			from = to;
			if(*(p+1) != '\0') from++;
		}

		p++; c = *p;
	}

	return 0;
}

void ESPPropInfo::init()
{
	m_name = "";
	m_description = "";
	m_definetext = "";
	m_type = ESPPropType_TEXT;
	m_is_formal = false;
	m_is_public = false;
}

//����ֵΪ0��ʾ�ɹ�������ֵ��Ϊ0��ʾʧ�ܣ�����>0ʱָ�������ַ�λ�ã�
int ESPPropInfo::ParsePropInfo(const char* szInfo, size_t len, bool defaultAsPublic, char** pszError)
{
	assert(szInfo && len > 0);
	if(szInfo == NULL || *szInfo == '\0' || len <= 0)
		return -1;

	init();
	m_is_formal = true;
	m_is_public = defaultAsPublic;
	m_definetext = string(szInfo, len);

	const char* p = szInfo;
	const char* from = szInfo;
	char c = *p;
	bool inParens = false; //С������, (...)
	bool inQuotes = false; //��������, '...'

	int i = 0;
	while(i++ < len)
	{
		if(c == '\'')
		{
			assert(inParens); //only accept in brackets
			if(!IsEscapedChar(p, szInfo))
				inQuotes = !inQuotes;
		}

		if(!inQuotes)
		{
			if(c == '(')
			{
				assert(!inParens);
				inParens = true;

				//get name
				m_name = string(from, p - from);
				m_name = string_trim_lr(m_name, " ");

				from = p + 1;
			}
			else if(c == ')')
			{
				assert(inParens);
				inParens = false;

				ParsePropInfo_x(string(from, p - from));
			}
		}

		if(inParens && !inQuotes && (c == ',' || c == ';'))
		{
			ParsePropInfo_x(string(from, p - from));

			from = p + 1;
		}
		
		p++; c = *p;
	}

	//������һ���ǿ��ַ�����������')', ��Ϊ��������
	if(m_name.length() == 0)
	{
		p = szInfo + len - 1;
		while(p >= szInfo && *p == ' ') p--;
		if(*p != ')')
		{
			m_name = string(szInfo, p - szInfo + 1);
			m_name = string_trim_lr(m_name, " ");
		}
	}

	SetInitialData(); //�����ʼֵ

	return 0;
}

//"int", or, "type:int", or "type=int"
void ESPPropInfo::ParsePropInfo_x(const string& x)
{
	const char* sz = x.c_str(); //only for debug
	string a, b; //a:b

	//�ָ��������� : �� = 
	int separatorIndex = x.find(":");
	if(separatorIndex == string::npos)
		separatorIndex = x.find("=");

	if(separatorIndex != string::npos)
	{
		a = x.substr(0, separatorIndex);
		b = x.substr(separatorIndex+1, x.length() - separatorIndex - 1);

		a = string_trim_lr(a, " ");
		b = string_trim_lr(b, " ");

		ParsePropInfo_ab(a, b);
	}
	else
	{
		b = string_trim_lr(x, " ");
		ParsePropInfo_b(b);
	}
}

bool ESPPropInfo::ParseType(const std::string& type)
{
	if(string_iequal(type, "bool"))
		m_type = ESPPropType_BOOL;
	else if(string_iequal(type, "int"))
		m_type = ESPPropType_INT;
	if(string_iequal(type, "int64"))
		m_type = ESPPropType_INT64;
	else if(string_iequal(type, "float"))
		m_type = ESPPropType_FLOAT;
	else if(string_iequal(type, "double"))
		m_type = ESPPropType_DOUBLE;
	else if(string_iequal(type, "text") || string_iequal(type, "string"))
		m_type = ESPPropType_TEXT;
	else if(string_iequal(type, "binary") || string_iequal(type, "bin"))
		m_type = ESPPropType_BINARY;
	else
		return false;

	return true;
}

bool ESPPropInfo::ParseVisibility(const std::string& visibility)
{
	if(string_iequal(visibility, "public"))
		m_is_public = true;
	else if(string_iequal(visibility, "private"))
		m_is_public = false;
	else
		return false;
	return true;
}

/*
  ȥ���ı����˵ĵ����ţ������������е�ת��������ش������ı���
  �ַ� ! ����ת�������������ڵ��ض��ַ�����ת�壺
  !'  ->  '
  !`  ->  "
  !(  ->  "
  !)  ->  "
  !{  ->  ��
  !}  ->  ��
  !!  ->  !
  ���!������������ַ���!�͸��ַ�����������

  ʹ��!������\��Ϊת���ַ��������ж���
  1������Ԫ���ʽǰ���!ת���ַ�����һ�£�2����\��Ϊת���ַ��ᵼ��ʹ��C���Կ���ESP��ʱ���������ı����Ӹ��ӣ���Ϊ\Ҳ��Cת���ַ�����
*/
static string remove_single_quoted_and_escape_chars(const string& s)
{
	const char* data = s.data();
	size_t len = s.length();

	if(!(len >= 2 && data[0] == '\'' && data[len-1] == '\''))
		return s;

	string temp;
	bool charIsEscape = false;
	for(int i = 1; i < len-1; i++)
	{
		if(data[i] == _EscapeChar_)
		{
			charIsEscape = !charIsEscape;
			if(!charIsEscape)
				temp += data[i];
		}
		else
		{
			if(charIsEscape) //ǰһ���ַ���ת���!��Ҫ�Ե�ǰ�ַ�data[i]ת��
			{
				charIsEscape = false;
				switch(data[i])
				{
				case '\'':
					temp += '\''; break;
				case '(':
				case ')':
				case '`':
					temp += '\"'; break;
				case '{':
					temp += "��"; break;
				case '}':
					temp += "��"; break;
				default:
					assert(false && "unknown escape char");
					temp += _EscapeChar_;
					temp += data[i];
					break;
				}
			}
			else
				temp += data[i];
		}
	} // end for

	return temp;
}

void ESPPropInfo::ParsePropInfo_b(const string& b)
{
	// ��β�е����ŵ���Ϊ˵���ı�
	if(b.length() >= 2 && b.data()[0] == '\'' && b.data()[b.length()-1] == '\'')
	{
		assert(m_description.length() == 0);
		m_description = remove_single_quoted_and_escape_chars(b);
		return;
	}

	// ���� 
	bool ok = ParseType(b);
	if(!ok)
		ok = ParseVisibility(b);
}

//a: Ŀǰ����ʶ�� type, description/help/docs, initial/init, visibility
//b: ��a����
void ESPPropInfo::ParsePropInfo_ab(const string& a, const string& b)
{
	if(string_iequal(a, "type"))
	{
		ParseType(b);
	}
	else if(string_iequal(a, "initial") || string_iequal(a, "init"))
	{
		m_initial_text = remove_single_quoted_and_escape_chars(b); //��Ϊ���Ϳ��ܻ�����ȷ, Ŀǰֻ�洢���ı���ʽ, ��� SetInitialData()
	}
	else if(string_iequal(a, "description") || string_iequal(a, "help") || string_iequal(a, "docs"))
	{
		m_description = remove_single_quoted_and_escape_chars(b);
	}
	else if(string_iequal(a, "visibility"))
	{
		ParseVisibility(b);
	}
}

//����ı�Ϊ true/yes/1/��,  ���� v = true
//����ı�Ϊ false/no/0/��,  ���� v = false
//���������, ����false, ������v���� 
static bool ParseBoolFromText(const char* szText, bool& v)
{
	string s = szText;
	for(int i = 0, n = s.length(); i < n; ++i)
		s[i] = tolower(s[i]);

	if(s == "true" || s == "yes" || s == "1" || s == "��")
		v = true;
	else if(s == "false" || s == "no" || s == "0" || s == "��")
		v = false;
	else
		return false;
	return true;
}

static bool SetPropDataFromText(ESPPropType type, ESPPropData& data, const char* szText, bool set_text_value)
{
	switch(type)
	{
		case ESPPropType_BOOL:
		{
			return ParseBoolFromText(szText, data.b);
		}
		case ESPPropType_INT:
		{
			sscanf(szText, "%d", &(data.i));
			return true;
		}
		case ESPPropType_INT64:
		{
			sscanf(szText, "%I64d", &(data.i64));
			return true;
		}
		case ESPPropType_FLOAT:
		{
			sscanf(szText, "%f", &(data.f));
			return true;
		}
		case ESPPropType_DOUBLE:
		{
			sscanf(szText, "%f", &(data.d));
			return true;
		}
		case ESPPropType_TEXT:
		{
			if(set_text_value)
			{
				freestr(data.text);
				data.text = mallocstr(szText, -1);
			}
			return true;
		}
		default:
			break;
	}

	return false;
}

void ESPPropInfo::SetInitialData()
{
	SetPropDataFromText(m_type, m_initial_data, m_initial_text.c_str(), false);
	//��ʼֵ�в������ı����Ե�ֵ(data.text), ���ʼֵ���ڴ�������ʱָ��, see FillInitialValues()
}

//ESPPropInfos

ESPPropInfo* ESPPropInfos::GetPropInfo(const std::string& propName)
{
	ESPName2PropInfoMap::iterator i = m_map.find(propName);
	return (i == m_map.end() ? NULL : (*i).second);
}

void ESPPropInfos::AddPropInfo(ESPPropInfo* pPropInfo)
{
	assert(pPropInfo);
	ESPName2PropInfoMap::iterator i = m_map.find(pPropInfo->m_name);
	if(i != m_map.end())
	{
		assert(false && "the property name is already exist!");
		delete (*i).second; //��ɾ����ǰ��pPropInfo
		(*i).second = pPropInfo; //�ٰ���ֵд��ȥ
	}
	else
		m_map[pPropInfo->m_name] = pPropInfo;
}

//-----------------------------------------------------------------------------
//ESPPropValues

//�ڲ�ʹ�ã���ȡָ���������Ƶ�ESPPropValue����ֵ�����û�д��������²���һ������Ϊtype�����ԣ�
ESPPropValue& ESPPropValues::GetOrInsertPropValueRef(const std::string& propName, ESPPropType type)
{
	ESPPropValue& propValue = m_values[propName]; //ȡ���е�,���²���

	if(propValue.info == NULL)
	{
		//Ϊ�²���Ľڵ����������Ϣ
		ESPPropInfo* pPropInfo = m_infos->GetPropInfo(propName);
		if(pPropInfo == NULL)
			pPropInfo = newTempPropInfo(propName, type); //��Ҫʱ����һ����ʱ��������Ϣ
		propValue.info = pPropInfo;
	}

	return propValue;
}

//�ڲ��޸�����ʱʹ��, ����ĳ������ֵ��ָ��(���ֵ�������Ѿ����ڵĻ��²����), ����ֱ���޸�������
//�������ֵ��ΪNULL�����������ƺ����ͱ�Ȼ�����һ��
ESPPropValue* ESPPropValues::SetProperty_GetPropValue(const string& propName, ESPPropType type)
{
	assert(type != ESPPropType_NULL);
	if(type == ESPPropType_NULL) return NULL;

	ESPPropValue& propValue = GetOrInsertPropValueRef(propName, type);

	if(propValue.info->m_type == type)
		return &propValue;
	else
		return NULL;
}

ESPPropInfo* ESPPropValues::newTempPropInfo(const string& propName, ESPPropType type)
{
	assert(type != ESPPropType_NULL);

	ESPPropInfo* pPropInfo = new ESPPropInfo();
	assert(pPropInfo);
	if(pPropInfo)
	{
		pPropInfo->m_name = propName;
		pPropInfo->m_type = type;
		pPropInfo->m_is_formal = false; //��ʾ������ʱ�ģ�����ʽ��
		pPropInfo->m_is_public = false; //˽��
	}
	return pPropInfo;
}

//ȡָ����������ָ�����͵�ESPPropValue*����������ڸ����ԣ������Ͳ�һ�£�����NULL��
ESPPropValue* ESPPropValues::GetProperty_GetPropValue(const std::string& propName, ESPPropType type)
{
	ESPName2PropValueMap::iterator i = m_values.find(propName);
	if(i == m_values.end())
		return NULL;

	ESPPropValue& propValue = (*i).second;

	if(propValue.info->m_type != type)
		return NULL;
	else
		return &propValue;
}

bool ESPPropValues::RemoveAll()
{
	ESPName2PropValueMap::iterator i = m_values.begin();
	for(; i != m_values.end(); i++)
	{
		ESPPropValue& value = (*i).second;

		if(value.info->m_type == ESPPropType_TEXT)
			freestr(value.data.text);
		else if(value.info->m_type == ESPPropType_BINARY)
			freebin(value.data.bin);

		if(value.info->m_is_formal == false)
			delete value.info;
	}

	m_values.clear();
	return true;
}

size_t ESPPropValues::GetAllPropertyCount()
{
	return m_values.size();
}

//���������������Ƶ�����(array of char*), ����ֵ������freeɾ���������������е��ı�����.
//û������ʱ����NULL
char** ESPPropValues::GetPropertyNames(bool includePublic, bool includePrivate, bool includeInformal, size_t& count)
{
	count = 0;
	size_t allcount = m_values.size();
	if(allcount == 0 || (!includePublic && !includePrivate && !includeInformal) )
		return NULL;

	char** pszNames = (char**) malloc(allcount * sizeof(char*));
	char** p = pszNames;

	ESPPropInfo* pInfo = NULL;
	ESPName2PropValueMap::iterator i = m_values.begin();
	for(; i != m_values.end(); i++)
	{
		pInfo = (*i).second.info;

		if( (includePublic && pInfo->m_is_public) //��������
			|| (includePrivate && pInfo->m_is_formal && !pInfo->m_is_public) //"��ʽ�����"˽������
			|| (includeInformal && !pInfo->m_is_formal) ) //����ʽ�������ʱ����
		{
			*p++ = (char*) pInfo->m_name.c_str();
			count++;
		}
	}

	assert(m_values.size() == allcount);
	assert(allcount >= count);

	return pszNames;
}

//�ж�ָ�����ƺ����͵������Ƿ���ڣ����typeΪESPPropType_NULL��ֻƥ������
bool ESPPropValues::IsPropertyExist(const string& propName, ESPPropType type)
{
	ESPPropInfo* pPropInfo = GetPropertyInfo(propName);
	if(pPropInfo == NULL)
		return false;
	
	if(type == ESPPropType_NULL)
		return true;
	else
		return (pPropInfo->m_type == type);
}

//���ָ�������Բ�����, ������ESPPropType_NULL (������Դ���,���Ͳ�����ΪESPPropType_NULL)
ESPPropType ESPPropValues::GetPropertyType(const std::string& propName)
{
	ESPPropInfo* pPropInfo = GetPropertyInfo(propName);
	return (pPropInfo ? pPropInfo->m_type : ESPPropType_NULL);
}

ESPPropInfo* ESPPropValues::GetPropertyInfo(const std::string& propName)
{
	ESPName2PropValueMap::iterator i = m_values.find(propName);
	if(i != m_values.end())
		return (*i).second.info;
	else
		return NULL;
}

const char* ESPPropValues::GetProperty_Text(const std::string& propName)
{
	ESPPropValue* pPropValue = GetProperty_GetPropValue(propName, ESPPropType_TEXT);
	return (pPropValue ? pPropValue->data.text : NULL);
}

bool ESPPropValues::SetProperty_Text(const string& propName, const char* szText)
{
	ESPPropValue* pPropValue = SetProperty_GetPropValue(propName, ESPPropType_TEXT);
	if(pPropValue == NULL) return false;

	freestr(pPropValue->data.text);
	pPropValue->data.text = mallocstr(szText, -1);
	return true;
}

int ESPPropValues::GetProperty_Int(const std::string& propName)
{
	ESPPropValue* pPropValue = GetProperty_GetPropValue(propName, ESPPropType_INT);
	return (pPropValue ? pPropValue->data.i : 0);
}

bool ESPPropValues::SetProperty_Int(const std::string& propName, int v)
{
	ESPPropValue* pPropValue = SetProperty_GetPropValue(propName, ESPPropType_INT);
	if(pPropValue)
	{
		pPropValue->data.i = v;
		return true;
	}
	return false;
}

ESP_INT64 ESPPropValues::GetProperty_Int64(const std::string& propName)
{
	ESPPropValue* pPropValue = GetProperty_GetPropValue(propName, ESPPropType_INT64);
	return (pPropValue ? pPropValue->data.i64 : 0);
}

bool ESPPropValues::SetProperty_Int64(const std::string& propName, ESP_INT64 v)
{
	ESPPropValue* pPropValue = SetProperty_GetPropValue(propName, ESPPropType_INT64);
	if(pPropValue)
	{
		pPropValue->data.i64 = v;
		return true;
	}
	return false;
}

float ESPPropValues::GetProperty_Float(const std::string& propName)
{
	ESPPropValue* pPropValue = GetProperty_GetPropValue(propName, ESPPropType_FLOAT);
	return (pPropValue ? pPropValue->data.f : 0);
}

bool ESPPropValues::SetProperty_Float(const std::string& propName, float v)
{
	ESPPropValue* pPropValue = SetProperty_GetPropValue(propName, ESPPropType_FLOAT);
	if(pPropValue)
	{
		pPropValue->data.f = v;
		return true;
	}
	return false;
}

double ESPPropValues::GetProperty_Double(const std::string& propName)
{
	ESPPropValue* pPropValue = GetProperty_GetPropValue(propName, ESPPropType_DOUBLE);
	return (pPropValue ? pPropValue->data.d : 0.0);
}

bool ESPPropValues::SetProperty_Double(const std::string& propName, double v)
{
	ESPPropValue* pPropValue = SetProperty_GetPropValue(propName, ESPPropType_DOUBLE);
	if(pPropValue)
	{
		pPropValue->data.d = v;
		return true;
	}
	return false;
}

bool ESPPropValues::GetProperty_Bool(const std::string& propName)
{
	ESPPropValue* pPropValue = GetProperty_GetPropValue(propName, ESPPropType_BOOL);
	return (pPropValue ? pPropValue->data.b : false);
}

bool ESPPropValues::SetProperty_Bool(const std::string& propName, bool v)
{
	ESPPropValue* pPropValue = SetProperty_GetPropValue(propName, ESPPropType_BOOL);
	if(pPropValue)
	{
		pPropValue->data.b = v;
		return true;
	}
	return false;
}

const void* ESPPropValues::GetProperty_Binary(const std::string& propName, size_t& length)
{
	ESPPropValue* pPropValue = GetProperty_GetPropValue(propName, ESPPropType_BINARY);
	if(pPropValue)
	{
		length = pPropValue->data.binlength;
		return pPropValue->data.bin;
	}
	return NULL;
}

bool ESPPropValues::SetProperty_Binary(const std::string& propName, void* pData, size_t len)
{
	ESPPropValue* pPropValue = SetProperty_GetPropValue(propName, ESPPropType_BINARY);
	if(pPropValue)
	{
		if(pData == NULL || len == 0)
		{
			freebin(pPropValue->data.bin);
			pPropValue->data.binlength = 0;
			return true;
		}

		void* pNewBin = mallocbin(pData, len);
		if(pNewBin == NULL)
			return false;
		freebin(pPropValue->data.bin);
		pPropValue->data.bin = pNewBin;
		pPropValue->data.binlength = len;
		return true;
	}
	return false;
}

string ESPPropValues::GetProperty(const std::string& propName)
{
	ESPName2PropValueMap::iterator i = m_values.find(propName);
	if(i == m_values.end())
		return "";

	ESPPropValue& propValue = (*i).second;
	
	char buffer[128];

	switch(propValue.info->m_type)
	{
		case ESPPropType_BOOL:
		{
			return (propValue.data.b ? "true" : "false");
		}
		case ESPPropType_INT:
		{
			sprintf(buffer, "%d", propValue.data.i);
			return buffer;
		}
		case ESPPropType_INT64:
		{
			sprintf(buffer, "%I64d", propValue.data.i64);
			return buffer;
		}
		case ESPPropType_FLOAT:
		{
			sprintf(buffer, "%f", propValue.data.f);
			return buffer;
		}
		case ESPPropType_DOUBLE:
		{
			sprintf(buffer, "%f", propValue.data.d);
			return buffer;
		}
		case ESPPropType_TEXT:
		{
			return (propValue.data.text ? propValue.data.text : "");
		}
		default:
			break;
	}

	return "";
}

//֧��д������С���ı��߼�ֵ���߼�ֵ�ı�����ʶ�� true/false, yes/no, 1/0, ��/��
bool ESPPropValues::SetProperty(const std::string& propName, const char* szText)
{
	ESPPropValue& propValue = GetOrInsertPropValueRef(propName, ESPPropType_TEXT);

	return SetPropDataFromText(propValue.info->m_type, propValue.data, szText, true);
}

//��ʼ�������Ѷ�������
void ESPPropValues::FillInitialValues()
{
	m_values.clear(); //�����������ֵ
	ESPPropInfos::ESPName2PropInfoMap::iterator i;
	for(i = m_infos->m_map.begin(); i != m_infos->m_map.end(); i++)
	{
		ESPPropInfo* pPropInfo = (*i).second;

		ESPPropValue& propValue = m_values[pPropInfo->m_name]; //��������

		//���¶����Ը���ֵ
		propValue.info = pPropInfo;
		propValue.data = pPropInfo->m_initial_data;
		if(pPropInfo->m_type == ESPPropType_TEXT && !pPropInfo->m_initial_text.empty())
		{
			propValue.data.text = mallocstr(pPropInfo->m_initial_text.c_str(), -1);
		}
	}
}
