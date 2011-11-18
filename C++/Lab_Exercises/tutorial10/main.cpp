#include <iostream>
#include <iomanip>
using namespace std;

/*
* Sample code that illustrates a variety of parameter passing issues
*/

void Print(const char* message, int i, int j, int k) {
	cout << setw(20) << message << "  " 
		<< " i=" << setw(4) << i 
		<< " j=" << setw(4) << j 
		<< " k=" << setw(4) << k << endl;
}

void Function1 (int i, int j, int k) {
	i += 10;
	j = 5;
	Print("within function1", i,j,k);
}

void Function2 (int i, int j, int &k) {
	k = i + j;
	Print("within function2", i,j,k);
}

void Function3 (int &i, int &j, int &k) {
	i = 10;
	j = 20;
	k = 30;
	Print("within function3", i,j,k);
}

int Function4 (int &i, int j) {
	int k;
	i = 10;
	j = 20;
	k = 30;
	Print("within function4", i,j,k);
	return k+i;
}

void Function5 (int &i, int j, int &k) {
	{
		int i, j;
		i = 10;
		j = 20;
		k = 30;
	}
	Print("within function5", i,j,k);
}

void main (int argc, char** argv) {
	int i=1;
	int j=2;
	int k=3;
	Print("at start", i,j,k);

	Function1(i,j,k);
	Print("after function1", i,j,k);

	Function2(i,j,k);
	Print("after function2", i,j,k);

	Function2(i,i,j);
	Print("after function2", i,j,k);

	Function2(i+j,i,k);
	Print("after function2", i,j,k);

	Function3(k,j,i);
	Print("after function3", i,j,k);

	i = Function4(k,j+3);
	Print("after function4", i,j,k);

	Function5(k,j,i);
	Print("after function5", i,j,k);

	Print("at end", i,j,k);
	int keypress; cin >> keypress;
}

