#include "Sphere.h"

Sphere::Sphere() { 
	_obj = NULL;
}

Sphere::~Sphere() {
	gluDeleteQuadric(_obj);
}

void Sphere::create(GLfloat radius, GLuint slices, GLuint stacks, bool texture) {
	_obj = gluNewQuadric();
	gluQuadricNormals(_obj, GLU_SMOOTH);
	_radius = radius;
	_slices = slices;
	_stacks = stacks;
	gluQuadricTexture(_obj, texture);
}

void Sphere::draw() const {
	if (_obj)
		gluSphere(_obj, _radius, _slices, _stacks);
}
