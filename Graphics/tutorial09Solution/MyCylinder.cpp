#include "MyCylinder.h"
#include <math.h>
#define PI  (float)3.1415926

MyCylinder::MyCylinder() {
	_vertexarrayTop = 0;
	_vertexarrayBody = 0;
	_vertexarrayBottom = 0;
	_normalarrayTop = 0;
	_normalarrayBody = 0;
	_normalarrayBottom = 0;
	_indexarrayTop = 0;
	_indexarrayBody = 0;
	_indexarrayBottom = 0;
	_texarrayTop = 0;
	_texarrayBody = 0;
	_texarrayBottom = 0;
}

MyCylinder::~MyCylinder() {
	DeallocateMemory();
}

void MyCylinder::DeallocateMemory()
{
	if(_vertexarrayTop) delete [] _vertexarrayTop;
	if(_vertexarrayBody) delete [] _vertexarrayBody;
	if(_vertexarrayBottom) delete [] _vertexarrayBottom;
	if(_normalarrayTop) delete [] _normalarrayTop;
	if(_normalarrayBody) delete [] _normalarrayBody;
	if(_normalarrayBottom) delete [] _normalarrayBottom;
	if(_indexarrayTop)  delete [] _indexarrayTop;
	if(_indexarrayBody)  delete [] _indexarrayBody;
	if(_indexarrayBottom)  delete [] _indexarrayBottom;
	if(_texarrayTop) delete [] _texarrayTop;
	if(_texarrayBody) delete [] _texarrayBody;
	if(_texarrayBottom) delete [] _texarrayBottom;
}

bool MyCylinder::create(GLfloat radius, GLfloat height, int slices, int stacks, bool texture) {
	float slice_inc;
	float stack_inc;
	float halfHeight;
	float currentHeight;
	int vertex_count;
	int index_count;

	_slices = slices;
	_stacks = stacks;

	if (slices < 3 || stacks < 2) return false;

	DeallocateMemory();
	_vertexarrayTop = new float[slices][3];
	_vertexarrayBody = new float[slices*stacks][3];
	_vertexarrayBottom = new float[slices][3];
	_normalarrayTop = new float[slices][3];
	_normalarrayBody = new float[slices*stacks][3];
	_normalarrayBottom = new float[slices][3];
	_texarrayTop = new float[slices][2];
	_texarrayBody = new float[slices*stacks][2];
	_texarrayBottom = new float[slices][2];
	_indexarrayTop = new GLuint[slices];
	_indexarrayBody = new GLuint[slices*(stacks-1)*4];
	_indexarrayBottom = new GLuint[slices];


	slice_inc = PI*2.0f/slices;

	halfHeight = currentHeight = height*0.5;
	stack_inc = height/(_stacks-1);


	// **** define the vertex/normal/texture arrays ****
	// Top
	vertex_count = 0;
	float angle = 0.0f;
	for(int slice = 0; slice < _slices; slice++)
	{
		_vertexarrayTop[vertex_count][0] = radius*cos(angle); 
		_vertexarrayTop[vertex_count][1] = halfHeight; 
		_vertexarrayTop[vertex_count][2] = -radius*sin(angle); 

		_normalarrayTop[vertex_count][0] = 0.0f; 
		_normalarrayTop[vertex_count][1] = 1.0f; 
		_normalarrayTop[vertex_count][2] = 0.0f;

		_texarrayTop[vertex_count][0] = cos(angle)*0.25f; 
		_texarrayTop[vertex_count++][1] = sin(angle)*0.25f; 

		angle += slice_inc;
	}

	// Body
	vertex_count = 0;
	angle = 0.0f;
	for(int stack = 0; stack < _stacks; stack++)
	{
		for(int slice = 0; slice < _slices; slice++)
		{
			_vertexarrayBody[vertex_count][0] = radius*cos(angle); 
			_vertexarrayBody[vertex_count][1] = currentHeight; 
			_vertexarrayBody[vertex_count][2] = -radius*sin(angle); 

			_normalarrayBody[vertex_count][0] = cos(angle); 
			_normalarrayBody[vertex_count][1] = 0.0f; 
			_normalarrayBody[vertex_count][2] = -sin(angle);

			_texarrayBody[vertex_count][0] = cos(angle)*0.25f; 
			_texarrayBody[vertex_count++][1] = sin(angle)*0.25f; 

			angle += slice_inc;
		}
		currentHeight -= stack_inc;
	}

	// Bottom
	vertex_count = 0;
	angle = 0.0f;
	for(int slice = 0; slice < _slices; slice++)
	{
		_vertexarrayBottom[vertex_count][0] = radius*cos(angle); 
		_vertexarrayBottom[vertex_count][1] = -halfHeight; 
		_vertexarrayBottom[vertex_count][2] = -radius*sin(angle); 

		_normalarrayBottom[vertex_count][0] = 0.0f; 
		_normalarrayBottom[vertex_count][1] = -1.0f; 
		_normalarrayBottom[vertex_count][2] = 0.0f;

		_texarrayBottom[vertex_count][0] = 1.0f - cos(angle)*0.25f; 
		_texarrayBottom[vertex_count++][1] = 1.0f - sin(angle)*0.25f; 

		angle += slice_inc;
	}

	// **** define the index array ****
	// Top 
	index_count = 0;
	for(int slice = 0; slice < slices; slice++)
	{
		_indexarrayTop[index_count] = index_count++;
	}
	// Body
	index_count = 0;
	for(int stack = 0; stack < _stacks-1; stack++)
	{
		for(int slice = 0; slice < slices-1; slice++)
		{
			_indexarrayBody[index_count++] = (_slices*stack)+slice;
			_indexarrayBody[index_count++] = (_slices*stack)+slice+_slices;
			_indexarrayBody[index_count++] = (_slices*stack)+slice+1+_slices;
			_indexarrayBody[index_count++] = (_slices*stack)+slice+1;
		}
		_indexarrayBody[index_count++] = (_slices*stack)-1+_slices;
		_indexarrayBody[index_count++] = (_slices*stack)-1+_slices*2;
		_indexarrayBody[index_count++] = (_slices*stack)+_slices;
		_indexarrayBody[index_count++] = (_slices*stack);
	}
	// Bottom 
	index_count = 0;
	for(int slice = 0; slice < _slices; slice++)
	{
		_indexarrayBottom[index_count++] = _slices - 1 - slice;
	}

	return true;
}

void MyCylinder::draw() const {
	// Body
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _vertexarrayBody);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, _texarrayBody);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, _normalarrayBody);
	glDrawElements(GL_QUADS, _slices*(_stacks-1)*4, GL_UNSIGNED_INT, _indexarrayBody);

	// Top
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _vertexarrayTop);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, _texarrayTop);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, _normalarrayTop);
	glDrawElements(GL_POLYGON, _slices, GL_UNSIGNED_INT, _indexarrayTop);
 
	// Bottom
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _vertexarrayBottom);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, _texarrayBottom);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, _normalarrayBottom);
	glDrawElements(GL_POLYGON, _slices, GL_UNSIGNED_INT, _indexarrayBottom);

}
