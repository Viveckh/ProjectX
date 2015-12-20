//
//		Assembler class - This is a container for all the components
//		that make up the assembler.
//

#pragma once 

/**/
/*
	NAME
		class Assembler

	DESCRIPTION
		This class is a container for all the components that make up the assembler.

		Capable of parsing the source file to:
			Create a symbol table with corresponding memory addresses of symbols
			Calculate machine instructions and insert those instructions into memory.
			Display error messages (if any) and finally, 
			Run the emulator (if no errors exist). 

	AUTHOR
		Vivek Pandey

	DATE
		11:30 PM 11/19/2015
*/
/**/

// Include files
#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Errors.h"
#include "Emulator.h"

class Assembler {
public:
	//Constructor
	Assembler(int argc, char *argv[]) 
		: m_faccess(argc, argv)
	{}
	
	//Destructor
	~Assembler() {}

	// Pass I - establishes the locations of the symbols
	void PassI();
	
	// Pass II - generates a translation
	void PassII();

	// Displays the symbols in the symbol table.
	void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }

	// Displays the errors.
	void DisplayErrorMessages() { m_err.DisplayErrors();  }

	// Runs emulator on the translation.
	void RunEmulator() { 
		if (m_err.IsEmpty()) { 
			m_emul.runProgram();
		}
		else {
			cout << endl <<"-----EMULATOR CANNOT BE STARTED UNTIL ERROR LIST IS EMPTY-----" << endl << endl; 
		}
	};

private:
	FileAccess m_faccess;	    // File Access object
	SymbolTable m_symtab;		// Symbol table object
	Instruction m_inst;			// Instruction object
	Errors m_err;				// Error object
	Emulator m_emul;			// Emulator
};

