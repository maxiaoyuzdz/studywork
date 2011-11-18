#include "cube.h"

Cube::Cube(const Vector3d &position, double size)
{
	pos = new Vector3d(position.X(), position.Y(), position.Z());
	vel = new Vector3d();
	setSize(size);
}

Cube::~Cube(void)
{
	if(pos) delete pos;
	if(vel) delete vel;
}

const Colour & Cube::getColour() const
{
	return colour;
}

void Cube::setColour(const Colour &colour)
{
	this->colour = colour;
}

double Cube::getSize() const
{
	return size;
}

void Cube::setSize(double size)
{
	if(size > 0) this->size = size;
}

void Cube::ApplyPhysics(double time)
{
	// Do physics stuff but not gravity
}
