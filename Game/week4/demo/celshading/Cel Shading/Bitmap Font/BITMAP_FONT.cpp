//////////////////////////////////////////////////////////////////////////////////////////
//	BITMAP_FONT.cpp
//	Functions for a bitmap font class
//	Downloaded from: www.paulsprojects.net
//	Created:	26th November 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <D3DX8.h>
#include "../Log/LOG.h"
#include "../Window/WINDOW.h"
#include "BITMAP_FONT.h"

//Initiate font
bool BITMAP_FONT::Init(IDirect3DDevice8 * d3dDevice)
{
	//Create font
	LOGFONT logFont={	-18,			//height
						0,				//default width,
						0, 0,			//angles
						FW_BOLD,		//bold
						false,			//italic
						false,			//underline
						false,			//strikeout
						ANSI_CHARSET,	//character set
						OUT_TT_PRECIS,	//precision
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,	//quality
						FF_DONTCARE | DEFAULT_PITCH,
						"Courier New"};

	HRESULT hr;
	hr=D3DXCreateFontIndirect(d3dDevice, &logFont, &font);

	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to create font");
		return false;
	}
	LOG::Instance()->OutputSuccess("Font created successfully");
	
	return true;
}

//Start text mode
void BITMAP_FONT::StartTextMode(void)
{
	font->Begin();
}

//Print some text
void BITMAP_FONT::Print(int x, int y, DWORD color, const char * string, ...)
{
	//Get rect to fill with text
	RECT fontRect;
	fontRect.left=x;
	fontRect.right=10000;
	fontRect.top=y;
	fontRect.bottom=10000;

	if(string==NULL)
		return;

	//Convert to text
	static char text[256];

	va_list va;
	
	va_start(va, string);
	vsprintf(text, string, va);
	va_end(va);

	//Print the text
	font->DrawText(text, -1, &fontRect, DT_LEFT, color);
}

//End text mode
void BITMAP_FONT::EndTextMode(void)
{
	font->End();
}

