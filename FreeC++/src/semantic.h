#pragma once
#include <stack>
#include <queue>
#include "parser_.h"
#include "error.h"
using namespace std;




class semantic :public parser
{
public:
	semantic(char *fin) :parser(fin) { };
	~semantic() {};

private:
	

};
