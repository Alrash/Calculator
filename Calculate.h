#ifndef _CALCULATE_H

#define _CALCULATE_H

#include <iostream>
#include <string>
#include <deque>

using std::string;
using std::deque;

class Calculate;
typedef double (Calculate::*pfun)(string, string);

/*����ģ��
 *�ӿڣ�
 *���캯��������--Calculate(const deque<string>)
 *calculate()--����string���͵ļ���ֵ
 *���ȣ�10
 */
class Calculate
{
public:
	Calculate(const deque<string> dq);
	//Calculate(deque<string> &dq, deque<string>::iterator start);
	//Calculate(deque<string> dq, bool isequal = true);
	~Calculate();

	string calculate();

	//string equal();
	//string brakets();

private:
	//���˫����е�ֵ
	deque<string> *expression;
	//ָ����������ĺ���ָ��
	//double (*p)(string exp1, string exp2);//Ϊָ��static�����Ա������ָ��
	//double(Calculate::*p)(string exp1, string exp2);

	//string function();
	string LdToStr(deque<string>::iterator Operator, pfun p);	//����ֻ������������ı��ʽ
	int SameFun(string flag, pfun p);							//ͨ���㷨
	string getValue();											//�����������ʽ

protected:
	double add(string exp1, string exp2);	//'+'
	double minus(string exp1, string exp2);	//'-'
	double plus(string exp1, string exp2);	//'*'
	double div(string exp1, string exp2);	//'/'
	double pow(string exp1, string exp2);	//'^'
};
#endif