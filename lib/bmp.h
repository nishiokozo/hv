
class Bmp
{
public:
	bool	m_flgActive;

	int  	m_width;
	int  	m_height;
	float*	m_pBuf;

//	BITMAPINFO	m_bmi;

	Bmp( const char *fname );
	~Bmp();

};

