//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"

// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
Assembler::Assembler(int argc, char *argv[])
	: m_faccess(argc, argv)
{
	// Nothing else to do here.
}

// Destructor currently does nothing.  You might need to add something.
Assembler::~Assembler()
{
}

// Pass I establishes the location of the labels.  You will do a better function comments.
void Assembler::PassI()
{
	int loc = 0;        // Tracks the location of the instructions to be generated.

						// Successively process each line of source code.
	for (; ; ) {
		m_inst.reset();
		// Read the next line from the source file.
		string buff;
		if (!m_faccess.GetNextLine(buff)) {

			// If there are no more lines, we are missing an end statement.
			// We will let this error be reported by Pass II.
			return;
		}
	
		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// If this is an end statement, there is nothing left to do in pass I.
		// Pass II will determine if the end is the last statement.
		if (st == Instruction::ST_End) return;

		// Labels can only be on machine language and assembler language
		// instructions.
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr) continue;

		// If the instruction has a label, record it and its location in the
		// symbol table.
		if (m_inst.isLabel()) {

			m_symtab.AddSymbol(m_inst.GetLabel(), loc);
		}
		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
}

void Assembler::PassII() {
	m_err.InitErrorReporting();
	string errorMsg;
	int loc = 0;
	int opCode, operand;
	int inst;
	m_faccess.rewind();

	cout << "---------TRANSLATION OF PROGRAM-----------------------------" << endl << endl;
	cout << "LOC\tCONTENT\t\tORIGINAL STATEMENT" << endl;
	
	for (; ; ) {	
		m_inst.reset();
		// Read the next line from the source file.
		string buff;
		if (!m_faccess.GetNextLine(buff)) {
			errorMsg = "File ended without an END statement";
			m_err.RecordError(errorMsg);
			cout << endl << "--------------------------------------------------------" << endl;
			return;
		}

		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// If this is an end statement,
		// Determine if the end is the last statement.
		if (st == Instruction::ST_End) {
			if (m_faccess.GetNextLine(buff)) {
				errorMsg = "Statements found after END opcode";
				m_err.RecordError(errorMsg);
			}
			cout << "\t\t\t" << buff << endl << endl;
			cout << endl << "--------------------------------------------------------" << endl;
			return;
		}
		
		opCode = m_inst.GetNumOpCode();
		if ((opCode < 0 || opCode > 13) && (st != Instruction::ST_Comment && buff.find_first_not_of(' ') != string::npos)) {
			errorMsg = "Illegal Opcode\r\n" + buff;
			m_err.RecordError(errorMsg);
		}

		// Labels can only be on machine language and assembler language
		// instructions.
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr) {
			cout << "\t\t\t" << buff << endl;
			continue;
		}

		cout << loc << "\t";

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

		if (m_inst.isNumericOperand()) {
			operand = m_inst.GetOperandValue();
		}
		else if (m_symtab.LookupSymbol(m_inst.GetOperand())) {
			operand = m_symtab.LookupLocation(m_inst.GetOperand());
		}
		else {
			operand = 0;
		}

		if (operand > 999999) {
			errorMsg = "Operand Value too high\r\n" + buff;
			m_err.RecordError(errorMsg);
		}

		if (operand == 0 && (m_inst.GetOpCode() != "halt" && m_inst.GetOpCode() != "end")) {
			errorMsg = "Operand value cannot be null/undefined\r\n" + buff;
			m_err.RecordError(errorMsg);
		}

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

		cout << buff << endl;
		//cout << "label : " << m_inst.GetLabel() << " opcode: " << opCode << " operand: " << operand << endl;
		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
}

