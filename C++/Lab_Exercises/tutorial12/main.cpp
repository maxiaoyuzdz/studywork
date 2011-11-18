#include <iostream>
#include <cmath>
using namespace std;

/*
* Calculates the area of a rectangle, then calculates the sum of the areas of two rectangles.
*/

//TODO: Debug the code, and produce the correct result.

double CalculateArea(double length, double height) {
	double area = length*height;
	return area;
}

void main(int argc, char** argv) {
	double area,
		lengthA = 2.0,
		heightA = 3.0,
		lengthB = 4.0,
		heightB = 5.0;

	// Calculate the area of A
	area = CalculateArea(lengthA, heightA);
	cout << "Area of A = " << area << endl;

	// Calculate the area of B
	area = CalculateArea(lengthB, heightB);
	cout << "Area of B = " << area << endl;

	// Calculate and sum the areas of A and B
	double totalArea = CalculateArea(lengthA, heightA) + CalculateArea(lengthB, heightB);
	cout << "Area of A + Area of B = " << totalArea << endl;

	int keypress; cin >> keypress;
}