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
#define PARSER_ANALYZE

int main(int argc, char ** argv)
{	
	//�ʷ������
	parser result= parser(argv[1]);

	if (result.token_scanner() == EXCEPTION)return 0;
#ifdef  LEXER_OUTPRINT
	result.Lexer_output();//token�������
#endif

	//�﷨������
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
	
	//�м��������
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
