#ifndef __ESP_DOLLAR_EXPR_H__
#define __ESP_DOLLAR_EXPR_H__

#include <string>

struct ESPObject;
typedef ESPObject ESPComponent;

struct ESPDollarExpr
{
	const char* pDollar;       // 指向字符 $
	const char* pOpeningBrace; // 指向字符 {
	const char* pClosingBrace; // 指向字符 }
	bool NotEval;              // 不需要对此表达式求值：例如 !$x{y} 被!转义为普通文本无需求值
};

//搜索美元表达式
//
//从szText搜寻并解析出第一个完整的美元表达式$x{y}（允许其中x和y嵌套其他美元表达式）
//返回true表示已成功解析出第一个美元表达式，解析结果存入expr,leftRemoveLen两参数中
//  其中expr中记录了${}这三个关键字符的位置，leftRemoveLen表示该美元表达式前应被忽略的字符数
//  此后可以从expr.pClosingBrace+1处再次调用本函数继续搜寻解析后面的美元表达式
//返回false表示szText文本中没有美元表达式
//注意有一种特殊情况：当遇到 !!!$x{y} 之类，本函数依然解析其中的美元表达式并返回true，但
//设置expr.NotEval==ture且leftRemoveLen==n，其目的是让调用者有机会删除该表达式前面的!符号
bool ESP_DollarExpr_Search(const char* szText, ESPDollarExpr& expr, int& leftRemoveLen);

//对美元表达式求值
//参数returnExprTextIfEvalFailed用于确定“当某表达式求值失败时”该表达式的求值结果：
//如果为false，结果为空文本；如果为true，结果为该表达式的文本形式"$x{y}"。
//例如："${x}" 在属性x不存在的情况下（表达式必然求值失败），求值结果可以是""或"${x}"。
//在渲染模板时令参数returnExprTextIfEvalFailed为true可有效提示用户该表达式求值失败；但
//在程序代码中对表达式求值时应设置改参数为false，否则程序逻辑是错误的。
std::string ESP_DollarExpr_Eval(const ESPDollarExpr& expr, ESPComponent* pComponent, bool returnExprTextIfEvalFailed = false);
std::string ESP_DollarExpr_Eval(const char* szText, ESPComponent* pComponent, bool returnExprTextIfEvalFailed = false);

#endif //__ESP_DOLLAR_EXPR_H__
