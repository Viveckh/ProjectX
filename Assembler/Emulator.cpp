#include "stdafx.h"
#include "Emulator.h"

bool Emulator::insertMemory(int a_location, int a_contents) {
	if (a_location < 0 || a_location >= MEMSZ) { return false; }
	m_memory[a_location] = a_contents;
	return true;
}

bool Emulator::runProgram() {
	int opCode, address, input;

	cout << "---------- EMULATOR PROGRAM----------------------------- " << endl << endl;
	for (int location = 0; location < MEMSZ; location++) {
		if (m_memory[location] != 0) {
			opCode = m_memory[location] / 10000;
			address = m_memory[location] % 10000;
			
			switch (opCode)
			{
			case 1:
				m_accm = m_accm + m_memory[address];
				break;
			case 2:
				m_accm = m_accm - m_memory[address];
				break;
			case 3:
				m_accm = m_accm * m_memory[address];
				break;
			case 4:
				m_accm = m_accm / m_memory[address];
				break;
			case 5:
				m_accm = m_memory[address];
				break;
			case 6:
				m_memory[address] = m_accm;
				break;
			case 7:
				cout << "? ";
				cin >> input;
				input = input % 1000000;
				m_memory[address] = input;
				break;
			case 8:
				cout << m_memory[address] << endl;;
				break;
			case 9:
				location = address - 1;
				break;
			case 10:
				if (m_accm < 0) { location = address - 1; }
					break;
			case 11:
				if (m_accm == 0) { location = address - 1; }
				break;
			case 12:
				if (m_accm > 0) { location = address - 1; }
				break;
			case 13:
				location = MEMSZ;
				break;
			default:
				return false;
			}
		}
	}
	cout << endl <<"---------END OF EMULATION-----------------------------" << endl << endl;
	return true;
}