#include "GXBase.h"
#include "MyWindow.h"
#include "MxyWindow.h"
using namespace gxbase;

class MyApp :public App {
	//MyWindow w;
	MxyWindow w;
};

// this is the single instance of our application
//
static MyApp tut3;
