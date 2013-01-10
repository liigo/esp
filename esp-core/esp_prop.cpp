#include "esp_prop.h"
#include <stdio.h>
#include <assert.h>
#include "string_util.h"

// 解析ESP对象属性定义文本，管理和维护对象的属性信息和属性值
// by Liigo, before 2009.

using namespace std;

static const char _EscapeChar_ = '!'; //属性定义文本里的转义字符 see: remove_single_quoted_and_escape_chars()

//判断szCurrentChar指向的字符是否被转义, 要求szFirstChar指向文本的最左边
//如果统计szCurrentChar左边有奇数个!字符, 返回true
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

//从文本参数szInfos中解析出属性定义信息并存储到ESPPropInfos对象中
//可以多次调用本函数, 把多个szInfos解析到同一个ESPPropInfos对象中
//返回0表示成功, 返回值>0表示出错字符位置
//used by ESPTypeInfoManager::LoadTypeInfo() in esp_managers.cpp
int ParsePropInfos(const char* szInfos, bool defaultAsPublic, ESPPropInfos* pInfos, char** pszError)
{
	if(szInfos == NULL || *szInfos == '\0')
		return 0;

	const char* p = szInfos;
	const char* from = szInfos;
	char c = *p;
	bool inParens = false; //小括号内, (...)
	bool inQuotes = false; //单引号内, '...'

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
			while(*from == ' ' && from < to) from++; //去掉前面的空格

			if(to > from)
			{
				ESPPropInfo* pPropInfo = new ESPPropInfo();
				int r = pPropInfo->ParsePropInfo(from, to - from, defaultAsPublic, NULL);
				if(r == 0)
					pInfos->AddPropInfo(pPropInfo); //把解析结果写入ESPPropInfos对象中
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

//返回值为0表示成功，返回值不为0表示失败（其中>0时指出错误字符位置）
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
	bool inParens = false; //小括号内, (...)
	bool inQuotes = false; //单引号内, '...'

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

	//如果最后一个非空字符不是右括号')', 视为属性名称
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

	SetInitialData(); //处理初始值

	return 0;
}

//"int", or, "type:int", or "type=int"
void ESPPropInfo::ParsePropInfo_x(const string& x)
{
	const char* sz = x.c_str(); //only for debug
	string a, b; //a:b

	//分隔符可以是 : 或 = 
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
  去除文本两端的单引号，并处理单引号中的转义符，返回处理后的文本。
  字符 ! 用作转义符，它后面紧邻的特定字符将被转义：
  !'  ->  '
  !`  ->  "
  !(  ->  "
  !)  ->  "
  !{  ->  “
  !}  ->  ”
  !!  ->  !
  如果!后面出现其它字符，!和该字符都将保留。

  使用!而不是\作为转义字符，理由有二：
  1、与美元表达式前面的!转义字符保持一致；2、用\作为转义字符会导致使用C语言开发ESP库时定义属性文本更加复杂（因为\也是C转义字符）。
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
			if(charIsEscape) //前一个字符是转义符!，要对当前字符data[i]转义
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
					temp += "“"; break;
				case '}':
					temp += "”"; break;
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
	// 首尾有单引号的视为说明文本
	if(b.length() >= 2 && b.data()[0] == '\'' && b.data()[b.length()-1] == '\'')
	{
		assert(m_description.length() == 0);
		m_description = remove_single_quoted_and_escape_chars(b);
		return;
	}

	// 类型 
	bool ok = ParseType(b);
	if(!ok)
		ok = ParseVisibility(b);
}

//a: 目前可以识别 type, description/help/docs, initial/init, visibility
//b: 视a而定
void ESPPropInfo::ParsePropInfo_ab(const string& a, const string& b)
{
	if(string_iequal(a, "type"))
	{
		ParseType(b);
	}
	else if(string_iequal(a, "initial") || string_iequal(a, "init"))
	{
		m_initial_text = remove_single_quoted_and_escape_chars(b); //因为类型可能还不明确, 目前只存储其文本形式, 另见 SetInitialData()
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

//如果文本为 true/yes/1/真,  则令 v = true
//如果文本为 false/no/0/假,  则令 v = false
//其它情况下, 返回false, 并保持v不变 
static bool ParseBoolFromText(const char* szText, bool& v)
{
	string s = szText;
	for(int i = 0, n = s.length(); i < n; ++i)
		s[i] = tolower(s[i]);

	if(s == "true" || s == "yes" || s == "1" || s == "真")
		v = true;
	else if(s == "false" || s == "no" || s == "0" || s == "假")
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
	//初始值中不包含文本属性的值(data.text), 其初始值将在创建对象时指定, see FillInitialValues()
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
		delete (*i).second; //先删除先前的pPropInfo
		(*i).second = pPropInfo; //再把新值写进去
	}
	else
		m_map[pPropInfo->m_name] = pPropInfo;
}

//-----------------------------------------------------------------------------
//ESPPropValues

//内部使用，获取指定属性名称的ESPPropValue引用值（如果没有此属性则新插入一个类型为type的属性）
ESPPropValue& ESPPropValues::GetOrInsertPropValueRef(const std::string& propName, ESPPropType type)
{
	ESPPropValue& propValue = m_values[propName]; //取现有的,或新插入

	if(propValue.info == NULL)
	{
		//为新插入的节点填充属性信息
		ESPPropInfo* pPropInfo = m_infos->GetPropInfo(propName);
		if(pPropInfo == NULL)
			pPropInfo = newTempPropInfo(propName, type); //必要时创建一个临时的属性信息
		propValue.info = pPropInfo;
	}

	return propValue;
}

//内部修改属性时使用, 返回某个属性值的指针(这个值可能是已经存在的或新插入的), 可以直接修改其内容
//如果返回值不为NULL，则属性名称和类型必然与参数一致
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
		pPropInfo->m_is_formal = false; //表示这是临时的，非正式的
		pPropInfo->m_is_public = false; //私有
	}
	return pPropInfo;
}

//取指定属性名称指定类型的ESPPropValue*。如果不存在该属性，或类型不一致，返回NULL。
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

//返回所有属性名称的数组(array of char*), 返回值必须用free删除，但不能数组中的文本内容.
//没有属性时返回NULL
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

		if( (includePublic && pInfo->m_is_public) //公开属性
			|| (includePrivate && pInfo->m_is_formal && !pInfo->m_is_public) //"正式定义的"私有属性
			|| (includeInformal && !pInfo->m_is_formal) ) //非正式定义的临时属性
		{
			*p++ = (char*) pInfo->m_name.c_str();
			count++;
		}
	}

	assert(m_values.size() == allcount);
	assert(allcount >= count);

	return pszNames;
}

//判断指定名称和类型的属性是否存在，如果type为ESPPropType_NULL则只匹配名称
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

//如果指定的属性不存在, 将返回ESPPropType_NULL (如果属性存在,类型不可能为ESPPropType_NULL)
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

//支持写入整数小数文本逻辑值。逻辑值文本可以识别 true/false, yes/no, 1/0, 真/假
bool ESPPropValues::SetProperty(const std::string& propName, const char* szText)
{
	ESPPropValue& propValue = GetOrInsertPropValueRef(propName, ESPPropType_TEXT);

	return SetPropDataFromText(propValue.info->m_type, propValue.data, szText, true);
}

//初始化所有已定义属性
void ESPPropValues::FillInitialValues()
{
	m_values.clear(); //清除现有属性值
	ESPPropInfos::ESPName2PropInfoMap::iterator i;
	for(i = m_infos->m_map.begin(); i != m_infos->m_map.end(); i++)
	{
		ESPPropInfo* pPropInfo = (*i).second;

		ESPPropValue& propValue = m_values[pPropInfo->m_name]; //插入属性

		//以下对属性赋初值
		propValue.info = pPropInfo;
		propValue.data = pPropInfo->m_initial_data;
		if(pPropInfo->m_type == ESPPropType_TEXT && !pPropInfo->m_initial_text.empty())
		{
			propValue.data.text = mallocstr(pPropInfo->m_initial_text.c_str(), -1);
		}
	}
}
