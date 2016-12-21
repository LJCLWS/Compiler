#include "lexer.h"
#include "parser_.h"
#include "semantic.h"
#include <vector>
#include <iostream>

using namespace std;

int SemParser::init_parser()
{
	Sem_TempRulesStack.push(BOTH_END);
	Sem_TempRulesStack.push(NT_E);
	//Sem_TempFourQt.ttt = 0;   //四元式t1
	//token序号出队列
	Sem_temp_token = TokenListQueue.front();
	TokenListQueue.pop();
	Sem_temp_terminal = token_to_gramer(Sem_temp_token.Ch_class);

	cout << endl << endl;
	return 0;
}

int SemParser::expression_parser()
{
	int temp_rule = 0;
	int choose_way = 0;
	vector<int> temp_gramer;

	//语法分析栈出栈
	temp_rule = Sem_TempRulesStack.top();
	Sem_TempRulesStack.pop();

	if (temp_rule >0) {  //是终结符
		if (temp_rule == Sem_temp_terminal) {
		     if (Sem_temp_terminal == BOTH_END)
		    {
			cout << "syntax alnayze successful" << endl;
			return 0;//success
		    }

		    if (Sem_temp_terminal == T_I) //PUSH
		    {
				Sem_TempSem.push(Sem_temp_token.spelling);
				//语法分析栈出栈
				temp_rule = Sem_TempRulesStack.top();
				Sem_TempRulesStack.pop();
		    }
			//token序号出队列
			Sem_temp_token = TokenListQueue.front();
			TokenListQueue.pop();
			Sem_temp_terminal = token_to_gramer(Sem_temp_token.Ch_class);

			return expression_parser();
		}
		else
		{
			error.syntax_error(MATCH_ERROR);
		}
	}

	else if (temp_rule < 0) //是非终结符
	{
		 if (temp_rule >= NT_F&& temp_rule <= NT_E)  //是非终结符
		{
			if ((choose_way = LookUp(temp_rule, Sem_temp_terminal))>0)
			{
				//倒序入栈
				temp_gramer = gramer[choose_way];
				while (temp_gramer.size()) {
					Sem_TempRulesStack.push(temp_gramer.back());
					temp_gramer.pop_back();
				}
				return expression_parser();
			}

			else
			{
				return ERROR;// error;
			}
		}


		else if ((temp_rule >= GEQ_STAR) && (temp_rule <= GEQ_DIVIDE))//GEQ
		{
			if (temp_rule == GEQ_DIVIDE)Sem_TempFourQt.operation = TokenTable[T_DIVIDE].spelling;
			else Sem_TempFourQt.operation = TokenTable[temp_rule + (TK_STAR - GEQ_STAR)].spelling;

			Sem_TempFourQt.bbb = Sem_TempSem.top();
			Sem_TempSem.pop();

			Sem_TempFourQt.aaa = Sem_TempSem.top();
			Sem_TempSem.pop();

			Sem_TempFourQt.ttt += "t";
			Sem_TempSem.push(Sem_TempFourQt.ttt);

			Sem_TempQT.push(Sem_TempFourQt);

			return expression_parser();
		}
	}

	else if (temp_rule == T_NULL)return expression_parser();

}

//+- token(53,54)    
//*/ token(52,57)  
//变量、常数  token(0,3) i
// (  token(43)
// ） token(44)
int SemParser::token_to_gramer(int token)
{
	int code = 0;
	if (token == 0 || token == 3) code = T_I;
	else     code = token;

	return code;
}

int SemParser::LookUp(int stack, int queue)
{
	int choose_way;
	switch (stack)
	{
	case NT_E:
		if (queue == T_I || queue == T_LEFT)choose_way = 1;
		else
		{
			choose_way = error.syntax_error(LOOKUP_ERROR0);//error
		}
		break;
	case NT_E1:
		if (queue == T_PLUS)choose_way = 2;
		else if (queue == T_MINUS)choose_way = 3;
		else if (queue == T_RIGHT || queue == BOTH_END)choose_way = 4;
		else
		{
			choose_way = error.syntax_error(LOOKUP_ERROR1);//error
		}
		break;
	case NT_T:
		if (queue == T_I || queue == T_LEFT)choose_way = 5;
		else
		{
			choose_way = error.syntax_error(LOOKUP_ERROR2);//error
		}
		break;
	case NT_T1:
		if (queue == T_STAR)choose_way = 6;
		else if (queue == T_DIVIDE)choose_way = 7;
		else if (queue == T_PLUS || queue == T_MINUS || queue == T_RIGHT || queue == BOTH_END) choose_way = 8;
		else
		{
			choose_way = error.syntax_error(LOOKUP_ERROR3);//error
		}
		break;
	case NT_F:
		if (queue == T_I)return 9;
		else if (queue == T_LEFT)return 10;
		else
		{
			choose_way = error.syntax_error(LOOKUP_ERROR4);//error
		}
		break;
	default:
		choose_way = error.syntax_error(LOOKUP_ERROR5);//error
		break;
	}

	return choose_way;
}

void SemParser::Sem_outprint()
{
	cout << endl << "四元式如下：" << endl;
	while (Sem_TempQT.size())
	{
		FourQtType t = Sem_TempQT.front();
		Sem_TempQT.pop();
		cout << "(" << t.operation.c_str() << "," << t.aaa.c_str() << ","<< t.bbb.c_str()<< ","<< t.ttt.c_str()<<")" <<endl;
		
	} 
}

