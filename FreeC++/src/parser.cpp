#include "lexer.h"
#include "parser_.h"
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include "error.h"

using namespace std;


//LL(1)分析表
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
#ifdef LL1
	TempRulesStack.push(BOTH_END);
	TempRulesStack.push(NT_E);

	//token序号出队列
	temp_token = TokenListQueue.front();
	TokenListQueue.pop();
	temp_terminal = token_to_gramer(temp_token.Ch_class);

	cout << endl << endl;
	return 0;
#else 
//token序号出队列
temp_token = TokenListQueue.front();
TokenListQueue.pop();
temp_terminal = token_to_gramer(temp_token.Ch_class);

return temp_terminal;
#endif
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
		else syntax_error(MATCH_ERROR);
	}
	
	else if (temp_rule <0)  //是非终结符
	{
		if ((choose_way = LookUp(temp_rule, temp_terminal))>0)
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
			return ERROR;// error;
		}
	}
	else if(temp_rule == T_NULL)expression_parser();
	
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
			choose_way = syntax_error(LOOKUP_ERROR0);//error
		}
		break;
	case NT_E1:
		if (queue == T_W0 )choose_way = 2;
		else if (queue == T_RIGHT || queue == BOTH_END)choose_way = 3;
		else
		{
			choose_way = syntax_error(LOOKUP_ERROR1);//error
		}
		break;
	case NT_T:
		if (queue == T_I || queue == T_LEFT)choose_way = 4;
		else
		{
			choose_way = syntax_error(LOOKUP_ERROR2);//error
		}
		break;
	case NT_T1:
		if (queue == T_W1)choose_way = 5;
		else if(queue == T_W0 || queue == T_RIGHT || queue == BOTH_END) choose_way = 6;
		else
		{
			choose_way = syntax_error(LOOKUP_ERROR3);//error
		}
		break;
	case NT_F:
		if (queue == T_I)return 7;
		else if (queue == T_LEFT)return 8;
		else
		{
			choose_way = syntax_error(LOOKUP_ERROR4);//error
		}
		break;
	default:
		choose_way = syntax_error(LOOKUP_ERROR5);//error

		break;
	}
	
	return choose_way;
}



//递归下降子程序法
//E->T E1
//E1->ω0T E1 |&
//T  -> F T1
//T1 -> ω1F T1 | &
//F  -> i | ( E )
int class_code=0;

int recursive_Z()
{
	class_code=init_parser();
	recursive_E();
	if (class_code == BOTH_END)
	{
		cout << endl<<"syntax alnayze successful" << endl;
		return 0;//结束
	}
	else
	{
		syntax_error(WRONG_END);
		return ERROR;
	}
		
}

int recursive_E()
{
	recursive_T();
	recursive_E1();
	return 0;
}

int recursive_E1()
{
	if (class_code == T_W0)
	{
		class_code = init_parser();
		recursive_T();
		recursive_E1();
	}
	else  //空
	{
		return 0;//结束
	}
		
}
int recursive_T()
{
	recursive_F();
	recursive_T1();
	return 0;
}
int recursive_T1()
{
	if (class_code == T_W1)
	{
		class_code = init_parser();
		recursive_F();
		recursive_T1();
	}
	else
	{ 
		return 0;//结束
	}		
}
int recursive_F()
{
	if (class_code == T_I)
	{
		class_code = init_parser();
		return 0;//结束
	}
	else if (class_code == T_LEFT)
	{
		class_code = init_parser();
		recursive_E();
		if (class_code == T_RIGHT)
		{
			class_code = init_parser();
			return class_code;//结束
		}
		else
		{
			syntax_error(MATCH_ERROR);
			class_code = -1;
			return ERROR;
		}
		    
	}
	else
	{
		syntax_error(WRONG_END);
		return ERROR;
	}
}
