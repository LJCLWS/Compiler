#pragma once


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

//语法分析器的初始化，包括结尾标识符入栈和起始标志入栈
int Sem_init_parser();
//语法分析器主体部分
int Sem_expression_parser();
//把token序列的元素对应到文法表示的终结符
int Sem_token_to_gramer(int token);
//根据给的非终结符与终结符到LL(1)分析表中查找路径
int Sem_LookUp(int stack, int queue);
//四元式的输出
void Sem_outprint();