#include	<iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>

//#include "vec.h"
//#include "gl.h"
#include "bmp.h"
//--
//#include "texture.h"

#include "gram.h"

//------------------------------------------------------------------------------
Gram::~Gram()
//------------------------------------------------------------------------------
{
	free( m_pBuf );
	m_pBuf = 0;
}

//------------------------------------------------------------------------------
Gram::Gram( int width, int height ) // , int type, bool nearest_linear )
//------------------------------------------------------------------------------
{
	memset( this, 0, sizeof(*this) );

//	m_type = type;

	{
		m_width = width;
		m_height = height;

		m_pBuf = (float*)malloc( m_width*m_height*sizeof(float[4]) );

//		int	min = nearest_linear ? GL_LINEAR : GL_NEAREST;
//		int	mag = nearest_linear ? GL_LINEAR : GL_NEAREST;
		
//		m_pTexture = new Texture( GL_TEXTURE_2D, GL_RGBA32F, m_width, m_height, min, mag, GL_REPEAT, GL_REPEAT );

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
void Gram::Clear()
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
void Gram::GetColor( int x, int y, float& r, float& g, float& b )
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
void Gram::FillColor( int x, int y, float* fm, int w, int h )
//------------------------------------------------------------------------------
{
				for ( int i = 0 ; i < h ; i++ )
				{
					int yy = y+i;
					if ( yy >= 0 && yy < m_height ) 
					{

						for ( int j = 0 ; j < w ; j++ )
						{

							int xx = x+j;
							if ( xx >=0 && xx < m_width       ) 
							{

								float*	to = &m_pBuf[ ( m_width*yy + xx ) * 4 ];
								to[0] = *fm++;
								to[1] = *fm++;
								to[2] = *fm++;
								to[3] = *fm++;

							}
							else
							{
								fm+=4;
							}
						}
					}
					else
					{
						fm+=4*w;
					}
				}
	

}

//------------------------------------------------------------------------------
void Gram::PutColor( int x, int y, float r, float g, float b )
//------------------------------------------------------------------------------
{
	if ( x >= 0 && x < m_width && y >= 0 && y < m_height )
	{
//		y = m_height - y-1;

		float*	ptr = &m_pBuf[ ( m_width*y + x ) * 4 ];
		ptr[0] = r;
		ptr[1] = g;
		ptr[2] = b;
		ptr[3] = 1.0;

	}

}
//------------------------------------------------------------------------------
void Gram::Load( float* fm, int w, int h )
//------------------------------------------------------------------------------
{
	float*	to = m_pBuf;

	for ( int y = 0 ; y < m_height ; y++ )
	for ( int x = 0 ; x < m_width ; x++ )
	{
		if ( x < w && y < h )
		{
			to[0] = *fm++;
			to[1] = *fm++;
			to[2] = *fm++;
			to[3] = *fm++;
		}

		to += 4;
	}

}
/*
//------------------------------------------------------------------------------
void Gram::UpdateTexture()
//------------------------------------------------------------------------------
{
	m_pTexture->LoadTexture( m_width, m_height, GL_RGBA, GL_FLOAT, m_pBuf );
}
*/