#include <iostream>
#include <cstdlib>
#include<iterator>
#include "lexer.h"
#include "parser_.h"
#include "semantic.h"
#include <queue>

#pragma warning(disable:4996)

using namespace std;

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
	identifier(fin);

	//Lexer_output(); //token�������

	//�﷨������
	//init_parser();
	//expression_parser();

	//�м��������
	Sem_init_parser();
	if(!Sem_expression_parser()) 
		Sem_outprint();

	return 0;
}
