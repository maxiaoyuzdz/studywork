#include "MyApp.h"

static MyApp theApp;

void MyApp::OnCreate()
{
	w.Show();
	if(!w.HasExtension("GL_ARB_vertex_buffer_object") )
	{
		MsgPrintf("Vertex buffer object extension not found\n");
	}

	
}
