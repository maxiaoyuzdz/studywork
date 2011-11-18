#include <iostream>
#include <fstream>
using namespace std;

#include "top.h"

void main(int, char**) {
	Top a, b, c;

	a.change(5);
	b.change(10);// = 10;

	cout << "a = " << a.lookAt() << endl;
	cout << "b = " << b.lookAt() << endl;
	cout << "c = " << c.lookAt() << endl;

//TODO: Add a call to the write method
	ofstream fout("output.txt");
	fout<<"test" ;
	a.write(fout);
	fout<<endl;

	int keypress; cin >> keypress;
}