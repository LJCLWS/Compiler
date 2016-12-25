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

	//语法分析器的初始化，包括结尾标识符入栈和起始标志入栈
	virtual int pop_terminal();
	//把token序列的元素对应到文法表示的终结符

	//语法分析入口
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
	
	//中间代码生成（语法制导技术）
	int iteration_WH(int wh);
	int iteration_DO(int kw_do);
	int iteration_WE(int we);

	int selection_IF(int kw_if);
	int selection_EL(int kw_else);
	int selection_IE(int ie);

	int expression_PUSH(TokenElementType id); //压栈函数(把当前 i 压入语义栈)
	int expression_ASSI(int kw_assi);
	int expression_GET(int w);
	
	void set_SEM_two_top();
	TokenElementType get_SEM_temp_();
	int  sem_SEND(int TokenCode, TokenElementType b, TokenElementType c, TokenElementType t);
	TokenElementType sem_NEWT(void);
	void sem_outprint();


private:
	TokenElementType temp_terminal; //存放终结符的临时变量 
	ExceptionClass error;        //异常类对象

	FourQtType TempFourQt;     //存放四元式的临时变量
	stack<TokenElementType> TempSem;     //语义栈
	queue<FourQtType> TempQT;  //四元式区

	TokenElementType TempSem_top;
	TokenElementType TempSem_second_top;
	TokenElementType TempSem_temp_;
};
