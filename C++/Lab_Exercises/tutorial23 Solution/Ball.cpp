#include "ball.h"

Ball::Ball(const Vector3d &position, double radius)
{
	gravity = 9.81;
	pos = new Vector3d(position.X(), position.Y(), position.Z());
	vel = new Vector3d();
	setRadius(radius);
}

Ball::~Ball(void)
{
	if(pos) delete pos;
	if(vel) delete vel;
}

const Colour & Ball::getColour() const
{
	return colour;
}

void Ball::setColour(const Colour &colour)
{
	this->colour = colour;
}

double Ball::getRadius() const
{
	return r;
}

void Ball::setRadius(double radius)
{
	if(radius > 0) r = radius;
}

void Ball::ApplyPhysics(double time)
{
	ApplyGravity(time);

	// Do other physics type stuff
}

void Ball::ApplyGravity(double time)
{
	// Do gravity
	double newVy = vel->Y() + gravity*time;
	double newPy = pos->Y() + newVy*time + 0.5*gravity*time*time;

	vel->setY(newVy);
	pos->setY(newPy);
}
