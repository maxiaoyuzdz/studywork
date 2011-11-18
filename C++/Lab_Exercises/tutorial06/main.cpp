#include <iostream>
#include <fstream>
#include <strstream>
#include <string>
using namespace std;

/*
* A program that scans through a C++ file looking for a particular variable
* When the variable is found the line number and position within the line are returned
* Comments are ignored
*/

void main(int argc, char **argv) { 

	

	ifstream fin("seat2.h");
	if(!fin){
		cout<<"file open error\n";
		return;
	}
	char buffer[100];
	int rA,rB,rv,rn,ru,rc;

	while(!fin.eof()){
		fin.getline(buffer, sizeof(buffer));
		int lengthOfLine = fin.gcount();
		istrstream sin (buffer, lengthOfLine-1);
		//cout<<lengthOfLine<<endl;
		string word;
		//word = "aa";
		sin>>word;
		
		rA = rB = rv = rn = ru = rc = -2;
		rA = word.compare("A");
		rB = word.compare("B");
		rv = word.compare("v");
		rn = word.compare("n");
		ru = word.compare("u");
		rc = word.compare("c");

		if(rA == 0){
			sin>>word;
			//float res;
			//res = atof(word.c_str());
			cout<<"vn = "<<atof(word.c_str())<<endl;
		}
		if(rB == 0){
			sin>>word;
			cout<<"fn = "<<atof(word.c_str())<<endl;
		}
		if(rv == 0){
			sin>>word;
			cout<<"v = "<<atof(word.c_str())<<endl;
		}
		if(rn == 0){
			sin>>word;
			cout<<"n = "<<atof(word.c_str())<<endl;
		}
		if(ru == 0){
			sin>>word;
			cout<<"u = "<<atof(word.c_str())<<endl;
		}
		if(rc == 0){
			sin>>word;
			cout<<"c = "<<atof(word.c_str())<<endl;
		}
		
	}
	fin.close();
	/**
	 **
	bool found = false;
	

	for (int line=0; !fin.eof(); line++) 
	{
		
		
		char lineBuffer[100];
		fin.getline(lineBuffer, sizeof(lineBuffer));
		int lengthOfLine = fin.gcount();
		
		if(lengthOfLine > 0)
		{
			istrstream sin (lineBuffer, 0);  // Removes end of line character
			string word;
			while(sin >> word && !(sin.eof()))
			{
				cout<<word<<endl;
			}
			//cout<<lengthOfLine<<endl;
		}
		
		/*
		
		while(sin >> word && !(sin.eof()))
		{

		}
		*/
		/**
		for (position=1; (sin >> word) && !found && !((word[0] == '/') && (word[1] == '/')); position++) {
			if (word.compare("q")==0) {
				found = true;
			}
		}
		*/
	//}
	//*/

	

	int keypress; 
	cin >> keypress;
}