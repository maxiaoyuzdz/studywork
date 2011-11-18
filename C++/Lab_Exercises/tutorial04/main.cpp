#include <iostream>
using namespace std;

/**
 * This program reads in a number of integers and counts the times a 
 * predefined value occurs
 *
 * It contains a bug and fails to give the correct output
 */

void main(int argc, char **argv) { 

	int counter, key;
	cout << "Enter a key value" << endl;
	cin >> key;
	//////////////////////////////////////////////////////////////////////////
	counter = 0;
	//////////////////////////////////////////////////////////////////////////
	
	int value, i;

	cout << "Enter a sequence of integers, terminating with a letter" << endl;
	for (i=0; cin >> value; i++) {
		if (key == value)
			counter++;
	}
	cin.clear(); 
	char endOfInput;
	cin >> endOfInput;

	cout << counter << " of the " << i << " values equal " << key << endl;

	int keypress; cin >> keypress;
}