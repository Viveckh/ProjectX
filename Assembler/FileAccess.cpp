//
//  Implementation of FileAccess class.
//
#include "stdafx.h"
#include "FileAccess.h"

/**/
/*
	FileAccess::FileAccess(int argc, char *argv[])

	NAME
		FileAccess Constructor - Opens the source file for reading

	SYNOPSIS
		FileAccess(int argc, char *argv[]);
		argc		-> the number of command line arguments
		argv		-> all the given command line arguments

	DESCRIPTION
		This constructor will open the file passed as command line argument for reading.
		Error message will be thrown and program terminates if the file can't be found.

	RETURNS
		Nothing

	AUTHOR
		Vivek Pandey

	DATE
		8:00PM 11/17/2015
*/
/**/

FileAccess::FileAccess(int argc, char *argv[])
{
	// Check that there is exactly one run time parameter.
	if (argc != 2) {
		cerr << "Usage: Assem <FileName>" << endl;
		exit(1);
	}

	// Open the file.
	m_sfile.open(argv[1], ios::in);

	// If the open failed, report the error and terminate.
	if (!m_sfile) {
		cerr << "Source file could not be opened, assembler terminated." << endl;
		exit(1);
	}
}

/**/
/*
	bool FileAccess::GetNextLine(string &a_buff)

	NAME
		FileAccess GetNextLine - Reads the next line from source file

	SYNOPSIS
		bool FileAccess::GetNextLine(string &a_buff);
		a_buff	-> string that will contain data read.

	DESCRIPTION
		As the name suggests, it reads the next line from file and returns a true boolean value
		if it is successful.

	RETURNS
		true if read is successful. False otherwise.

	AUTHOR
		Vivek Pandey

	DATE
		8:10PM 11/17/2015
*/
/**/

bool FileAccess::GetNextLine(string &a_buff)
{
	if (m_sfile.eof()) return false;

	getline(m_sfile, a_buff);
	return true;
}

/**/
/*
	void FileAccess::rewind()

	NAME
		Rewind - Resets the file for re-reading

	SYNOPSIS
		void FileAccess::rewind();

	DESCRIPTION
		Cleans the end of file flag and goes back to the beginning of the file.

	RETURNS
		Nothing.

	AUTHOR
		Vivek Pandey

	DATE
		8:10PM 11/17/2015
*/
/**/

void FileAccess::rewind()
{
	m_sfile.clear();
	m_sfile.seekg(0, ios::beg);
}
