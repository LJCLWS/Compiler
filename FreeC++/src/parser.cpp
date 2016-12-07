#include "lexer.h"
#include "parser_.h"
#include <stack>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

const vector<int> gramer[9]=
{
	{0},
	{NT_T,NT_E1},
	{T_W0,NT_T,NT_E1},
	{T_NULL},
	{NT_F,NT_T1},
	{T_W1,NT_F,NT_T1},
	{T_NULL},
	{T_I},
	{T_LEFT,NT_E,T_RIGHT}
};

extern queue<TokenListType> TokenListQueue;
stack<int> TempRulesStack;
TokenListType temp_token;
int temp_terminal = 0;

int init_parser()
{
	TempRulesStack.push(BOTH_END);
	TempRulesStack.push(NT_E);

	//token序号出队列
	temp_token = TokenListQueue.front();
	TokenListQueue.pop();
	temp_terminal = token_to_gramer(temp_token.Ch_class);

	cout << endl << endl;
	return 0;
}

int expression_parser()
{
	int temp_rule = 0;
	int choose_way = 0;
	vector<int> temp_gramer;
		
	//语法分析栈出栈
	temp_rule = TempRulesStack.top();
	TempRulesStack.pop();

	if (temp_rule >0) {  //是终结符
		if (temp_rule == temp_terminal) {
			if (temp_rule == BOTH_END)
			{
				cout << "syntax alnayze successful" << endl;
				return 0;//success
			}
			//token序号出队列
			temp_token = TokenListQueue.front();
			TokenListQueue.pop();
			temp_terminal = token_to_gramer(temp_token.Ch_class);

			expression_parser();
		}
		else cout << "error";
	}
	
	else if (temp_rule <0)  //是非终结符
	{
		if (choose_way = LookUp(temp_rule, temp_terminal))
		{
            //倒序入栈
			temp_gramer = gramer[choose_way];
			while (temp_gramer.size()) {
				TempRulesStack.push(temp_gramer.back());
				temp_gramer.pop_back();
			}
			expression_parser();
		}
		
		else
		{
			cout << "lookup failed" << endl;
			return -1;// error;
		}
	}
	else if(temp_rule == T_NULL)expression_parser();
	
	else
	{
		cout << "syntax alnayze failed" << endl;
		return -1;  //error
	}
	
}


//+- token(53,54)  w0  
//*/ token(52,57)  w1
//变量、常数  token(0,3) i
// (  token(43)
// ） token(44)
int token_to_gramer(int token)
{
	int code=0;
	if (token == 53 || token == 54)code=T_W0;
	if (token == 52 || token == 57)code=T_W1;
	if (token == 0 || token == 3) code =T_I;
	if (token == 43)code = T_LEFT;
	if (token == 44)code = T_RIGHT;
	//if (token == TK_HASH)code = TK_HASH;
	if (token == TK_SEMICOLON)code = TK_SEMICOLON;
	

	return code;
}





int LookUp(int stack,int queue)
{
	int choose_way;
	switch (stack)
	{
	case NT_E:
		if (queue == T_I || queue == T_LEFT)choose_way = 1;
		else
		{
			cout << "error0"<<endl;
			choose_way = 0;//error
		}
		break;
	case NT_E1:
		if (queue == T_W0 )choose_way = 2;
		else if (queue == T_RIGHT || queue == BOTH_END)choose_way = 3;
		else
		{
			cout << "error1"<<endl;
			choose_way = 0;//error
		}
		break;
	case NT_T:
		if (queue == T_I || queue == T_LEFT)choose_way = 4;
		else
		{
			cout << "error2"<<endl;
			choose_way = 0;//error
		}
		break;
	case NT_T1:
		if (queue == T_W1)choose_way = 5;
		else if(queue == T_W0 || queue == T_RIGHT || queue == BOTH_END) choose_way = 6;
		else
		{
			cout << "error3" << endl;
			choose_way = 0;//error
		}
		break;
	case NT_F:
		if (queue == T_I)return 7;
		else if (queue == T_LEFT)return 8;
		else
		{
			cout << "error4" << endl;
			choose_way = 0;//error
		}
		break;
	default:
		choose_way = 0;//error
        cout << "error5" << endl;

		break;
	}
	
	return choose_way;
}





