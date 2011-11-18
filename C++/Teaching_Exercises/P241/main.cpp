#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
	char c = 'c';
	char d = 'd';
	char* const p = &c;
	p = &d;

	const char *e = &d;
	*e = 'e';


}