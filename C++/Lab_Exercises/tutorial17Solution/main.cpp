#include <iostream>
using namespace std;

#include "vector3d.h"

void main (int, char**) {
	Vector3d a;
	Vector3d b;
	Vector3d c;
	double n;

	cout << "Enter x,y,z for Vector A" << endl;
	cin >> a;

	cout << "Enter x,y,z for Vector B" << endl;
	cin >> b;

	c = a + b;
	cout << c << endl;

	c = -a;
	cout << c << endl;

	c = a - b;
	cout << c << endl;

	c = a * 5;
	cout << c << endl;

	c = 5 * a;
	cout << c << endl;

	n = a * b;
	cout << n << endl;

	c = a ^ b;
	cout << c << endl;

	a += b;
	cout << a << endl;

	a -= b;
	cout << a << endl;

	cout <<"\nPress a key" << endl;
	int keypress; cin >> keypress;
}