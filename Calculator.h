#ifndef _CALCULATOR_H

#define _CALCULATOR_H

#include <string>
#include "Calculate.h"
#include "Input.h"
#include "Deal.h"
#include "Output.h"

using std::string;

class Calculator
{
public:
	Calculator();
	~Calculator();

	int run();
private:
	Calculate *cal;
	Input in;
	Deal deal;
	Output out;

	string error;
	string value;
	string left;
	char ch;
};

#endif