#include "GXBase.h"
#include <math.h>
#define PI  (float)3.1415926

using namespace gxbase;

// This example draws two windows, a perspective view and a plan view
// You can control the camera in both views



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

class MySphere {
private:
	float (*_vertexarray)[3];	// contains the vertices
	float (*_normalarray)[3];	// contains the normals to each vertex
	GLuint *_indexarray;		// index array that defines the polygons
	float (*_texarray)[2];		// texture coordinates for each vertex
	int _stacks, _slices;

public:
	MySphere() {
	}

	~MySphere() {
		delete [] _vertexarray;
		delete [] _normalarray;
		delete [] _indexarray;
		delete [] _texarray;
	}

	bool create(GLfloat radius, int slices, int stacks, bool texture) {
		int array_size;
		float stack_inc;
		float slice_inc;
		float x, y , z;
		int vertex_count;
		int index_count;
		int temp_vc;
		float temp_tex;
		float temp_rad;

		_stacks = stacks;
		_slices = slices;


		array_size = (slices+1)*(stacks-1)+2;	// +2 is for the top and bottom vertex

		_vertexarray = new float[array_size][3];
		_normalarray = new float[array_size][3];
		_indexarray = new GLuint[2+(stacks-1)*(slices+1)*2];
		_texarray = new float[array_size][2];

		if ((stacks < 2) & (slices <2)) return false;

		stack_inc = 1.0f/(float)stacks;
		slice_inc = PI*2.0f/slices;

		// define the vertex array

		// top point
		vertex_count = 0;
		_vertexarray[vertex_count][0] = 0.0f; 
		_vertexarray[vertex_count][1] = radius; 
		_vertexarray[vertex_count][2] = 0.0f; 

		_normalarray[vertex_count][0] = 0.0f; 
		_normalarray[vertex_count][1] = 1.0f; 
		_normalarray[vertex_count][2] = 0.0f;

		_texarray[vertex_count][0] = 0; 
		_texarray[vertex_count++][1] = 1; 

		// bottom point
		_vertexarray[vertex_count][0] = 0.0f; 
		_vertexarray[vertex_count][1] = -radius; 
		_vertexarray[vertex_count][2] = 0.0f;

		_normalarray[vertex_count][0] = 0.0f; 
		_normalarray[vertex_count][1] = -1.0f; 
		_normalarray[vertex_count][2] = 0.0f;

		_texarray[vertex_count][0] = 0; 
		_texarray[vertex_count++][1] = 0; 


		for (int i = 1; i < stacks; i++) {
			y = sin(PI*(1/2.0f - stack_inc*(float)i));
			temp_rad = cos(PI*(1/2.0f - stack_inc*(float)i));
			temp_vc = vertex_count;
			temp_tex = 1.0f - stack_inc*(float)i;
			for(int j = 0; j < slices; j++) {
				x = cos((float)j*slice_inc); 
				z = -sin((float)j*slice_inc);  
				_vertexarray[vertex_count][0] = radius*temp_rad*x;
				_vertexarray[vertex_count][1] = radius*y;
				_vertexarray[vertex_count][2] = radius*temp_rad*z;
				_normalarray[vertex_count][0] = temp_rad*x;
				_normalarray[vertex_count][1] = y;
				_normalarray[vertex_count][2] = temp_rad*z;
				_texarray[vertex_count][0] = (float)j/(float)slices;
				_texarray[vertex_count++][1] = temp_tex;
			};
			_vertexarray[vertex_count][0] = _vertexarray[temp_vc][0];
			_vertexarray[vertex_count][1] = _vertexarray[temp_vc][1];
			_vertexarray[vertex_count][2] = _vertexarray[temp_vc][2];
			_normalarray[vertex_count][0] = _normalarray[temp_vc][0];
			_normalarray[vertex_count][1] = _normalarray[temp_vc][1];
			_normalarray[vertex_count][2] = _normalarray[temp_vc][2];
			_texarray[vertex_count][0] = 1;
			_texarray[vertex_count++][1] = temp_tex;
		};

		// now generate the index array
		// start with triangle fans for the top
		index_count = 0;
		vertex_count =2;
		_indexarray[index_count++] = 0; // very top vertex
		for(int j = 0; j<= slices; j++) {
			_indexarray[index_count++] = vertex_count++;
		};
		vertex_count -= (slices+1);
		// now do the main strips
		for(int i = 0; i< (stacks-2); i++) {
			for(int j = 0; j<= slices; j++) {
				_indexarray[index_count++] = vertex_count++;
				_indexarray[index_count++] = slices+vertex_count;
			};
		};

		_indexarray[index_count++] = 1; // very bottom vertex
		for(int j = 0; j<= slices; j++) {
			_indexarray[index_count++] = vertex_count+slices-j;
		};

		return true;
	}

	void draw() {

		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, _normalarray);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _vertexarray);


		glDrawElements(GL_TRIANGLE_FAN, _slices+2, GL_UNSIGNED_INT, &_indexarray[0]);
		for (int i = 0; i < (_stacks-2); i++) { 
			glDrawElements(GL_TRIANGLE_STRIP, (_slices+1)*2, GL_UNSIGNED_INT, &_indexarray[_slices+2+i*(_slices+1)*2]);
		};
		glDrawElements(GL_TRIANGLE_FAN, _slices+2, GL_UNSIGNED_INT, &_indexarray[_slices+2+(_stacks-2)*(_slices+1)*2]);

		glDisableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, _normalarray);
		glDisableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _vertexarray);

	}
};



class MyWindow :public GLWindow {
private:
	// OpenGL objects
	Lights _light1, _light2;
	Materials _sun_material, _earth_material, _moon_material;
	MySphere _sun, _earth, _moon;

	const float _earth_sun, _moon_earth;

	float _cameraAngle, _cameraPosition, _cameraRotation;
	bool _leftDown, _rightDown;


public:
	MyWindow(float cam);
	void OnCreate();
	void floor() const;
	void OnDisplay();
	void OnIdle();
	void OnResize(int w, int h);
	void OnKeyboard(int key, bool down);
	void OnMouseButton(MouseButton button, bool down);
	void OnMouseMove(int x, int y) ;
};

class MyApp :public App {

private:
	const float _sun_angle_inc, _earth_angle_inc, _moon_angle_inc;
	const float _earth_sun_angle_inc, _moon_earth_angle_inc;
	float _sun_angle, _earth_angle, _moon_angle;
	float _earth_sun_angle, _moon_earth_angle;

public:

MyWindow front;

	MyApp();

	void OnIdle();

	float MyApp::get_sun();
	float MyApp::get_earth();
	float MyApp::get_moon();
	float MyApp::get_earth_sun();
	float MyApp::get_moon_earth();
};

static MyApp tut14;	

MyWindow::MyWindow(float cam) :  _earth_sun(3), _moon_earth(0.5) {
		SetSize(512,512);
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

		glViewport(0,0, Width(), Height());
		glEnable(GL_DEPTH_TEST);

		// set the background clear colour to black
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		// set the shade model to smooth (Gouraud shading)
		glShadeModel(GL_SMOOTH);

		// remove back faces
		glEnable(GL_CULL_FACE);

		_sun_material.create(Color::black(), Color(0.8f,0.8f,0.0f,1.0f), Color(0.3f,0.3f,0.0f,1.0f));
		_earth_material.create(Color::black(), Color(0.0f,0.0f,0.8f,1.0f));
		_moon_material.create(Color::black(), Color(0.5f,0.5f,0.5f,1.0f));

		// setup some lights (ambient is turned off on all lights)
		_light1.create(0, Color::black(), Color(0.5f,0.5f,0.5f,1.0f)); 
		_light2.create(1, Color::black(), Color(0.5f,0.5f,0.5f,1.0f)); 

		// turn the global ambient off by setting it to zero
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Color::black().rgba());

		// Turn on the light
		_light1.apply();
		_light2.apply();

		// setup the two spheres
		_sun.create(1.0f, 20, 20, false);
		_earth.create(0.3f, 5, 5, false);
		_moon.create(0.1f, 5, 5, false);

		_cameraPosition = -5.0;
		_cameraRotation = 0.0;

	}


	void MyWindow::OnDisplay() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPushMatrix();
			//move on z
			glTranslatef(0.0,0.0,_cameraPosition);
			//rotate on x
			glRotatef(_cameraAngle, 1.0,0.0,0.0);
			//rotate on y
			glRotatef(_cameraRotation, 0.0, 1.0, 0.0);
			//lighting
			_light1.setPosition(Vector4f(2.0,2.0,4.0,1.0));
			_light2.setPosition(Vector4f(-2.0,2.0,4.0,1.0));

			//////////////////////////////////////////////////////////////////////////
			// draw sun
			glPushMatrix();
				glRotatef(tut14.get_sun(),0.0f,1.0f,0.0f);
				_sun_material.apply();
				_sun.draw();
			glPopMatrix();
			//////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////// 
			////////////////////////////////////////////////////////////////////////// 
			////////////////////////////////////////////////////////////////////////// 
			glPushMatrix();
			//from here the coordinate is change to earth
			// place earth system in orbit
			glRotatef(tut14.get_earth_sun(),0.0f,1.0f,0.0f);
			glTranslatef(_earth_sun,0.0f,0.0f);
			// to earth
			//////////////////////////////////////////////////////////////////////////
			// draw rotating earth
			glPushMatrix();
				//base on earth system, ratate
				glRotatef(tut14.get_earth(),0.0f,1.0f,0.0f);
				_earth_material.apply();
				_earth.draw();
			glPopMatrix();

			// translate moon away from earth
			glRotatef(tut14.get_moon_earth(),0.0f,1.0f,0.0f);
			glTranslatef(_moon_earth,0.0f,0.0f);
			glRotatef(tut14.get_moon(),0.0f,1.0f,0.0f);
			_moon_material.apply();
			_moon.draw();
			//////////////////////////////////////////////////////////////////////////
			glPopMatrix();
			//////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////// 
			////////////////////////////////////////////////////////////////////////// 
			////////////////////////////////////////////////////////////////////////// 



			////////////////////////////////////////////////////////////////////////// 
			glPushMatrix();
			//from here the coordinate is change to earth
			// place earth system in orbit
			glRotatef(-tut14.get_earth_sun(),0.0f,1.0f,0.0f);
			glTranslatef(_earth_sun/2,0.0f,0.0f);
			// to earth
			//////////////////////////////////////////////////////////////////////////
			// draw rotating earth
			glPushMatrix();
			//base on earth system, ratate
			glRotatef(tut14.get_earth(),0.0f,1.0f,0.0f);
			_earth_material.apply();
			_earth.draw();
			glPopMatrix();

			// translate moon away from earth
			glRotatef(tut14.get_moon_earth(),0.0f,1.0f,0.0f);
			glTranslatef(_moon_earth,0.0f,0.0f);
			glRotatef(tut14.get_moon(),0.0f,1.0f,0.0f);
			_moon_material.apply();
			_moon.draw();
			//////////////////////////////////////////////////////////////////////////
			glPopMatrix();
			//////////////////////////////////////////////////////////////////////////
		glPopMatrix();

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

	MyApp::MyApp() : _sun_angle_inc(10), _earth_angle_inc(30), _moon_angle_inc(30), _earth_sun_angle_inc(60),
					 _moon_earth_angle_inc(480), front(30) {

		_sun_angle = _earth_angle = _moon_angle = 0.0f;
		_earth_sun_angle = _moon_earth_angle = 0.0f;
	}

	void MyApp::OnIdle() {
		float deltatime = (float)App::GetDeltaTime();
		_sun_angle += _sun_angle_inc * deltatime;
		_earth_angle += _earth_angle_inc * deltatime;
		_moon_angle += _moon_angle_inc * deltatime;
		_earth_sun_angle += _earth_sun_angle_inc * deltatime;
		_moon_earth_angle += _moon_earth_angle_inc * deltatime;

		if (_sun_angle > 360.0) _sun_angle -= 360.0;
		if (_earth_angle > 360.0) _earth_angle -= 360.0;
		if (_moon_angle > 360.0) _moon_angle -= 360.0;
		if (_earth_sun_angle > 360.0) _earth_sun_angle -= 360.0;
		if (_moon_earth_angle > 360.0) _moon_earth_angle -= 360.0;

	}

	float MyApp::get_sun() {
		return _sun_angle;
	}
	float MyApp::get_earth() {
		return _earth_angle;
	}
	float MyApp::get_moon() {
		return _moon_angle;
	}
	float MyApp::get_earth_sun() {
		return _earth_sun_angle;
	}
	float MyApp::get_moon_earth() {
		return _moon_earth_angle;
	}