#include "stdafx.h"
#include "Assembler.h"

int main(int argc, char *argv[]) {

	SymbolTable symTable;
	/*
	SYMBOLTABLE TESTING CODE

	string Vivek = "Vivek";
	string Safal = "Safal";
	string Sujil = "Sadil";
	int temp = 109;
	symTable.AddSymbol(Vivek, 105);
	symTable.AddSymbol(Vivek, 106);


	symTable.AddSymbol(Safal, 109);
	symTable.AddSymbol(Sujil, 112);
	symTable.DisplaySymbolTable();

	if (symTable.LookupSymbol(Sujil, temp)) {
		cout << "Sujil exists" << endl;
	}
	if (symTable.LookupSymbol(Safal, temp)) {
		cout << "Safal exists in that location" << endl;
	}
	*/
	/*
	string buffer;
	FileAccess faccess(argc, argv);
	
	while (faccess.GetNextLine(buffer)) {
		Instruction instruction;
		cout << buffer << endl;
		instruction.ParseInstruction(buffer);
		cout << endl;
	}
	*/

	Assembler assem(argc, argv);

	// Establish the location of the labels:
	assem.PassI();

	// Display the symbol table.
	assem.DisplaySymbolTable();

	// Output the symbol table and the translation.
	assem.PassII();

	system("pause");
}