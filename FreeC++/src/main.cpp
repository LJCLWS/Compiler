#include <iostream>
#include <cstdlib>
#include<iterator>
#include "lexer.h"
#include "parser_.h"
#include "error.h"
#include <queue>
#include "symtable.h"
#include "object.h"

#pragma warning(disable:4996)

using namespace std;


#define PARSER_ANALYZE

int main(int argc, char ** argv)
{	
	//词法处理机
	object result(argv[1]);

	if (result.token_scanner() == EXCEPTION)return 0;
#ifdef  LEXER_OUTPRINT
	result.Lexer_output();//token序列输出
#endif

	//语法分析器

#ifdef  PARSER_ANALYZE

	try{ 
		result.translation_unit();
	}
	catch (int str)
	{
		cout << str << endl;
	}

#endif
	
	//for (int i = 0; i < 200;i++)
	//cout << result.sem_NEWT().c_str() << endl;

	result.SymbolTable.SymbolList_print();
	result.SymbolTable.FuctionListAT_print();
	result.SymbolTable.FuctionList_print();
	result.SymbolTable.ConstList_print();
	//result.SymbolTable.ActRecordList_print();

	result.init_active_inf();
	result.MainSymbolList_print();
	result.sem_outprint();
	result.writeFile();
	result.Result_Code();
	return 0;
}

