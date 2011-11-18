#pragma once

#include "GXBase.h"

class MySphere {
private:
	float (*_vertexarray)[3];	// contains the vertices
	float (*_normalarray)[3];	// contains the normals to each vertex
	GLuint *_indexarray;		// index array that defines the polygons
	float (*_texarray)[2];		// texture coordinates for each vertex
	int _stacks, _slices;

public:
	MySphere();

	~MySphere();

	bool create(GLfloat radius, int slices, int stacks, bool texture);

	void draw() const;
};

