//
//	Emulator class - supports the emulation of VC3600 programs
//
#pragma once

/**/
/*
	NAME
		Emulator class - emulates the VC3600 Programs

	DESCRIPTION
		Supports the emulation of VC3600 Programs

	AUTHOR
		Vivek Pandey

	DATE
		7:00AM 11/21/2015
*/
/**/

class Emulator {
public:
	const static int MEMSZ = 10000;	// The size of the memory of the VC3600.
	
	// Constructor
	Emulator() {
		memset(m_memory, 0, MEMSZ * sizeof(int));
	}

	// Records instructions and data into VC3600 memory.
	bool insertMemory(int a_location, int a_contents);

	// Runs the VC3600 program recorded in memory.
	bool runProgram();

private:
	int m_memory[MEMSZ];	// The memory of the VC3600
	int m_accm = 0;				// Accumulator
};