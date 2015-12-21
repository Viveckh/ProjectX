//
// Instruction Class - Class to parse and provide information about instructions
//
#pragma once

/**/
/*
	NAME
		Instruction Class - Parses and provides information about instructions

	DESCRIPTION
		Parses the instruction and provides information on them.
		Consists information on opcodes, labels, instruction type & location of next instruction.

	AUTHOR
		Vivek Pandey

	DATE
		8:00PM 12/1/2015
*/
/**/

class Instruction {
public:
	
	// Constructor
	Instruction() { 
		m_NumOpCode = -99;		// -99 means Undefined
		m_type = ST_NULL;
		m_IsNumericOperand = false;
		m_OperandValue = 0;
	};

	// Deconstructor
	~Instruction() { };

	// Resets all the Instruction elements for fresh start
	void reset() {
		m_Label = "";
		m_OpCode = "";
		m_Operand = "";
		m_instruction = "";
		m_NumOpCode = -99;
		m_type = ST_NULL;
		m_IsNumericOperand = false;
		m_OperandValue = 0;
	}

	// Codes to indicate the type of instruction we are processing
	enum InstructionType {
		ST_NULL,
		ST_MachineLanguage, // A machine language instruction.
		ST_AssemblerInstr,  // Assembler Language instruction.
		ST_Comment,         // Comment or blank line
		ST_End              // end instruction.
	};
	 
	// Parses the Instruction.
	InstructionType ParseInstruction(string &a_buff);

	// Computes the location of the next instruction.
	int LocationNextInstruction(int a_loc);

	// To access the label
	inline string &GetLabel() {
		return m_Label;
	};

	// To access the symbolic opCode
	inline string &GetOpCode() {
		return m_OpCode;
	};

	// To access the numerical value of opCode
	inline int &GetNumOpCode() {
		return m_NumOpCode;
	};

	// To access the operand
	inline string &GetOperand() {
		return m_Operand;
	};

	// To access the numerical value of operand
	inline int &GetOperandValue() {
		return m_OperandValue;
	};

	// To determine if a label is blank.
	inline bool isLabel() {
		return !m_Label.empty();
	};

	// To determine if the operand is a numerical value or variable
	inline bool isNumericOperand() {
		return m_IsNumericOperand;
	};

private:
	// List of machine language opcodes
	vector<string> machineCodes = { "add", "sub", "mult", "div", "load",
		"store", "read", "write", "b", "bm",
		"bz", "bp", "halt" };

	// List of assembly language opcodes
	vector<string> asmCodes = { "dc", "ds", "org", "end" };

	// The elements of a instruction
	string m_Label;			// The label.
	string m_OpCode;       // The symbolic op code.
	string m_Operand;      // The operand.
	
	string m_instruction;    // The original instruction.

	// Derived values.
	int m_NumOpCode;		// The numerical value of the op code.
	InstructionType m_type;	// The type of instruction.

	bool m_IsNumericOperand;// == true if the operand is numeric.
	int m_OperandValue;		// The value of the operand if it is numeric.
};

