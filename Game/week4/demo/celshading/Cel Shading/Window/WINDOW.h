//////////////////////////////////////////////////////////////////////////////////////////
//	WINDOW.h
//	Singleton class to handle window, messages, input.
//	Singleton was chosen because of the static callback functions required in WINDOW
//	Downloaded from: www.paulsprojects.net
//	Created:	26th November 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef WINDOW_H
#define WINDOW_H

class WINDOW
{
protected:
	//protected constructor and copy constructor to prevent making copies
	WINDOW()
	{}
	WINDOW(const WINDOW &)
	{}
	WINDOW & operator= (const WINDOW &)
	{}

public:
	//public function to access the instance of the window class
	static WINDOW * Instance()
	{
		//Instance of window class
		static WINDOW instance;
		return &instance;
	}

	//Initiate window
	bool Init(	char * windowTitle, int newWidth, int newHeight,
				D3DFORMAT newBackBufferFormat, D3DFORMAT newFrontBufferFormat,
				D3DFORMAT newDepthFormat, bool newFullscreen,
				LPDIRECT3D8 * d3d, IDirect3DDevice8 ** d3dDevice);

	void Update()
	{	UpdateInput();	}
	void Shutdown();

	//Handle windows messages
	bool HandleMessages(void);
	static LRESULT CALLBACK WndProc(	HWND hWnd,			//static for CALLBACK
										UINT msg,
										WPARAM wParam,
										LPARAM lParam);

	//Handle dialog box used to select window resolution etc in ARB_extended window setup
	static INT_PTR CALLBACK SelectModeProc(	HWND hWnd,
											UINT msg,
											WPARAM wParam,
											LPARAM lParam);

	//Misc functions
	void SaveScreenshot(IDirect3DDevice8 * d3dDevice);

protected:
	//Get a supported color format for full screen mode
	//Windowed mode is bound to the current display mode
	bool GetFullscreenFrontBufferFormat(	D3DFORMAT requestedFormat, D3DFORMAT & resultFormat,
											LPDIRECT3D8 d3d);

	//Get a matching back buffer for our front buffer format
	bool GetBackBufferFormat(	D3DFORMAT requestedFormat, D3DFORMAT & resultFormat,
								D3DFORMAT frontBufferFormat,
								LPDIRECT3D8 d3d, bool windowed);

	//Get a supported depth format
	bool GetDepthFormat(D3DFORMAT requestedFormat, D3DFORMAT & resultFormat,
						D3DFORMAT frontBufferFormat, D3DFORMAT backBufferFormat,
						LPDIRECT3D8 d3d, bool windowed);

	//AA samples supported
	bool windowedAASamplesSupported[17];	//use 2-16
	bool fullscreenAASamplesSupported[17];	//use 2-16
	int currentAASamples;					//0, or 2-16

public:

	//windows variables
	HWND		hWnd;			//Window handle
	HINSTANCE	hInstance;		//Handle to window instance

	//Window statistics
	char * title;				//title
	int width, height;			//Window size
	D3DFORMAT backBufferFormat;		//color formats
	D3DFORMAT frontBufferFormat;
	D3DFORMAT depthFormat;		//depth format

	bool fullscreen;


	
	//Input Functions
	void UpdateInput();

public:
	//Keyboard
	void SetKeyPressed(int keyNumber)
	{
		if(keyNumber>=0 && keyNumber<256)
			keyPressed[keyNumber]=true;
	}
	
	void SetKeyReleased(int keyNumber)
	{
		if(keyNumber>=0 && keyNumber<256)
			keyPressed[keyNumber]=false;
	}

	bool IsKeyPressed(int keyNumber)
	{
		if(keyNumber>=0 && keyNumber<256)
			return keyPressed[keyNumber];
		else
			return false;
	}

protected:
	bool keyPressed[256];	//is a key pressed?

public:
	//Mouse
	void SetLeftButtonPressed()
	{	mouseLDown=true;	}
	
	void SetRightButtonPressed()
	{	mouseRDown=true;	}
	
	void SetLeftButtonReleased()
	{	mouseLDown=false;	}
	
	void SetRightButtonReleased()
	{	mouseRDown=false;	}

	bool IsLeftButtonPressed()
	{	return mouseLDown;	}

	bool IsRightButtonPressed()
	{	return mouseRDown;	}

	int GetMouseX()
	{	return mouseX;	}

	int GetMouseY()
	{	return mouseY;	}

	int GetMouseXMovement()
	{	return mouseX-oldMouseX;	}
	
	int GetMouseYMovement()
	{	return mouseY-oldMouseY;	}

protected:
	int oldMouseX, oldMouseY;
	int mouseX, mouseY;
	bool mouseLDown, mouseRDown;
};

#endif	//WINDOW_H