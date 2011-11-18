#pragma once

#include "Vector3d.h"

class NewtonianObject
{
public:
	NewtonianObject(void);
	virtual ~NewtonianObject(void);

	virtual void ApplyPhysics(double time) = 0;

protected:
	Vector3d *pos, *vel;
	double gravity;
};
