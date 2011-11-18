#include <iostream>
#include <fstream>
using namespace std;

#include "vector3d.h"

void main (int, char**) {
	Vector3d a(1,2,3);
	Vector3d b(2,2,3);
	Vector3d c;
	c = a.Add(b);


	double dis = a.Distance(b);

	Vector3d croessProduct = a.CrossProduct(b);

	double dotproduct = a.DotProduct(b);

	cout << "cx= " << c.x << endl;
	cout << "cy= " << c.y << endl;
	cout << "cz= " << c.z << endl;
	cout << "dis= " << dis << endl;
	cout << "crox= " << croessProduct.x<<"croy= " << croessProduct.y<<"croz= " << croessProduct.z << endl;
	cout << "dp= " << dotproduct << endl;


	ofstream fout("simple.txt");

	a.write(fout);

	cout <<"\nPress a key" << endl;
	int keypress; cin >> keypress;
}