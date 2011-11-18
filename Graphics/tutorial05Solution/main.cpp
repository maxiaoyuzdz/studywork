#include "GXBase.h"
#include "MyWindow.h"

using namespace gxbase;

class MyApp :public App {
public:

	MyWindow w;

};

// this is the single instance of our application
//
static MyApp tut5;
