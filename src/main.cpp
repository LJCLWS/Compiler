#include <iostream>
#include "lexer.h"

using namespace std;

int main(int argc, char ** argv)
{
    //源文件输入
//	fin = fopen(argv[1],"rb");
//	if(!fin)
//	{
//		printf("Can't find source file!\n");
//		return 0;
//	}
//
//	init();
//	getch();
//	test_lex();
//
//	cleanup();
//	fclose(fin);
//	printf("%s Analyze Success!",argv[1]);
	cout << "%d\n" << KW_break << "  " << TK_OPENPA << endl;
	return 0;
}
