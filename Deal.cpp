#include <algorithm>
#include "Deal.h"
#include "stdafx.h"

using std::find;

Deal::Deal()
{
	sf.clear();
}

Deal::~Deal()
{
}

string Deal::getNum()
{
	return sf + num;
}

string Deal::getExpression()
{
	return expression;
}

deque<string> Deal::getDq()
{
	return dq;
}

int Deal::deal(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':plusminus(ch);break;
	case '*':
	case '/':
	case '^':flag(ch);break;
	case '.':point();break;
	case '(':leftbraket();break;
	case ')':rightbraket();break;
	case '=':equal();break;
	case '~':sign();break;
	case 'A':charA(ch);break;
	case 'C':charC(ch);break;
	case DEL:backspace();break;
	default:charnum(ch);break;
	}

	return 0;
}

int Deal::del(string value)
{
	deque<string>::reverse_iterator last = find(dq.rbegin(), dq.rend(), "(");
	
	if (last == dq.rend())
		dq.clear();
	else
		for (int n = last - dq.rbegin(); n >= 0; n--)
			dq.pop_back();
	dq.push_back(value);

	return 0;
}

bool Deal::IsFlag()
{//非空串下使用
	if (num[0] >= '0' && num[0] <= '9')
		return false;
	return true;
}

int Deal::point()
{
	if (num.empty())
	{
		num = "0.";
	}
	else
	{
		if (IsFlag() == true)
		{
			dq.push_back(num);
			expression += num;
			num = "0.";
		}
		else
			num += ".";
	}
	return 0;
}

int Deal::leftbraket()
{
	if (!num.empty())
	{
		if (IsFlag())
		{//运算符
			dq.push_back(num);
			dq.push_back("(");
			expression += (num + "(");
			num.clear();
		}
		else
		{//20(20 + 10)之类
			sf += num;
			dq.push_back(sf);
			dq.push_back("*");
			dq.push_back("(");
			expression = expression + sf + "(";
			sf.clear();
			num.clear();
		}
	}
	else
	{
		//20  (20 + 10)
		if (!dq.empty() && dq.back().back() >= '0' && dq.back().back() <= '9')
			dq.push_back("*");
		dq.push_back("(");
		expression += "(";
	}
	
	return 0;
}

int Deal::rightbraket()
{
	if (!num.empty())
	{//value
		//防止20.
		if (num.back() == '.')
			num += '0';
		sf += num;
		dq.push_back(sf);
		expression += sf;
	}
	expression += ")";
	
	num.clear();
	sf.clear();
	
	return 0;
}

int Deal::backspace()
{
	num.erase(num.size() - 1);		//擦除最后一个
	return 0;
}

int Deal::plusminus(char ch)
{
	//等于号输出之后，应取结果，而不是保留原表达式
	if (dq.size() == 1)
		expression = dq.front();

	if (!num.empty())
	{
		if (!IsFlag())
		{
			if (num.back() == '.')
				num += "0";
			sf += num;

			dq.push_back(sf);
			expression += sf;
		}
	}

	sf.clear();				//情况'+' + '~'
	num = ch;

	return 0;
}

int Deal::flag(char ch)
{
	this->plusminus(ch);
	return 0;
}

int Deal::equal()
{
	if (!num.empty())
	{
		if (num.at(0) >= '0' && num.at(0) <= '9')
		{//else num为符号
			dq.push_back(sf + num);
			expression += (sf + num);
		}
	}

	sf.clear();
	num.clear();

	return 0;
}

int Deal::sign()
{//输入数字的符号位
	if (IsFlag())
	{
		dq.push_back(num);
		expression += num;
		num = "";
		sf.clear();
	}
	
	if (sf.empty())
		sf = "-";
	else
		sf.clear();

	return 0;
}

int Deal::charA(char ch)
{//四个全部清空
	sf.clear();
	dq.clear();
	num.clear();
	expression.clear();

	return 0;
}

int Deal::charC(char ch)
{
	sf.clear();
	num.clear();

	return 0;
}

int Deal::charnum(char ch)
{	
	if (num.empty() == true)
	{
		if (dq.size() == 1 && dq.front().compare("("))
		{//按下等于号后，想继续按数字
		 //&&右值是防止输入
		 //例：5+5=10后按下2,即为2而不是102之类
			dq.clear();
			expression.clear();
		}
		num = ch;
	}
	else
	{//非空，判断num串，是sign还是0-9
	 //符号太多，换思路，判断是否为数字
	 //是数字，则第一个为数值(0. | 1 | -1)
	 //操作:数字，ch连接到后面
	 //符号，符号入队，num = ch
		if (!IsFlag())
			num += ch;
		else
		{
			sf += num;
			dq.push_back(sf);

			expression += sf;		//更新表达式
			num = ch;			//更换操作数
			sf.clear();			//清空符号位
		}
	}

	return 0;
}
