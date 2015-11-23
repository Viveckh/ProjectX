#include "stdafx.h"

#include "SymTab.h"
#include "FileAccess.h"
#include "Instruction.h"

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
	
	string buffer;
	FileAccess faccess(argc, argv);
	
	while (faccess.GetNextLine(buffer)) {
		Instruction instruction;
		cout << buffer << endl;
		instruction.ParseInstruction(buffer);
		cout << endl;
	}
	
	system("pause");
}