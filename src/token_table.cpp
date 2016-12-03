#include "lexer.h"

#define KW_TOKEN_NUM  87


static TkWord token_Table[KW_TOKEN_NUM+3]
{
    {0,"0"},
    {1,"0"},
    {2,"0"},
    {KW_auto,"auto"},
    {KW_break,"break"},
    {KW_case,"case"},
    {KW_char,"char"},
    {KW_const,"const"},
    {KW_continue,"continue"},
    {KW_default,"default"},
    {KW_do,"do"},
    {KW_double,"double"},
    {KW_else,"else"},
    {KW_enum,"enum"},
    {KW_extern,"extern"},
    {KW_float,"float"},
    {KW_for,"for"},
    {KW_goto,"goto"},
    {KW_if,"if"},
    {KW_inline,"inline"},
    {KW_int,"int"},
    {KW_long,"long"},
    {KW_register,"register"},
    {KW_restrict,"restrict"},
    {KW_return,"return"},
    {KW_short,"short"},
    {KW_signed,"signed"},
    {KW_sizeof,"sizeof"},
    {KW_static,"static"},
    {KW_struct,"struct"},
    {KW_switch,"switch"},
    {KW_typedef,"typedef"},
    {KW_union,"union"},
    {KW_unsigned,"unsigned"},
    {KW_void,"void"},
    {KW_volatile,"volatile"},
    {KW_while,"while"},
    {KW__Bool,"_Bool"},
    {KW__Complex,"_Complex"},
    {KW__Imaginary,"_Imaginary"},

    {TK_OPENBR,"["},		// [ 左中括号
	{TK_CLOSEBR,"]"},		// ] 右圆括号
	{TK_OPENPA,"("},		// ( 左圆括号
	{TK_CLOSEPA,")"},		// ) 右圆括号
	{TK_BEGIN,"{"},		// { 左大括号
	{TK_END,"}"},			// } 右大括号
	{TK_DOT,"."},			// . 结构体成员运算符
    {TK_POINTSTO,"->"},	// -> 指向结构init体成员运算符

    {TK_PLUS2,"++"},       // ++
    {TK_MINUS2,"--"},      // --
    {TK_AND,"&"},         // & 地址与运算符
    {TK_STAR,"*"},		// * 乘号
	{TK_PLUS,"+"},		// + 加号
    {TK_MINUS,"-"},		// - 减号
    {TK_NOT,"~"},         // ~
    {TK_NOTEQ,"!"},       // !

    {TK_DIVIDE,"/"},		// / 除号
    {TK_MOD,"%"},			// % 求余运算符
    {TK_LSHIFT,"<<"},      // <<
    {TK_RSHIFT,">>"},      // >>
    {TK_LT,"<"},			// < 小于号
    {TK_GT,">"},			// > 大于号
    {TK_LEQ,"<="},			// <= 小于等于号
    {TK_GEQ,">="},			// >= 大于等于号
    {TK_EQ,"=="},			// == 等于号
    {TK_NEQ,"!="},			// != 不等于号
    {TK_SQUARE,"^"},      // ^
    {TK_OR,"|"},          // |
    {TK_AND2,"&&"},        // &&
    {TK_OR2,"||"},         // ||

    {TK_ASK,"?"},         // ?
    {TK_COLON,":"},       // :
    {TK_SEMICOLON,";"},	// ; 分号
    {TK_ELLIPSIS,"..."},	// ... 省略号

    {TK_ASSIGN,"="},		// = 赋值运算符
    {TK_STAREQ,"*="},      // *=
    {TK_DIVIDEEQ,"/="},    // /=
    {TK_MODEQ,"%="},       // %=
    {TK_PLUSEQ,"+="},      // +=
    {TK_MINUSEQ,"-+"},     // -=
    {TK_LSHIFTEQ,"<<="},    // <<=
    {TK_RSHIFTEQ,">>="},    // >>=
    {TK_ANDEQ,"&="},       // &=
    {TK_SQUAREEQ,"^="},    // ^=
    {TK_OREQ,"|="},        // |=

    {TK_COMMA,","},		// , 逗号
    {TK_HASH,"#"},        // #
    {TK_HASH2,"##"},       // ##

} ;
//static TKWord CS_Table[8] ;
