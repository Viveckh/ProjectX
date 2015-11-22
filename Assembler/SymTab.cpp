//
//		Implementation of the symbol table class.
//
#include "stdafx.h"
#include "SymTab.h"

/*
NAME
	AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS
	void AddSymbol( char *a_symbol, int a_loc );

DESCRIPTION
	This function will place the symbol "a_symbol" and its location "a_loc"
	in the symbol table.
*/

void 
SymbolTable::AddSymbol(string &a_symbol, int a_loc)
{
	// If the symbol is already in the symbol table, record it as multiply defined.
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	if (st != m_symbolTable.end()) {

		st->second = multiplyDefinedSymbol;
		return;
	}
	// Record a the  location in the symbol table.
	m_symbolTable[a_symbol] = a_loc;
}

void
SymbolTable::DisplaySymbolTable()
{
	map<string, int>::iterator st;
	int i = 0;
	for (st = m_symbolTable.begin(); st != m_symbolTable.end(); st++, i++) {
		cout << i << "\t" << st->first << "\t" << st->second << endl;
	}
}

bool
SymbolTable::LookupSymbol(string &a_symbol, int &a_loc)
{
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	if (st->second == a_loc) {
		return true;
	}
	else { 
		return false; 
	}
}