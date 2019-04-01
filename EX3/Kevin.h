#pragma once

#include <cstring>
#include <iostream>
#include <stack>
using namespace std;

class RPN {
public:
	//double cal(int);
	bool isOper(int);
	void inputStr();
	void doRPN();
	bool isFinish();
	bool isPrio(char,char);
	void outputAns();
private:
	int countt;
	stack<char> OPT;
	char Ans[100];
	char Rawdata[100];
	//string Ans;
	//string Rawdata;
};
