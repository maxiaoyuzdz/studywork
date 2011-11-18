#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	int red = 0, green = 0, blue = 0;

	int color = 0;

	cout<<"input four integers, then encode them to a 32bit value"<<endl;
	cout<<"input Red value from 0 ~ 255"<<endl;
	cin>>red;

	cout<<"input Green value from 0 ~ 255"<<endl;
	cin>>green;
	cout<<"input Blue value from 0 ~ 255"<<endl;
	cin>>blue;

	cout<<"Encoding ..."<<endl;

	red = (red && 0x0000000F)<<28;
	green = (green && 0x0000000F)<<20;
	blue = (blue && 0x0000000F)<<12;

	color = red+ green + blue;


	cout<<"color value = "<<color<<endl;


	cin>>red;

}