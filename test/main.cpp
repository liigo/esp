#include <stdio.h>
#include <stdlib.h>

#include "../esp-core/esp_globals.h"
#include "../esp-core/esp_objects.h"
#include "../esp-core/esp_template.h"
#include "../esp-core/esp_dollarexpr.h"

static void test_load_template()
{
	ESPTemplate t;
	t.LoadFile("test.html");
	t.dumpNodes(stdout);
}

struct DollarExprTestData
{
	const char* szText;
	bool bHasExpr;
	int offsetDollar, offsetOpeningBrace, offsetClosingBrace; //三者均可以为负值
	int leftRemoveLen;
};

static void check_dollar_expr(const DollarExprTestData& t, bool bGotIt, const ESPDollarExpr& expr, int leftRemoveLen)
{
	if(bGotIt)
	{
		assert(t.bHasExpr == !expr.NotEval);
		assert(t.leftRemoveLen == leftRemoveLen);
		
		if(t.offsetDollar >= 0) {
			assert(t.offsetDollar == expr.pDollar - t.szText);
		} else {
			assert(t.offsetDollar == 0 - strlen(expr.pDollar));
		}
	
		if(t.offsetOpeningBrace >= 0) {
			assert(t.offsetOpeningBrace == expr.pOpeningBrace - t.szText);
		} else {
			assert(t.offsetOpeningBrace == 0 - strlen(expr.pOpeningBrace));
		}

		if(t.offsetClosingBrace >= 0) {
			assert(t.offsetClosingBrace == expr.pClosingBrace - t.szText);
		} else {
			assert(t.offsetClosingBrace == 0 - strlen(expr.pClosingBrace));
		}
	} else {
		assert(t.bHasExpr == false);
	}
}

static void test_dollar_expression()
{
	const DollarExprTestData testData[] = 
	{
		{ "$x{y}", true, 0, 2, -1, 0 },
		{ "$x{}", true, 0, 2, 3, 0 },
		{ "${y}", true, 0, 1, 3, 0 },
		{ "${$y}", true, 0, 1, 4, 0 }, //{}之间有非美元表达式的$字符
		{ "xxx$abc{xyz}ooo", true, 3, 7, -4, 0 },
		{ "123!$x{y}...", false, 4, 6, 8, 1 }, //!
		{ "123!!$x{y}...", true, 5, 7, -4, 1 }, //!!, leftRemoveLen=1
		{ "123!!!$x{y}...", false, 6, 8, 10, 2 }, //!!!, leftRemoveLen=2
		{ "$ x{y}", false }, //invalid
		{ " x{y} $", false }, //no expr
		{ "$ x{y} ${}", true, -3, -2, -1, 0 }, //second is valid
		{ "$$a{b}x{y$1{}}", true, 0, 7, -1, 0 }, //嵌套
		{ "...$$a$1{2${3}}{b}x{y$x{}}...", true, 3, -10, -4, 0 }, //多级嵌套
		//    ^               ^     ^
		{ NULL, } //end test data
	};

	ESPDollarExpr expr;
	int leftRemoveLen;
	int i = 0;
	while(testData[i].szText)
	{
		bool gotIt = ESP_DollarExpr_Search(testData[i].szText, expr, leftRemoveLen);
		check_dollar_expr(testData[i], gotIt, expr, leftRemoveLen);
		i++;
	}

	std::string s;
	s = ESP_DollarExpr_Eval("+++$x{y}...", NULL);
	s = ESP_DollarExpr_Eval("!$x{y}_!!$x{y}", NULL);
	s = ESP_DollarExpr_Eval("+++$<$a{b}>{y}...", NULL);
	s = ESP_DollarExpr_Eval("+++$<$a{b}x>{$1{0}y}...", NULL);
	s = ESP_DollarExpr_Eval("...$<$a$1{2$3{0}}{b}x>{y$x{}}__$k{}.", NULL);
}

int main()
{
	test_dollar_expression();
	//test_load_template();
	return 0;
}
