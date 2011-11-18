#include "House.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

House::House(void)
{
	// load extensions when the OpenGL drawing context is created
	glex::Load();
	_numberOfVertices = 48;
	_numberOfIndices = 48;
	fillCubeVerticesObject();
	fillCubeIndicesObject();


	buildVBOs();
}


House::~House(void)
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

void House::Initialize(){}

void House::Update(){}

void House::Draw(){
	this->drawUsingVertexBufferObjects();
}






void House::drawUsingVertexBufferObjects()
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
	// GL_LINE_LOOP
	// GL_TRIANGLES
	glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));

	// Disable our client state back to normal drawing
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}




void House::buildVBOs()
{
	_vboId = 0;                  // ID of VBO for vertex arrays (to store vertex coords and normals)	

	// create vertex buffer objects, you need to delete them when program exits
	// Try to put both vertex coords array and vertex normal array in the same buffer object.
	// glBufferDataARB with NULL pointer reserves only memory space.
	// Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
	// target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STREAM_DRAW_ARB because we will update vertices every frame.
	glGenBuffersARB(1, &_vboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, _vboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(Vertex)*48, 0, GL_STATIC_DRAW_ARB);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(Vertex)*48, _vertices);                             // copy vertices starting from 0 offest

	//these function is very interesting
	//I can depart Vertex to small arrays, easy to use
	// float  = 4 bytes , 3*4 = 12
	int k = sizeof(Vertex);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));


	_indexVboId = 0;
	glGenBuffers(1, &_indexVboId); // Generate buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexVboId); // Bind the element array buffer
	// Upload the index array, this can be done the same way as above (with NULL as the data, then a 
	// glBufferSubData call, but doing it all at once for convenience)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 48 * sizeof(GLubyte), _indices, GL_STATIC_DRAW);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void House::fillCubeVerticesObject()
{
	_vertices = new Vertex[48];

	// define the vertex array

	// 1
	_vertices[0].position[X_POS] = 1.000000;
	_vertices[0].position[Y_POS] = 0.999999;
	_vertices[0].position[Z_POS] = 1.000000;
	_vertices[0].normal[X_POS] = 0.719077;
	_vertices[0].normal[Y_POS] = 0.629566;
	_vertices[0].normal[Z_POS] = 0.294168;
	_vertices[0].colour[R_POS] = 1.0;
	_vertices[0].colour[G_POS] = 0.0;
	_vertices[0].colour[B_POS] = 0.0;
	_vertices[0].colour[A_POS] = 1.0;
	_vertices[0].texture[U_POS] = 0.0;
	_vertices[0].texture[V_POS] = 0.0;
	//2
	_vertices[1].position[X_POS] = -1.000000;
	_vertices[1].position[Y_POS] = 1.000000;
	_vertices[1].position[Z_POS] = 1.000000;
	_vertices[1].normal[X_POS] = -0.814722;
	_vertices[1].normal[Y_POS] = 0.475112;
	_vertices[1].normal[Z_POS] = 0.332286;
	_vertices[1].colour[R_POS] = 1.0;
	_vertices[1].colour[G_POS] = 0.0;
	_vertices[1].colour[B_POS] = 0.0;
	_vertices[1].colour[A_POS] = 1.0;
	_vertices[1].texture[U_POS] = 0.0;
	_vertices[1].texture[V_POS] = 0.0;
	//3
	_vertices[2].position[X_POS] = -0.002152;
	_vertices[2].position[Y_POS] = 1.000000;
	_vertices[2].position[Z_POS] = 2.019756;
	_vertices[2].normal[X_POS] = -0.000855;
	_vertices[2].normal[Y_POS] = 0.581133;
	_vertices[2].normal[Z_POS] = 0.813776;
	_vertices[2].colour[R_POS] = 1.0;
	_vertices[2].colour[G_POS] = 0.0;
	_vertices[2].colour[B_POS] = 0.0;
	_vertices[2].colour[A_POS] = 1.0;
	_vertices[2].texture[U_POS] = 0.0;
	_vertices[2].texture[V_POS] = 0.0;

	//4
	_vertices[3].position[X_POS] = 0.999999;
	_vertices[3].position[Y_POS] = -1.000001;
	_vertices[3].position[Z_POS] = 1.000000;
	_vertices[3].normal[X_POS] = 0.486007;
	_vertices[3].normal[Y_POS] = -0.851009;
	_vertices[3].normal[Z_POS] = 0.198828;
	_vertices[3].colour[R_POS] = 1.0;
	_vertices[3].colour[G_POS] = 0.0;
	_vertices[3].colour[B_POS] = 0.0;
	_vertices[3].colour[A_POS] = 1.0;
	_vertices[3].texture[U_POS] = 0.0;
	_vertices[3].texture[V_POS] = 0.0;
	//5
	_vertices[4].position[X_POS] = -0.002152;
	_vertices[4].position[Y_POS] = -1.000000;
	_vertices[4].position[Z_POS] = 2.019756;
	_vertices[4].normal[X_POS] = -0.001007;
	_vertices[4].normal[Y_POS] = -0.336253;
	_vertices[4].normal[Z_POS] = 0.941740;
	_vertices[4].colour[R_POS] = 1.0;
	_vertices[4].colour[G_POS] = 0.0;
	_vertices[4].colour[B_POS] = 0.0;
	_vertices[4].colour[A_POS] = 1.0;
	_vertices[4].texture[U_POS] = 0.0;
	_vertices[4].texture[V_POS] = 0.0;
	//6
	_vertices[5].position[X_POS] = -1.000000;
	_vertices[5].position[Y_POS] = -1.000000;
	_vertices[5].position[Z_POS] = 1.000000;
	_vertices[5].normal[X_POS] = -0.629078;
	_vertices[5].normal[Y_POS] = -0.733726;
	_vertices[5].normal[Z_POS] = 0.256569;
	_vertices[5].colour[R_POS] = 1.0;
	_vertices[5].colour[G_POS] = 0.0;
	_vertices[5].colour[B_POS] = 0.0;
	_vertices[5].colour[A_POS] = 1.0;
	_vertices[5].texture[U_POS] = 0.0;
	_vertices[5].texture[V_POS] = 0.0;
	//7
	_vertices[6].position[X_POS] = -1.000000;
	_vertices[6].position[Y_POS] = -1.000000;
	_vertices[6].position[Z_POS] = 1.000000;
	_vertices[6].normal[X_POS] = -0.629078;
	_vertices[6].normal[Y_POS] = -0.733726;
	_vertices[6].normal[Z_POS] = 0.256569;
	_vertices[6].colour[R_POS] = 1.0;
	_vertices[6].colour[G_POS] = 0.0;
	_vertices[6].colour[B_POS] = 0.0;
	_vertices[6].colour[A_POS] = 1.0;
	_vertices[6].texture[U_POS] = 0.0;
	_vertices[6].texture[V_POS] = 0.0;
	//8
	_vertices[7].position[X_POS] = -0.002152;
	_vertices[7].position[Y_POS] = -1.000000;
	_vertices[7].position[Z_POS] = 2.019756;
	_vertices[7].normal[X_POS] = -0.001007;
	_vertices[7].normal[Y_POS] = -0.336253;
	_vertices[7].normal[Z_POS] = 0.941740;
	_vertices[7].colour[R_POS] = 1.0;
	_vertices[7].colour[G_POS] = 0.0;
	_vertices[7].colour[B_POS] = 0.0;
	_vertices[7].colour[A_POS] = 1.0;
	_vertices[7].texture[U_POS] = 0.0;
	_vertices[7].texture[V_POS] = 0.0;
	//9
	_vertices[8].position[X_POS] = -1.000000;
	_vertices[8].position[Y_POS] = 1.000000;
	_vertices[8].position[Z_POS] = 1.000000;
	_vertices[8].normal[X_POS] = -0.814722;
	_vertices[8].normal[Y_POS] = 0.475112;
	_vertices[8].normal[Z_POS] = 0.332286;
	_vertices[8].colour[R_POS] = 1.0;
	_vertices[8].colour[G_POS] = 0.0;
	_vertices[8].colour[B_POS] = 0.0;
	_vertices[8].colour[A_POS] = 1.0;
	_vertices[8].texture[U_POS] = 0.0;
	_vertices[8].texture[V_POS] = 0.0;
	//10
	_vertices[9].position[X_POS] = -0.002152;
	_vertices[9].position[Y_POS] = -1.000000;
	_vertices[9].position[Z_POS] = 2.019756;
	_vertices[9].normal[X_POS] = -0.001007;
	_vertices[9].normal[Y_POS] = -0.336253;
	_vertices[9].normal[Z_POS] = 0.941740;
	_vertices[9].colour[R_POS] = 1.0;
	_vertices[9].colour[G_POS] = 0.0;
	_vertices[9].colour[B_POS] = 0.0;
	_vertices[9].colour[A_POS] = 1.0;
	_vertices[9].texture[U_POS] = 0.0;
	_vertices[9].texture[V_POS] = 0.0;
	//11
	_vertices[10].position[X_POS] = -0.002152;
	_vertices[10].position[Y_POS] = 1.000000;
	_vertices[10].position[Z_POS] = 2.019756;
	_vertices[10].normal[X_POS] = -0.000855;
	_vertices[10].normal[Y_POS] = 0.581133;
	_vertices[10].normal[Z_POS] = 0.813776;
	_vertices[10].colour[R_POS] = 1.0;
	_vertices[10].colour[G_POS] = 0.0;
	_vertices[10].colour[B_POS] = 0.0;
	_vertices[10].colour[A_POS] = 1.0;
	_vertices[10].texture[U_POS] = 0.0;
	_vertices[10].texture[V_POS] = 0.0;
	//12
	_vertices[11].position[X_POS] = -1.000000;
	_vertices[11].position[Y_POS] = 1.000000;
	_vertices[11].position[Z_POS] = 1.000000;
	_vertices[11].normal[X_POS] = -0.814722;
	_vertices[11].normal[Y_POS] = 0.475112;
	_vertices[11].normal[Z_POS] = 0.332286;
	_vertices[11].colour[R_POS] = 1.0;
	_vertices[11].colour[G_POS] = 0.0;
	_vertices[11].colour[B_POS] = 0.0;
	_vertices[11].colour[A_POS] = 1.0;
	_vertices[11].texture[U_POS] = 0.0;
	_vertices[11].texture[V_POS] = 0.0;
	//13
	_vertices[12].position[X_POS] = 1.000000;
	_vertices[12].position[Y_POS] = 0.999999;
	_vertices[12].position[Z_POS] = 1.000000;
	_vertices[12].normal[X_POS] = 0.719077;
	_vertices[12].normal[Y_POS] = 0.629566;
	_vertices[12].normal[Z_POS] = 0.294168;
	_vertices[12].colour[R_POS] = 1.0;
	_vertices[12].colour[G_POS] = 0.0;
	_vertices[12].colour[B_POS] = 0.0;
	_vertices[12].colour[A_POS] = 1.0;
	_vertices[12].texture[U_POS] = 0.0;
	_vertices[12].texture[V_POS] = 0.0;
	//14
	_vertices[13].position[X_POS] = -0.002152;
	_vertices[13].position[Y_POS] = 1.000000;
	_vertices[13].position[Z_POS] = 2.019756;
	_vertices[13].normal[X_POS] = -0.000855;
	_vertices[13].normal[Y_POS] = 0.581133;
	_vertices[13].normal[Z_POS] = 0.813776;
	_vertices[13].colour[R_POS] = 1.0;
	_vertices[13].colour[G_POS] = 0.0;
	_vertices[13].colour[B_POS] = 0.0;
	_vertices[13].colour[A_POS] = 1.0;
	_vertices[13].texture[U_POS] = 0.0;
	_vertices[13].texture[V_POS] = 0.0;
	//15
	_vertices[14].position[X_POS] = -0.002152;
	_vertices[14].position[Y_POS] = -1.000000;
	_vertices[14].position[Z_POS] = 2.019756;
	_vertices[14].normal[X_POS] = -0.001007;
	_vertices[14].normal[Y_POS] = -0.336253;
	_vertices[14].normal[Z_POS] = 0.941740;
	_vertices[14].colour[R_POS] = 1.0;
	_vertices[14].colour[G_POS] = 0.0;
	_vertices[14].colour[B_POS] = 0.0;
	_vertices[14].colour[A_POS] = 1.0;
	_vertices[14].texture[U_POS] = 0.0;
	_vertices[14].texture[V_POS] = 0.0;
	//16
	_vertices[15].position[X_POS] = 1.000000;
	_vertices[15].position[Y_POS] = 0.999999;
	_vertices[15].position[Z_POS] = 1.000000;
	_vertices[15].normal[X_POS] = 0.719077;
	_vertices[15].normal[Y_POS] = 0.629566;
	_vertices[15].normal[Z_POS] = 0.294168;
	_vertices[15].colour[R_POS] = 1.0;
	_vertices[15].colour[G_POS] = 0.0;
	_vertices[15].colour[B_POS] = 0.0;
	_vertices[15].colour[A_POS] = 1.0;
	_vertices[15].texture[U_POS] = 0.0;
	_vertices[15].texture[V_POS] = 0.0;
	//17
	_vertices[16].position[X_POS] = -0.002152;
	_vertices[16].position[Y_POS] = -1.000000;
	_vertices[16].position[Z_POS] = 2.019756;
	_vertices[16].normal[X_POS] = -0.001007;
	_vertices[16].normal[Y_POS] = -0.336253;
	_vertices[16].normal[Z_POS] = 0.941740;
	_vertices[16].colour[R_POS] = 1.0;
	_vertices[16].colour[G_POS] = 0.0;
	_vertices[16].colour[B_POS] = 0.0;
	_vertices[16].colour[A_POS] = 1.0;
	_vertices[16].texture[U_POS] = 0.0;
	_vertices[16].texture[V_POS] = 0.0;
	//18
	_vertices[17].position[X_POS] = 0.999999;
	_vertices[17].position[Y_POS] = -1.000001;
	_vertices[17].position[Z_POS] = 1.000000;
	_vertices[17].normal[X_POS] = 0.486007;
	_vertices[17].normal[Y_POS] = -0.851009;
	_vertices[17].normal[Z_POS] = 0.198828;
	_vertices[17].colour[R_POS] = 1.0;
	_vertices[17].colour[G_POS] = 0.0;
	_vertices[17].colour[B_POS] = 0.0;
	_vertices[17].colour[A_POS] = 1.0;
	_vertices[17].texture[U_POS] = 0.0;
	_vertices[17].texture[V_POS] = 0.0;
	//19
	_vertices[18].position[X_POS] = 1.000000;
	_vertices[18].position[Y_POS] = 0.999999;
	_vertices[18].position[Z_POS] = 1.000000;
	_vertices[18].normal[X_POS] = 0.719077;
	_vertices[18].normal[Y_POS] = 0.629566;
	_vertices[18].normal[Z_POS] = 0.294168;
	_vertices[18].colour[R_POS] = 1.0;
	_vertices[18].colour[G_POS] = 0.0;
	_vertices[18].colour[B_POS] = 0.0;
	_vertices[18].colour[A_POS] = 1.0;
	_vertices[18].texture[U_POS] = 0.0;
	_vertices[18].texture[V_POS] = 0.0;
	//20
	_vertices[19].position[X_POS] = 1.000000;
	_vertices[19].position[Y_POS] = 1.000000;
	_vertices[19].position[Z_POS] = -1.000000;
	_vertices[19].normal[X_POS] = 0.408246;
	_vertices[19].normal[Y_POS] = 0.408246;
	_vertices[19].normal[Z_POS] = -0.816492;
	_vertices[19].colour[R_POS] = 1.0;
	_vertices[19].colour[G_POS] = 0.0;
	_vertices[19].colour[B_POS] = 0.0;
	_vertices[19].colour[A_POS] = 1.0;
	_vertices[19].texture[U_POS] = 0.0;
	_vertices[19].texture[V_POS] = 0.0;
	//21
	_vertices[20].position[X_POS] = -1.000000;
	_vertices[20].position[Y_POS] = 1.000000;
	_vertices[20].position[Z_POS] = -1.000000;
	_vertices[20].normal[X_POS] = -0.408246;
	_vertices[20].normal[Y_POS] = 0.816492;
	_vertices[20].normal[Z_POS] = -0.408246;
	_vertices[20].colour[R_POS] = 1.0;
	_vertices[20].colour[G_POS] = 0.0;
	_vertices[20].colour[B_POS] = 0.0;
	_vertices[20].colour[A_POS] = 1.0;
	_vertices[20].texture[U_POS] = 0.0;
	_vertices[20].texture[V_POS] = 0.0;
	//22
	_vertices[21].position[X_POS] = 1.000000;
	_vertices[21].position[Y_POS] = 0.999999;
	_vertices[21].position[Z_POS] = 1.000000;
	_vertices[21].normal[X_POS] = 0.719077;
	_vertices[21].normal[Y_POS] = 0.629566;
	_vertices[21].normal[Z_POS] = 0.294168;
	_vertices[21].colour[R_POS] = 1.0;
	_vertices[21].colour[G_POS] = 0.0;
	_vertices[21].colour[B_POS] = 0.0;
	_vertices[21].colour[A_POS] = 1.0;
	_vertices[21].texture[U_POS] = 0.0;
	_vertices[21].texture[V_POS] = 0.0;
	//23
	_vertices[22].position[X_POS] = -1.000000;
	_vertices[22].position[Y_POS] = 1.000000;
	_vertices[22].position[Z_POS] = -1.000000;
	_vertices[22].normal[X_POS] = -0.408246;
	_vertices[22].normal[Y_POS] = 0.816492;
	_vertices[22].normal[Z_POS] = -0.408246;
	_vertices[22].colour[R_POS] = 1.0;
	_vertices[22].colour[G_POS] = 0.0;
	_vertices[22].colour[B_POS] = 0.0;
	_vertices[22].colour[A_POS] = 1.0;
	_vertices[22].texture[U_POS] = 0.0;
	_vertices[22].texture[V_POS] = 0.0;
	//24
	_vertices[23].position[X_POS] = -1.000000;
	_vertices[23].position[Y_POS] = 1.000000;
	_vertices[23].position[Z_POS] = 1.000000;
	_vertices[23].normal[X_POS] = -0.814722;
	_vertices[23].normal[Y_POS] = 0.475112;
	_vertices[23].normal[Z_POS] = 0.332286;
	_vertices[23].colour[R_POS] = 1.0;
	_vertices[23].colour[G_POS] = 0.0;
	_vertices[23].colour[B_POS] = 0.0;
	_vertices[23].colour[A_POS] = 1.0;
	_vertices[23].texture[U_POS] = 0.0;
	_vertices[23].texture[V_POS] = 0.0;
	//25
	_vertices[24].position[X_POS] = -1.000000;
	_vertices[24].position[Y_POS] = -1.000000;
	_vertices[24].position[Z_POS] = -1.000000;
	_vertices[24].normal[X_POS] = -0.577349;
	_vertices[24].normal[Y_POS] = -0.577349;
	_vertices[24].normal[Z_POS] = -0.577349;
	_vertices[24].colour[R_POS] = 1.0;
	_vertices[24].colour[G_POS] = 0.0;
	_vertices[24].colour[B_POS] = 0.0;
	_vertices[24].colour[A_POS] = 1.0;
	_vertices[24].texture[U_POS] = 0.0;
	_vertices[24].texture[V_POS] = 0.0;
	//26
	_vertices[25].position[X_POS] = -1.000000;
	_vertices[25].position[Y_POS] = -1.000000;
	_vertices[25].position[Z_POS] = 1.000000;
	_vertices[25].normal[X_POS] = -0.629078;
	_vertices[25].normal[Y_POS] = -0.733726;
	_vertices[25].normal[Z_POS] = 0.256569;
	_vertices[25].colour[R_POS] = 1.0;
	_vertices[25].colour[G_POS] = 0.0;
	_vertices[25].colour[B_POS] = 0.0;
	_vertices[25].colour[A_POS] = 1.0;
	_vertices[25].texture[U_POS] = 0.0;
	_vertices[25].texture[V_POS] = 0.0;
	//27
	_vertices[26].position[X_POS] = -1.000000;
	_vertices[26].position[Y_POS] = 1.000000;
	_vertices[26].position[Z_POS] = 1.000000;
	_vertices[26].normal[X_POS] = -0.814722;
	_vertices[26].normal[Y_POS] = 0.475112;
	_vertices[26].normal[Z_POS] = 0.332286;
	_vertices[26].colour[R_POS] = 1.0;
	_vertices[26].colour[G_POS] = 0.0;
	_vertices[26].colour[B_POS] = 0.0;
	_vertices[26].colour[A_POS] = 1.0;
	_vertices[26].texture[U_POS] = 0.0;
	_vertices[26].texture[V_POS] = 0.0;
	//28
	_vertices[27].position[X_POS] = -1.000000;
	_vertices[27].position[Y_POS] = -1.000000;
	_vertices[27].position[Z_POS] = -1.000000;
	_vertices[27].normal[X_POS] = -0.577349;
	_vertices[27].normal[Y_POS] = -0.577349;
	_vertices[27].normal[Z_POS] = -0.577349;
	_vertices[27].colour[R_POS] = 1.0;
	_vertices[27].colour[G_POS] = 0.0;
	_vertices[27].colour[B_POS] = 0.0;
	_vertices[27].colour[A_POS] = 1.0;
	_vertices[27].texture[U_POS] = 0.0;
	_vertices[27].texture[V_POS] = 0.0;
	//29
	_vertices[28].position[X_POS] = -1.000000;
	_vertices[28].position[Y_POS] = 1.000000;
	_vertices[28].position[Z_POS] = 1.000000;
	_vertices[28].normal[X_POS] = -0.814722;
	_vertices[28].normal[Y_POS] = 0.475112;
	_vertices[28].normal[Z_POS] = 0.332286;
	_vertices[28].colour[R_POS] = 1.0;
	_vertices[28].colour[G_POS] = 0.0;
	_vertices[28].colour[B_POS] = 0.0;
	_vertices[28].colour[A_POS] = 1.0;
	_vertices[28].texture[U_POS] = 0.0;
	_vertices[28].texture[V_POS] = 0.0;
	//30
	_vertices[29].position[X_POS] = -1.000000;
	_vertices[29].position[Y_POS] = 1.000000;
	_vertices[29].position[Z_POS] = -1.000000;
	_vertices[29].normal[X_POS] = -0.408246;
	_vertices[29].normal[Y_POS] = 0.816492;
	_vertices[29].normal[Z_POS] = -0.408246;
	_vertices[29].colour[R_POS] = 1.0;
	_vertices[29].colour[G_POS] = 0.0;
	_vertices[29].colour[B_POS] = 0.0;
	_vertices[29].colour[A_POS] = 1.0;
	_vertices[29].texture[U_POS] = 0.0;
	_vertices[29].texture[V_POS] = 0.0;
	//31
	_vertices[30].position[X_POS] = 1.000000;
	_vertices[30].position[Y_POS] = -1.000000;
	_vertices[30].position[Z_POS] = -1.000000;
	_vertices[30].normal[X_POS] = 0.816492;
	_vertices[30].normal[Y_POS] = -0.408246;
	_vertices[30].normal[Z_POS] = -0.408246;
	_vertices[30].colour[R_POS] = 1.0;
	_vertices[30].colour[G_POS] = 0.0;
	_vertices[30].colour[B_POS] = 0.0;
	_vertices[30].colour[A_POS] = 1.0;
	_vertices[30].texture[U_POS] = 0.0;
	_vertices[30].texture[V_POS] = 0.0;
	//32
	_vertices[31].position[X_POS] = 0.999999;
	_vertices[31].position[Y_POS] = -1.000001;
	_vertices[31].position[Z_POS] = 1.000000;
	_vertices[31].normal[X_POS] = 0.486007;
	_vertices[31].normal[Y_POS] = -0.851009;
	_vertices[31].normal[Z_POS] = 0.198828;
	_vertices[31].colour[R_POS] = 1.0;
	_vertices[31].colour[G_POS] = 0.0;
	_vertices[31].colour[B_POS] = 0.0;
	_vertices[31].colour[A_POS] = 1.0;
	_vertices[31].texture[U_POS] = 0.0;
	_vertices[31].texture[V_POS] = 0.0;
	//33
	_vertices[32].position[X_POS] = -1.000000;
	_vertices[32].position[Y_POS] = -1.000000;
	_vertices[32].position[Z_POS] = -1.000000;
	_vertices[32].normal[X_POS] = -0.577349;
	_vertices[32].normal[Y_POS] = -0.577349;
	_vertices[32].normal[Z_POS] = -0.577349;
	_vertices[32].colour[R_POS] = 1.0;
	_vertices[32].colour[G_POS] = 0.0;
	_vertices[32].colour[B_POS] = 0.0;
	_vertices[32].colour[A_POS] = 1.0;
	_vertices[32].texture[U_POS] = 0.0;
	_vertices[32].texture[V_POS] = 0.0;
	//34
	_vertices[33].position[X_POS] = 0.999999;
	_vertices[33].position[Y_POS] = -1.000001;
	_vertices[33].position[Z_POS] = 1.000000;
	_vertices[33].normal[X_POS] = 0.486007;
	_vertices[33].normal[Y_POS] = -0.851009;
	_vertices[33].normal[Z_POS] = 0.198828;
	_vertices[33].colour[R_POS] = 1.0;
	_vertices[33].colour[G_POS] = 0.0;
	_vertices[33].colour[B_POS] = 0.0;
	_vertices[33].colour[A_POS] = 1.0;
	_vertices[33].texture[U_POS] = 0.0;
	_vertices[33].texture[V_POS] = 0.0;
	//35
	_vertices[34].position[X_POS] = -1.000000;
	_vertices[34].position[Y_POS] = -1.000000;
	_vertices[34].position[Z_POS] = 1.000000;
	_vertices[34].normal[X_POS] = -0.629078;
	_vertices[34].normal[Y_POS] = -0.733726;
	_vertices[34].normal[Z_POS] = 0.256569;
	_vertices[34].colour[R_POS] = 1.0;
	_vertices[34].colour[G_POS] = 0.0;
	_vertices[34].colour[B_POS] = 0.0;
	_vertices[34].colour[A_POS] = 1.0;
	_vertices[34].texture[U_POS] = 0.0;
	_vertices[34].texture[V_POS] = 0.0;
	//36
	_vertices[35].position[X_POS] = -1.000000;
	_vertices[35].position[Y_POS] = -1.000000;
	_vertices[35].position[Z_POS] = -1.000000;
	_vertices[35].normal[X_POS] = -0.577349;
	_vertices[35].normal[Y_POS] = -0.577349;
	_vertices[35].normal[Z_POS] = -0.577349;
	_vertices[35].colour[R_POS] = 1.0;
	_vertices[35].colour[G_POS] = 0.0;
	_vertices[35].colour[B_POS] = 0.0;
	_vertices[35].colour[A_POS] = 1.0;
	_vertices[35].texture[U_POS] = 0.0;
	_vertices[35].texture[V_POS] = 0.0;
	//37
	_vertices[36].position[X_POS] = 1.000000;
	_vertices[36].position[Y_POS] = 1.000000;
	_vertices[36].position[Z_POS] = -1.000000;
	_vertices[36].normal[X_POS] = 0.408246;
	_vertices[36].normal[Y_POS] = 0.408246;
	_vertices[36].normal[Z_POS] = -0.816492;
	_vertices[36].colour[R_POS] = 1.0;
	_vertices[36].colour[G_POS] = 0.0;
	_vertices[36].colour[B_POS] = 0.0;
	_vertices[36].colour[A_POS] = 1.0;
	_vertices[36].texture[U_POS] = 0.0;
	_vertices[36].texture[V_POS] = 0.0;
	//38
	_vertices[37].position[X_POS] = 1.000000;
	_vertices[37].position[Y_POS] = 0.999999;
	_vertices[37].position[Z_POS] = 1.000000;
	_vertices[37].normal[X_POS] = 0.719077;
	_vertices[37].normal[Y_POS] = 0.629566;
	_vertices[37].normal[Z_POS] = 0.294168;
	_vertices[37].colour[R_POS] = 1.0;
	_vertices[37].colour[G_POS] = 0.0;
	_vertices[37].colour[B_POS] = 0.0;
	_vertices[37].colour[A_POS] = 1.0;
	_vertices[37].texture[U_POS] = 0.0;
	_vertices[37].texture[V_POS] = 0.0;
	//39
	_vertices[38].position[X_POS] = 1.000000;
	_vertices[38].position[Y_POS] = -1.000000;
	_vertices[38].position[Z_POS] = -1.000000;
	_vertices[38].normal[X_POS] = 0.816492;
	_vertices[38].normal[Y_POS] = -0.408246;
	_vertices[38].normal[Z_POS] = -0.408246;
	_vertices[38].colour[R_POS] = 1.0;
	_vertices[38].colour[G_POS] = 0.0;
	_vertices[38].colour[B_POS] = 0.0;
	_vertices[38].colour[A_POS] = 1.0;
	_vertices[38].texture[U_POS] = 0.0;
	_vertices[38].texture[V_POS] = 0.0;
	//40
	_vertices[39].position[X_POS] = 1.000000;
	_vertices[39].position[Y_POS] = 0.999999;
	_vertices[39].position[Z_POS] = 1.000000;
	_vertices[39].normal[X_POS] = 0.719077;
	_vertices[39].normal[Y_POS] = 0.629566;
	_vertices[39].normal[Z_POS] = 0.294168;
	_vertices[39].colour[R_POS] = 1.0;
	_vertices[39].colour[G_POS] = 0.0;
	_vertices[39].colour[B_POS] = 0.0;
	_vertices[39].colour[A_POS] = 1.0;
	_vertices[39].texture[U_POS] = 0.0;
	_vertices[39].texture[V_POS] = 0.0;
	//41
	_vertices[40].position[X_POS] = 0.999999;
	_vertices[40].position[Y_POS] = -1.000001;
	_vertices[40].position[Z_POS] = 1.000000;
	_vertices[40].normal[X_POS] = 0.486007;
	_vertices[40].normal[Y_POS] = -0.851009;
	_vertices[40].normal[Z_POS] = 0.198828;
	_vertices[40].colour[R_POS] = 1.0;
	_vertices[40].colour[G_POS] = 0.0;
	_vertices[40].colour[B_POS] = 0.0;
	_vertices[40].colour[A_POS] = 1.0;
	_vertices[40].texture[U_POS] = 0.0;
	_vertices[40].texture[V_POS] = 0.0;
	//42
	_vertices[41].position[X_POS] = 1.000000;
	_vertices[41].position[Y_POS] = -1.000000;
	_vertices[41].position[Z_POS] = -1.000000;
	_vertices[41].normal[X_POS] = 0.816492;
	_vertices[41].normal[Y_POS] = -0.408246;
	_vertices[41].normal[Z_POS] = -0.408246;
	_vertices[41].colour[R_POS] = 1.0;
	_vertices[41].colour[G_POS] = 0.0;
	_vertices[41].colour[B_POS] = 0.0;
	_vertices[41].colour[A_POS] = 1.0;
	_vertices[41].texture[U_POS] = 0.0;
	_vertices[41].texture[V_POS] = 0.0;
	//43
	_vertices[42].position[X_POS] = 1.000000;
	_vertices[42].position[Y_POS] = 1.000000;
	_vertices[42].position[Z_POS] = -1.000000;
	_vertices[42].normal[X_POS] = 0.408246;
	_vertices[42].normal[Y_POS] = 0.408246;
	_vertices[42].normal[Z_POS] = -0.816492;
	_vertices[42].colour[R_POS] = 1.0;
	_vertices[42].colour[G_POS] = 0.0;
	_vertices[42].colour[B_POS] = 0.0;
	_vertices[42].colour[A_POS] = 1.0;
	_vertices[42].texture[U_POS] = 0.0;
	_vertices[42].texture[V_POS] = 0.0;
	//44
	_vertices[43].position[X_POS] = 1.000000;
	_vertices[43].position[Y_POS] = -1.000000;
	_vertices[43].position[Z_POS] = -1.000000;
	_vertices[43].normal[X_POS] = 0.816492;
	_vertices[43].normal[Y_POS] = -0.408246;
	_vertices[43].normal[Z_POS] = -0.408246;
	_vertices[43].colour[R_POS] = 1.0;
	_vertices[43].colour[G_POS] = 0.0;
	_vertices[43].colour[B_POS] = 0.0;
	_vertices[43].colour[A_POS] = 1.0;
	_vertices[43].texture[U_POS] = 0.0;
	_vertices[43].texture[V_POS] = 0.0;
	//45
	_vertices[44].position[X_POS] = -1.000000;
	_vertices[44].position[Y_POS] = -1.000000;
	_vertices[44].position[Z_POS] = -1.000000;
	_vertices[44].normal[X_POS] = -0.577349;
	_vertices[44].normal[Y_POS] = -0.577349;
	_vertices[44].normal[Z_POS] = -0.577349;
	_vertices[44].colour[R_POS] = 1.0;
	_vertices[44].colour[G_POS] = 0.0;
	_vertices[44].colour[B_POS] = 0.0;
	_vertices[44].colour[A_POS] = 1.0;
	_vertices[44].texture[U_POS] = 0.0;
	_vertices[44].texture[V_POS] = 0.0;
	//46
	_vertices[45].position[X_POS] = 1.000000;
	_vertices[45].position[Y_POS] = 1.000000;
	_vertices[45].position[Z_POS] = -1.000000;
	_vertices[45].normal[X_POS] = 0.408246;
	_vertices[45].normal[Y_POS] = 0.408246;
	_vertices[45].normal[Z_POS] = -0.816492;
	_vertices[45].colour[R_POS] = 1.0;
	_vertices[45].colour[G_POS] = 0.0;
	_vertices[45].colour[B_POS] = 0.0;
	_vertices[45].colour[A_POS] = 1.0;
	_vertices[45].texture[U_POS] = 0.0;
	_vertices[45].texture[V_POS] = 0.0;
	//47//
	_vertices[46].position[X_POS] = -1.000000;
	_vertices[46].position[Y_POS] = -1.000000;
	_vertices[46].position[Z_POS] = -1.000000;
	_vertices[46].normal[X_POS] = -0.577349;
	_vertices[46].normal[Y_POS] = -0.577349;
	_vertices[46].normal[Z_POS] = -0.577349;
	_vertices[46].colour[R_POS] = 1.0;
	_vertices[46].colour[G_POS] = 0.0;
	_vertices[46].colour[B_POS] = 0.0;
	_vertices[46].colour[A_POS] = 1.0;
	_vertices[46].texture[U_POS] = 0.0;
	_vertices[46].texture[V_POS] = 0.0;
	//48//
	_vertices[47].position[X_POS] = -1.000000;
	_vertices[47].position[Y_POS] = 1.000000;
	_vertices[47].position[Z_POS] = -1.000000;
	_vertices[47].normal[X_POS] = -0.408246;
	_vertices[47].normal[Y_POS] = 0.816492;
	_vertices[47].normal[Z_POS] = -0.408246;
	_vertices[47].colour[R_POS] = 1.0;
	_vertices[47].colour[G_POS] = 0.0;
	_vertices[47].colour[B_POS] = 0.0;
	_vertices[47].colour[A_POS] = 1.0;
	_vertices[47].texture[U_POS] = 0.0;
	_vertices[47].texture[V_POS] = 0.0;


}

//triangle
void House::fillCubeIndicesObject()
{
	_indices = new GLubyte[48];
	// 36/3 = 12 triangle / 2 = 6 face

	//16 faces * 3 = 48 vertex
	_indices[0] = 0;
	_indices[1] = 1;
	_indices[2] = 2;
	_indices[3] = 3;
	_indices[4] = 4;
	_indices[5] = 5;
	_indices[6] = 6;
	_indices[7] = 7;
	_indices[8] = 8;
	_indices[9] = 9;
	_indices[10] = 10;
	_indices[11] = 11;
	_indices[12] = 12;
	_indices[13] = 13;
	_indices[14] = 14;
	_indices[15] = 15;
	_indices[16] = 16;
	_indices[17] = 17;
	_indices[18] = 18;
	_indices[19] = 19;
	_indices[20] = 20;
	_indices[21] = 21;
	_indices[22] = 22;
	_indices[23] = 23;
	_indices[24] = 24;
	_indices[25] = 25;
	_indices[26] = 26;
	_indices[27] = 27;
	_indices[28] = 28;
	_indices[29] = 29;
	_indices[30] = 30;
	_indices[31] = 31;
	_indices[32] = 32;
	_indices[33] = 33;
	_indices[34] = 34;
	_indices[35] = 35;
	_indices[36] = 36;
	_indices[37] = 37;
	_indices[38] = 38;
	_indices[39] = 39;
	_indices[40] = 40;
	_indices[41] = 41;

	_indices[42] = 42;
	_indices[43] = 43;
	_indices[44] = 44;
	_indices[45] = 45;
	_indices[46] = 46;
	_indices[47] = 47;
}
