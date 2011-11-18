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
* 1. Copy the file to an output file
* 2. Locate the object with the largest size.  Print out the level within the 
*	object hierarchy.  Assume the outer most object is level 1
*/

// No error checking has been implemented

void FormatOutput(ofstream &out, int level)
{
	for(int count = 0; count < level; count++)
	{
		out << "    ";
	}
}

int main(int argc, char **argv) {
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

	string attribute, parameters;
	int maxSize = 0;
	int level=0, levelOfMaxObject = 0;

	while (fin >> attribute) {
		if(attribute.compare("{") == 0)	// found increase level attribute
		{
			FormatOutput(fout, level++);		// increase level
			fout << attribute << endl;
		}
		else if(attribute.compare("}") == 0)	// found decrease level attribute
		{
			FormatOutput(fout, --level);		// decrease level
			fout << attribute << endl;
		}
		else if(attribute.compare("size") == 0)	// found SIZE attribute
		{
			fin >> parameters;
			int begin = (int)parameters.find('(')+1;
			int end   = (int)parameters.find(')');
			int size  = atoi(parameters.substr(begin, end-begin).c_str());	// find size parameter
			if(size > maxSize)					// is size bigger than maxSize?
			{
				maxSize = size;					// YES, so assign size to maxSize
				levelOfMaxObject = level;		// and assign the current level to levelOfMaxObject
			}
			FormatOutput(fout, level);
			fout << attribute << " " << parameters << endl;
		}
		else if(attribute.compare("colour") == 0)	// found COLOUR attribute
		{
			fin >> parameters;
			int begin = (int)parameters.find('(')+1;
			int end   = (int)parameters.find(')');
			int colour  = atoi(parameters.substr(begin, end-begin).c_str()); // find colour parameter
			// ******** Handle colour here if required in future ********
			FormatOutput(fout, level);
			fout << attribute << " " << parameters << endl;
		}
		else if(attribute.compare("position") == 0)	// found POSITION attribute
		{
			fin >> parameters;
			int begin  = (int)parameters.find('(')+1;
			int middle = (int)parameters.find(',');
			int end    = (int)parameters.find(')');
			int x      = atoi(parameters.substr(begin, middle-begin).c_str());	   // find x parameter
			int y      = atoi(parameters.substr(middle+1, end-middle-1).c_str());  // find y parameter
			// ******** Handle position here if required in future ********
			FormatOutput(fout, level);
			fout << attribute << " " << parameters << endl;
		}
	}

	cout << "Largest object of size " << maxSize << " is located at level " << levelOfMaxObject << endl;

	int keypress; cin >> keypress;
}