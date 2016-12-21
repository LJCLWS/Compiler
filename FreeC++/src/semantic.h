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
	//�﷨�������ĳ�ʼ����������β��ʶ����ջ����ʼ��־��ջ
	int init_parser();
	//�﷨���������岿��
	int expression_parser();
	//��token���е�Ԫ�ض�Ӧ���ķ���ʾ���ս��
	int token_to_gramer(int token);
	//���ݸ��ķ��ս�����ս����LL(1)�������в���·��
	int LookUp(int stack, int queue);
	//��Ԫʽ�����
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
