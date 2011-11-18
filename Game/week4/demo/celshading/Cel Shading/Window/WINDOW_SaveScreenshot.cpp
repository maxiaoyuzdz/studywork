//////////////////////////////////////////////////////////////////////////////////////////
//	WINDOW_SaveScreenshot.cpp
//	Save a screenshot
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

//Save a screenshot
void WINDOW::SaveScreenshot(IDirect3DDevice8 * d3dDevice)
{
	FILE * file;

	//Calculate the filename to use
	char filename[32];

	for(int i=0; i<1000; ++i)
	{
		sprintf(filename, "screen%03d.bmp", i);

		//Try opening this file. If it is not possible, use this filename
		file=fopen(filename, "rb");

		if(!file)
			break;

		//Otherwise, the file exists. Try the next, unless we reached the end
		fclose(file);

		if(i==999)
		{
			LOG::Instance()->OutputError("No space to save screenshot - 0 to 999 exist");
			return;
		}
	}

	LOG::Instance()->OutputSuccess("Saving %s", filename);

	HRESULT hr;

	//Get the size of the front buffer
	D3DDISPLAYMODE mode;

	hr=d3dDevice->GetDisplayMode(&mode);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to get front buffer size");
		return;
	}

	//Create an image surface the same size as the window
	LPDIRECT3DSURFACE8 surface=NULL;
	hr=d3dDevice->CreateImageSurface(mode.Width, mode.Height, D3DFMT_A8R8G8B8, &surface);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to create surface to hold screenshot");
		return;
	}

	//Copy the front buffer onto the surface
	hr=d3dDevice->GetFrontBuffer(surface);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to read front buffer");
		return;
	}

	//Save the screenshot
	hr=D3DXSaveSurfaceToFile(filename, D3DXIFF_BMP, surface, NULL, NULL);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to save %s", filename);
		return;
	}

	//Release the surface
	if(surface)
		surface->Release();
	surface=NULL;

	LOG::Instance()->OutputSuccess("Saved Screenshot: %s", filename);
	return;
}
