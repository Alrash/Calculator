#ifndef _VARIABLE_H

#define _VARIABLE_H

#include <iostream>
#include <deque>
#include <string>

using std::string;
using std::deque;

class Variable
{
public:
	Variable();
	~Variable();

protected:
	static deque<string> dq;
	static string num;
};

#endif
