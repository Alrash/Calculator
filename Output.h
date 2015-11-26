#ifndef _OUTPUT_H

#define _OUTPUT_H

#include <string>
#include <ncurses.h>
#include <vector>

using std::string;
using std::vector;

const int COLOR_OPTION = 10;
const int COLOR_KEY = 11;
const int COLOR_ERROR = COLOR_RED;

const int PAIR_OPTION = 1;
const int PAIR_KEY = 2;
const int PAIR_ERROR = 3;
const int PAIR_BKGD = 4;

struct Pos
{
	int x, y;
};


Pos point[22] = { {9, 4}, {7, 2}, {7, 6}, {7, 10},
		{5, 2}, {5, 6}, {5, 10}, {3, 2}, 
		{3, 6}, {3, 10}, {9, 10}, {9, 14},
		{7, 14}, {5, 14}, {3, 14}, {5, 18},
		{1, 11}, {8, 18}, {1, 2}, {1, 6}, 
		{1, 14}, {3, 14}};

class Output
{
public:
	Output();
	~Output();

	int init();
	int Out(string exp, string num, string error, char ch);

private:
	WINDOW *mainwin, *errwin, *optionwin, *keywin, *expwin;
	int line, column;
	string option[5];
	string map[9];
	//vector<char> flags;
	string flags;
	Pos p;
	char ch_last;

	int initoption();
	int initkey();
	int printerr(string error);
	int printexp(string exp, string num, char ch);
	int printkey(char ch);
};

#endif
