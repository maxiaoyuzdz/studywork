// main.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <cstdlib>
#include <stdio.h>
#include <tchar.h>
#include "ErrorManager.h"

void main(int argc, _TCHAR* argv[])
{
    try{
        throw ErrorException(1, "this is my error", __FILE__, __LINE__);
    }
    catch(ErrorException& e)
    {
		ErrorManager* Log = ErrorManager::GetErrorManager();
        Log->Create("testlog.txt");
		Log->Output("*****ERROR*****");
        Log->LogException(e);
		Log->Output("***************");
		Log->Close();
    }
}

