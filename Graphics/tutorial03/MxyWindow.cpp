#include "MxyWindow.h"

MxyWindow::MxyWindow() {
	SetSize(512,512);
}

void MxyWindow::OnCreate() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0f, +1.0f, -1.0f, +1.0f, -1.0f, +1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0,0, Width(), Height());

	angle_inc = 60.0f;
	angle = 0.0f;

	
	current_time = (float)App::GetTime();
}

void MxyWindow::OnDisplay() {

	float delta_t, temp_time;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f,0.0f,0.5f);

	temp_time = (float)App::GetTime();
	delta_t = temp_time-current_time;
	current_time = temp_time;

	angle += angle_inc*delta_t;

	angle1 = -angle;

	glPushMatrix();

		glTranslatef(0.5f,0.0f,0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);


		glBegin(GL_TRIANGLES);
			glVertex3f(-0.45f, -0.45f, 0.0f);
			glVertex3f(0.45f, -0.45f, 0.0f);
			glVertex3f(0,0.45f, 0.0f);
		glEnd();

		

	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.5f,0.0f,0.0f);
		glRotatef(-angle, 0.0f, 0.0f, 1.0f);


		glBegin(GL_TRIANGLES);
		glVertex3f(-0.45f, -0.45f, 0.0f);
		glVertex3f(0.45f, -0.45f, 0.0f);
		glVertex3f(0,0.45f, 0.0f);
		glEnd();
	glPopMatrix();

	SwapBuffers();
}

void MxyWindow::OnIdle() {
	Redraw();
}
