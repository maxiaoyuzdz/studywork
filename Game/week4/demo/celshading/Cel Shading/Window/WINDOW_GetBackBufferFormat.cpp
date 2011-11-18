//////////////////////////////////////////////////////////////////////////////////////////
//	WINDOW_GetBackBufferFormat.cpp
//	Get a supported back buffer format. Will first try to use given format, then some fallbacks
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
#include "WINDOW.h"

//Get a supported back buffer format
bool WINDOW::GetBackBufferFormat(	D3DFORMAT requestedFormat, D3DFORMAT & resultFormat,
									D3DFORMAT frontBufferFormat,
									LPDIRECT3D8 d3d, bool windowed)
{
	//See if the requested back buffer format is supported
	HRESULT hr;
	
	hr=d3d->CheckDeviceType(	D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, frontBufferFormat,
								requestedFormat, windowed);
	if(SUCCEEDED(hr))
	{
		LOG::Instance()->OutputSuccess("Chosen back buffer format is available in %s mode",
										windowed ? "windowed" : "fullscreen");
		resultFormat=requestedFormat;
		return true;
	}

	//If failed, try A8R8G8B8, X8R8G8B8, R5G6B5
	D3DFORMAT testFormats[3]={D3DFMT_A8R8G8B8, D3DFMT_X8R8G8B8, D3DFMT_R5G6B5};
	char * testStrings[3]={"D3DFMT_A8R8G8B8", "D3DFMT_X8R8G8B8", "D3DFMT_R5G6B5"};
	for(int i=0; i<3; ++i)
	{
		D3DFORMAT currentTestFormat=testFormats[i];

		if(FAILED(hr))
		{
			hr=d3d->CheckDeviceType(	D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, frontBufferFormat,
										currentTestFormat, windowed);
			if(SUCCEEDED(hr))
			{
				LOG::Instance()->OutputMisc("%s will be used instead of chosen back buffer format in %s mode",
												testStrings[i],
												windowed ? "windowed" : "fullscreen");
				resultFormat=testFormats[i];
				return true;
			}
		}
	}

	//If still failed, no color formats supported
	LOG::Instance()->OutputError("No suitable back buffer formats supported in %s mode",
										windowed ? "windowed" : "fullscreen");

	return false;
}