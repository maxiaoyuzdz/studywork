#pragma once

//------------------------------------------------------------------------

#include "EngineObject.h"
#include "ErrorException.h"
#include <string>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <fstream>

using namespace std;

//------------------------------------------------------------------------

//Singleton Logging Object

class ErrorManager : public EngineObject
{
public:
    static ErrorManager* GetErrorManager();
    void Create(const string& filename);
    void Close();
    void LogException(ErrorException &e);
	void Output(const char* message);

protected:
    ErrorManager();
    virtual ~ErrorManager();

private:
    void Flush();

    static ErrorManager _errorManager;
    stringstream _logBuffer;
    string getTimeString();
    ofstream _logFile;
};
