#include "GXBase.h"
#include <math.h>
#define PI  (float)3.1415926
using namespace gxbase;

// this is a simple example: it creates one window,
// and draws a rotating sphere with hidden surface removal

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

	static Color yellow() {
		return Color(1.0, 1.0, 0.0, 1.0);
	}

	static Color null() {
		return Color(0.0, 0.0, 0.0, 0.0);
	}
};

class MySphere {
private:
	float (*_vertexarray)[3];	// contains the vertices
	float (*_normalarray)[3];	// contains the normals to each vertex
	GLuint *_indexarray;		// index array that defines the polygons
	float *_texarray;			// texture coordinate for each vertex
	int _stacks, _slices;
	int _array_size;

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

		float stack_inc;
		float slice_inc;
		float x, y , z;
		int vertex_count;
		int index_count;
		int temp_vc;
		float temp_rad;

		_stacks = stacks;
		_slices = slices;


		_array_size = (slices+1)*(stacks-1)+2;	// +2 is for the top and bottom vertex

		_vertexarray = new float[_array_size][3];
		_normalarray = new float[_array_size][3];
		_indexarray = new GLuint[2+(stacks-1)*(slices+1)*2];
		_texarray = new float[_array_size];

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
		_normalarray[vertex_count++][2] = 0.0f;

		// bottom point
		_vertexarray[vertex_count][0] = 0.0f; 
		_vertexarray[vertex_count][1] = -radius; 
		_vertexarray[vertex_count][2] = 0.0f;

		_normalarray[vertex_count][0] = 0.0f; 
		_normalarray[vertex_count][1] = -1.0f; 
		_normalarray[vertex_count++][2] = 0.0f;


		for (int i = 1; i < stacks; i++) {
			y = sin(PI*(1/2.0f - stack_inc*(float)i));
			temp_rad = cos(PI*(1/2.0f - stack_inc*(float)i));
			temp_vc = vertex_count;
			for(int j = 0; j < slices; j++) {
				x = cos((float)j*slice_inc); 
				z = -sin((float)j*slice_inc);  
				_vertexarray[vertex_count][0] = radius*temp_rad*x;
				_vertexarray[vertex_count][1] = radius*y;
				_vertexarray[vertex_count][2] = radius*temp_rad*z;
				_normalarray[vertex_count][0] = temp_rad*x;
				_normalarray[vertex_count][1] = y;
				_normalarray[vertex_count++][2] = temp_rad*z;
			};
			_vertexarray[vertex_count][0] = _vertexarray[temp_vc][0];
			_vertexarray[vertex_count][1] = _vertexarray[temp_vc][1];
			_vertexarray[vertex_count][2] = _vertexarray[temp_vc][2];
			_normalarray[vertex_count][0] = _normalarray[temp_vc][0];
			_normalarray[vertex_count][1] = _normalarray[temp_vc][1];
			_normalarray[vertex_count++][2] = _normalarray[temp_vc][2];
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


	void calctex(float mat[], float light[]) {
		float lightpos[3], lightdir[3];
	
		// now need to apply the matrix to the light position
		// should write a matrix class but it isn't really needed
		lightpos[0] = mat[0]*light[0] + mat[4]*light[1] + mat[8]*light[2] + mat[12];
		lightpos[1] = mat[1]*light[0] + mat[5]*light[1] + mat[9]*light[2] + mat[13];
		lightpos[2] = mat[2]*light[0] + mat[6]*light[1] + mat[10]*light[2] + mat[14];
		// now make it into a unit vector

		for (int i = 0; i<_array_size; i++) {
			lightdir[0] = lightpos[0] - _vertexarray[i][0];
			lightdir[1] = lightpos[1] - _vertexarray[i][1];
			lightdir[2] = lightpos[2] - _vertexarray[i][2];

			float tempvec = sqrt(lightdir[0]*lightdir[0]+lightdir[1]*lightdir[1]+lightdir[2]*lightdir[2]);
			lightdir[0] /= tempvec;
			lightdir[1] /= tempvec;
			lightdir[2] /= tempvec;
			// now calculate the values for the texture array
			float t = lightdir[0]*_normalarray[i][0]+lightdir[1]*_normalarray[i][1]+lightdir[2]*_normalarray[i][2];
			if (t > 0.0f) 
				_texarray[i] = t;
			else
				_texarray[i] = 0;
		}
	}


	void draw() {

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(1, GL_FLOAT, 0, _texarray);
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, _normalarray);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _vertexarray);


		glDrawElements(GL_TRIANGLE_FAN, _slices+2, GL_UNSIGNED_INT, &_indexarray[0]);
		for (int i = 0; i < (_stacks-2); i++) { 
			glDrawElements(GL_TRIANGLE_STRIP, (_slices+1)*2, GL_UNSIGNED_INT, &_indexarray[_slices+2+i*(_slices+1)*2]);
		};
		glDrawElements(GL_TRIANGLE_FAN, _slices+2, GL_UNSIGNED_INT, &_indexarray[_slices+2+(_stacks-2)*(_slices+1)*2]);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
};




		


class MyWindow :public GLWindow {
private:
	// OpenGL objects

	MySphere _sphere;

	// Simulation data
	const float _angleInc;
	float _angle;
	float _cameraAngle, _cameraPosition, _cameraRotation;
	bool _leftDown, _rightDown, _fullscreen;
	GLuint _intensity;
	float *_lightpos;
public:
	MyWindow() : _angleInc(30) {
		SetSize(512,512);
		SetDepthBits(24);

		_angle = 0.0f;
	}

	void OnCreate() {


		// clear window first: it might take a moment before image loads
		glClear(GL_COLOR_BUFFER_BIT);
		SwapBuffers();

		//GLubyte texval[16]={127, 127, 127, 191, 191, 191, 191, 191, 255, 255, 255, 255, 255, 255, 255, 255};
		GLubyte texval[16]={120, 120, 120, 180, 180, 180, 191, 191, 191, 255, 255, 255, 255, 255, 255, 255};

		glGenTextures(1, &_intensity);
		glBindTexture(GL_TEXTURE_1D, _intensity);
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 16, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texval);

		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);

		// set the projection required
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-0.1f, +0.1f, -0.1f, +0.1f, 0.1f, +10.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glViewport(0,0, Width(), Height());
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		// set the background clear colour to black
		glClearColor(0.0f, 0.8f, 0.0f, 0.0f);
		// set the shade model to smooth (Gouraud shading)
		glShadeModel(GL_SMOOTH);
		// remove back faces
		glEnable(GL_CULL_FACE);
		// setup point size and line width
		glPointSize(10.0f);
		glLineWidth(9.0f);

		// put the light in position
		_lightpos = new float[3];
		_lightpos[0] = 0.0f, _lightpos[1] = 2.5f, _lightpos[2] = 3.0f;
		_sphere.create(1.0f, 30, 30, true);

		// place camera at a starting location
		_cameraAngle = 30.0;
		_cameraPosition = -5.0;
		_cameraRotation = 0.0;
		_fullscreen = false;
	
	}


	void OnDisplay() {

		float iMatrix[16];

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

			glColor3f(1.0f,1.0f,0.0f);

			glBegin(GL_POINTS);
				glVertex3fv(_lightpos);
			glEnd();

			// get the inverse matrix to the one use for moving the object around
			// this will be applied to the light 
			glPushMatrix();
				glLoadIdentity();
				glRotatef(-_angle*2.0f, 0.0, 1.0, 0.0);
				glTranslatef(0.0f,-1.0f,0.0f);
				glGetFloatv(GL_MODELVIEW_MATRIX, iMatrix);
			glPopMatrix();
			

			_sphere.calctex(iMatrix, _lightpos);

			glPushMatrix();
				glTranslatef(0.0f, 1.0f, 0.0f);
				glRotatef(_angle*2.0f, 0.0, 1.0, 0.0);
				glColor3f(0.9f,0.0f,0.0f);
				glEnable(GL_TEXTURE_1D);
				glBindTexture(GL_TEXTURE_1D, _intensity);
				_sphere.draw();
				glDisable(GL_TEXTURE_1D);

				// now draw the outline 
				glCullFace(GL_FRONT);
				glColor3f(0.0f, 0.0f, 0.0f);
				glPolygonMode(GL_BACK, GL_LINE);
				_sphere.draw();
				glPolygonMode(GL_BACK, GL_FILL);
				glCullFace(GL_BACK);
			glPopMatrix();

		glPopMatrix();

		SwapBuffers();
	}

	// When nothing else is happening OnIdle() is called.  In this case, the 
	// inclusion Redraw() makes sure that the window is then updated, which 
	// causes OnDisplay() to be called
	void OnIdle() {
		Redraw();
	}

	void OnResize(int w, int h) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-(float)w/h, (float)w/h, -1.0f, 1.0f, 1.0f, +10.0f);
		glMatrixMode(GL_MODELVIEW);
		glViewport(0,0,w,h);
	}

	void OnKeyboard(int key, bool down) {
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

	void OnMouseButton(MouseButton button, bool down) {
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

	void OnMouseMove(int x, int y) {
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

};


class MyApp :public App {
public:

	MyWindow w;

};

// this is the single instance of our application
//
static MyApp tut24;
