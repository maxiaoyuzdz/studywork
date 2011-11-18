#include <iostream>
using namespace std;

int& min(int a, int b){
	if(a<b)
		return a;
	else
		return b;
}

int main(void)
{

	int a = 2, b = 4;
	int c = min(a,b) * 2 + 10;
	int d = ++min(a,b);

	int k;
	cin>>k;
}