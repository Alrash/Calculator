#include <algorithm>
#include <ncurses.h>
#include <locale.h>
#include "Calculator.h"
#include "stdafx.h"

using std::find;

Calculator::Calculator()
{
}

Calculator::~Calculator()
{
}

int Calculator::run()
{
	setlocale(LC_ALL, "");		//支持输出中文
	initscr();
	noecho();
	curs_set(false);		//光标隐藏
	keypad(stdscr, true);
	//start_color();

	Output::init();
	Output::Out("", "", "", 'e');

	while (true)
	{
		error = "";

		try
		{
			Input::get();
			ch = Input::take();

			Deal::deal(ch);
			value = Deal::getNum();

			if (ch == ')' || ch == '=')
			{

				cal = new Calculate(Deal::getDq());
				value = cal->calculate();
				Deal::del(value);
				delete cal;
			}
		}
		catch (Error e)
		{
			//退出使用
			if (e == Exit)
				break;
			else
			{
				ch = 'e';		//error

				switch (e)
				{
				case StrNull:
					error = "Unexcepted Operators";
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
				case Scaling:
					ch = 's';	//scaling
					break;
				case Others:
					error = "This key can't be used.";
					break;
				}
				if (ch == 'c')
					beep();
			}
		}

		Output::Out(Deal::getExpression(), value, error, ch);
	}

	endwin();

	return 0;
}
