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
    //源文件输入
	fin = fopen(argv[1],"rb");
	if(!fin)
	{
		printf("Can't find source file!\n");
		return 0;
	}
	
	//词法处理机
	identifier(fin);

	//Lexer_output(); //token序列输出

	//语法分析器
	//init_parser();
	//expression_parser();

	//中间代码生成
	Sem_init_parser();
	if(!Sem_expression_parser()) 
		Sem_outprint();

	return 0;
}
