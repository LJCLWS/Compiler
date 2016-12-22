#include "lexer.h"
#include "parser_.h"
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include "error.h"

using namespace std;

int parser:: pop_terminal()
{
//token序号出队列
temp_terminal = TokenListQueue.front();
TokenListQueue.pop();

return temp_terminal.token_code;
}

//递归下降子程序法

//递归下降主程序
int parser::translation_unit() 
{
	pop_terminal();
	external_declaration();

	if (temp_terminal.token_code == BOTH_END)
	{
		cout << endl << "syntax alnayze successful" << endl;
		return 0;//结束
	}
	else
	{
		external_declaration();
		/*error.syntax_error(WRONG_END);
		return ERROR;*/
	}
}

int parser::external_declaration()
{
	function_definition();
	return 0;
}

int parser::function_definition()
{
	declaration_specifiers();
	declarator();
	compound_statement();
	return 0;
}

int parser::declaration_specifiers()
{
	if(temp_terminal.sytax_code == type_specifier)pop_terminal();
	else throw START_ERROR; //error
	return 0;
}

int parser::declarator()
{
	direct_declarator();
	return 0;
}

int parser::direct_declarator()
{
	if (temp_terminal.token_code == 0)
	{
		pop_terminal();
		if (temp_terminal.token_code == TK_OPENPA)
		{
			pop_terminal();
			parameter_type_list();
		}
		else throw PARSER_ERROR2;
		if (temp_terminal.token_code == TK_CLOSEPA)
		{
			pop_terminal();
		}
		else throw PARSER_ERROR4;
	}
	else throw PARSER_ERROR1;
	return 0;
}

int parser::parameter_type_list()
{
	parameter_list();
	if (temp_terminal.token_code == TK_COMMA)
	{
		pop_terminal();
		if (temp_terminal.token_code == TK_ELLIPSIS)
		{
			pop_terminal();
		}
		else throw PARSER_ERROR3;

	}
	return 0;
}

int parser::parameter_list()
{
	parameter_declaration();
	if (temp_terminal.sytax_code == type_specifier) 
	{
		pop_terminal();
		parameter_declaration();
	}
	return 0;
}

int parser::parameter_declaration()
{
	declaration_specifiers();
	declarator();
	return 0;
}
int parser::compound_statement()
{
	if (temp_terminal.token_code == TK_BEGIN)
	{
		pop_terminal();
		if (temp_terminal.token_code == TK_END)
		{
			pop_terminal();
			return 0;
		}
		else block_item_list();
		if (temp_terminal.token_code == TK_END)
		{
			pop_terminal();
			return 0;
		}
		else throw TK_END_MATCH_ERROR;
	}
	return 0;
}

int parser::block_item_list()
{
	block_item();
	
	//还没完
	return 0;
}

int parser::block_item()
{
	if (temp_terminal.sytax_code == type_specifier)
	{
		//pop_terminal();
		declaration();
	}
	else
	{
		statement();
	}
	return 0;
}

int parser::declaration()
{
	declaration_specifiers();
	init_declarator_list();
	return 0;
}

int parser::init_declarator_list()
{
	init_declarator(); 
	//没完
	return 0;
}

int parser::init_declarator()
{
	declarator();
	if (temp_terminal.token_code == TK_ASSIGN)
	{
		pop_terminal();
		initializer();
		return 0;
	}
	return 0;
}

int parser::initializer()
{
	assignment_expression();
	return 0;
}
int parser::statement()
{
	if (temp_terminal.token_code == KW_case|| temp_terminal.token_code == KW_default)
	{
		//pop_terminal();
		labeled_statement();
	}
	else if (temp_terminal.token_code == TK_BEGIN)
	{
		//pop_terminal();
		compound_statement();
	}
	else if (temp_terminal.token_code == KW_if || temp_terminal.token_code == KW_switch)
	{
		//pop_terminal();
		selection_statement();
	}
	else if (temp_terminal.token_code == KW_while || temp_terminal.token_code == KW_do)
	{
		//pop_terminal();
		iteration_statement();
	}
	else if (temp_terminal.token_code == KW_continue || temp_terminal.token_code == KW_break || temp_terminal.token_code == KW_return)
	{
		//pop_terminal();
		jump_statement();
	}
	else
	{
		expression();
	}
	return 0;
}


int parser::labeled_statement()
{

	return 0;
}

int parser::selection_statement()
{
	return 0;
}

int parser::iteration_statement()
{
	return 0;

}

int parser::jump_statement()
{
	return 0;
}

//递归下降子程序
int parser::expression()
{
	assignment_expression();
	
	return 0;
}
int parser::assignment_expression()
{
	conditional_expression();

	return 0;
}
int parser::conditional_expression()
{

	return 0;
}
int parser::logical_OR_expression()
{

	return 0;
}
int parser::logical_AND_expression()
{

	return 0;
}
int parser::inclusive_OR_expression()
{

	return 0;
}
int parser::exclusive_OR_expression()
{

	return 0;
}