#include <iostream>
#include <ncurses.h>
#include "stdafx.h"
#include "Calculator.h"
#include "Calculate.h"

using namespace std;

int main()
{
	Calculator calculator;

	//calculator.run();

	Calculate *calculate;
	string error, value, left;
	char ch;

	setlocale(LC_ALL, "");		//支持输出中文
	initscr();
	noecho();
	curs_set(false);		//光标隐藏
	keypad(stdscr, true);

	calculator.init();
	calculator.Out("", "", "", 'e');

	while (true)
	{
		error = "";

		try
		{
			calculator.get();
			ch = calculator.take();

			calculator.deal(ch);
			value = calculator.getNum();

			if (ch == ')' || ch == '=')
			{

				calculate = new Calculate(calculator.getDq());
				value = calculate->calculate();
				calculator.del(value);
				delete calculate;

				if (ch == '=')
					left = "=" + value;
			}
		}
		catch (Error e)
		{
			//退出使用
			if (e == Exit)
				break;
			else
			{
				ch = 'e';
				switch (e)
				{
				case StrNull:
					error = "Unexcepted " + ch;
					break;
				case NeedOperators:
					error = "Need Operators";
					break;
				case NotFindleft:
					error = "Not find open parenthesis";
					break;
				case NotFindRightValue:
					error = "In front of close parenthesis, it's just operatoer.";
					break;
				case UnExpectedEqual:
					error = "Lack close parenthesis when inputing equal.";
					break;
				case ExistPoint:
					error = "Existing point, don't input it again.";
					break;
				case Backspace:
					error = "Don't delete any more.";
					break;
				case Others:
					error = "This key can't be used.";
					break;
				}
			}
		}

		calculator.output(calculator.getExpression() + left, value, error, ch);
	}
	
	endwin();

	return 0;
}
