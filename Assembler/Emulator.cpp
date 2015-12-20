//
// Implementation of Emulator class
//

#include "stdafx.h"
#include "Emulator.h"

/**/
/*
	bool Emulator::insertMemory(int a_location, int a_contents)

	NAME
		insertMemory - inserts a machine instruction to a memory location

	SYNOPSIS
		bool Emulator::insertMemory(int a_location, int a_contents);
		a_location	->	Memory location to be stored in
		a_contents	->	Content to be stored in the given location

	DESCRIPTION
		This short function simply puts the given machine instruction (content)
		in the given memory location of the VC3600.

	RETURNS
		True if done, false if invalid location is passed

	AUTHOR
		Vivek Pandey

	DATE
		8:10PM 12/12/2015
*/
/**/

bool Emulator::insertMemory(int a_location, int a_contents) {
	if (a_location < 0 || a_location >= MEMSZ) { return false; }
	m_memory[a_location] = a_contents;
	return true;
}

/**/
/*
	bool Emulator::runProgram()

	NAME
		runProgram - Runs the emulator

	SYNOPSIS
		bool Emulator::runProgram();

	DESCRIPTION
		Goes through each memory location of the VC3600 and
		executes the found instruction.

	RETURNS
		True if done, false if instruction can't be emulated

	AUTHOR
		Vivek Pandey

	DATE
		7:00AM 11/21/2015
*/
/**/

bool Emulator::runProgram() {
	//	Necessary components for emulation
	int opCode = 0;
	int address = 0;
	int input = 0;

	cout << "---------- EMULATOR PROGRAM----------------------------- " << endl << endl;
	for (int location = 0; location < MEMSZ; location++) {
		// If an instruction is found
		if (m_memory[location] != 0) {
			// Get the opCode and address of the current location
			opCode = m_memory[location] / 10000;
			address = m_memory[location] % 10000;
			
			switch (opCode)
			{
			case 1:
				// ADD
				m_accm = m_accm + m_memory[address];
				break;
			case 2:
				// SUBTRACT
				m_accm = m_accm - m_memory[address];
				break;
			case 3:
				// MULTIPLY
				m_accm = m_accm * m_memory[address];
				break;
			case 4:
				// DIVIDE
				m_accm = m_accm / m_memory[address];
				break;
			case 5:
				// LOAD
				m_accm = m_memory[address];
				break;
			case 6:
				// STORE
				m_memory[address] = m_accm;
				break;
			case 7:
				// READ
				cout << "? ";
				cin >> input;
				input = input % 1000000;
				m_memory[address] = input;
				break;
			case 8:
				// WRITE
				cout << m_memory[address] << endl;;
				break;
			case 9:
				// BRANCH
				location = address - 1;
				break;
			case 10:
				// BRANCH MINUS
				if (m_accm < 0) { location = address - 1; }
					break;
			case 11:
				// BRANCH ZERO
				if (m_accm == 0) { location = address - 1; }
				break;
			case 12:
				// BRANCH POSITIVE
				if (m_accm > 0) { location = address - 1; }
				break;
			case 13:
				// HALT
				location = MEMSZ;
				break;
			default:
				// IF INSTRUCTION CAN'T BE EMULATED
				return false;
			}
		}
	}
	cout << endl <<"---------END OF EMULATION-----------------------------" << endl << endl;
	return true;
}