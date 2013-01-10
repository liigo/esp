#include "esp_dollarexpr.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stack>
#include "esp_objects.h"
#include "esp_prop.h"

// Dollar Expression, 美元表达式: $x{y}
// 解析和求值
// by Liigo, 2012-5-25

//参见头文件中的说明
bool ESP_DollarExpr_Search(const char* szText, ESPDollarExpr& expr, int& leftRemoveLen)
{
	if(szText == NULL) return false;
	const char* pDollar = strchr(szText, '$'); //先找美元符号'$'
	if(pDollar == NULL) return false;

	const char* pOpeningBrace = NULL;
	const char* pClosingBrace = NULL;

	std::stack<char> subexprStack; // '$' or '{'
	const char* p = pDollar + 1;
	int c;

	while(c = *p++)
	{
		switch(c)
		{
		case '$':
			subexprStack.push('$');
			break;
		case '{':
			if(subexprStack.empty())
			{
				pOpeningBrace = p - 1; //定位左括号
			} else {
				assert(subexprStack.top() == '$');
				subexprStack.top() = '{';
			}
			break;
		case '}':
			//允许x{y}中的y里面有非美元表达式的$字符：${$querystring}
			while(!subexprStack.empty() && subexprStack.top() == '$')
				subexprStack.pop();
			if(subexprStack.empty())
			{
				pClosingBrace = p - 1; //定位右括号，表达式解析结束
				if(pOpeningBrace == NULL)
					return ESP_DollarExpr_Search(p, expr, leftRemoveLen);
				else
					goto endparse;
			} else {
				assert(subexprStack.top() == '{');
				subexprStack.pop();
			}
			break;
		case ' ' :
		case '\t':
		case '\n':
		case '\r':
			if((subexprStack.empty() && pOpeningBrace == NULL)
				|| (subexprStack.size() > 0 && subexprStack.top() == '$'))
			{
				//$x{y}: x部分不允许有空白字符，遇到空白字符说明这不是美元表达式，往后面从头找起
				return ESP_DollarExpr_Search(p, expr, leftRemoveLen);
			}
			break;
		default:
			break;
		}
	} //end while(c)

endparse:

	if(c == '\0') return false;

	if(pOpeningBrace == NULL || pClosingBrace == NULL)
	{
		assert((pOpeningBrace && !pClosingBrace) && "uncompleted parsing on dollar expression");
		assert((!pOpeningBrace && pClosingBrace) && "uncompleted parsing on dollar expression");
		return false;
	}

	expr.pDollar = pDollar;
	expr.pOpeningBrace = pOpeningBrace;
	expr.pClosingBrace = pClosingBrace;
	expr.NotEval = false;
	leftRemoveLen = 0;

	//处理表达式前面的转义符号!：!$x{y}, !!$x{y}, !!!$x{y}, ...
	//此处转义规则与C语言的转义符号\一致，已仔细测试无误
	int countOfESC = 0;
	p = pDollar - 1;
	while(p >= szText && *p-- == '!')
		countOfESC++; //统计$号前面紧邻的转义符号!的数量
	if(countOfESC == 0)
		return true;
	if(countOfESC > 0)
	{
		div_t d = div(countOfESC, 2);
		expr.NotEval = (d.rem == 1);
		leftRemoveLen = d.quot + d.rem;
		return true;
	}

	assert(false && "error execute flow");
	return false;
}

std::string ESP_DollarExpr_Eval(const char* szText, ESPComponent* pComponent, bool returnExprTextIfEvalFailed)
{
	ESPDollarExpr expr;
	int leftRemoveLen = 0;
	if(ESP_DollarExpr_Search(szText, expr, leftRemoveLen) == false)
		return std::string(szText);

	std::string result;
	do {
		result.append(szText, expr.pDollar - szText - leftRemoveLen);
		result.append(ESP_DollarExpr_Eval(expr, pComponent, returnExprTextIfEvalFailed));
		szText = expr.pClosingBrace + 1;
	} while(ESP_DollarExpr_Search(szText, expr, leftRemoveLen));
	result.append(szText);
	return result;
}

inline static std::string EvalFailed(std::string& xValue, std::string& yValue, bool returnExprTextIfEvalFailed)
{
	//TODO(liigo): ESP Runtime Error
	return returnExprTextIfEvalFailed ? (std::string("$") + xValue + "{" + yValue + "}") : std::string();
}

std::string ESP_DollarExpr_Eval(const ESPDollarExpr& expr, ESPComponent* pComponent, bool returnExprTextIfEvalFailed)
{
	if(expr.NotEval)
		return std::string(expr.pDollar, expr.pClosingBrace - expr.pDollar + 1);

	std::string x(expr.pDollar + 1, expr.pOpeningBrace - expr.pDollar - 1);
	std::string y(expr.pOpeningBrace + 1, expr.pClosingBrace - expr.pOpeningBrace - 1);

	std::string xValue = ESP_DollarExpr_Eval(x.c_str(), pComponent);
	std::string yValue = ESP_DollarExpr_Eval(y.c_str(), pComponent);

	if(xValue.empty() && !yValue.empty()) 
	{
		// ${pageprop} 返回页面属性值
		assert(pComponent->page);
		if(ESPObject_GetPropertyType(pComponent->page, yValue.c_str()) != ESPPropType_NULL)
		{
			char* szPagePropValue = ESPObject_GetProperty(pComponent->page, yValue.c_str());
			std::string pagePropValue(szPagePropValue ? szPagePropValue : "");
			free(szPagePropValue);
			return pagePropValue;
		} else {
			return EvalFailed(xValue, yValue, returnExprTextIfEvalFailed);
		}
	}

	//TODO: 调用相应ESP库中的美元表达式求值函数 esp_dollar_expr(x,y) or esp_dollar_expr_x(y)

	return EvalFailed(xValue, yValue, returnExprTextIfEvalFailed);
}
