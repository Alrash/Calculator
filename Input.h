#ifndef _INPUT_H
#define _INPUT_H

#include "Variable.h"

class Input : protected Variable
{
public:
	Input();
	~Input();

	int get();					//�Ӽ��̻�ȡ�ַ�
	char take();				//������ȷ���ַ�
private:
	char ch;

	int distinguish();			//�б���ܵ��ַ��Ƿ���Ҫ
	deque<string>::iterator pos;//��ֹƵ������
};
#endif