#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

/*
* Calculates the roots for a quadratic equation
*/

bool CalcRoots(double a, double b, double c, double &root1, double &root2)
{
// calculate the square root operand
	double operand = b*b - 4.0*a*c;
	if(operand > 0)						// two real roots
	{
		double sqrOperand = sqrt(operand);	// find square root of operand once (faster)
		double denominator = 2.0 * a;		// find denominator once (faster) and
		if(denominator == 0.0)				// test for division by 0
		{
			cout << "Cannot divide by 0!" << endl;
			return false;
		}
		else
		{
			root1 = (-b + sqrOperand) / denominator;	// calc root 1
			root2 = (-b - sqrOperand) / denominator;	// calc root 2
		}
	}
	else if(operand == 0)				// one real roots
	{
		double denominator = 2.0 * a;		// find denominator and
		if(denominator == 0.0)				// test for division by 0
		{
			cout << "Cannot divide by 0!" << endl;
			return false;
		}
		else
		{
			root1 = root2 = -b / denominator;	// calc the single root
		}
	}
	else								// two imaginary roots
	{
		cout << "There are two imaginary roots of the equation " << endl;
		return false;
	}

	return true;
}

void main (int argc, char **argv) {
	cout << "Enter the coefficiants for a quadratic equation" << endl;
	double a, b, c, root1, root2;
	cin >> a >> b >> c;

	if(CalcRoots(a, b, c, root1, root2))
	{
		cout << "The roots of the equation " << setprecision(3) 
		<< a << "x^2 + " << b << "x + " << c << "\n"
		<< "are " << root1 << " and " << root2 << endl;
	}

	int keypress; cin >> keypress;
}
