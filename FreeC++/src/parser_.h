#pragma once

#include <stack>
#include <queue>
#include "lexer.h"
#include "error.h"

using namespace std;

#define IF_END -1
#define WHILE_END -2


enum syntax_express {
	type_specifier = -100,
	storage_class_specifier,
	unary_operator,
	assignment_operator,

	function_name,
	var_name,
    argv_name,


};

typedef struct FourQtType
{
	string operation;
	string aaa;
	string bbb;
	string ttt;
}FourQtType;


class parser:public lexer 
{
public:
	parser(char *fin):lexer(fin){};
	~parser() {};

	//�﷨�������ĳ�ʼ����������β��ʶ����ջ����ʼ��־��ջ
	virtual int pop_terminal();
	//��token���е�Ԫ�ض�Ӧ���ķ���ʾ���ս��

	//�﷨�������
	int translation_unit();
	int external_declaration();
	int declaration();
	int declarator();
	int initializer();
	int parameter_type_list();
	int block_item_list();
	int block_item();

	int statement();
	int compound_statement();
	int selection_statement();
	int iteration_statement();
	int jump_statement();
	int expression_statement();

	int expression();
	int conditional_expression();
	int additive_expression();
	int multiplicative_expression();
	int unary_expression();
	
	//�м�������ɣ��﷨�Ƶ�������
	int iteration_WH(int wh);
	int iteration_DO(int kw_do);
	int iteration_WE(int we);

	int selection_IF(int kw_if);
	int selection_EL(int kw_else);
	int selection_IE(int ie);

	int expression_PUSH(TokenElementType id); //ѹջ����(�ѵ�ǰ i ѹ������ջ)
	int expression_ASSI(int kw_assi);
	int expression_GET(int w);
	
	void set_SEM_two_top();
	TokenElementType get_SEM_temp_();
	int  sem_SEND(int TokenCode, TokenElementType b, TokenElementType c, TokenElementType t);
	TokenElementType sem_NEWT(void);
	void sem_outprint();


private:
	TokenElementType temp_terminal; //����ս������ʱ���� 
	ExceptionClass error;        //�쳣�����

	FourQtType TempFourQt;     //�����Ԫʽ����ʱ����
	stack<TokenElementType> TempSem;     //����ջ
	queue<FourQtType> TempQT;  //��Ԫʽ��

	TokenElementType TempSem_top;
	TokenElementType TempSem_second_top;
	TokenElementType TempSem_temp_;
};
