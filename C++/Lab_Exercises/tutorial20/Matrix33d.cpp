#include "Matrix33d.h"
#include <cmath>

//-----------------------------------------------------------------------------

Matrix33d::Matrix33d()
{
}

//-----------------------------------------------------------------------------

Matrix33d::Matrix33d(double m[9])
{
	_row[0].x = m[0]; _row[0].y = m[1]; _row[0].z = m[2];
	_row[1].x = m[3]; _row[1].y = m[4]; _row[1].z = m[5];
	_row[2].x = m[6]; _row[2].y = m[7]; _row[2].z = m[8];
}

//-----------------------------------------------------------------------------

