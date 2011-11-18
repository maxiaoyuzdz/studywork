#include "GXBase.h"
#include "MyWindow.h"
#include "MxyWindow1.h"
#include "MxyWindow2.h"

using namespace gxbase;

class MyApp :public App {
private:
	//MxyWindow1 w;
	MxyWindow1 w1;
	//MxyWindow2 w2;
};

// this is the single instance of our application
//
static MyApp tut1;
