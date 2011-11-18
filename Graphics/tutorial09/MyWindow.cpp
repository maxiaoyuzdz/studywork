#include "MyWindow.h"
#include <math.h>

MyWindow::MyWindow() : _angleInc(30) {
	SetSize(512,512);
	SetDepthBits(24);

	_angle = 0.0f;
}

void MyWindow::OnCreate() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// clear window first: it might take a moment before image loads
	glClear(GL_COLOR_BUFFER_BIT);
	SwapBuffers();

	// load image
	_images[0].Load("left.bmp");
	_images[1].Load("right.bmp");
	_images[2].Load("top.bmp");
	_images[3].Load("bottom.bmp");
	_images[4].Load("front.bmp");
	_images[5].Load("back.bmp");
	_images[6].Load("map.bmp");

	glGenTextures(7, &_textures[0]);

	// build 2D mip-maps from image
	for (int i = 0; i<7;i++) {
		glBindTexture(GL_TEXTURE_2D, _textures[i]);
		_images[i].gluBuild2DMipmaps();
		_images[i].Free();
	};
	

	// set the projection required
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0f, +1.0f, -1.0f, +1.0f, 1.0f, +10.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0,0, Width(), Height());
	glEnable(GL_DEPTH_TEST);

	// set the background clear colour to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// set the shade model to smooth (Gouraud shading)
	glShadeModel(GL_SMOOTH);

	// remove back faces
	glEnable(GL_CULL_FACE);

	_material1.create(Color::black(), Color(0.8f,0.8f,0.8f,1.0f));
	_material2.create(Color::black(), Color(0.7f,0.7f,0.7f,1.0f));
	_material3.create(Color::black(), Color::black(), Color::yellow());

	// setup some lights (ambient is turned off on all lights)
	_light1.create(0, Color::black(), Color(0.5f,0.5f,0.5f,1.0f)); 
	_light2.create(1, Color::black(), Color(0.5f,0.5f,0.5f,1.0f)); 
	_light3.create(2, Color::black(), Color(0.5f,0.5f,0.0f,1.0f));

	// turn the global ambient off by setting it to zero
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Color::black().rgba());

	// Turn on the lights
	_light1.apply();
	_light2.apply();
	_light3.apply();

	// setup the two spheres
	_sphere1.create(0.1f, 10, 10, false);
	//_sphere2.create(1.0f, 20, 20, true);
	_sphere.create(1.0f, 40, 40, true);
	_cameraAngle = 30.0;
	_cameraPosition = -5.0;
	_cameraRotation = 0.0;
	_fullscreen = false;
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

void MyWindow::texcube() const
{
	glEnable(GL_TEXTURE_2D);
	// Front Face
	glBindTexture(GL_TEXTURE_2D, _textures[4]);
	glBegin(GL_QUADS);
		glNormal3f(0.0f,0.0f,1.0f);
		glTexCoord2d(0.0, 0.0);		glVertex3d(-1.0, -1.0,  1.0);
		glTexCoord2d(1.0, 0.0);		glVertex3d( 1.0, -1.0,  1.0);
		glTexCoord2d(1.0, 1.0);		glVertex3d( 1.0,  1.0,  1.0);
		glTexCoord2d(0.0, 1.0);		glVertex3d(-1.0,  1.0,  1.0);
	glEnd();
	// Back Face
	glBindTexture(GL_TEXTURE_2D, _textures[5]);
	glBegin(GL_QUADS);
		glNormal3f(0.0f,0.0f,-1.0f);
		glTexCoord2d(1.0, 0.0);		glVertex3d(-1.0, -1.0, -1.0);
		glTexCoord2d(1.0, 1.0);		glVertex3d(-1.0,  1.0, -1.0);
		glTexCoord2d(0.0, 1.0);		glVertex3d( 1.0,  1.0, -1.0);
		glTexCoord2d(0.0, 0.0);		glVertex3d( 1.0, -1.0, -1.0);
	glEnd();
	// Top Face
	glBindTexture(GL_TEXTURE_2D, _textures[2]);
	glBegin(GL_QUADS);
		glNormal3f(0.0f,1.0f,0.0f);
		glTexCoord2d(0.0, 1.0);		glVertex3d(-1.0,  1.0, -1.0);
		glTexCoord2d(0.0, 0.0);		glVertex3d(-1.0,  1.0,  1.0);
		glTexCoord2d(1.0, 0.0);		glVertex3d( 1.0,  1.0,  1.0);
		glTexCoord2d(1.0, 1.0);		glVertex3d( 1.0,  1.0, -1.0);
	glEnd();
	// Bottom Face
	glBindTexture(GL_TEXTURE_2D, _textures[3]);
	glBegin(GL_QUADS);
		glNormal3f(0.0f,-1.0f,0.0f);
		glTexCoord2d(1.0, 1.0);		glVertex3d(-1.0, -1.0, -1.0);
		glTexCoord2d(0.0, 1.0);		glVertex3d( 1.0, -1.0, -1.0);
		glTexCoord2d(0.0, 0.0);		glVertex3d( 1.0, -1.0,  1.0);
		glTexCoord2d(1.0, 0.0);		glVertex3d(-1.0, -1.0,  1.0);
	glEnd();
	// Right face
	glBindTexture(GL_TEXTURE_2D, _textures[1]);
	glBegin(GL_QUADS);
		glNormal3f(1.0f,0.0f,0.0f);
		glTexCoord2d(1.0, 0.0);		glVertex3d( 1.0, -1.0, -1.0);
		glTexCoord2d(1.0, 1.0);		glVertex3d( 1.0,  1.0, -1.0);
		glTexCoord2d(0.0, 1.0);		glVertex3d( 1.0,  1.0,  1.0);
		glTexCoord2d(0.0, 0.0);		glVertex3d( 1.0, -1.0,  1.0);
	glEnd();
	// Left Face
	glBindTexture(GL_TEXTURE_2D, _textures[0]);
	glBegin(GL_QUADS);
		glNormal3f(-1.0f,0.0f,0.0f);
		glTexCoord2d(0.0, 0.0);		glVertex3d(-1.0, -1.0, -1.0);
		glTexCoord2d(1.0, 0.0);		glVertex3d(-1.0, -1.0,  1.0);
		glTexCoord2d(1.0, 1.0);		glVertex3d(-1.0,  1.0,  1.0);
		glTexCoord2d(0.0, 1.0);		glVertex3d(-1.0,  1.0, -1.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void MyWindow::OnDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float deltaTime = (float)App::GetDeltaTime();

	_angle += _angleInc * deltaTime;
	if(_angle > 360.0f) 
		_angle -=360.0f;

	glPushMatrix();
		glTranslatef(0.0f, 0.0f,_cameraPosition);
		glRotatef(_cameraAngle, 1.0,0.0,0.0);
		glRotatef(_cameraRotation, 0.0, 1.0, 0.0);
		glTranslatef(0.0f, -1.0f,0.0f);

		_light1.setPosition(Vector4f(1.0,2.0,3.0,1.0));
		_light2.setPosition(Vector4f(-1.0,2.0,3.0,1.0));

		glPushMatrix();
			glRotatef(-4*_angle, 0.0, 1.0, 0.0);
			_light3.setPosition(Vector4f(0.0,4.5,-3.0,1.0));
			glTranslatef(0.0,4.5,-3.0);
			_material3.apply();
			_sphere1.draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f, 3.0f, 0.0f);
			glRotatef(_angle*2.0f, 0.0, 1.0, 0.0);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textures[6]);
			_material1.apply();
			_sphere.draw();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f, 0.5f, 0.0f);
			glRotatef(-_angle, 0.0, 1.0, 0.0);
			_material1.apply();
			texcube();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f, -0.8f, 0.0f);
			_material2.apply();
			floor();
		glPopMatrix();
	glPopMatrix();

	SwapBuffers();
}

void MyWindow::OnIdle() {
	Redraw();
}

void MyWindow::OnResize(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-(float)w/h, (float)w/h, -1.0f, 1.0f, 1.0f, +10.0f);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,w,h);
}

void MyWindow::OnKeyboard(int key, bool down) {
	if (!down) return;
	switch( tolower(key) ) {
		case 'a': 
			_cameraAngle += 5.0;
			break;
		case 'z':
			_cameraAngle -= 5.0;
			break;
		case 'f':
			_fullscreen = !_fullscreen;
			SetFullscreen(_fullscreen);
			break;
		case 'q':
			Close();
			break;
		default:
			break;
	}
}	

void MyWindow::OnMouseButton(MouseButton button, bool down) {
	if (down) {
		switch(button) {
			case MBLeft: 
				_leftDown = true;
				break;
			case MBRight:
				_rightDown = true;
				break;
			default:
				break;
		}
	} else {
		switch(button) {
			case MBLeft: 
				_leftDown = false;
				break;
			case MBRight:
				_rightDown = false;
				break;
			default:
				break;
		}
	}
}

void MyWindow::OnMouseMove(int x, int y) {
	static int temp_x, temp_y;
	if(_leftDown) {
		_cameraPosition += (y-temp_y)*0.05f;
	}
	if(_rightDown) {
		_cameraRotation += (x-temp_x)*0.5f;
	}
	temp_x = x;
	temp_y = y;
}
