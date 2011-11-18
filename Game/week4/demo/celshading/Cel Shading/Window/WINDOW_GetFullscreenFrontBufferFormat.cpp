//////////////////////////////////////////////////////////////////////////////////////////
//	WINDOW_GetFullscreenFrontBufferFormat.cpp
//	Get a supported full screen front buffer format. (windowed uses the current display mode)
//	Will first try to use given format, then some fallbacks
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

//Get a supported front buffer format
bool WINDOW::GetFullscreenFrontBufferFormat(D3DFORMAT requestedFormat, D3DFORMAT & resultFormat,
											LPDIRECT3D8 d3d)
{
	//See if the requested front buffer format is supported
	HRESULT hr;
	
	bool requestedFormatSupported=false;
	bool X8R8G8B8Supported=false;
	bool R5G6B5Supported=false;

	//Get the number of available display modes
	unsigned int numModes=d3d->GetAdapterModeCount(D3DADAPTER_DEFAULT);

	//Loop through the modes to see if the formats are supported
	for(unsigned int i=0; i<numModes; ++i)
	{
		D3DDISPLAYMODE mode;
		hr=d3d->EnumAdapterModes(D3DADAPTER_DEFAULT, i, &mode);

		if(mode.Format==requestedFormat)
			requestedFormatSupported=true;

		if(mode.Format==D3DFMT_X8R8G8B8)
			X8R8G8B8Supported=true;

		if(mode.Format==D3DFMT_R5G6B5)
			R5G6B5Supported=true;
	}

	//Return the best supported format
	if(requestedFormatSupported)
	{
		LOG::Instance()->OutputSuccess("Chosen front buffer format is available in fullscreen mode");
		resultFormat=requestedFormat;
		return true;
	}

	if(X8R8G8B8Supported)
	{
		LOG::Instance()->OutputMisc("D3DFMT_X8R8G8B8 will be used instead of chosen front buffer format in %s mode");
		resultFormat=D3DFMT_X8R8G8B8;
		return true;
	}

	if(R5G6B5Supported)
	{
		LOG::Instance()->OutputMisc("D3DFMT_R5G6B5 will be used instead of chosen front buffer format in %s mode");
		resultFormat=D3DFMT_R5G6B5;
		return true;
	}

	
	//No color formats supported
	LOG::Instance()->OutputError("No suitable front buffer formats supported in fullscreen mode");
	
	return false;
}