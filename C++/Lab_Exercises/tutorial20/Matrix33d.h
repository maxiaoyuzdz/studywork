#ifndef MATRIX33D_H
#define MATRIX33D_H

//-----------------------------------------------------------------------------

#include <iostream>
using namespace std;

#include "Vector3d.h"

#define M33_EPSILON 1.0E-8

/**
* Double precision, 3x3 matrix class.
*/

class Matrix33d {
public:
	Matrix33d();

	Matrix33d(double M[9]);

private:
	Vector3d _row[3]; // rows
};
#endif