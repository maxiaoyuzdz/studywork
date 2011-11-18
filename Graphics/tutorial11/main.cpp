#include "GXBase.h"
#include "PaletteWindow.h"
using namespace gxbase;

// This program is a cut down, modified version of a test program by James Ward
// I thought it was so good that it desrved a slot in the tutorial, especially since
// it demonstrates the creation, writing to, and saving of image maps
//
class MyWindow :public GLWindow {
public:
	MyWindow(PaletteWindow* pw);
	void OnCreate();
	void OnDisplay();
	void OnMouseButton(MouseButton button, bool down);
	void OnMouseMove(int x, int y);
	void OnKeyboard(int key, bool down);

private:
	void DrawPixel();
	Image m_image;
	float m_fMousePos[2];
	float m_colour[3];
	bool  m_bDraw;
};

class MyApp :public App {

public:
	MyApp();
private:
	MyWindow *m_wnd;
	PaletteWindow *p_wnd;


};

MyApp::MyApp()
{
	
	
	p_wnd = new PaletteWindow();

	m_wnd = new MyWindow(p_wnd);
	
}

static MyApp theApp;

MyWindow::MyWindow(PaletteWindow* pw) {
	SetSize(256,256);
	m_colour[0]=1;
	m_colour[1]=1;
	m_colour[2]=1;
	m_bDraw=false;
}

void MyWindow::OnCreate() {
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_image.Create(128,128);
	m_image.Clear3b(0,0,0);
}//OnCreate

void MyWindow::OnDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	m_image.glTexImage2D();

	glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(-1,-1);
		glTexCoord2f(1,0); glVertex2f(+1,-1);
		glTexCoord2f(1,1); glVertex2f(+1,+1);
		glTexCoord2f(0,1); glVertex2f(-1,+1);
	glEnd();

	SwapBuffers();
}//OnDisplay

void MyWindow::OnMouseButton(MouseButton button, bool down) {
	if (down) {
		float r=0.0f,g=0.0f,b=0.0f;
		switch (button) {
		case MBLeft:
			r=1.0f;
			break;
		case MBMiddle:
			g=1.0f;
			break;
		case MBRight:
			g=0.3f; b=1.0f;
			break;
		}
		m_colour[0]=r;
		m_colour[1]=g;
		m_colour[2]=b;
		m_bDraw=true;
		DrawPixel();
	} else
		m_bDraw=false;

	// request a redraw
	Redraw();
}//OnMouseButton

void MyWindow::OnMouseMove(int x, int y) {
	int w=Width(), h=Height();
	m_fMousePos[0] = w?(float)x/(float)w:0.0f;
	m_fMousePos[1] = h?(float)y/(float)h:0.0f;
	// if drawing, draw a pixel
	if (m_bDraw) {
		DrawPixel();
		// request a redraw
		Redraw();
	}
}//OnMouseMove

void MyWindow::OnKeyboard(int key, bool down) {
	if (down) switch (tolower(key)) {
	case 's':
		m_image.Save("test1.bmp");
		Redraw();
		break;
	default :
		break;
	}
}//OnKeyboard


void MyWindow::DrawPixel() {
	// scale into image coords.
	int
		i = (int)(m_fMousePos[0] * (float)m_image.Width()  + 0.5f),
		j = (int)(m_fMousePos[1] * (float)m_image.Height() + 0.5f);
	// draw into image

	m_image.SetPixel3f( i,j, m_colour[0], m_colour[1], m_colour[2] );
	
}//DrawPixel

