#pragma once

#include "NewtonianObject.h"
#include "Colour.h"

class Cube : public NewtonianObject
{
public:
	Cube(const Vector3d &position, double size = 1);
	~Cube(void);
	const Colour & getColour() const;
	void  setColour(const Colour &colour);
	double getSize() const;
	void   setSize(double size);
	void   ApplyPhysics(double time);

private:
	double size;
	Colour colour;
};
