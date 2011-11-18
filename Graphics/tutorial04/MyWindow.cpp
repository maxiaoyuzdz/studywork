#include "MyWindow.h"

// this is a simple example: it creates one window,
// and draws a rotating cube with hidden surface removal

MyWindow::MyWindow() {
	SetSize(512,512);
	SetDepthBits(24);
}





void drawQuadFaceByTraingle()
{
	glBegin(GL_TRIANGLES);
	// front face
	glColor3f(1.0f,0.0f,0.0f);

	glVertex3f(-0.5,-0.5,0.5);//1

	glVertex3f(0.5,-0.5,0.5);//2

	glVertex3f(-0.5,0.5,0.5);//4

	glVertex3f(-0.5,0.5,0.5);//4

	

	glVertex3f(0.5,-0.5,0.5);//2

	glVertex3f(0.5,0.5,0.5);//3

	glEnd();

}

#define ENPROJECTION


void MyWindow::OnCreate() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#ifdef ENPROJECTION
	glFrustum(1.0,1.0,1.0,1.0,1.5,2.5);
#else
	glOrtho(-1.0f, +1.0f, -1.0f, +1.0f, -1.0f, +1.0f);
#endif
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0,0, Width(), Height());
	glEnable(GL_DEPTH_TEST);

	angle_inc = 30.0f;
	angle = 0.0f;
	current_time = (float)App::GetTime();
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

/************************************************************************/
/* exercise1:                                                                      */
/************************************************************************/

static float vertex_arr[24][3] = 
{
	//6 faces * 4 points = 34
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

static float color_arr[6][3] = 
{
	//6 faces * 1 = 6
	//call face 6 times
	1.0f,0.0f,0.0f,
	1.0f,1.0f,0.0f,
	1.0f,1.0f,1.0f,
	0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,
	1.0f,0.0f,1.0f

};
void drawQuadfaceByQuad(float arr[][3], 
						int astart, 
						int aoffset, 
						float colorarr[][3],
						int cstart, 
						int coffset)
{
	glBegin(GL_QUADS);
	
	glColor3f(colorarr[cstart][0],colorarr[cstart][1],colorarr[cstart][2]);
	
	for(int i = 0; i<4;i++)
	{
		
		glVertex3f(arr[astart][0],arr[astart][1], arr[astart][2]  );
		astart++;
	}
	
	glEnd();
}

void drawCylinder()
{

}

void MyWindow::drawCubebyVertexArr() const
{
	int pos_index = 0;
	int color_index = 0;
	for(int i = 0; i< 6;i++)
	{
		pos_index =  i*4; // 0, 4,
		color_index = i;
		drawQuadfaceByQuad(vertex_arr,pos_index,12,color_arr,color_index,3);
	}
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
		glScalef(0.5,0.5,0.5);
		glTranslated(1.0,0.0,0.0);
		glRotatef(angle, 1.0, 1.0, 1.0);
		//glTranslated(1.0,0.0,0.0);
		drawCubebyVertexArr();
	glPopMatrix();
	
	glPushMatrix();
		glScalef(0.5,0.5,0.5);
		glTranslated(-1.0,0.0,-0.5);
		glRotatef(angle*2, 1.0, 1.0, 1.0);
		//glTranslated(-1.0,0.0,0.0);
		drawCubebyVertexArr();
	glPopMatrix();

	SwapBuffers();
}

void MyWindow::OnIdle() {
	Redraw();
}
