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
*		colour (integer)
*		position (integer, integer)
*		size (integer)
*
* Requirement
* 1. Copy the file to a output file
* 2. Locate the object with the largest size.  Print out the level within the 
*	object hierarchy.  Assume the outer most object is level 1
*/

int main(int argc, char **argv) {
	/**
	if (argc !=3) {
		cerr << "Usage: " << argv[0] << " <input filename> <output filename>" << endl;
		return -1;
	}
	*/
	ifstream fin("sample.txt");
	/**
	if (!fin) {
		cerr << "Error: Failed to open file " << argv[1] << " for reading" << endl;
		return -1;
	}
	*/
	ofstream fout("output.txt");
	/**
	if (!fout) {
		cerr << "Error: Failed to open file " << argv[2] << " for writing" << endl;
		return -1;
	}
	*/
	char ch;
	string attribute;
	int maxSize = 0;
	int level=0, levelOfMaxObject = 0;

	int object_num = 0;

	while (fin >> attribute) {
//TODO: Construct the main parsing loop
		/**
		if(attribute == "{")
		{
			cout<<"{ \n"<<endl;
			object_num++;
			cout<<"Obejct Num: "<<object_num<<endl;
		}
		*/

		int x =  attribute.find('{');
		int y =  attribute.find('}');

		int z = attribute.find('(');
		int w = attribute.find(')');

		if(x < 0 && y<0 )
		{
			if(z<0 && w<0)
				cout<<"ok a attribute \n"<<endl;
		}

		if(z>=0 || w >= 0)
		{

		}


	}

	//cout << "Largest object of size " << maxSize << " is located at level " << levelOfMaxObject << endl;
	cout<< "End Parser \n"<<endl;
	int keypress; cin >> keypress;
}