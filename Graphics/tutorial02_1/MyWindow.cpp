#include "MyWindow.h"

// this is a simple example: it creates one window,
// and draws a rotating yellow triangle inside it
void MyWindow::OnDisplay() {

	static const float speed  = 0.5f;
	

	static float xpos = 0.0f, ypos = 0.0f; 
	static float xinc = speed;

	

	static float current_time = (float)App::GetTime();
	float delta_t, temp_time;

	

	temp_time = (float)App::GetTime();
	delta_t = temp_time - current_time;
	current_time = temp_time;

	//position  =  speed * t + original position
	xpos += xinc * delta_t;
	


	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f-xpos,0.0f,0.5f+xpos);

	//edge check
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
