#include "PaltteWindow.h"

PaletteWindow::PaletteWindow()
{
	
	SetSize(128,128);
	SetTitle("Palette");
}

void PaletteWindow::OnCreate()
{
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_image.Create(128,128);
	m_image.Clear3b(0,0,0);

	int w=Width(), h=Height();

	for(int i = 0; i<w;i++)
	{

		for(int j = 0;j<h;j++)
		{
			m_image.SetPixel3f( i,j, 1.0,0.0,0.0 );
		}
	}
	
}


void PaletteWindow::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	m_image.glTexImage2D();

	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex2f(-1,-1);
	glTexCoord2f(1,0); glVertex2f(+1,-1);
	glTexCoord2f(1,1); glVertex2f(+1,+1);
	glTexCoord2f(0,1); glVertex2f(-1,+1);
	glEnd();

	SwapBuffers();
}

void PaletteWindow::OnMouseButton(MouseButton button, bool down)
{

}

void PaletteWindow::OnMouseMove(int x, int y)
{

}


void PaletteWindow::OnKeyboard(int key, bool down)
{

}


const float* PaletteWindow::ChoosedColor() const
{
	return _rgb;
}

void PaletteWindow::DrawPixel() {
	

	

}