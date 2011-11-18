#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/*
* Calculates the roots for a quadratic equation
* No account is taken of an imaginary root or floating point overflows
*/

//TODO: Enable the program to handle equal or imaginary roots
//TODO: Improve the efficiency of the program
//TODO: Output the roots to only 3 decimal places

void main (int argc, char **argv) {
	cout << "Enter the coefficiants for a quadratic equation" << endl;
	double a, b, c;
	cin >> a >> b >> c;

	double operand = b*b - 4.0*a*c;
	if(a == 0)
		a = 1;
	double root1 = (-b + sqrt(operand)) / (2.0 * a);
	double root2 = (-b - sqrt(operand)) / (2.0 * a);

	cout.precision(3);
	cout << "The roots of the equation " 
		//<< setprecision(3) 
		<< a << "x^2 + " << b << "x + " << c << "\n"
		<< "are " << root1 << " and " << root2 << endl;

	int keypress; cin >> keypress;
}
