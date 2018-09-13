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
#include "gra.h"

//------------------------------------------------------------------------------
Gra::Gra()
//------------------------------------------------------------------------------
{
	m_cntLines = 0;

	for ( int i = 0 ; i < m_MAX_LINES ; i++ )
	{
		m_tblIndex[i] = i;
	}
}
//------------------------------------------------------------------------------
void Gra::Init( const char* fnShader )
//------------------------------------------------------------------------------
{


	Gl::CreateBuffer( &m_hdlVertex_Index, GL_ELEMENT_ARRAY_BUFFER, sizeof(m_tblIndex), m_tblIndex );

	m_cntIndex = sizeof(m_tblIndex)/sizeof(int);


	Gl::CreateBuffer( &m_hdlVertex_Position, GL_ELEMENT_ARRAY_BUFFER, sizeof(m_tblPosition), m_tblPosition );

	Gl::shader_LoadFile( &m_hdlProgram, fnShader );

	m_hdl_Position	= glGetAttribLocation( m_hdlProgram, "Position");

}

//------------------------------------------------------------------------------
void Gra::Line( vec2 s, vec2 e )
//------------------------------------------------------------------------------
{
	if( m_cntLines < m_MAX_LINES )
	{
		int	n=m_cntLines++;
		m_tblPosition[n].s = s;
		m_tblPosition[n].e = e;
	}
}

//------------------------------------------------------------------------------
void Gra::UpdateGra()
//------------------------------------------------------------------------------
{

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_hdlVertex_Position );
	glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, 0,  sizeof(m_ModelLine)*m_cntLines, m_tblPosition );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );


	m_cntLines = 0;
	
	glUseProgram( m_hdlProgram );

	glEnableVertexAttribArray( 0 );

	Gl::SetBuffer( m_hdl_Position, m_hdlVertex_Position, GL_ARRAY_BUFFER, 2, GL_FLOAT );

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hdlVertex_Index );
	glDrawElements( GL_LINES, m_cntIndex, GL_UNSIGNED_INT, 0 );

	glDisableVertexAttribArray( 0 );

}


