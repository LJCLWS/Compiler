#include <iostream>
#include "error.h"

using namespace std;

int token_error(int state)
{
	switch (state)
	{
	case IN_ERROR:
		cout << "�Ƿ�����" << endl;
		return ERROR;
	case IDENTICAL_ERROR:
		cout << "�Ƿ���ʶ��" << endl;
		return ERROR;
	}
}

int syntax_error(int choose_way)
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
	case ANALYZE_ERROR:
		cout << "ANALYZE_ERROR" << endl;
		break;
	case MATCH_ERROR:
		cout << "MATCH_ERROR" << endl;
		break;
	}
	return ERROR;
}
