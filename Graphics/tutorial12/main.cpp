#include "GXBase.h"
using namespace gxbase;

/**
 * Simple painting application with a 'clone' brush that copies pixels from
 * one part of an image to another. Right-Click with the mouse to select the
 * origin for the clone brush, then Left-Click and drag to paint.
 *
 * This program was written to test the Image::GetPixel method. It also
 * partially tests the Image::glDrawPixels() and Image::glSetPixel methods.
 *   JWW 16/10/03
 */

//-----------------------------------------------------------------------------

struct Point2 {
	int x,y;
	
	Point2() :x(0),y(0) {}

	Point2(int X,int Y) :x(X),y(Y) {}
	
	Point2(const Point2 &rhs) {
		*this=rhs;
	}
	
	Point2 & operator = (const Point2 &rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
};

//-----------------------------------------------------------------------------

class MyWnd :public GLWindow {
public:
	MyWnd();

	void OnDisplay();
	void OnMouseButton(MouseButton button, bool down);
	void OnMouseMove(int x, int y);
	void OnIdle();

protected:
	void Draw();		// draw into the image (at current mouse pos)

private:
	bool m_bDraw;		// are we drawing currently?
	Image m_image;		// image to draw into
	Point2
		m_cloneOrg,		// origin of clone (copy from)
		m_mousePos,		// current mouse position
		m_dragOrg;		// origin of drag (copy to)
};

//-----------------------------------------------------------------------------

/**
 * Constructor: create an image
 */
MyWnd::MyWnd() {
	m_bDraw = false;

	// create an image
	m_image.Create(256,256);
	
	// fill image with a funky pattern
	for (long i=0;i<m_image.Width();i++)
		for (long j=0;j<m_image.Height();j++)
			m_image.SetPixel3b(i,j, (BYTE)i, (BYTE)j, (BYTE)(i^j));

	// resize window to match image
	SetSize( m_image.Width(), m_image.Height() );
}//MyWnd

//-----------------------------------------------------------------------------

/**
 * Display function
 */
void MyWnd::OnDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	// draw the image into the window, 1:1 size, bottom-left corner
	glRasterPos2f(-1,-1);
	m_image.glDrawPixels();

	SwapBuffers();
}//OnDisplay

//-----------------------------------------------------------------------------

/**
 * Called when a mouse button is pressed/released
 */
void MyWnd::OnMouseButton(MouseButton button, bool down) {
	switch (button) {
	case MBLeft:
		m_bDraw = down;
		if (down) {
			m_dragOrg = m_mousePos;
			Draw();
		}
		break;
	case MBRight:
		if (down) m_cloneOrg = m_mousePos;
		break;
	}
}//OnMouseButton

//-----------------------------------------------------------------------------

/**
 * Called when the mouse moves
 */
void MyWnd::OnMouseMove(int x, int y) {
	m_mousePos.x = x;
	m_mousePos.y = y;
	// if we are drawing, update the clone brush
	if (m_bDraw) Draw();
}//OnMouseMove

//-----------------------------------------------------------------------------

/**
 * Clones pixels from one part of the image to another
 */
void MyWnd::Draw() {
	// work out centre point to copy pixels from
	int
		x = m_cloneOrg.x + (m_mousePos.x - m_dragOrg.x),
		y = m_cloneOrg.y + (m_mousePos.y - m_dragOrg.y);

	// a simple 'clone' brush: copies pixels from one point to another
	for (int i=-4;i<4;i++)
		for (int j=-4;j<4;j++) if (i*i+j*j<16) {
			BYTE r,g,b;
			m_image.GetPixel3b(x+i,y+j, r,g,b);
			m_image.SetPixel3b(m_mousePos.x+i, m_mousePos.y+j, r,g,b);
		}
}//Draw

//-----------------------------------------------------------------------------

/**
 * Redraw continuously on idle
 */
void MyWnd::OnIdle() {
	Redraw();
}//OnIdle

//-----------------------------------------------------------------------------

// run the application
static class MyApp :public App {
	MyWnd m_mainWnd;
} theApp;

//-----------------------------------------------------------------------------
