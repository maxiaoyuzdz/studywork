#pragma once

class Vector3d
{
public:
	Vector3d(double x = 0, double y = 0, double z = 0);
	~Vector3d(void);
	void setX(double x);
	void setY(double y);
	void setZ(double z);
	double X() const;
	double Y() const;
	double Z() const;

private:
	double x, y, z;
};
