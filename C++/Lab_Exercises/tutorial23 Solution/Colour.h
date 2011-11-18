#pragma once

class Colour
{
public:
	Colour(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0);
	~Colour(void);
	unsigned char Red() const;
	unsigned char Green() const;
	unsigned char Blue() const;

private:
	unsigned char r, g, b;
};
