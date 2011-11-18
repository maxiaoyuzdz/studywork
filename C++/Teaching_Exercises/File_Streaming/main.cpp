#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char* agrv[])
{
	
	double x,y;
	x = 99;
	y = 0;
	

	ofstream fout("Output.txt");
	fout<<"Output file"<<endl;
	fout<<x<<" "<<y<<endl;
	ifstream fin("Input.txt");
	fin>>x>>y;

	cout<<x<<" "<<y<<endl;

	double x1  =1.23456789, y1= 1234.56789;

	cout<<setw(20)<<x1<<setw(20)<<y1<<endl;

	cout<<setw(20)<<setprecision(3)<<x1<<setw(20)<<setprecision(3)<<y1<<endl;


	cin>>x;

	return 0;
}