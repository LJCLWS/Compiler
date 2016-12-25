#include <iostream>
#include <cstdlib>
#include<iterator>
#include "lexer.h"
#include "parser_.h"
//#include "semantic.h"
#include "error.h"
#include <queue>

#pragma warning(disable:4996)

using namespace std;

//#define LEXER_OUTPRINT
//#define PARSER_ANALYZE

int main(int argc, char ** argv)
{	
	//词法处理机
	parser result= parser(argv[1]);

	if (result.token_scanner() == EXCEPTION)return 0;
#ifdef  LEXER_OUTPRINT
	result.Lexer_output();//token序列输出
#endif

	//语法分析器
#ifndef LEXER_OUTPRINT
#ifdef  PARSER_ANALYZE

	try{ 
		result.translation_unit();
	}
	catch (int str)
	{
		cout << str << endl;
	}

#endif
#endif
	
	//中间代码生成
#ifndef LEXER_OUTPRINT
#ifndef PARSER_ANALYZE
	try {
		result.translation_unit();
	}
	catch (int str)
	{
		cout << str << endl;
		return 0;
	}
	result.sem_outprint();
#endif
#endif // !LEXER_OUTPRINT
	//for (int i = 0; i < 200;i++)
	//cout << result.sem_NEWT().c_str() << endl;

	return 0;
}
