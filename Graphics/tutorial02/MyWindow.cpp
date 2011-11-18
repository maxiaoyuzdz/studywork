#include "MyWindow.h"

// this is a simple example: it creates one window,
// and draws a rotating yellow triangle inside it
void MyWindow::OnDisplay() {

	static float xpos = 0.0f, ypos = 0.0f;
	static float xinc = 0.001f;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f-xpos,0.0f,0.5f+xpos);

	xpos += xinc;

	if(xpos > 0.5f) {
		xinc = -xinc;
		xpos = 0.5f;
	};

	if(xpos < -0.5f) {
		xinc = -xinc;
		xpos = -0.5f;
	};
		
	glBegin(GL_TRIANGLES);
		glVertex2f(xpos-0.45f, ypos-0.45f);
		glVertex2f(xpos+0.45f, ypos-0.45f);
		glVertex2f(xpos,ypos+0.45f);

	glEnd();

	SwapBuffers();
}


// When nothing else is happening OnIdle() is called.  In this case, the 
// inclusion Redraw() makes sure that the window is then updated, which 
// causes OnDisplay() to be called
void MyWindow::OnIdle() {
	Redraw();
}
