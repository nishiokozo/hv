#include <windows.h>
#include <stdio.h>
#include "bmp.h"
#include "gdi.h"

//------------------------------------------------------------------------------
Gdi::Gdi()
//------------------------------------------------------------------------------
{
	m_pPixel = 0;
	memset(&m_bmi, 0, sizeof(BITMAPINFOHEADER) );

}
//------------------------------------------------------------------------------
void	GDI_CreateBmp( BYTE** ppPixel, BITMAPINFO& bmi, int width, int height )
//------------------------------------------------------------------------------
{
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = 0;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;
	bmi.bmiHeader.biClrUsed = 0;
	bmi.bmiHeader.biClrImportant = 0;

	(*ppPixel) = (BYTE *) malloc (bmi.bmiHeader.biWidth*bmi.bmiHeader.biHeight*bmi.bmiHeader.biBitCount/8);
/*
	int	i = 0;
	for ( int y = 0 ; y < bmi.bmiHeader.biHeight ; y++)
	for ( int x = 0 ; x < bmi.bmiHeader.biWidth ; x++)
	{
		int	r = bmp.m_pBuf[(y*128+x)*4+0];
		int	g = bmp.m_pBuf[(y*128+x)*4+1];
		int	b = bmp.m_pBuf[(y*128+x)*4+2];

		(*ppPixel)[i++] = g;
		(*ppPixel)[i++] = b;
		(*ppPixel)[i++] = r;
	}
*/

#if 0
	
	printf("biSize %d\n", (int)bmi.bmiHeader.biSize );
	printf("biWidth %d\n", (int)bmi.bmiHeader.biWidth );
	printf("biHeight %d\n", (int)bmi.bmiHeader.biHeight );
	printf("biPlanes %d\n", (int)bmi.bmiHeader.biPlanes );
	printf("biBitCount %d\n", (int)bmi.bmiHeader.biBitCount );
	printf("biCompression %d\n", (int)bmi.bmiHeader.biCompression );
	printf("biSizeImage %d\n", (int)bmi.bmiHeader.biSizeImage );
	printf("biXPelsPerMeter %d\n", (int)bmi.bmiHeader.biXPelsPerMeter );
	printf("biYPelsPerMeter %d\n", (int)bmi.bmiHeader.biYPelsPerMeter );
	printf("biClrUsed %d\n", (int)bmi.bmiHeader.biClrUsed );
	printf("biClrImportant %d\n", (int)bmi.bmiHeader.biClrImportant );
#endif

}
//------------------------------------------------------------------------------
void	GDI_Paint( HWND hWnd, BITMAPINFO& bmi, BYTE* pPixel )
//------------------------------------------------------------------------------
{

	int w = bmi.bmiHeader.biWidth;
	int h = bmi.bmiHeader.biHeight;
	BITMAPINFO bi;
	BITMAPINFOHEADER &bih=bi.bmiHeader;
	bih.biSize			= sizeof(bih);
	bih.biWidth			= w;
	bih.biHeight		= -h;
	bih.biPlanes		= 1;
	bih.biBitCount		= 24;
	bih.biCompression	= BI_RGB;//BI_BITFIELDS;
	bih.biSizeImage		= 0;
	bih.biXPelsPerMeter	= 0;
	bih.biYPelsPerMeter	= 0;
	bih.biClrUsed		= 0;
	bih.biClrImportant	= 0;
	HDC hdc = GetDC(hWnd);
	RECT rect;
	GetClientRect(hWnd, &rect);
	StretchDIBits(hdc, 0, 0, rect.right, rect.bottom, 0, 0, w, h, pPixel, &bi, DIB_RGB_COLORS, SRCCOPY);
	ReleaseDC(hWnd,hdc);



}

//------------------------------------------------------------------------------
void	Gdi::Paint( HWND hWnd )
//------------------------------------------------------------------------------
{
	GDI_Paint( hWnd, m_bmi, m_pPixel );
}

//------------------------------------------------------------------------------
void	GDI_Draw( HWND hWnd, BYTE* pPixel, int width, int heigit )
//------------------------------------------------------------------------------
{

	int w = width;
	int h = heigit;
	BITMAPINFO bi;
	BITMAPINFOHEADER &bih=bi.bmiHeader;
	bih.biSize			= sizeof(bih);
	bih.biWidth			= w;
	bih.biHeight		= h;
	bih.biPlanes		= 1;
	bih.biBitCount		= 24;
	bih.biCompression	= BI_RGB;//BI_BITFIELDS;
	bih.biSizeImage		= 0;
	bih.biXPelsPerMeter	= 0;
	bih.biYPelsPerMeter	= 0;
	bih.biClrUsed		= 0;
	bih.biClrImportant	= 0;
	HDC hdc = GetDC(hWnd);
	RECT rect;
	GetClientRect(hWnd, &rect);
	StretchDIBits(hdc, 0, 0, rect.right, rect.bottom, 0, 0, w, h, pPixel, &bi, DIB_RGB_COLORS, SRCCOPY);
	ReleaseDC(hWnd,hdc);



}

