#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <sstream>
#include "Calculate.h"

using std::stringstream;
using std::find;
using std::find_end;

Calculate::Calculate(const deque<string> dq)
{
	//取出队列的所有值
	deque<string>::const_reverse_iterator last = find(dq.crbegin(), dq.crend(), "(");
	deque<string> *tmp = new deque<string>(dq.crbegin(), last);
	expression = new deque<string>;

	//后期发现做6/5*4是，答案错误，因为原本逆序时，做的是6/(5*4)
	for (deque<string>::iterator iter = tmp->begin(); iter != tmp->end(); iter++)
		expression->push_front(*iter);

	delete tmp;
}

////已无用
//Calculate::Calculate(deque<string> &dq, deque<string>::iterator start)
//{
//	//取出队列的所有值
//	expression = new deque<string>(start + 1, dq.end());
//}

//Calculate::Calculate(deque<string> dq, bool isequal)
//{
//	/*切片取出队列中的值，原队列无损
//	 *")"进入，表示队列尾的情况至少为(10 * 20
//	 */
//	if (isequal == false)
//		expression = new deque<string>(dq.end() - 3, dq.end());
//	else
//		expression = new deque<string>(dq.begin(), dq.end());
//	/*取出队列内部的值，队列无损*/
//	//for(deque<string>::iterator iter = dq.begin(); iter != dq.end(); iter++)
//	//	std::cout << *iter << "\n";
//}

Calculate::~Calculate()
{
	delete expression;
}

/*以下五个运算，均将string转char*转double
 *使用double原因:可能会有小数点
 *不用long double的原因:没必要
 *cout输出时，类似200.00会输出200
 */
double Calculate::add(string exp1, string exp2)
{
	//return atof(exp1.c_str()) + atof(exp2.c_str());
	return strtold(exp1.c_str(), NULL) + strtold(exp2.c_str(), NULL);
}

double Calculate::minus(string exp1, string exp2)
{
	return strtold(exp1.c_str(), NULL) - strtold(exp2.c_str(), NULL);
}

double Calculate::plus(string exp1, string exp2)
{
	return strtold(exp1.c_str(), NULL) * strtold(exp2.c_str(), NULL);
}

double Calculate::div(string exp1, string exp2)
{
	return strtold(exp1.c_str(), NULL) / strtold(exp2.c_str(), NULL);
}

double Calculate::pow(string exp1, string exp2)
{
	return powl(strtold(exp1.c_str(), NULL), strtold(exp2.c_str(), NULL));
}

//计算并返回string
string Calculate::LdToStr(deque<string>::iterator Operator, pfun p)
{
	string value("");
	stringstream ss;						//double转回str使用

	/*switch ((*Operator)[0])
	{
	case '*':p = &Calculate::plus;break;
	case '/':p = &Calculate::div;break;
	case '+':p = &Calculate::add;break;
	case '-':p = &Calculate::minus;break;
	case '^':p = &Calculate::pow;break;
	}*/

	/*将格式化输入给ss
	 *修改精度为15
	 *(this->*p)...调用函数进行计算
	 *根据运算符结合律，可写成下方算法
	 */
	ss.precision(15);
	ss << (this->*p)(*(Operator - 1), *(Operator + 1));
	//格式化输出到value
	ss >> value;

	return value;
}

int Calculate::SameFun(string flag, pfun p)
{
	deque<string>::iterator pos;
	string value;

	while ((pos = find(expression->begin(), expression->end(), flag)) != expression->end())
	{
		value = LdToStr(pos, p);
		expression->insert(pos - 1, value);
		pos = find(expression->begin(), expression->end(), flag);
		expression->erase(pos - 1, pos + 2);		//左闭右开
	}

	return 0;
}

string Calculate::getValue()
{
	SameFun("^", &Calculate::pow);
	SameFun("/", &Calculate::div);
	SameFun("*", &Calculate::plus);
	SameFun("-", &Calculate::minus);
	SameFun("+", &Calculate::add);

	return expression->front();
}

string Calculate::calculate()
{
	return getValue();
}

//推掉的部分
//string Calculate::brakets()
//{
//	return this->function();
//}

//推掉的部分
//string Calculate::equal()
//{
////队列中必为10 + 20 - 30这种情况
//	string value;
//
//	/*流程：10 + 20 - 30...
//	 *1.value = 30 = 10 + 20
//	 *2.队列: - 30...
//	 *3.队列:30 - 30 ...
//	 */
//	do
//	{
//		//计算第一个表达式的值
//		value = this->function();
//		//删除第一个表达式
//		expression->erase(expression->begin(), expression->begin() + 3);
//		//值放入队列
//		expression->push_front(value);
//	} while (expression->size() != 1);
//
//	return expression->at(0);
//}