#include	<iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>

#include "vec.h"
#include "gl.h"
#include "bmp.h"
//--
#include "texture.h"

#include "glfont.h"


//-----------------------------------------------------------------------------
GlFont::~GlFont()
//-----------------------------------------------------------------------------
{
}

//-----------------------------------------------------------------------------
GlFont::GlFont( const char *fnFont, const char *fnShader, int scrnw, int scrnh )
//-----------------------------------------------------------------------------
{
	int	w = scrnw * FW;
	int	h = scrnh * FH;


	m_ScrnW = scrnw;
	m_ScrnH = scrnh;
	//	fontTexture

	m_pTexFont = new Texture( fnFont );


	//	font model

	{
		static const float sx = 2*(float)FW / (float)scrnw;
		static const float sy = 2*(float)FH / (float)scrnh;
		float	tblVertex[] =
		{
			 0	,  0,	0.0f,
			 sx	,  0,	0.0f,
			 sx	,  sy,	0.0f,
			 0	,  sy,	0.0f,
		};
		Gl::CreateBuffer( &m_hdlVertex_Position, GL_ARRAY_BUFFER, sizeof(tblVertex), tblVertex );
	}

	{
		static const float w = 1.0f/16.0f;
		static const float h = 1.0f/16.0f;
		float	tblUv[] =
		{
			 0.0f,  0.0f,
			 w,  	0.0f,
			 w,  	h,
			 0.0f,  h,
		};
		Gl::CreateBuffer( &m_hdlVertex_Uv, GL_ARRAY_BUFFER, 	 sizeof(tblUv), tblUv );
	}

	{
		int	tblIndex[] =	{		0,2,1,		2,3,0,	};
		Gl::CreateBuffer( &m_hdlVertex_Index, GL_ELEMENT_ARRAY_BUFFER, sizeof(tblIndex), tblIndex );
		m_cntIndex = sizeof(tblIndex)/sizeof(int);
	}
	Gl::shader_LoadFile( &m_hdlProgram, fnShader );

	//	for streach texture
	m_hdl_Position	= glGetAttribLocation( m_hdlProgram, "Position");
	m_hdl_Uv		= glGetAttribLocation( m_hdlProgram, "Uv");
	m_hdl_Tex0		= glGetUniformLocation( m_hdlProgram, "Tex0");
	m_hdl_Ofs		= glGetUniformLocation( m_hdlProgram, "Ofs");
	m_hdl_Pos		= glGetUniformLocation( m_hdlProgram, "Pos");
	m_hdl_Col		= glGetUniformLocation( m_hdlProgram, "Col");


	m_col[0] = 1.0;
	m_col[1] = 1.0;
	m_col[2] = 1.0;
	m_col[3] = 1.0;

}

//------------------------------------------------------------------------------
void GlFont::Color( float r, float g, float b )
//------------------------------------------------------------------------------
{
	m_col[0] = r;
	m_col[1] = g;
	m_col[2] = b;
	m_col[3] = 1.0;

}
//------------------------------------------------------------------------------
void GlFont::Printc( int x, int y, const char c )
//------------------------------------------------------------------------------
{
	glUseProgram( m_hdlProgram );
	Gl::SetBuffer( m_hdl_Position, m_hdlVertex_Position, GL_ARRAY_BUFFER, 3, GL_FLOAT );
	Gl::SetBuffer( m_hdl_Uv, m_hdlVertex_Uv,  GL_ARRAY_BUFFER, 2, GL_FLOAT );
	Gl::SetTexture( GL_TEXTURE_2D, m_hdl_Tex0, 0, m_pTexFont->m_hdl );
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hdlVertex_Index );


	{
		float	ofs[2] = {0,0};
		int	ox = c&0xf;
		int	oy = c>>4;
		ofs[0] =        ox * 1.0f/16.0f;
		ofs[1] = 1.0f - oy * 1.0f/16.0f - 1.0f/16.0f;
		glUniform2fv( m_hdl_Ofs, 1, ofs );
	}

	{
		float	pos[2] = {1.0f-(x*FW)*2.0f/m_ScrnW, (y*FH+FH)*2.0f/m_ScrnH-1.0f};
		glUniform2fv( m_hdl_Pos, 1, pos );
	}

	{
		glUniform4fv( m_hdl_Col, 1, m_col );
	}

	glDrawElements( GL_TRIANGLE_STRIP, m_cntIndex, GL_UNSIGNED_INT, 0 );

	glUseProgram( 0 );
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0 );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glDisableVertexAttribArray( m_hdl_Position );
	glDisableVertexAttribArray( m_hdl_Uv );


}
