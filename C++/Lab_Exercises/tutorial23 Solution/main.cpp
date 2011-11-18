#include <vld.h>
#include <iostream>
#include "Ball.h"
#include "Cube.h"
using namespace std;

void main(int, char**)
{
	//Ball *b = new Ball(Vector3d(20, 34, 25), 20);
	//b->setColour(Colour(255, 0, 0));

	//Cube *c = new Cube(Vector3d(40, -56, -6), 10);
	//c->setColour(Colour(0, 255, 0));

	//b->ApplyPhysics(0.1);  // update ball's position after 0.1s
	//c->ApplyPhysics(0.1);  // update cube's position after 0.1s

	//delete b;
	//delete c;

	Ball *b = new Ball(Vector3d(20, 34, 25), 20);
	b->setColour(Colour(255, 0, 0));

	Cube *c = new Cube(Vector3d(40, -56, -6), 10);
	c->setColour(Colour(0, 255, 0));

	NewtonianObject *list[2] = {b, c};
	for(int nObject = 0; nObject < 2; nObject++)
	{
		list[nObject]->ApplyPhysics(0.1); // update object's position after 0.1s
	}
	for(int nObject = 0; nObject < 2; nObject++)
		delete list[nObject];
}