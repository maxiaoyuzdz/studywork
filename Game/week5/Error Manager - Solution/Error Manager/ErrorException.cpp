#include "ErrorException.h"

//------------------------------------------------------------------------

//ErrorException

//------------------------------------------------------------------------

ErrorException::ErrorException() : _errorNumber(0), _lineNumber(0)
{
}

ErrorException::ErrorException(int errorNumber, const string &errorDesc, const string &srcFileName, int lineNumber) : 
							   _errorNumber(errorNumber), _errorDesc(errorDesc), _srcFileName(srcFileName), _lineNumber(lineNumber), _errText("")
{
	stringstream ErrStr;
	ErrStr << "Error Num: " << _errorNumber << "\nError Desc: " << _errorDesc << "\nSrc File: "
		<< _srcFileName << "\nLine Number: " << _lineNumber << "\n";
	_errText = ErrStr.str();
}

ErrorException::~ErrorException() throw()
{
}

//------------------------------------------------------------------------

const char* ErrorException::what()
{
	return _errText.c_str();
}