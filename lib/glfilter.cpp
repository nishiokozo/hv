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
//--
#include "texture.h"

#include "glfilter.h"

#define	_line	printf("--%s(%d)\n",__FILE__,__LINE__)
//------------------------------------------------------------------------------
GlFilter::~GlFilter()
//------------------------------------------------------------------------------
{
}
//------------------------------------------------------------------------------
GlFilter::GlFilter( const char* fnShader )
//------------------------------------------------------------------------------
{

	float	tblVertex[] =
	{
		-1.0f, -1.0f,	0.0f,
		 1.0f, -1.0f,	0.0f,
		 1.0f,  1.0f,	0.0f,
		-1.0f,  1.0f,	0.0f,
	};
	Gl::CreateBuffer( &m_hdlVertex_Position, GL_ARRAY_BUFFER, sizeof(tblVertex), tblVertex );
	int	tblIndex[] =	{		0,2,1,		2,3,0,	};
	Gl::CreateBuffer( &m_hdlVertex_Index, GL_ELEMENT_ARRAY_BUFFER, sizeof(tblIndex), tblIndex );
	m_cntIndex = sizeof(tblIndex)/sizeof(int);
	Gl::shader_LoadFile( &m_hdlProgram, fnShader );

	{
		float	tblUv[] =
		{
			 0.0f,  0.0f,
			 1.0f,  0.0f,
			 1.0f,  1.0f,
			 0.0f,  1.0f,
		};
		Gl::CreateBuffer( &m_hdlVertex_Uv, GL_ARRAY_BUFFER, 	 sizeof(tblUv), tblUv );
	}

	//	for streach texture
	m_hdl_Position		= glGetAttribLocation( m_hdlProgram, "Position");
	m_hdl_Tex0			= glGetUniformLocation( m_hdlProgram, "Tex0");
	m_hdl_Uv			= glGetAttribLocation( m_hdlProgram, "Uv");

}

//------------------------------------------------------------------------------
void GlFilter::DrawFilterTexture( Texture* pTex )
//------------------------------------------------------------------------------
{
	glUseProgram( m_hdlProgram );
	Gl::SetBuffer( m_hdl_Position, m_hdlVertex_Position, GL_ARRAY_BUFFER, 3, GL_FLOAT );
	Gl::SetBuffer( m_hdl_Uv, m_hdlVertex_Uv,  GL_ARRAY_BUFFER, 2, GL_FLOAT );
	if ( pTex ) Gl::SetTexture( GL_TEXTURE_2D, m_hdl_Tex0, 0, pTex->m_hdl );
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hdlVertex_Index );

	glDrawElements( GL_TRIANGLE_STRIP, m_cntIndex, GL_UNSIGNED_INT, 0 );

	glUseProgram( 0 );
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0 );
	if ( pTex ) glBindTexture( GL_TEXTURE_2D, 0 );
	glDisableVertexAttribArray( m_hdl_Position );
	glDisableVertexAttribArray( m_hdl_Uv );


}
