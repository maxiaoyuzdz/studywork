#include "MxyWindow2.h"

#include <math.h>




#define POSITIVE_DIRECTION

static const float scale_factor = 0.5f;

static float vertex_coor[4][2] = {-0.45f,-0.45f,
	+0.45f,-0.45f,
	+0.45f,+0.45f,
	-0.45f,+0.45f};

MxyWindow2::MxyWindow2()
{
	SetSize(512,512);

	//scale to small
	for(int i = 0; i<4;i++)
	{
		for(int j = 0; j<2; j++)
		{
			vertex_coor[i][j] = vertex_coor[i][j] * scale_factor;
		}
	}


}

// this is a simple example: it creates one window,
// and draws a rotating yellow triangle inside it
void MxyWindow2::OnDisplay() {


	static const float rotate_speed = 0.001f;

	static const float speed  = 0.5f;

	static float xpos = 0.0f, ypos = 0.0f, rpos = 0.0f;
	static float xinc = speed;


	static float current_time = (float)App::GetTime();
	float delta_t, temp_time;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f-xpos,0.0f,0.5f+xpos);

	temp_time = (float)App::GetTime();
	delta_t = temp_time - current_time;
	current_time = temp_time;

	//position  =  speed * t + original position
	xpos += xinc * delta_t;

	
	rpos = rotate_speed;

	for(int i = 0; i<4; i++)
	{
		//x
		float x;
		float y;

#ifdef POSITIVE_DIRECTION
		x = cos(rpos) *  vertex_coor[i][0] + -sin(rpos) * vertex_coor[i][1];
		y = sin(rpos) * vertex_coor[i][0] + cos(rpos) * vertex_coor[i][1];
#else
		x = cos(rpos) * vertex_coor[i][0] + sin(rpos) *   vertex_coor[i][1];
		y = -sin(rpos) * vertex_coor[i][0] + cos(rpos) * vertex_coor[i][1];
#endif

		vertex_coor[i][0] = x;
		vertex_coor[i][1] = y;

	}


	if(xpos > 0.5f) {
		xinc = -xinc;
		xpos = 0.5f;
	};

	if(xpos < -0.5f) {
		xinc = -xinc;
		xpos = -0.5f;
	};

	

	glBegin(GL_QUADS);

	
	/**
	glVertex2f(xpos-0.45f, ypos-0.45f);
	glVertex2f(xpos+0.45f, ypos-0.45f);
	glVertex2f(xpos+0.45f, ypos+0.45f);
	glVertex2f(xpos-0.45f, ypos+0.45f);
	*/
	//glRotatef(0.1f,0.0f,0.0f,1.0f);
	
	glVertex2f(vertex_coor[0][0], vertex_coor[0][1]);
	glVertex2f(vertex_coor[1][0], vertex_coor[1][1]);
	glVertex2f(vertex_coor[2][0], vertex_coor[2][1]);
	glVertex2f(vertex_coor[3][0], vertex_coor[3][1]);
	
	/**
	glVertex2f(xpos-vertex_coor[0][0], ypos-vertex_coor[0][1]);
	glVertex2f(xpos+vertex_coor[1][0], ypos-vertex_coor[1][1]);
	glVertex2f(xpos+vertex_coor[2][0], ypos+vertex_coor[2][1]);
	glVertex2f(xpos-vertex_coor[3][0], ypos+vertex_coor[3][1]);
	*/
	

	glEnd();

	

	
	

	SwapBuffers();
}


// When nothing else is happening OnIdle() is called.  In this case, the 
// inclusion Redraw() makes sure that the window is then updated, which 
// causes OnDisplay() to be called
void MxyWindow2::OnIdle() {
	Redraw();
}

