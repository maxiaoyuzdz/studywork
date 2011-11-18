#include <iostream>

using namespace std;

namespace A{
	int i = 10;
}
namespace B{
	int i= 20;
}

int main(int argc, char* argv[]){
	using namespace A;
	int k;
	cout<<"i = "<<i
		<<" A::i="<<A::i
		<<" B::i="<<B::i<<endl;

	using B::i;

	cout<<"i="<<i
		<<" A::i="<<A::i
		<<" B::i="<<B::i
		<<endl;


	cin>>k;

	return 0;
}