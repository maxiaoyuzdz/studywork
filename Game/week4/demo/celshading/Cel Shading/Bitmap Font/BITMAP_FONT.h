//////////////////////////////////////////////////////////////////////////////////////////
//	BITMAP_FONT.h
//	Bitmap font class
//	Downloaded from: www.paulsprojects.net
//	Created:	26th November 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef BITMAP_FONT_H
#define BITMAP_FONT_H

class BITMAP_FONT
{
public:
	BITMAP_FONT()
	{}
	~BITMAP_FONT()	{}

	bool Init(IDirect3DDevice8 * d3dDevice);
	void Shutdown()
	{}

	//Text writing functions
	void StartTextMode(void);
	void Print(int x, int y, DWORD color, const char * string, ...);
	void EndTextMode(void);

protected:
	ID3DXFont * font;
};

#endif	//BITMAP_FONT_H
