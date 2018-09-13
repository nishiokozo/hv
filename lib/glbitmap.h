////////////////////////////////////////////////////////////////////////////////
class GlBitmap
////////////////////////////////////////////////////////////////////////////////
{
public:

	int		m_type;
	GLuint	m_hdl_idTexture;
	float*	m_pBuf;
	int		m_width;
	int		m_height;

	Texture*	m_pTexture;

	void 	Clear();
	
	void	PutColor( int x, int y, float r, float g, float b );
	void	GetColor( int x, int y, float& r, float& g, float& b );

	~GlBitmap();
	GlBitmap( int width, int height, int type, bool nearest_linear );
	void 	UpdateTexture();
//	GLuint	GetTexture();
};
