#include "Sphere.h"

Sphere::Sphere() { 
	_obj = NULL;
}

Sphere::~Sphere() {
	gluDeleteQuadric(_obj);
}

void Sphere::create(GLfloat radius, GLuint slices, GLuint stacks) {
	_obj = gluNewQuadric();
	//_obj = gluNewQuadric();
	gluQuadricNormals(_obj, GLU_SMOOTH);
	gluQuadricDrawStyle(_obj,GL_TRIANGLE_FAN);
	_radius = radius;
	_slices = slices;
	_stacks = stacks;
}

void Sphere::draw() const {
	if (_obj)
		gluSphere(_obj, _radius, _slices, _stacks);
}
