//
// Class to manage error reporting. Note: all members are static so we can access them anywhere.
//
#ifndef _ERRORS_H
#define _ERRORS_H

//#include <string>

class Errors {

public:

	// Initializes error reports.
	static void InitErrorReporting();

	// Records an error message.
	static void RecordError(string &a_emsg);

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
	static vector<string> m_ErrorMsgs;
};
#endif
