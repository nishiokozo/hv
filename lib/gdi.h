void	GDI_Draw( HWND hWnd, BYTE* pPixel, int width, int heigit );



void	GDI_LoadBmp( BYTE ** bPixelBits, BITMAPINFO& bmi,  Bmp& bmp );
void	GDI_Paint( HWND hWnd, BITMAPINFO& bmi, BYTE* pPixel );
void	GDI_CreateBmp( BYTE** ppPixel, BITMAPINFO& bmi, int width, int height );

class	Gdi
{
	BYTE* 			m_pPixel;
	BITMAPINFO		m_bmi;

	Gdi();
	void	LoadBmp( Bmp& bmp );
	void	Paint( HWND hWnd );
};
