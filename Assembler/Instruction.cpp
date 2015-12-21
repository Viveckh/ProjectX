//
// Implementation file for Instruction class
//

#include "stdafx.h"
#include "Instruction.h"
#include "Errors.h"

/**/
/*
	Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)

	NAME
		ParseInstruction - Parses the instruction to provide information on its components

	SYNOPSIS
		Instruction::InstructionType Instruction::ParseInstruction(string &a_buff);
		a_buff	->	the original instruction to be parsed

	DESCRIPTION
		This function goes through the given instruction and identifies the label, opcode and operand.
		It further derives the numerical value of the opcode and the operand value as well.
		In doing so, it first counts the number of columns in an instruction,
		and then performs accordingly based on whether the line has a label, has a comment, etc.
		
	RETURNS
		The instruction type. 
		Could be a ST_NULL, ST_MachineLanguage, ST_AssemblerInstr, ST_Comment or ST_End

	AUTHOR
		Vivek Pandey

	DATE
		8:00PM 12/1/2015
*/
/**/

Instruction::InstructionType Instruction::ParseInstruction(string &a_buff) {
	
	// Initializing Elements for parsing
	m_instruction = a_buff;			// The instruction line
	istringstream input(a_buff);	// Instruction loaded into a stream
	string ibuff = "";				// Temporary string for extracting info from instruction
	bool commentFlag = false;		// true indicates a comment was found in instruction
	
	// STEP 1: Count the number of columns in a given instruction
	int count = 0;				// Count for columns
	istringstream temp(a_buff); // Temporary stream
	// Examine an element at a time and see if a comment begins somewhere in between
	for (; ;) {
		ibuff = "";
		temp >> ibuff;
		if (ibuff.size() != 0) {
			if (ibuff.find_first_of(";") == string::npos) {
				count++;
			}
			else {
				if (ibuff[0] == ';') {
					break;
				}
				else {
					count++;
					break;
				}
			}
		}
		else {
			break;
		}
	}

	// STEP 2: Check if the line consists of a label
	bool labelFlag = true;	// true indicates chances exist a label might be still found in instruction
	int current = 1;		// Current element being inspected in instruction
	if (count != 3) {
		labelFlag = false;
	}
	
	// STEP 3: Parse the instruction and identify the label, opcode and operand
	for (; ; ) {

		// CLear what was previously in ibuff.
		ibuff = "";

		// Read the next element into ibuff.
		input >> ibuff;

		// if nothing was read, terminate.
		if (ibuff.size() == 0 || commentFlag == true) {
			return m_type;
		}

		string ibuffConverted = "";		// Store lowercase form
		string ibuffPlainParse = "";	

		// Check to see if the instruction is a comment, convert everything to lowercase otherwise
		for (int i = 0; i < ibuff.length(); i++) {
			if (ibuff[i] == ';') {
				if (i == 0) {
					if (m_type == 0 && m_Label == "") {
						m_type = ST_Comment;
					}
					return m_type;
				}
				commentFlag = true;
				break;
			}
			ibuffPlainParse += ibuff[i];
			ibuffConverted += tolower(ibuff[i]);
		}

		vector<string>::iterator it;
		// Check to see if the element is a machine language opcode
		if ((m_OpCode.empty() && labelFlag == false) && find(machineCodes.begin(), machineCodes.end(), ibuffConverted) != machineCodes.end()) {
			it = find(machineCodes.begin(), machineCodes.end(), ibuffConverted);
			m_OpCode = ibuffConverted;
			m_NumOpCode = distance(machineCodes.begin(), it) + 1;
			m_type = ST_MachineLanguage;
			current++;
		}
		// Check to see if the element is an assembly or end opcode
		else if ((m_OpCode.empty() && labelFlag == false) && find(asmCodes.begin(), asmCodes.end(), ibuffConverted) != asmCodes.end()) {
			m_OpCode = ibuffConverted;
			m_NumOpCode = 0;
			if (m_OpCode == "end") {
				m_type = ST_End;
			}
			else {
				m_type = ST_AssemblerInstr;
			}
			current++;
		}
		else {
			// Check to see if the element is a label
			if (m_OpCode.empty()) {
				m_Label = ibuffPlainParse;
			}
			else {
				// If nothing above is true, then the element is an operand
				m_Operand = ibuffPlainParse;

				// Get the numerical value of the operand
				if (!m_Operand.empty() && m_Operand.find_first_not_of("0123456789") == string::npos) {
					m_IsNumericOperand = true;
					m_OperandValue = atoi(m_Operand.c_str());
				}
				else {
					//Get it from the symbol table
				}
			}
			current++;
		}
		if (current != 1) labelFlag = false;
	}
}

/**/
/*
	int Instruction::LocationNextInstruction(int a_loc)

	NAME
		LocationNextInstruction - Gets the location of the next instruction

	SYNOPSIS
		int Instruction::LocationNextInstruction(int a_loc);
		a_loc	->	current instruction's location

	DESCRIPTION
		This function simply returns the memory location of the next instruction to be executed

	RETURNS
		Memory Location of the next instruction as an integer

	AUTHOR
		Vivek Pandey

	DATE
		8:00PM 12/1/2015
*/
/**/

int Instruction::LocationNextInstruction(int a_loc) {
	// In an 'org' instruction, operand value is the location of next instruction
	if (m_OpCode == "org") {
		a_loc = m_OperandValue;
	}
	// In a 'ds' instruction, operand value should be added to current location to get location of next instruction
	else if (m_OpCode == "ds") {
		a_loc += m_OperandValue;
	}
	// In any other case other than end, adding one to current location gives next location
	else if (m_OpCode != "" && m_OpCode != "end") {
		a_loc++;
	}
	else {
		//Leave it as it is
	}

	return a_loc;
}