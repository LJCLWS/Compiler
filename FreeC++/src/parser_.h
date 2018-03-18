#pragma once

#include <stack>
#include <vector>
#include "lexer.h"
#include "error.h"
#include "symtable.h"

using namespace std;

#define IF_END -1
#define WHILE_END -2

typedef struct FourQtType
{
	string operation;
	SymbolListCommon_Type aaa;
	SymbolListCommon_Type bbb;
	SymbolListCommon_Type ttt;
}FourQtType;


class parser:public lexer 
{
public:
	parser(char *fin):lexer(fin){};
	virtual ~parser() {};

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

protected:
	vector<FourQtType> TempQT;  //��Ԫʽ��

private:
	int temp_type = 0;        //�������ű�������ʱ�����ʶ������
	TokenElementType temp_id;       //�������ű�������ʱ�����ʶ��
	TokenElementType temp_terminal; //����ս������ʱ���� 
	ExceptionClass error;        //�쳣�����

	stack<TokenElementType> TempSem;     //����ջ
	

	TokenElementType TempSem_top;
	TokenElementType TempSem_second_top;
	TokenElementType TempSem_temp_;
};
