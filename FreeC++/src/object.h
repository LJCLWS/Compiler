#pragma once
#include <stack>
#include <queue>
#include "parser_.h"
#include "error.h"
using namespace std;

class object :public parser
{
public:
	object(char *fin) :parser(fin) { };
	~object() {};

	//int object_CODE(string );
	//int BACK(pi, pk);
private:
	

};
