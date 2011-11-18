#include "Vector4f.h"

void Vector4f::Assign(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	_xyzw[0] = x;
	_xyzw[1] = y;
	_xyzw[2] = z;
	_xyzw[3] = w;
}

Vector4f::Vector4f() { 
	Assign(0.0, 0.0, 0.0, 1.0);
}

Vector4f::Vector4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	Assign(x, y, z, w);
}

Vector4f::Vector4f(GLfloat xyzw[]) {
	Assign(xyzw[0], xyzw[1], xyzw[2], xyzw[3]);
}

const GLfloat* Vector4f::xyzw() const {
	return _xyzw;
}
