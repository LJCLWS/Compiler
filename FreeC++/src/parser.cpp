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
//token��ų�����
temp_terminal = TokenListQueue.front();
TokenListQueue.pop();

return temp_terminal.token_code;
}

//�ݹ��½��ӳ���

//�ݹ��½�������
int parser::translation_unit() 
{
	pop_terminal();
	external_declaration();

	if (temp_terminal.token_code == EOF)
	{
		cout << endl << "syntax alnayze successful" << endl;
		return 0;//����
	}
	else
	{
		translation_unit();
		/*error.syntax_error(WRONG_END);
		return ERROR;*/
	}
}

int parser::external_declaration()
{
	declaration();
	//����
	if (temp_terminal.token_code == TK_OPENPA)
	{
		pop_terminal();
		if (temp_terminal.token_code != TK_CLOSEPA)parameter_type_list();
		else if (temp_terminal.token_code == TK_CLOSEPA)
		{
			pop_terminal();
			if (temp_terminal.token_code == TK_BEGIN)
			{
				pop_terminal();
				block_item_list();
				if (temp_terminal.token_code == TK_END)pop_terminal();
				else throw PARSER_ERROR1;
			}
			else throw PARSER_ERROR2;
		}
		else throw PARSER_ERROR3;
	}
	//����
	else if(temp_terminal.token_code == TK_SEMICOLON|| temp_terminal.token_code == TK_COMMA|| temp_terminal.token_code == TK_ASSIGN)
	{
		declarator();
	}
	else throw PARSER_ERROR4;
	return 0;
}

int parser::declaration()
{
	if (temp_terminal.sytax_code == type_specifier)pop_terminal();
	else throw PARSER_ERROR20; //error
	if (temp_terminal.token_code == IDentifier)pop_terminal();
	else throw START_ERROR;
	return 0;
}

int parser::declarator()
{
	while (temp_terminal.token_code != TK_SEMICOLON)
	{
		switch (temp_terminal.token_code)
		{
		case TK_ASSIGN:
			pop_terminal();
			initializer();
			if (temp_terminal.token_code == TK_SEMICOLON); //;����					
			else if (temp_terminal.token_code == TK_COMMA) //,����
			{
				pop_terminal();
				if (temp_terminal.token_code == IDentifier)pop_terminal();
				else throw PARSER_ERROR5;
			}
			else throw PARSER_ERROR6;
			break;

		case TK_COMMA:
			pop_terminal();
			if (temp_terminal.token_code == IDentifier)pop_terminal();
			else throw PARSER_ERROR7;
			break;

		default:
			throw PARSER_ERROR8;
			break;
		}
	}
	pop_terminal();
}

int parser::initializer()
{
	if (temp_terminal.token_code == digit_constant || temp_terminal.token_code == character_constant
		|| temp_terminal.token_code == string_literal)
	{
		pop_terminal();
	}
	else throw PARSER_ERROR9;
	return 0;
}

int parser::parameter_type_list()
{
	declaration();
	while (temp_terminal.token_code == TK_COMMA)
	{
		pop_terminal();
		declaration();
	}
	return 0;
}

int parser::block_item_list()
{
	block_item();
	if (temp_terminal.token_code == TK_END);
	else block_item_list();
	//��û��  �о�������
	return 0;
}

int parser::block_item()
{
	if (temp_terminal.sytax_code == type_specifier)
	{
		//pop_terminal();
		declaration();
		declarator();
	}

	else
	{
		statement();
	}
	return 0;
}

int parser::statement()
{
	if (temp_terminal.token_code == TK_BEGIN)
	{
		//pop_terminal();
		compound_statement();
	}
	else if (temp_terminal.token_code == KW_if)
	{
		//pop_terminal();
		selection_statement();
	}
	else if (temp_terminal.token_code == KW_while)
	{
		//pop_terminal();
		iteration_statement();
	}
	else if (temp_terminal.token_code == KW_return)
	{
		//pop_terminal();
		jump_statement();
	}
	else
	{
		if (temp_terminal.token_code == TK_SEMICOLON)
			pop_terminal();
		else expression();	
	}
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

int parser::selection_statement()
{
	if (temp_terminal.token_code == KW_if)
	{
		pop_terminal();
		if (temp_terminal.token_code == TK_OPENPA)
		{
			pop_terminal();
			conditional_expression();
			if (temp_terminal.token_code == TK_CLOSEPA)
			{
				pop_terminal();
				statement();
				IF(KW_if);
				//pop_terminal();  //??
				if (temp_terminal.token_code == KW_else)
				{
					pop_terminal();
					statement();
					IE(KW_else);
				}
			}
			else throw PARSER_ERROR10;
		}
		else throw PARSER_ERROR11;

	}
	else throw PARSER_ERROR12;
	return 0;
}

int parser::IF(int kw_if)
{
	//�� SEND(if  SEM[m], _, _);
	//�� POP;
	return 0;
}
int parser::EL(int kw_else)
{
	//�� SEND(el  _, _, _);
	return 0;
}
int parser::IE(int ie)
{
	//�� SEND(ie  _, _, _);
	return 0;
}

int parser::iteration_statement()
{
	//while WH() (conditional - expression) DO(do) statement WE(we)
	if (temp_terminal.token_code == KW_while)
	{
		pop_terminal();
		WH(KW_while);
		if (temp_terminal.token_code == TK_OPENPA)
		{
			pop_terminal();
			conditional_expression();
			if (temp_terminal.token_code == TK_CLOSEPA)
			{
				pop_terminal();
				DO(KW_do);
				statement();
                WE(KW_else);

			}
			else throw PARSER_ERROR13;
		}
		else throw PARSER_ERROR14;

	}
	return 0;
}

int parser::WH(int wh)
{
	//�� SEND(wh  _, _, _);
	return 0;
}
int parser::DO(int kw_do)
{
	//(1) SEND(do SEM[m], _, _);
	//��  POP;
	return 0;
}
int parser::WE(int we)
{
	//�� SEND(we  _, _, _);
	return 0;
}

int parser::jump_statement()
{
	if (temp_terminal.token_code == KW_return)
	{
		pop_terminal();
		if (temp_terminal.token_code == TK_SEMICOLON);
		else additive_expression();
	}
	else throw PARSER_ERROR15;
	return 0;
}

//�ݹ��½��ӳ���
int parser::expression()
{
	if (temp_terminal.token_code == IDentifier)
	{
		pop_terminal();
		//PUSH(IDentifier);
		if (temp_terminal.token_code == TK_ASSIGN)
		{
			pop_terminal();
			additive_expression();

			//ASSI(= );
		}
		else throw PARSER_ERROR16;
	}
	else throw PARSER_ERROR17;
	return 0;
}

int parser::conditional_expression()
{
	/*  additive - expression{ < additive - expression GET(>) }
		additive - expression{ > additive - expression GET(<) }
		additive - expression{ == additive - expression GET(== ) }
		additive - expression{ != additive - expression GET(!= ) }*/
	additive_expression();
	if (temp_terminal.token_code == TK_LT)
	{
		additive_expression();
		//GET(> );
	}
	else if (temp_terminal.token_code == TK_GT)
	{
		additive_expression();
		//GET(< );
	}
	else if (temp_terminal.token_code == TK_EQ)
	{
		additive_expression();
		//GET(== );
	}
	else if (temp_terminal.token_code == TK_NEQ)
	{
		additive_expression();
		//GET(!= );
	}
	return 0;
}

int parser::additive_expression()
{
	//multiplicative - expression{ +multiplicative - expression GET(+) }
	//multiplicative - expression{ -multiplicative - expression GET(-) }
	multiplicative_expression();
	if (temp_terminal.token_code == TK_PLUS)
	{
		pop_terminal();
		multiplicative_expression();
		//GET(+);
	}
	else if (temp_terminal.token_code == TK_MINUS)
	{
		pop_terminal();
		multiplicative_expression();
		//GET(-);
	}
	return 0;
	return 0;
}
int parser::multiplicative_expression()
{
	//unary - expression{ *unary - expression GET(*) }
	//unary - expression{ / unary - expression GET(/) }
	unary_expression();
	if (temp_terminal.token_code == TK_STAR)
	{
		pop_terminal();
		unary_expression();
		//GET(*);
	}
	else if (temp_terminal.token_code == TK_DIVIDE)
	{
		pop_terminal();
		unary_expression();
		//GET(/);
	}
	return 0;
}
int parser::unary_expression()
{
	//identifier PUSH(identifier)
	//	(additive - expression)
	if (temp_terminal.token_code == IDentifier|| temp_terminal.token_code == digit_constant)
	{
		pop_terminal();
		//PUSH(identifier);
	}
	else if (temp_terminal.token_code == TK_OPENPA)
	{
		pop_terminal();
		additive_expression();
		if (temp_terminal.token_code == TK_CLOSEPA)
		{
			pop_terminal();
		}
		else throw PARSER_ERROR18;
	}
	else throw PARSER_ERROR19;
	return 0;
}