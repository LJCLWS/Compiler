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

//�﷨�������ĳ�ʼ����������β��ʶ����ջ����ʼ��־��ջ
int Sem_init_parser();
//�﷨���������岿��
int Sem_expression_parser();
//��token���е�Ԫ�ض�Ӧ���ķ���ʾ���ս��
int Sem_token_to_gramer(int token);
//���ݸ��ķ��ս�����ս����LL(1)�������в���·��
int Sem_LookUp(int stack, int queue);
//��Ԫʽ�����
void Sem_outprint();