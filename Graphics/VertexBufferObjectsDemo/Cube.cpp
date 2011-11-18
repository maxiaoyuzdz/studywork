#include "Cube.h"
#include "gxbase.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

Cube::Cube(void)
{
	 // load extensions when the OpenGL drawing context is created
		glex::Load();
		_numberOfVertices = 24;
		_numberOfIndices = 36;
		fillCubeVerticesObject();
		fillCubeIndicesObject();
		fillCubeInterleavedVertexArray();
		fillCubeInterleavedVertexArrayElements();
		fillCubeInterleavedVertexArrayQuads();
		fillCubeSeparateVertexArrays();
		fillDrawRangeIndices();
		fillDrawRangeIndicesQuads();
		fillDrawRangeVertices();
		fillDisplayList();
		buildVBOs();	

}




Cube::~Cube(void)
{
	delete [] _vertices;
	delete [] _indices;	
	delete [] _vertices_normals_and_colours;
	delete [] _verticesArray;
	delete [] _normalsArray;
	delete [] _coloursArray;
	delete [] _texturesArray;
	delete [] _drawRangeVertices;
	delete [] _drawRangeIndices;
}

void Cube::drawImmediate() {
	

	int vertexArrayIndex = 0;
	glBegin(GL_TRIANGLES);
	for(int j=0;j<_numberOfIndices;j++) {
		
			vertexArrayIndex = _indices[j];
			
			glNormal3fv(_vertices[vertexArrayIndex].normal);
			glTexCoord2fv(_vertices[vertexArrayIndex].texture);
			glColor4fv(_vertices[vertexArrayIndex].colour);
			glVertex3fv(_vertices[vertexArrayIndex].position);		
		
	}
	glEnd();
	
	
}

void Cube::drawImmediateQuads() {
	

	int vertexArrayIndex = 0;
	glBegin(GL_QUADS);
	for(int j=0;j<_numberOfVertices;j++) {
		
			
			
			glNormal3fv(_vertices[j].normal);
			glTexCoord2fv(_vertices[j].texture);
			glColor4fv(_vertices[j].colour);
			glVertex3fv(_vertices[j].position);		
		
	}
	glEnd();
	
	
}

void Cube::drawArraysUsingSeparateVertexArrays()
{
	
	// enable pointers to vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);

	// enable pointers to normal arrays
    glEnableClientState(GL_NORMAL_ARRAY);

	// enable pointers to colour arrays
    glEnableClientState(GL_COLOR_ARRAY);

	// enable pointers to colour arrays
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  	
   
	// void glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per vertex (2, 3, or 4)
	// GLenum type -> vertex coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between vertices. If 0 then vertices are 'tightly packed' so data must be homogeneous ie all vertices.
	// const GLvoid *pointer -> pointer to the array of vertices.
	glVertexPointer(3, GL_FLOAT, 0, _verticesArray);

	// void glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per colour (2, 3, or 4)
	// GLenum type -> colour coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between colours. If 0 then colours are 'tightly packed' so data must be homogeneous ie all colours.
	// const GLvoid *pointer -> pointer to the array of colours.
	glTexCoordPointer(2, GL_FLOAT, 0, _texturesArray);

	// void glNormalPointer(GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLenum type -> normal coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between normals. If 0 then normals are 'tightly packed' so data must be homogeneous ie all normals.
	// const GLvoid *pointer -> pointer to the array of normals.
	glNormalPointer(GL_FLOAT, 0, _normalsArray);

	// void glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per colour (2, 3, or 4)
	// GLenum type -> colour coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between colours. If 0 then colours are 'tightly packed' so data must be homogeneous ie all colours.
	// const GLvoid *pointer -> pointer to the array of colours.
	glColorPointer(4, GL_FLOAT, 0, _coloursArray);

    glDrawArrays(GL_TRIANGLES, 0, _numberOfIndices);
	
    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
 
    glDisableClientState(GL_NORMAL_ARRAY);

	glDisableClientState(GL_COLOR_ARRAY);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Cube::drawArraysUsingSeparateVertexArraysQuads()
{
	
	// enable pointers to vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);

	// enable pointers to normal arrays
    glEnableClientState(GL_NORMAL_ARRAY);

	// enable pointers to colour arrays
    glEnableClientState(GL_COLOR_ARRAY);

	// enable pointers to colour arrays
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  	
   
	// void glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per vertex (2, 3, or 4)
	// GLenum type -> vertex coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between vertices. If 0 then vertices are 'tightly packed' so data must be homogeneous ie all vertices.
	// const GLvoid *pointer -> pointer to the array of vertices.
	glVertexPointer(3, GL_FLOAT, 0, _verticesArray);

	// void glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per colour (2, 3, or 4)
	// GLenum type -> colour coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between colours. If 0 then colours are 'tightly packed' so data must be homogeneous ie all colours.
	// const GLvoid *pointer -> pointer to the array of colours.
	glTexCoordPointer(2, GL_FLOAT, 0, _texturesArray);

	// void glNormalPointer(GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLenum type -> normal coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between normals. If 0 then normals are 'tightly packed' so data must be homogeneous ie all normals.
	// const GLvoid *pointer -> pointer to the array of normals.
	glNormalPointer(GL_FLOAT, 0, _normalsArray);

	// void glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per colour (2, 3, or 4)
	// GLenum type -> colour coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between colours. If 0 then colours are 'tightly packed' so data must be homogeneous ie all colours.
	// const GLvoid *pointer -> pointer to the array of colours.
	glColorPointer(4, GL_FLOAT, 0, _coloursArray);

    glDrawArrays(GL_QUADS, 0, _numberOfVertices);
	
    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
 
    glDisableClientState(GL_NORMAL_ARRAY);

	glDisableClientState(GL_COLOR_ARRAY);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Cube::drawArraysUsingInterleavedVertexArrays()
{
	
	// enable pointers to vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);

	// enable pointers to normal arrays
    glEnableClientState(GL_NORMAL_ARRAY);

	// enable pointers to colour arrays
    glEnableClientState(GL_COLOR_ARRAY);

	// enable pointers to colour arrays
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  	
   
	// void glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per vertex (2, 3, or 4)
	// GLenum type -> vertex coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between vertices. If 0 then vertices are 'tightly packed' so data must be homogeneous ie all vertices.
	// const GLvoid *pointer -> pointer to the array of vertices.
	glVertexPointer(3, GL_FLOAT, 12 * sizeof(GLfloat), _vertices_normals_and_colours);

	// void glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per colour (2, 3, or 4)
	// GLenum type -> colour coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between colours. If 0 then colours are 'tightly packed' so data must be homogeneous ie all colours.
	// const GLvoid *pointer -> pointer to the array of colours.
	glTexCoordPointer(2, GL_FLOAT, 12 * sizeof(GLfloat), &_vertices_normals_and_colours[3]);

	// void glNormalPointer(GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLenum type -> normal coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between normals. If 0 then normals are 'tightly packed' so data must be homogeneous ie all normals.
	// const GLvoid *pointer -> pointer to the array of normals.
	glNormalPointer(GL_FLOAT, 12 * sizeof(GLfloat), &_vertices_normals_and_colours[5]);

	// void glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per colour (2, 3, or 4)
	// GLenum type -> colour coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between colours. If 0 then colours are 'tightly packed' so data must be homogeneous ie all colours.
	// const GLvoid *pointer -> pointer to the array of colours.
	glColorPointer(4, GL_FLOAT, 12 * sizeof(GLfloat), &_vertices_normals_and_colours[8]);

    glDrawArrays(GL_TRIANGLES, 0, _numberOfIndices);
	
    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
 
    glDisableClientState(GL_NORMAL_ARRAY);

	glDisableClientState(GL_COLOR_ARRAY);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Cube::drawRangeElementsUsingSeparateVertexArrays()
{
	

	// enable pointers to vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);

		
   
	// void glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per vertex (2, 3, or 4)
	// GLenum type -> vertex coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between vertices. If 0 then vertices are 'tightly packed' so data must be homogeneous ie all vertices.
	// const GLvoid *pointer -> pointer to the array of vertices.
	glVertexPointer(3, GL_FLOAT, 0, _drawRangeVertices);

	// front face
	glColor3f(1.0,0.0,0.0);
	glNormal3f(0.0,0.0,1.0);
	glDrawRangeElements(GL_TRIANGLES, 0, 5, 6, GL_UNSIGNED_BYTE, _drawRangeIndices);

	// back face
	glColor3f(1.0,1.0,0.0);
	glNormal3f(0.0,0.0,-1.0);
	glDrawRangeElements(GL_TRIANGLES, 6, 11, 6, GL_UNSIGNED_BYTE, _drawRangeIndices+6);

	// left face
	glColor3f(1.0,1.0,1.0);
	glNormal3f(-1.0,0.0,0.0);
	glDrawRangeElements(GL_TRIANGLES, 12, 17, 6, GL_UNSIGNED_BYTE, _drawRangeIndices+12);

	// right face
	glColor3f(0.0,1.0,1.0);
	glNormal3f(1.0,0.0,0.0);
	glDrawRangeElements(GL_TRIANGLES, 18, 23, 6, GL_UNSIGNED_BYTE, _drawRangeIndices+18);

	// top face
	glColor3f(0.0,0.0,1.0);
	glNormal3f(0.0,1.0,0.0);
	glDrawRangeElements(GL_TRIANGLES, 24, 29, 6, GL_UNSIGNED_BYTE, _drawRangeIndices+24);

	// bottom face
	glColor3f(0.0,1.0,0.0);
	glNormal3f(0.0,-1.0,0.0);
	glDrawRangeElements(GL_TRIANGLES, 30, 36, 6, GL_UNSIGNED_BYTE, _drawRangeIndices+30);
	
    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
 
   
}

void Cube::drawElementsUsingInterleavedVertexArrays()
{
	
	// enable pointers to vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);

	// enable pointers to normal arrays
    glEnableClientState(GL_NORMAL_ARRAY);

	// enable pointers to colour arrays
    glEnableClientState(GL_COLOR_ARRAY);

	// enable pointers to colour arrays
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  	
   
	

	// void glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per colour (2, 3, or 4)
	// GLenum type -> colour coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between colours. If 0 then colours are 'tightly packed' so data must be homogeneous ie all colours.
	// const GLvoid *pointer -> pointer to the array of colours.
	glTexCoordPointer(2, GL_FLOAT, 12 * sizeof(GLfloat), &_vertices_normals_and_colours_elements[3]);

	// void glNormalPointer(GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLenum type -> normal coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between normals. If 0 then normals are 'tightly packed' so data must be homogeneous ie all normals.
	// const GLvoid *pointer -> pointer to the array of normals.
	glNormalPointer(GL_FLOAT, 12 * sizeof(GLfloat), &_vertices_normals_and_colours_elements[5]);

	// void glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per colour (2, 3, or 4)
	// GLenum type -> colour coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between colours. If 0 then colours are 'tightly packed' so data must be homogeneous ie all colours.
	// const GLvoid *pointer -> pointer to the array of colours.
	glColorPointer(4, GL_FLOAT, 12 * sizeof(GLfloat), &_vertices_normals_and_colours_elements[8]);

	// void glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per vertex (2, 3, or 4)
	// GLenum type -> vertex coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between vertices. If 0 then vertices are 'tightly packed' so data must be homogeneous ie all vertices.
	// const GLvoid *pointer -> pointer to the array of vertices.
	glVertexPointer(3, GL_FLOAT, 12 * sizeof(GLfloat), _vertices_normals_and_colours_elements);

   glDrawElements(GL_TRIANGLES, _numberOfIndices, GL_UNSIGNED_BYTE, _indices);
	
    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
 
    glDisableClientState(GL_NORMAL_ARRAY);

	glDisableClientState(GL_COLOR_ARRAY);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Cube::drawElementsUsingInterleavedVertexArraysQuads()
{
	
	// enable pointers to vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);

	// enable pointers to normal arrays
    glEnableClientState(GL_NORMAL_ARRAY);

	// enable pointers to colour arrays
    glEnableClientState(GL_COLOR_ARRAY);

	// enable pointers to colour arrays
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  	
   
	

	// void glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per colour (2, 3, or 4)
	// GLenum type -> colour coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between colours. If 0 then colours are 'tightly packed' so data must be homogeneous ie all colours.
	// const GLvoid *pointer -> pointer to the array of colours.
	glTexCoordPointer(2, GL_FLOAT, 12 * sizeof(GLfloat), &_vertices_normals_and_colours_quads[3]);

	// void glNormalPointer(GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLenum type -> normal coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between normals. If 0 then normals are 'tightly packed' so data must be homogeneous ie all normals.
	// const GLvoid *pointer -> pointer to the array of normals.
	glNormalPointer(GL_FLOAT, 12 * sizeof(GLfloat), &_vertices_normals_and_colours_quads[5]);

	// void glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per colour (2, 3, or 4)
	// GLenum type -> colour coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between colours. If 0 then colours are 'tightly packed' so data must be homogeneous ie all colours.
	// const GLvoid *pointer -> pointer to the array of colours.
	glColorPointer(4, GL_FLOAT, 12 * sizeof(GLfloat), &_vertices_normals_and_colours_quads[8]);

	// void glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	// GLint size -> number of coordinates per vertex (2, 3, or 4)
	// GLenum type -> vertex coordinate type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
	// GLsizei stride -> byte offset between vertices. If 0 then vertices are 'tightly packed' so data must be homogeneous ie all vertices.
	// const GLvoid *pointer -> pointer to the array of vertices.
	glVertexPointer(3, GL_FLOAT, 12 * sizeof(GLfloat), _vertices_normals_and_colours_quads);

   glDrawElements(GL_QUADS, _numberOfVertices, GL_UNSIGNED_BYTE, _drawRangeIndicesQuads);
	
    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
 
    glDisableClientState(GL_NORMAL_ARRAY);

	glDisableClientState(GL_COLOR_ARRAY);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Cube::drawUsingVertexBufferObjects()
{
		// Bind our buffers much like we would for texturing
glBindBuffer(GL_ARRAY_BUFFER, _vboId);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexVboId);
 
// Set the state of what we are drawing (I don't think order matters here, but I like to do it in the same 
// order I set the pointers
//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
glEnableClientState(GL_COLOR_ARRAY);
glEnableClientState(GL_NORMAL_ARRAY);
glEnableClientState(GL_VERTEX_ARRAY);
 
// Resetup our pointers.  This doesn't reinitialise any data, only how we walk through it
//glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));
 
// Actually do our drawing, parameters are Primative (Triangles, Quads, Triangle Fans etc), Elements to 
// draw, Type of each element, Start Offset
//glDrawArrays( GL_TRIANGLES, 0,6 );
glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
 
// Disable our client state back to normal drawing
//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
glDisableClientState(GL_COLOR_ARRAY);
glDisableClientState(GL_NORMAL_ARRAY);
glDisableClientState(GL_VERTEX_ARRAY);
 glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   
}

void Cube::drawDisplayList()
{
	glCallList(1);                        // Draw The List
}

void Cube::fillDrawRangeIndices()
{
	_drawRangeIndices = new GLubyte[_numberOfVertices];
	// front face
		_drawRangeIndices[0] = 0;
		_drawRangeIndices[1] = 1;
		_drawRangeIndices[2] = 2;
		_drawRangeIndices[3] = 2;
		_drawRangeIndices[4] = 3;
		_drawRangeIndices[5] = 0;
		// back face
		_drawRangeIndices[6] = 4;
		_drawRangeIndices[7] = 5;
		_drawRangeIndices[8] = 6;
		_drawRangeIndices[9] = 6;
		_drawRangeIndices[10] = 7;
		_drawRangeIndices[11] = 4;
		// left face
		_drawRangeIndices[12] = 0;
		_drawRangeIndices[13] = 3;
		_drawRangeIndices[14] = 5;
		_drawRangeIndices[15] = 5;
		_drawRangeIndices[16] = 4;
		_drawRangeIndices[17] = 0;
		// right face
		_drawRangeIndices[18] = 1;
		_drawRangeIndices[19] = 7;
		_drawRangeIndices[20] = 6;
		_drawRangeIndices[21] = 6;
		_drawRangeIndices[22] = 2;
		_drawRangeIndices[23] = 1;
		// top face
		_drawRangeIndices[24] = 3;
		_drawRangeIndices[25] = 2;
		_drawRangeIndices[26] = 6;
		_drawRangeIndices[27] = 6;
		_drawRangeIndices[28] = 5;
		_drawRangeIndices[29] = 3;
		// bottom face
		_drawRangeIndices[30] = 0;
		_drawRangeIndices[31] = 4;
		_drawRangeIndices[32] = 7;
		_drawRangeIndices[33] = 7;
		_drawRangeIndices[34] = 1;
		_drawRangeIndices[35] = 0;
}

void Cube::fillDrawRangeIndicesQuads()
{
	_drawRangeIndicesQuads = new GLubyte[_numberOfVertices];
	// front face
		_drawRangeIndicesQuads[0] = 0;
		_drawRangeIndicesQuads[1] = 1;
		_drawRangeIndicesQuads[2] = 2;
		_drawRangeIndicesQuads[3] = 3;
		_drawRangeIndicesQuads[4] = 4;
		_drawRangeIndicesQuads[5] = 5;
		_drawRangeIndicesQuads[6] = 6;
		_drawRangeIndicesQuads[7] = 7;
		_drawRangeIndicesQuads[8] = 8;
		_drawRangeIndicesQuads[9] = 9;
		_drawRangeIndicesQuads[10] = 10;
		_drawRangeIndicesQuads[11] = 11;
		_drawRangeIndicesQuads[12] = 12;
		_drawRangeIndicesQuads[13] = 13;
		_drawRangeIndicesQuads[14] = 14;
		_drawRangeIndicesQuads[15] = 15;
		_drawRangeIndicesQuads[16] = 16;
		_drawRangeIndicesQuads[17] = 17;
		_drawRangeIndicesQuads[18] = 18;
		_drawRangeIndicesQuads[19] = 19;
		_drawRangeIndicesQuads[20] = 20;
		_drawRangeIndicesQuads[21] = 21;
		_drawRangeIndicesQuads[22] = 22;
		_drawRangeIndicesQuads[23] = 23;
		
		
}

void Cube::fillDrawRangeVertices()
{
	_drawRangeVertices = new GLfloat[24];
// front face
		_drawRangeVertices[0] = -0.5;	_drawRangeVertices[1] = -0.5;	_drawRangeVertices[2] = 0.5;
		_drawRangeVertices[3] = 0.5;	_drawRangeVertices[4] = -0.5;	_drawRangeVertices[5] = 0.5;
		_drawRangeVertices[6] = 0.5;	_drawRangeVertices[7] = 0.5;	_drawRangeVertices[8] = 0.5;
		_drawRangeVertices[9] = -0.5;	_drawRangeVertices[10] = 0.5;	_drawRangeVertices[11] = 0.5;
		// back face
		_drawRangeVertices[12] = -0.5;	_drawRangeVertices[13] = -0.5;	_drawRangeVertices[14] = -0.5;
		_drawRangeVertices[15] = -0.5;	_drawRangeVertices[16] = 0.5;	_drawRangeVertices[17] = -0.5;
		_drawRangeVertices[18] = 0.5;	_drawRangeVertices[19] = 0.5;	_drawRangeVertices[20] = -0.5;
		_drawRangeVertices[21] = 0.5;	_drawRangeVertices[22] = -0.5;	_drawRangeVertices[23] = -0.5;

}

void Cube::fillCubeInterleavedVertexArray() {
	
	_vertices_normals_and_colours = new GLfloat[_numberOfIndices*12];

	int vertexArrayIndex = 0;
	int interleavedIndex = 0;
	for(int j=0;j<_numberOfIndices;j++) {
		
			vertexArrayIndex = _indices[j];
			
			_vertices_normals_and_colours[interleavedIndex++] = _vertices[vertexArrayIndex].position[0];
			_vertices_normals_and_colours[interleavedIndex++] = _vertices[vertexArrayIndex].position[1];
			_vertices_normals_and_colours[interleavedIndex++] = _vertices[vertexArrayIndex].position[2];
			_vertices_normals_and_colours[interleavedIndex++] = _vertices[vertexArrayIndex].texture[0];
			_vertices_normals_and_colours[interleavedIndex++] = _vertices[vertexArrayIndex].texture[1];
			_vertices_normals_and_colours[interleavedIndex++] = _vertices[vertexArrayIndex].normal[0];
			_vertices_normals_and_colours[interleavedIndex++] = _vertices[vertexArrayIndex].normal[1];
			_vertices_normals_and_colours[interleavedIndex++] = _vertices[vertexArrayIndex].normal[2];
			_vertices_normals_and_colours[interleavedIndex++] = _vertices[vertexArrayIndex].colour[0];
			_vertices_normals_and_colours[interleavedIndex++] = _vertices[vertexArrayIndex].colour[1];
			_vertices_normals_and_colours[interleavedIndex++] = _vertices[vertexArrayIndex].colour[2];
			_vertices_normals_and_colours[interleavedIndex++] = _vertices[vertexArrayIndex].colour[3];
		
	}
	
	
	
}

void Cube::fillCubeInterleavedVertexArrayElements() {
	
	_vertices_normals_and_colours_elements = new GLfloat[_numberOfVertices*12];

	int interleavedIndex = 0;
	for(int j=0;j<_numberOfVertices;j++) {
		
			_vertices_normals_and_colours_elements[interleavedIndex++] = _vertices[j].position[0];
			_vertices_normals_and_colours_elements[interleavedIndex++] = _vertices[j].position[1];
			_vertices_normals_and_colours_elements[interleavedIndex++] = _vertices[j].position[2];
			_vertices_normals_and_colours_elements[interleavedIndex++] = _vertices[j].texture[0];
			_vertices_normals_and_colours_elements[interleavedIndex++] = _vertices[j].texture[1];
			_vertices_normals_and_colours_elements[interleavedIndex++] = _vertices[j].normal[0];
			_vertices_normals_and_colours_elements[interleavedIndex++] = _vertices[j].normal[1];
			_vertices_normals_and_colours_elements[interleavedIndex++] = _vertices[j].normal[2];
			_vertices_normals_and_colours_elements[interleavedIndex++] = _vertices[j].colour[0];
			_vertices_normals_and_colours_elements[interleavedIndex++] = _vertices[j].colour[1];
			_vertices_normals_and_colours_elements[interleavedIndex++] = _vertices[j].colour[2];
			_vertices_normals_and_colours_elements[interleavedIndex++] = _vertices[j].colour[3];
		
	}
	
	
	
}

void Cube::fillCubeInterleavedVertexArrayQuads() {
	
	_vertices_normals_and_colours_quads = new GLfloat[_numberOfVertices*12];

	int interleavedIndex = 0;
	for(int j=0;j<_numberOfVertices;j++) {
		
			_vertices_normals_and_colours_quads[interleavedIndex++] = _vertices[j].position[0];
			_vertices_normals_and_colours_quads[interleavedIndex++] = _vertices[j].position[1];
			_vertices_normals_and_colours_quads[interleavedIndex++] = _vertices[j].position[2];
			_vertices_normals_and_colours_quads[interleavedIndex++] = _vertices[j].texture[0];
			_vertices_normals_and_colours_quads[interleavedIndex++] = _vertices[j].texture[1];
			_vertices_normals_and_colours_quads[interleavedIndex++] = _vertices[j].normal[0];
			_vertices_normals_and_colours_quads[interleavedIndex++] = _vertices[j].normal[1];
			_vertices_normals_and_colours_quads[interleavedIndex++] = _vertices[j].normal[2];
			_vertices_normals_and_colours_quads[interleavedIndex++] = _vertices[j].colour[0];
			_vertices_normals_and_colours_quads[interleavedIndex++] = _vertices[j].colour[1];
			_vertices_normals_and_colours_quads[interleavedIndex++] = _vertices[j].colour[2];
			_vertices_normals_and_colours_quads[interleavedIndex++] = _vertices[j].colour[3];
		
	}
	
	
	
}

void Cube::fillCubeSeparateVertexArrays() {
	
	_verticesArray = new GLfloat[_numberOfIndices*3];
	_normalsArray = new GLfloat[_numberOfIndices*3];
	_texturesArray = new GLfloat[_numberOfIndices*2];
	_coloursArray = new GLfloat[_numberOfIndices*4];

	int vertexArrayIndex = 0;
	int verticesIndex = 0;
	int normalsIndex = 0;
	int texturesIndex = 0;
	int coloursIndex = 0;
	for(int j=0;j<_numberOfIndices;j++) {
		
			vertexArrayIndex = _indices[j];
			
			_verticesArray[verticesIndex++] = _vertices[vertexArrayIndex].position[0];
			_verticesArray[verticesIndex++] = _vertices[vertexArrayIndex].position[1];
			_verticesArray[verticesIndex++] = _vertices[vertexArrayIndex].position[2];
			_texturesArray[texturesIndex++] = _vertices[vertexArrayIndex].texture[0];
			_texturesArray[texturesIndex++] = _vertices[vertexArrayIndex].texture[1];
			_normalsArray[normalsIndex++] = _vertices[vertexArrayIndex].normal[0];
			_normalsArray[normalsIndex++] = _vertices[vertexArrayIndex].normal[1];
			_normalsArray[normalsIndex++] = _vertices[vertexArrayIndex].normal[2];
			_coloursArray[coloursIndex++] = _vertices[vertexArrayIndex].colour[0];
			_coloursArray[coloursIndex++] = _vertices[vertexArrayIndex].colour[1];
			_coloursArray[coloursIndex++] = _vertices[vertexArrayIndex].colour[2];
			_coloursArray[coloursIndex++] = _vertices[vertexArrayIndex].colour[3];
		
	}
	
	
	
}

void Cube::fillDisplayList()
{
	GLuint displayListID = glGenLists(1);
	glNewList(displayListID,GL_COMPILE);                          // New Compiled box Display List

	drawArraysUsingInterleavedVertexArrays();

	glEndList();                                    // Done Building The box List
}

void Cube::buildVBOs()
{
	_vboId = 0;                  // ID of VBO for vertex arrays (to store vertex coords and normals)	

    // create vertex buffer objects, you need to delete them when program exits
    // Try to put both vertex coords array and vertex normal array in the same buffer object.
    // glBufferDataARB with NULL pointer reserves only memory space.
    // Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
    // target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STREAM_DRAW_ARB because we will update vertices every frame.
		glGenBuffersARB(1, &_vboId);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, _vboId);
        glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(Vertex)*24, 0, GL_STATIC_DRAW_ARB);
        glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(Vertex)*24, _vertices);                             // copy vertices starting from 0 offest
       
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
		glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
		glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

		_indexVboId = 0;
		glGenBuffers(1, &_indexVboId); // Generate buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexVboId); // Bind the element array buffer
		// Upload the index array, this can be done the same way as above (with NULL as the data, then a 
		// glBufferSubData call, but doing it all at once for convenience)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLubyte), _indices, GL_STATIC_DRAW);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	/*	delete [] _vertices;
		_vertices = NULL;
		delete [] _indices;
		_indices = NULL;*/
}

void Cube::fillCubeVerticesObject()
{
		_vertices = new Vertex[24];
		
		// define the vertex array

		// front face
		_vertices[0].position[X_POS] = -0.5;
		_vertices[0].position[Y_POS] = 0.5;
		_vertices[0].position[Z_POS] = 0.5;
		_vertices[0].normal[X_POS] = 0.0;
		_vertices[0].normal[Y_POS] = 0.0;
		_vertices[0].normal[Z_POS] = 1.0;
		_vertices[0].colour[R_POS] = 1.0;
		_vertices[0].colour[G_POS] = 0.0;
		_vertices[0].colour[B_POS] = 0.0;
		_vertices[0].colour[A_POS] = 1.0;
		_vertices[0].texture[U_POS] = 0.0;
		_vertices[0].texture[V_POS] = 0.0;

		_vertices[1].position[X_POS] = -0.5;
		_vertices[1].position[Y_POS] = -0.5;
		_vertices[1].position[Z_POS] = 0.5;
		_vertices[1].normal[X_POS] = 0.0;
		_vertices[1].normal[Y_POS] = 0.0;
		_vertices[1].normal[Z_POS] = 1.0;
		_vertices[1].colour[R_POS] = 1.0;
		_vertices[1].colour[G_POS] = 0.0;
		_vertices[1].colour[B_POS] = 0.0;
		_vertices[1].colour[A_POS] = 1.0;
		_vertices[1].texture[U_POS] = 0.0;
		_vertices[1].texture[V_POS] = 1.0;

		_vertices[2].position[X_POS] = 0.5;
		_vertices[2].position[Y_POS] = -0.5;
		_vertices[2].position[Z_POS] = 0.5;
		_vertices[2].normal[X_POS] = 0.0;
		_vertices[2].normal[Y_POS] = 0.0;
		_vertices[2].normal[Z_POS] = 1.0;
		_vertices[2].colour[R_POS] = 1.0;
		_vertices[2].colour[G_POS] = 0.0;
		_vertices[2].colour[B_POS] = 0.0;
		_vertices[2].colour[A_POS] = 1.0;
		_vertices[2].texture[U_POS] = 1.0;
		_vertices[2].texture[V_POS] = 1.0;

		_vertices[3].position[X_POS] = 0.5;
		_vertices[3].position[Y_POS] = 0.5;
		_vertices[3].position[Z_POS] = 0.5;
		_vertices[3].normal[X_POS] = 0.0;
		_vertices[3].normal[Y_POS] = 0.0;
		_vertices[3].normal[Z_POS] = 1.0;
		_vertices[3].colour[R_POS] = 1.0;
		_vertices[3].colour[G_POS] = 0.0;
		_vertices[3].colour[B_POS] = 0.0;
		_vertices[3].colour[A_POS] = 1.0;
		_vertices[3].texture[U_POS] = 1.0;
		_vertices[3].texture[V_POS] = 0.0;

		// back face
		_vertices[4].position[X_POS] = -0.5;
		_vertices[4].position[Y_POS] = -0.5;
		_vertices[4].position[Z_POS] = -0.5;
		_vertices[4].normal[X_POS] = 0.0;
		_vertices[4].normal[Y_POS] = 0.0;
		_vertices[4].normal[Z_POS] = -1.0;
		_vertices[4].colour[R_POS] = 1.0;
		_vertices[4].colour[G_POS] = 1.0;
		_vertices[4].colour[B_POS] = 0.0;
		_vertices[4].colour[A_POS] = 1.0;
		_vertices[4].texture[U_POS] = 0.0;
		_vertices[4].texture[V_POS] = 0.0;

		_vertices[5].position[X_POS] = -0.5;
		_vertices[5].position[Y_POS] = 0.5;
		_vertices[5].position[Z_POS] = -0.5;
		_vertices[5].normal[X_POS] = 0.0;
		_vertices[5].normal[Y_POS] = 0.0;
		_vertices[5].normal[Z_POS] = -1.0;
		_vertices[5].colour[R_POS] = 1.0;
		_vertices[5].colour[G_POS] = 1.0;
		_vertices[5].colour[B_POS] = 0.0;
		_vertices[5].colour[A_POS] = 1.0;
		_vertices[5].texture[U_POS] = 0.0;
		_vertices[5].texture[V_POS] = 0.0;

		_vertices[6].position[X_POS] = 0.5;
		_vertices[6].position[Y_POS] = 0.5;
		_vertices[6].position[Z_POS] = -0.5;
		_vertices[6].normal[X_POS] = 0.0;
		_vertices[6].normal[Y_POS] = 0.0;
		_vertices[6].normal[Z_POS] = -1.0;
		_vertices[6].colour[R_POS] = 1.0;
		_vertices[6].colour[G_POS] = 1.0;
		_vertices[6].colour[B_POS] = 0.0;
		_vertices[6].colour[A_POS] = 1.0;
		_vertices[6].texture[U_POS] = 0.0;
		_vertices[6].texture[V_POS] = 0.0;

		_vertices[7].position[X_POS] = 0.5;
		_vertices[7].position[Y_POS] = -0.5;
		_vertices[7].position[Z_POS] = -0.5;
		_vertices[7].normal[X_POS] = 0.0;
		_vertices[7].normal[Y_POS] = 0.0;
		_vertices[7].normal[Z_POS] = -1.0;
		_vertices[7].colour[R_POS] = 1.0;
		_vertices[7].colour[G_POS] = 1.0;
		_vertices[7].colour[B_POS] = 0.0;
		_vertices[7].colour[A_POS] = 1.0;
		_vertices[7].texture[U_POS] = 0.0;
		_vertices[7].texture[V_POS] = 0.0;

		// left face
		_vertices[8].position[X_POS] = -0.5;
		_vertices[8].position[Y_POS] = -0.5;
		_vertices[8].position[Z_POS] = 0.5;
		_vertices[8].normal[X_POS] = -1.0;
		_vertices[8].normal[Y_POS] = 0.0;
		_vertices[8].normal[Z_POS] = 0.0;
		_vertices[8].colour[R_POS] = 1.0;
		_vertices[8].colour[G_POS] = 1.0;
		_vertices[8].colour[B_POS] = 1.0;
		_vertices[8].colour[A_POS] = 1.0;
		_vertices[8].texture[U_POS] = 0.0;
		_vertices[8].texture[V_POS] = 0.0;

		_vertices[9].position[X_POS] = -0.5;
		_vertices[9].position[Y_POS] = 0.5;
		_vertices[9].position[Z_POS] = 0.5;
		_vertices[9].normal[X_POS] = -1.0;
		_vertices[9].normal[Y_POS] = 0.0;
		_vertices[9].normal[Z_POS] = 0.0;
		_vertices[9].colour[R_POS] = 1.0;
		_vertices[9].colour[G_POS] = 1.0;
		_vertices[9].colour[B_POS] = 1.0;
		_vertices[9].colour[A_POS] = 1.0;
		_vertices[9].texture[U_POS] = 0.0;
		_vertices[9].texture[V_POS] = 0.0;

		_vertices[10].position[X_POS] = -0.5;
		_vertices[10].position[Y_POS] = 0.5;
		_vertices[10].position[Z_POS] = -0.5;
		_vertices[10].normal[X_POS] = -1.0;
		_vertices[10].normal[Y_POS] = 0.0;
		_vertices[10].normal[Z_POS] = 0.0;
		_vertices[10].colour[R_POS] = 1.0;
		_vertices[10].colour[G_POS] = 1.0;
		_vertices[10].colour[B_POS] = 1.0;
		_vertices[10].colour[A_POS] = 1.0;
		_vertices[10].texture[U_POS] = 0.0;
		_vertices[10].texture[V_POS] = 0.0;

		_vertices[11].position[X_POS] = -0.5;
		_vertices[11].position[Y_POS] = -0.5;
		_vertices[11].position[Z_POS] = -0.5;
		_vertices[11].normal[X_POS] = -1.0;
		_vertices[11].normal[Y_POS] = 0.0;
		_vertices[11].normal[Z_POS] = 0.0;
		_vertices[11].colour[R_POS] = 1.0;
		_vertices[11].colour[G_POS] = 1.0;
		_vertices[11].colour[B_POS] = 1.0;
		_vertices[11].colour[A_POS] = 1.0;
		_vertices[11].texture[U_POS] = 0.0;
		_vertices[11].texture[V_POS] = 0.0;

		// right face
		_vertices[12].position[X_POS] = 0.5;
		_vertices[12].position[Y_POS] = -0.5;
		_vertices[12].position[Z_POS] = 0.5;
		_vertices[12].normal[X_POS] = 1.0;
		_vertices[12].normal[Y_POS] = 0.0;
		_vertices[12].normal[Z_POS] = 0.0;
		_vertices[12].colour[R_POS] = 0.0;
		_vertices[12].colour[G_POS] = 1.0;
		_vertices[12].colour[B_POS] = 1.0;
		_vertices[12].colour[A_POS] = 1.0;
		_vertices[12].texture[U_POS] = 0.0;
		_vertices[12].texture[V_POS] = 0.0;

		_vertices[13].position[X_POS] = 0.5;
		_vertices[13].position[Y_POS] = -0.5;
		_vertices[13].position[Z_POS] = -0.5;
		_vertices[13].normal[X_POS] = 1.0;
		_vertices[13].normal[Y_POS] = 0.0;
		_vertices[13].normal[Z_POS] = 0.0;
		_vertices[13].colour[R_POS] = 0.0;
		_vertices[13].colour[G_POS] = 1.0;
		_vertices[13].colour[B_POS] = 1.0;
		_vertices[13].colour[A_POS] = 1.0;
		_vertices[13].texture[U_POS] = 0.0;
		_vertices[13].texture[V_POS] = 0.0;

		_vertices[14].position[X_POS] = 0.5;
		_vertices[14].position[Y_POS] = 0.5;
		_vertices[14].position[Z_POS] = -0.5;
		_vertices[14].normal[X_POS] = 1.0;
		_vertices[14].normal[Y_POS] = 0.0;
		_vertices[14].normal[Z_POS] = 0.0;
		_vertices[14].colour[R_POS] = 0.0;
		_vertices[14].colour[G_POS] = 1.0;
		_vertices[14].colour[B_POS] = 1.0;
		_vertices[14].colour[A_POS] = 1.0;
		_vertices[14].texture[U_POS] = 0.0;
		_vertices[14].texture[V_POS] = 0.0;

		_vertices[15].position[X_POS] = 0.5;
		_vertices[15].position[Y_POS] = 0.5;
		_vertices[15].position[Z_POS] = 0.5;
		_vertices[15].normal[X_POS] = 1.0;
		_vertices[15].normal[Y_POS] = 0.0;
		_vertices[15].normal[Z_POS] = 0.0;
		_vertices[15].colour[R_POS] = 0.0;
		_vertices[15].colour[G_POS] = 1.0;
		_vertices[15].colour[B_POS] = 1.0;
		_vertices[15].colour[A_POS] = 1.0;
		_vertices[15].texture[U_POS] = 0.0;
		_vertices[15].texture[V_POS] = 0.0;

		// top face
		_vertices[16].position[X_POS] = -0.5;
		_vertices[16].position[Y_POS] = 0.5;
		_vertices[16].position[Z_POS] = 0.5;
		_vertices[16].normal[X_POS] = 0.0;
		_vertices[16].normal[Y_POS] = 1.0;
		_vertices[16].normal[Z_POS] = 0.0;
		_vertices[16].colour[R_POS] = 0.0;
		_vertices[16].colour[G_POS] = 0.0;
		_vertices[16].colour[B_POS] = 1.0;
		_vertices[16].colour[A_POS] = 1.0;
		_vertices[16].texture[U_POS] = 0.0;
		_vertices[16].texture[V_POS] = 0.0;

		_vertices[17].position[X_POS] = 0.5;
		_vertices[17].position[Y_POS] = 0.5;
		_vertices[17].position[Z_POS] = 0.5;
		_vertices[17].normal[X_POS] = 0.0;
		_vertices[17].normal[Y_POS] = 1.0;
		_vertices[17].normal[Z_POS] = 0.0;
		_vertices[17].colour[R_POS] = 0.0;
		_vertices[17].colour[G_POS] = 0.0;
		_vertices[17].colour[B_POS] = 1.0;
		_vertices[17].colour[A_POS] = 1.0;
		_vertices[17].texture[U_POS] = 0.0;
		_vertices[17].texture[V_POS] = 0.0;

		_vertices[18].position[X_POS] = 0.5;
		_vertices[18].position[Y_POS] = 0.5;
		_vertices[18].position[Z_POS] = -0.5;
		_vertices[18].normal[X_POS] = 0.0;
		_vertices[18].normal[Y_POS] = 1.0;
		_vertices[18].normal[Z_POS] = 0.0;
		_vertices[18].colour[R_POS] = 0.0;
		_vertices[18].colour[G_POS] = 0.0;
		_vertices[18].colour[B_POS] = 1.0;
		_vertices[18].colour[A_POS] = 1.0;
		_vertices[18].texture[U_POS] = 0.0;
		_vertices[18].texture[V_POS] = 0.0;

		_vertices[19].position[X_POS] = -0.5;
		_vertices[19].position[Y_POS] = 0.5;
		_vertices[19].position[Z_POS] = -0.5;
		_vertices[19].normal[X_POS] = 0.0;
		_vertices[19].normal[Y_POS] = 1.0;
		_vertices[19].normal[Z_POS] = 0.0;
		_vertices[19].colour[R_POS] = 0.0;
		_vertices[19].colour[G_POS] = 0.0;
		_vertices[19].colour[B_POS] = 1.0;
		_vertices[19].colour[A_POS] = 1.0;
		_vertices[19].texture[U_POS] = 0.0;
		_vertices[19].texture[V_POS] = 0.0;

		// bottom face
		_vertices[20].position[X_POS] = -0.5;
		_vertices[20].position[Y_POS] = -0.5;
		_vertices[20].position[Z_POS] = 0.5;
		_vertices[20].normal[X_POS] = 0.0;
		_vertices[20].normal[Y_POS] = -1.0;
		_vertices[20].normal[Z_POS] = 0.0;
		_vertices[20].colour[R_POS] = 0.0;
		_vertices[20].colour[G_POS] = 1.0;
		_vertices[20].colour[B_POS] = 0.0;
		_vertices[20].colour[A_POS] = 1.0;
		_vertices[20].texture[U_POS] = 0.0;
		_vertices[20].texture[V_POS] = 0.0;

		_vertices[21].position[X_POS] = -0.5;
		_vertices[21].position[Y_POS] = -0.5;
		_vertices[21].position[Z_POS] = -0.5;
		_vertices[21].normal[X_POS] = 0.0;
		_vertices[21].normal[Y_POS] = -1.0;
		_vertices[21].normal[Z_POS] = 0.0;
		_vertices[21].colour[R_POS] = 0.0;
		_vertices[21].colour[G_POS] = 1.0;
		_vertices[21].colour[B_POS] = 0.0;
		_vertices[21].colour[A_POS] = 1.0;
		_vertices[21].texture[U_POS] = 0.0;
		_vertices[21].texture[V_POS] = 0.0;

		_vertices[22].position[X_POS] = 0.5;
		_vertices[22].position[Y_POS] = -0.5;
		_vertices[22].position[Z_POS] = -0.5;
		_vertices[22].normal[X_POS] = 0.0;
		_vertices[22].normal[Y_POS] = -1.0;
		_vertices[22].normal[Z_POS] = 0.0;
		_vertices[22].colour[R_POS] = 0.0;
		_vertices[22].colour[G_POS] = 1.0;
		_vertices[22].colour[B_POS] = 0.0;
		_vertices[22].colour[A_POS] = 1.0;
		_vertices[22].texture[U_POS] = 0.0;
		_vertices[22].texture[V_POS] = 0.0;

		_vertices[23].position[X_POS] = 0.5;
		_vertices[23].position[Y_POS] = -0.5;
		_vertices[23].position[Z_POS] = 0.5;
		_vertices[23].normal[X_POS] = 0.0;
		_vertices[23].normal[Y_POS] = -1.0;
		_vertices[23].normal[Z_POS] = 0.0;
		_vertices[23].colour[R_POS] = 0.0;
		_vertices[23].colour[G_POS] = 1.0;
		_vertices[23].colour[B_POS] = 0.0;
		_vertices[23].colour[A_POS] = 1.0;
		_vertices[23].texture[U_POS] = 0.0;
		_vertices[23].texture[V_POS] = 0.0;

}

void Cube::fillCubeIndicesObject()
{
	_indices = new GLubyte[36];
		_indices[0] = 0;
		_indices[1] = 1;
		_indices[2] = 2;
		_indices[3] = 2;
		_indices[4] = 3;
		_indices[5] = 0;
		_indices[6] = 4;
		_indices[7] = 5;
		_indices[8] = 6;
		_indices[9] = 6;
		_indices[10] = 7;
		_indices[11] = 4;
		_indices[12] = 8;
		_indices[13] = 9;
		_indices[14] = 10;
		_indices[15] = 10;
		_indices[16] = 11;
		_indices[17] = 8;
		_indices[18] = 12;
		_indices[19] = 13;
		_indices[20] = 14;
		_indices[21] = 14;
		_indices[22] = 15;
		_indices[23] = 12;
		_indices[24] = 16;
		_indices[25] = 17;
		_indices[26] = 18;
		_indices[27] = 18;
		_indices[28] = 19;
		_indices[29] = 16;
		_indices[30] = 20;
		_indices[31] = 21;
		_indices[32] = 22;
		_indices[33] = 22;
		_indices[34] = 23;
		_indices[35] = 20;
}