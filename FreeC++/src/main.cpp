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


//#define LEXER_OUTPRINT
#define PARSER_ANALYZE

FILE *fin = NULL;

int main(int argc, char ** argv)
{
    //Դ�ļ�����
	fin = fopen(argv[1],"rb");
	if(!fin)
	{
		printf("Can't find source file!\n");
		return 0;
	}
	
	//�ʷ������
	if (identifier(fin) == ERROR)return 0;
#ifdef  LEXER_OUTPRINT
	Lexer_output();//token�������
#endif

	//�﷨������
#ifndef LEXER_OUTPRINT
#ifdef  PARSER_ANALYZE
#ifdef  LL1
	init_parser();
	expression_parser();
#else
	recursive_Z();
#endif
#endif
#endif
	
	//�м��������
#ifndef LEXER_OUTPRINT
#ifndef PARSER_ANALYZE
	Sem_init_parser();
	if (!Sem_expression_parser())
		Sem_outprint();
#endif
#endif // !LEXER_OUTPRINT

	

	return 0;
}
