#include <iostream>
using namespace std;

void main(int *argc, char *argv)
{
	int red, green, blue, alpha;
	unsigned int colour;

	// Read in 4 colour channels (RGBA 0-255)
	do {
		cout << "Please enter 4 integers (0-255) in the order Red, Green, Blue, Alpha" << endl;
		cin >> red >> green >> blue >> alpha;
	} while (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255 || alpha < 0 || alpha > 255);

	// Convert to 32bit number
	colour  = red   << 24;
	colour |= green << 16;
	colour |= blue  <<  8;
	colour |= alpha;

	// Output 32bit colour
	cout << "32bit colour:" << colour;
	printf(" Hex:%x", colour);
	cout << endl;

	// extract RGBA info from 32bit number (Version 1)
	red = green = blue = alpha = 0;
	red   = (colour & (255 << 24)) >> 24;
	green = (colour & (255 << 16)) >> 16;
	blue  = (colour & (255 << 8))  >> 8;
	alpha =  colour &  255;

	cout << "Red:" << red << " Green:" << green << " Blue:" << blue << " Alpha:" << alpha << endl;

	// extract RGBA info from 32bit number (Version 2)
	red = green = blue = alpha = 0;
	alpha = colour & 255;
	colour >>= 8;
	blue  = colour & 255;
	colour >>= 8;
	green = colour & 255;
	colour >>= 8;
	red   = colour;

	cout << "Red:" << red << " Green:" << green << " Blue:" << blue << " Alpha:" << alpha << endl;
}