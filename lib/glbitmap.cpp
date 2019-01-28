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

#include "vec.h"
#include "gl.h"
#include "bmp.h"
//--
#include "texture.h"

#include "glbitmap.h"

#define	_line	printf("--%s(%d)\n",__FILE__,__LINE__)

//------------------------------------------------------------------------------
GlBitmap::~GlBitmap()
//------------------------------------------------------------------------------
{
	free( m_pBuf );
	m_pBuf = 0;
}

//------------------------------------------------------------------------------
GlBitmap::GlBitmap( int width, int height, int type, bool nearest_linear )
//------------------------------------------------------------------------------
{
	memset( this, 0, sizeof(*this) );

	m_type = type;

	{
		m_width = width;
		m_height = height;

		m_pBuf = (float*)malloc( m_width*m_height*sizeof(float[4])*2 );

		int	min = nearest_linear ? GL_LINEAR : GL_NEAREST;
		int	mag = nearest_linear ? GL_LINEAR : GL_NEAREST;
		
		m_pTexture = new Texture( GL_TEXTURE_2D, GL_RGBA32F, m_width, m_height, min, mag, GL_REPEAT, GL_REPEAT );

	}


	for( int py = 0 ; py < m_height ; py++ )
	{
		for( int px = 0 ; px < m_width ; px++ )
		{
			PutColor( px, py,  0,0,0);

		}
	}

}

//------------------------------------------------------------------------------
void GlBitmap::Clear()
//------------------------------------------------------------------------------
{
	for ( int y = 0 ; y < m_height ; y++ )
		for ( int x = 0 ; x < m_width ;x++ )
		{
//			int h = m_height - y-1;
			float*	ptr = &m_pBuf[ ( m_width*y + x ) * 4 ];
			ptr[0] = 0;
			ptr[1] = 0;
			ptr[2] = 0;
			ptr[3] = 0;
		}
}
//------------------------------------------------------------------------------
void GlBitmap::GetColor( int x, int y, float& r, float& g, float& b )
//------------------------------------------------------------------------------
{
	if ( x >= 0 && x < m_width && y >= 0 && y < m_height )
	{
		y = m_height - y-1;

		float*	ptr = &m_pBuf[ ( m_width*y + x ) * 4 ];
		r = ptr[0];
		g = ptr[1];
		b = ptr[2];

	}

}

//------------------------------------------------------------------------------
void GlBitmap::PutColor( int x, int y, float r, float g, float b )
//------------------------------------------------------------------------------
{
	if ( x >= 0 && x < m_width && y >= 0 && y < m_height )
	{
		y = m_height - y-1;

		float*	ptr = &m_pBuf[ ( m_width*y + x ) * 4 ];
		ptr[0] = r;
		ptr[1] = g;
		ptr[2] = b;
		ptr[3] = 1.0;

	}

}

//------------------------------------------------------------------------------
void GlBitmap::UpdateTexture()
//------------------------------------------------------------------------------
{
	m_pTexture->LoadTexture( m_width, m_height, GL_RGBA, GL_FLOAT, m_pBuf );
}
