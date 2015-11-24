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
	cout << "SYMBOL#\tSYMBOL\tLOCATION" << endl;
	for (st = m_symbolTable.begin(); st != m_symbolTable.end(); st++, i++) {
		cout << i << "\t" << st->first << "\t" << st->second << endl;
	}
	cout << endl;
}

bool
SymbolTable::LookupSymbol(string &a_symbol)
{
	if (m_symbolTable.find(a_symbol) == m_symbolTable.end()) {
		return false;
	}
	else { 
		return true; 
	}
}

int SymbolTable::LookupLocation(string a_symbol) {
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	return st->second;
}