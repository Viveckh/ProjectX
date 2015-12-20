//
//	SymbolTable - Maintains a table of symbols and their corresponding addresses
//
#pragma once

/**/
/*
	NAME
		SymbolTable - Maintains a table of symbols and their addresses

	DESCRIPTION
		Maintains a table of symbols and their corresponding addresses

	AUTHOR
		Vivek Pandey

	DATE
		9:00PM 11/29/2015
*/
/**/

class SymbolTable {

public:
	// Constructor
	SymbolTable() {};

	// Destructor
	~SymbolTable() {};

	const int multiplyDefinedSymbol = -999;

	// Add a new symbol to the symbol table.
	void AddSymbol(string &a_symbol, int a_loc);

	// Display the symbol table.
	void DisplaySymbolTable();

	// Lookup a symbol in the symbol table.
	bool LookupSymbol(string &a_symbol);

	// Lookup the location of a symbol
	int LookupLocation(string a_symbol);

private:
	map<string, int> m_symbolTable;		// Symbol table
};