#include "MyWindow.h"
#include <math.h>

MyWindow::MyWindow() : _angleInc(30) {
	SetSize(512,512);
	SetDepthBits(24);

	_angle = 0.0f;
}

void MyWindow::OnCreate() {
	// clear window first: it might take a moment before image loads
	glClear(GL_COLOR_BUFFER_BIT);
	SwapBuffers();

	// load image
	_texturemap.Load("terrain.bmp");

	glGenTextures(1, &_texture);

	// build 2D mip-maps from image
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	_texturemap.gluBuild2DMipmaps();
	_texturemap.Free();
	// create the terrain
	_terra.OnCreate();

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

	_material1.create(Color::black(), Color(0.95f,0.95f,0.95f,1.0f));
	_material2.create(Color::black(), Color::green());
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

	_cameraAngle = 30.0;
	_cameraPosition = -5.0;
	_cameraRotation = 0.0;
	_fullscreen = false;
	_normals = _textures = false;
	glBindTexture(GL_TEXTURE_2D, _texture);
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
			_light3.setPosition(Vector4f(0.0,2.0,-3.0,1.0));
			glTranslatef(0.0,2.0,-3.0);
			_material3.apply();
			_sphere1.draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f, 0.5f, 0.0f);
			glRotatef(-90.0f,1.0,0.0,0.0);
			_material1.apply();
			_terra.draw(!_textures);
			_material2.apply();
			_terra.normal(_normals);
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
		case 'n':
			_normals = !_normals;
			break;
		case 't':
			_textures = !_textures;
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
