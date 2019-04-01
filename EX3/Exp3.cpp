// Exp3.cpp: 定义控制台应用程序的入口点。
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
	int numb=0;  //数据组数
	while (1)
	{
		R[numb].inputStr();
		if (R[numb].isFinish())break;
		numb++;
	}

	for (int i = 0; i < numb; i++) {  //多组数据循环
		R[i].doRPN();
	}

	for (int i = 0; i < numb; i++) {  //多组数据输出
		R[i].outputAns();
	}
	return 0;
}
