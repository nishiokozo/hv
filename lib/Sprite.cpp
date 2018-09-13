#include	<iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>
//  #include <AL/al.h>
//  #include <AL/alut.h>

#include "vec.h"
#include "gl.h"
#include "bmp.h"


//------------------------------------------------------------------------------
Sprite::~Sprite()
//------------------------------------------------------------------------------
{
}
//------------------------------------------------------------------------------
Sprite::Sprite( const char* fnShader )
//------------------------------------------------------------------------------
{
	float	tblVertex[] =
	{
		-0.5f, -0.5f,	0.0f,
		 0.5f, -0.5f,	0.0f,
		 0.5f,  0.5f,	0.0f,
		-0.5f,  0.5f,	0.0f,
	};
	Gl::CreateBuffer( &m_hdlVertex_Position, GL_ARRAY_BUFFER, sizeof(tblVertex), tblVertex );
	int	tblIndex[] =	{		0,2,1,		2,3,0,	};
	Gl::CreateBuffer( &m_hdlVertex_Index, GL_ELEMENT_ARRAY_BUFFER, sizeof(tblIndex), tblIndex );
	m_cntIndex = sizeof(tblIndex)/sizeof(int);
	Gl::shader_LoadFile( &m_hdlProgram, fnShader );

	//	for streach texture
	m_hdl_Position		= glGetAttribLocation( m_hdlProgram, "Position");
	m_hdl_Tex0			= glGetUniformLocation( m_hdlProgram, "Tex0");

}

//------------------------------------------------------------------------------
void Sprite::DrawFilter( int hdlTex )
//------------------------------------------------------------------------------
{
	glUseProgram( m_hdlProgram );

	glEnableVertexAttribArray( 0 );

	Gl::SetBuffer( m_hdl_Position, m_hdlVertex_Position, GL_ARRAY_BUFFER, 3, GL_FLOAT );
	Gl::SetTexture( GL_TEXTURE_2D, m_hdl_Tex0, 0, hdlTex );

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hdlVertex_Index );
	glDrawElements( GL_TRIANGLE_STRIP, m_cntIndex, GL_UNSIGNED_INT, 0 );

	glDisableVertexAttribArray( 0 );
}

