#ifndef _INPUT_H
#define _INPUT_H

#include "Variable.h"

class Input : protected Variable
{
public:
	Input();
	~Input();

	int get();					//从键盘获取字符
	char take();				//返回正确的字符
private:
	char ch;

	int distinguish();			//判别接受的字符是否需要
	deque<string>::iterator pos;//防止频繁调用
};
#endif