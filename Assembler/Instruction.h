//
// Class to parse and provide information about instructions
//
#pragma once

// The elements of an instruction.
class Instruction {

public:

	Instruction() { 
		m_NumOpCode = -99;
		m_type = ST_NULL;
		m_IsNumericOperand = false;
		m_OperandValue = 0;
	};
	~Instruction() { };

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

	// Codes to indicate the type of instruction we are processing.  Why is this inside the
	// class?
	enum InstructionType {
		ST_NULL,
		ST_MachineLanguage, // A machine language instruction.
		ST_AssemblerInstr,  // Assembler Language instruction.
		ST_Comment,          // Comment or blank line
		ST_End                    // end instruction.
	};
	 
	// Parse the Instruction.
	InstructionType ParseInstruction(string &a_buff);

	// Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc);

	// To access the label
	inline string &GetLabel() {
		return m_Label;
	};

	inline string &GetOpCode() {
		return m_OpCode;
	};

	inline int &GetNumOpCode() {
		return m_NumOpCode;
	};

	inline string &GetOperand() {
		return m_Operand;
	};

	inline int &GetOperandValue() {
		return m_OperandValue;
	};

	// To determine if a label is blank.
	inline bool isLabel() {
		return !m_Label.empty();
	};

	inline bool isNumericOperand() {
		return m_IsNumericOperand;
	};


private:
	vector<string> machineCodes = { "add", "sub", "mult", "div", "load",
		"store", "read", "write", "b", "bm",
		"bz", "bp", "halt" };

	vector<string> asmCodes = { "dc", "ds", "org", "end" };

	// The elements of a instruction
	string m_Label;            // The label.
	string m_OpCode;       // The symbolic op code.
	string m_Operand;      // The operand.
	
	string m_instruction;    // The original instruction.

							 // Derived values.
	int m_NumOpCode;     // The numerical value of the op code.
	InstructionType m_type; // The type of instruction.

	bool m_IsNumericOperand;// == true if the operand is numeric.
	int m_OperandValue;   // The value of the operand if it is numeric.
};

