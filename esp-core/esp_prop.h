#ifndef __ESP_PROP_H__
#define __ESP_PROP_H__

//ESP对象(页面/组件)的属性/参数的定义和值

#include <string>
#include "esp_clientapi.h" // only to use ESPPropType, and ESP_INT64
#include "stl_hash_map.h"

struct ESPPropData
{
	union
	{
		bool b;
		int i;
		ESP_INT64 i64;
		float f;
		double d;
		char* text;
		void* bin;
	};
	size_t binlength;
	
	ESPPropData() : i64(0L), binlength(0) {}
};

class ESPPropInfo
{
public:
	std::string m_name;
	std::string m_description;
	std::string m_initial_text; //初始值文本
	ESPPropType m_type;
	bool m_is_formal; //明确定义过的属性, 区别于临时属性
	bool m_is_public; //公开的或私有的，临时属性必然是私有的

	ESPPropData m_initial_data;

	std::string m_definetext; //just for debug

	ESPPropInfo() { init(); }
	int ParsePropInfo(const char* szInfo, size_t len, bool defaultAsPublic, char** pszError);

private:
	void init();
	void ParsePropInfo_x(const std::string& x);
	void ParsePropInfo_ab(const std::string& a, const std::string& b);
	void ParsePropInfo_b(const std::string& b);
	bool ParseType(const std::string& type);
	bool ParseVisibility(const std::string& visibility);
	void SetInitialData();
};


class ESPPropInfos
{
friend class ESPPropValues;
typedef STL_HASH_MAP(std::string,ESPPropInfo*) ESPName2PropInfoMap;

private:
	ESPName2PropInfoMap m_map;
public:
	ESPPropInfo* GetPropInfo(const std::string& propName);
	void AddPropInfo(ESPPropInfo* pPropInfo);
};

//从文本参数szInfos中解析出属性定义信息并存储到ESPPropInfos对象中
//可以多次调用本函数, 把多个szInfos解析到同一个ESPPropInfos对象中
//返回0表示成功, 返回值>0表示出错字符位置
int ParsePropInfos(const char* szInfos, bool defaultAsPublic, ESPPropInfos* pInfos, char** pszError);


struct ESPPropValue
{
	ESPPropInfo* info;
	ESPPropData data;

	ESPPropValue(): info(NULL) {}
};


class ESPPropValues
{
typedef STL_HASH_MAP(std::string,ESPPropValue) ESPName2PropValueMap;

private:
	ESPName2PropValueMap m_values;
	ESPPropInfos* m_infos;

public:
	ESPPropValues(ESPPropInfos* infos): m_infos(infos) {}
	void FillInitialValues();
	bool RemoveAll();
	size_t GetAllPropertyCount();
	char** GetPropertyNames(bool includePublic, bool includePrivate, bool includeInformal, size_t& count);
	bool IsPropertyExist(const std::string& propName, ESPPropType type);
	ESPPropType GetPropertyType(const std::string& propName);
	ESPPropInfo* GetPropertyInfo(const std::string& propName);
	

	//根据属性的类型，自动进行类型转换
	std::string GetProperty(const std::string& propName); //不支持字节集类型(ESPPropType_BINARY)
	bool SetProperty(const std::string& propName, const char* szText);

	//以下读写属性值，要求类型必须匹配，否则操作失败
	bool GetProperty_Bool(const std::string& propName);
	bool SetProperty_Bool(const std::string& propName, bool v);
	int GetProperty_Int(const std::string& propName);
	bool SetProperty_Int(const std::string& propName, int v);
	ESP_INT64 GetProperty_Int64(const std::string& propName);
	bool SetProperty_Int64(const std::string& propName, ESP_INT64 v);
	float GetProperty_Float(const std::string& propName);
	bool SetProperty_Float(const std::string& propName, float v);
	double GetProperty_Double(const std::string& propName);
	bool SetProperty_Double(const std::string& propName, double v);
	const char* GetProperty_Text(const std::string& propName);
	bool SetProperty_Text(const std::string& propName, const char* szText);
	const void* GetProperty_Binary(const std::string& propName, size_t& length);
	bool SetProperty_Binary(const std::string& propName, void* pData, size_t len);	

private:
	ESPPropValue* GetProperty_GetPropValue(const std::string& propName, ESPPropType type);
	ESPPropValue* SetProperty_GetPropValue(const std::string& propName, ESPPropType type);
	ESPPropValue& GetOrInsertPropValueRef(const std::string& propName, ESPPropType type);
	ESPPropInfo* newTempPropInfo(const std::string& propName, ESPPropType type);
};


#endif //__ESP_PROP_H__
