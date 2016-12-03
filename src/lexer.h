#ifndef _LEXER_H
#define _LEXER_H

#include<cstdlib>

/* 关键字表 */
enum KW_Table
{
    KW_auto=3,
    KW_break,
    KW_case,
    KW_char,
    KW_const,
    KW_continue,
    KW_default,
    KW_do,
    KW_double,
    KW_else,
    KW_enum,
    KW_extern,
    KW_float,
    KW_for,
    KW_goto,
    KW_if,
    KW_inline,
    KW_int,
    KW_long,
    KW_register,
    KW_restrict,
    KW_return,
    KW_short,
    KW_signed,
    KW_sizeof,
    KW_static,
    KW_struct,
    KW_switch,
    KW_typedef,
    KW_union,
    KW_unsigned,
    KW_void,
    KW_volatile,
    KW_while,
    KW__Bool,
    KW__Complex,
    KW__Imaginary,
};

/* 界符表 *//* 运算符及分隔符 */
enum BS_Table
{
	TK_OPENBR=40,	// [ 左中括号
	TK_CLOSEBR,		// ] 右圆括号
	TK_OPENPA,		// ( 左圆括号
	TK_CLOSEPA,		// ) 右圆括号
	TK_BEGIN,		// { 左大括号
	TK_END,			// } 右大括号
	TK_DOT,			// . 结构体成员运算符
    TK_POINTSTO,	// -> 指向结构init体成员运算符

    TK_PLUS2,       // ++
    TK_MINUS2,      // --
    TK_AND,         // & 地址与运算符
    TK_STAR,		// * 乘号
	TK_PLUS,		// + 加号
    TK_MINUS,		// - 减号
    TK_NOT,         // ~
    TK_NOTEQ,       // !

    TK_DIVIDE,		// / 除号
    TK_MOD,			// % 求余运算符
    TK_LSHIFT,      // <<
    TK_RSHIFT,      // >>
    TK_LT,			// < 小于号
    TK_GT,			// > 大于号
    TK_LEQ,			// <= 小于等于号
    TK_GEQ,			// >= 大于等于号
    TK_EQ,			// == 等于号
    TK_NEQ,			// != 不等于号
    TK_SQUARE,      // ^
    TK_OR,          // |
    TK_AND2,        // &&
    TK_OR2,         // ||

    TK_ASK,         // ?
    TK_COLON,       // :
    TK_SEMICOLON,	// ; 分号
    TK_ELLIPSIS,	// ... 省略号

    TK_ASSIGN,		// = 赋值运算符
    TK_STAREQ,      // *=
    TK_DIVIDEEQ,    // /=
    TK_MODEQ,       // %=
    TK_PLUSEQ,      // +=
    TK_MINUSEQ,     // -=
    TK_LSHIFTEQ,    // <<=
    TK_RSHIFTEQ,    // >>=
    TK_ANDEQ,       // &=
    TK_SQUAREEQ,    // ^=
    TK_OREQ,        // |=

    TK_COMMA,		// , 逗号
    TK_HASH,        // #
    TK_HASH2,       // ##

                    // <:
                    // :>
                    // <%
                    // %>
                    // %:
                    // %:%:
};

/* 单词存储结构定义 */
typedef struct TkWord
{
    int    Hashcode;					// 单词编码
    //struct TkWord *next;			// 指向哈希冲突的其它单词
    char * spelling;					// 单词字符串
}TkWord;

#endif // _LEXER_H
