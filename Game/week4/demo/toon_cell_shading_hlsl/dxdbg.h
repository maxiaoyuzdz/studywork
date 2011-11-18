/**********************************************************************************/
/*                                                                                */
/*  File:    dxdbg.h                                                              */
/*  Author:  bkenwright@xbdev.net                                                 */
/*  Web:     www.xbdev.net                                                        */
/*  Date:    10-12-2005 (xmas)                                                    */
/*                                                                                */
/**********************************************************************************/
/*
    Updated: 12-12-05
	Simple debug functions/classes.

	Implemented so you can add simple debugging/testing output to various demos/
	games/test apps etc.  Most of the methods make use of static variables so
	functions can be called within main loops and won't create/release resources
	over and over again - this is so we don't have to create globals and also don't
	loose out due to inefficient creation/releasing of resources such as fonts
	bitmaps etc.

	Also designed for easy implementation of directx8 and directx9
*/
/**********************************************************************************/

#ifndef DXDBG_H
#define DXDBG_H

#include <d3dx9.h>
#pragma comment(lib, "D3d9.lib")
#pragma comment(lib, "D3dx9.lib")

#include <stdio.h> // sprintf(..)


#if(DIRECT3D_VERSION >= 0x0900)
#define IDirect3DDevice		IDirect3DDevice9
#define IDirect3DTexture	IDirect3DTexture9
#else
#define IDirect3DDevice		IDirect3DDevice8
#define IDirect3DTexture	IDirect3DTexture8
#endif // DIRECT3D_VERSION



void StatsDisplay(IDirect3DDevice  * pDevice,
				 char * str);

void FlatTexture(IDirect3DDevice  * pDevice,
				 IDirect3DTexture * pTexture );

void TriDisplay(IDirect3DDevice  * pDevice,
				 int nTris);


void printf(IDirect3DDevice * pDevice,
			char * str, 
			float xpos = 10, 
			float ypos = 10, 
			unsigned int rgb = 0xffffff,
			int size = 15);


void FPSDisplay(IDirect3DDevice  * pDevice);

void FlatSquare(IDirect3DDevice  * pDevice, 
				float x, 
				float y, 
				float w, 
				float h,
				unsigned int col );


class debugtxt
{
public:
	debugtxt(IDirect3DDevice * pDevice){ Create(pDevice); };
	~debugtxt(){ Release(); };

protected:
	ID3DXFont* pFont;

public:

	void printf(char * str, 
			int xpos = 10, 
			int ypos = 10, 
			unsigned int rgb = 0xffffff)
	{

			static char szbuff[900];
			sprintf(szbuff, "%s", str );
			RECT rect = {xpos,ypos, xpos+800,ypos+800};


			#if(DIRECT3D_VERSION >= 0x0900)
			pFont->DrawTextA(NULL,
									szbuff,
									-1,
									&rect,
									DT_LEFT,
									0xFFBBBBFF);
			#else
			pFont->DrawTextA(szbuff,
									-1,
									&rect,
									DT_LEFT,
									0xFFBBBBFF);
			#endif // DIRECT3D_VERSION

	}

	
protected:

	bool Create(IDirect3DDevice * pDevice)
	{
		//MessageBox(0, "create", "dbg", 0);

			#if(DIRECT3D_VERSION >= 0x0900)

				D3DXCreateFont(pDevice,  // LPDIRECT3DDEVICE9
							15,          // Width
							0,           // Height
							FW_NORMAL,   // Weight
							1,           // MipLevels
							false,       // Italic
							DEFAULT_CHARSET,     // CharSet
							OUT_DEFAULT_PRECIS,  // OutputPrecision
							ANTIALIASED_QUALITY, // Quality
							DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
							"Arial",     // pFacename
							&pFont);     // LPD3DXFONT

			#else
				LPD3DXFONT ff;
				static LOGFONT lfont={
						15, //height
						0,  //width; 
						0,  // lfEscapement; 
						0,  //lfOrientation; 
						FW_BOLD, // lfWeight; 
						FALSE, // lfItalic; 
						FALSE, // lfUnderline; 
						FALSE, // lfStrikeOut; 
						DEFAULT_CHARSET, // lfCharSet; 
						OUT_DEFAULT_PRECIS, //lfOutPrecision; 
						CLIP_DEFAULT_PRECIS, // lfClipPrecision; 
						ANTIALIASED_QUALITY,// lfQuality; 
						DEFAULT_PITCH,// lfPitchAndFamily; 
						"Arial"// lfFaceName[LF_FACESIZE]; 
						};

				lfont.lfHeight = size;

			//This is all there is to creating a D3DXFont.  Hmmmm....
			D3DXCreateFontIndirect( pDevice ,&lfont,&pFont );

			#endif // DIRECT3D_VERSION

			return true;

	}//End Create(..)

	void Release()
	{
		//MessageBox(0, "release", "dbg", 0);
		pFont->Release();
	}
};

#endif // DXDBG_H