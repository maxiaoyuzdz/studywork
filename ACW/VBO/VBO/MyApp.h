#pragma once
#include "GXBase.h"
#include "MyWindow.h"
using namespace gxbase;



class MyApp :
	public App
{
public:
	MyWindow w;

	void OnCreate();
};

