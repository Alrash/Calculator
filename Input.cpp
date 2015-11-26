#include <iostream>
#include <algorithm>
//#include <conio.h>		//window
#include <curses.h>		//linux
#include <cstdio>
#include "Input.h"
#include "stdafx.h"

using std::find;

Input::Input()
{
}

Input::~Input()
{
}

int Input::get()
{
//记得修改
	ch = getch();
	return 0;
}

char Input::take()
{
	this->distinguish();
	return ch;
}

/*
 *需要的字符:0-9 a c + - * / ^ ~ ( ) . backspace esc
 *特殊字符解释:^ 幂 ~ 正负号 C 清除 A 全清
 *throw条件:0-9 ~ A C ( backspace 没有
 * ( 没有的解释:输入成(?)(?)，会被处理成(?)*(?)
 * //已放弃//( :num空,队尾为字符，否则，num为字符
 * ) :队列中没有 (
 *ecs:按下后退出程序
 * + - * / = ^ :一开始就输入，或者队列尾部为(
 * . :正在输入的串中已有.
 */
int Input::distinguish()
{
	if (('0' > ch || ch > '9') && ch != '~')
	{
		ch = toupper(ch);

		switch (ch)
		{
		case DEL:
			if (num.empty() == true)
				throw Backspace;
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			if (num.empty())
			{
				if (dq.empty() || !dq.back().compare("("))
					throw StrNull;
			}
			break;
		case '(':
			//if (num.empty())
			//{//队尾数字
			//	if (dq.back().at(dq.back().size()) >= '0' && dq.back().at(dq.back().size()) <= '9')
			//		throw UnExpectedLeft;
			//}
			//else
			//{
			//	if (num.at(0) >= '0' && num.at(0) <= '9')
			//		throw UnExpectedLeft;
			//}
			break;
		case ')':
			pos = find(dq.begin(), dq.end(), "(");
			if (pos == dq.end())
				throw NotFindleft;
			if (!num.empty() && (num.at(0) >= '9' || num.at(0) <= '0'))
				throw NotFindRightValue;
			if (num.empty() && !(dq.back().back() >= '0' && dq.back().back() <= '9'))
				throw NotFindRightValue;
			break;
		case '.':
			if (num.find('.') != -1)
				throw ExistPoint;
			break;
		case RET:
			ch = '=';
		case '=':
			if (dq.empty())
				if (num.empty())
					throw StrNull;
			pos = find(dq.begin(), dq.end(), "(");
			if (!num.empty())
			{
				if (pos != dq.end() && num.at(0) != ')')
					throw UnExpectedEqual;
			}
			break;
		case ESC:
			throw Exit;
		case 'A':
		case 'C':break;
		case F11:
			throw Scaling;
			break;
		default:
			throw Others;
			break;
		}
	}
	else
	{//防止出现5+(5+2)55情况
	 //判断0-9
		if (ch != '~')
			if (!dq.empty() && num.empty() && (dq.back().back() >= '0' && dq.back().back() <= '9'))
				if (dq.size() != 1)
					throw NeedOperators;
	}
	
	return 0;
}