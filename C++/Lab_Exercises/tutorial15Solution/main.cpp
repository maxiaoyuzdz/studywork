#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "top.h"

void main(int, char**) {
	Top a, b, c;

	a.change(5);
	b.change(10);

	// output to the console
	cout << "a = "; a.write(cout); cout << endl;
	cout << "b = "; b.write(cout); cout << endl;
	cout << "c = "; c.write(cout); cout << endl;

	// output to the file
	ofstream fout("output.txt");
	fout << "a = "; a.write(fout); fout << endl;
	fout << "b = "; b.write(fout); fout << endl;
	fout << "c = "; c.write(fout); fout << endl;

	int keypress; cin >> keypress;
}