#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
* Partially completed program
* The program should parse a text file.
*
* The text file contains a sequence of nested objects, where each object is
* delimited by characters { and } 
* Attributes within the objects consist of a name followed by at least one white space followed by a 
* set of parameters delimited by characters ( and ).
* e.g colour (5)
* A comma is used to separate multiple parameters
* e.g. position (3,5,8)
* At least one white space is used to separate attributes
* e.g. colour (5) position (3,5,6)
* The full set of named attributes are: 
*		colour(integer)
*		position(integer, integer)
*		size(integer)
*
* Requirement
* 1. Copy the file to a output file
* 2. Locate the object with the largest size.  Print out the level within the 
*	object hierarchy.  Assume the outer most object is level 1
*/

//TODO: Construct the recursive function
void testFunction(int &maxSize, int &levelOfMaxObject,ifstream *fin)
{

	string attribute;
	*fin>>attribute;

	int x =  attribute.find('{');
	int y =  attribute.find('}');

	int z = attribute.find('(');
	int w = attribute.find(')');

	if( x >= 0 ){
		cout<<"{ \n"<<endl;
	}

	if(y >= 0 ){
		cout<<"} \n"<<endl;
	}
	if( z >=0 ){
		cout<<"( \n"<<endl;
	}
	if( w >= 0){
		cout<<") \n"<<endl;
	}

	testFunction(maxSize,levelOfMaxObject,fin);
}

int main(int argc, char **argv) {
	/**
	if (argc !=3) {
		cerr << "Usage: " << argv[0] << " <input filename> <output filename>" << endl;
		return -1;
	}

	ifstream fin(argv[1]);
	if (!fin) {
		cerr << "Error: Failed to open file " << argv[1] << " for reading" << endl;
		return -1;
	}

	ofstream fout(argv[2]);
	if (!fout) {
		cerr << "Error: Failed to open file " << argv[2] << " for writing" << endl;
		return -1;
	}
	}*/

	ifstream fin("sample.txt");
	ofstream fout("output.txt");
	int maxSize = 0;
	int levelOfMaxObject = 0;

//TODO: Construct the recursive call
	testFunction(maxSize, levelOfMaxObject,&fin);

	cout << "Largest object of size " << maxSize << " is located at level " << levelOfMaxObject << endl;

	int keypress; cin >> keypress;
}