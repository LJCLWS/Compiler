#include "lexer.h"
#include <queue>
#include <cstring>
#include <iostream>
#include <windows.h>
#include "error.h"
#include <iomanip>

using namespace std;

queue<TokenListType> TokenListQueue;
static char ch;
TokenListType TempToken;
static int state=0;
int state_before = 0;
int code = 0;
static string token="";


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

	};

//�ʷ�������
int identifier(FILE *fin)
{
	    state = 1;
		
		while(!feof(fin))
		{   
			getch();
			state_before = state;
			state = state_change(state, ch_to_num(ch));
			if (state) {
				if(state>1)token += ch;// ��¼�ַ���;
				else if (state <=0) //�Ƿ�����
				{
					token_error(state);
					return ERROR;
				}
			    else cout << ch;//����ո��뻻��
			}
			else
			{				
				TempToken.Ch_class = end_state_to_code(state_before, token);
				TempToken.Ch_code = 0;
				TempToken.spelling = token;
				if(TempToken.Ch_class>=0)TokenListQueue.push(TempToken);

				color_token();

				state = 1;
				ungetc(ch, fin);
				token = "";

				//parse(code);
			}
		}

		return 0;
}


int state_change(int state, int ch_code)
{
	switch (state)
	{
	 case 1: //��ʶ��
		 if      (ch_code == 0 )state =  1;     //�ո�
		 else if (ch_code == 1 )state =  2;     //��ĸ
		 else if (ch_code == 2 )state =  3;     //����
		 else if (ch_code == 28)state =  9;     //'
		 else if (ch_code == 29)state = 11;     //"
		 else if (ch_code == 19)state =  4;     //>
		 else if (ch_code == 18)state =  5;	    //<
		 else if (ch_code == 25)state =  6;     //=
		 else if (ch_code == 5 )state = 18;    //(
		 else if (ch_code == 6 )state = 19;    //)
		 else if (ch_code == 7 )state = 20;    //{
		 else if (ch_code == 8 )state = 21;    //}
		 else if (ch_code == 26)state = 22;    //,
		 else if (ch_code == 24)state = 23;    //;
		 else if (ch_code == 3 )state = 24;    //[
		 else if (ch_code == 4 )state = 25;    //]
		 else if (ch_code == 12)state = 26;    //+
		 else if (ch_code == 13)state = 27;    //-
		 else if (ch_code == 11)state = 28;    //*
		 else if (ch_code == 16)state = 29;    // /
		 else if (ch_code == 27)state = 30;    // #
		 else if (ch_code == -1)state = -1;    //�Ƿ�����

		 else state = 0;

		 break;
	 case 2: //��ʶ��
		 if (ch_code == 1)state= 2;        //��ĸ
		 else if (ch_code == 2)state= 2;        //����
		 else
			 state= 0;
		 break;
	 case 3: //����
		 if (ch_code == 2)state= 3;         //����
		 else if (ch_code == 1)state = -2;     //error
		 else if (ch_code == 9)state= 8;         //.
		 else
			 state= 0;
		 break;
	 case 4:  //>
		 if (ch_code == 25)state = 13;
		 else state = 0;
		 break;
	 case 5:  //<
		 if (ch_code == 25)state = 14;
		 else state = 0;
		 break;
	 case 6:  //=
		 if (ch_code == 25)state = 15;
		 else state = 0;
		 break;
	 case 7:
		 if (ch_code == 2)state = 7;        //����
		 else state = 0;
		 break;
	 case 8://.
		 if (ch_code == 2)state = 7;        //����
		 else;//error
		 break;
	 case 9://'
		 if (ch_code == 1)state= 10;        //��ĸ
		 else;//error;
		 break;
	 case 10:
		 if (ch_code == 28)state= 16;       //'
		 else;//error;
		 break;
	 case 11://"
			 state= 12;
		 break;
	 case 12:
		 if (ch_code == 29)state= 17;      //"
		 else if (ch_code == 1) state = 12;   //��ĸ
		 
		 break;
	 case 13:
	 case 14:
	 case 15:
		 state = 0;
		 break;
	 case 16:
		 if (ch_code == 28)state = 0;       //'
		 else state = 0;
		 break;
	 case 17://������
		 if (ch_code == 29)state= 17;      //"
		 else state= 0;
	
		 break;
	 case 18:
	 case 19:
	 case 20:
	 case 21:
	 case 22:
	 case 23:
	 case 24:
	 case 25:
	 case 26:
	 case 27:
	 case 28:
	 case 29:
	 case 30:
		 state = 0;
		 break;

	 default:
		 state = 0;//error
		 break;

	}
	return state;
}

int search(string token)
{
	for (int i = KW_auto; i < KW__Imaginary; i++)
		if (token==TokenTable[i].spelling) return i;

	return 0;//��ʶ��
}

int end_state_to_code(int state_before, string token)
{
	switch (state_before)
	{
	case 2:
		code = search(token);
		break;
	case 3:
		code = 3;//��������
		break;
	case 4:
		code = TK_GT;
		break;
	case 5:
		code = TK_LT;
		break;
	case 6:
		code = TK_ASSIGN;
		break;
	case 7:
		code = 3;//��������
	    break;
	case 13:
		code = TK_GEQ;
		break;

	case 14:
		code = TK_LEQ;
		break;

	case 15:
		code = TK_EQ;
		break;

	case 16:
		code = 1;
		break;
	case 17:
		code = 2;
		break;

	case 18:
		code = TK_OPENPA;
		break;
	case 19:
		code = TK_CLOSEPA;
		break;
	case 20:
		code = TK_BEGIN;
		break;
	case 21:
		code = TK_END;
		break;
	case 22:
		code = TK_COMMA;
		break;
	case 23:
		code = TK_SEMICOLON;
		break;
	case 24:
		code = TK_OPENBR;
		break;
	case 25:
		code = TK_CLOSEBR;
		break;
	case 26:
		code = TK_PLUS;
		break;
	case 27:
		code = TK_MINUS;
			break;
	case 28:
		code = TK_STAR;
			break;
	case 29:
		code = TK_DIVIDE;
			break;
	case 30:
		code = TK_HASH;
		break;
	default:
		code = ERROR;//error;
		break;

	}

	return code;
}

int ch_to_num(char ch)
{
	if (is_nondigit(ch))    return 1; //��ĸ���»���
	else if (is_digit(ch))       return 2; //����
	else {
		switch (ch)
		{
		case ' ':
		case '\t':
		case '\r':
		case '\n':
			return 0; //�ո�

		case '[':return 3;
		case ']':return 4;
		case '(':return 5;
		case ')':return 6;
		case '{':return 7;
		case '}':return 8;
		case '.':return 9;
		case '&':return 10;
		case '*':return 11;
		case '+':return 12;
		case '-':return 13;
		case '~':return 14;
		case '!':return 15;
		case '/':return 16;
		case '%':return 17;
		case '<':return 18;
		case '>':return 19;
		case '^':return 20;
		case '|':return 21;
		case '?':return 22;
		case ':':return 23;
		case ';':return 24;
		case '=':return 25;
		case ',':return 26;
		case '#':return 27;

		case '\'':return 28;
		case '\"':return 29;

		default:
			if(ch!=EOF)return ERROR;//error
			else return 0;
			break;
		}
	}
}

//token�������
void Lexer_output(void)
{
	cout << endl<< "token list:" << endl;
	while (TokenListQueue.size())
	{
		static int i = 1;
		TokenListType t = TokenListQueue.front();
		TokenListQueue.pop();
		cout <<setw(4) << "<"<< t.Ch_class<< "," << t.spelling.c_str() << ">"<<"	" << right;
		if (i++ % 5 == 0)cout << endl;
	} 
	cout << endl;
}


//�ʷ���ɫ
void color_token(void)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	    if (TempToken.Ch_class == 0)     //��ʶ��
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		else if (TempToken.Ch_class == 1)  //�ַ�����
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		else if (TempToken.Ch_class == 2)  //�ַ�������
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		else if (TempToken.Ch_class == 3)  //���ֳ���
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		else if (TempToken.Ch_class <= KW__Imaginary&& TempToken.Ch_class >=KW_auto)//�ؼ���
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		else if (TempToken.Ch_class <= TK_HASH2 && TempToken.Ch_class >= TK_OPENBR)//���
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		else
			SetConsoleTextAttribute(h, FOREGROUND_RED| FOREGROUND_INTENSITY);

		cout << TempToken.spelling.c_str();
}
