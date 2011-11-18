#include "Materials.h"

Materials::Materials() {
	_ambient = Color::black();
	_diffuse = Color::white();
}

void Materials::create(const Color &ambient, const Color &diffuse, const Color &emission) {
	setAmbient(ambient);
	setDiffuse(diffuse);
	setEmission(emission);
}

void Materials::setAmbient(const Color &ambient) {
	_ambient = ambient;
}		

void Materials::setDiffuse(const Color &diffuse) {
	_diffuse = diffuse;
}		

void Materials::setEmission(const Color &emission) {
	_emission = emission;
}		

void Materials::apply() const {
	glMaterialfv(GL_FRONT, GL_AMBIENT, _ambient.rgba());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _diffuse.rgba());
	glMaterialfv(GL_FRONT, GL_EMISSION, _emission.rgba());
}
