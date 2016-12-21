#pragma once
#include <stack>
#include <queue>
#include "error.h"
using namespace std;

#define PUSH_I           -6

#define GEQ_STAR         -10
#define GEQ_PLUS         -9
#define GEQ_MINUS        -8
#define GEQ_DIVIDE       -7

#define T_STAR          TK_STAR
#define T_PLUS          TK_PLUS
#define T_MINUS         TK_MINUS
#define T_DIVIDE        TK_DIVIDE

typedef struct FourQtType
{
	string operation;
	string aaa;
	string bbb;
	string ttt;
}FourQtType;


class SemParser:public parser
{
public:
	SemParser(char *fin) :parser(fin) { };
	~SemParser() {};
	//语法分析器的初始化，包括结尾标识符入栈和起始标志入栈
	int init_parser();
	//语法分析器主体部分
	int expression_parser();
	//把token序列的元素对应到文法表示的终结符
	int token_to_gramer(int token);
	//根据给的非终结符与终结符到LL(1)分析表中查找路径
	int LookUp(int stack, int queue);
	//四元式的输出
	void Sem_outprint();

private:
	stack<int> Sem_TempRulesStack;
	TokenListType Sem_temp_token;
	int Sem_temp_terminal = 0;

	stack<string> Sem_TempSem;
	FourQtType Sem_TempFourQt;
	queue<FourQtType> Sem_TempQT;

	ExceptionClass error;

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

		{ T_I,PUSH_I },
		{ T_LEFT,NT_E,T_RIGHT }
	};

};
