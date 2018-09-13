#include	<iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>
//#include <GL/glew.h>
//#include <GL/wglew.h>

//#include "vec.h"
#include "win.h"
#include "bmp.h"
#include "gdi.h"
//#include "gl.h"

/*
static	bool	req_flg_SIEZE = false;
static	int		req_w = 0;
static	int		req_h = 0;

static	bool	req_flg_MOVE = false;
static	int		req_x = 0;
static	int		req_y = 0;
*/





//------------------------------------------------------------------------------
Win::~Win()
//------------------------------------------------------------------------------
{
}
//------------------------------------------------------------------------------
Win::Win( const char* classname, LRESULT CALLBACK (*callback)(HWND, UINT, WPARAM, LPARAM) )
//------------------------------------------------------------------------------
{
	QueryPerformanceFrequency(&m_frequency);

	strcpy( m_classname, classname );

	m_measure_timerSec = 0;
	m_measure_timerPaint = 0;
	m_measure_counterPaint = 0;

	m_Interval	= 0;
	m_Fps		= 0;
	m_ShowFlg	= 0;
	m_ShowSec	= 0;


	m_flgError = 0;
	m_hWnd = 0;
	m_hDC = 0;

	HINSTANCE	hInstance;
	hInstance	 = GetModuleHandle( NULL );

	WNDCLASSEX wc;
	wc.cbSize			= sizeof( WNDCLASSEX );
	wc.style			= 0;
	wc.lpfnWndProc		= callback;//WndProcStatic;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;  
	wc.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground 	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  	= MAKEINTRESOURCE( NULL );
	wc.lpszClassName 	= m_classname;
	wc.hIconSm			= NULL;
	if ( 0 == RegisterClassEx( &wc ) ) 
	{
		m_flgError = true;	
		printf("error1 @Win::OpenWin()\n");
		exit(0);
	}
	else
	{
	}



	QueryPerformanceFrequency(&m_frequency);

	FlgActive = true;
}


//------------------------------------------------------------------------------
void	Win::CloseWin()
//------------------------------------------------------------------------------
{
//			printf("~CloseWin.1\n");
//	Gl::DisableOpenGL( m_hWnd, &m_hDC, &m_hGLRC );

	if ( m_hDC ) ReleaseDC( m_hWnd, m_hDC );
	m_hDC = 0;

//			printf("~CloseWin.2\n");
	DestroyWindow( m_hWnd );
	m_hWnd = 0;
//			printf("~CloseWin.3\n");

	FlgActive = false;

}


//------------------------------------------------------------------------------
void	Win::OpenWin( int _x, int _y, int _w, int _h, int _buf_w, int _buf_h, const char* name )
//------------------------------------------------------------------------------
{

	m_x = _x;
	m_y = _y;
	m_w = _w;
	m_h = _h;

	m_buf_w = _buf_w;
	m_buf_h = _buf_h;
	
	HINSTANCE	hInstance;
	hInstance	 = GetModuleHandle( NULL );


	{
		{
			RECT rc;
			SetRect(&rc, 0, 0, _w, _h );

			//,(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
			int valWin = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
			AdjustWindowRectEx(&rc, valWin, FALSE, 0);


			m_hWnd = CreateWindowEx(
				  0
				, m_classname//m_classname//wc.lpszClassName
				, name 
				, valWin
				, m_x+rc.left   	        // horizontal position of window
				, m_y+rc.top				// vertical position of window
				, rc.right-rc.left 		// window width
				, rc.bottom-rc.top			// window height
				, NULL                    // handle to parent or owner window
				, NULL                    // handle to menu, or child-window identifier
				, hInstance               // handle to application instance
				, 0				       // pointer to window-creation data
			);


		}
	
		m_hDC = GetDC( m_hWnd );
//		Gl::EnableOpenGL( m_hWnd, &m_hDC, &m_hGLRC );
	}





}
//------------------------------------------------------------------------------
void	Win::ShowWin()
//------------------------------------------------------------------------------
{
		ShowWindow( m_hWnd, SW_NORMAL );
}

/*
//------------------------------------------------------------------------------
void	Win::MakeCurrentGL()
//------------------------------------------------------------------------------
{
			wglMakeCurrent( m_hDC, m_hGLRC );
		wglSwapIntervalEXT(1);
}
*/
//------------------------------------------------------------------------------
bool	Win::Message()
//------------------------------------------------------------------------------
{
	bool ret = true;
	//	message 

	{
		MSG	msg;
		while (PeekMessage( &msg, NULL, 0, 0, PM_REMOVE) )
		{
			if (msg.message == WM_QUIT)
			{
				ret = false;
				FlgActive = false;
			}
//			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return	ret;
}
/*
//------------------------------------------------------------------------------
void	Win::SwapBuffer()
//------------------------------------------------------------------------------
{

#if 0
	if ( req_flg_MOVE ) 
	{
		req_flg_MOVE = false;
		m_x = req_x;
		m_y = req_y;
	}
#endif


#if 0
	if ( req_flg_SIEZE ) 
	{
		req_flg_SIEZE = false;
		m_w = req_w;
		m_h = req_h;
	}
#endif

	//---

	LARGE_INTEGER f0;
	LARGE_INTEGER f1;

	// 描画速度計測:start
	QueryPerformanceCounter(&f0);

	{
		//glFenceSync — create a new sync object and insert it into the GL command stream
//		GLsync  SyncObject = glFenceSync( GL_SYNC_GPU_COMMANDS_COMPLETE, 0 );

		//glWaitSync — instruct the GL server to block until the specified sync object becomes signaled
//		glWaitSync( SyncObject, 0, GL_TIMEOUT_IGNORED );

//		wglSwapIntervalEXT( m_Interval );
#if 0
		SwapBuffers( m_hDC );
#else
//						SendMessage( m_hWnd , WM_PAINT , 0 , 0);
{
	extern	BITMAPINFO 	sys_bmpInfo;
	extern	BYTE * 		sys_pPixel;

//		if ( sys_pPixel ) GDI_Paint( m_hWnd, sys_bmpInfo, sys_pPixel );
//		if ( sys_pPixel ) GDI_Paint( m_hWnd, sys_bmpInfo, sys_pPixel );
		if ( sys_pPixel ) GDI_Draw( m_hWnd, sys_pPixel, m_buf_w, m_buf_h );

}
#endif

		//glClientWaitSync — block and wait for a sync object to become signaled
//		glClientWaitSync( SyncObject, 0, GL_TIMEOUT_IGNORED );

//		glDeleteSync( SyncObject );
	}

	// 描画速度計測:end
	QueryPerformanceCounter(&f1);


	// 描画速度計測:calc
	m_measure_timerPaint += (double)(f1.QuadPart-f0.QuadPart) / (double)m_frequency.QuadPart;
	m_measure_counterPaint++;
	m_measure_timerSec += m_timerFrame;


	// 描画速度計測:disp
	if ( m_ShowFlg && m_measure_timerSec > m_ShowSec )
	{
		char	str[256];
		sprintf( str, "paint %fms fps=%f\n", 1000 * m_measure_timerPaint / m_measure_counterPaint, (float)m_measure_counterPaint/m_ShowSec );

		SetWindowText( m_hWnd, str );

		// 描画速度計測:clear
		m_measure_timerSec = 0;
		m_measure_timerPaint = 0;
		m_measure_counterPaint = 0;
	}

	//-- wait

	if ( m_Interval == 0 )
	{
		m_timerFrame = 0;  
		while(true)
		{
			QueryPerformanceFrequency(&m_frequency);	// << これがないとなぜか遅くなる。
//	printf("tm %I64d \n", m_frequency.QuadPart );

			static	LARGE_INTEGER tm0;
			static	LARGE_INTEGER tm1;

			QueryPerformanceCounter(&tm1);
			m_timerFrame += (double)(tm1.QuadPart-tm0.QuadPart) / (double)m_frequency.QuadPart;
			QueryPerformanceCounter(&tm0);

			if ( m_timerFrame >= (1.0f/m_Fps) )
			{
//				SendMessage( m_hWnd , WM_PAINT , 0 , 0);
				break;
			}

		}
	}
//			printf("quit.3\n");

}
*/




