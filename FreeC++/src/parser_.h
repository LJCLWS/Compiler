#pragma once



typedef struct GrammerType {
	int token;
	string gram;
}GrammerType;




#define NT_E   -1
#define NT_E1  -2
#define NT_T   -3
#define NT_T1  -4
#define NT_F   -5

#define T_NULL    0
#define T_I       1
#define T_W0      2
#define T_W1      3
#define T_LEFT    4
#define T_RIGHT   5

#define BOTH_END   TK_SEMICOLON //TK_HASH

int init_parser();
int expression_parser();
int token_to_gramer(int token);
int LookUp(int stack, int queue);