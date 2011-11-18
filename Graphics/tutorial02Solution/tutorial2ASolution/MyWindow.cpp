#include "MyWindow.h"
#include <math.h>

// this is a simple example: it creates one window,
// and draws a rotating yellow triangle inside it
void MyWindow::OnDisplay() {

		static const float speed = 1.0f;
		static float xpos = 0.0f, ypos = 0.0f;
		static float xinc = speed;
		static float current_time = (float)App::GetTime();
		float delta_t, temp_time;

		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.5f-xpos,0.0f,0.5f+xpos);

		temp_time = (float)App::GetTime();
		delta_t = temp_time-current_time;
		current_time = temp_time;
		xpos += xinc*delta_t;

		if(xpos > 0.5f) {
			xinc = -xinc;
			xpos = 0.5f;
		};

		if(xpos < -0.5f) {
			xinc = -xinc;
			xpos = -0.5f;
		};
			
		static float angle = 0.0f;
		float cosAngle = cos(angle);
		float sinAngle = sin(angle);
		angle += 0.5f*delta_t;

		glBegin(GL_QUADS);
			glVertex2f(xpos + (-0.45f)*cosAngle - (-0.45f)*sinAngle, ypos + (-0.45f)*sinAngle + (-0.45f)*cosAngle);
			glVertex2f(xpos + (+0.45f)*cosAngle - (-0.45f)*sinAngle, ypos + (+0.45f)*sinAngle + (-0.45f)*cosAngle);
			glVertex2f(xpos + (+0.45f)*cosAngle - (+0.45f)*sinAngle, ypos + (+0.45f)*sinAngle + (+0.45f)*cosAngle);
			glVertex2f(xpos + (-0.45f)*cosAngle - (+0.45f)*sinAngle, ypos + (-0.45f)*sinAngle + (+0.45f)*cosAngle);
		glEnd();

		SwapBuffers();
}


// When nothing else is happening OnIdle() is called.  In this case, the 
// inclusion Redraw() makes sure that the window is then updated, which 
// causes OnDisplay() to be called
void MyWindow::OnIdle() {
	Redraw();
}
