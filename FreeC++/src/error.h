#pragma once

#define ERROR             -1

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




int token_error(int state);
int syntax_error(int error_type);
