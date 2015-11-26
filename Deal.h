/*
 *�����Ǵ�����ȷ���ַ�
 *��֧��(a+b)(a-b),��֧��(a+b)*(a-b)
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
	string sf;							//+ - ����λ

	bool IsFlag();

protected:
	//������ܵ��ַ�
	int point();						//.
	int leftbraket();					//(
	int rightbraket();					//)
	int backspace();					//ɾ��

	int plusminus(char ch);				//+ -
	int flag(char ch);					//* / ^
	int equal();						//=
	int sign();							//~

	int charA(char ch);					//A
	int charC(char ch);					//C
	int charnum(char ch);				//0-9
};

#endif
