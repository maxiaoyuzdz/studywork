#include "MyWindow.h"
#include <math.h>

// this is a simple example: it creates one window,
// and draws a rotating yellow triangle inside it
void MyWindow::OnDisplay() {

	static const float speed = 1.0f;
	static const float cubeSize = 0.25f;
	static const float radius = 0.75f;
	static float xpos = 0.0f, ypos = 0.0f;
	static float xinc = speed;
	static float current_time = (float)App::GetTime();
	static float angle = 0.0f;
	float delta_t, temp_time;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f-xpos,0.0f,0.5f+xpos);

	temp_time = (float)App::GetTime();
	delta_t = temp_time-current_time;
	current_time = temp_time;
		
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	xpos = radius * cosAngle;
	ypos = radius * sinAngle;
	glBegin(GL_QUADS);
		glVertex2f(xpos + (-cubeSize)*cosAngle - (-cubeSize)*sinAngle,
			       ypos + (-cubeSize)*sinAngle + (-cubeSize)*cosAngle);
		glVertex2f(xpos + (+cubeSize)*cosAngle - (-cubeSize)*sinAngle,
			       ypos + (+cubeSize)*sinAngle + (-cubeSize)*cosAngle);
		glVertex2f(xpos + (+cubeSize)*cosAngle - (+cubeSize)*sinAngle,
			       ypos + (+cubeSize)*sinAngle + (+cubeSize)*cosAngle);
		glVertex2f(xpos + (-cubeSize)*cosAngle - (+cubeSize)*sinAngle,
			       ypos + (-cubeSize)*sinAngle + (+cubeSize)*cosAngle);
	glEnd();

	SwapBuffers();

	angle += 0.5f*delta_t;
}


// When nothing else is happening OnIdle() is called.  In this case, the 
// inclusion Redraw() makes sure that the window is then updated, which 
// causes OnDisplay() to be called
void MyWindow::OnIdle() {
	Redraw();
}
