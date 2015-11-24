#include "stdafx.h"
#include "Instruction.h"

Instruction::InstructionType Instruction::ParseInstruction(string &a_buff) {
	m_instruction = a_buff;
	istringstream input(a_buff);

	// In the following loop we will read each element from the buffer and display
	// it.  Note how we can determine if we are done.
	
	string ibuff;
	bool commentFlag = false;
	
	//This loop below counts the number of columns
	int count = 0;
	istringstream temp(a_buff);
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

	bool labelFlag = true;
	int current = 1;
	if (count != 3) {
		labelFlag = false;
	}
	
	for (; ; ) {

		// CLear what was previously in ibuff.
		ibuff = "";

		// Read the next element into ibuff.
		input >> ibuff;

		// if nothing was read, terminate.
		if (ibuff.size() == 0 || commentFlag == true) {

			//cout << "No more data" << endl;
			//cout << "label: " << m_Label << ", OpCode: " << m_OpCode << ", Operand: " << m_Operand
				//<< ", numOpCode: " << m_NumOpCode << ", operandvalue: " << m_OperandValue << endl;
			//cout << "Count of words: " << count << endl;
			return m_type;
		}

		string ibuffConverted;
		string ibuffPlainParse;

		vector<string>::iterator it;

		for (int i = 0; i < ibuff.length(); i++) {
			if (ibuff[i] == ';') {
				if (i == 0) {
					if (m_type == 0) {
						//cout << "It's a full comment" << endl;
						m_type = ST_Comment;
					}
					//cout << "label: " << m_Label << ", OpCode: " << m_OpCode << ", Operand: " << m_Operand
						//<< ", numOpCode: " << m_NumOpCode << ", operandvalue: " << m_OperandValue << endl;
					//cout << "Count of words: " << count << endl;
					return m_type;
				}
				commentFlag = true;
				break;
			}
			ibuffPlainParse += ibuff[i];
			ibuffConverted += tolower(ibuff[i]);
		}

		if ((m_OpCode.empty() && labelFlag == false) && find(machineCodes.begin(), machineCodes.end(), ibuffConverted) != machineCodes.end()) {
			//cout << ibuffConverted << " - Machine Instruction found" << endl;
			it = find(machineCodes.begin(), machineCodes.end(), ibuffConverted);
			m_OpCode = ibuffConverted;
			m_NumOpCode = distance(machineCodes.begin(), it) + 1;
			m_type = ST_MachineLanguage;
			current++;
		}
		else if ((m_OpCode.empty() && labelFlag == false) && find(asmCodes.begin(), asmCodes.end(), ibuffConverted) != asmCodes.end()) {
			//cout << ibuffConverted << " - Assembler Instruction found" << endl;
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
			if (m_OpCode.empty()) {
				m_Label = ibuffPlainParse;
			}
			else {
				m_Operand = ibuffPlainParse;
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

int Instruction::LocationNextInstruction(int a_loc) {
	if (m_OpCode == "org") {
		a_loc = m_OperandValue;
	}
	else if (m_OpCode == "ds") {
		a_loc += m_OperandValue;
	}
	else if (m_OpCode != "" && m_OpCode != "end") {
		a_loc++;
	}
	else {
		//Leave it as it is
	}

	return a_loc;
}