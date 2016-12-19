#pragma once

//#define LL1

#define NT_E   -1
#define NT_E1  -2
#define NT_T   -3
#define NT_T1  -4
#define NT_F   -5

#define T_NULL    0
#define T_I       1
#define T_W0      2
#define T_W1      3
#define T_LEFT    TK_OPENPA
#define T_RIGHT   TK_CLOSEPA

#define BOTH_END   TK_SEMICOLON //TK_HASH

//语法分析器的初始化，包括结尾标识符入栈和起始标志入栈
int init_parser();
//语法分析器主体部分
int expression_parser();
//把token序列的元素对应到文法表示的终结符
int token_to_gramer(int token);
//根据给的非终结符与终结符到LL(1)分析表中查找路径
int LookUp(int stack, int queue);

//递归下降主程序
int recursive_Z();
//递归下降子程序
int recursive_E();
int recursive_E1();
int recursive_T();
int recursive_T1();
int recursive_F();
