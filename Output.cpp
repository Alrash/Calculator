#include "Output.h" 
#include <cstring>
#include <cstdio>

Output::Output()
{
	//start_color();			//初始化像素

	line = LINES;
	column = COLS;

	option[0] = "+加 -减 *乘 /除 ^乘方 ~正负号";
	option[1] = "支持小数点,支持(),支持括号省略";
	option[2] = "= 回车输出结果";
	option[3] = "Esc退出程序";
	option[4] = "其余按键无效";

	map[0] = " ( | ) |  +/-  | A ";
	map[1] = "-------------------";
	map[2] = " 7 | 8 | 9 | / | C ";
	map[3] = "-------------------";
	map[4] = " 4 | 5 | 6 | * | ^ ";
	map[5] = "-------------------";
	map[6] = " 1 | 2 | 3 | - |   ";
	map[7] = "---------------- = ";
	map[8] = "   0   | . | + |   ";

	flags = "0123456789.+-*/^~=()AC";

	/*pos = { {9, 4}, {7, 2}, {7, 6}, {7, 10},
			{5, 2},	{5, 6},	{5, 10}, {3, 2},
			{3, 6}, {3, 10}, {9, 10}, {9, 14},
			{7, 14}, {5, 14}, {3, 14}, {5, 18},
			{1, 11}, {8, 18}, {1, 2}, {1, 6},
			{1, 14}, {3, 14}};*/

	p.x = 9;
	p.y = 4;
	ch_last = '0';

	//init_color(COLOR_OPTION, 255, 69, 0);	//orangeRed
	//init_color(COLOR_KEY, 148, 0, 211);		//DarkViolet

	//init_pair(PAIR_OPTION, COLOR_OPTION, COLOR_BLACK);
	//init_pair(PAIR_KEY, COLOR_KEY, COLOR_BLACK);
	//init_pair(PAIR_ERROR, COLOR_ERROR, COLOR_BLACK);
	//init_pair(PAIR_BKGD, COLOR_BLACK, COLOR_WHITE);
}

Output::~Output()
{
	for (int i = 0; i < 5; i++)
		option[i].clear();

	for (int i = 0; i < 9; i++)
		map[i].clear();

	delwin(mainwin);
	delwin(errwin);
	delwin(optionwin);
	delwin(keywin);
	delwin(expwin);
}

int Output::init()
{
	start_color();

	erase();
	attrset(A_NORMAL);
	attron(A_BOLD);
	mvprintw(0, (column - strlen("Calculator")) / 2, "%s", "Calculator");
	attroff(A_BOLD);
	refresh();

	mainwin = newwin( line - 1, column, 1, 0);
	expwin = newwin( 4, column, 1, 0);
	errwin = newwin( 3, column, 4, 0);
	keywin = newwin( 11, 21, (line - 11) / 2, (column - 20) / 2);
	optionwin = newwin( 8, column, line - 8, 0);

	init_pair(PAIR_BKGD, COLOR_BLACK, COLOR_WHITE);
	wbkgd(expwin, COLOR_PAIR(PAIR_BKGD));
	wrefresh(expwin);

	box(mainwin, '|', '-');
	box(errwin, '|', '-');
	box(expwin, '|', '-');
	box(keywin, '|', '-');
	box(optionwin, '|', '-');

	wrefresh(mainwin);
	wrefresh(errwin);
	wrefresh(expwin);
	wrefresh(keywin);
	wrefresh(optionwin);

	initoption();
	initkey();

	return 0;
}

int Output::Out(string exp, string num, string error, char ch)
{
	if (line != LINES || column != COLS)
	{
		line = LINES;
		column = COLS;

		delwin(mainwin);
		delwin(errwin);
		delwin(optionwin);
		delwin(keywin);
		delwin(expwin);
		init();
	}

	printexp(exp, num, ch);
	printerr(error);
	printkey(ch);

	return 0;
}

int Output::initoption()
{
	start_color();

	init_color(COLOR_OPTION, 255, 0, 255);			//Magenta
	init_pair(PAIR_OPTION, COLOR_OPTION, COLOR_BLACK);

	wattron(optionwin, A_BOLD);
	wattron(optionwin, COLOR_PAIR(PAIR_OPTION));
	mvwprintw(optionwin, 1, 8, "%s", "操作说明:");
	wattroff(optionwin, COLOR_PAIR(PAIR_OPTION));
	wattroff(optionwin, A_BOLD);
	wrefresh(optionwin);

	int len = strlen("操作说明: ") + 6;

	for (int i = 1; i <= 5; i++)
		mvwprintw(optionwin, i, len, "%d.%s", i, option[i - 1].c_str());
	wrefresh(optionwin);

	return 0;
}

int Output::initkey()
{
	for (int i = 1; i <= 9; i++)
		mvwprintw(keywin, i, 1, "%s", map[i - 1].c_str());
	wrefresh(keywin);
	return 0;
}

int Output::printerr(string error)
{
	start_color();

	wmove(errwin, 1, 1);
	wclrtoeol(errwin);
	wrefresh(errwin);
	
	init_pair(PAIR_ERROR, COLOR_RED, COLOR_CYAN);
	wattron(errwin, COLOR_PAIR(PAIR_ERROR));
	mvwprintw(errwin, 1, column - error.size() - 5, "%s", error.c_str());
	wattroff(errwin, COLOR_PAIR(PAIR_ERROR));
	wrefresh(errwin);
	
	return 0;
}

int Output::printexp(string exp, string num, char ch)
{
	start_color();

	if (ch != 'e')
	{
		werase(expwin);

		switch(ch)
		{
		case ')':
			num = "";
			break;
		case '=':
			exp += "=";
			break;
		}
		box(expwin, '|', '-');
		
		wattron(expwin, A_BOLD);
		//wattron(expwin, COLOR_PAIR());
		mvwprintw(expwin, 1, column - exp.size() - num.size() - 5, "%s", exp.c_str());
		wattroff(expwin, A_BOLD);
		wprintw(expwin, "%s", num.c_str());
		mvwprintw(expwin, 2, column - num.size() - 5, "%s", num.c_str());
		wrefresh(expwin);
	}

	return 0;
}

int Output::printkey(char ch)
{
	if (ch != 'e')
	{
		start_color();

		init_color(COLOR_KEY, 131, 111, 255);		//slateBlue1
		init_pair(PAIR_KEY, COLOR_KEY, COLOR_BLACK);
		init_pair(100, COLOR_WHITE, COLOR_BLACK);
		
		if (ch == 's')
		{
			wattroff(keywin, COLOR_PAIR(PAIR_KEY));
			wattron(keywin, A_BOLD);
			wattron(keywin, A_BLINK);
			if (ch == '~')
				mvwprintw(keywin, p.x, p.y, "+/-");
			else
				mvwprintw(keywin, p.x, p.y, "%c", ch);
			wattroff(keywin, A_BLINK);
			wattroff(keywin, A_BOLD);
			wattroff(keywin, COLOR_PAIR(PAIR_KEY));
			wrefresh(keywin);
		
			return 0;
		}

		flags = "0123456789.+-*/^~=()AC";
		int _pos = flags.find(ch);

		//mvwprintw(keywin, 0, 1,"%s %c %d",flags.c_str(),  ch, _pos); 
		
		wattroff(keywin, COLOR_PAIR(100));
		if (ch_last == '~')
			mvwprintw(keywin, p.x, p.y, "+/-");
		else
			mvwprintw(keywin, p.x, p.y, "%c", ch_last);
		wattroff(keywin, COLOR_PAIR(100));
		wrefresh(keywin);

		wattron(keywin, COLOR_PAIR(PAIR_KEY));
		wattron(keywin, A_BOLD);
		wattron(keywin, A_BLINK);
		if (ch == '~')
			mvwprintw(keywin, point[_pos].x, point[_pos].y, "+/-");
		else
			mvwprintw(keywin, point[_pos].x, point[_pos].y, "%c", ch);
		wattroff(keywin, A_BLINK);
		wattroff(keywin, A_BOLD);
		wattroff(keywin, PAIR_KEY);
		wattroff(keywin, COLOR_PAIR(PAIR_KEY));
		wrefresh(keywin);

		p.x = point[_pos].x;
		p.y = point[_pos].y;
		ch_last = ch;
	}

	return 0;
}
