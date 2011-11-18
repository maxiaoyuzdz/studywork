/**********************************************************************************/
/*                                                                                */
/*  File:    dxdbg.cpp                                                            */
/*  Author:  bkenwright@xbdev.net                                                 */
/*  Web:     www.xbdev.net                                                        */
/*  Date:    10-12-2005 (xmas)                                                    */
/*                                                                                */
/**********************************************************************************/


#include "dxdbg.h"



#include <stdio.h> //sprintf(..)

/*
void StatsDisplay(IDirect3DDevice  * pDevice,
				 char * str)
{
	int len = strlen(str);
	static float pos = 0;
	pos+=0.1f;

	if( int(pos) >= len ) pos = 0.0f;

	char buf[500];

	sprintf(buf, "%s", str+int(pos) );

	static debugtxt txt(pDevice);

	txt.printf(buf, 5, 250 , 0);
}
*/

void TriDisplay(IDirect3DDevice  * pDevice,
				 int nTris)
{
	static char buff[100];
	sprintf(buff, "tris : %d", nTris);
	//printf(pDevice, buff, 10, 23  );

	static debugtxt txt(pDevice);
	txt.printf(buff, 10, 24 , 0);
}

void WireSquare(IDirect3DDevice  * pDevice, 
				float x, 
				float y, 
				float w, 
				float h,
				unsigned int col )
{
		struct TLVERTEX
		{
			float x,y,z,rhw;
			unsigned int colour;
			enum{ FVF_TLVERTEX = D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
		};

		//pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		pDevice->SetTextureStageState(0,D3DTSS_COLOROP,	D3DTOP_SELECTARG1);
		pDevice->SetTextureStageState(0,D3DTSS_COLORARG1,	D3DTA_DIFFUSE);
		float scale = 128.0f;
		TLVERTEX Vertex[4] = 
		{
			//   x      y    z    rhw     colour
			{    x,     y,   0,  1.0f,   col},
			{    x+w,   y,   0,  1.0f,   col},
			{    x+w,   y+h, 0,  1.0f,   col},
			{    x,     y+h, 0,  1.0f,   col},
		};
		pDevice->SetTexture( 0, NULL);
		
#if(DIRECT3D_VERSION >= 0x0900)
		pDevice->SetFVF( TLVERTEX::FVF_TLVERTEX );
#else
		pDevice->SetVertexShader( TLVERTEX::FVF_TLVERTEX );
#endif // DIRECT3D_VERSION

		
		HRESULT hr = pDevice->DrawPrimitiveUP( D3DPT_LINELIST, 2, Vertex, sizeof( TLVERTEX ) );
		pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
}


void FlatSquare(IDirect3DDevice  * pDevice, 
				float x, 
				float y, 
				float w, 
				float h,
				unsigned int col )
{
		struct TLVERTEX
		{
			float x,y,z,rhw;
			unsigned int colour;
			enum{ FVF_TLVERTEX = D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
		};

		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		pDevice->SetTextureStageState(0,D3DTSS_COLOROP,	D3DTOP_SELECTARG1);
		pDevice->SetTextureStageState(0,D3DTSS_COLORARG1,	D3DTA_DIFFUSE);
		float scale = 128.0f;
		TLVERTEX Vertex[4] = 
		{
			//   x      y    z  rhw     colour
			{    x,     y,   0,  1.0f,   col},
			{    x+w,   y,   0,  1.0f,   col},
			{    x+w,   y+h, 0,  1.0f,   col},
			{    x,     y+h, 0,  1.0f,   col},
		};
		pDevice->SetTexture( 0, NULL);

		
#if(DIRECT3D_VERSION >= 0x0900)
		pDevice->SetFVF( TLVERTEX::FVF_TLVERTEX );
#else
		pDevice->SetVertexShader( TLVERTEX::FVF_TLVERTEX );
#endif // DIRECT3D_VERSION

		HRESULT hr = pDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, Vertex, sizeof( TLVERTEX ) );
}

int GetFPS()
{
	float fTimeNow = (float)GetTickCount();
	static float fOldTime = fTimeNow;

	static int nCounter = 0;
	nCounter++;

	static int nFPS = 0;
	if( fOldTime+1000.0f < fTimeNow )
	{
		fOldTime = fTimeNow;

		nFPS = nCounter;
		nCounter = 0;
	}//End if

	return nFPS;
}//End GetFPS(..)

void FPSDisplay(IDirect3DDevice  * pDevice)
{
	int fps = GetFPS();

	// Scale the width as values can go from 0 to 300+ etc
	int w = fps*2;

	// Typically about 30 to 300 fps, so we'll limit our bar width
	if( w < 50  ) w = 50;
	if( w > 250 ) w = 250;
	
	// Linear value.  Lets say our fps goes from 0 to 1000, then we can
	// scale it from 0 to 0xff
	int r = (int)(float(fps)/500.0f)*0xff;

	// Create a changing colour with fps value

	DWORD col = D3DCOLOR_ARGB(0x33, r, 55, 55);
	
	FlatSquare(pDevice, 5, 5, (float)w, 17, col);
	WireSquare(pDevice, 5, 5, (float)w, 17, 0x00ffffff);

	static char buff[100];
	sprintf(buff, "fps : %d", fps);
	//printf(pDevice, buff, 10, 6  );

	static debugtxt txt(pDevice);

	txt.printf(buff, 10, 6 , 0);

}



void FlatTexture(IDirect3DDevice  * pDevice,
				 IDirect3DTexture * pTexture )
{
		struct TLVERTEX
		{
			float x,y,z,rhw;
			float tu,tv;
		};
		#define	FVF_TLVERTEX (D3DFVF_XYZRHW | D3DFVF_TEX1)

		pDevice->SetTextureStageState(0,D3DTSS_COLOROP,	D3DTOP_SELECTARG1);
		pDevice->SetTextureStageState(0,D3DTSS_COLORARG1,	D3DTA_TEXTURE);
		float scale = 128.0f;
		TLVERTEX Vertex[4] = 
		{
			// x  y  z rhw tu tv
			{    0,    0,0, 1, 0, 0,},
			{scale,    0,0, 1, 1, 0,},
			{scale,scale,0, 1, 1, 1,},
			{    0,scale,0, 1, 0, 1,},
		};

#if(DIRECT3D_VERSION >= 0x0900)
		pDevice->SetFVF( FVF_TLVERTEX );
#else
		pDevice->SetVertexShader( FVF_TLVERTEX );
#endif // DIRECT3D_VERSION

		pDevice->SetTexture( 0, pTexture );
		pDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, Vertex, sizeof( TLVERTEX ) );
}

void printf(IDirect3DDevice * pDevice,
			char * str, 
			int xpos /*= 10*/, 
			int ypos /*= 10*/, 
			unsigned int rgb /*= 0xffffff*/,
			int size /*=15*/)
{
	static ID3DXFont* pFont;

#if(DIRECT3D_VERSION >= 0x0900)

	D3DXCreateFont(pDevice,  // LPDIRECT3DDEVICE9
				size,        // Width
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
			size, //height
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



   static char szbuff[900];
   sprintf(szbuff, "%s", str );
   RECT rect = {xpos,ypos, ((int)xpos)+800,ypos+800};


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


	pFont->Release();
}

