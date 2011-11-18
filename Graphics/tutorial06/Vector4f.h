#pragma once

#include "GXBase.h"

class Vector4f {
private:
	GLfloat _xyzw[4];

public:
	void Assign(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	Vector4f();

	Vector4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	Vector4f(GLfloat xyzw[]);

	const GLfloat* xyzw() const;
};
