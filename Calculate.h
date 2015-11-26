#ifndef _CALCULATE_H

#define _CALCULATE_H

#include <iostream>
#include <string>
#include <deque>

using std::string;
using std::deque;

class Calculate;
typedef double (Calculate::*pfun)(string, string);

/*计算模块
 *接口：
 *构造函数，仅有--Calculate(const deque<string>)
 *calculate()--返回string类型的计算值
 *精度：10
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
	//存放双向队列的值
	deque<string> *expression;
	//指向怎样运算的函数指针
	//double (*p)(string exp1, string exp2);//为指向static对象成员函数的指针
	//double(Calculate::*p)(string exp1, string exp2);

	//string function();
	string LdToStr(deque<string>::iterator Operator, pfun p);	//计算只含单个运算符的表达式
	int SameFun(string flag, pfun p);							//通用算法
	string getValue();											//计算整个表达式

protected:
	double add(string exp1, string exp2);	//'+'
	double minus(string exp1, string exp2);	//'-'
	double plus(string exp1, string exp2);	//'*'
	double div(string exp1, string exp2);	//'/'
	double pow(string exp1, string exp2);	//'^'
};
#endif