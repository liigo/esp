#ifndef __ESP_PROP_H__
#define __ESP_PROP_H__

//ESP����(ҳ��/���)������/�����Ķ����ֵ

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
	std::string m_initial_text; //��ʼֵ�ı�
	ESPPropType m_type;
	bool m_is_formal; //��ȷ�����������, ��������ʱ����
	bool m_is_public; //�����Ļ�˽�еģ���ʱ���Ա�Ȼ��˽�е�

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

//���ı�����szInfos�н��������Զ�����Ϣ���洢��ESPPropInfos������
//���Զ�ε��ñ�����, �Ѷ��szInfos������ͬһ��ESPPropInfos������
//����0��ʾ�ɹ�, ����ֵ>0��ʾ�����ַ�λ��
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
	

	//�������Ե����ͣ��Զ���������ת��
	std::string GetProperty(const std::string& propName); //��֧���ֽڼ�����(ESPPropType_BINARY)
	bool SetProperty(const std::string& propName, const char* szText);

	//���¶�д����ֵ��Ҫ�����ͱ���ƥ�䣬�������ʧ��
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
