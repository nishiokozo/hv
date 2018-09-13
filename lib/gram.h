////////////////////////////////////////////////////////////////////////////////
class Gram
////////////////////////////////////////////////////////////////////////////////
{
public:

//	int		m_type;
//	GLuint	m_hdl_idTexture;
	float*	m_pBuf;
	int		m_width;
	int		m_height;

//	Texture*	m_pTexture;

	void 	Clear();
	
	void	PutColor( int x, int y, float r, float g, float b );
	void	GetColor( int x, int y, float& r, float& g, float& b );

	void	FillColor( int x, int y, float* ptr, int w, int h );

	~Gram();
//	Gram( int width, int height, int type, bool nearest_linear );
	Gram( int width, int height );
//
	void Load( float* fm, int w, int h );

};
