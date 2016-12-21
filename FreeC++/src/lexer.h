#ifndef _LEXER_H
#define _LEXER_H
#pragma warning(disable:4996)

#include<cstdlib>
#include<iostream>
#include <queue>
#include "error.h"

using namespace std;

#define is_nondigit(c) ((c >= 'a' && c <= 'z') ||(c >= 'A' && c <= 'Z') ||c == '_')  //�ж�c�Ƿ�Ϊ��ĸ(a-z,A-Z)���»���(-)
#define is_digit(c)   (c >= '0' && c <= '9')
 
//0Ϊ��ʶ������
//1Ϊ�ַ���������
//2Ϊ�ַ�����������
//3Ϊ���ֳ���

/* �ؼ�������� */
enum KW_Table //KeyWords
{
    KW_auto=4,
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

/* �������� */
enum PT_Table  //Punctuators
{
	TK_OPENBR=41,	// [ ��������
	TK_CLOSEBR,		// ] ��Բ����
	TK_OPENPA,		// ( ��Բ����
	TK_CLOSEPA,		// ) ��Բ����
	TK_BEGIN,		// { �������
	TK_END,			// } �Ҵ�����
	TK_DOT,			// . �ṹ���Ա�����
    TK_POINTSTO,	// -> ָ��ṹinit���Ա�����

    TK_PLUS2,       // ++
    TK_MINUS2,      // --
    TK_AND,         // & ��ַ�������
    TK_STAR,		// * �˺�
	TK_PLUS,		// + �Ӻ�
    TK_MINUS,		// - ����
    TK_NOT,         // ~
    TK_NOTEQ,       // !

    TK_DIVIDE,		// / ����
    TK_MOD,			// % ���������
    TK_LSHIFT,      // <<
    TK_RSHIFT,      // >>
    TK_LT,			// < С�ں�
    TK_GT,			// > ���ں�
    TK_LEQ,			// <= С�ڵ��ں�
    TK_GEQ,			// >= ���ڵ��ں�
    TK_EQ,			// == ���ں�
    TK_NEQ,			// != �����ں�
    TK_SQUARE,      // ^
    TK_OR,          // |
    TK_AND2,        // &&
    TK_OR2,         // ||

    TK_ASK,         // ?
    TK_COLON,       // :
    TK_SEMICOLON,	// ; �ֺ�
    TK_ELLIPSIS,	// ... ʡ�Ժ�

    TK_ASSIGN,		// = ��ֵ�����
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

    TK_COMMA,		// , ����
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
//��̬�����ѯ�� �����������ѯ�ؼ���������

/* ���ʴ洢�ṹ���� */
typedef struct TokenTableType
{
    int    Class_code;					// ���ʱ���
    string spelling;					// �����ַ���
}TokenTableType;


typedef struct TokenListType
{
	int Ch_class;   //������
	int Ch_code;    //������
	string spelling;
	//struct TokenListType *next;

}TokenListType;



class lexer {
public:
	lexer(char *argv) {
		//Դ�ļ�����
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

	int identifier(void);//�ʷ������������庯��
	int ch_to_num(char ch);//��ʶ����ַ��������ֱ�ʾ������ֵ��Ӧ�Զ�����״̬ת��������

	int state_change(int ch_code);//����״̬ת����stateΪ��ǰ״̬��ch_codeΪת������

	int search(string token);//��ؼ��ֱ�ʶ���Ǳ�ʶ�����ǹؼ���
	int end_state_to_code(int state_before, string token);//���Զ����ս�״ֵ̬�ó���Ӧ�ĵ�������

	void Lexer_output(void);//�ʷ��������Ľ�����
	void color_token(void);//�Թؼ��ָ�����ɫ��ʾ

	inline void  getch() {ch = getc(fin);}  //��Դ�ļ��ж�ȡһ���ַ�

protected:
	queue<TokenListType> TokenListQueue;
	TokenTableType TokenTable[KW_TOKEN_NUM] =
	{
		{ 0,"0" },  //��ʶ��
		{ 1,"0" },  //�ַ�����
		{ 2,"0" },  //�ַ�������
		{ 3,"0" },  //���ֳ���
		{ KW_auto,"auto" },
		{ KW_break,"break" },
		{ KW_case,"case" },
		{ KW_char,"char" },
		{ KW_const,"const" },
		{ KW_continue,"continue" },
		{ KW_default,"default" },
		{ KW_do,"do" },
		{ KW_double,"double" },
		{ KW_else,"else" },
		{ KW_enum,"enum" },
		{ KW_extern,"extern" },
		{ KW_float,"float" },
		{ KW_for,"for" },
		{ KW_goto,"goto" },
		{ KW_if,"if" },
		{ KW_inline,"inline" },
		{ KW_int,"int" },
		{ KW_long,"long" },
		{ KW_register,"register" },
		{ KW_restrict,"restrict" },
		{ KW_return,"return" },
		{ KW_short,"short" },
		{ KW_signed,"signed" },
		{ KW_sizeof,"sizeof" },
		{ KW_static,"static" },
		{ KW_struct,"struct" },
		{ KW_switch,"switch" },
		{ KW_typedef,"typedef" },
		{ KW_union,"union" },
		{ KW_unsigned,"unsigned" },
		{ KW_void,"void" },
		{ KW_volatile,"volatile" },
		{ KW_while,"while" },
		{ KW__Bool,"_Bool" },
		{ KW__Complex,"_Complex" },
		{ KW__Imaginary,"_Imaginary" },

		{ TK_OPENBR,"[" },		// [ ��������
		{ TK_CLOSEBR,"]" },		// ] ��Բ����
		{ TK_OPENPA,"(" },		// ( ��Բ����
		{ TK_CLOSEPA,")" },		// ) ��Բ����
		{ TK_BEGIN,"{" },		// { �������
		{ TK_END,"}" },			// } �Ҵ�����
		{ TK_DOT,"." },			// . �ṹ���Ա�����
		{ TK_POINTSTO,"->" },	// -> ָ��ṹinit���Ա�����

		{ TK_PLUS2,"++" },       // ++
		{ TK_MINUS2,"--" },      // --
		{ TK_AND,"&" },         // & ��ַ�������
		{ TK_STAR,"*" },		// * �˺�
		{ TK_PLUS,"+" },		// + �Ӻ�
		{ TK_MINUS,"-" },		// - ����
		{ TK_NOT,"~" },         // ~
		{ TK_NOTEQ,"!" },       // !

		{ TK_DIVIDE,"/" },		// / ����
		{ TK_MOD,"%" },			// % ���������
		{ TK_LSHIFT,"<<" },      // <<
		{ TK_RSHIFT,">>" },      // >>
		{ TK_LT,"<" },			// < С�ں�
		{ TK_GT,">" },			// > ���ں�
		{ TK_LEQ,"<=" },			// <= С�ڵ��ں�
		{ TK_GEQ,">=" },			// >= ���ڵ��ں�
		{ TK_EQ,"==" },			// == ���ں�
		{ TK_NEQ,"!=" },			// != �����ں�
		{ TK_SQUARE,"^" },      // ^
		{ TK_OR,"|" },          // |
		{ TK_AND2,"&&" },        // &&
		{ TK_OR2,"||" },         // ||

		{ TK_ASK,"?" },         // ?
		{ TK_COLON,":" },       // :
		{ TK_SEMICOLON,";" },	// ; �ֺ�
		{ TK_ELLIPSIS,"..." },	// ... ʡ�Ժ�

		{ TK_ASSIGN,"=" },		// = ��ֵ�����
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

		{ TK_COMMA,"," },		// , ����
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
