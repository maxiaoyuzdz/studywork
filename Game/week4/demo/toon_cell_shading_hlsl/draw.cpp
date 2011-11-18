/*****************************************************************************/
/*                                                                           */
/*   draw.cpp                                                                */
/*   www.xbdev.net                                                           */
/*                                                                           */
/*****************************************************************************/


#include <windows.h>
#include <assert.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9mesh.h>  


#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")

#include <stdio.h>  //sprintf(..)

#include "dxdbg.h"


#define SZ_FX_FILE					"media//toon.fx"

#define SZ_X_FILE					"media//tank.x"

#define SZ_TEXTURE_FILE0			"media//toon.bmp"



extern LPDIRECT3DDEVICE9			g_pd3dDevice;
extern HWND							g_hWnd;

extern float						g_fSpinX;
extern float						g_fSpinY;
extern float						g_fZoom;


static ID3DXEffect*					g_pEffect				= NULL;
static LPDIRECT3DVERTEXDECLARATION9 g_pVertexDeclaration	= NULL;

static IDirect3DTexture9*			g_pTexture0;

static LPD3DXBUFFER					g_pMtrlBuffer = NULL;
static DWORD						g_dwMaterials;
static LPD3DXMESH					g_pMesh;




bool LoadShader();
bool LoadMesh();
bool LoadTextures();


const D3DVERTEXELEMENT9 declaration[] = 
{
	{ 0, 0  * sizeof(float),D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },  // pos
	{ 0, 3  * sizeof(float),D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },  // normal
	{ 0, 6  * sizeof(float),D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },  // tex0
	D3DDECL_END()
};


bool LoadMesh()
{
	ID3DXMesh * pMesh = NULL;
	HRESULT hr = S_OK;							// Error checking variable

	hr |= 
	// File Name ---------+
    //                    |
    //                   \|/
    //                    |
    D3DXLoadMeshFromX( SZ_X_FILE,				// pFilename
						D3DXMESH_SYSTEMMEM,		// Options
						g_pd3dDevice,			// pD3DDevice
                        NULL,					// ppAdjacency
						&g_pMtrlBuffer,			// ppMaterials
						NULL,					// ppEffectInstances
						&g_dwMaterials,			// pNumMaterials
						&pMesh);				// ppMesh

	hr |= 
	pMesh->CloneMesh( D3DXMESH_SYSTEMMEM,
						declaration,
						g_pd3dDevice,
						&g_pMesh );
	pMesh->Release();


	hr |=
	D3DXComputeNormals(g_pMesh,					// Mesh
						NULL);					// pAdjacency


	if( hr!= S_OK )
	{
		MessageBox(0, "Failed in LoadMesh()", "Load Error", 0);
		return false;
	}

	return true;
}


bool LoadTextures()
{
	HRESULT hr = S_OK;							// Error checking variable

	hr |= 
	D3DXCreateTextureFromFile(g_pd3dDevice, 
                              SZ_TEXTURE_FILE0, 
                              &g_pTexture0);

	if( hr!= S_OK )
	{
		MessageBox(0, "Failed in LoadTextures()", "Load Error", 0);
		return false;
	}

	return true;
}

bool Create()
{
	bool bOkay = true;
	
	bOkay &= LoadShader();

	bOkay &= LoadMesh();

	bOkay &= LoadTextures();

	return bOkay;
}//End Create(..)


bool Release()
{
	g_pMesh->Release();
	g_pMtrlBuffer->Release();

	g_pTexture0->Release();

	if( g_pEffect )
	{
		g_pEffect->Release();
		g_pVertexDeclaration->Release();
	}

	return true;
}// End Release()


bool LoadShader()
{
	LPD3DXBUFFER pBufferErrors;
	DWORD dwShaderFlags = 0;

	HRESULT hr =									// Return Error Checking
		
	D3DXCreateEffectFromFile(	g_pd3dDevice,		// pDevice
								SZ_FX_FILE,			// pSrcFile
								NULL,				// pDefines
								NULL,				// pInclude
								dwShaderFlags,		// Flags
								NULL,				// pPool
								&g_pEffect,			// ppEffect
								&pBufferErrors);	// ppCompilationErrors

	if(FAILED(hr) )
	{
		LPVOID pCompileErrors = pBufferErrors->GetBufferPointer(); 
		MessageBox(NULL, (const char*)pCompileErrors, "Compile Error", 
		MB_OK|MB_ICONEXCLAMATION);

		return false;
	}

	g_pd3dDevice->CreateVertexDeclaration( declaration, &g_pVertexDeclaration );
	g_pd3dDevice->SetVertexDeclaration( g_pVertexDeclaration );

	return true;
}// End LoadShader(..)




void SetShaderConstants(float x, float y, float z)
// Setting Shader Constants
{		
	D3DXMATRIX matTrans;
	D3DXMATRIX matRot;
    D3DXMATRIX matProj,matIWorld,matView,matWorld;

	D3DXMatrixTranslation( &matTrans, x, y, z + g_fZoom ); 
	

	D3DXMatrixRotationYawPitchRoll( &matRot, D3DXToRadian(g_fSpinX), 
										     D3DXToRadian(g_fSpinY), 
												0.0f );
	
	D3DXMatrixPerspectiveFovLH( &matProj, D3DXToRadian( 45.0f ), 
                            640.0f / 480.0f, 0.1f, 500.0f );

	matWorld = matRot * matTrans;

	D3DXMatrixIdentity( &matView ); // This sample is not really making use of a view matrix

	D3DXMATRIX worldViewProj = matWorld * matView * matProj;

	D3DXMATRIX matWorldI = matWorld;
	D3DXMatrixTranspose(&matWorldI, &matWorldI);

	g_pEffect->SetMatrix("matWorldViewProj", &worldViewProj);
	g_pEffect->SetMatrix("matWorld",  &matWorld);
	g_pEffect->SetMatrix("matWorldI", &matWorldI);

}//End SetShaderConstants(..)






void RenderShape()
{
	DWORD iPass = 0;
	UINT cPasses = 0;

	SetShaderConstants(0,0,0);

	g_pEffect->SetTechnique("ToonEffect");
	g_pd3dDevice->SetVertexDeclaration( g_pVertexDeclaration );

	g_pEffect->SetTexture("texture0", g_pTexture0);

	g_pEffect->Begin(&cPasses, 0);	
	g_pEffect->BeginPass(0);

	g_pMesh->DrawSubset(0);
	
	//End of our Effect Render
	g_pEffect->EndPass();
	g_pEffect->End();
}// End RenderShape(..)



/***************************************************************************/
/*                                                                         */
/* render()                                                                */
/* Our main render loop, which gets called over and over agian to do our   */
/* drawing...clears the screen, draws the data, then presents it..         */
/*                                                                         */
/***************************************************************************/
bool Render()
{

#if(0)
	g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
#else
	g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
#endif

	g_pd3dDevice->Clear( 0, 
						 NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
						 0xAA338800, 
						 1.0f, 
						 0 );

    g_pd3dDevice->BeginScene();
	
	RenderShape();


	TriDisplay(g_pd3dDevice, g_pMesh->GetNumFaces() );
	FPSDisplay(g_pd3dDevice);
    g_pd3dDevice->EndScene();
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );


	return true;

}//End Render()
