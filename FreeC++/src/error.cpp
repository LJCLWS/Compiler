#include <iostream>
#include "error.h"

using namespace std;

int outprint_error(int state)
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
	case LOOKUP_ERROR1:
	case LOOKUP_ERROR2:
	case LOOKUP_ERROR3:
	case LOOKUP_ERROR4:
	case LOOKUP_ERROR5:
		cout << "lookup failed" << endl;
		break;
	case ANALYZE_ERROR:
		cout << "syntax alnayze failed" << endl;
		break;
	}
	return ERROR;
}

int lookup_error(int choose_way)
{
	switch (choose_way)
	{
	case LOOKUP_ERROR0:
		cout << "LOOKUP_ERROR0" << endl;
		break;
	case LOOKUP_ERROR1:
		cout << "LOOKUP_ERROR1" << endl;
		break;
	case LOOKUP_ERROR2:
		cout << "LOOKUP_ERROR2" << endl;
		break;
	case LOOKUP_ERROR3:
		cout << "LOOKUP_ERROR3" << endl;
		break;
	case LOOKUP_ERROR4:
		cout << "LOOKUP_ERROR4" << endl;
		break;
	case LOOKUP_ERROR5:
		cout << "LOOKUP_ERROR5" << endl;
		break;
	}
	return ERROR;
}