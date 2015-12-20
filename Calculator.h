#ifndef _CALCULATOR_H

#define _CALCULATOR_H

#include <string>
#include "Input.h"
#include "Deal.h"
#include "Output.h"
#include "Calculate.h"

using std::string;

class Calculator :
	public Input, public Output, public Deal
{
public:
	Calculator();
	~Calculator();

	int run();
private:
	Calculate *cal;
	string error, value, left;
	char ch;
};

#endif
