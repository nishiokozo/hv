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

#include "gl.h"
#include "bmp.h"


#include "file.h"

//------------------------------------------------------------------------------
void	Gl::MakeCuttent( HDC hDC, HGLRC hGLRC )
//------------------------------------------------------------------------------
{
	wglMakeCurrent( hDC, hGLRC );
}
//------------------------------------------------------------------------------
void Gl::EnableOpenGL(HWND hWnd, HDC hDC, HGLRC * hGLRC)
//------------------------------------------------------------------------------
{

	PIXELFORMATDESCRIPTOR pfd;
	int format;
	
	// get the device context (DC)
//	hDC = GetDC( hWnd );
	
	// set the pixel format for the DC
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat( hDC, &pfd );
	SetPixelFormat( hDC, format, &pfd );
	
	// create and enable the render context (RC)
	*hGLRC = wglCreateContext( hDC );

	wglMakeCurrent( hDC, *hGLRC );

		printf( "GL_VERSION                 :%s\n", glGetString(GL_VERSION) );

	// GLEW初期化
//	if (g_initializedGL == false )
	{

		int err = glewInit();
		if (err != GLEW_OK)
		{
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
	}


		//	version
		printf( "GL_SHADING_LANGUAGE_VERSION:%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION) );

//	wglSwapIntervalEXT(1);

//	WGLExtensionSupported( "glGetString" );

//	g_initializedGL = true;

}
//------------------------------------------------------------------------------
void Gl::DisableOpenGL(HWND hWnd,  HGLRC* hGLRC)
//------------------------------------------------------------------------------
{
	wglMakeCurrent( NULL, NULL );
	if ( (*hGLRC) ) wglDeleteContext( (*hGLRC) );
	(*hGLRC) = 0;

//	if ( (*hDC) ) ReleaseDC( hWnd, (*hDC) );
//	(*hDC) = 0;
}
//------------------------------------------------------------------------------
bool Gl::WGLExtensionSupported(const char *extension_name)
//------------------------------------------------------------------------------
{
    // this is pointer to function which returns pointer to string with list of all wgl extensions
    PFNWGLGETEXTENSIONSSTRINGEXTPROC _wglGetExtensionsStringEXT = NULL;

    // determine pointer to wglGetExtensionsStringEXT function
    _wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC) wglGetProcAddress("wglGetExtensionsStringEXT");

    if (strstr(_wglGetExtensionsStringEXT(), extension_name) == NULL)
    {
        // string was not found
        printf( "NO:%s\n", extension_name );
        return false;
    }

        printf( "OK:%s\n", extension_name );
    // extension is supported
    return true;
}

//-----------------------------------------------------------------------------
void	Gl::CreateBuffer( GLuint* pHdl, int type, int size, void* tbl )
//-----------------------------------------------------------------------------
{
	glGenBuffers( 1, &(*pHdl) );
	glBindBuffer( type, (*pHdl) );
	glBufferData( type, size, tbl, GL_STATIC_DRAW );
	glBufferSubData( type, 0, size, tbl );
	glBindBuffer( type, 0);
}
//-----------------------------------------------------------------------------
void	Gl::SetBuffer( GLint hdlTag, GLuint hdlBuffer, int type, int sizeVal, int defVal )
//-----------------------------------------------------------------------------
{
	glEnableVertexAttribArray( hdlTag );
	glBindBuffer( type, hdlBuffer  );
	glVertexAttribPointer( hdlTag, sizeVal, defVal, GL_FALSE, 0, 0);
	glBindBuffer( type, 0);
}
//-----------------------------------------------------------------------------
void	Gl::TexSubImage2D( int target, int level, GLuint hdl_Texture, int innerformat, int x0, int y0, int width, int height, int format, int type, void* pBuf )
//-----------------------------------------------------------------------------
{
	glBindTexture( target, hdl_Texture );
	glTexSubImage2D( target, level, x0,y0, width, height, format, type, pBuf );
	glBindTexture( target, 0 );
}
//-----------------------------------------------------------------------------
void	Gl::CreateTexture( GLuint*  p_hdl_Texture, int target, int format, int width, int height, int min, int mag, int wraps, int wrapt )
//-----------------------------------------------------------------------------
{
	glGenTextures( 1, p_hdl_Texture );
	glBindTexture( target, *p_hdl_Texture );
	glTexParameterf( target, GL_TEXTURE_MIN_FILTER, min );
	glTexParameterf( target, GL_TEXTURE_MAG_FILTER, mag );
	glTexParameterf( target, GL_TEXTURE_WRAP_S, wraps );
	glTexParameterf( target, GL_TEXTURE_WRAP_T, wrapt );
//	glTexImage2D( target, 0, format, width, height, 0, GL_RGBA, GL_FLOAT, 0 );
	glTexImage2D( target, 0, format, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0 );

	glBindTexture( target, 0 );
}
//-----------------------------------------------------------------------------
void	Gl::SetTexture( int target, int hdl_Texture, int num, GLuint hdl_idTexture )
//-----------------------------------------------------------------------------
{
	glUniform1i( hdl_Texture, num );
	glActiveTexture( GL_TEXTURE0 + num );
	glBindTexture( target, hdl_idTexture );
}





#define MAX_SHADER_LOG_SIZE		(1024)
static	char s_logBuffer[MAX_SHADER_LOG_SIZE]; 
//-----------------------------------------------------------------------------
bool Gl::printShaderInfoLog(
//-----------------------------------------------------------------------------
	GLuint shader
)
{
	int logSize;
	int length;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &logSize);

	if (logSize > 1)
	{
		glGetShaderInfoLog(shader, MAX_SHADER_LOG_SIZE, &length, s_logBuffer);


		printf( "%s", s_logBuffer );
		if ( s_logBuffer[0] =='0' ) 
		{
			return false;
		}

	}
	return true;
}
//-----------------------------------------------------------------------------
void Gl::shader_Remove( GLuint hdlProgram )
//-----------------------------------------------------------------------------
{
	glDeleteProgram( hdlProgram );
}
//-----------------------------------------------------------------------------
void Gl::shader_LoadFile( GLuint*	pHdlProgram, const char* fn )
//-----------------------------------------------------------------------------
{

	GLuint hdlProgram = glCreateProgram();

	char*	pBuf = 0; 
	int		len = 0;

	File::file_malloc_Load( fn, &pBuf, &len );

	GLint result;

	struct SHADER
	{
		enum
		{
			NONE,
			VS,
			FS,

			MAX
		};
		int		ofs;
		char*	pBuf;
		int		len;
		int		type;
	} inf[ SHADER::MAX ] =
	{
		{0,0,0,0},
		{0,0,0,GL_VERTEX_SHADER},
		{0,0,0,GL_FRAGMENT_SHADER},
	};
	{
		int	shd = SHADER::NONE; 
		int	cntLF = 0;
		for ( int i = 0 ; i  < len ; i++ )
		{
			if ( pBuf[i] == 0x0a ) cntLF++;
			if ( '!' ) 
			{
				int	flg = false;
				if ( strncmp( &pBuf[i], "!vs",3 ) == 0 ) 
				{
					shd = SHADER::VS;
					flg = true;
				}
				if ( strncmp( &pBuf[i], "!fs",3 ) == 0 )
				{
					shd = SHADER::FS;
					flg = true;
				}
				if ( flg )
				{
					pBuf[i+0] = ' ';
					pBuf[i+1] = ' ';
					pBuf[i+2] = ' ';
					inf[shd].pBuf = &pBuf[i];
					inf[shd].len = cntLF;
					inf[shd].ofs = cntLF;
				}

			}
			inf[shd].len++;
		}
	}

	bool flgOK = true;
	for ( int shd = 1 ; shd  < SHADER::MAX ; shd ++ )
	{
		GLuint hdlShader = glCreateShader( inf[shd].type );

		{
			// エラー表示の行番号をそろえるためのオフセット調整
			int	s = 0;
			char*	str = new char[ inf[shd].len+1  ];
			for ( int i = 0 ; i < inf[shd].len ; i++ )
			{
				if ( i < inf[shd].ofs ) str[i] = 0x0a;
				else
				{
					str[i] = inf[shd].pBuf[s];
					s++;
				}
			}	
			str[inf[shd].len] = 0;
//			printf("[[[[%s]]]]]\n", str );	
			glShaderSource( hdlShader, 1, (const char **)&str, &inf[shd].len);
			delete str;
		}

		glCompileShader( hdlShader );
		glGetShaderiv( hdlShader, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			printShaderInfoLog( hdlShader );
			if ( shd == SHADER::VS ) fprintf(stderr, "Compile error at Vertex Shader in [%s]\n", fn);
			if ( shd == SHADER::FS ) fprintf(stderr, "Compile error at Fragment Shader in [%s]\n", fn);
			flgOK = false;
			glDeleteShader( hdlShader );
			break;
		}
		if ( false == printShaderInfoLog( hdlShader ) )
		{
			if ( shd == SHADER::VS ) fprintf(stderr, "Compile warning at Vertex Shader in [%s]\n", fn);
			if ( shd == SHADER::FS ) fprintf(stderr, "Compile warning at Fragment Shader in [%s]\n", fn);
		}

		glAttachShader( hdlProgram, hdlShader );
		glDeleteShader( hdlShader );
	}
//	mem_free( &pBuf );
	if ( pBuf ) {free( pBuf );pBuf = 0;}


	if ( (*pHdlProgram) != 0 ) 
	{
		glDeleteProgram( (*pHdlProgram) );
		(*pHdlProgram) = 0;
	}

	if ( flgOK )
	{
		glLinkProgram( hdlProgram );
		glValidateProgram( hdlProgram );

		(*pHdlProgram) = hdlProgram;
	}
	else
	{
		glDeleteProgram( hdlProgram );
	}
	
}
/*
//-----------------------------------------------------------------------------
bool Gl::shader_Compile(
//-----------------------------------------------------------------------------
	int		hdlProgram,
	int		type,
	const char*	fn
)
{
	GLint result;

	char*	pBuf = 0; 
	int		len = 0;

	file_malloc_Load( fn, &pBuf, &len );
	GLuint hdl = glCreateShader(type);

	glShaderSource( hdl, 1, (const char **)&pBuf, &len);
	glCompileShader( hdl );
	glGetShaderiv( hdl, GL_COMPILE_STATUS, &result);

	printShaderInfoLog( hdl );
	if (result == GL_FALSE)
	{
		fprintf(stderr, "Compile error at [%s]\n", fn);
	}

	glAttachShader( hdlProgram, hdl );
	glDeleteShader( hdl );
//	mem_free( &pBuf );
	if ( pBuf ) {free( pBuf );pBuf = 0;}
	return	true;
}
*/
