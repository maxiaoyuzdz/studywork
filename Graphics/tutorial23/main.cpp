#include "GXBase.h"
#include <math.h>
using namespace gxbase;


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

	const float& operator[](int i) const {
		return _xyzw[i];
	}

	float& operator[](int i) {
		return _xyzw[i];
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
	Vector4f _position, _direction;
	GLfloat _cutoff;
	GLfloat _exponent;

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

	void setDirection(const Vector4f &direction) {
		_direction = direction;
		glLightfv(GL_LIGHT0+_lightNumber, GL_SPOT_DIRECTION, _direction.xyzw());
	}

	void setSpot(const GLfloat &cutoff, const GLfloat &exponent) {
		_cutoff = cutoff;
		_exponent = exponent;
		glLightf(GL_LIGHT0+_lightNumber,GL_SPOT_CUTOFF, cutoff);
		glLightf(GL_LIGHT0+_lightNumber,GL_SPOT_EXPONENT, exponent);
	}

	void apply() {
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0 + _lightNumber);
	}

	const float& operator[](int i) const {
		return _position[i];
	}

	float& operator[](int i) {
		return _position[i];
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

	void create(GLfloat radius, GLuint slices, GLuint stacks, bool texture) {
		_obj = gluNewQuadric();
		gluQuadricNormals(_obj, GLU_SMOOTH);
		_radius = radius;
		_slices = slices;
		_stacks = stacks;
		gluQuadricTexture(_obj, texture);
	}


	void draw() const {
		if (_obj)
			gluSphere(_obj, _radius, _slices, _stacks);
	}
};

class terrain {
private:
	Image _heightfield;
	float (*_vertexarray)[3];
	float (*_normalarray)[3];
	GLuint *_indexarray;
	float (*_texarray)[2];
	int _width, _height;
public:
	terrain() {
	}

	~terrain() {
		delete [] _vertexarray;
		delete [] _normalarray;
		delete [] _indexarray;
		delete [] _texarray;
	}

	void OnCreate() {
		int bitsperpixel;
		unsigned char* rowpointer;
		int vertex_index;
		int current_vertex;

		_heightfield.Load("ground.bmp");


		// now need to build the vertex array
		// first some basic information about the image
		_height =_heightfield.Height();
		_width = _heightfield.Width();
		bitsperpixel = _heightfield.GetPixelSize();
		_vertexarray = new float[_width*_height][3];
		_normalarray = new float[_width*_height][3];
		_indexarray = new GLuint[_width*_height*2];
		_texarray = new float[_width*_height][2];

		// now need to produce the vertexarray from this
		vertex_index = 0;
		for(int j=0;j<_height;j++) {
			rowpointer =_heightfield.GetRowData(j);
			for(int i = 0; i <_width; i++) {
				_texarray[vertex_index][0] = (float)i/(_width-1);
				_texarray[vertex_index][1] = (float)j/(_height-1);
				_vertexarray[vertex_index][0] = -2.0f + 4.0f*_texarray[vertex_index][0];
				_vertexarray[vertex_index][1] =  -2.0f + 4.0f*_texarray[vertex_index][1];
				_vertexarray[vertex_index][2] =  (float)rowpointer[i*bitsperpixel]/(255.0f*4.0f);
				vertex_index++;

			};
		};

		// need to generate the index array
		vertex_index = 0;
		for(int j=0;j<_height-1;j++) {
			for(int i = 0; i<_width;i++) {
				current_vertex = j*_width+i;
				_indexarray[vertex_index++] = current_vertex + _width;
				_indexarray[vertex_index++] = current_vertex;
			};
		};

		// now need to generate normals for the terrain
		// this is not that simple
		_gen_normals();
		_heightfield.Free();
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, _normalarray);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _vertexarray);
		glTexCoordPointer(2, GL_FLOAT, 0, _texarray);
	}

	void draw() {
		for(int j=0;j<_height-1;j++) {
			glDrawElements(GL_TRIANGLE_STRIP, _width*2, GL_UNSIGNED_INT, &_indexarray[j*_width*2]);
		}
	}

	void normal(bool normon) {
		if (normon) {
			for(int j=0;j<_height*_width;j++) {
				glBegin(GL_LINES);
					glVertex3f(_vertexarray[j][0],_vertexarray[j][1],_vertexarray[j][2]);
					glVertex3f(_vertexarray[j][0]+0.1f*_normalarray[j][0],_vertexarray[j][1]+0.1f*_normalarray[j][1],_vertexarray[j][2]+0.1f*_normalarray[j][2]);
				glEnd();
			};
		};
	}
private:
	void _gen_normals() {
		int vertex_index;

		vertex_index = 0;
		_normalarray[vertex_index][0] = -_vertexarray[vertex_index][2];
		_normalarray[vertex_index][1] = -_vertexarray[vertex_index+_width][2];
		_normalarray[vertex_index][2] = 8.0f/(_width-1);
		vertex_index++;
		for(int i = 1; i<_width-1;i++) {
			_normalarray[vertex_index][0] = _vertexarray[vertex_index-1][2]-_vertexarray[vertex_index+1][2];
			_normalarray[vertex_index][1] = -_vertexarray[vertex_index+_width][2];
			_normalarray[vertex_index][2] = 8.0f/(_width-1);
			vertex_index++;
		};
		_normalarray[vertex_index][0] = _vertexarray[vertex_index-1][2];
		_normalarray[vertex_index][1] = -_vertexarray[vertex_index+_width][2];
		_normalarray[vertex_index][2] = 8.0f/(_width-1);
		vertex_index++;

		for(int j=1;j<_height-1;j++) {
			_normalarray[vertex_index][0] = -_vertexarray[vertex_index][2];
			_normalarray[vertex_index][1] = -_vertexarray[vertex_index+_width][2];
			_normalarray[vertex_index][2] = 8.0f/(_width-1);
			vertex_index++;
			for(int i=1;i<_width-1;i++) {
				_normalarray[vertex_index][0] = _vertexarray[vertex_index-1][2]-_vertexarray[vertex_index+1][2];
				_normalarray[vertex_index][1] = _vertexarray[vertex_index-_width][2]-_vertexarray[vertex_index+_width][2];
				_normalarray[vertex_index][2] = 8.0f/(_width-1);
				vertex_index++;
			}
			_normalarray[vertex_index][0] = _vertexarray[vertex_index-1][2];
			_normalarray[vertex_index][1] = -_vertexarray[vertex_index+_width][2];
			_normalarray[vertex_index][2] = 8.0f/(_width-1);
			vertex_index++;
		}
		_normalarray[vertex_index][0] = -_vertexarray[vertex_index][2];
		_normalarray[vertex_index][1] = _vertexarray[vertex_index-_width][2];
		_normalarray[vertex_index][2] = 8.0f/(_width-1);
		vertex_index++;
		for(int i = 1; i<_width-1;i++) {
			_normalarray[vertex_index][0] = _vertexarray[vertex_index-1][2]-_vertexarray[vertex_index+1][2];
			_normalarray[vertex_index][1] = _vertexarray[vertex_index-_width][2];
			_normalarray[vertex_index][2] = 8.0f/(_width-1);
			vertex_index++;
		};
		_normalarray[vertex_index][0] = _vertexarray[vertex_index-1][2];
		_normalarray[vertex_index][1] = -_vertexarray[vertex_index-_width][2];
		_normalarray[vertex_index][2] = 8.0f/(_width-1);

		// make normals unit
		_normalize();

	}

	void _normalize() {
		float temp;

		for(int j=0;j<_height*_width;j++) {
			temp = _normalarray[j][0]*_normalarray[j][0]+_normalarray[j][1]*_normalarray[j][1]+_normalarray[j][2]*_normalarray[j][2];
			temp = sqrt(temp);
			_normalarray[j][0] /= temp;_normalarray[j][1] /= temp;_normalarray[j][2] /= temp;
		};
	}

};

	
void Aeroplane()
{
	glDisable(GL_CULL_FACE);
	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,0.0f,-0.1f);
		glVertex3f(0.0f,0.0f,+0.1f);
		glVertex3f(0.2f,0.0f,0.0f);
		glNormal3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.2f, 0.0f, 0.0f);
		glVertex3f(0.0f,0.1f, 0.0f);
	glEnd();
	glEnable(GL_CULL_FACE);
};




class MyWindow :public GLWindow {
private:
	// OpenGL objects
	Lights _light1, _light2, _light3, _spotlight;
	Materials _material1, _material2, _material3;
	Sphere _sphere1;

	// Simulation data
	const float _angleInc;
	float _angle;
	float _cameraAngle, _cameraPosition, _cameraRotation;
	bool _leftDown, _rightDown, _fullscreen, _normals;
	Image _project, _texturemap;
	GLuint _texture, _projector;
	terrain _terra;
	Vector4f _PS, _PT, _PR, _PQ;
	Vector4f _planepos;

public:
	MyWindow() : _angleInc(30) {
		SetSize(512,512);
		SetDepthBits(24);

		_angle = 0.0f;
	}



void init_project()
{
	_PS.Assign(1.0f,0.0f,0.0f,0.0f);
	_PT.Assign(0.0f,1.0f,0.0f,0.0f);
	_PR.Assign(0.0f,0.0f,1.0f,0.0f);
	_PQ.Assign(0.0f,0.0f,0.0f,1.0f);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	// First scale and bias into [0..1] range.
	glTranslatef(0.5, 0.5, 0);
	glScalef(0.5, 0.5, 1);
	gluPerspective(30, 1, 0.1, 1);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

}


	void OnCreate() {

		// clear window first: it might take a moment before image loads
		glClear(GL_COLOR_BUFFER_BIT);
		SwapBuffers();


		// load ground texture
		_texturemap.Load("terrain.bmp");
		glGenTextures(1, &_texture);

		// build 2D mip-maps from image
		glBindTexture(GL_TEXTURE_2D, _texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		_texturemap.gluBuild2DMipmaps();
		_texturemap.Free();

		// load projected image (light)
		_project.Load("spotlight.bmp");
		glGenTextures(1, &_projector);
		glBindTexture(GL_TEXTURE_2D, _projector);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		_project.glTexImage2D();
		_project.Free();

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
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_BLEND);

		// set the background clear colour to black
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		// set the shade model to smooth (Gouraud shading)
		glShadeModel(GL_SMOOTH);

		// remove back faces
		glEnable(GL_CULL_FACE);

		_material1.create(Color::black(), Color(0.5f,0.5f,0.5f,1.0f));
		_material2.create(Color::black(), Color::green());
		_material3.create(Color::black(), Color::black(), Color::yellow());

		// setup some lights (ambient is turned off on all lights)
		_light1.create(0, Color::black(), Color(0.6f,0.6f,0.6f,1.0f)); 
		_light2.create(1, Color::black(), Color(0.6f,0.6f,0.6f,1.0f)); 
		_light3.create(2, Color::black(), Color(0.5f,0.5f,0.0f,1.0f));
		_spotlight.create(3, Color::black(), Color(1.0f,0.0f,0.0f,1.0f));
		_spotlight.setSpot(30.0f,100.0f);

		// turn the global ambient off by setting it to zero
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Color::black().rgba());

		_light3.setPosition(Vector4f(0.0,5.0,-3.0,1.0));
		// Turn on the lights
		_light1.apply();
		_light2.apply();
		_light3.apply();
		_spotlight.apply();

		// setup the two spheres
		_sphere1.create(0.1f, 10, 10, false);

		_cameraAngle = 30.0;
		_cameraPosition = -5.0;
		_cameraRotation = 0.0;
		_fullscreen = false;
		_normals  = false;
		_planepos.Assign(0.0f,2.0f,0.0f, 1.0f);
		init_project();

	}

	void floor() const
	{
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-2.0f,0.0f,2.0f);
		glVertex3f(2.0f,0.0f,2.0f);
		glVertex3f(2.0f,0.0f,-2.0f);
		glVertex3f(-2.0f,0.0f,-2.0f);
		glEnd();
	}


	void OnDisplay() {


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

			glBlendFunc(GL_ONE, GL_ZERO);
			glPushMatrix();
				_light3.setPosition(Vector4f(_light3[0],_light3[1],_light3[2],1.0));
				_spotlight.setPosition(Vector4f(_planepos[0],_planepos[1],_planepos[2], 1.0f));
				_spotlight.setDirection(Vector4f(1.0f,-4.0f,0.0f, 0.0f));
				glTranslatef(_light3[0],_light3[1],_light3[2]);	
				_material3.apply();
				_sphere1.draw();
			glPopMatrix();

			glPushMatrix();
				_material2.apply();
				glTranslatef(_planepos[0],_planepos[1],_planepos[2]);
				Aeroplane();
			glPopMatrix();

			
			glBindTexture(GL_TEXTURE_2D, _texture);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
				glTranslatef(0.0f, 0.5f, 0.0f);
				glRotatef(-90.0f,1.0,0.0,0.0);
				_material1.apply();
				_terra.draw();
				_material2.apply();
				_terra.normal(_normals);
			glPopMatrix();
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_TEXTURE_2D);

			glDisable(GL_LIGHTING);
			glBlendFunc(GL_DST_COLOR, GL_ONE);
			glBindTexture(GL_TEXTURE_2D, _projector);

			glTexGenfv(GL_S, GL_EYE_PLANE, _PS.xyzw());
			glTexGenfv(GL_T, GL_EYE_PLANE, _PT.xyzw());
			glTexGenfv(GL_R, GL_EYE_PLANE, _PR.xyzw());
			glTexGenfv(GL_Q, GL_EYE_PLANE, _PQ.xyzw());

			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_GEN_R);
			glEnable(GL_TEXTURE_GEN_Q);
			glEnable(GL_TEXTURE_2D);

			glMatrixMode(GL_TEXTURE);
			glPopMatrix();
			glPushMatrix();
				gluLookAt(_planepos[0], _planepos[1], _planepos[2], _planepos[0]-1.0f, _planepos[1]-4.0f, _planepos[2]-0.0f, 0.0f, 1.0f, 0.0f); 
			glMatrixMode(GL_MODELVIEW);

			glDepthMask(false);
			glPushMatrix();
				glTranslatef(0.0f, 0.5f, 0.0f);
				glRotatef(-90.0f,1.0,0.0,0.0);
				_material1.apply();
				_terra.draw();
				_material2.apply();
				_terra.normal(_normals);
			glPopMatrix();
			glDepthMask(true);

			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_GEN_R);
			glDisable(GL_TEXTURE_GEN_Q);

			glMatrixMode(GL_TEXTURE);
				glLoadIdentity();
			glMatrixMode(GL_MODELVIEW);
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_LIGHTING);

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
			case 'm':
				_light3[0]+=0.1f;
				break;
			case 'n':
				_light3[0]-=0.1f;
				break;
			case 'p':
				_light3[2]-=0.1f;
				break;
			case 'l':
				_light3[2]+=0.1f;
				break;
			case '2':
				_light3[1]+=0.1f;
				break;
			case '1':
				_light3[1]-=0.1f;
				break;
			case 'd':
				_planepos[0] += 0.1f;
				break;
			case 's':
				_planepos[0] -= 0.1f;
				break;
			case '9':
				_normals = !_normals;
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
static MyApp tut23;
