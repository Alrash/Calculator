/*
 *仅考虑传入正确的字符
 *不支持(a+b)(a-b),仅支持(a+b)*(a-b)
 */
#ifndef _DEAL_H

#define _DEAL_H

#include <iostream>
#include <string>
#include <deque>
#include "Variable.h"

using std::string;
using std::deque;

class Deal: protected Variable
{
public:
	Deal();
	~Deal();

	string getNum();
	string getExpression();
	deque<string> getDq();

	int deal(char ch);
	int del(string value);

private:
	string expression;
	string sf;							//+ - 符号位

	bool IsFlag();

protected:
	//处理接受的字符
	int point();						//.
	int leftbraket();					//(
	int rightbraket();					//)
	int backspace();					//删除

	int plusminus(char ch);				//+ -
	int flag(char ch);					//* / ^
	int equal();						//=
	int sign();							//~

	int charA(char ch);					//A
	int charC(char ch);					//C
	int charnum(char ch);				//0-9
};

#endif
