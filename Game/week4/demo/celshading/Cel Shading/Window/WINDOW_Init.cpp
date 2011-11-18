//////////////////////////////////////////////////////////////////////////////////////////
//	WINDOW_Init.cpp
//	Create a D3D window
//	Downloaded from: www.paulsprojects.net
//	Created:	12th November 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <D3DX8.h>
#include "../Log/LOG.h"
#include "../Resources/resource.h"
#include "WINDOW.h"

bool WINDOW::Init(	char * windowTitle, int newWidth, int newHeight,
					D3DFORMAT newBackBufferFormat, D3DFORMAT newFrontBufferFormat,
					D3DFORMAT newDepthFormat, bool newFullscreen,
					LPDIRECT3D8 * d3d, IDirect3DDevice8 ** d3dDevice)
{
	//Set member variables
	title=windowTitle;
	
	width=newWidth;
	height=newHeight;
	backBufferFormat=newBackBufferFormat;
	frontBufferFormat=newFrontBufferFormat;
	depthFormat=newDepthFormat;
	fullscreen=newFullscreen;
	currentAASamples=0;

	LOG::Instance()->OutputSuccess("Creating Window");
	LOG::Instance()->OutputNewLine();

	//Create D3D
	(*d3d)=Direct3DCreate8(D3D_SDK_VERSION);
	if(!(*d3d))
	{
		LOG::Instance()->OutputError("Unable to create D3D");
		return false;
	}

	//Find out the front buffer format for windowed mode
	D3DDISPLAYMODE displayMode;

	HRESULT hr;
	hr=(*d3d)->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to get current display mode");
		return false;
	}

	D3DFORMAT windowedFrontBufferFormat=displayMode.Format;

	//Find a supported front buffer color format for fullscreen mode
	D3DFORMAT fullscreenFrontBufferFormat;

	if(!GetFullscreenFrontBufferFormat(frontBufferFormat, fullscreenFrontBufferFormat, (*d3d)))
		return false;


	//Find a supported back buffer color format
	D3DFORMAT windowedBackBufferFormat, fullscreenBackBufferFormat;

	if(!GetBackBufferFormat(backBufferFormat, windowedBackBufferFormat,
							windowedFrontBufferFormat, (*d3d), true))
		return false;

	if(!GetBackBufferFormat(backBufferFormat, fullscreenBackBufferFormat,
							fullscreenFrontBufferFormat, (*d3d), false))
		return false;


	//Now find a supported depth format
	D3DFORMAT windowedDepthFormat, fullscreenDepthFormat;

	if(!GetDepthFormat(	depthFormat, windowedDepthFormat, windowedFrontBufferFormat,
						windowedBackBufferFormat, (*d3d), true))
		return false;

	if(!GetDepthFormat(	depthFormat, fullscreenDepthFormat, fullscreenFrontBufferFormat,
						fullscreenBackBufferFormat, (*d3d),	false))
		return false;


	//Find supported AA samples
	for(int i=2; i<=16; ++i)
	{
		//Get the enumerated value for this number of samples
		D3DMULTISAMPLE_TYPE numSamples=(D3DMULTISAMPLE_TYPE)i;

		//Check in windowed mode
		if(	SUCCEEDED((*d3d)->CheckDeviceMultiSampleType(	D3DADAPTER_DEFAULT,
															D3DDEVTYPE_HAL,
															windowedBackBufferFormat,
															true,
															numSamples))			&&
			SUCCEEDED((*d3d)->CheckDeviceMultiSampleType(	D3DADAPTER_DEFAULT,
															D3DDEVTYPE_HAL,
															windowedDepthFormat,
															true,
															numSamples)))
		{
			windowedAASamplesSupported[i]=true;
		}
		else
			windowedAASamplesSupported[i]=false;

		//Check in full screen mode
		if(	SUCCEEDED((*d3d)->CheckDeviceMultiSampleType(	D3DADAPTER_DEFAULT,
															D3DDEVTYPE_HAL,
															fullscreenBackBufferFormat,
															false,
															numSamples))			&&
			SUCCEEDED((*d3d)->CheckDeviceMultiSampleType(	D3DADAPTER_DEFAULT,
															D3DDEVTYPE_HAL,
															fullscreenDepthFormat,
															false,
															numSamples)))
		{
			fullscreenAASamplesSupported[i]=true;
		}
		else
			fullscreenAASamplesSupported[i]=false;
	}

	//Bring up the dialog box to set resolution etc
	DialogBox(	hInstance, MAKEINTRESOURCE(IDD_RESOLUTION), HWND_DESKTOP,
				SelectModeProc);

	//Set the formats to use
	if(fullscreen)
	{
		backBufferFormat=fullscreenBackBufferFormat;
		frontBufferFormat=fullscreenFrontBufferFormat;
		depthFormat=fullscreenDepthFormat;
	}
	else
	{
		backBufferFormat=windowedBackBufferFormat;
		frontBufferFormat=windowedFrontBufferFormat;
		depthFormat=windowedDepthFormat;
	}



	//Window class structure
	WNDCLASS wc;

	//Fill in window class
	wc.style		= CS_OWNDC;
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hInstance	= hInstance;
	wc.hIcon		= LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground= (HBRUSH) GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName	= NULL;
	wc.lpszClassName= "Direct3D";

	//Provide default message handler
	wc.lpfnWndProc	= WndProc;

	//register class
	if(!RegisterClass(&wc))
	{
		LOG::Instance()->OutputError("Unable to register class");
		return false;
	}
	else
		LOG::Instance()->OutputSuccess("Window class registered");

	//Set style
	DWORD style;

	if(fullscreen)
		style=WS_POPUP;
	else
		style=WS_OVERLAPPED | WS_SYSMENU;

	//Create window
	hWnd=CreateWindow("Direct3D", title, style, 0, 0, width, height, NULL, NULL, hInstance, NULL);

	if(!hWnd)
	{
		LOG::Instance()->OutputError("Unable to create window");
		return false;
	}
	else
		LOG::Instance()->OutputSuccess("Window Created");

	//Make sure window is visible and has focus
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	SetFocus(hWnd);



	//Set up present parameters
	D3DPRESENT_PARAMETERS presentParameters;
	memset(&presentParameters, 0, sizeof(D3DPRESENT_PARAMETERS));

	presentParameters.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	presentParameters.hDeviceWindow				= hWnd;
	presentParameters.BackBufferCount			= 1;
	presentParameters.BackBufferFormat			= backBufferFormat;
	presentParameters.EnableAutoDepthStencil	= true;
	presentParameters.AutoDepthStencilFormat	= depthFormat;
	
	//Set AA samples
	presentParameters.MultiSampleType			= (D3DMULTISAMPLE_TYPE)currentAASamples;

	if(fullscreen)
	{
		presentParameters.Windowed=false;
		presentParameters.BackBufferWidth=width;
		presentParameters.BackBufferHeight=height;
	}
	else
	{
		presentParameters.Windowed=true;
	}

	//Create the D3D device
	hr=(*d3d)->CreateDevice(	D3DADAPTER_DEFAULT,
								D3DDEVTYPE_HAL,
								hWnd,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								&presentParameters,
								d3dDevice);

	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to create D3D device");
		return false;
	}
	else
		LOG::Instance()->OutputSuccess("D3D device created");

	//Hide cursor in fullscreen
	if(fullscreen)
		ShowCursor(false);

	LOG::Instance()->OutputSuccess("Window created successfully");
	return true;
}

		



