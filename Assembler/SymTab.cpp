//
//	Implementation of the symbol table class.
//
#include "stdafx.h"
#include "SymTab.h"

/**/
/*
	void SymbolTable::AddSymbol(string &a_symbol, int a_loc)

	NAME
		AddSymbol - Adds a symbol to symbol table

	SYNOPSIS
		void SymbolTable::AddSymbol(string &a_symbol, int a_loc);
		a_symbol	->	The symbol to be added to the table
		a_loc		->	Location of the symbol
	
	DESCRIPTION
		Adds a symbol to the SymbolTable. 
		If it already exists, changes its address to -999 to indicate it is multiply defined

	RETURNS
		Nothing

	AUTHOR
		Vivek Pandey

	DATE
		7:00PM 11/26/2015
*/
/**/

void SymbolTable::AddSymbol(string &a_symbol, int a_loc)
{
	// If the symbol is already in the symbol table, record it as multiply defined.
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	if (st != m_symbolTable.end()) {

		st->second = multiplyDefinedSymbol;
		return;
	}
	// Or else, normally record the symbol with its location
	m_symbolTable[a_symbol] = a_loc;
}

/**/
/*
	void SymbolTable::DisplaySymbolTable()

	NAME
		DisplaySymbolTable - Displays the symbol table

	SYNOPSIS
		void SymbolTable::DisplaySymbolTable();

	DESCRIPTION
		As the name suggests, displays the symbol table on the console in below format:
		Symbol no.	->	Symbol	->	Address

	RETURNS
		Nothing

	AUTHOR
		Vivek Pandey

	DATE
		7:00PM 11/26/2015
*/
/**/

void SymbolTable::DisplaySymbolTable()
{
	map<string, int>::iterator st;
	int i = 0;

	cout << "---------SYMBOL TABLE-------------------------------------" << endl << endl;
	cout << left << setw(10) << "SYMBOL#" 
			<< setw(20) << "SYMBOL"
			<< "LOCATION" << endl;
	for (st = m_symbolTable.begin(); st != m_symbolTable.end(); st++, i++) {
		cout << left << setw(10) << i 
				<< setw(20) << st->first 
				<< st->second << endl;
	}
	cout << endl << "-------------------------------------------------------" << endl;
}

/**/
/*
	bool SymbolTable::LookupSymbol(string &a_symbol)

	NAME
		LookupSymbol - Looks up if a symbol exists in SymbolTable
	
	SYNOPSIS
		bool SymbolTable::LookupSymbol(string &a_symbol);
		a_symbol	->	The Symbol to look up

	DESCRIPTION
		Looks up if a symbol exists in the SymbolTable

	RETURNS
		True if found, false if not found

	AUTHOR
		Vivek Pandey

	DATE
		7:00PM 11/26/2015
*/
/**/

bool SymbolTable::LookupSymbol(string &a_symbol)
{
	if (m_symbolTable.find(a_symbol) == m_symbolTable.end()) {
		return false;
	}
	else { 
		return true; 
	}
}

/**/
/*
	int SymbolTable::LookupLocation(string a_symbol)

	NAME
		LookupLocation - Looks up the location of a symbol in SymbolTable

	SYNOPSIS
		int SymbolTable::LookupLocation(string a_symbol);
		a_symbol	->	The Symbol to look up

	DESCRIPTION
		Looks up the location of a symbol in SymbolTable

	RETURNS
		The location of the symbol

	AUTHOR
		Vivek Pandey

	DATE
		7:00PM 11/26/2015
*/
/**/

int SymbolTable::LookupLocation(string a_symbol) {
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	return st->second;
}