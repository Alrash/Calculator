#ifndef _STDAFX_H

#define _STDAFX_H

#define RET 0x0A		//return
#define ESC 0x1B		//esc
#define DEL 0x7F		//backspace
#define F11 -102		//是在没有办法的写法，通过键入F11得到

enum Error
{
	StrNull,
	NeedOperators,
	NotFindleft,
	NotFindRightValue,
	UnExpectedEqual,
	ExistPoint,
	Backspace,
	Scaling,
	Others,
	Exit
};

#endif