#include "Vector3d.h"
#include <cmath>

//-----------------------------------------------------------------------------

Vector3d::Vector3d()
{
	x=0.0;
	y=0.0;
	z=0.0;
}

//-----------------------------------------------------------------------------

Vector3d::Vector3d(double d)
{
	x=d;
	y=d;
	z=d;
}

//-----------------------------------------------------------------------------

Vector3d::Vector3d(double X, double Y, double Z)
{
	x=X;
	y=Y;
	z=Z;
}

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------

bool Vector3d::operator == (const Vector3d &V) const
{
	return (x==V.x) && (y==V.y) && (z==V.z);
}

//-----------------------------------------------------------------------------

bool Vector3d::operator != (const Vector3d &V) const
{
	return !(*this==V);
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::Add(const Vector3d &R) const
{
	return Vector3d(x+R.x, y+R.y, z+R.z);	
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::Subtract(const Vector3d &R) const
{
	return Vector3d(x-R.x, y-R.y, z-R.z);	
}

//-----------------------------------------------------------------------------

double Vector3d::Distance  (const Vector3d &V) const
{
	return (double)sqrt( DistanceSqr(V) );
}

double Vector3d::DistanceSqr (const Vector3d &V) const
{
	return Subtract(V).LengthSqr();
}

//-----------------------------------------------------------------------------

double Vector3d::Length  () const
{
	return (double)sqrt( LengthSqr() );
}

double Vector3d::LengthSqr () const
{
	return (x*x + y*y + z*z);
}

//-----------------------------------------------------------------------------

const Vector3d & Vector3d::Normalise()
{
	return Normalise(*this);
}

const Vector3d & Vector3d::Normalise( const Vector3d &V )
{
	double r = V.Length();
	if (r!=0.0)				// guard against divide by zero
		return *this=Vector3d(V.x/r, V.y/r, V.z/r);	// normalise and return
	else
		return *this;
}

//-----------------------------------------------------------------------------

bool Vector3d::IsZero  (double Tolerance) const
{
	return (LengthSqr() <= Tolerance*Tolerance);
}

bool Vector3d::IsUnit (double Tolerance) const
{
	return fabs(Length() - 1.0) <= Tolerance;
}

bool Vector3d::IsEqual(const Vector3d &V, double Tolerance) const
{
	return Subtract(V).IsZero(Tolerance);
}

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
