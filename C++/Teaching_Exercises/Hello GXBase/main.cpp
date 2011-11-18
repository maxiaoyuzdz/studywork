#include <GXBase.h>
using namespace gxbase;

class MyWindow:public GLWindow
{
public:
	void OnDisplay()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(0,1,0);
		glRasterPos2d(-0.9f,-0.9f);
		Printf("Hellow world\n");

		SwapBuffers();
	}
};

class MyApp:public App{
	MyWindow w;
};

static MyApp helloworld;