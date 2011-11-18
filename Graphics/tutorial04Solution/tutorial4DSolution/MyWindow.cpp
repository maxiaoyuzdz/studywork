#include "MyWindow.h"
#include <math.h>

const float PI = 3.1415926535898f;

// this is a simple example: it creates one window,
// and draws a rotating cube with hidden surface removal

MyWindow::MyWindow() {
	SetSize(512,512);
	SetDepthBits(24);
}

void MyWindow::OnCreate() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1.0f, +1.0f, -1.0f, +1.0f, -5.0f, +5.0f);
	glFrustum(-1.0, +1.0, -1.0, +1.0, 2.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0,0, Width(), Height());
	glEnable(GL_DEPTH_TEST);

	angle_inc = 30.0f;
	angle = 0.0f;
	current_time = (float)App::GetTime();
}

void MyWindow::Face() const
{
	glBegin(GL_QUADS);
		// draw face around the origin at z=0
		glVertex2f(-0.5, -0.5);
		glVertex2f(+0.5, -0.5);
		glVertex2f(+0.5, +0.5);
		glVertex2f(-0.5, +0.5);	
	glEnd();
}

void MyWindow::MyCube() const
{
	// front face
	glColor3f(1.0f,0.0f,0.0f);
	glPushMatrix();
		glTranslated(0, 0, +0.5);
		Face();
	glPopMatrix();
	// back face
	glColor3f(1.0f,1.0f,0.0f);
	glPushMatrix();
		glTranslated(0, 0, -0.5);
		Face();
	glPopMatrix();
	// left face
	glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();
		glTranslated(-0.5, 0, 0);
		glRotated(90, 0, 1, 0);
		Face();
	glPopMatrix();
	// right face
	glColor3f(0.0f,1.0f,1.0f);
	glPushMatrix();
		glTranslated(+0.5, 0, 0);
		glRotated(90, 0, 1, 0);
		Face();
	glPopMatrix();
	// top face
	glColor3f(0.0f,0.0f,1.0f);
	glPushMatrix();
		glTranslated(0, +0.5, 0);
		glRotated(90, 1, 0, 0);
		Face();
	glPopMatrix();
	// bottom face
	glColor3f(1.0f,0.0f,1.0f);
	glPushMatrix();
		glTranslated(0, -0.5, 0);
		glRotated(90, 1, 0, 0);
		Face();
	glPopMatrix();
}

void MyWindow::Cube() const {
	glBegin(GL_QUADS);
		// front face
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-0.5,-0.5,0.5);
		glVertex3f(0.5,-0.5,0.5);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(-0.5,0.5,0.5);		
		// back face
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(-0.5,-0.5,-0.5);
		glVertex3f(-0.5,0.5,-0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(0.5,-0.5,-0.5);
		// left face
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f(-0.5,-0.5,0.5);
		glVertex3f(-0.5,0.5,0.5);
		glVertex3f(-0.5,0.5,-0.5);
		glVertex3f(-0.5,-0.5,-0.5);
		// right face
		glColor3f(0.0f,1.0f,1.0f);
		glVertex3f(0.5,-0.5,0.5);
		glVertex3f(0.5,-0.5,-0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(0.5,0.5,0.5);		
		// top face
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-0.5,0.5,0.5);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(-0.5,0.5,-0.5);
		// bottom face
		glColor3f(1.0f,0.0f,1.0f);
		glVertex3f(-0.5,-0.5,0.5);
		glVertex3f(-0.5,-0.5,-0.5);
		glVertex3f(0.5,-0.5,-0.5);
		glVertex3f(0.5,-0.5,0.5);
	glEnd();
}

void MyWindow::MyCylinder() const
{
	float radius = 1.0f;
	float halfLength = 1.0f;
	float angleInc = 0.01745; // 1 degree = 0.01745 radians
	glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 0.0f);
		for(float angle = 0.0; angle < 2*PI; angle += angleInc)
		{
			float nextAngle = angle + angleInc;
			float x1 = radius*cos(angle);
			float z1 = -radius*sin(angle);
			float x2 = radius*cos(nextAngle);
			float z2 = -radius*sin(nextAngle);

			glVertex3f(x1, -halfLength, z1);
			glVertex3f(x2, -halfLength, z2);
			glVertex3f(x2, +halfLength, z2);
			glVertex3f(x1, +halfLength, z1);
		}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f, 0.0f, 0.0f);
		for(float angle = 0.0; angle < 2*PI; angle += angleInc)
		{
			glVertex3f(radius*cos(angle), -halfLength, -radius*sin(angle));
		}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0f, 1.0f, 0.0f);
		for(float angle = 0.0; angle < 2*PI; angle += angleInc)
		{
			glVertex3f(radius*cos(angle), +halfLength, -radius*sin(angle));
		}
	glEnd();
}

void MyWindow::OnDisplay() {
	float delta_t, temp_time;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.5f,0.0f,0.5f);

	temp_time = (float)App::GetTime();
	delta_t = temp_time-current_time;
	current_time = temp_time;

	angle += angle_inc*delta_t;

	if(angle>360.0f) angle -=360.0f;
	glPushMatrix();
		glTranslated(-0.5, 0, -3);
		glRotatef(angle, 1.0, 1.0, 1.0);
		MyCube();
	glPopMatrix();
	glPushMatrix();
		glTranslated(0.5, 0, -6);
		glRotatef(angle*2, 1.0, 1.0, 1.0);
		MyCylinder();
	glPopMatrix();

	SwapBuffers();
}

void MyWindow::OnIdle() {
	Redraw();
}
