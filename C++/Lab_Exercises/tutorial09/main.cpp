#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/*
* Calculates the roots for a quadratic equation
* No account is taken of an imaginary root or floating point overflows
*/

double QuadraticCalculation1(double a, double b, double c){

	if(a == 0) a = 1;
	double operand = b*b - 4.0*a*c;
	double root1 = (-b + sqrt(operand)) / (2.0 * a);

	return root1;
}

double QuadraticCalculation2(double a, double b, double c){
	if(a == 0) a = 1;
	double operand = b*b - 4.0*a*c;
	double root2 = (-b - sqrt(operand)) / (2.0 * a);
	return root2;
}

void main (int argc, char **argv) {
	cout << "Enter the coefficiants for a quadratic equation" << endl;
	double a, b, c;
	cin >> a >> b >> c;
	/**
	double operand = b*b - 4.0*a*c;
	double root1 = (-b + sqrt(operand)) / (2.0 * a);
	double root2 = (-b - sqrt(operand)) / (2.0 * a);
	*/
	double root1 = QuadraticCalculation1(a,b,c);
	double root2 = QuadraticCalculation2(a,b,c);

	cout << "The roots of the equation " 
		<< a << "x^2 + " << b << "x + " << c << "\n"
		<< "are " << root1 << " and " << root2 << endl;

	int keypress; cin >> keypress;
}
