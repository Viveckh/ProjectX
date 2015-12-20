//
//	File access to source file.
//

#pragma once

/**/
/*
	NAME
		FileAccess - Accesses source file

	DESCRIPTION
		Facilitates to Read source file

	AUTHOR
		Vivek Pandey

	DATE
		8:00AM 11/17/2015
*/
/**/

class FileAccess {

public:

	// Opens the file.
	FileAccess(int argc, char *argv[]);

	// Closes the file.
	~FileAccess() {
		m_sfile.close();
	};

	// Get the next line from the source file.
	bool GetNextLine(string &a_buff);

	// Put the file pointer back to the beginning of the file.
	void rewind();

private:
	ifstream m_sfile;		// Source file object.
};
