#ifndef __ESP_DOLLAR_EXPR_H__
#define __ESP_DOLLAR_EXPR_H__

#include <string>

struct ESPObject;
typedef ESPObject ESPComponent;

struct ESPDollarExpr
{
	const char* pDollar;       // ָ���ַ� $
	const char* pOpeningBrace; // ָ���ַ� {
	const char* pClosingBrace; // ָ���ַ� }
	bool NotEval;              // ����Ҫ�Դ˱��ʽ��ֵ������ !$x{y} ��!ת��Ϊ��ͨ�ı�������ֵ
};

//������Ԫ���ʽ
//
//��szText��Ѱ����������һ����������Ԫ���ʽ$x{y}����������x��yǶ��������Ԫ���ʽ��
//����true��ʾ�ѳɹ���������һ����Ԫ���ʽ�������������expr,leftRemoveLen��������
//  ����expr�м�¼��${}�������ؼ��ַ���λ�ã�leftRemoveLen��ʾ����Ԫ���ʽǰӦ�����Ե��ַ���
//  �˺���Դ�expr.pClosingBrace+1���ٴε��ñ�����������Ѱ�����������Ԫ���ʽ
//����false��ʾszText�ı���û����Ԫ���ʽ
//ע����һ����������������� !!!$x{y} ֮�࣬��������Ȼ�������е���Ԫ���ʽ������true����
//����expr.NotEval==ture��leftRemoveLen==n����Ŀ�����õ������л���ɾ���ñ��ʽǰ���!����
bool ESP_DollarExpr_Search(const char* szText, ESPDollarExpr& expr, int& leftRemoveLen);

//����Ԫ���ʽ��ֵ
//����returnExprTextIfEvalFailed����ȷ������ĳ���ʽ��ֵʧ��ʱ���ñ��ʽ����ֵ�����
//���Ϊfalse�����Ϊ���ı������Ϊtrue�����Ϊ�ñ��ʽ���ı���ʽ"$x{y}"��
//���磺"${x}" ������x�����ڵ�����£����ʽ��Ȼ��ֵʧ�ܣ�����ֵ���������""��"${x}"��
//����Ⱦģ��ʱ�����returnExprTextIfEvalFailedΪtrue����Ч��ʾ�û��ñ��ʽ��ֵʧ�ܣ���
//�ڳ�������жԱ��ʽ��ֵʱӦ���øĲ���Ϊfalse����������߼��Ǵ���ġ�
std::string ESP_DollarExpr_Eval(const ESPDollarExpr& expr, ESPComponent* pComponent, bool returnExprTextIfEvalFailed = false);
std::string ESP_DollarExpr_Eval(const char* szText, ESPComponent* pComponent, bool returnExprTextIfEvalFailed = false);

#endif //__ESP_DOLLAR_EXPR_H__
