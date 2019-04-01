#include "stdafx.h"
#include "Kevin.h"




bool RPN::isOper(int inow)
{
	int a = Rawdata[inow];
	if ((a == '+') || (a == '-') || (a == '*') || (a == '/') 
			|| (a == '(') || (a == ')') || (a == '='))
		return true;
	else return false;
}

void RPN::inputStr() {
	cin >> Rawdata;
//	cout << Rawdata;
}

void RPN::doRPN() {
	countt = 0;
	for (int j = 0; j < strlen(Rawdata); j++) {//单组数据处理
	//for (int j = 0; j < Rawdata.length(); j++) {//单组数据处理
		if (Rawdata[j] == '=')
		{
			while (!OPT.empty())
			{
				char etop = OPT.top();
				Ans[countt++] = etop;
				OPT.pop();
			}
			break;
		}
		if (isOper(j)) {
			switch (Rawdata[j]) {
				case '(':
				{
					OPT.push(Rawdata[j]);
					break;
				}
				case ')':
				{
					while (1) {
						char wtop = OPT.top();
						if (wtop == '(') {
							OPT.pop(); 
							break;
						}
						else {
							Ans[countt++] = wtop;
							OPT.pop();
							wtop = OPT.top();
						}
					}
						
						
				
				}

				default:
				{
					while (1)
					{
						if (OPT.empty())
						{
							OPT.push(Rawdata[j]);
							break;
						}
						int itop = OPT.top();
						if (isPrio(itop, Rawdata[j]))
						{
							Ans[countt++] = itop;
							OPT.pop();
							itop = OPT.top();
						}
						else
						{
							OPT.push(Rawdata[j]);
							break;
						}
					}
					

				}

			}
		}

		else {
			Ans[countt++] = Rawdata[j];
		}
	}
}


void RPN::outputAns() {
	cout << Ans << endl;
}

bool RPN::isFinish() {
	if (Rawdata[0] == '=')return true;
	else return false;
}

bool RPN::isPrio(char top, char now) {

	//相同优先级
		if (((top == '+')||(top == '-')) && ((now == '+') || (now == '-'))) return true;
		if (((top == '*')||(top == '/')) && ((now == '*') || (now == '/'))) return true;
	//括号优先级
		if (now == ')') return true;
	//较高优先级
		if (((top== '*') || (top == '/')) && ((now == '+') || (now == '-'))) return true;
		return false;
};