#include <iostream>
#include "error.h"

using namespace std;

int token_error(int state)
{
	switch (state)
	{
	case IN_ERROR:
		cout << "非法输入" << endl;
		return ERROR;
	case IDENTICAL_ERROR:
		cout << "非法标识符" << endl;
		return ERROR;
	}
}

int syntax_error(int choose_way)
{
	switch (choose_way)
	{
	case LOOKUP_ERROR0:
		cout << endl << "LOOKUP_ERROR0" << endl;
		break;
	case LOOKUP_ERROR1:
		cout << endl << "LOOKUP_ERROR1" << endl;
		break;
	case LOOKUP_ERROR2:
		cout << endl << "LOOKUP_ERROR2" << endl;
		break;
	case LOOKUP_ERROR3:
		cout << endl << "LOOKUP_ERROR3" << endl;
		break;
	case LOOKUP_ERROR4:
		cout << endl << "LOOKUP_ERROR4" << endl;
		break;
	case LOOKUP_ERROR5:
		cout << endl << "LOOKUP_ERROR5" << endl;
		break;
	case ANALYZE_ERROR:
		cout << endl << "ANALYZE_ERROR" << endl;
		break;
	case MATCH_ERROR:
		cout << endl << "MATCH_ERROR" << endl;
		break;
	case WRONG_END:
		cout << endl << "WRONG_END" << endl;
		break;
	}
	return ERROR;
}
