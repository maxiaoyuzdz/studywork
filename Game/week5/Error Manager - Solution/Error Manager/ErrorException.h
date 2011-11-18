#pragma once

//------------------------------------------------------------------------

#include <string>
#include <sstream>
#include <iostream>
#include <exception>

using namespace std;

//------------------------------------------------------------------------

//Custom exception class

class ErrorException : public exception
{
public:
	ErrorException();
	ErrorException(int errorNumber, const string &errorDesc, const string &srcFileName, int lineNumber);
	~ErrorException() throw();

	// Override std::exception::what
	const char* what();

private:
	int _errorNumber;
	string _errorDesc;
	string _srcFileName;
	int _lineNumber;
	string _errText;
};