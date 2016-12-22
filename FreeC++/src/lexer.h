#ifndef _LEXER_H
#define _LEXER_H
#pragma warning(disable:4996)

#include<cstdlib>
#include<iostream>
#include <queue>
#include "error.h"

using namespace std;

#define is_nondigit(c) ((c >= 'a' && c <= 'z') ||(c >= 'A' && c <= 'Z') ||c == '_')  //判断c是否为字母(a-z,A-Z)或下划线(-)
#define is_digit(c)   (c >= '0' && c <= '9')
 
//0为标识符类码
//1为字符常数类码
//2为字符串常量类码
//3为数字常量

/* 关键字类码表 */
enum KW_Table //KeyWords
{
	KW_void=4,
	KW_char,
	KW_short,
	KW_int,
	KW_long,
	KW_float,
	KW_double,
	KW_signed,
	KW_unsigned,
	KW__Bool,
	KW__Complex,
	KW__Imaginary,

	KW_struct,
	KW_union,
	KW_enum,

	KW_typedef,
	KW_extern,
	KW_static,
	KW_auto,
	KW_register,

	KW_volatile,
    KW_const,
    KW_inline, 
    KW_return,    
    KW_sizeof,
	
	KW_restrict,

	KW_if,
	KW_else,
	KW_goto,
	KW_for,
	KW_do,
	KW_while,
	KW_continue,
    KW_switch,           
	KW_case,
	KW_break,
	KW_default,
};

/* 界符类码表 */
enum PT_Table  //Punctuators
{
	TK_OPENBR=41,	// [ 左中括号
	TK_CLOSEBR,		// ] 右中括号
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

    TK_LMAO,                // <:
    TK_MAOG,                // :>
    TK_LBAI,                // <%
    TK_BAIG,                // %>
    TK_BAIMAO,               // %:
    TK_DBAIMAO              // %:%:
};


#define KW_TOKEN_NUM  TK_DBAIMAO+1
//静态类码查询表 （根据类码查询关键字与界符）

/* 单词存储结构定义 */
typedef struct TokenTableType
{
    int    token_code;					// 单词编码
    string spelling;					// 单词字符串
}TokenTableType;


typedef struct TokenListType
{
	int token_code;   //分类码
	int sytax_code;    //语义码
	string spelling;
	//struct TokenListType *next;

}TokenListType;



class lexer {
public:
	lexer(char *argv) {
		//源文件输入
		try { 
			fin = fopen(argv, "rb"); 
			if(!fin)
			{
				throw string("Can't find source file!\n");
			}
		}
		catch (string e) {
			cout << e.c_str()<<endl;
			exit(0);
		}	
	};

	virtual ~lexer() {};

	int identifier(void);//词法分析器的主体函数
	int ch_to_num(char ch);//把识别的字符进行数字表示，返回值对应自动机的状态转换的条件

	int state_change(int sytax_code);//进行状态转换，state为当前状态，sytax_code为转换条件

	int search(string token);//查关键字表，识别是标识符还是关键字
	int end_state_to_code(int state_before, string token);//由自动机终结状态值得出对应的单词类码

	void Lexer_output(void);//词法分析器的结果输出
	void color_token(void);//对关键字高亮颜色显示

	inline void  getch() {ch = getc(fin);}  //从源文件中读取一个字符

protected:
	queue<TokenListType> TokenListQueue;
	TokenTableType TokenTable[KW_TOKEN_NUM] =
	{
		{ 0,"0" },  //标识符
		{ 1,"0" },  //字符常量
		{ 2,"0" },  //字符串常量
		{ 3,"0" },  //数字常量
		{ KW_void,"void" },
		{ KW_char,"char" },
		{ KW_short,"short" },
		{ KW_int,"int"},
		{ KW_long,"long" },
		{ KW_float,"float" },
		{ KW_double,"double" },
		{ KW_signed,"signed" },
		{ KW_unsigned,"usigned" },
		{ KW__Bool,"_Bool" },
		{ KW__Complex,"_Complex" },
		{ KW__Imaginary,"_Imaginary" },

		{ KW_struct,"struct" },
		{ KW_union,"union" },
		{ KW_enum,"enum" },
		{ KW_typedef,"typedef" },
		{ KW_volatile,"volatile" },

		{ KW_auto,"auto" },
		{ KW_const,"const" },
		{ KW_static,"static" },
		{ KW_extern,"extern" },
		{ KW_inline,"inline" },
		{ KW_return,"return" },
		{ KW_sizeof,"sizeof" },
		{ KW_register,"register" },
		{ KW_restrict,"restrict" },
		{ KW_if,"if" },
		{ KW_else,"else" },
		{ KW_goto,"goto" },
		{ KW_for,"for" },
		{ KW_do,"do" },
		{ KW_while,"while" },
		{ KW_continue,"continue" },
		{ KW_switch,"switch" },
		{ KW_case,"case" },
		{ KW_break,"break" },
		{ KW_default,"default"},

		{ TK_OPENBR,"[" },		// [ 左中括号
		{ TK_CLOSEBR,"]" },		// ] 右圆括号
		{ TK_OPENPA,"(" },		// ( 左圆括号
		{ TK_CLOSEPA,")" },		// ) 右圆括号
		{ TK_BEGIN,"{" },		// { 左大括号
		{ TK_END,"}" },			// } 右大括号
		{ TK_DOT,"." },			// . 结构体成员运算符
		{ TK_POINTSTO,"->" },	// -> 指向结构init体成员运算符

		{ TK_PLUS2,"++" },       // ++
		{ TK_MINUS2,"--" },      // --
		{ TK_AND,"&" },         // & 地址与运算符
		{ TK_STAR,"*" },		// * 乘号
		{ TK_PLUS,"+" },		// + 加号
		{ TK_MINUS,"-" },		// - 减号
		{ TK_NOT,"~" },         // ~
		{ TK_NOTEQ,"!" },       // !

		{ TK_DIVIDE,"/" },		// / 除号
		{ TK_MOD,"%" },			// % 求余运算符
		{ TK_LSHIFT,"<<" },      // <<
		{ TK_RSHIFT,">>" },      // >>
		{ TK_LT,"<" },			// < 小于号
		{ TK_GT,">" },			// > 大于号
		{ TK_LEQ,"<=" },			// <= 小于等于号
		{ TK_GEQ,">=" },			// >= 大于等于号
		{ TK_EQ,"==" },			// == 等于号
		{ TK_NEQ,"!=" },			// != 不等于号
		{ TK_SQUARE,"^" },      // ^
		{ TK_OR,"|" },          // |
		{ TK_AND2,"&&" },        // &&
		{ TK_OR2,"||" },         // ||

		{ TK_ASK,"?" },         // ?
		{ TK_COLON,":" },       // :
		{ TK_SEMICOLON,";" },	// ; 分号
		{ TK_ELLIPSIS,"..." },	// ... 省略号

		{ TK_ASSIGN,"=" },		// = 赋值运算符
		{ TK_STAREQ,"*=" },      // *=
		{ TK_DIVIDEEQ,"/=" },    // /=
		{ TK_MODEQ,"%=" },       // %=
		{ TK_PLUSEQ,"+=" },      // +=
		{ TK_MINUSEQ,"-+" },     // -=
		{ TK_LSHIFTEQ,"<<=" },    // <<=
		{ TK_RSHIFTEQ,">>=" },    // >>=
		{ TK_ANDEQ,"&=" },       // &=
		{ TK_SQUAREEQ,"^=" },    // ^=
		{ TK_OREQ,"|=" },        // |=

		{ TK_COMMA,"," },		// , 逗号
		{ TK_HASH,"#" },        // #
		{ TK_HASH2,"##" },       // ##
		{ TK_LMAO,"<:"},          // <:
		{ TK_MAOG,":>"},           // :>
		{ TK_LBAI,"<%"},          // <%
		{ TK_BAIG,"%>"},          // %>
		{ TK_BAIMAO,"%:"},        // %:
		{ TK_DBAIMAO,"%:%:"}    // %:%:
	};

private:
	char ch;
	TokenListType TempToken;
	int state=0;  //0
	int state_before=0;  //0
	int code = 0;
	string token="";
	FILE *fin;

	ExceptionClass error;

};

#endif // _LEXER_H
