#include "MySphere.h"
#include <math.h>
#define PI  (float)3.1415926

MySphere::MySphere() {
}

MySphere::~MySphere() {
	delete [] _vertexarray;
	delete [] _normalarray;
	delete [] _indexarray;
	delete [] _texarray;
}

bool MySphere::create(GLfloat radius, int slices, int stacks, bool texture) {
	int array_size;
	float stack_inc;
	float slice_inc;
	float x, y , z;
	int vertex_count;
	int index_count;
	int temp_vc;
	float temp_tex;
	float temp_rad;

	_stacks = stacks;
	_slices = slices;


	array_size = (slices+1)*(stacks-1)+2;	// +2 is for the top and bottom vertex

	_vertexarray = new float[array_size][3];
	_normalarray = new float[array_size][3];
	_indexarray = new GLuint[2+(stacks-1)*(slices+1)*2];
	_texarray = new float[array_size][2];

	if ((stacks < 2) & (slices <2)) return false;

	stack_inc = 1.0f/(float)stacks;
	slice_inc = PI*2.0f/slices;

	// define the vertex array

	// top point
	vertex_count = 0;
	_vertexarray[vertex_count][0] = 0.0f; 
	_vertexarray[vertex_count][1] = radius; 
	_vertexarray[vertex_count][2] = 0.0f; 

	_normalarray[vertex_count][0] = 0.0f; 
	_normalarray[vertex_count][1] = 1.0f; 
	_normalarray[vertex_count][2] = 0.0f;

	_texarray[vertex_count][0] = 0; 
	_texarray[vertex_count++][1] = 1; 

	// bottom point
	_vertexarray[vertex_count][0] = 0.0f; 
	_vertexarray[vertex_count][1] = -radius; 
	_vertexarray[vertex_count][2] = 0.0f;

	_normalarray[vertex_count][0] = 0.0f; 
	_normalarray[vertex_count][1] = -1.0f; 
	_normalarray[vertex_count][2] = 0.0f;

	_texarray[vertex_count][0] = 0; 
	_texarray[vertex_count++][1] = 0; 


	for (int i = 1; i < stacks; i++) {
		y = sin(PI*(1/2.0f - stack_inc*(float)i));
		temp_rad = cos(PI*(1/2.0f - stack_inc*(float)i));
		temp_vc = vertex_count;
		temp_tex = 1.0f - stack_inc*(float)i;
		for(int j = 0; j < slices; j++) {
			x = cos((float)j*slice_inc); 
			z = -sin((float)j*slice_inc);  
			_vertexarray[vertex_count][0] = radius*temp_rad*x;
			_vertexarray[vertex_count][1] = radius*y;
			_vertexarray[vertex_count][2] = radius*temp_rad*z;
			_normalarray[vertex_count][0] = temp_rad*x;
			_normalarray[vertex_count][1] = y;
			_normalarray[vertex_count][2] = temp_rad*z;
			_texarray[vertex_count][0] = (float)j/(float)slices;
			_texarray[vertex_count++][1] = temp_tex;
		};
		_vertexarray[vertex_count][0] = _vertexarray[temp_vc][0];
		_vertexarray[vertex_count][1] = _vertexarray[temp_vc][1];
		_vertexarray[vertex_count][2] = _vertexarray[temp_vc][2];
		_normalarray[vertex_count][0] = _normalarray[temp_vc][0];
		_normalarray[vertex_count][1] = _normalarray[temp_vc][1];
		_normalarray[vertex_count][2] = _normalarray[temp_vc][2];
		_texarray[vertex_count][0] = 1;
		_texarray[vertex_count++][1] = temp_tex;
	};

	// now generate the index array
	// start with triangle fans for the top
	index_count = 0;
	vertex_count =2;
	_indexarray[index_count++] = 0; // very top vertex
	for(int j = 0; j<= slices; j++) {
		_indexarray[index_count++] = vertex_count++;
	};
	vertex_count -= (slices+1);
	// now do the main strips
	for(int i = 0; i< (stacks-2); i++) {
		for(int j = 0; j<= slices; j++) {
			_indexarray[index_count++] = vertex_count++;
			_indexarray[index_count++] = slices+vertex_count;
		};
	};

	_indexarray[index_count++] = 1; // very bottom vertex
	for(int j = 0; j<= slices; j++) {
		_indexarray[index_count++] = vertex_count+slices-j;
	};

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, _texarray);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, _normalarray);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _vertexarray);

	return true;
}

void MySphere::draw() const {
	glDrawElements(GL_TRIANGLE_FAN, _slices+2, GL_UNSIGNED_INT, &_indexarray[0]);
	for (int i = 0; i < (_stacks-2); i++) { 
		glDrawElements(GL_TRIANGLE_STRIP, (_slices+1)*2, GL_UNSIGNED_INT, &_indexarray[_slices+2+i*(_slices+1)*2]);
	};
	glDrawElements(GL_TRIANGLE_FAN, _slices+2, GL_UNSIGNED_INT, &_indexarray[_slices+2+(_stacks-2)*(_slices+1)*2]);
}
