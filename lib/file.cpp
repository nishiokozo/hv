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

#include "file.h"

//-----------------------------------------------------------------------------
bool	File::file_Save( const char* fname, char* pBuf, int lenBuf )
//-----------------------------------------------------------------------------
{
		FILE*	fp = 0;
		if ((fp = fopen(fname, "wb")) == NULL)
		{
			printf( "File error [%s]\n", fname );
			return	false;
		}
		else
		{
						fwrite(pBuf, 1, lenBuf, fp);

						fclose( fp );

		}

	return	true;
}

//-----------------------------------------------------------------------------
bool	File::file_Load( const char* fname, char* pBuf, int lenBuf, int* pLen )
//-----------------------------------------------------------------------------
{
	char*	fbuf = pBuf;
	int		flen = 0;
	{

		FILE*	fp = 0;
		if ((fp = fopen(fname, "rb+")) == NULL)
		{
			printf( "File error [%s]\n", fname );
			return	false;
		}
		else
		{
			{
				fseek(fp, 0, SEEK_END);
				flen = (int)ftell(fp);
				fseek(fp, 0, SEEK_SET);
			}
			if ( flen >= lenBuf )
			{
				fclose( fp );
				return false;
			}
			{
				fread(fbuf, 1, flen, fp);
			}
			fclose( fp );
		}
	}
	(*pLen) = flen;

	return	true;
}
//-----------------------------------------------------------------------------
bool	File::file_malloc_Load( const char* fname, char** ppBuf, int* pLen )
//-----------------------------------------------------------------------------
{
	char*	fbuf = 0;
	int		flen = 0;
	{

		FILE*	fp = 0;
		if ((fp = fopen(fname, "rb")) == NULL)
		{
			printf( "File error [%s]\n", fname );
			return	false;
		}
		else
		{
			{
				fseek(fp, 0, SEEK_END);
				flen = (int)ftell(fp);
				fseek(fp, 0, SEEK_SET);
			}
			{
				fbuf = (char*)malloc( flen );
//				fbuf = new char( flen );
				fread(fbuf, 1, flen, fp);
			}
			fclose( fp );
		}
	}
	(*ppBuf) = fbuf;
	(*pLen) = flen;

	return	true;
}
