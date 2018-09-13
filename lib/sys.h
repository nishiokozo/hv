#include	<iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>

//--
#include <vec.h>
#include <gl.h>
#include <bmp.h>
//--
#include <texture.h>
#include <win.h>
//--
#include <joystick.h>
#include <mouse.h>
#include <key.h>
//#include <math.h>
#include <camera.h>
#include <gra.h>
#include <file.h>
#include <env.h>
#include <glfilter.h>
#include <glbitmap.h>
#include <glfont.h>
#include <sound.h>
#include <gdi.h>
#include <gram.h>

#define	_line	printf("--%s(%d)\n",__FILE__,__LINE__)
#define	RAD(n)	((n)*M_PI/180.0f)
#define	SYS_PRINT_FPS(s) \
		{\
			static	LARGE_INTEGER tm0,tm1;\
			LARGE_INTEGER frequency; \
			QueryPerformanceFrequency(&frequency);\
			QueryPerformanceCounter(&tm1);\
			printf("%s %f\n", s, (double)(tm1.QuadPart-tm0.QuadPart) / (double)frequency.QuadPart);\
			QueryPerformanceCounter(&tm0);\
		}
//extern	BITMAPINFO 	sys_bmpInfo;
//extern	BYTE * 		sys_pPixel;


////////////////////////////////////////////////////////////////////////////////
class Sys
////////////////////////////////////////////////////////////////////////////////
{
public:
	Joystick	joy0;
	Joystick	joy1;
	Mouse		mouse;
	Key			key;
//	Camera		camera;
//	Gra			gra;
	Env			env;

	Sound		sound;
//	Win			win;
//	Win			win2;
	Win*			pWin1;
//	Win*			pWin2;

	BITMAPINFO gdi_bmpInfo;
	BYTE * 		gdi_pPixel;

//	HDC		m_win1_hDC;
//	HGLRC	m_win1_hGLRC;
//	HDC		m_win2_hDC;
//	HGLRC	m_win2_hGLRC;


//	GLuint		m_hdlFbo;
//	Texture*	m_pTexColor;

 //	GlFilter*		m_pGlFilter;
//	GlBitmap*		m_pGlBitmap;
//	GlFont*			m_pGlFont;
	Gram*		pGram;

	Bmp*		m_pFontBmp;


	double	m_SoundVolume;

	int		m_keyCloseHi;
	int		m_keyCloseLo;

	int		m_scrn_W;
	int		m_scrn_H;
	char*	m_scrn_buf;



	int			m_Interval;
	double		m_Fps;
	bool		m_ShowFlg;
	double		m_ShowSec;

	LARGE_INTEGER m_frequency; 
	double		m_timerFrame;
	double		m_measure_timerSec;
	double		m_measure_timerPaint1_prev;
	double		m_measure_timerPaint1;
	double		m_measure_timerPaint2_prev;
	double		m_measure_timerPaint2;
	uint64_t	m_measure_counterPaint;

	double		m_time_paint_st;
	double		m_time_paint_en;
	double		m_time_paint_st2;
	double		m_time_paint_en2;
	


	~Sys();
	Sys( const char* fn );

	void	Sync();
	bool	Message();
	void	 SwapBuffer();

//	void SetRendertexture( Texture* pTexColor );

	void	Clear();
	void	Draw();

	void	scrn_Clear();
	void	scrn_Decode( int line, int cx, int cy );

	void PrintHex( int lx, int ly, int val );


	double	GetPerformanceCounter();

	void	font_Printc( Gram& gram, int qx, int qy, int c );

	int	m_key_now;
	int	m_key_hi;
	int		Input();

	enum
	{
		DRAW_GDI,
		DRAW_GL_PIX,
		DRAW_GL_TEX,
	} m_draw_mode;
	

	void InitGL();

};


