#pragma once

#include <stack>
#include <queue>
#include "error.h"

using namespace std;


enum syntax_express {
	type_specifier = -100,
	storage_class_specifier,
	unary_operator,
	assignment_operator,

	function_name,
	var_name,
    argv_name,


};

#define T_NULL     0
#define BOTH_END   TK_SEMICOLON

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
	int function_definition();
	int declaration();
	int declarator();
	int initializer();
	int parameter_type_list();
	int block_item_list();
	int block_item();

	int statement();
	int compound_statement();
	int expression_statement();
	int selection_statement();
	int IF(int kw_if);
	int EL(int kw_else);
	int IE(int ie);
	int iteration_statement();
	int WH(int wh);
	int DO(int kw_do);
	int WE(int we);
	int jump_statement();

	int expression();
	int assignment_expression();
	int unary_expression();
	int conditional_expression();
	int additive_expression();
	int multiplicative_expression();
	

private:
	stack<int> TempRulesStack;
	TokenListType temp_terminal;
	ExceptionClass error;

};

