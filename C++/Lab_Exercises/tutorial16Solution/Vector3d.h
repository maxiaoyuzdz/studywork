#ifndef VECTOR3D_H
#define VECTOR3D_H

//-----------------------------------------------------------------------------

#include <iostream>
using namespace std;

#define V3_EPSILON 1.0E-8



/**
* Double precision, 3D vector class.
*/

class Vector3d {
public:
	double x;
	double y;
	double z;

public:
	//-------------------------------------------------------------------------

	/**
	* Default constructor. Initialises vector to zero.
	*/
	Vector3d();

	/**
	* Construct from double. Assigns double value to all elements of vector.
	*/
	Vector3d(double);

	/**
	* Construct from three doubles. Assigns the three parameters to the
	* X,Y,Z elements of the vector.
	*/
	Vector3d(double, double, double);

	//-------------------------------------------------------------------------

	/**
	* Exact equality. Returns true if both vectors are exactly equal. It is
	* not good practice to use this operator. Use IsEqual() instead.
	*/
	bool operator == (const Vector3d &) const;

	/**
	* Inequality operator. Returns true if the vectors are not exactly equal.
	* It is not good practice to use this operator. Use !IsEqual() instead.
	*/
	bool operator != (const Vector3d &) const;

	//-------------------------------------------------------------------------

	/**
	* Vector addition. The code A = L.Add(R) is equivalent to A=L+R
	*/
	Vector3d Add(const Vector3d &R ) const;

	/**
	* Vector subtraction. The code A = L.Subtract(R) is equivalent to A=L-R
	*/
	Vector3d Subtract(const Vector3d &R ) const;

	//-------------------------------------------------------------------------

	/**
	* Distance between two vectors.
	*/
	double Distance (const Vector3d &V) const;

	/**
	* Squared distance between two vectors. When comparing distances, it is
	* generally faster to compare the squared distance to avoid the square
	* root calculation.
	*/
	double DistanceSqr (const Vector3d &V) const;

	/**
	* Length of vector. This returns the length (magnitude) of the vector.
	*/
	double Length () const;

	/**
	* Squared length of vector. This returns the squared length of the
	* vector (squared magnitude). When comparing length, it is generally
	* faster to compare the squared length to avoid the square root
	* calculation.
	*/
	double LengthSqr () const;

	//-------------------------------------------------------------------------

	/**
	* Normalise a vector in place. If the vector is zero magnitude, then
	* the result is a zero vector.
	*/
	const Vector3d & Normalise();

	/**
	* Normalise a vector. The operation L.Normalise(R) replaces L with
	* the normalised (unit length) version of R. It is equivalent to
	* L=R.Normalise() but with less overhead, since a temporary object
	* is not returned.
	*/
	const Vector3d & Normalise( const Vector3d &V );


	//-------------------------------------------------------------------------

	/**
	* Calculate the Vector Product (Cross Product) between the vector in place
	* and another vector
	*/
	Vector3d CrossProduct( const Vector3d &V );

	/**
	* Calculate the Dot Product (Cross Product) between the vector in place
	* and another vector
	*/
	double DotProduct( const Vector3d &V );


	//-------------------------------------------------------------------------

	// Write the vector to the ostream
	void write(ostream &out) const;


	//-------------------------------------------------------------------------

	/**
	* Vector is near zero. Returns true if a vector is very close to zero.
	* The default tolerance can be overidden.
	*/
	bool IsZero  (double Tolerance = V3_EPSILON) const;

	/**
	* Vector is near unit-length. Returns true if vector is very close to
	* unit length. The default tolerance can be overidden.
	*/
	bool IsUnit  (double Tolerance = V3_EPSILON) const;

	/**
	* Vector this is near equal to V. Returns true if vector this and V are very close to equal.
	* The default tolerance can be overidden.
	*/
	bool IsEqual(const Vector3d &V, double Tolerance = V3_EPSILON) const;

	//-------------------------------------------------------------------------


};
#endif //VECTOR3D_H
