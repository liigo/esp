#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

#include <string>
#include <algorithm>
#include <list>
#include <assert.h>

// 字符串是否相等不区分大小写
//template<typename _Char>
bool char_iequal (char elem1, char elem2);

template<class _Elem,
class _Traits,
class _Ax>
bool basic_string_iequal(const std::basic_string<_Elem, _Traits, _Ax>& str1, const std::basic_string<_Elem, _Traits, _Ax>& str2)
{
	if(str1.length() != str2.length()) return false;
	return std::equal(str1.begin(), str1.end(), str2.begin(), char_iequal);
	return true;
}

inline bool string_iequal(const std::string& str1, const std::string& str2)
{
	return basic_string_iequal(str1, str2);
}
inline bool wstring_iequal(const std::wstring& str1, const std::wstring& str2)
{
	return basic_string_iequal(str1, str2);
}

//删除字符串首部(左边)的空白字符
template<class _Elem,
class _Traits,
class _Ax>
std::basic_string<_Elem, _Traits, _Ax> basic_string_trim_l(const std::basic_string<_Elem, _Traits, _Ax>& str, const std::basic_string<_Elem, _Traits, _Ax>& space_chars)
{
	typedef std::basic_string<_Elem, _Traits, _Ax> String;
	size_t pos = str.find_first_not_of(space_chars); //String::size_type GCC编译不过
	if(pos != String::npos)
	{
		return str.substr(pos);
	}
	else if(str.length() > 0 && space_chars.find(str[0]) != String::npos) // 处理整个字符串全部是由 space_chars 中的字符中的一个或多个组成
	{
		return String();
	}
	return str;
}

#define STRING_UTIL_DEFAULT_SPACE_CHARS (" \t　")
#define STRING_UTIL_DEFAULT_SPACE_WCHARS (L" \t　")

inline std::string string_trim_l(const std::string& str)
{
	return basic_string_trim_l(str, std::string(STRING_UTIL_DEFAULT_SPACE_CHARS));
}

inline std::string string_trim_l(const std::string& str, const std::string& space_chars)
{
	return basic_string_trim_l(str, space_chars);
}

inline std::wstring wstring_trim_l(const std::wstring& str)
{
	return basic_string_trim_l(str, std::wstring(STRING_UTIL_DEFAULT_SPACE_WCHARS));
}

inline std::wstring wstring_trim_l(const std::wstring& str, const std::wstring& space_chars)
{
	return basic_string_trim_l(str, space_chars);
}

//删除字符串尾部(右边)的空白字符
template<class _Elem,
class _Traits,
class _Ax>
	std::basic_string<_Elem, _Traits, _Ax> basic_string_trim_r(const std::basic_string<_Elem, _Traits, _Ax>& str, const std::basic_string<_Elem, _Traits, _Ax>& space_chars)
{
	typedef std::basic_string<_Elem, _Traits, _Ax> String;
	size_t pos = str.find_last_not_of(space_chars); //String::size_type GCC编译不过
	if(pos != String::npos)
	{
		return str.substr(0, pos + 1);
	}
	else if(str.length() > 0 && space_chars.find(str[0]) != String::npos) // 处理整个字符串全部是由 space_chars 中的字符中的一个或多个组成
	{
		return String();
	}
	return str;
}

inline std::string string_trim_r(const std::string& str)
{
	return basic_string_trim_r(str, std::string(STRING_UTIL_DEFAULT_SPACE_CHARS));
}

inline std::string string_trim_r(const std::string& str, const std::string space_chars)
{
	return basic_string_trim_r(str, space_chars);
}

inline std::wstring wstring_trim_r(const std::wstring& str)
{
	return basic_string_trim_r(str, std::wstring(STRING_UTIL_DEFAULT_SPACE_WCHARS));
}

inline std::wstring wstring_trim_r(const std::wstring& str, const std::wstring& space_chars)
{
	return basic_string_trim_r(str, space_chars);
}

inline std::string string_trim_lr(const std::string& str)
{
	return string_trim_l(string_trim_r(str));
}

inline std::string string_trim_lr(const std::string& str, const std::string& space_chars)
{
	return string_trim_l(string_trim_r(str, space_chars), space_chars);
}

inline std::wstring wstring_trim_lr(const std::wstring& str)
{
	return wstring_trim_l(wstring_trim_r(str));
}

inline std::wstring wstring_trim_lr(const std::wstring& str, const std::wstring& space_chars)
{
	return wstring_trim_l(wstring_trim_r(str, space_chars), space_chars);
}


//删除字符串中的所有空白字符
template<class String>
struct copy_except
{
	copy_except(String& destination, const String& space_chars) : dest(destination), space(space_chars) {}
	void operator()(const typename String::value_type& c)
	{
		if(String::npos == space.find(c))
			dest.append(1, c);
	}
	String& dest;
	const String& space;
};

template<class _Elem,
class _Traits,
class _Ax>
	std::basic_string<_Elem, _Traits, _Ax> basic_string_trim_through(const std::basic_string<_Elem, _Traits, _Ax>& str, const std::basic_string<_Elem, _Traits, _Ax>& space_chars)
{
	typedef std::basic_string<_Elem, _Traits, _Ax> String;
	String result;
	std::for_each(str.begin(), str.end(), copy_except<String>(result, space_chars));
	return result;
}

inline std::string string_trim_through(const std::string& str)
{
	return basic_string_trim_through(str, std::string(STRING_UTIL_DEFAULT_SPACE_CHARS));
}

inline std::string string_trim_through(const std::string& str, const std::string& space_chars)
{
	return basic_string_trim_through(str, space_chars);
}

inline std::wstring wstring_trim_through(const std::wstring& str)
{
	return basic_string_trim_through(str, std::wstring(STRING_UTIL_DEFAULT_SPACE_WCHARS));
}

inline std::wstring wstring_trim_through(const std::wstring& str, const std::wstring& space_chars)
{
	return basic_string_trim_through(str, space_chars);
}


//-----------------------------------------------------------------------------

//用半角逗号分隔参数szText, 并将分隔后的所有文本加入参数resultList, 自动过滤空白字符
//T可以是支持 push_back() 和 clear() 的任何容器类型, 如 vector<string>
template <class T>
void ParseCommaSeparatedString(const char* szText, T& result)
{
	assert(szText);
	result.clear();
	if(szText == NULL) return;
	
	const char* szDelimit = ",";
	std::string strText = szText, spacechars = " \t\r\n", strToken;
	const char* szTextBak = strText.c_str();
	const char* szToken = strtok((char*)szTextBak, szDelimit);
	while(szToken)
	{
		strToken = szToken;
		strToken = string_trim_through(strToken, spacechars);
		result.push_back(strToken);
		szToken = strtok(NULL, szDelimit);
	}
	return;

}

//alloc a new str, need to be free use freestr()
//len can be -1
char* mallocstr(const char* szSrc, size_t len);

//free a str returned by mallocstr()
void freestr(char* sz);

//malloc a new bin, need to be free by freebin()
void* mallocbin(void* pDataSrc, size_t len);

//free a bin returned by mallocbin()
void freebin(void* pData);

#ifdef __GNUC__
	#include <strings.h>
	#define stricmp strcasecmp
#endif

#endif //__STRING_UTIL_H__
