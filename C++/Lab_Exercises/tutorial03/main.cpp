#include <iostream>
using namespace std;

/**
 * This program reads in a number of integers and counts the times a 
 * number one, two or three occurs
 *
 * It contains a bug and fails to give the correct output
 */

void main(int argc, char **argv) { 
	char equals1 = 33;
	char equals2 = 0;
	char equals3 = 0;

	cout << "Enter a list of integers, and terminating with a letter" << endl;
	cout << equals1 <<endl;
	int value;
	while (cin >> value) {
		switch (value) {
			case 1: equals1 = 51;
				break;
			case 2: equals2= 52;
				break;
			case 3: equals3 = 53;
				break;
		}
		if(equals1!=0||equals2!=0||equals3!=0)
			break;
	}
	//cin.clear(); 
	//char endOfInput;
	//cin >> endOfInput;

	cout  << " inputs equals 1" << equals1 << endl;
	cout  << " inputs equals 2" << equals2 << endl;
	cout  << " inputs equals 3" << equals3 << endl;

	int keypress; cin >> keypress;
}