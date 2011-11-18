#include "MyWindow.h"
#include <math.h>
#include <gl/glut.h>

// this is a simple example: it creates one window,
// and draws a rotating cube with hidden surface removal
// and uses three lights to give shading

#define  NUSEVERTEXARRAY

MyWindow::MyWindow() {
	SetSize(512,512);
	SetDepthBits(24);
}

void MyWindow::OnCreate() {
	// just for the demo, setup lights here
	float const globalAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f };

	float const ambientLight0[] = {0.0f, 0.0f, 0.0f, 1.0f };
	float const diffuseLight0[] = {0.5f, 0.5f, 0.5f, 1.0f };
	float const lightPosition0[] = {1.0f, 2.0f, 1.0f, 1.0f };

	float const ambientLight1[] = {0.0f, 0.0f, 0.0f, 1.0f };
	float const diffuseLight1[] = {0.5f, 0.5f, 0.5f, 1.0f };
	float const lightPosition1[] = {-1.0f, 2.0f, 1.0f, 1.0f };

	float const ambientLight2[] = {0.0f, 0.0f, 0.0f, 1.0f };
	float const diffuseLight2[] = {0.5f, 0.5f, 0.5f, 1.0f };
	float const lightPosition2[] = {0.0f, 2.0f, -4.0f, 1.0f };

	float const matAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f };
	float const matDiffuse[] = {0.7f, 0.7f, 0.2f, 1.0f };

	// set the projection required

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1.0f, +1.0f, -1.0f, +1.0f, -1.0f, +10.0f);
	glFrustum(-1.0f, +1.0f, -1.0f, +1.0f, 1.0f, +10.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0,0, Width(), Height());
	glEnable(GL_DEPTH_TEST);

	// set the background clear colour to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// set the shade model to smooth (Gouraud shading)
	glShadeModel(GL_FLAT);

	// remove back faces
	glEnable(GL_CULL_FACE);
	// enable lighting (we will later need to enable individual lights
	glEnable(GL_LIGHTING);

	// setup the material for the objects 
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);

	// setup some lights (ambient is turned off on all lights)
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight2);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);

	// turn the global ambient off by setting it to zero
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

	// now turn the lights on
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	angle_inc = 30.0f;
	angle = 0.0f;
	current_time = (float)App::GetTime();
}



void MyWindow::Cube() const {
#ifndef USEVERTEXARRAY
	float const matAmbient2[] = {1.0f, 1.0f, 1.0f, 1.0f };
	float const matDiffuse2[] = {0.7f, 0.7f, 0.2f, 1.0f };
	glBegin(GL_QUADS);

	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse2);
		// front face
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5,-0.5,0.5);
		glVertex3f(0.5,-0.5,0.5);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(-0.5,0.5,0.5);		
		// back face
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5,-0.5,-0.5);
		glVertex3f(-0.5,0.5,-0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(0.5,-0.5,-0.5);
		// left face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5,-0.5,0.5);
		glVertex3f(-0.5,0.5,0.5);
		glVertex3f(-0.5,0.5,-0.5);
		glVertex3f(-0.5,-0.5,-0.5);
		// right face
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5,-0.5,0.5);
		glVertex3f(0.5,-0.5,-0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(0.5,0.5,0.5);		
		// top face
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5,0.5,0.5);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(-0.5,0.5,-0.5);
		// bottom face
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-0.5,-0.5,0.5);
		glVertex3f(-0.5,-0.5,-0.5);
		glVertex3f(0.5,-0.5,-0.5);
		glVertex3f(0.5,-0.5,0.5);
	glEnd();

#else

	GLfloat _normals[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, -1.0f,
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, -1.0f, 0.0f
	};

	GLfloat _vertices[] = {
		-0.5,-0.5,0.5,
		0.5,-0.5,0.5,
		0.5,0.5,0.5,
		-0.5,0.5,0.5,

		-0.5,-0.5,-0.5,
		-0.5,0.5,-0.5,
		0.5,0.5,-0.5,
		0.5,-0.5,-0.5,

		-0.5,-0.5,0.5,
		-0.5,0.5,0.5,
		-0.5,0.5,-0.5,
		-0.5,-0.5,-0.5,

		0.5,-0.5,0.5,
		0.5,-0.5,-0.5,
		0.5,0.5,-0.5,
		0.5,0.5,0.5,

		-0.5,0.5,0.5,
		0.5,0.5,0.5,
		0.5,0.5,-0.5,
		-0.5,0.5,-0.5,

		-0.5,-0.5,0.5,
		-0.5,-0.5,-0.5,
		0.5,-0.5,-0.5,
		0.5,-0.5,0.5
	};



#endif
}


void redCube()
{
	
	float const matAmbient1[] = {1.0f, 0.0f, 0.0f, 1.0f };
	float const matDiffuse1[] = {0.7f, 0.0f, 0.0f, 1.0f };
	

	glBegin(GL_QUADS);

	
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse1);

	glColor3f(1.0,0.0,0.0);

	
	// front face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5,-0.5,0.5);
	glVertex3f(0.5,-0.5,0.5);
	glVertex3f(0.5,0.5,0.5);
	glVertex3f(-0.5,0.5,0.5);		
	// back face
	glColor3f(1.0,0.0,0.0);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5,-0.5,-0.5);
	glVertex3f(-0.5,0.5,-0.5);
	glVertex3f(0.5,0.5,-0.5);
	glVertex3f(0.5,-0.5,-0.5);
	// left face
	glColor3f(1.0,0.0,0.0);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5,-0.5,0.5);
	glVertex3f(-0.5,0.5,0.5);
	glVertex3f(-0.5,0.5,-0.5);
	glVertex3f(-0.5,-0.5,-0.5);
	// right face
	glColor3f(1.0,0.0,0.0);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5,-0.5,0.5);
	glVertex3f(0.5,-0.5,-0.5);
	glVertex3f(0.5,0.5,-0.5);
	glVertex3f(0.5,0.5,0.5);		
	// top face
	glColor3f(1.0,0.0,0.0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5,0.5,0.5);
	glVertex3f(0.5,0.5,0.5);
	glVertex3f(0.5,0.5,-0.5);
	glVertex3f(-0.5,0.5,-0.5);
	// bottom face
	glColor3f(1.0,0.0,0.0);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.5,-0.5,0.5);
	glVertex3f(-0.5,-0.5,-0.5);
	glVertex3f(0.5,-0.5,-0.5);
	glVertex3f(0.5,-0.5,0.5);
	glEnd();
}
void MyWindow::floor() const
{
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-2.0f,0.0f,2.0f);
		glVertex3f(2.0f,0.0f,2.0f);
		glVertex3f(2.0f,0.0f,-2.0f);
		glVertex3f(-2.0f,0.0f,-2.0f);
	glEnd();
}
/************************************************************************/
/* light position                                                                     */
/************************************************************************/
static float light1pos[] = {-1.0f, 2.0f, 1.0f, 1.0f};


void MyWindow::OnDisplay() {
	float delta_t, temp_time;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// glColor3f(0.9f,0.9f,0.9f);

	temp_time = (float)App::GetTime();
	delta_t = temp_time-current_time;
	current_time = temp_time;

	angle += angle_inc*delta_t;

	if(angle>360.0f) angle -=360.0f;

	float x = light1pos[0] * cos(angle) - light1pos[2] * sin(angle);
	float z = light1pos[0] * sin(angle) + light1pos[2] * cos(angle);
	
	
	glPushMatrix();

	glDisable(GL_LIGHT1);

	
	
	glRotatef(angle, 0.0, 1.0, 0.0);



	glTranslatef(light1pos[0],light1pos[1],light1pos[2]  );

	//glutSolidSphere(0.1,4,4);

	glEnable(GL_LIGHT1);
	
	glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
	

	glPopMatrix();
	
	

	
	glPushMatrix();
	
	

	glTranslatef(-0.8f, 0.5f, -2.0f);
	glRotatef(angle_inc, 0.0, 1.0, 0.0);
	redCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.5f, -2.0f);
	glRotatef(angle_inc, 0.0, 1.0, 0.0);
	Cube();
	glPopMatrix();


	glPushMatrix();
		glTranslatef(0.0f, -0.8f, -2.0f);
		floor();
	glPopMatrix();

	SwapBuffers();
}

void MyWindow::OnIdle() {
	Redraw();
}
