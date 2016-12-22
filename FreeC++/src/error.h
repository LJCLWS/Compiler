#pragma once

#define EXCEPTION             -1
          

#define IN_ERROR          -1
#define IDENTICAL_ERROR   -2

#define ANALYZE_ERROR    0

#define LOOKUP_ERROR0   -1
#define LOOKUP_ERROR1   -2
#define LOOKUP_ERROR2   -3
#define LOOKUP_ERROR3   -4
#define LOOKUP_ERROR4   -5
#define LOOKUP_ERROR5   -6

#define MATCH_ERROR     -7

#define WRONG_END       -8

#define START_ERROR     -9
#define PARSER_ERROR1   -10
#define PARSER_ERROR2   -11
#define PARSER_ERROR3   -12
#define PARSER_ERROR4   -13
#define PARSER_ERROR5   -14
#define PARSER_ERROR6   -15
#define PARSER_ERROR7   -16
#define PARSER_ERROR8   -17
#define TK_END_MATCH_ERROR -18



class ExceptionClass
{
public:
	ExceptionClass() {};
	~ExceptionClass() {};
	int token_error(int state);
	int syntax_error(int error_type);

private:


};

