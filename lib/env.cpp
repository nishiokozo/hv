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
#include "file.h"
#include "env.h"

//-----------------------------------------------------------------------------
Env::Env()
//-----------------------------------------------------------------------------
{
	m_pBuf = 0;
	m_len = 0;
}
//-----------------------------------------------------------------------------
Env::~Env()
//-----------------------------------------------------------------------------
{
//			printf("~Env.1\n");
	
	if ( m_pBuf ) {free( m_pBuf );m_pBuf = 0;}
//			printf("~Env.2\n");
}

//-----------------------------------------------------------------------------
void Env::Load( const char* fn )
//-----------------------------------------------------------------------------
{
		File::file_malloc_Load( fn, &m_pBuf, &m_len );
}

//-----------------------------------------------------------------------------
bool	Env::FindValue( const char* strKey, char* strValue, int len )
//-----------------------------------------------------------------------------
{
	int		n = 0;
	int		clm = 0;
	bool	flgFind = false;

	char	strToken[256];	
	strToken[0] = 0;

	for ( int i = 0 ; i < len  ; i++  )
	{
		char	c = m_pBuf[i];

		bool	flgGraph = isgraph(c);
		bool	flgEot = ( flgGraph == false && n > 0 ) ;
		bool	flgEol = ( c == 0x0a || i+1 == len ) ;

		if ( flgGraph ) strToken[n++] = c;
			
		if ( flgEot )
		{
			strToken[n] = 0;
			n = 0;

			if ( clm == 0 && strcmp( strToken, strKey ) == 0 ) 
			{
				flgFind = true;
			}

			if ( flgFind && clm > 0 ) break;
			
			clm++;
		}
		
		if ( flgEol )
		{
			clm = 0;
		}
		
	}

	if ( flgFind )
	{
		strcpy( strValue, strToken );
	}
	else
	{
		strValue[0] = 0;
	}
	

	if ( flgFind == false ) 
	{
		printf("error Can not found Value [%s]\n", strKey );
	}
	return flgFind;
}

//-----------------------------------------------------------------------------
float	Env::GetFloat( const char* name )
//-----------------------------------------------------------------------------
{
	if ( FindValue( name, m_str, m_len ) ) return atof( m_str );
	return 0.0f;
}
//-----------------------------------------------------------------------------
int		Env::GetInt( const char* name )
//-----------------------------------------------------------------------------
{
	if ( FindValue( name, m_str, m_len ) ) return atoi( m_str );
	return 0;
}
//-----------------------------------------------------------------------------
string	Env::GetString( const char* name )
//-----------------------------------------------------------------------------
{
	FindValue( name, m_str, m_len );
	return m_str;
}
