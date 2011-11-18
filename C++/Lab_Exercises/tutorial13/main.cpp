#include <iostream>
#include <string>
#include <windows.h>  // required for timeGetTime()
using namespace std;

#pragma comment(lib, "Winmm")  // required for timeGetTime()

string Concat(string a, string b, string c) {
	return a + b + c;
}

string Concat2(string& a, string& b, string& c) {
	return a + b + c;
}

string& Concat3(string& a, string& b, string& c, string& d) {
	d= a + b + c;
	return d;
}

/**
 * Program experiments with the concatenation of strings
 */

//TODO: Determine which of the three functions is the most efficient

void main(int argc, char** argv) {
	string a = "Hello";
	string b = " ";
	string c = "World";
	string d;
	string e;
	
	cout << "Enter number of iterations" << endl;
	int limit=0;
	cin >> limit;

	unsigned int startTime = timeGetTime();

	for (int i=0; i<limit; i++) {
		d = Concat(a, b, c);
	}

	unsigned int endTime = timeGetTime();

	cout << "Duration for " << limit << " cycles is " << (endTime - startTime) << "ms" << endl;
	cout << "Result string is \"" << d << "\"" << endl;

	unsigned int startTime2 = timeGetTime();

	for (int i=0; i<limit; i++) {
		d = Concat2(a, b, c);
	}

	unsigned int endTime2 = timeGetTime();

	cout << "Duration for " << limit << " cycles is " << (endTime2 - startTime2) << "ms" << endl;
	cout << "Result string is \"" << d << "\"" << endl;

	unsigned int startTime3 = timeGetTime();

	for (int i=0; i<limit; i++) {
		e = Concat3(a, b, c,d);
	}

	unsigned int endTime3 = timeGetTime();

	cout << "Duration for " << limit << " cycles is " << (endTime3 - startTime3) << "ms" << endl;
	cout << "Result string is \"" << d << "\"" << endl;

	int keypress; cin >> keypress;
}