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
	static int is_first = 0;
	if (is_first == 0)
	{
		pop_terminal();
		is_first++;
	}
	external_declaration();

	if (temp_terminal.token_code == EOF)
	{
		cout << endl << "syntax alnayze successful" << endl;
		return 0;//结束
	}
	else
	{
		translation_unit();
	}
}

int parser::external_declaration()
{
	if (temp_terminal.token_code == KW_const)
	{
		temp_type = temp_terminal.token_code;
		pop_terminal();
		if (temp_terminal.sytax_code == type_specifier)
		{
			pop_terminal();
			if (temp_terminal.token_code == IDentifier)
			{
				temp_id = temp_terminal;

				try
				{
					//插入公共总表
					if (SymbolTable.CommonListElement_insert(temp_id,temp_type, const_value,0));
					else throw false;
				}
				catch (bool error)
				{
					if (error == false)
					{
						cout << endl << "变量重复定义" << endl;
						exit(0);
					}
					else;
				}
				
				pop_terminal();
				if (temp_terminal.token_code == TK_ASSIGN)pop_terminal();
				else throw START_ERROR;
				if (temp_terminal.token_code == digit_constant || temp_terminal.token_code == character_constant
					|| temp_terminal.token_code == string_literal)
				{
					//插入常量表
					SymbolTable.ConstElement_insert(temp_terminal);
					pop_terminal();
				}
				else throw START_ERROR;
				if (temp_terminal.token_code == TK_SEMICOLON)pop_terminal();
				else throw START_ERROR;
			}
			else throw START_ERROR;
		}
		else throw START_ERROR;
	}
	else
	{
		declaration();
		//函数
		if (temp_terminal.token_code == TK_OPENPA)
		{
			pop_terminal();
			if (temp_terminal.token_code != TK_CLOSEPA)
			{
				parameter_type_list();
				if (temp_terminal.token_code == TK_CLOSEPA)
				{
					pop_terminal();
					if (temp_terminal.token_code == TK_BEGIN)
					{
						pop_terminal();
						block_item_list();
						if (temp_terminal.token_code == TK_END)
						{
							SymbolTable.is_fuction_entry = 0;
							SymbolTable.SymbolFuctionList_insert();
							SymbolTable.FunctionATList_insert(0, 0, SymbolTable.arg_number, 0, 0);
							SymbolTable.arg_number = 0;
							pop_terminal();
						}
						else throw PARSER_ERROR1;
					}
					else throw PARSER_ERROR2;
				}
			}
			else if (temp_terminal.token_code == TK_CLOSEPA)
			{
				pop_terminal();
				if (temp_terminal.token_code == TK_BEGIN)
				{
					pop_terminal();
					block_item_list();
					if (temp_terminal.token_code == TK_END)
					{
						SymbolTable.is_fuction_entry = 0;
						pop_terminal();
					}
					else throw PARSER_ERROR1;
				}
				else throw PARSER_ERROR2;
			}
			else throw PARSER_ERROR3;
		}
		//声明
		else if (temp_terminal.token_code == TK_SEMICOLON || temp_terminal.token_code == TK_COMMA || temp_terminal.token_code == TK_ASSIGN)
		{
			declarator();
		}
		else throw PARSER_ERROR4;
	}
	return 0;
}

int parser::declaration()
{
  if (temp_terminal.sytax_code == type_specifier)
	{
			temp_type = temp_terminal.token_code;
			pop_terminal();
		if (temp_terminal.token_code == IDentifier)
		{
			temp_id = temp_terminal;
			pop_terminal();
			//插入函数值表
			if (temp_terminal.token_code == TK_OPENPA)
			{
				SymbolTable.is_fuction_entry = 1;
				SymbolTable.TempSymbolFuctionList_insert(temp_id, temp_type, function_name, 0);
				if (SymbolTable.CommonListElement_insert(temp_id, temp_type, var_name, 0));
				else throw false;
			}
			else
			{
				try
				{
					if (SymbolTable.is_fuction_entry)
					{
						if (SymbolTable.TempSymbolFuctionList_insert(temp_id, temp_type, function_name, 0));
						else throw false;
					}
					else 
					{

						//插入公共总表
						if (SymbolTable.CommonListElement_insert(temp_id, temp_type, var_name, 0));
						else throw false;
					}
				}
					catch (bool error)
					{
						cout << endl << "变量重复定义" << endl;
						exit(0);
					}
			}
		}
		else throw START_ERROR;
	}
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
			if (temp_terminal.token_code == TK_SEMICOLON); //;结束					
			else if (temp_terminal.token_code == TK_COMMA) //,再来
			{
				pop_terminal();
				if (temp_terminal.token_code == IDentifier)
				{
					try
					{
						//插入公共总表
						if (SymbolTable.is_fuction_entry)
						{
							if (SymbolTable.TempSymbolFuctionList_insert(temp_terminal, temp_type, var_name, temp_type));
							else throw false;
						}
						else
						{
							if (SymbolTable.CommonListElement_insert(temp_terminal, temp_type, var_name, temp_type));
							else throw false;
						}
					}
					catch (bool error)
					{
						cout << endl << "变量重复定义"<< endl;
						exit(0);
					}

					pop_terminal();
				}
				else throw PARSER_ERROR5;
			}
			else throw PARSER_ERROR6;
			break;

		case TK_COMMA:
			pop_terminal();
			if (temp_terminal.token_code == IDentifier)
			{
				try
				{
					if(SymbolTable.CommonListElement_insert(temp_terminal, temp_type, var_name, temp_type));
					else throw false;
				}
				catch (bool error)
				{
					cout << endl << "变量重复定义：" << endl;
					exit(0);
				}
				pop_terminal();
			}
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
		temp_id = temp_terminal;
		pop_terminal();
	}
	else throw PARSER_ERROR9;
	return 0;
}

int parser::parameter_type_list()
{
	declaration();
	SymbolTable.arg_number++;  //参数个数计数
	while (temp_terminal.token_code == TK_COMMA)
	{
		pop_terminal();
		declaration();
		SymbolTable.arg_number++;
	}
	return 0;
}

int parser::block_item_list()
{
	block_item();
	if (temp_terminal.token_code == TK_END);
	else block_item_list();
	//还没完  感觉有问题
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
		else expression_statement();	
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
				selection_IF(KW_if);
				statement();
				//pop_terminal();  //??
				if (temp_terminal.token_code == KW_else)
				{
					pop_terminal();
					selection_EL(KW_else);
					statement();
					selection_IE(IF_END);
				}
			}
			else throw PARSER_ERROR10;
		}
		else throw PARSER_ERROR11;

	}
	else throw PARSER_ERROR12;
	return 0;
}


int parser::iteration_statement()
{
	//while WH() (conditional - expression) DO(do) statement WE(we)
	if (temp_terminal.token_code == KW_while)
	{
		pop_terminal();
		iteration_WH(KW_while);
		if (temp_terminal.token_code == TK_OPENPA)
		{
			pop_terminal();
			conditional_expression();
			if (temp_terminal.token_code == TK_CLOSEPA)
			{
				pop_terminal();
				iteration_DO(KW_do);
				statement();
				iteration_WE(WHILE_END);

			}
			else throw PARSER_ERROR13;
		}
		else throw PARSER_ERROR14;

	}
	return 0;
}


int parser::jump_statement()
{
	if (temp_terminal.token_code == KW_return)
	{
		pop_terminal();
		if (temp_terminal.token_code == TK_SEMICOLON);
		else additive_expression();
		if (temp_terminal.token_code == TK_SEMICOLON)pop_terminal();
		else throw PARSER_ERROR15;
	}
	else throw PARSER_ERROR15;
	return 0;
}

int parser::expression_statement()
{
	if (temp_terminal.token_code == TK_SEMICOLON)pop_terminal();
	else
	{
		expression();
		if (temp_terminal.token_code == TK_SEMICOLON)pop_terminal();
		else throw PARSER_ERROR15;
	}
	return 0;
}
//递归下降子程序
int parser::expression()
{
	if (temp_terminal.token_code == IDentifier)
	{
		//PUSH(IDentifier);
		expression_PUSH(temp_terminal);
		pop_terminal();
		if (temp_terminal.token_code == TK_ASSIGN)
		{
			pop_terminal();
			additive_expression();
			
			//ASSI(= );
			expression_ASSI(TK_ASSIGN);
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
		//GET(< );
		expression_GET(TK_LT);
	}
	else if (temp_terminal.token_code == TK_GT)
	{
		additive_expression();
		//GET(> );
		expression_GET(TK_GT);
	}
	else if (temp_terminal.token_code == TK_EQ)
	{
		additive_expression();
		//GET(== );
		expression_GET(TK_EQ);
	}
	else if (temp_terminal.token_code == TK_NEQ)
	{
		additive_expression();
		//GET(!= );
		expression_GET(TK_NEQ);
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
		expression_GET(TK_PLUS);
	}
	else if (temp_terminal.token_code == TK_MINUS)
	{
		pop_terminal();
		multiplicative_expression();
		//GET(-);
		expression_GET(TK_MINUS);
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
		expression_GET(TK_STAR);
	}
	else if (temp_terminal.token_code == TK_DIVIDE)
	{
		pop_terminal();
		unary_expression();
		expression_GET(TK_DIVIDE);
	}
	return 0;
}
int parser::unary_expression()
{
	if (temp_terminal.token_code == IDentifier|| temp_terminal.token_code == digit_constant)
	{
		expression_PUSH(temp_terminal);
		pop_terminal();
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


int parser::iteration_WH(int wh)
{
	//⑴ SEND(wh  _, _, _);
	sem_SEND(wh, get_SEM_temp_(), get_SEM_temp_(), get_SEM_temp_());
	return 0;
}
int parser::iteration_DO(int kw_do)
{
	//(1) SEND(do SEM[m], _, _);
	sem_SEND(kw_do, TempSem.top(), get_SEM_temp_(), get_SEM_temp_());
	TempSem.pop();
	//⑵  POP;
	return 0;
}
int parser::iteration_WE(int we)
{
	//⑴ SEND(we  _, _, _);
	sem_SEND(we, get_SEM_temp_(), get_SEM_temp_(), get_SEM_temp_());
	return 0;
}

int parser::selection_IF(int kw_if)
{
	//⑴ SEND( if  SEM[m], _ , _ ); 
	sem_SEND(kw_if, TempSem.top(), get_SEM_temp_(), get_SEM_temp_());
	TempSem.pop();
	//⑵ POP;
	return 0;
}
int parser::selection_EL(int kw_else)
{
	//⑴ SEND(el  _, _, _);
	sem_SEND(kw_else, get_SEM_temp_(), get_SEM_temp_(), get_SEM_temp_());
	return 0;
}
int parser::selection_IE(int ie)
{
	//⑴ SEND(ie  _, _, _);
	sem_SEND(ie, get_SEM_temp_(), get_SEM_temp_(), get_SEM_temp_());
	return 0;
}

int parser::expression_PUSH(TokenElementType id)//压栈函数(把当前 i 压入语义栈)
{
	TempSem.push(id);
	return 0;
}
int parser::expression_ASSI(int kw_assi)
{
	//⑴ SEND(:= SEM[m], _, SEM[m - 1]);
	//⑵ POP;POP; 
	set_SEM_two_top();
	sem_SEND(kw_assi, TempSem_top, get_SEM_temp_(),TempSem_second_top);
	return 0;
}
int parser::expression_GET(int w)
{
	TokenElementType t = sem_NEWT();
	set_SEM_two_top();
	sem_SEND(w, TempSem_second_top, TempSem_top,t);
	TempSem.push(t);
	return 0;
}

void parser::set_SEM_two_top()
{
	TempSem_top=TempSem.top();
	TempSem.pop();
	TempSem_second_top=TempSem.top();
	TempSem.pop();
}

TokenElementType parser::get_SEM_temp_()
{
	TempSem_temp_.spelling = "_";
	return TempSem_temp_;
}

int parser::sem_SEND(int TokenCode, TokenElementType b, TokenElementType c, TokenElementType t)
{
	if(TokenCode>0)TempFourQt.operation = TokenTable[TokenCode].spelling;
	else if (TokenCode == IF_END)TempFourQt.operation = "if_e";
	else if (TokenCode == WHILE_END)TempFourQt.operation = "wh_e";
	else ;
	TempFourQt.aaa = b.spelling;
	TempFourQt.bbb = c.spelling;
	TempFourQt.ttt = t.spelling;

	TempQT.push(TempFourQt);

	return 0;
}

TokenElementType parser::sem_NEWT(void)
{
	//创建临时变量t1~t1000
	static int symbol = 0;
	string temp_str = "t";
	TokenElementType temp_type;

	char chr = '0';
	chr += symbol/100;
	if(chr!='0')temp_str += chr;

	chr = '0';
	chr += (symbol-((symbol/100)*100))/10;
	if ((symbol / 100) != 0|| chr!='0')temp_str += chr;

	chr = '0';
	chr += symbol % 10;
	temp_str += chr;

	symbol++;

	temp_type.spelling = temp_str;

	return temp_type;
}

void parser::sem_outprint()
{
	cout << endl << "四元式如下：" << endl;
	while (TempQT.size())
	{
		FourQtType t = TempQT.front();
		TempQT.pop();
		cout << "(" << t.operation.c_str() << "," << t.aaa.c_str() << "," << t.bbb.c_str() << "," << t.ttt.c_str() << ")" << endl;

	}
}
