//////////////////////////////////////////////////////////////////////////////////////////
//	Main.cpp
//	Cel Shading
//	Downloaded from: www.paulsprojects.net
//	Created:	26th November 2002
//	Modified:	8th December 2002	-	Changed L8 textures to A8R8G8B8 to work on cards
//										with no L8 support
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <D3DX8.h>
#include "Log/LOG.h"
#include "Timer/TIMER.h"
#include "Fps Counter/FPS_COUNTER.h"
#include "Window/WINDOW.h"
#include "Bitmap Font/BITMAP_FONT.h"
#include "Main.h"

//link to libraries
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d8.lib")
#pragma comment(lib, "d3dx8.lib")

TIMER timer;
FPS_COUNTER fpsCounter;
BITMAP_FONT font;

//Main D3D interface
LPDIRECT3D8 d3d=NULL;

//D3D device
IDirect3DDevice8 * d3dDevice=NULL;

//Torus
ID3DXMesh * torus=NULL;
LPDIRECT3DVERTEXBUFFER8 torusVB=NULL;
LPDIRECT3DINDEXBUFFER8 torusIB=NULL;
D3DXCOLOR torusColor(0.75f, 0.95f, 1.0f, 1.0f);

//Sharp lighting texture
IDirect3DTexture8 * lightTexture;

//Border texture
IDirect3DTexture8 * borderTexture;

//Light
D3DXVECTOR3 lightPosition(5.0f, 5.0f, 5.0f);
D3DMATERIAL8 lightMaterial;
ID3DXMesh * lightSphere;
D3DXCOLOR lightColor(1.0f, 1.0f, 0.0f, 1.0f);

//Vertex shader handle
DWORD celVS;

//Vertex shader declaration
DWORD celVSDecl[]={	D3DVSD_STREAM(0),
					D3DVSD_REG(0, D3DVSDT_FLOAT3),	//position
					D3DVSD_REG(1, D3DVSDT_FLOAT3),	//normal
					D3DVSD_END()	};

//Matrices
D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;

//Set up D3D
bool D3DInit()
{
	//Init window
	if(!WINDOW::Instance()->Init("Cel Shading", 640, 480, D3DFMT_A8R8G8B8, D3DFMT_X8R8G8B8,
								 D3DFMT_D24S8, false, &d3d, &d3dDevice))
	{
		return false;
	}
	
	//Check for caps
	D3DCAPS8 caps;
	d3dDevice->GetDeviceCaps(&caps);

	//Check for 2 texture units
	if(caps.MaxSimultaneousTextures<2 || caps.MaxTextureBlendStages<2)
	{
		LOG::Instance()->OutputError("I require at least 2 simultaneous textures and");
		LOG::Instance()->OutputError("at least 2 texture blend stages");
		return false;
	}

	//Check for vertex shader 1.0
	if(D3DSHADER_VERSION_MAJOR(caps.VertexShaderVersion)<1)
	{
		LOG::Instance()->OutputError("I require at least vertex shader 1.0");
		return false;
	}


	//Init font
	if(!font.Init(d3dDevice))
		return false;

	//Enable z buffer
	d3dDevice->SetRenderState(D3DRS_ZENABLE, true);

	//Cull CW since using a RH coordinate system
	d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//Disable Lighting
	d3dDevice->SetRenderState(D3DRS_LIGHTING, false);

	//Set up projection matrix
	D3DXMatrixPerspectiveFovRH(	&projectionMatrix,
								D3DX_PI/4,
							(float)WINDOW::Instance()->width/(float)WINDOW::Instance()->height,
								1.0f,
								100.0f);
	d3dDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	//Set up view matrix
	D3DXMatrixTranslation(&viewMatrix, 0.0f, 0.0f, -20.0f);
	d3dDevice->SetTransform(D3DTS_VIEW, &viewMatrix);

	return true;
}

//Set up variables
bool DemoInit()
{
	HRESULT hr;

	//Create the torus
	hr=D3DXCreateTorus(d3dDevice, 1.5f, 4.0f, 24, 36, &torus, NULL);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to create torus");
		return false;
	}

	//Fill our vertex and index buffers from the torus mesh
	hr=torus->GetVertexBuffer(&torusVB);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to get torus vertex buffer");
		return false;
	}

	hr=torus->GetIndexBuffer(&torusIB);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to get torus index buffer");
		return false;
	}
	
	//Create the light sphere
	hr=D3DXCreateSphere(d3dDevice, 0.25f, 12, 24, &lightSphere, NULL);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to create light sphere");
		return false;
	}

	//Init the light material
	memset(&lightMaterial, 0, sizeof(D3DMATERIAL8));
	lightMaterial.Emissive=lightColor;


	//Create the sharp lighting texture
	hr=d3dDevice->CreateTexture(16, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &lightTexture);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to create cel brightness texture");
		return false;
	}

	D3DLOCKED_RECT dataRect;
	memset(&dataRect, 0, sizeof(D3DLOCKED_RECT));

	//Lock the texture to this rectangle
	hr=lightTexture->LockRect(0, &dataRect, NULL, 0);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to lock texture");
		return false;
	}

	//Copy the data into the locked rectangle
	unsigned char celBrightData[16]={	127, 127, 127, 191, 191, 191, 191, 191,
										255, 255, 255, 255, 255, 255, 255, 255};

	unsigned char * dataPtr=(unsigned char *)dataRect.pBits;

	for(int i=0; i<16; ++i)
	{
		dataPtr[i*4+0]=celBrightData[i];
		dataPtr[i*4+1]=celBrightData[i];
		dataPtr[i*4+2]=celBrightData[i];
		dataPtr[i*4+3]=celBrightData[i];
	}

	//Unlock the texture surface
	lightTexture->UnlockRect(0);


	//Create the border texture
	hr=d3dDevice->CreateTexture(8, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &borderTexture);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to create border texture");
		return false;
	}

	memset(&dataRect, 0, sizeof(D3DLOCKED_RECT));

	//Lock the texture to this rectangle
	hr=borderTexture->LockRect(0, &dataRect, NULL, 0);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to lock texture");
		return false;
	}

	//Copy the data into the locked rectangle
	unsigned char borderData[8]={0, 0, 255, 255, 255, 255, 255, 255};

	dataPtr=(unsigned char *)dataRect.pBits;
	
	for(int i=0; i<8; ++i)
	{
		dataPtr[i*4+0]=borderData[i];
		dataPtr[i*4+1]=borderData[i];
		dataPtr[i*4+2]=borderData[i];
		dataPtr[i*4+3]=borderData[i];
	}

	//Unlock the texture surface
	borderTexture->UnlockRect(0);


	//Load and create vertex shader
	LPD3DXBUFFER vsCode;
	hr=D3DXAssembleShaderFromFile("celVS.txt", 0, NULL, &vsCode, NULL);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to load vertex shader");
		return false;
	}

	hr=d3dDevice->CreateVertexShader(	celVSDecl, (DWORD *)vsCode->GetBufferPointer(),
										&celVS, D3DUSAGE_SOFTWAREPROCESSING);
	if(FAILED(hr))
	{
		LOG::Instance()->OutputError("Unable to create vertex shader");
		return false;
	}
	vsCode->Release();


	//reset timer
	timer.Reset();

	return true;
}

//Perform per-frame updates
void UpdateFrame()
{
	//set currentTime and timePassed
	static double lastTime=timer.GetTime();
	double currentTime=timer.GetTime();
	double timePassed=currentTime-lastTime;
	lastTime=currentTime;

	//Update window
	WINDOW::Instance()->Update();

	//rotation angles
	static float angleYaw=-0.5f, anglePitch=1.2f;

	//Rotate the model with the mouse
	if(WINDOW::Instance()->IsLeftButtonPressed())
	{
		angleYaw+=(float)WINDOW::Instance()->GetMouseXMovement()/180;
		anglePitch+=(float)WINDOW::Instance()->GetMouseYMovement()/180;
	}

	//Set world matrix for torus
	D3DXMATRIX tempMatrix1, tempMatrix2, tempMatrix3;
	D3DXMatrixRotationX(&tempMatrix1, D3DX_PI/2);	//first align torus' axis with Y axis
	D3DXMatrixRotationZ(&tempMatrix2,-angleYaw);
	D3DXMatrixRotationX(&tempMatrix3, anglePitch);
	worldMatrix=tempMatrix1*tempMatrix2*tempMatrix3;
	d3dDevice->SetTransform(D3DTS_WORLD, &worldMatrix);


	//Calculate the inverse world matrix
	D3DXMATRIX inverseWorldMatrix;
	D3DXMatrixInverse(&inverseWorldMatrix, NULL, &worldMatrix);

	//Calculate the object space camera position
	D3DXVECTOR4 objectSpaceCameraPos;
	D3DXVec3Transform(&objectSpaceCameraPos, &D3DXVECTOR3(0.0f, 0.0f, 20.0f),
											 &inverseWorldMatrix);
	//Homogenous divide not necessary since world matrix is composed of rotations
	//objectSpaceCameraPos/=objectSpaceCameraPos.w;

	//Similarly calculate the object space light position
	D3DXVECTOR4 objectSpaceLightPos;
	D3DXVec3Transform(&objectSpaceLightPos, &lightPosition, &inverseWorldMatrix);
	//objectSpaceLightPos/=objectSpaceLightPos.w;

	//Calculate the total matrix
	D3DXMATRIX totalMatrix;
	totalMatrix=worldMatrix*viewMatrix*projectionMatrix;
	D3DXMatrixTranspose(&totalMatrix, &totalMatrix);

	//Update vertex shader constants
	d3dDevice->SetVertexShaderConstant(0, &totalMatrix, 4);
	d3dDevice->SetVertexShaderConstant(4, &torusColor, 1);
	d3dDevice->SetVertexShaderConstant(5, &objectSpaceLightPos, 1);
	d3dDevice->SetVertexShaderConstant(6, &objectSpaceCameraPos, 1);
	
	//Render frame
	RenderFrame(currentTime, timePassed);
}

//Render a frame
void RenderFrame(double currentTime, double timePassed)
{
	//Clear buffers
	d3dDevice->Clear(	0,
						NULL,
						D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,	//which buffers to clear
						D3DCOLOR_XRGB(51, 160, 14),			//color to clear to
						1.0f, 0);							//depth & stencil values

	//Bind brightness texture to tex0
	d3dDevice->SetTexture(0, lightTexture);
	d3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_POINT);
	d3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTEXF_POINT);
	d3dDevice->SetTextureStageState(0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
	d3dDevice->SetTextureStageState(0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);

	//Bind border texture to tex1
	d3dDevice->SetTexture(1, borderTexture);
	d3dDevice->SetTextureStageState(1, D3DTSS_MAGFILTER, D3DTEXF_POINT);
	d3dDevice->SetTextureStageState(1, D3DTSS_MINFILTER, D3DTEXF_POINT);
	d3dDevice->SetTextureStageState(1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
	d3dDevice->SetTextureStageState(1, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);

	//Set texture stages to output tex0*col0*tex1
	d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	d3dDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	d3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	d3dDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	

	//Draw scene
	if(SUCCEEDED(d3dDevice->BeginScene()))
	{
		//Set vertex shader
		d3dDevice->SetVertexShader(celVS);

		//Set stream source
		unsigned int stride=D3DXGetFVFVertexSize(torus->GetFVF());
		d3dDevice->SetStreamSource(0, torusVB, stride);

		//Set indices
		d3dDevice->SetIndices(torusIB, 0);

		//Draw torus
		d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, torus->GetNumVertices(),
										0, torus->GetNumFaces());

		//End Drawing
		d3dDevice->EndScene();
	}

	//Disable textures
	d3dDevice->SetTexture(0, NULL);
	d3dDevice->SetTexture(1, NULL);

	//Set texture stages to simply output diffuse
	d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);

	d3dDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	d3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SELECTARG1);

	//Enable lighting
	d3dDevice->SetRenderState(D3DRS_LIGHTING, true);

	//Move to light position
	D3DXMatrixTranslation(&worldMatrix, lightPosition.x, lightPosition.y, lightPosition.z);
	d3dDevice->SetTransform(D3DTS_WORLD, &worldMatrix);

	//Draw light
	if(SUCCEEDED(d3dDevice->BeginScene()))
	{
		d3dDevice->SetMaterial(&lightMaterial);
		lightSphere->DrawSubset(0);

		//End Drawing
		d3dDevice->EndScene();
	}

	//Disable lighting
	d3dDevice->SetRenderState(D3DRS_LIGHTING, false);



	fpsCounter.Update();

	//Print text
	if(SUCCEEDED(d3dDevice->BeginScene()))
	{
		font.StartTextMode();
		font.Print(0, 8, 0xFFFFFF00, "FPS: %.2f", fpsCounter.GetFps());
		font.EndTextMode();

		//End Drawing
		d3dDevice->EndScene();
	}


	//Swap buffers
	d3dDevice->Present(NULL, NULL, NULL, NULL);

	//Save a screenshot
	if(WINDOW::Instance()->IsKeyPressed(VK_F1))
	{
		WINDOW::Instance()->SaveScreenshot(d3dDevice);
		WINDOW::Instance()->SetKeyReleased(VK_F1);
	}

	//quit if necessary
	if(WINDOW::Instance()->IsKeyPressed(VK_ESCAPE))
		PostQuitMessage(0);
}

//Shut down demo
void DemoShutdown()
{
	d3dDevice->SetStreamSource(0, NULL, 0);
	d3dDevice->SetTexture(0, NULL);
	d3dDevice->SetTexture(1, NULL);

	//Release torus objects
	if(torus)
		torus->Release();
	torus=NULL;

	if(torusVB)
		torusVB->Release();
	torusVB=NULL;

	if(torusIB)
		torusIB->Release();
	torusIB=NULL;

	//Release light sphere
	if(lightSphere)
		lightSphere->Release();
	lightSphere=NULL;

	//release textures
	if(lightTexture)
		lightTexture->Release();
	lightTexture=NULL;

	if(borderTexture)
		borderTexture->Release();
	borderTexture=NULL;

	//Shut down D3D objects
	if(d3dDevice)
		d3dDevice->Release();
	d3dDevice=NULL;

	if(d3d)
		d3d->Release();
	d3d=NULL;

	font.Shutdown();
	WINDOW::Instance()->Shutdown();
}

//WinMain
int WINAPI WinMain(	HINSTANCE	hInstance,			//Instance
					HINSTANCE	hPrevInstance,		//Previous Instance
					LPSTR		lpCmdLine,			//Command line params
					int			nShowCmd)			//Window show state
{
	//Save hInstance
	WINDOW::Instance()->hInstance=hInstance;

	//Init D3D and variables
	if(!D3DInit())
	{
		LOG::Instance()->OutputError("Direct3D Initiation Failed");
		return false;
	}
	else
		LOG::Instance()->OutputSuccess("Direct3D Initiation Successful");

	if(!DemoInit())
	{
		LOG::Instance()->OutputError("Demo Initiation Failed");
		return false;
	}
	else
		LOG::Instance()->OutputSuccess("Demo Initiation Successful");

	//Main Loop
	for(;;)
	{
		if(!(WINDOW::Instance()->HandleMessages()))	//quit if HandleMessages returns false
			break;

		UpdateFrame();
	}

	//Shutdown
	DemoShutdown();

	//Exit program
	LOG::Instance()->OutputSuccess("Exiting...");
	return 0;
}
