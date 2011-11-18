#include <vector>
#include <iostream>
using namespace std;

/*
    1. find out how long it takes for the following
	   operations to take place for the container - vector
	2. complete the same tasks for container - list
	3. complete the same tasks for container - set
*/

typedef vector<int>::iterator vIterator;

const int SIZE = 99999;

void main(int, char**) {
	int item = 0;
	vector<int> v;

	for(item = 0; item < SIZE; item++)	// add SIZE items to the vector
		v.push_back(item);
	cout << "Completed Vector Add" << endl;

	for(item = 0; item < SIZE; item++)	// access all item in the vector
		v.at(item);
	cout << "Completed Vector Random Access" << endl;

	vIterator p = v.begin();
	for(item = 0; item < SIZE; item++)	// traverse all items in the vector
		*(p++);
	cout << "Completed Vector Traverse Access" << endl;

	for(item = 0; item < SIZE; item++)	// delete all items in the vector
		v.pop_back();
	cout << "Completed Vector Items Remove" << endl;

	int keypress;
	cin >> keypress;
}
