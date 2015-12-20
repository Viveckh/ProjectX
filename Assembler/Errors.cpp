//
// Implementation of Errors class
//

#include "stdafx.h"
#include "Errors.h"

// Redeclaring the static vector for storing errors
vector<string> Errors::m_ErrorMsgs;

/**/
/*
	void Errors::DisplayErrors()

	NAME
		DisplayErrors - Displays the recorded errors

	SYNOPSIS
		void Errors::DisplayErrors();

	DESCRIPTION
		Displays the errors that have been recorded during the translation
		of the assembly code

	RETURNS
		Nothing

	AUTHOR
		Vivek Pandey

	DATE
		10:00PM 11/25/2015
*/
/**/

void Errors::DisplayErrors() {
	cout << "---------ERROR LIST-------------------------------------" << endl << endl;
	if (m_ErrorMsgs.empty()) {
		cout << "NO ERRORS FOUND!" << endl << endl;
	}
	else {
		cout << "The Following Errors were found:" << endl << endl;
		vector<string>::iterator er;
		for (er = m_ErrorMsgs.begin(); er != m_ErrorMsgs.end(); er++) {
			cout << "-> " << *er << endl << endl;
		}
	}
	cout << endl << "----------------------------------------------------------" << endl;
}