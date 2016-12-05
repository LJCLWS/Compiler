#include <iostream>
#include <cstdlib>
#include<iterator>
#include "lexer.h"
#include "parser_.h"
#include <queue>

#pragma warning(disable:4996)

using namespace std;
FILE *fin = NULL;
extern queue<TokenListType> TokenListQueue;


int main(int argc, char ** argv)
{
    //Դ�ļ�����
	fin = fopen(argv[1],"rb");
	if(!fin)
	{
		printf("Can't find source file!\n");
		return 0;
	}
	
	identifier(fin);//�ʷ������

	//�﷨������
	init_parser();
	expression_parser();

	////token�������
	//while (TokenListQueue.size())
	//{
	//	TokenListType t = TokenListQueue.front();
	//	TokenListQueue.pop();
	//	cout << "<"<<t.Ch_class << "," << t.Ch_code<< ","<< t.spelling.c_str()<< ">" <<endl;
	//} 

	return 0;
}
