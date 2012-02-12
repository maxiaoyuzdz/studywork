#include "GXBase.h"
#include "image.h"
#include <iostream>
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

	const float& operator[](int i) const {
		return _rgba[i];
	}

	float& operator[](int i) {
		return _rgba[i];
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

	void alphaDiffuse(const float inc) {
		_diffuse[3] += inc;
		if (_diffuse[3] < 0.0f) _diffuse[3] = 0.0f;
		if (_diffuse[3] > 1.0f) _diffuse[3] = 1.0f;
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


class MyWindow :public GLWindowEx {
private:
	// OpenGL objects
	Lights _light1, _light2, _light3, _light4, _light5;
	Materials _material1, _material2, _material3, _green;
	Sphere _sphere1, _sphere2;
	// variables for testing multitextures
	bool   _bHaveMultitex;	// do we have mulitexture support?
	bool   _bMultitex;		// using multitexturing?
	bool   _stencil;		// flag to indicate stencil on/off

	// Simulation data
	const float _angleInc;
	float _angle;
	float _cameraAngle, _cameraPosition, _cameraRotation;
	bool _leftDown, _rightDown, _fullscreen, _begin;
	Image _images[8];
	GLuint _textures[8];

public:
	MyWindow() : _angleInc(30) {
		_bHaveMultitex	= false;	// do we have multitexture support?
		_bMultitex		= false;	// are we using multitexture?

		SetSize(512,512);
		SetDepthBits(24);
		SetStencilBits(16);
		_angle = 0.0f;
		_stencil = false;
	}

	void OnCreate() {


		// important: call base class to load extensions
		GLWindowEx::OnCreate();

		// does this driver support multitexture?
		_bHaveMultitex = glex::Supports( "GL_ARB_multitexture" );
		if (!_bHaveMultitex) {
			// warn the user if multitexture not supported
			App::MsgPrintf("GL_ARB_multitexture NOT found");
		}

		// if it supports multitexture, turn it on
		_bMultitex = _bHaveMultitex;


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
		_images[6].Load("checker3.bmp");
		_images[7].Load("star.bmp");

		glGenTextures(8, &_textures[0]);

		// build 2D mip-maps from image
		for (int i = 0; i<7;i++) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glBindTexture(GL_TEXTURE_2D, _textures[i]);
			_images[i].gluBuild2DMipmaps();
			_images[i].Free();
		};

		// last star texture
		glBindTexture(GL_TEXTURE_2D, _textures[7]);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		_images[7].gluBuild2DMipmaps();
		_images[7].Free();


		// set the projection required
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1.0f, +1.0f, -1.0f, +1.0f, 1.0f, +30.0f);
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

		_material1.create(Color::black(), Color(0.9f,0.9f,0.9f,1.0f));
		_material2.create(Color::black(), Color(0.7f,0.7f,0.7f,0.5f));
		_material3.create(Color::black(), Color::black(), Color::yellow());
		_green.create(Color::black(), Color::green());

		// setup some lights (ambient is turned off on all lights)
		_light1.create(0, Color::black(), Color(0.5f,0.5f,0.5f,1.0f)); 
		_light2.create(1, Color::black(), Color(0.5f,0.5f,0.5f,1.0f)); 
		_light3.create(2, Color::black(), Color(0.5f,0.5f,0.0f,1.0f));
		_light4.create(3, Color::black(), Color(0.5f,0.5f,0.5f,1.0f)); 
		_light5.create(4, Color::black(), Color(0.5f,0.5f,0.5f,1.0f)); 


		// turn the global ambient off by setting it to zero
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Color::black().rgba());

		_light3.setPosition(Vector4f(0.0,5.0,-3.0,1.0));
		// Turn on the lights
		_light1.apply();
		_light2.apply();
		_light3.apply();
		_light4.apply();
		_light5.apply();

		// setup the two spheres
		_sphere1.create(0.1f, 10, 10, false);
		_sphere2.create(1.0f, 20, 20, true);

		_cameraAngle = 15.0;
		_cameraPosition = -5.0;
		_cameraRotation = 0.0;
		_fullscreen = false;

	}

	void floor()
	{

		//activate texture unit 0 and bind the 'Star' texture to it, and enable it
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, _textures[6]);
		glEnable(GL_TEXTURE_2D);

        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glTranslatef(0.5f, 0.5f, 0.0f);
        glRotatef(_angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(-0.5f, -0.5f, 0.0f);
        glMatrixMode(GL_MODELVIEW);

		
		//activate texture unit 2 and bind the 'checker' texture to it, and enable it
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, _textures[7]);
		glEnable(GL_TEXTURE_2D);

        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glTranslatef(0.5f, 0.5f, 0.0f);
        glRotatef(-_angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(-0.5f, -0.5f, 0.0f);
        glMatrixMode(GL_MODELVIEW);



		glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);

		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0);
		glVertex3f(-10.0f,0.0f,10.0f);

		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0);
		glVertex3f(10.0f,0.0f,10.0f);

		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1);
		glVertex3f(10.0f,0.0f,-10.0f);

		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1);	
		glVertex3f(-10.0f,0.0f,-10.0f);
		glEnd();

		glActiveTextureARB(GL_TEXTURE1_ARB);
		glDisable(GL_TEXTURE_2D);
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glDisable(GL_TEXTURE_2D);


        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
	}

	void stencil_floor() 
	{
		glBegin(GL_QUADS);

			glVertex3f(-10.0f,0.0f,10.0f);
			glVertex3f(10.0f,0.0f,10.0f);
			glVertex3f(10.0f,0.0f,-10.0f);
			glVertex3f(-10.0f,0.0f,-10.0f);
		glEnd();
	}


	void texcube()
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

	void tree()
	{
		float matrix[16];

		glPushMatrix();

		glGetFloatv(GL_MODELVIEW_MATRIX , matrix);

		matrix[0] = matrix[10] = matrix[15] = 1.0f;
		matrix[1] = matrix[2] = matrix[8] = matrix[9] = 0.0f;

		glLoadMatrixf(matrix);
		glDisable(GL_CULL_FACE);
		glBegin(GL_TRIANGLES);
		glNormal3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f,1.0f,0.0f);
		glVertex3f(1.0f,1.0f,0.0f);
		glVertex3f(0.0f,2.0f,0.0f);
// 		glVertex3f(-0.25f,0.0f,0.0f);
// 		glVertex3f(0.25f,0.0f,0.0f);
// 		glVertex3f(-0.25f,1.0f,0.0f);
// 		glVertex3f(0.25f,0.0f,0.0f);
// 		glVertex3f(0.25f,1.0f,0.0f);
// 		glVertex3f(-0.25f,1.0f,0.0f);
		glEnd();
		glEnable(GL_CULL_FACE);
		glPopMatrix();

	}
			

	void OnDisplay() {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		float deltaTime = (float)App::GetDeltaTime();

		_angle += _angleInc * deltaTime;
		if(_angle > 360.0f) 
			_angle -=360.0f;

		glPushMatrix();
			glTranslatef(0.0f, 0.0f,_cameraPosition);
			glRotatef(_cameraAngle, 1.0,0.0,0.0);
			glRotatef(_cameraRotation, 0.0, 1.0, 0.0);
			glTranslatef(0.0f, -2.0f,0.0f);

			// First draw the floor into the stencil buffer
			if(_stencil) {
				glDisable(GL_DEPTH_TEST);
				glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
				glDisable(GL_LIGHTING);
				glEnable(GL_STENCIL_TEST);
				glStencilFunc(GL_ALWAYS, 1, 1);
				glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE);
				stencil_floor();  // floor with nothing fancy
				glEnable(GL_LIGHTING);
				glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
				glEnable(GL_DEPTH_TEST);

				// everything set ready for drawing
				// set stencil ready for drawing the cube
				glStencilFunc(GL_EQUAL, 1, 1);
				glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
			};

			// now draw the a reflected cube and light under the floor but only 
			// when stencil value is 1
			glPushMatrix();
				// reflect all objects about y=0 plane 
				glScalef(1.0, -1.0, 1.0);	

				// but normals are messed up 
				// and front faces become back faces and visa-versa
				glEnable(GL_NORMALIZE);
				glCullFace(GL_FRONT);

				// includes the light position and the light source

				_light1.setPosition(Vector4f(5.0,5.0,5.0,1.0));
				_light2.setPosition(Vector4f(-5.0,5.0,5.0,1.0));
				_light4.setPosition(Vector4f(0.0,5.0,-5.0,1.0));
				_light5.setPosition(Vector4f(0.0,-1.0,-5.0,1.0));


				glPushMatrix();
					_light3.setPosition(Vector4f(_light3[0],_light3[1],_light3[2],1.0));
					glTranslatef(_light3[0],_light3[1],_light3[2]);
					_material3.apply();
					_sphere1.draw();
				glPopMatrix();
				// now the textured cube
				glPushMatrix();
					_green.apply();
					tree();
					glPushMatrix();
						glTranslatef(2.5f, 0.0f, 0.0f);
						tree();
					glPopMatrix();
					glTranslatef(2.5f, 2.0f, -2.5f);
					glRotatef(-_angle, 0.0, 1.0, 0.0);
					_material1.apply();
					texcube();
				glPopMatrix();
				
				// Done this, put things back together again
				glDisable(GL_NORMALIZE);
				glCullFace(GL_BACK);
			glPopMatrix();

			// remember to turn the stencil buffer off for the rest of the image
			if (_stencil) {
				glDisable(GL_STENCIL_TEST);
			}

			// put the lights back
				_light1.setPosition(Vector4f(5.0,5.0,5.0,1.0));
				_light2.setPosition(Vector4f(-5.0,5.0,5.0,1.0));
				_light4.setPosition(Vector4f(0.0,5.0,-5.0,1.0));
				_light5.setPosition(Vector4f(0.0,-1.0,-5.0,1.0));


			glPushMatrix();
				_light3.setPosition(Vector4f(_light3[0],_light3[1],_light3[2],1.0));
				glTranslatef(_light3[0],_light3[1],_light3[2]);
				_material3.apply();
				_sphere1.draw();
			glPopMatrix();
			



			// make the floor semi-transparent
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			_material2.apply();
			floor();
			glDisable(GL_BLEND);

			// now draw the floor again from below but with no blending
			// switch meaning of front face from anti-clockwise to clockwise
			glFrontFace(GL_CW);
			floor();
			// undo the meaning of front face
			glFrontFace(GL_CCW);


			glPushMatrix();
				_green.apply();
				tree();
				glPushMatrix();
					glTranslatef(2.5f, 0.0f, 0.0f);
					tree();
				glPopMatrix();
				glTranslatef(2.5f, 2.0f, -2.5f);
				glRotatef(-_angle, 0.0, 1.0, 0.0);
				_material1.apply();
				texcube();
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
		glFrustum(-(float)w/h, (float)w/h, -1.0f, 1.0f, 1.0f, +30.0f);
		glMatrixMode(GL_MODELVIEW);
		glViewport(0,0,w,h);
	}

	void OnKeyboard(int key, bool down) {
		Image Screen;
		if (!down) return;
		switch( tolower(key) ) {
			case 'a': 
				_cameraAngle += 5.0;
				break;
			case 'z':
				_cameraAngle -= 5.0;
				break;
			case 'm':
				_light3[0]++;
				break;
			case 'n':
				_light3[0]--;
				break;
			case 'p':
				_light3[2]--;
				break;
			case 'l':
				_light3[2]++;
				break;
			case '2':
				_light3[1]++;
				break;
			case '1':
				_light3[1]--;
				break;
			case 'f':
				_fullscreen = !_fullscreen;
				SetFullscreen(_fullscreen);
				break;
			case 'q':
				Close();
				break;
			case 's': 
				_stencil = !_stencil; // flip stencil bool
				break;
			case '9':
				Screen.GrabScreen();
				Screen.Save("screen.bmp");
				Screen.Free();
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
					_begin = true;
					break;
				case MBRight:
					_rightDown = true;
					_begin = true;
					break;
				default:
					break;
			}
		} else {
			switch(button) {
				case MBLeft: 
					_leftDown = false;
					_begin = false;
					break;
				case MBRight:
					_rightDown = false;
					_begin = false;
					break;
				default:
					break;
			}
		}
	}

	void OnMouseMove(int x, int y) {
		static int temp_x, temp_y;

		if (_begin) {
			_begin = false;
		} else {
			if(_leftDown) {
				 _cameraPosition += (y-temp_y)*0.05f;
			}
			if(_rightDown) {
				_cameraRotation += (x-temp_x)*0.5f;
			}
		}
		temp_x = x;
	    temp_y = y;
		std::cout << temp_y << std::endl;
	}

};


class MyApp :public App {
public:

	MyWindow w;

};

// this is the single instance of our application
//
static MyApp tut22;
