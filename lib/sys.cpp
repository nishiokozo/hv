#include "sys.h"

#define	USE_DRAW_GDI	1
#define	USE_DRAW_GL_PIX		0
#define	USE_DRAW_GL_TEX		0
#define	USE_GLEW		0

#if	USE_DRAW_GL_PIX||USE_DRAW_GL_TEX
static	HGLRC g_hRC;
#endif

#define	USE_OLD_GL	0
#if USE_OLD_GL
static	HGLRC 		g_hRC;
static	Texture*	g_pTexture;
static	GlFilter*	g_pGlFilter;

#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

static GLuint texName;
#endif

const	static	int		VKBUF_MAX = 256;
		static	int		vkbuf_tbl1[VKBUF_MAX];
		static	int		vkbuf_tbl2[VKBUF_MAX];
			int		vkbuf_cnt;

static	GLuint	g_texture;			// Storage For 3 Textures

static		char	g_vkkeybuf[VKBUF_MAX];

static	BITMAPINFO 	sys_bmpInfo;
static	BYTE * 		sys_pPixel = 0;

//------------------------------------------------------------------------------
void vkbuf_add( int p1, int p2 )
//------------------------------------------------------------------------------
{
	if ( vkbuf_cnt >= VKBUF_MAX-1 ) return;

//	for ( int i = vkbuf_cnt-1 ; i >= 0 ; i-- )
//	{
//		vkbuf_tbl1[i+1] = vkbuf_tbl1[i];
//		vkbuf_tbl2[i+1] = vkbuf_tbl2[i];
//	}
	vkbuf_tbl1[vkbuf_cnt] = p1;
	vkbuf_tbl2[vkbuf_cnt] = p2;
	vkbuf_cnt++;
}

//------------------------------------------------------------------------------
void vkbuf_Clear()
//------------------------------------------------------------------------------
{
	vkbuf_cnt = 0;
	for ( int i = 0 ; i < VKBUF_MAX ; i++ )
	{
		g_vkkeybuf[i] = 0;

		vkbuf_tbl1[i] = 0;
		vkbuf_tbl2[i] = 0;
	}

}
//------------------------------------------------------------------------------
void vkbuf_get( int* p1, int* p2 )
//------------------------------------------------------------------------------
{
	*p1 = 0;
	*p2 = 0;
	if ( vkbuf_cnt <= 0 ) return ;
	(*p1) = vkbuf_tbl1[0];
	(*p2) = vkbuf_tbl2[0];
	for ( int i = 0 ; i < vkbuf_cnt-1 ; i++ )
	{
		vkbuf_tbl1[i] = vkbuf_tbl1[i+1];
		vkbuf_tbl2[i] = vkbuf_tbl2[i+1];
	}
	vkbuf_cnt--;


}




//------------------------------------------------------------------------------
static LRESULT CALLBACK WndProc1
//------------------------------------------------------------------------------
(
	  HWND	hWnd
	, UINT	uMsg
	, WPARAM wParam
	, LPARAM lParam
)
{
	switch( uMsg ) 
	{

	case WM_PAINT:
//		if ( sys_pPixel ) GDI_Paint( hWnd, sys_bmpInfo, sys_pPixel );
		break;

	case WM_KEYUP:
		g_vkkeybuf[wParam] = 0;
		break;

	case WM_KEYDOWN:
		g_vkkeybuf[wParam] = 1;
		vkbuf_add( wParam,
			(((g_vkkeybuf[VK_SHIFT]   ) != 0)<<WIN_SHIFT) | 
			(((g_vkkeybuf[VK_CONTROL] ) != 0)<<WIN_CTRL)  | 
			(((g_vkkeybuf[VK_MENU]    ) != 0)<<WIN_ALT)   | 
			(((GetKeyState(VK_CAPITAL)&0x01)!= 0)<<WIN_CAPS)|
			0 
		);
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	default:
		break;
	}



	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

//-----------------------------------------------------------------------------
int		Sys::Input()
//-----------------------------------------------------------------------------
{
	static	int prev = 0;

				joy0.UpdateJoystick();                             ////c:			sys.joy0.UpdateJoystick();
				key.UpdateKey();                             ////c:			sys.key.UpdateKey();
				if ( key.hi(VK_ESCAPE) ) SendMessage( pWin1->m_hWnd , WM_CLOSE , 0 , 0);                             ////c:			if ( sys.key.hi(VK_ESCAPE) ) SendMessage( sys.pWin1->m_hWnd , WM_CLOSE , 0 , 0);

				int a = key.inkey().ascii;

	prev = m_key_now;
	m_key_now = a;

	m_key_hi = 0;
	if ( prev != a ) m_key_hi = a;
	return m_key_hi;
}
//-----------------------------------------------------------------------------
void	Sys::Sync()
//-----------------------------------------------------------------------------
{

	//---
/*
	LARGE_INTEGER f0;
	LARGE_INTEGER f1;

	// 描画速度計測:start
	QueryPerformanceCounter(&f0);

	{
		{
			extern	BITMAPINFO 	sys_bmpInfo;
			extern	BYTE * 		sys_pPixel;

//					if ( sys_pPixel ) GDI_Draw( pWin1->m_hWnd, sys_pPixel, pWin1->m_buf_w, pWin1->m_buf_h );


		}
	}

	// 描画速度計測:end
	QueryPerformanceCounter(&f1);


	// 描画速度計測:calc
	m_measure_timerPaint += (double)(f1.QuadPart-f0.QuadPart) / (double)m_frequency.QuadPart;
*/

#define	USE_AVERAGE 0

#if USE_AVERAGE
	m_measure_timerPaint1 += m_time_paint_en - m_time_paint_st;
	m_measure_timerPaint2 += m_time_paint_en2 - m_time_paint_st2;
#else
	if ( m_measure_timerPaint1 < m_time_paint_en - m_time_paint_st ) m_measure_timerPaint1 = m_time_paint_en - m_time_paint_st;
	if ( m_measure_timerPaint2 < m_time_paint_en2 - m_time_paint_st2 ) m_measure_timerPaint2 = m_time_paint_en2 - m_time_paint_st2;
#endif

	m_measure_counterPaint++;
	m_measure_timerSec += m_timerFrame;


	// 描画速度計測:disp
	if ( m_ShowFlg && m_measure_timerSec > m_ShowSec )
	{
		char	str[256];
#if USE_AVERAGE
		sprintf( str, "paint ave %5.2fms %5.2fms fps=%f5.2 %s\n"
			, 1000 * (m_measure_timerPaint1) / m_measure_counterPaint
			, 1000 * (m_measure_timerPaint2) / m_measure_counterPaint
#else
		sprintf( str, "paint peak %5.2fms %5.2fms fps=%f5.2 %s\n"
			, 1000 * (m_measure_timerPaint1) 
			, 1000 * (m_measure_timerPaint2) 
#endif
			, (double)m_measure_counterPaint/m_ShowSec
			,	(m_draw_mode == DRAW_GDI)? "GDI":"GL"
		);

		SetWindowText( pWin1->m_hWnd, str );


		m_measure_timerPaint1_prev = m_measure_timerPaint1;
		m_measure_timerPaint2_prev = m_measure_timerPaint2;

		// 描画速度計測:clear
		m_measure_timerSec = 0;
		m_measure_timerPaint1 = 0;
		m_measure_timerPaint2 = 0;
		m_measure_counterPaint = 0;
	}

	//-- wait

	if ( m_Interval == 0 )
	{
		m_timerFrame = 0;  
		while(true)
		{
			QueryPerformanceFrequency(&m_frequency);	// << これがないとなぜか遅くなる。

			static	LARGE_INTEGER tm0;
			static	LARGE_INTEGER tm1;

			QueryPerformanceCounter(&tm1);
			m_timerFrame += (double)(tm1.QuadPart-tm0.QuadPart) / (double)m_frequency.QuadPart;
			QueryPerformanceCounter(&tm0);

			if ( m_timerFrame >= (1.0f/m_Fps) )
			{
//printf("time %f\n", m_timerFrame );
				break;
			}

		}
	}

}

//------------------------------------------------------------------------------
void	Sys::Clear()
//------------------------------------------------------------------------------
{
		pGram->Clear();
//			glClearColor(0.0,0,0,0);
//			glClear( GL_COLOR_BUFFER_BIT );
}
		
//------------------------------------------------------------------------------
void	Sys::Draw()
//------------------------------------------------------------------------------
{
	m_time_paint_st = GetPerformanceCounter();

#if USE_OLD_GL

		g_pTexture->LoadTexture(  (*pWin1).m_buf_w,  (*pWin1).m_buf_h, GL_RGBA, GL_FLOAT, pGram->m_pBuf );
		g_pGlFilter->DrawFilter( g_pTexture );


	{
			HDC WinDC;
			WinDC=GetDC( pWin1->m_hWnd );
   			SwapBuffers(WinDC);
	}

#endif


			switch ( m_draw_mode )
			{
			case DRAW_GL_TEX:
#if	USE_DRAW_GL_TEX
				{
					wglMakeCurrent((*pWin1).m_hDC,g_hRC);
					//	trans
					glBindTexture( GL_TEXTURE_2D, g_texture );
					glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, pGram->m_width , pGram->m_height, 0, GL_RGBA, GL_FLOAT, pGram->m_pBuf);

					//	draw
					glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

				//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
					glBindTexture(GL_TEXTURE_2D, g_texture);

				glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
				glEnd();


					SwapBuffers((*pWin1).m_hDC);
				}
#endif
				break;
			
			case DRAW_GL_PIX:
		#if USE_DRAW_GL_PIX

			#if 1
//				glClearColor(0.0, 0.4, 0.0, 0.0);
//				glClear(GL_COLOR_BUFFER_BIT);

				glPixelZoom(3.0,3.0);
				glDrawPixels( pGram->m_width , pGram->m_height, GL_RGBA, GL_FLOAT, pGram->m_pBuf);
				glFlush();

				{
//					HDC WinDC;
//					WinDC=GetDC((*pWin1).m_hWnd);
//					SwapBuffers(WinDC);
					SwapBuffers((*pWin1).m_hDC);
				}
			#else
			
//				glPixelZoom(3.0,3.0);
//				glDrawPixels(pGram->m_width , pGram->m_height , GL_RGB , GL_FLOAT , pGram->m_pBuf);
//				glFlush();

				{
//					SwapBuffers((*pWin1).m_hDC);
				}
			#endif
		#endif
				break;

			case DRAW_GDI:
		#if USE_DRAW_GDI

					{

						int	i = 0;
						for ( int y = 0 ; y < pGram->m_height; y++)
						for ( int x = 0 ; x < pGram->m_width ; x++)
						{
							float	r = 0;
							float	g = 0;
							float	b = 0;
							pGram->GetColor( x, y, r, g, b );

							(sys_pPixel)[i++] = int(b*255);
							(sys_pPixel)[i++] = int(g*255);
							(sys_pPixel)[i++] = int(r*255);
						}

					}


					if ( sys_pPixel ) GDI_Draw( pWin1->m_hWnd, sys_pPixel, pWin1->m_buf_w, pWin1->m_buf_h );
		#endif
					break;
			}
	m_time_paint_en = GetPerformanceCounter();

			Sync();


			pWin1->Message();

}
//-----------------------------------------------------------------------------
void	Sys::font_Printc( Gram& gram, int qx, int qy, int c )
//-----------------------------------------------------------------------------
{
	int	ox = (     c     &0xf)*8;
	int	oy = ((   (c>>4))&0xf)*8;

	for ( int y = 0 ; y < 8 ; y++ )
	for ( int x = 0 ; x < 8 ; x++ )
	{
		int	idx = ((oy+y)*m_pFontBmp->m_width + ox + x)*4;
		float r = m_pFontBmp->m_pBuf[ idx + 0 ];
		float g = m_pFontBmp->m_pBuf[ idx + 1 ];
		float b = m_pFontBmp->m_pBuf[ idx + 2 ];

		int	py  = (qy*8+  y);
		int	px  =  qx*8+  x;

		gram.PutColor( px, py, r, g, b );
	}

}

//------------------------------------------------------------------------------
void Sys::PrintHex( int lx, int ly, int val )
//------------------------------------------------------------------------------
{
		char	str[256];
		sprintf( str, "%x", val );

		for ( int i=0 ; i < (signed)strlen( str ) ; i++ )
		{
			int a = str[i];
			m_scrn_buf[ly*m_scrn_W + lx + i] = a;
		}
}

//static	HGLRC	m_win1_hGLRC;
//------------------------------------------------------------------------------
Sys::~Sys()
//------------------------------------------------------------------------------
{
//	Gl::DisableOpenGL( (*pWin1).m_hWnd, &m_win1_hGLRC );
//	Gl::DisableOpenGL( (*pWin2).m_hWnd, &m_win2_hGLRC );

//			printf("~Sys.1\n");

#if USE_DRAW_GL_PIX||USE_DRAW_GL_TEX
		{
//			HDC WinDC;
//			WinDC=GetDC((*pWin1).m_hWnd);

			wglMakeCurrent((*pWin1).m_hDC, 0);
			wglDeleteContext(g_hRC);

			PostQuitMessage(0);
		}
#endif

#if USE_OLD_GL
	if ( g_pTexture ) delete g_pTexture;
 	if ( g_pGlFilter ) delete	g_pGlFilter;
#endif



	(*pWin1).CloseWin();
//	(*pWin2).CloseWin();
//			printf("~Sys.2\n");


	if ( pGram ) delete	pGram;
//	if ( m_pGlFont ) delete	m_pGlFont;
	if ( m_scrn_buf )delete[] m_scrn_buf;

/*
	if ( m_pTexColor ) delete	m_pTexColor;
			printf("~Sys.3\n");


*/
}
//------------------------------------------------------------------------------
Sys::Sys( const char* fn )  : joy0(0),  joy1(1)// , win("sys1"), win2("sys2")
//------------------------------------------------------------------------------
{
			QueryPerformanceFrequency(&m_frequency);	// << これがないとなぜか遅くなる。

	m_time_paint_st = 0;
	m_time_paint_en = 0;

	pWin1 = new Win("sys1", WndProc1);
//	pWin2 = new Win("sys2", WndProc2);



	for ( int i = 0 ; i < VKBUF_MAX ; i++ )
	{
		g_vkkeybuf[i] = 0;

		vkbuf_tbl1[i] = 0;
		vkbuf_tbl2[i] = 0;
	}
	vkbuf_cnt = 0;

	if ( fn )
	{
		env.Load( fn );
	}
	else
	{
		printf("error env file not found [%s]\n", fn );
		exit(0);
	}


//	pWin = Win("win1", WndProc );

	m_draw_mode = DRAW_GDI;
	if ( strcmp( env.GetString("DrawMode").c_str(), "GL_PIX" ) == 0 ) m_draw_mode = DRAW_GL_PIX;
	if ( strcmp( env.GetString("DrawMode").c_str(), "GL_TEX" ) == 0 ) m_draw_mode = DRAW_GL_TEX;
	


	(*pWin1).OpenWin( 
		env.GetInt("win_x"),
		env.GetInt("win_y"),
		env.GetInt("win_w"),
		env.GetInt("win_h"),
		env.GetInt("buf_w"),
		env.GetInt("buf_h"),
		(env.GetString("name") + ":" + string(__DATE__) ).c_str() 
	);

/*
	(*pWin2).OpenWin( 
		env.GetInt("2.win_x"),
		env.GetInt("2.win_y"),
		env.GetInt("2.win_w"),
		env.GetInt("2.win_h"),
		env.GetInt("2.buf_w"),
		env.GetInt("2.buf_h"),
		(env.GetString("name") + ":" + string(__DATE__) ).c_str() 
	);
*/

	m_keyCloseHi = (env.GetInt("KeyClose")>>8)&0xff;
	m_keyCloseLo =  env.GetInt("KeyClose")    &0xff;

	sound.SetVolume( env.GetFloat("SoundVolume") );

	m_scrn_W	= (*pWin1).m_buf_w/8;
	m_scrn_H	= (*pWin1).m_buf_h/8;
	m_scrn_buf	= new char[ m_scrn_W*m_scrn_H *10];


		for ( int h = 0 ; h < m_scrn_H ; h++ )
		{
			for ( int w = 0 ; w < m_scrn_W ; w++ )
			{
				m_scrn_buf[h*m_scrn_W + w] = ' ';
			}
		}


	key.SetRepatTime( env.GetInt("Keyrepeat1"), env.GetInt("Keyrepeat2"));

	(*pWin1).m_Interval	= env.GetInt("Interval");
	(*pWin1).m_Fps		= env.GetFloat("Fps");
	(*pWin1).m_ShowFlg	= env.GetInt("ShowFlg");
	(*pWin1).m_ShowSec	= env.GetFloat("ShowSec");

	m_Interval	= env.GetInt("Interval");
	m_Fps		= env.GetFloat("Fps");
	m_ShowFlg	= env.GetInt("ShowFlg");
	m_ShowSec	= env.GetFloat("ShowSec");

//	(*pWin2).m_Interval	= env.GetInt("Interval");
//	(*pWin2).m_Fps		= env.GetFloat("Fps");
//	(*pWin2).m_ShowFlg	= env.GetInt("ShowFlg");
//	(*pWin2).m_ShowSec	= env.GetFloat("ShowSec");


#if USE_DRAW_GL_PIX||USE_DRAW_GL_TEX
	{
		HDC WinDC;
//		WinDC=GetDC((*pWin1).m_hWnd);

		int pixelFormat;
		PIXELFORMATDESCRIPTOR pfd = 
		{ 
			sizeof(PIXELFORMATDESCRIPTOR)   // size of this pfd 
			,1                     // version number 
			,PFD_DRAW_TO_WINDOW    // support window 
			|PFD_SUPPORT_OPENGL    // support OpenGL 
			|PFD_DOUBLEBUFFER      // double buffered 
			,PFD_TYPE_RGBA          // RGBA type 
			,24                    // 24-bit color depth 
			,0, 0, 0, 0, 0, 0      // color bits ignored 
			,0                     // no alpha buffer 
			,0                     // shift bit ignored 
			,0                     // no accumulation buffer 
			,0, 0, 0, 0            // accum bits ignored 
			,32                    // 32-bit z-buffer 
			,0                     // no stencil buffer 
			,0                     // no auxiliary buffer 
			,PFD_MAIN_PLANE        // main layer 
			,0                     // reserved 
			,0, 0, 0                // layer masks ignored 
		}; 
		pixelFormat = ChoosePixelFormat((*pWin1).m_hDC,&pfd);
		SetPixelFormat((*pWin1).m_hDC,pixelFormat,&pfd);

		g_hRC=wglCreateContext((*pWin1).m_hDC);
//		wglMakeCurrent((*pWin1).m_hDC,g_hRC);
	}


		wglMakeCurrent((*pWin1).m_hDC,g_hRC);
	#if USE_GLEW
	{
		int err = glewInit();
		if (err != GLEW_OK)
		{
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
	}

//	printf( "GL_SHADING_LANGUAGE_VERSION:%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION) );
	wglSwapIntervalEXT(0);

	glGenTextures(1, &g_texture);					// Create Three Textures
	glBindTexture(GL_TEXTURE_2D, g_texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	#endif


#endif

	//----
#if USE_OLD_GL
	
	Gl::EnableOpenGL( (*pWin1).m_hWnd, (*pWin1).m_hDC, &g_hRC );
	g_pGlFilter	= new GlFilter( env.GetString("filter").c_str() );


		{
			int w = (*pWin1).m_buf_w;
			int h = (*pWin1).m_buf_h;
			g_pTexture = new Texture( GL_TEXTURE_2D, GL_RGBA32F, w, h, GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT );
//			g_pTexture = new Texture( "font.bmp" );

		}

#endif
	//----

//	Gl::EnableOpenGL( (*pWin1).m_hWnd, (*pWin1).m_hDC, &m_win1_hGLRC );
//	Gl::EnableOpenGL( (*pWin2).m_hWnd, (*pWin2).m_hDC, &m_win2_hGLRC );
//	Gl::MakeCuttent( (*pWin1).m_hDC, m_win1_hGLRC );

//	pGram	= new Gram( (*pWin1).m_buf_w, (*pWin1).m_buf_h, GL_RGBA32F, false );

/*
	m_pGlFont		= new GlFont( 
		env.GetString("FontTexture").c_str() ,
		env.GetString("FontShader").c_str() ,
		env.GetInt("buf_w"),
		env.GetInt("buf_h")
	);
*/
	m_pFontBmp = new Bmp(env.GetString("FontTexture").c_str());


	pGram	= new Gram( (*pWin1).m_buf_w, (*pWin1).m_buf_h );


//	wglSwapIntervalEXT( env.GetInt("Interval") );


#if 1
	{
		sys_pPixel = 0;
		memset(&sys_bmpInfo, 0, sizeof(BITMAPINFOHEADER) );

		int w = env.GetInt("buf_w");
		int h = env.GetInt("buf_h");


//		GDI_CreateBmp( &sys_pPixel, sys_bmpInfo,  w,  h );
		sys_pPixel = (BYTE *) malloc (w*h*24/8);

	}
//	if ( sys.key.hi('G') )

#endif



	(*pWin1).ShowWin();
//	(*pWin2).ShowWin();

};
//------------------------------------------------------------------------------
double	Sys::GetPerformanceCounter()
//------------------------------------------------------------------------------
{
	LARGE_INTEGER	f;
	QueryPerformanceCounter(&f);

	if ( (*pWin1).m_frequency.QuadPart == 0 ) return 0;
	return  (double)(f.QuadPart) / (double)(*pWin1).m_frequency.QuadPart;
}


#if 0
//------------------------------------------------------------------------------
void	Sys::SetRendertexture( Texture* pTexColor )
//------------------------------------------------------------------------------
{

//		if ( pTexColor )
//		{
//			glBindFramebuffer(GL_FRAMEBUFFER, m_hdlFbo);
//			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pTexColor->m_hdl, 0/*mipmap level*/);
//			glViewport(0,0, m_pTexColor->m_width, m_pTexColor->m_height );
//
//		}
//		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0 );
			glViewport(0,0, (*pWin1).m_w, (*pWin1).m_h );
		}
}
#endif

#if 0
//------------------------------------------------------------------------------
void	 Sys::SwapBuffer()
//------------------------------------------------------------------------------
{

//	移動	書込	補正		表示
//	入力
//	move	exec	collition	draw
//	update						paint
//	input	update	normalize
//	calc
//	draw
//	request			exec
//	order

	{

		//	escape




		//	joystick

		joy0.UpdateJoystick();
		joy1.UpdateJoystick();

		//	mouse

		mouse.UpdateMouse( (*pWin1).m_x, (*pWin1).m_y, (*pWin1).m_w, (*pWin1).m_h );

		//	camera

//		camera.UpdateCamera();

		//	keyboard

		key.UpdateKey();

		//	graphics

//		gra.UpdateGra();


		//	bitmap

//		pGram->UpdateTexture();
//		m_pGlFilter->DrawFilter( pGram->m_pTexture );


/*
		//font
		for ( int h = 0 ; h < m_scrn_H ; h++ )
		{
			for ( int w = 0 ; w < m_scrn_W ; w++ )
			{
				m_pGlFont->Printc( w, h, m_scrn_buf[h*m_scrn_W + w] );
			}
		}
*/


//		SetRendertexture( 0 );

//		m_pGlFilter->DrawFilter( m_pTexColor );

//		SetRendertexture( m_pTexColor );

	}
	

		if( key.hi(m_keyCloseLo) && key.now( m_keyCloseHi ) )
		{
			SendMessage((*pWin1).m_hWnd , WM_CLOSE , 0 , 0);
			
		}
			if ( pWin1->Message()  )
			{
				pWin1->SwapBuffer();
			}

}
#endif
