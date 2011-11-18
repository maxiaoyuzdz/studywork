#include <iostream>

using namespace std;

int i = 1;
//extern int j;

void functionA()
{
	cout<<i<<endl;
	//cout<<::j<<endl;
}

int main(){
	cout<<i<<endl;
	{

		char i = 'a';
		cout<<i<<endl;
		i = 2;
		cout<<i<<endl;
		cout<<::i<<endl;
	}
	cout << i<<endl;

	cin>>i;
	return 0;
}