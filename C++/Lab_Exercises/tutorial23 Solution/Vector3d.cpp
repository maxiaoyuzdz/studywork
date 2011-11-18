#include ".\vector3d.h"

Vector3d::Vector3d(double x, double y, double z)
{
	setX(x);
	setY(y);
	setZ(z);
}

Vector3d::~Vector3d(void)
{
}

double Vector3d::X() const
{
	return x;
}

double Vector3d::Y() const
{
	return y;
}

double Vector3d::Z() const
{
	return z;
}

void Vector3d::setX(double x)
{
	this->x = x;
}

void Vector3d::setY(double y)
{
	this->y = y;
}

void Vector3d::setZ(double z)
{
	this->z = z;
}
