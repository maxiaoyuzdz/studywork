#pragma once
#include "glex.h"

struct Vertex
	{
	GLfloat position[3];        // x, y, z
	GLfloat texture[2];			// u, v
	GLfloat normal[3];			// nx, ny, nz
	GLfloat colour[4];			// r, b, g, a
	GLubyte padding[16];		// padded to 64 bytes for performance
	};

// Location/Normals
#define X_POS 0
#define Y_POS 1
#define Z_POS 2
// Texture Coordinates
#define U_POS 0
#define V_POS 1
// Colours
#define R_POS 0
#define G_POS 1
#define B_POS 2
#define A_POS 3

class Cube
	: public glex
{
public:

	

	Vertex (*_vertices);
	GLubyte (*_indices);
	GLfloat (*_vertices_normals_and_colours);
	GLfloat (*_vertices_normals_and_colours_elements);
	GLfloat (*_vertices_normals_and_colours_quads);
	GLfloat (*_verticesArray);
	GLfloat (*_normalsArray);
	GLfloat (*_coloursArray);
	GLfloat (*_texturesArray);

	GLfloat (*_drawRangeVertices);
	GLubyte (*_drawRangeIndices);
	GLubyte (*_drawRangeIndicesQuads);

	GLuint _vboId;                  // ID of VBO for vertex arrays (to store vertex coords and normals)
	GLuint _indexVboId;                  // ID of VBO for index array

	int _numberOfVertices;
	int _numberOfIndices;
	
	Cube(void);
	~Cube(void);


	void fillCubeVerticesObject(void);
	void fillCubeIndicesObject(void);
	
	void drawUsingVertexBufferObjects(void);



	void buildVBOs(void);
};

