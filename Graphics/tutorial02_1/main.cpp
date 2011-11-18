#include "GXBase.h"
#include "MyWindow.h"
#include "MxyWindow.h"
#include "MxyWindow2.h"
#include "MxyWindow3.h"
using namespace gxbase;

class MyApp :public App {
	//MyWindow w;
	MxyWindow3 w2;
};

// this is the single instance of our application
//
static MyApp tut2;
