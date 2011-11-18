#pragma once

#include "GXBase.h"

class Color {
private:
	GLfloat _rgba[4];

public:
	void Assign(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	Color();

	Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	Color(GLfloat rgba[]);

	const GLfloat* rgba() const;

	static Color black();

	static Color white();

	static Color red();

	static Color green();

	static Color blue();

	static Color yellow();

	static Color null();
};