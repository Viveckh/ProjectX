//
// Assem.cpp : Defines the entry point for the VC3600 Assembler.
//

/**/
/*
	NAME
		Assem -Entry Point

	SYNOPSIS
		Runs the Assembler and Emulator

	DESCRIPTION
		Compiles and executes the assembly code.

		Initializes an instance of the Assembler class & parses the assembly code.
		Creates a symbol table, calculates and inserts machine instructions into memory.
		Displays error messages (if any) and finally, runs the emulator (if no errors exist).

	RETURNS
		0 when done.

	AUTHOR
		Vivek Pandey

	DATE
		9:00 AM 11/17/2015
*/
/**/

#include "stdafx.h"
#include "Assembler.h"

int main(int argc, char *argv[]) {
	//Initializes an instance of the Assembler class
	Assembler assem(argc, argv);

	// Establishes the location of the labels
	assem.PassI();

	// Displays the symbol table
	assem.DisplaySymbolTable();

	// Outputs the assembly code translation
	assem.PassII();

	// Displays Errors
	assem.DisplayErrorMessages();

	//Runs the emulator (if no errors exist)
	assem.RunEmulator();

	system("pause");
}