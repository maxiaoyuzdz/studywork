#pragma once
#include <Windows.h>

#ifdef _WINDLL
#define DLL_OUTPUT dllexport
#else
#define DLL_OUTPUT dllimport
#endif

class SayHello
{
public:
	__declspec(DLL_OUTPUT) SayHello(void);
	__declspec(DLL_OUTPUT) ~SayHello(void);

	void __declspec(DLL_OUTPUT) DisplayHelloMessage() const;
};

