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

//�﷨�������ĳ�ʼ����������β��ʶ����ջ����ʼ��־��ջ
int init_parser();
//�﷨���������岿��
int expression_parser();
//��token���е�Ԫ�ض�Ӧ���ķ���ʾ���ս��
int token_to_gramer(int token);
//���ݸ��ķ��ս�����ս����LL(1)�������в���·��
int LookUp(int stack, int queue);

//�ݹ��½�������
int recursive_Z();
//�ݹ��½��ӳ���
int recursive_E();
int recursive_E1();
int recursive_T();
int recursive_T1();
int recursive_F();
