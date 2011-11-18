#include <iostream>
#include <fstream>
using namespace  std;

static ofstream dout("dump file for main.txt");

void message(){
	static bool firstTime = true;
	if(firstTime){
		firstTime = false;
		cout<<"First time in function"<<endl;
	}
	else{
		cout<<"Second time in function"<<endl;
	}
}

int main(int argc, char* argv[]){
	dout<<"Begin"<<endl;
	message ();
	message ();
	dout<<"End"<<endl;

	int k;
	cin>>k;
	return 0;
}