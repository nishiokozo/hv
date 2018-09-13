#include	<iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>

#include "lib/vec.h"
#include "shape.h"
#include "shader.h"
#include "lib/gl.h"

//------------------------------------------------------------------------------
Shader::Shader( const char* fn )
//------------------------------------------------------------------------------
{
	Gl::shader_LoadFile( &m_hdlProgram, fn );

	m_hdl_buf_Position			= glGetAttribLocation( m_hdlProgram, "Position");
	m_hdl_Uv					= glGetAttribLocation( m_hdlProgram, "Uv");
	m_hdl_bufer_Normal			= glGetAttribLocation( m_hdlProgram, "Normal");
	m_hdl_var_Projection		= glGetUniformLocation( m_hdlProgram, "Projection");
	m_hdl_var_Model				= glGetUniformLocation( m_hdlProgram, "matModel");
	m_hdl_var_View				= glGetUniformLocation( m_hdlProgram, "matView");
	m_hdl_var_ColModel			= glGetUniformLocation( m_hdlProgram, "colModel");
	m_hdl_var_PosEye			= glGetUniformLocation( m_hdlProgram, "posEye");
	m_hdl_var_VecEye			= glGetUniformLocation( m_hdlProgram, "vecEye");

}


//------------------------------------------------------------------------------
void Shader::DrawShape( const Shape& shape, const mat4& matModel, const mat4& matView, const mat4& matProj, const vec3& color, const vec3& posEye, const vec3& vecEye )
//------------------------------------------------------------------------------
{

	glUseProgram( m_hdlProgram );


	glUniform3f( m_hdl_var_ColModel, color.r, color.g, color.b );
	glUniform3f( m_hdl_var_PosEye, posEye.x, posEye.y, posEye.z );
	glUniform3f( m_hdl_var_VecEye, vecEye.x, vecEye.y, vecEye.z );


	glUniformMatrix4fv( m_hdl_var_Model,      1, GL_TRUE, matModel.m_array );
	glUniformMatrix4fv( m_hdl_var_View,       1, GL_TRUE, matView.m_array );
	glUniformMatrix4fv( m_hdl_var_Projection, 1, GL_TRUE, matProj.m_array );

	glEnableVertexAttribArray( m_hdl_buf_Position );
	glBindBuffer(GL_ARRAY_BUFFER, shape.m_hdlVertex_Position  );
	glVertexAttribPointer( m_hdl_buf_Position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray( m_hdl_bufer_Normal );
	glBindBuffer(GL_ARRAY_BUFFER, shape.m_hdlVertex_Normal  );
	glVertexAttribPointer( m_hdl_bufer_Normal, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape.m_hdlVertex_Index );
	glDrawElements( GL_TRIANGLE_STRIP, shape.m_cntIndex, GL_UNSIGNED_INT, 0 );

	glUseProgram( 0 );

}

