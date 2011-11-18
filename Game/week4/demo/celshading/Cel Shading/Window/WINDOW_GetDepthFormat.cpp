//////////////////////////////////////////////////////////////////////////////////////////
//	WINDOW_GetDepthFormat.cpp
//	Get a supported depth format. Will first try to use given format, then some fallbacks
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

//Get a supported depth format
bool WINDOW::GetDepthFormat(D3DFORMAT requestedFormat, D3DFORMAT & resultFormat,
							D3DFORMAT frontBufferFormat, D3DFORMAT backBufferFormat, 
							LPDIRECT3D8 d3d, bool windowed)
{
	//See if the requested depth format is supported
	HRESULT hr, hr2;
	
	hr=d3d->CheckDeviceFormat(	D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, frontBufferFormat,
								D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, requestedFormat);

	hr2=d3d->CheckDepthStencilMatch(	D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, frontBufferFormat,
										backBufferFormat, requestedFormat);

	if(SUCCEEDED(hr) && SUCCEEDED(hr2))
	{
		LOG::Instance()->OutputSuccess("Chosen depth format is available in %s mode",
										windowed ? "windowed" : "fullscreen");
		resultFormat=requestedFormat;
		return true;
	}

	//If failed, try D24S8, D16
	D3DFORMAT testFormats[2]={D3DFMT_D24S8, D3DFMT_D16};
	char * testStrings[3]={"D3DFMT_D24S8", "D3DFMT_D16"};
	for(int i=0; i<2; ++i)
	{
		D3DFORMAT currentTestFormat=testFormats[i];
		
		if(FAILED(hr))
		{
			hr=d3d->CheckDeviceFormat(	D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, frontBufferFormat,
										D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE,
										currentTestFormat);

			hr2=d3d->CheckDepthStencilMatch(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
											frontBufferFormat,
											backBufferFormat, currentTestFormat);

			if(SUCCEEDED(hr) && SUCCEEDED(hr2))
			{
				LOG::Instance()->OutputError("%s will be used instead of chosen depth format in %s mode",
												testStrings[i],
												windowed ? "windowed" : "fullscreen");
				resultFormat=testFormats[i];
				return true;
			}
		}
	}

	//If still failed, no color formats supported
	LOG::Instance()->OutputError("No suitable depth formats supported in %s mode",
									windowed ? "windowed" : "fullscreen");
	
	return false;
}