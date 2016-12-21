#include <iostream>
#include <cstdlib>
#include<iterator>
#include "lexer.h"
#include "parser_.h"
#include "semantic.h"
#include "error.h"
#include <queue>

#pragma warning(disable:4996)

using namespace std;

#define LEXER_OUTPRINT
//#define PARSER_ANALYZE

int main(int argc, char ** argv)
{	
	//词法处理机
	SemParser semparser= SemParser(argv[1]);

	if (semparser.identifier() == ERROR)return 0;
#ifdef  LEXER_OUTPRINT
	semparser.Lexer_output();//token序列输出
#endif

	//语法分析器
#ifndef LEXER_OUTPRINT
#ifdef  PARSER_ANALYZE
#ifdef  LL1
	try {
		semparser.init_parser();
		semparser.expression_parser();
	}
	catch (string str)
	{
		cout << str.c_str() << endl;
	}
#else
	try{ 
		semparser.recursive_Z();
	}
	catch (string str)
	{
		cout << str.c_str() << endl;
	}
	
#endif
#endif
#endif
	
	//中间代码生成
#ifndef LEXER_OUTPRINT
#ifndef PARSER_ANALYZE
	try {
		semparser.init_parser();
		if (!semparser.expression_parser())
			semparser.Sem_outprint();
	}
	catch (string str)
	{
		cout << str.c_str() << endl;
	}
#endif
#endif // !LEXER_OUTPRINT

	return 0;
}
