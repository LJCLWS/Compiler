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
	int declaration_specifiers();
	int declarator();
	int direct_declarator();
	int parameter_type_list();
	int parameter_list();
	int parameter_declaration();
	int compound_statement();
	int block_item_list();
	int block_item();
	int declaration();
	int statement();
	int init_declarator_list();
	int init_declarator();
	int initializer();
	int labeled_statement();
	int selection_statement();
	int iteration_statement();
	int jump_statement();


	int expression();
	int assignment_expression();
	int conditional_expression();
	int logical_OR_expression();
	int logical_AND_expression();
	int inclusive_OR_expression();
	int exclusive_OR_expression();

private:
	stack<int> TempRulesStack;
	TokenListType temp_terminal;
	ExceptionClass error;

};

