//
// Errors Class to manage error reporting. All members are static so we can access them anywhere.
//
#pragma once

/**/
/*
	NAME
		Errors class - Manages errors found while translation

	DESCRIPTION
		Manages error reporting. All members are static so we can access them anywhere
	
	AUTHOR
		Vivek Pandey

	DATE
		6:30PM 11/25/2015
*/
/**/

class Errors {
public:
	// Initializes error reports.
	static void InitErrorReporting() {
		m_ErrorMsgs.clear();
	}

	// Records an error message.
	static void RecordError(string &a_emsg) {
		m_ErrorMsgs.push_back(a_emsg);
	}

	// Displays the collected error message.
	static void DisplayErrors();

	// Checks if the error list is empty.
	inline bool IsEmpty() {
		if (m_ErrorMsgs.empty()) { 
			return true;
		};
		return false;
	};

private:
	static vector<string> m_ErrorMsgs;	// Storage for error messages
};
