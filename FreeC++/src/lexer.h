#ifndef _LEXER_H
#define _LEXER_H

#include<cstdlib>
#include<iostream>
using namespace std;

#define getch() (ch=getc(fin))  //��Դ�ļ��ж�ȡһ���ַ�
#define is_nondigit(c) ((c >= 'a' && c <= 'z') ||(c >= 'A' && c <= 'Z') ||c == '_')  //�ж�c�Ƿ�Ϊ��ĸ(a-z,A-Z)���»���(-)
#define is_digit(c)   (c >= '0' && c <= '9')
 

int ch_to_num(char ch);
int identifier(FILE *fin);
int state_check(int state, int ch_code);
int  state_change(int state, char ch);
int search(string token);
int end_state_to_code(int state_before, string token);

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

                    // <:
                    // :>
                    // <%
                    // %>
                    // %:
                    // %:%:
};


#define KW_TOKEN_NUM  TK_HASH2+1
//��̬�����ѯ�� �����������ѯ�ؼ���������

/* ���ʴ洢�ṹ���� */
typedef struct TokenTableType
{
    int    Hashcode;					// ���ʱ���
    string spelling;					// �����ַ���
}TokenTableType;


typedef struct TokenListType
{
	int Ch_class;   //������
	int Ch_code;    //������
	string spelling;
	//struct TokenListType *next;

}TokenListType;

#endif // _LEXER_H
