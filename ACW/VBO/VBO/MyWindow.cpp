#include "MyWindow.h"
#include <iostream>
#include <sstream>
// this is a simple example: it creates one window,
// and draws a rotating cube with hidden surface removal



MyWindow::MyWindow() {
	SetSize(512,512);
	SetDepthBits(24);
	SetTitle("Vertex Buffer Objects Demo");
	_startTime = (float)App::GetTime();

	_drawMode = drawMode::IMMEDIATE;
	_numberOfCubes = 1;
	_quads = false;
}

void MyWindow::OnCreate() {
	GLWindowEx::OnCreate();
	// turns vsync off so the frame rate is not limited
	wglSwapIntervalEXT(0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1.0f, +1.0f, -1.0f, +1.0f, -1.0f, +1.0f);
	gluPerspective(45.0f,(GLfloat)512/(GLfloat)512,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glViewport(0,0, Width(), Height());
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	 // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
	initialiseLights();
	_angle_inc = 30.0f;
	_angle = 0.0f;
	_current_time = (float)App::GetTime();
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	_cube = new House();
	//////////////////////////////////////////////////////////////////////////

	_frames = 0;
	_startTime = (float)App::GetTime();
	
}



void MyWindow::OnDisplay() {
	float delta_t, temp_time;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	temp_time = (float)App::GetTime();
	delta_t = temp_time-_current_time;
	_current_time = temp_time;

	_angle += _angle_inc * delta_t;

	if(_angle>360.0f) 
	{
		_angle -=360.0f;
	}

	if (_numberOfCubes == 50)
	{
		for (int y = 0; y < _numberOfCubes; y++)
		{
			for (int x = 0; x < _numberOfCubes; x++)
			{
				glPushMatrix();
					// draw top left	

					glTranslatef((float)x*1.6f - 39.0f,((float(y))*1.6f-39.0f),-99.0f);
					glRotatef(_angle, 1.0, 1.0, 1.0);		

					/************************************************************************/
					/*                                                                      */
					/************************************************************************/
					_cube->drawUsingVertexBufferObjects();
					//////////////////////////////////////////////////////////////////////////

				glPopMatrix();
			}
		}
	}
	else if (_numberOfCubes == 1)
	{
			glPushMatrix();
					// draw top left	

					glTranslatef(0.0,0.0,-7.0f);
					glRotatef(_angle, 1.0, 1.0, 1.0);	

					
					_cube->drawUsingVertexBufferObjects();
					
				glPopMatrix();
			
	}
	_frames++;
	if  ((float)App::GetTime() - _startTime >= 1)
	{
		
		_fps = _frames;
		// add fps multiplier for FAKE video card
		bool fake = false;
		if (fake== true)
		{
			if (_drawMode == drawMode::VBOS)
			{
				_fps *= 20;
			}
			
		}
		_startTime = (float)App::GetTime();
		_frames = 0;
		
	}
	std::stringstream ss;
	ss << "Vertex Buffer Objects - ";
	
		ss << "FPS: " << _fps << std::endl;
		glDisable(GL_LIGHTING);
		glColor3f(1.0,1.0,1.0);
		glRasterPos3f(-1.5f,2.0f, -7.0f);
		Printf(ss.str().c_str());
		glEnable(GL_LIGHTING);
	SwapBuffers();
	

}

void MyWindow::OnIdle() {
	Redraw();
}

///////////////////////////////////////////////////////////////////////////////
// initialize lights
///////////////////////////////////////////////////////////////////////////////
void MyWindow::initialiseLights()
{
    // set up light colors (ambient, diffuse, specular)
    GLfloat lightAmbient[] = {0.2, 0.2, 0.2, 1.0};  // ambient light
    GLfloat lightDiffuse[] = {0.7, 0.7, 0.7, 1.0};  // diffuse light
    GLfloat lightSpecular[] = {1.0, 1.0, 1.0, 1.0};           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // position the light
    GLfloat lightPos[4] = {0, 0, 20, 1}; // positional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration
}

void MyWindow::OnKeyboard(int key, bool down) {
	if (!down) return;
	switch( tolower(key) ) {
		case 'v':
			if (_drawMode == drawMode::VBOS)
			{
				_drawMode = drawMode::DISPLAY_LIST;
			}
			else if (_drawMode == drawMode::DISPLAY_LIST)
			{
				_drawMode = drawMode::IMMEDIATE;
			}
			else if (_drawMode == drawMode::RANGE_ELEMENTS)
			{
				_drawMode = drawMode::VBOS;
			}
			else if (_drawMode == drawMode::IMMEDIATE)
			{
				_drawMode = drawMode::DRAW_ARRAY_SEPARATE_VERTEX_ARRAY;
			}
			else if (_drawMode == drawMode::DRAW_ARRAY_SEPARATE_VERTEX_ARRAY)
			{
				_drawMode = drawMode::DRAW_ARRAY_INTERLEAVED_VERTEX_ARRAY;
			}
			else if (_drawMode == drawMode::DRAW_ARRAY_INTERLEAVED_VERTEX_ARRAY)
			{
				_drawMode = drawMode::DRAW_ELEMENTS_INTERLEAVED_VERTEX_ARRAY;
				//_drawMode = drawMode::RANGE_ELEMENTS;
			}
			else if (_drawMode == drawMode::DRAW_ELEMENTS_INTERLEAVED_VERTEX_ARRAY)
			{
				_drawMode = drawMode::RANGE_ELEMENTS;
			}
			break;
		case 'c':
			if (_numberOfCubes == 1)
			{
				_numberOfCubes = 50;
			}
			else
			{
				_numberOfCubes = 1;
			}
			
			break;
		case 'q':
			_quads = !_quads;
			
			break;
		default:
			break;
	}
}	