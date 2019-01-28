#include	<iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>
#undef APIENTRY
#include <GL/glew.h>
#undef GLEWAPI
#include <GL/wglew.h>
//  #include <AL/al.h>
//  #include <AL/alut.h>

#include "vec.h"
#include "gl.h"
#include "bmp.h"

#include "texture.h"



//-----------------------------------------------------------------------------
Texture::Texture( int target, int format, int width, int height, int min, int mag, int wraps, int wrapt )
//-----------------------------------------------------------------------------
{
	CreateTexture( target, format, width, height, min, mag, wraps, wrapt );
}

//-----------------------------------------------------------------------------
Texture::Texture( const char* fname )
//-----------------------------------------------------------------------------
{
	Bmp	bmp( fname );

	CreateTexture( GL_TEXTURE_2D, GL_RGBA, bmp.m_width, bmp.m_height, GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT );
//	Gl::LoadTexture( m_target, m_hdl, m_format, bmp.m_width, bmp.m_height, GL_RGBA, GL_UNSIGNED_BYTE, bmp.m_pBuf );
	Gl::TexSubImage2D( m_target, 0, m_hdl, m_format, 0, 0, bmp.m_width, bmp.m_height, GL_RGBA, GL_UNSIGNED_BYTE, bmp.m_pBuf );

//GL_UNSIGNED_INT_8_8_8_8_REV
//GL_UNSIGNED_INT_8_8_8_8
//GL_UNSIGNED_BYTE

}

/*
//-----------------------------------------------------------------------------
void Texture::ClearTexture()
//-----------------------------------------------------------------------------
{
	float	buf[] = {1.0,1.0,1.0,1.0};
//	Gl::LoadTexture( m_target, m_hdl, m_format, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, buf );

	int 	target		= m_target; 
	GLuint 	hdl_Texture = m_hdl; 
	int 	innerformat = m_format; 
	int 	width 		= 1; 
	int 	height 		= 1; 
	int 	format 		= GL_RGBA; 
	int 	type		= GL_FLOAT; 
	void*	pBuf		= buf;
	{
		int	x0 = 0;
		int	y0 = 0;
		glBindTexture( target, hdl_Texture );
	//	glTexImage2D( target, 0, innerformat, width, height, 0, format, type, pBuf );
		glTexSubImage2D( target, 0, 0,0, 1, 1, format, type, pBuf );
		glBindTexture( target, 0 );
	}

}
*/
//-----------------------------------------------------------------------------
void Texture::CreateTexture( int target, int format, int width, int height, int min, int mag, int wraps, int wrapt )
//-----------------------------------------------------------------------------
{
	m_target = target;
	m_format = format;
	m_width = width;
	m_height = height;
	m_min = min;
	m_mag = mag;
	m_wraps = wraps;
	m_wrapt = wrapt;

	Gl::CreateTexture( &m_hdl, m_target, m_format, m_width, m_height, m_min, m_mag, m_wraps, m_wrapt );
}
//-----------------------------------------------------------------------------
void Texture::LoadTexture( int width, int height, int format, int type, void* pBuf )
//-----------------------------------------------------------------------------
{

	Gl::TexSubImage2D( m_target, 0, m_hdl, m_format, 0, 0, width, height, format, type, pBuf );
}
