#include "MyWindow.h"

// this is a simple example: it creates one window,
// and draws a yellow triangle inside it
void MyWindow::OnDisplay() {
	glClearColor(1.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,0.0);

	glBegin(GL_TRIANGLES);
		glVertex2f(-0.9f, -0.9f);
		glVertex2f(+0.9f,-0.9f);
		glVertex2f(0.0f,0.9f);
	glEnd();

	SwapBuffers();
}