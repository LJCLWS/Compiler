#ifndef _LEXER_H
#define _LEXER_H

#include<cstdlib>

/* �ؼ��ֱ� */
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

/* ����� *//* ��������ָ��� */
enum BS_Table
{
	TK_OPENBR=40,	// [ ��������
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

/* ���ʴ洢�ṹ���� */
typedef struct TkWord
{
    int    Hashcode;					// ���ʱ���
    //struct TkWord *next;			// ָ���ϣ��ͻ����������
    char * spelling;					// �����ַ���
}TkWord;

#endif // _LEXER_H
