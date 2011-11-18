#include "MyWindow.h"
#include <math.h>

const float PI = 3.1415926535898f;

// this is a simple example: it creates one window,
// and draws a rotating yellow triangle inside it
void MyWindow::OnDisplay() {

	static const float speed = 1.0f;
	static const float diskSize = 0.15f;
	static const float radius = 0.55f;
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
		
	xpos = radius * cos(angle);
	ypos = radius * sin(angle);
	glBegin(GL_TRIANGLE_FAN);
		// construct disk from 0 to 360 degrees in 1 degree increments
		for(float diskAngle = 0.0; diskAngle < 2*PI; diskAngle += 0.01745f) 
		{
			float cosAngle = cos(diskAngle);
			float sinAngle = sin(diskAngle);
			glVertex2f((xpos + (diskSize)*cosAngle) - (ypos + (diskSize)*sinAngle),
					   (xpos + (diskSize)*sinAngle) + (ypos + (diskSize)*cosAngle));
		}
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
