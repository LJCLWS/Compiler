#pragma once


#define PUSH_I           -6

#define GEQ_PLUS         -7
#define GEQ_MINUS        -8
#define GEQ_STAR         -9
#define GEQ_DIVIDE      -10

#define T_PLUS          TK_PLUS
#define T_MINUS         TK_MINUS
#define T_STAR          TK_STAR
#define T_DIVIDE        TK_DIVIDE

int Sem_init_parser();
int Sem_expression_parser();
int Sem_token_to_gramer(int token);
int Sem_LookUp(int stack, int queue);
