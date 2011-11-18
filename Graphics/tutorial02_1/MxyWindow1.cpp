#include "MxyWindow1.h"

#include <math.h>


// this is a simple example: it creates one window,
// and draws a rotating yellow triangle inside it
void MxyWindow1::OnDisplay() {

	static const float speed  = 0.5f;
	static float xpos = 0.0f, ypos = 0.0f;
	static float xinc = speed;

	static const float rotate_speed = 1.0f;
	static float rd = 0.0f;
	
	//static float rinc = rotate_speed;

	static float vertex_pos[6][2] = {-0.45f,-0.45f,
									+0.45f,-0.45f,
									+0.45f,+0.45f,
									+0.45f,+0.45f,
									-0.45f,+0.45f,
									-0.45f,-0.45f};

	static float current_time = (float)App::GetTime();
	float delta_t, temp_time;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f-xpos,0.0f,0.5f+xpos);

	temp_time = (float)App::GetTime();
	delta_t = temp_time - current_time;
	current_time = temp_time;

	//position  =  speed * t + original position
	//xpos += xinc * delta_t;

	rd += rotate_speed * delta_t;

	for(int i = 0; i<6; i++)
	{

		//x
		vertex_pos[i][0] = vertex_pos[i][0] * cos(rd) + vertex_pos[i][1] * (0- (sin(rd)));


		//y
		vertex_pos[i][1] = vertex_pos[i][0] * sin(rd) + vertex_pos[i][1] * cos(rd);
	}


	/**
	if(xpos > 0.5f) {
		xinc = -xinc;
		xpos = 0.5f;
	};

	if(xpos < -0.5f) {
		xinc = -xinc;
		xpos = -0.5f;
	};
	*/

	glBegin(GL_TRIANGLES);
	/**
	glVertex2f(xpos-0.45f, ypos-0.45f);
	glVertex2f(xpos+0.45f, ypos-0.45f);
	glVertex2f(xpos+0.45f, ypos+0.45f);

	glVertex2f(xpos+0.45f, ypos+0.45f);
	glVertex2f(xpos-0.45f, ypos+0.45f);
	glVertex2f(xpos-0.45f, ypos-0.45f);
	*/
	
	glVertex2f(vertex_pos[0][0], vertex_pos[0][1]);
	glVertex2f(vertex_pos[1][0], vertex_pos[1][1]);
	glVertex2f(vertex_pos[2][0], vertex_pos[2][1]);

	glVertex2f(vertex_pos[3][0], vertex_pos[3][1]);
	glVertex2f(vertex_pos[4][0], vertex_pos[4][1]);
	glVertex2f(vertex_pos[5][0], vertex_pos[5][1]);


	glEnd();

	SwapBuffers();
}


// When nothing else is happening OnIdle() is called.  In this case, the 
// inclusion Redraw() makes sure that the window is then updated, which 
// causes OnDisplay() to be called
void MxyWindow1::OnIdle() {
	Redraw();
}

MxyWindow1::MxyWindow1()
{
	SetSize(512,512);
}
