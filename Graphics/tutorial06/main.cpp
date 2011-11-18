#pragma once

#include "GXBase.h"
#include "MyWindow.h"
#include "MxyWindow1.h"

using namespace gxbase;


class MyApp :public App {
public:

	//MyWindow w;
	MxyWindow1 w1;

};

// this is the single instance of our application
//
static MyApp tut6;
