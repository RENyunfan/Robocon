// Exp3.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Kevin.h"
#include <iostream>
#include <vector>

using namespace std;
/*
9+(3-1)*3+1/2=
*/

RPN R[10];
int main() {
	int numb=0;  //��������
	while (1)
	{
		R[numb].inputStr();
		if (R[numb].isFinish())break;
		numb++;
	}

	for (int i = 0; i < numb; i++) {  //��������ѭ��
		R[i].doRPN();
	}

	for (int i = 0; i < numb; i++) {  //�����������
		R[i].outputAns();
	}
	return 0;
}
