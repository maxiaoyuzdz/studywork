#pragma once

#include "NewtonianObject.h"
#include "Colour.h"

class Ball : public NewtonianObject
{
public:
	Ball(const Vector3d &position, double radius = 1);
	~Ball(void);
	const Colour & getColour() const;
	void  setColour(const Colour &colour);
	double getRadius() const;
	void   setRadius(double radius);
	void   ApplyPhysics(double time);
	void   ApplyGravity(double time);

private:
	double r;
	Colour colour;
};
