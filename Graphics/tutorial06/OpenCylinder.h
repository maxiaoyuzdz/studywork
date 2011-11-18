#pragma once

#include "GXBase.h"

class OpenCylinder
{
private:
	GLUquadric *_obj;
	GLint _slices, _stacks;
	GLdouble _baseradius,_topradius,_height;


public:
	OpenCylinder();
	~OpenCylinder();

	void create(GLdouble baseradius, GLdouble topradius, GLdouble height, GLint slices, GLint stacks);

	void draw() const;
};

