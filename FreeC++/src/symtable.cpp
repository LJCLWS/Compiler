#include <iostream>
#include "symtable.h"


using namespace std;

bool symtable::CommonListElement_insert(TokenElementType ident,int type,int cat,int addr)
{
	TempSymbolListElement.name = ident.spelling;
	TempSymbolListElement.type = type;
	TempSymbolListElement.cat = cat;

	if (type == KW_char)address += 1;
	else if (type == KW_short)address += 2;
	else if (type == KW_int)address += 4;
	else if (type == KW_long)address += 8;
	else if (type == KW_float)address += 4;
	else if (type == KW_double)address += 4;
	else address = addr;
	TempSymbolListElement.addr = address;

	unordered_map<string, SymbolListCommon_Type>::iterator  iter;
	pair<unordered_map<string, SymbolListCommon_Type>::iterator, bool > ret;
	ret = SymbolList.insert(pair<string, SymbolListCommon_Type>(TempSymbolListElement.name, TempSymbolListElement));
	if (ret.second) oredered_SymbolList.push(TempSymbolListElement);
	return ret.second;
}

bool symtable::TempSymbolFuctionList_insert(TokenElementType ident, int type, int cat, int addr)
{

	TempSymbolFuctionElement.name = ident.spelling;
	TempSymbolFuctionElement.type = type;
	TempSymbolFuctionElement.cat = cat;
	TempSymbolFuctionElement.addr = addr;

	unordered_map<string, SymbolListFuction_Type>::iterator  iter;
	pair<unordered_map<string, SymbolListFuction_Type>::iterator, bool > ret;
	ret = TempSymbolFuctionListElement.insert(pair<string, SymbolListFuction_Type>(TempSymbolFuctionElement.name, TempSymbolFuctionElement));
	if (ret.second) oredered_TempSymbolFuctionListElement.push_back(TempSymbolFuctionElement);

	return ret.second;

}

bool symtable::SymbolFuctionList_insert()
{
	vector<SymbolListFuction_Type> empty;
	SymbolFuctionList.push_back(oredered_TempSymbolFuctionListElement);
	oredered_TempSymbolFuctionListElement.clear();
	TempSymbolFuctionListElement.clear();

	return true;
}
bool symtable::ConstElement_insert(TokenElementType ident)
{
	//ConstList.begin();
	int type;
	TempConstListElement.value = ident.spelling;
	
	//if (ident.token_code == character_constant)type = character_constant;
	//else if (ident.token_code == digit_constant)type = digit_constant;
	//else if (ident.token_code == string_literal)type = string_literal;
	//else type = type_in;
	//SymbolList[ident.spelling].type = type;

	ConstList.push_back(TempConstListElement);
	return true;
}

bool symtable::FunctionATList_insert(int level, int OFF, int arg_number, int arg_list_addr,int entry)
{
	FuctionList_Type temp;
	temp.level = level;
	temp.OFF = OFF;
	temp.argv_number = arg_number;
	temp.arg_list_addr = arg_list_addr;
	temp.entry = entry;
	FuctionATList.push_back(temp);
	return true;
}


bool symtable::ActRecordList_insert(TokenElementType ident)
{

	return true;
}

bool symtable::ArgList_insert(TokenElementType ident, int type, int cat, int addr)
{

	return true;
}
//输出符号表
void symtable::SymbolList_print(void)
{

	cout << endl << "总符号表如下：" << endl;
	while (oredered_SymbolList.size())
	{
		SymbolListCommon_Type t = oredered_SymbolList.front();
		oredered_SymbolList.pop();
		cout << SymbolList[t.name].name << "," << SymbolList[t.name].type << "," << SymbolList[t.name].cat << "," << SymbolList[t.name].addr << endl;
	}
}

void symtable::SymbolFuctionList_print(void)
{
	cout << endl << "函数表：" << endl;
		for (int i = 0; i < SymbolFuctionList.size(); i++)
		{
			vector<SymbolListFuction_Type> temp;
			temp = SymbolFuctionList[i];
				for (int j = 0; j < temp.size(); j++)
				{
					SymbolListFuction_Type t = temp[j];
					cout << t.name << "," << t.type << "," << t.cat << "," << t.addr << endl;
				}
			cout << endl;
		}    
}
void symtable::FuctionList_print(void)
{
	cout << endl << "函数属性表：" << endl;
	for (int i = 0; i <  FuctionATList.size(); i++)
		cout << FuctionATList[i].level<<","<< FuctionATList[i].OFF <<","<< FuctionATList[i].argv_number <<","
		     << FuctionATList[i].arg_list_addr <<","<< FuctionATList[i].entry << endl;
}
void symtable::ConstList_print(void)
{
	cout << endl << "常量表：" << endl;
	for (int i = 0; i < ConstList.size();i++)
		cout << ConstList[i].value.c_str() << endl;
}
void symtable::ActRecordList_print(void)
{
	cout << endl << "活动记录表：" << endl;

}

