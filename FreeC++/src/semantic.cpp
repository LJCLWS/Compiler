#include "lexer.h"
#include "parser_.h"
#include "semantic.h"
#include <vector>
#include <stack>
#include <queue>
#include <iostream>

using namespace std;

const vector<int> gramer[11] =
{
	{ 0 },

	{ NT_T,NT_E1 },
	{ T_PLUS,NT_T,GEQ_PLUS,NT_E1 },
	{ T_MINUS,NT_T,GEQ_MINUS,NT_E1 },
	{ T_NULL },

	{ NT_F,NT_T1 },
	{ T_STAR,NT_F,GEQ_STAR,NT_T1 },
	{ T_DIVIDE,NT_F,GEQ_DIVIDE,NT_T1 },
	{ T_NULL },

	{ T_I,PUSH_I},
	{ T_LEFT,NT_E,T_RIGHT }
};

extern queue<TokenListType> TokenListQueue;
stack<int> Sem_TempRulesStack;
TokenListType Sem_temp_token;
int Sem_temp_terminal = 0;

int Sem_init_parser()
{
	Sem_TempRulesStack.push(BOTH_END);
	Sem_TempRulesStack.push(NT_E);

	//token序号出队列
	Sem_temp_token = TokenListQueue.front();
	TokenListQueue.pop();
	Sem_temp_terminal = token_to_gramer(Sem_temp_token.Ch_class);

	return 0;
}

int Sem_expression_parser()
{
	int temp_rule = 0;
	int choose_way = 0;
	vector<int> temp_gramer;

	//语法分析栈出栈
	temp_rule = Sem_TempRulesStack.top();
	Sem_TempRulesStack.pop();

	if (temp_rule >0 && temp_rule != BOTH_END) {  //是终结符
		if (temp_rule == Sem_temp_terminal) {
			//token序号出队列
			Sem_temp_token = TokenListQueue.front();
			TokenListQueue.pop();
			Sem_temp_terminal = Sem_token_to_gramer(Sem_temp_token.Ch_class);

			Sem_expression_parser();
		}
	}

	else if (temp_rule >= NT_F&& temp_rule <= NT_E)  //是非终结符
	{
		if (choose_way = Sem_LookUp(temp_rule, Sem_temp_terminal))
		{
			//倒序入栈
			temp_gramer = gramer[choose_way];
			while (temp_gramer.size()) {
				Sem_TempRulesStack.push(temp_gramer.back());
				temp_gramer.pop_back();
			}
			Sem_expression_parser();
		}

		else
		{
			cout << "lookup failed" << endl;
			return -1;// error;
		}
	}


	else if (temp_rule >= GEQ_DIVIDE&&temp_rule >= GEQ_PLUS);//GEQ
	else if (temp_rule == PUSH_I);//PUSH


	else if (temp_rule == T_NULL)Sem_expression_parser();
	else if (temp_rule == BOTH_END)
	{
		cout << "alnayze success" << endl;
		return 0;//success
	}


	else
	{
		cout << "alnayze failed" << endl;
		return -1;  //error
	}

	//cout << i++ << endl;
}

//+- token(53,54)    
//*/ token(52,57)  
//变量、常数  token(0,3) i
// (  token(43)
// ） token(44)
int Sem_token_to_gramer(int token)
{
	int code = 0;
	if (token == 0 || token == 3) code = T_I;
	else     code = token;

	return code;
}

int Sem_LookUp(int stack, int queue)
{
	int choose_way;
	switch (stack)
	{
	case NT_E:
		if (queue == T_I || queue == T_LEFT)choose_way = 1;
		else
		{
			cout << "error0" << endl;
			choose_way = 0;//error
		}
		break;
	case NT_E1:
		if (queue == T_PLUS)choose_way = 2;
		else if (queue == T_MINUS)choose_way = 3;
		else if (queue == T_RIGHT || queue == BOTH_END)choose_way = 4;
		else
		{
			cout << "error1" << endl;
			choose_way = 0;//error
		}
		break;
	case NT_T:
		if (queue == T_I || queue == T_LEFT)choose_way = 5;
		else
		{
			cout << "error2" << endl;
			choose_way = 0;//error
		}
		break;
	case NT_T1:
		if (queue == T_STAR)choose_way = 6;
		else if (queue == T_DIVIDE)choose_way = 7;
		else if (queue == T_PLUS || queue == T_MINUS || queue == T_RIGHT || queue == BOTH_END) choose_way = 8;
		else
		{
			cout << "error3" << endl;
			choose_way = 0;//error
		}
		break;
	case NT_F:
		if (queue == T_I)return 9;
		else if (queue == T_LEFT)return 10;
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


