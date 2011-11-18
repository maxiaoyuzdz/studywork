#include "MxyWindow3.h"

#include <math.h>


#define DEV_R  1.0f


/**
//original coordinate
static float vertex_coor[4][2] = {-0.45f,-0.45f,
	+0.45f,-0.45f,
	+0.45f,+0.45f,
	-0.45f,+0.45f};




static float fix_scale_matrix[3][3] = {1,	0,	0,
										0,	1,	0,
										0,	0,	1};


static float translate_matrix[3][3] = {1,	0,	0,
										0,	1,	0,
										1,	1,	1};
*/

static const float original_square_vertex_coord[4][2] = {-0.45f, -0.45f,
	+0.45f, -0.45f,
	+0.45f, +0.45f,
	-0.45f, +0.45f};

static float draw_square_vertex_coord[4][2] = {0};

void MatrixCalculate3x3(float *vextor, float matrix[][3], float *res)
{
	/************************************************************************/
	/*   2D[x,y,] * [3 x 3] = 2D [x,y,w], temp w                           */
	/************************************************************************/

	res[0] = vextor[0] * matrix[0][0] + vextor[1] * matrix[1][0] + 1 * matrix[2][0];
	res[1] = vextor[0] * matrix[0][1] + vextor[1] * matrix[1][1] + 1 * matrix[2][1];
	res[2] = vextor[0] * matrix[0][2] + vextor[1] * matrix[1][2] + 1 * matrix[2][2];

}

/**
void RescaleOriginal2DObject()
{
	static const float scale_factor = 0.5f;
	static float scale_matrix[3][3] = {scale_factor,	0,	0,
										0,	scale_factor,	0,
										0,	0,	1};

	float x;
	float y;

	float temp_in[3] = {0.0f,0.0f,1.0f};
	float temp_res[3] = {0};

	for(int i = 0; i < 4; i++)
	{
		for(int k = 0; k<3;k++)
			temp_res[k] = 0;

		x = vertex_coor[i][0];
		y = vertex_coor[i][1];

		temp_in[0] = x;
		temp_in[1] = y;
		

		MatrixCalculate3x3(temp_in, scale_matrix,temp_res);

		//x = y = 0;

		vertex_coor[i][0] = temp_res[0];
		vertex_coor[i][1] = temp_res[1];

	}
}
*/

MxyWindow3::MxyWindow3()
{
	SetSize(512,512);
	/************************************************************************/
	/*scale to small                                                                      */
	/************************************************************************/
	/**
	for(int i = 0; i<4;i++)
	{
		for(int j = 0; j<2; j++)
		{
			vertex_coor[i][j] = vertex_coor[i][j] * scale_factor;
		}
	}
	*/
	/************************************************************************/
	/* test matrix calculate                                                                     */
	/************************************************************************/
	/**
	float sourcedata[3] = {22, 34, 1};
	float res[3] = {0};


	MatrixCalculate3x3(sourcedata, fix_scale_matrix, res);

	for(int i = 0; i<3; i++)
	{
		res[i] = res[i];
	}
	*/

	/************************************************************************/
	/* rescale original matrix                                                                     */
	/************************************************************************/
	//RescaleOriginal2DObject();
}

// this is a simple example: it creates one window,
// and draws a rotating yellow triangle inside it
void MxyWindow3::OnDisplay() {


	/************************************************************************/
	/* rotate parameter                                                                     */
	/************************************************************************/
	static const float rotate_speed = 0.25f;
	static float rpos = 0.0f;
	static float rinc = rotate_speed;

	/************************************************************************/
	/* x , y axis move parameter                                                                     */
	/************************************************************************/
	static const float speed  = 0.25f;

	static float xpos = 0.0f, ypos = 0.0f;
	static float xinc = speed; 
	static float yinc = speed;

	/************************************************************************/
	/* color change                                                                     */
	/************************************************************************/
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f-xpos,0.0f,0.5f+xpos);
	//////////////////////////////////////////////////////////////////////////

	/************************************************************************/
	/* delta time                                                                     */
	/************************************************************************/
	static float current_time = (float)App::GetTime();
	float delta_t, temp_time;

	temp_time = (float)App::GetTime();
	delta_t = temp_time - current_time;
	current_time = temp_time;
	//////////////////////////////////////////////////////////////////////////

	/************************************************************************/
	/* x axis move                                                                     */
	/************************************************************************/

	static int move_direction = 0;
	

	/************************************************************************/
	/* move to x positive                                                                     */
	/************************************************************************/
	if( move_direction == 0)
	{
		xpos += xinc * delta_t;

		/************************************************************************/
		/* once arrive to a x edge, stop to move y axis                                                                     */
		/************************************************************************/
		if(xpos > 0.5f) {
			xinc = -xinc;
			xpos = 0.5f;

			move_direction = 1;
		};

		if(xpos < -0.5f) {
			xinc = -xinc;
			xpos = -0.5f;

			move_direction = 1;
		};
	}

	else
	{
		ypos += yinc * delta_t;

		/************************************************************************/
		/* once arrive to a y edge, stop to move x axis                                                                     */
		/************************************************************************/
		if(ypos > 0.5f) {
			yinc = -yinc;
			ypos = 0.5f;

			move_direction = 0;
		};

		if(ypos < -0.5f) {
			yinc = -yinc;
			ypos = -0.5f;

			move_direction = 0;
		};
	}
	/************************************************************************/
	/* rotated increasing                                                                     */
	/************************************************************************/
	rpos += rinc * delta_t;
	//////////////////////////////////////////////////////////////////////////

	/************************************************************************/
	/* rotate matrix                                                                     */
	/************************************************************************/
	
	
	static float rotate_matrix[3][3] = {	cos(rpos) , sin(rpos), 0,
											-sin(rpos),	cos(rpos), 0,
											0,			0,			1};
	
	//////////////////////////////////////////////////////////////////////////


	/************************************************************************/
	/* scale matrix                                                                     */
	/************************************************************************/
	static float scale_matrix[3][3] = {0.5f,			0,				0,
										0,				0.5f,			0,
										0,				0,				1};
	//////////////////////////////////////////////////////////////////////////

	/************************************************************************/
	/* translate matrix                                                                     */
	/************************************************************************/
	static float transaction_matrix[3][3] = {	1,		0,		0,
												0,		1,		0,
												xpos,	ypos,	1};


	/************************************************************************/
	/* do rotate , scale , translate Matrix calculate   result =  draw_square_vertex_coord                                                                */
	/************************************************************************/
	
	static float temp_in[3] = {0.0f,0.0f,1.0f};
	static float temp_rotate_res[3] = {0};
	static float temp_scale_res[3] = {0};
	static float temp_traclate_res[3] = {0};

	//update rotate data
	rotate_matrix[0][0] = cos(rpos);
	rotate_matrix[0][1] = sin(rpos);
	rotate_matrix[1][0] = -sin(rpos);
	rotate_matrix[1][1] = cos(rpos);
	//////////////////////////////////////////////////////////////////////////
	//update translate data
	transaction_matrix[2][0] = xpos;
	transaction_matrix[2][1] = ypos;


	for(int i = 0; i< 4; i++)
	{
		temp_in[2] = 1.0f;
		
		
		for(int k = 0; k<3;k++)
		{
			temp_rotate_res[k] = 0;
			temp_scale_res[k] = 0;
			temp_traclate_res[k] = 0;
		}
		
		
		temp_in[0] = original_square_vertex_coord[i][0];
		temp_in[1] = original_square_vertex_coord[i][1];

		MatrixCalculate3x3(temp_in, rotate_matrix,temp_rotate_res);

		MatrixCalculate3x3(temp_rotate_res,scale_matrix,temp_scale_res);

		MatrixCalculate3x3(temp_scale_res,transaction_matrix,temp_traclate_res);

		draw_square_vertex_coord[i][0] = temp_traclate_res[0];//x
		draw_square_vertex_coord[i][1] = temp_traclate_res[1];//y

		
	}


	glBegin(GL_QUADS);

	
	glVertex2f(draw_square_vertex_coord[0][0], draw_square_vertex_coord[0][1]);
	glVertex2f(draw_square_vertex_coord[1][0], draw_square_vertex_coord[1][1]);
	glVertex2f(draw_square_vertex_coord[2][0], draw_square_vertex_coord[2][1]);
	glVertex2f(draw_square_vertex_coord[3][0], draw_square_vertex_coord[3][1]);
	
	glEnd();

	
	SwapBuffers();
}


// When nothing else is happening OnIdle() is called.  In this case, the 
// inclusion Redraw() makes sure that the window is then updated, which 
// causes OnDisplay() to be called
void MxyWindow3::OnIdle() {
	Redraw();
}

