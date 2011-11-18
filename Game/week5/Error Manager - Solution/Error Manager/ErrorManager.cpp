#include "ErrorManager.h"

ErrorManager ErrorManager::_errorManager;

//------------------------------------------------------------------------

//ErrorManager

//------------------------------------------------------------------------

ErrorManager::ErrorManager()
{
}

ErrorManager::~ErrorManager()
{
}

//------------------------------------------------------------------------

ErrorManager* ErrorManager::GetErrorManager()
{
    return &_errorManager;
}

//------------------------------------------------------------------------

//Opens log file
void ErrorManager::Create(const std::string &Filename)
{
    _logFile.open(Filename.c_str());
}

//------------------------------------------------------------------------

//Commits information to file and clears text cache
void ErrorManager::Flush()
{
    _logFile << _logBuffer.str();
    _logFile.flush();
    _logBuffer.str("");
}

//------------------------------------------------------------------------

//Close log file
void ErrorManager::Close()
{
    _logFile.close();
}

//------------------------------------------------------------------------

void ErrorManager::LogException(ErrorException &e)
{
    _logFile << getTimeString() << "\n" << e.what();
    _logFile.flush();
}

//------------------------------------------------------------------------

void ErrorManager::Output(const char* message)
{
	_logBuffer << message << '\n';
	Flush();
}

//------------------------------------------------------------------------

//Gets current time as string in the form: hours:mins:secs
std::string ErrorManager::getTimeString()
{
    std::stringstream TimeStr;

    struct tm *pTime = 0;
    time_t ctTime; time(&ctTime);
    pTime = localtime( &ctTime );

    TimeStr << std::setw(2) << std::setfill('0') <<pTime->tm_hour << ":";
    TimeStr << std::setw(2) << std::setfill('0') <<pTime->tm_min << ":";
    TimeStr << std::setw(2) << std::setfill('0') <<pTime->tm_sec;

    return TimeStr.str();
}

//------------------------------------------------------------------------