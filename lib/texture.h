class Texture
{
	void CreateTexture( int target, int format, int width, int height, int min, int mag, int wraps, int wrapt );
public:
	GLuint	m_hdl;

	int		m_target;
	int		m_format;
	int		m_width;
	int		m_height;
	int		m_min;
	int		m_mag;
	int		m_wraps;
	int		m_wrapt;

	Texture( int target, int format, int width, int height, int min, int mag, int wraps, int wrapt );
	Texture( const char* fname );

	void LoadTexture( int width, int height, int format, int type, void* pBuf );
//	void ClearTexture();

};
