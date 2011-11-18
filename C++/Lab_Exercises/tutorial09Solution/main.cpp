#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

/*
* Calculates the roots for a quadratic equation
*/

void CalcRoots(double a, double b, double c)
{
// calculate the square root operand
	double operand = b*b - 4.0*a*c;
	if(operand > 0)						// two real roots
	{
		double sqrOperand = sqrt(operand);	// find square root of operand once (faster)
		double denominator = 2.0 * a;		// find denominator once (faster) and
		if(denominator == 0.0)				// test for division by 0
			cout << "Cannot divide by 0!" << endl;
		else
		{
			double root1 = (-b + sqrOperand) / denominator;	// calc root 1
			double root2 = (-b - sqrOperand) / denominator;	// calc root 2
			cout << "The two real roots of the equation " << setprecision(3) 
				<< a << "x^2 + " << b << "x + " << c << "\n"
				<< "are " << root1 << " and " << root2 << endl;
		}
	}
	else if(operand == 0)				// one real roots
	{
		double denominator = 2.0 * a;		// find denominator and
		if(denominator == 0.0)				// test for division by 0
			cout << "Cannot divide by 0!" << endl;
		else
		{
			double root = -b / denominator;	// calc the single root
			cout << "The root of the equation " << setprecision(3)
				<< a << "x^2 + " << b << "x + " << c << "\n"
				<< "is " << root << endl;
		}
	}
	else								// two imaginary roots
	{
		cout << "There are two imaginary roots of the equation " << endl;
	}
}

void main (int argc, char **argv) {
	cout << "Enter the coefficiants for a quadratic equation" << endl;
	double a, b, c;
	cin >> a >> b >> c;

	CalcRoots(a, b, c);

	int keypress; cin >> keypress;
}
