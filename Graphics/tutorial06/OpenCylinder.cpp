#include "OpenCylinder.h"


OpenCylinder::OpenCylinder(void)
{
	_obj  = NULL;
}


OpenCylinder::~OpenCylinder(void)
{
	gluDeleteQuadric(_obj);
}

void OpenCylinder::create(GLdouble baseradius, GLdouble topradius, GLdouble height, GLint slices, GLint stacks)
{
	_obj = gluNewQuadric();

	gluQuadricNormals(_obj, GLU_SMOOTH);
	_baseradius = baseradius;
	_topradius = topradius;
	_height = height;
	_slices = slices;
	_stacks = stacks;

}

void OpenCylinder::draw() const
{
	if (_obj)
	{
		gluCylinder(_obj, _baseradius, _topradius,_height,_slices,_stacks);
		
	}
}
