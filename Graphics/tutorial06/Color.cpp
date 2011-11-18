#include "Color.h"

void Color::Assign(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	_rgba[0] = r;
	_rgba[1] = g;
	_rgba[2] = b;
	_rgba[3] = a;
}

Color::Color() { 
	Assign(0.0, 0.0, 0.0, 0.0);
}

Color::Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	Assign(r, g, b, a);
}

Color::Color(GLfloat rgba[]) {
	Assign(rgba[0], rgba[1], rgba[2], rgba[3]);
}

const GLfloat* Color::rgba() const {
	return _rgba;
}

Color Color::black() {
	//return static Color Object with rgba data
	return Color(0.0, 0.0, 0.0, 1.0);
}

Color Color::white() {
	return Color(1.0, 1.0, 1.0, 1.0);
}

Color Color::red() {
	return Color(1.0, 0.0, 0.0, 1.0);
}

Color Color::green() {
	return Color(0.0, 1.0, 0.0, 1.0);
}

Color Color::blue() {
	return Color(0.0, 0.0, 1.0, 1.0);
}

Color Color::null() {
	return Color(0.0, 0.0, 0.0, 0.0);
}
