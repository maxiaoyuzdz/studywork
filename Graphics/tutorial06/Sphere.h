#pragma once

#include "GXBase.h"

class Sphere {
private:
	GLUquadric *_obj;
	GLfloat _radius;
	GLuint _slices, _stacks;

public:	 
	Sphere();

	~Sphere();

	void create(GLfloat radius, GLuint slices, GLuint stacks);

	void draw() const;
};
