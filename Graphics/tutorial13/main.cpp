#include "GXBase.h"

using namespace gxbase;

// This example draws two viewports in a single window, a perspective view and a plan view




class Vector4f {
private:
	GLfloat _xyzw[4];

public:
	void Assign(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
		_xyzw[0] = x;
		_xyzw[1] = y;
		_xyzw[2] = z;
		_xyzw[3] = w;
	}

	Vector4f() { 
		Assign(0.0, 0.0, 0.0, 1.0);
	}

	Vector4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
		Assign(x, y, z, w);
	}

	Vector4f(GLfloat xyzw[]) {
		Assign(xyzw[0], xyzw[1], xyzw[2], xyzw[3]);
	}

	const GLfloat* xyzw() const {
		return _xyzw;
	}
};

class Color {
private:
	GLfloat _rgba[4];

public:
	void Assign(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
		_rgba[0] = r;
		_rgba[1] = g;
		_rgba[2] = b;
		_rgba[3] = a;
	}

	Color() { 
		Assign(0.0, 0.0, 0.0, 0.0);
	}

	Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
		Assign(r, g, b, a);
	}

	Color(GLfloat rgba[]) {
		Assign(rgba[0], rgba[1], rgba[2], rgba[3]);
	}

	const GLfloat* rgba() const {
		return _rgba;
	}

	static Color black() {
		return Color(0.0, 0.0, 0.0, 1.0);
	}

	static Color white() {
		return Color(1.0, 1.0, 1.0, 1.0);
	}

	static Color red() {
		return Color(1.0, 0.0, 0.0, 1.0);
	}

	static Color green() {
		return Color(0.0, 1.0, 0.0, 1.0);
	}

	static Color blue() {
		return Color(0.0, 0.0, 1.0, 1.0);
	}

	static Color null() {
		return Color(0.0, 0.0, 0.0, 0.0);
	}
};

class Materials {
private:
	Color _ambient;
	Color _diffuse;
	Color _emission;

public:
	Materials() {
		_ambient = Color::black();
		_diffuse = Color::white();
	}

	void create(const Color &ambient=Color::black(), const Color &diffuse=Color::white(), const Color &emission=Color::null()) {
		setAmbient(ambient);
		setDiffuse(diffuse);
		setEmission(emission);
	}

	void setAmbient(const Color &ambient) {
		_ambient = ambient;
	}		

	void setDiffuse(const Color &diffuse) {
		_diffuse = diffuse;
	}		

	void setEmission(const Color &emission) {
		_emission = emission;
	}		

	void apply() const {
		glMaterialfv(GL_FRONT, GL_AMBIENT, _ambient.rgba());
		glMaterialfv(GL_FRONT, GL_DIFFUSE, _diffuse.rgba());
		glMaterialfv(GL_FRONT, GL_EMISSION, _emission.rgba());
	}
};


class Lights {
private:
	// Light number
	GLuint _lightNumber;				

	// Ambient, diffuse and position
	Color _ambient;
	Color _diffuse;
	Vector4f _position;

public:
	Lights() {
		_lightNumber = -1;
	}

	void create(GLuint lightNum, const Color &ambient=Color::black(), const Color &diffuse=Color::white(), const Vector4f &position=Vector4f(0.0f,0.0f,0.0f,1.0f)) {
		// the light being defined
		_lightNumber = lightNum;	

		setAmbient(ambient);
		setDiffuse(diffuse);
		setPosition(position);
	}

	void setAmbient(const Color &ambient) {
		_ambient = ambient;
		glLightfv(GL_LIGHT0+_lightNumber, GL_AMBIENT, _ambient.rgba());
	}		

	void setDiffuse(const Color &diffuse) {
		_diffuse = diffuse;
		glLightfv(GL_LIGHT0+_lightNumber, GL_DIFFUSE, _diffuse.rgba());
	}		

	void setPosition(const Vector4f &position) {
		_position = position;
		glLightfv(GL_LIGHT0+_lightNumber, GL_POSITION, _position.xyzw());
	}

	void apply() {
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0 + _lightNumber);
	}
};


class Sphere {
private:
	GLUquadric *_obj;
	GLfloat _radius;
	GLuint _slices, _stacks;

public:	 
	Sphere() { 
		_obj = NULL;
	}

	~Sphere() {
		gluDeleteQuadric(_obj);
	}

	void create(GLfloat radius, GLuint slices, GLuint stacks) {
		_obj = gluNewQuadric();
		gluQuadricNormals(_obj, GLU_SMOOTH);
		_radius = radius;
		_slices = slices;
		_stacks = stacks;
	}

	void draw() const {
		if (_obj)
			gluSphere(_obj, _radius, _slices, _stacks);
	}
};



class MyWindow :public GLWindow {
private:
	// OpenGL objects
	Lights _light1, _light2, _light3;
	Materials _material1, _material2, _material3;
	Sphere _sphere1, _sphere2;
	int _width, _height;

	float _cameraAngle, _cameraPosition, _cameraRotation;
	bool _leftDown, _rightDown;


public:
	MyWindow(float cam);
	void OnCreate();
	void floor() const;
	void drawscene(float angle, float cameraRotation);
	void OnDisplay();
	void OnIdle();
	void OnResize(int w, int h);
	void OnKeyboard(int key, bool down);
	void OnMouseButton(MouseButton button, bool down);
	void OnMouseMove(int x, int y) ;
};

class MyApp :public App {

private:
	float _angle;
	const float _angleInc;

public:

MyWindow  front;

	MyApp();

	void OnIdle();

	float getangle();
};

static MyApp tut13;	

	MyWindow::MyWindow(float cam)  {
		_width = 800; _height = 400;
		SetSize(_width,_height);

		SetDepthBits(24);
		SetPosition(512,512);

		_cameraAngle = cam;
	}

	void MyWindow::OnCreate() {
		// set the projection required
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1.0f, +1.0f, -1.0f, +1.0f, 1.0f, +10.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glEnable(GL_DEPTH_TEST);

		// set the background clear colour to black
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		// set the shade model to smooth (Gouraud shading)
		glShadeModel(GL_SMOOTH);

		// remove back faces
		glEnable(GL_CULL_FACE);

		_material1.create(Color::black(), Color(0.8f,0.8f,0.8f,1.0f));
		_material2.create(Color::black(), Color(0.7f,0.7f,0.7f,1.0f));
		_material3.create(Color::black(), Color::black(), Color::red());

		// setup some lights (ambient is turned off on all lights)
		_light1.create(0, Color::black(), Color(0.5f,0.5f,0.5f,1.0f)); 
		_light2.create(1, Color::black(), Color(0.5f,0.5f,0.5f,1.0f)); 
		_light3.create(2, Color::black(), Color(0.5f,0.0f,0.0f,1.0f));

		// turn the global ambient off by setting it to zero
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Color::black().rgba());

		// Turn on the light
		_light1.apply();
		_light2.apply();
		_light3.apply();

		// setup the two spheres
		_sphere1.create(0.1f, 10, 10);
		_sphere2.create(1.0f, 20, 20);

		_cameraPosition = -5.0;
		_cameraRotation = 0.0;
		glEnable(GL_NORMALIZE);
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

	void MyWindow::drawscene(float angle, float cameraRotation) {
		glPushMatrix();
			glTranslatef(0.0,0.0,_cameraPosition);
			glRotatef(_cameraAngle, 1.0,0.0,0.0);
			glRotatef(cameraRotation, 0.0, 1.0, 0.0);
			_light1.setPosition(Vector4f(1.0,2.0,3.0,1.0));
			_light2.setPosition(Vector4f(-1.0,2.0,3.0,1.0));

			glPushMatrix();
				glRotatef(-4*angle, 0.0, 1.0, 0.0);
				_light3.setPosition(Vector4f(0.0,2.0,-3.0,1.0));
				glTranslatef(0.0,2.0,-3.0);
				_material3.apply();
				_sphere1.draw();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0f, 0.5f, 0.0f);
				glRotatef(angle, 0.0, 1.0, 0.0);
				_material1.apply();
				_sphere2.draw();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0f, -0.8f, 0.0f);
				_material2.apply();
				floor();
			glPopMatrix();
		glPopMatrix();
	}

	void MyWindow::OnDisplay() {

		static unsigned int id=Printf("");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float angle = tut13.getangle();

		// front viewport
		glViewport(0,0,_width/2,_height);
		glDisable(GL_LIGHTING);
		glColor3f(1.0f,0.0f,0.0f);
		glRasterPos3f(-0.1f,-0.9f, -1.1f);

		Printf("Front");
		glEnable(GL_LIGHTING);
		drawscene(angle, _cameraRotation);

		// back viewport
		glViewport(_width/2,0,_width/2,_height);
		glDisable(GL_LIGHTING);
		glColor3f(0.0f,1.0f,0.0f);
		glRasterPos3f(-0.1f,-0.9f, -1.1f);
		Printf("Back");

		glEnable(GL_LIGHTING);
		drawscene(angle, _cameraRotation+180.0f);

		SwapBuffers();
	}

	// When nothing else is happening OnIdle() is called.  In this case, the 
	// inclusion Redraw() makes sure that the window is then updated, which 
	// causes OnDisplay() to be called
	void MyWindow::OnIdle() {
		Redraw();
	}

	void MyWindow::OnResize(int w, int h) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-(float)w/(2*h), (float)w/(2*h), -1.0f, 1.0f, 1.0f, +10.0f);
		glMatrixMode(GL_MODELVIEW);
		_width = w; _height = h;
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

	MyApp::MyApp() : _angleInc(30), front(30) {
		_angle = 0;
	}

	void MyApp::OnIdle() {
		float deltatime = (float)App::GetDeltaTime();
		_angle += _angleInc * deltatime;

		if(_angle > 360.0f) 
			_angle -=360.0f;

	}

	float MyApp::getangle() {
		return _angle;
	}
