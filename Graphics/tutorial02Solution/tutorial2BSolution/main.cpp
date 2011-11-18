#include "GXBase.h"
#include "MyWindow.h"
using namespace gxbase;

class MyApp :public App {
	MyWindow w;
};

// this is the single instance of our application
//
static MyApp tut2;
