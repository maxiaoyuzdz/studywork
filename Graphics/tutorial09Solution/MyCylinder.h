#pragma once

#include "GXBase.h"

class MyCylinder {
private:
	float (*_vertexarrayTop)[3];	// contains the vertices
	float (*_vertexarrayBody)[3];	// contains the vertices
	float (*_vertexarrayBottom)[3];	// contains the vertices
	float (*_normalarrayTop)[3];	// contains the normals to each top and bottom vertex
	float (*_normalarrayBody)[3];	// contains the normals to each top and bottom vertex
	float (*_normalarrayBottom)[3];	// contains the normals to each top and bottom vertex
	GLuint *_indexarrayTop;			// index array that defines the polygons
	GLuint *_indexarrayBody;			// index array that defines the polygons
	GLuint *_indexarrayBottom;			// index array that defines the polygons
	float (*_texarrayTop)[2];	// texture coordinates for each vertex
	float (*_texarrayBody)[2];		// texture coordinates for each vertex
	float (*_texarrayBottom)[2];	// texture coordinates for each vertex
	int _slices;
	int _stacks;

public:
	MyCylinder();
	~MyCylinder();
	bool create(GLfloat radius, GLfloat height, int slices, int stacks, bool texture);
	void draw() const;

private:
	void DeallocateMemory();
};