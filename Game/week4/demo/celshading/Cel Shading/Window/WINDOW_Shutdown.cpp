//////////////////////////////////////////////////////////////////////////////////////////
//	WINDOW_Shutdown.cpp
//	Shutdown the window
//	Downloaded from: www.paulsprojects.net
//	Created:	13th November 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <D3DX8.h>
#include "../Log/LOG.h"
#include "WINDOW.h"

void WINDOW::Shutdown()
{
	LOG::Instance()->OutputNewLine();

	//Show cursor if hidden
	if(fullscreen)
		ShowCursor(1);

	//Destroy window
	if(hWnd)
	{
		if(!DestroyWindow(hWnd))
			LOG::Instance()->OutputError("Unable to destroy window");
		else
			LOG::Instance()->OutputSuccess("Window Destroyed");

		hWnd=NULL;
	}

	//Unregister class
	if(!UnregisterClass("Direct3D", hInstance))
		LOG::Instance()->OutputError("Unable to unregister class");
	else
		LOG::Instance()->OutputSuccess("Window class unregistered");

	hInstance=NULL;
}
