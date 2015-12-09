#include "stdafx.h"
#include "Errors.h"

vector<string> Errors::m_ErrorMsgs;

void Errors::InitErrorReporting() {
	m_ErrorMsgs.clear();
}

void Errors::RecordError(string &a_emsg) {
	m_ErrorMsgs.push_back(a_emsg);
}

void Errors::DisplayErrors() {
	if (m_ErrorMsgs.empty()) {
		cout << "NO ERRORS FOUND!" << endl << endl;
	}
	else {
		cout << "The Following Errors were found:" << endl << endl;
		vector<string>::iterator er;
		for (er = m_ErrorMsgs.begin(); er != m_ErrorMsgs.end(); er++) {
			cout << "-> " << *er << endl;
		}
	}
}