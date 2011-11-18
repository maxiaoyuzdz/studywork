#include <iostream>
using namespace std;

#include "vector3d.h"

void main (int, char**) {
	Vector3d a(1,2,3);
	Vector3d b(2,2,3);
	Vector3d c;
	double n;
	
	c = a.CrossProduct(b);
	c.write(cout); cout << endl;
	cout << endl;

	n = a.DotProduct(b);
	cout << "n = " << n << endl;
	cout << endl;

	c = a.Add(b);
	cout << "cx= " << c.x << endl;
	cout << "cy= " << c.y << endl;
	cout << "cz= " << c.z << endl;
	cout << endl;

	c = a.Subtract(b);
	cout << "cx= " << c.x << endl;
	cout << "cy= " << c.y << endl;
	cout << "cz= " << c.z << endl;
	cout << endl;

	n = a.Distance(b);
	cout << "n = " << n << endl;
	cout << endl;

	n = a.DistanceSqr(b);
	cout << "n = " << n << endl;
	cout << endl;

	n = a.Length();
	cout << "n = " << n << endl;
	cout << endl;

	n = a.LengthSqr();
	cout << "n = " << n << endl;
	cout << endl;

	a.Normalise();
	cout << "cx= " << a.x << endl;
	cout << "cy= " << a.y << endl;
	cout << "cz= " << a.z << endl;
	cout << endl;

	a.Normalise(b);
	cout << "cx= " << a.x << endl;
	cout << "cy= " << a.y << endl;
	cout << "cz= " << a.z << endl;
	cout << endl;


	cout <<"\nPress a key" << endl;
	int keypress; cin >> keypress;
}