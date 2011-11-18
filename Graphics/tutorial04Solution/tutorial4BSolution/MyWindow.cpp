#include "MyWindow.h"

// this is a simple example: it creates one window,
// and draws a rotating cube with hidden surface removal

MyWindow::MyWindow() {
	SetSize(512,512);
	SetDepthBits(24);
}

void MyWindow::OnCreate() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0f, +1.0f, -1.0f, +1.0f, -5.0f, +5.0f);
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
		glTranslated(-0.5, 0, 0);
		glRotatef(angle, 1.0, 1.0, 1.0);
		MyCube();
	glPopMatrix();
	glPushMatrix();
		glTranslated(0.5, 0, -3);
		glRotatef(angle*2, 1.0, 1.0, 1.0);
		MyCube();
	glPopMatrix();

	SwapBuffers();
}

void MyWindow::OnIdle() {
	Redraw();
}
