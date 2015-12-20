//
//	Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"

/**/
/*
	Assembler::PassI()

	NAME
		PassI - establishes the location of the labels

	SYNOPSIS
		Assembler::PassI();

	DESCRIPTION
		Parses the assembly code and establishes the location of the labels,
		and adds the symbols with their respective addresses to the symbol table

	RETURNS
		Nothing

	AUTHOR
		Vivek Pandey

	DATE
	11:00PM 11/19/2015
*/
/**/

void Assembler::PassI()
{
	int loc = 0;	// Tracks the location of the instructions to be generated

	// Successively process each line of source code.
	for (; ; ) {
		// Read the next line from the source file.
		m_inst.reset();
		string buff;
		if (!m_faccess.GetNextLine(buff)) {
			return;
		}
	
		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// If this is an end statement, there is nothing left to do in pass I.
		if (st == Instruction::ST_End) return;

		// Skip to next line if this is not a machine or assembly instruction
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr) continue;

		// If the instruction has a label, record it and its location in the symbol table.
		if (m_inst.isLabel()) {
			m_symtab.AddSymbol(m_inst.GetLabel(), loc);
		}

		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
}

/**/
/*
	Assembler::PassII()

	NAME
		PassII -Translates the assembly code, records errors

	SYNOPSIS
		Assembler::PassII();

	DESCRIPTION
		Parses the assembly code line-by-line and generates machine language instructions,
		and records any errors it comes across while translating the code.

	RETURNS
		Nothing

	AUTHOR
		Vivek Pandey

	DATE
		11:00PM 11/19/2015
*/
/**/

void Assembler::PassII() {
	m_err.InitErrorReporting();	// Initializes the error recorder
	string errorMsg;			// temp for error message
	int loc = 0;				// location of instructions to be generated
	int opCode, operand;		// parsed opcode and operand in a line of code
	int inst;					// Resulting machine language instruction
	m_faccess.rewind();			// Resetting the file to read

	cout << "---------TRANSLATION OF PROGRAM-----------------------------" << endl << endl;
	cout << "LOC\tCONTENT\t\tORIGINAL STATEMENT" << endl;
	
	// Process a line at a time
	for (; ; ) {	
		
		// STEP 1: Read the next line from the source file.
		m_inst.reset();
		string buff;
		if (!m_faccess.GetNextLine(buff)) {
			errorMsg = "File ended without an END statement";
			m_err.RecordError(errorMsg);
			cout << endl << "--------------------------------------------------------" << endl;
			return;
		}

		// STEP 2: Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// STEP 3: If this is an end statement, determine if the end is the last statement & return
		if (st == Instruction::ST_End) {
			if (m_faccess.GetNextLine(buff)) {
				errorMsg = "Statements found after END opcode";
				m_err.RecordError(errorMsg);
			}
			cout << "\t\t\t" << buff 
				<< endl << endl;
			cout << endl << "--------------------------------------------------------" << endl;
			return;
		}
		
		// STEP 4: Check the validity of parsed opCode
		opCode = m_inst.GetNumOpCode();
		if ((opCode < 0 || opCode > 13) && (st != Instruction::ST_Comment && buff.find_first_not_of(' ') != string::npos)) {
			errorMsg = "Illegal Opcode\r\n" + buff;
			m_err.RecordError(errorMsg);
		}

		// STEP 5: Jump to next line if this is not a machine or assembly instruction
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr) {
			cout << "\t\t\t" << buff << endl;
			continue;
		}

		cout << loc << "\t";

		// STEP 6: Check the validity of the parsed label name
		if (m_inst.GetLabel() != "") {
			if (strlen(m_inst.GetLabel().c_str()) > 10) {
				errorMsg = "Too Long Labelname\r\n" + buff;
				m_err.RecordError(errorMsg);
			}
			if (!isalpha(m_inst.GetLabel()[0])) {
				errorMsg = "The first letter of the labelname " + m_inst.GetLabel() + " is not a letter\r\n" + buff;
				m_err.RecordError(errorMsg);
			}
		}

		// STEP 7: Get the parsed operand's value
		if (m_inst.isNumericOperand()) {
			operand = m_inst.GetOperandValue();
		}
		else if (m_symtab.LookupSymbol(m_inst.GetOperand())) {
			operand = m_symtab.LookupLocation(m_inst.GetOperand());
		}
		else {
			operand = 0;
		}

		// STEP 8: Check the validity of the parsed operand
		if (operand > 999999) {
			errorMsg = "Operand Value too high\r\n" + buff;
			m_err.RecordError(errorMsg);
		}
		if (operand == 0 && (m_inst.GetOpCode() != "halt" && m_inst.GetOpCode() != "end")) {
			errorMsg = "Operand value cannot be null/undefined\r\n" + buff;
			m_err.RecordError(errorMsg);
		}

		// STEP 9: Generate machine language instruction and store it in memory
		if (operand == -999) {
			errorMsg = "Multiply defined operand found at\r\n" + buff;
			m_err.RecordError(errorMsg);
		}
		else if (m_inst.GetOpCode() == "org" || m_inst.GetOpCode() == "ds") {
			cout << "\t\t";
		}
		else {
			inst = opCode * 10000;
			inst = inst + operand;
			m_emul.insertMemory(loc, inst);
			cout << right << setw(6) << setfill('0') << inst << "\t\t";
		}

		// Print the orginal line of code
		cout << buff << endl;

		// STEP 10: Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
}

