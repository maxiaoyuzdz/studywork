#include "MxyWindow2.h"


void MxyWindow2::OnDisplay()
{
	glClearColor(1.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,0.0);
	glLineWidth(4.0f);


	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.9f, -0.9f);
	glVertex2f(+0.9f,-0.9f);
	glVertex2f(0.0f,0.9f);
	glEnd();

	SwapBuffers();


}