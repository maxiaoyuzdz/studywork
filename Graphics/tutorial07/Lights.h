#pragma once

#include "GXBase.h"
#include "Vector4f.h"
#include "Color.h"

class Lights {
private:
	// Light number
	GLuint _lightNumber;				

	// Ambient, diffuse and position
	Color _ambient;
	Color _diffuse;
	Vector4f _position;

public:
	Lights();

	void create(GLuint lightNum, const Color &ambient=Color::black(), const Color &diffuse=Color::white(), const Vector4f &position=Vector4f(0.0f,0.0f,0.0f,1.0f));

	void setAmbient(const Color &ambient);

	void setDiffuse(const Color &diffuse);

	void setPosition(const Vector4f &position);

	void apply() const;
};
