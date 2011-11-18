#include "colour.h"

Colour::Colour(unsigned char red, unsigned char green, unsigned char blue)
{
	r = red;
	g = green;
	b = blue;
}

Colour::~Colour(void)
{
}

unsigned char Colour::Red() const
{
	return r;
}

unsigned char Colour::Green() const
{
	return g;
}

unsigned char Colour::Blue() const
{
	return b;
}
