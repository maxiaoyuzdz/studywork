/*****************************************************************************/
/*
   main.cpp
   www.xbdev.net
*/
/*****************************************************************************/
/*

*/
/*****************************************************************************/


#define STRICT
#define WIN32_LEAN_AND_MEAN

#define D3D_DEBUG_INFO

#include <windows.h>
#include <assert.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <stdio.h>  //sprintf(..)

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")



/*****************************************************************************/
/*
   GLOBALS
   As much as we all hate them, its sometimes a little easier...so we've got
   a few globals for the essential of our code.
/*
/*****************************************************************************/

HWND                    g_hWnd          = NULL;
LPDIRECT3D9             g_pD3D          = NULL;
LPDIRECT3DDEVICE9       g_pd3dDevice    = NULL;



float			g_fSpinX			=  0.0f;
float			g_fSpinY			= -5.0f;
float			g_fZoom             = 5.0f;


extern bool Create();   // draw.cpp - Initial creating/memory allocation etc
extern bool Render();   // draw.cpp - Called to render any shapes
extern bool Release();  // draw.cpp - Release any allocated resources




/***************************************************************************/
// PROTOTYPES                                                              //
/***************************************************************************/
bool init(void);         // - called at the start of our program
void renderLoop(void);   // - our mainloop..called over and over again
void shutDown(void);     // - last function we call before we end!


/***************************************************************************/
/*                                                                         */
/* Handle all messages for the main window here                            */
/*                                                                         */
/***************************************************************************/
long _stdcall MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
    static POINT ptLastMousePosit;
    static POINT ptCurrentMousePosit;
    static bool bMousing;
	static bool bZooming;
    
    switch( uMsg )
    {
        case WM_KEYDOWN:
        {
            switch( wParam )
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                    break;
            }
        }//End WM_KEYDOWN

        break;

        case WM_LBUTTONDOWN:
        {
            ptLastMousePosit.x = ptCurrentMousePosit.x = LOWORD (lParam);
            ptLastMousePosit.y = ptCurrentMousePosit.y = HIWORD (lParam);
            bMousing = true;
        }
        break;

		case WM_RBUTTONDOWN:
        {
            ptLastMousePosit.x = ptCurrentMousePosit.x = LOWORD (lParam);
            ptLastMousePosit.y = ptCurrentMousePosit.y = HIWORD (lParam);
            bZooming = true;
        }
        break;

        case WM_LBUTTONUP:
        {
            bMousing = false;
        }
        break;

		case WM_RBUTTONUP:
        {
			bZooming = false;
        }
        break;

        case WM_MOUSEMOVE:
        {
            ptCurrentMousePosit.x = LOWORD (lParam);
            ptCurrentMousePosit.y = HIWORD (lParam);

            if( bMousing )
            {
                g_fSpinX -= (ptCurrentMousePosit.x - ptLastMousePosit.x);
                g_fSpinY += (ptCurrentMousePosit.y - ptLastMousePosit.y);
            }

			if( bZooming )
            {
				// 0.2 is so the zoom isn't so fast!  Makes it more user friendly
                g_fZoom += (ptCurrentMousePosit.y - ptLastMousePosit.y) * 0.2f;
            }
            
            ptLastMousePosit.x = ptCurrentMousePosit.x;
            ptLastMousePosit.y = ptCurrentMousePosit.y;
        }
	}//End switch(..)


    if(uMsg == WM_DESTROY )
    {
            // We destroy any directx memory we allocated etc, 
            // Tidy up before leaving.
		    shutDown();

            PostQuitMessage(0);
			return 0;
    }

    return (long)DefWindowProc(hWnd, uMsg, wParam, lParam);
}


/***************************************************************************/
/*                                                                         */
/* Program entry point.                                                    */
/*                                                                         */
/***************************************************************************/
int _stdcall WinMain(HINSTANCE i, HINSTANCE, char* k, int) 
{
    MSG msg;
    char szname[] = "www.xbdev.net";
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      szname, NULL };
    RegisterClassEx( &wc );
    g_hWnd = CreateWindowEx(WS_EX_APPWINDOW,
                     szname, szname, 
                     WS_OVERLAPPEDWINDOW,//for fullscreen make into WS_POPUP
                     50, 50, 500,500,    //for full screen 
										  // GetSystemMetrics(SM_CXSCREEN), 
										  // GetSystemMetrics(SM_CYSCREEN),
                     GetDesktopWindow(), NULL, wc.hInstance, NULL);
    
    // Initilise or directX code here!
	if( init() == false)
	{
		shutDown();
		return 0;
	}

    ShowWindow(g_hWnd, SW_SHOW);
    UpdateWindow(g_hWnd);     
 
    // Message loop. Note that this has been modified to allow
    // us to execute if no messages are being processed.
    while(1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            if (!GetMessage(&msg, NULL, 0, 0))
                break;

            DispatchMessage(&msg);
        }
		else
			// Idle-time processing - do our work here!
			renderLoop();
    }
    return 0;
}// End WinMain(..)






/***************************************************************************/
/*                                                                         */
/* init()                                                                  */
/* Called once at the start of our program to setup directx.               */
/*                                                                         */
/***************************************************************************/
bool init( void )
{
    g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

    D3DDISPLAYMODE d3ddm;

    g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );

	D3DPOOL_DEFAULT;

    d3dpp.Windowed               = TRUE;
    d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat       = d3ddm.Format;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    //d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_DEFAULT;
	//d3dpp.Flags                  = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;


#if(1) // HAL or REF
	
    g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
                          D3DCREATE_MIXED_VERTEXPROCESSING,
						  //D3DCREATE_HARDWARE_VERTEXPROCESSING,
                          &d3dpp, &g_pd3dDevice );
	
#else
	
	g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, g_hWnd,
                          D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                          &d3dpp, &g_pd3dDevice );
#endif


	// Lets enable alpha blending so we can have transparency
	g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,        D3DBLEND_SRCALPHA );
	g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,       D3DBLEND_INVSRCALPHA );

	g_pd3dDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);


	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE,          TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,     TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_ZFUNC,            D3DCMP_LESSEQUAL );
    g_pd3dDevice->SetRenderState( D3DRS_SHADEMODE,        D3DSHADE_FLAT );
    g_pd3dDevice->SetRenderState( D3DRS_FILLMODE,         D3DFILL_SOLID );
    g_pd3dDevice->SetRenderState( D3DRS_FOGENABLE,        FALSE );
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE,         D3DCULL_CCW );
    g_pd3dDevice->SetRenderState( D3DRS_CLIPPING,		  TRUE ); 
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING,         FALSE );
    g_pd3dDevice->SetRenderState( D3DRS_LOCALVIEWER,      FALSE );


	bool bOkay = true;
	
	bOkay &= Create();


	return bOkay;
}//End init(..)




/***************************************************************************/
/*                                                                         */
/* shutDown()                                                              */
/* Release any allocated memory, andy directx api's, resources etc before  */
/* our program finally terminates.                                         */
/*                                                                         */
/***************************************************************************/
void shutDown( void )
{
	Release();

    g_pd3dDevice->Release();
    g_pd3dDevice = NULL;

    g_pD3D->Release();
    g_pD3D = NULL;
}// End shutDown(..)


void renderLoop()
{
	Render();
}




