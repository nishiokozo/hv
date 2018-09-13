
class GlFont
{
public:

	static const int	FW = 8;
	static const int	FH = 8;

	float	m_ScrnW;
	float	m_ScrnH;


	//	color

	float		m_col[4];

	//	texture

	GLuint		m_hdlFont;
	Texture*	m_pTexFont;

	//	screen
//	GLuint	m_hdlScreen;
	Texture*	m_pTexScreen;

	//	shader
	int		m_cntIndex;
	GLuint	m_hdlVertex_Position;
	GLuint	m_hdlVertex_Uv;
	GLuint	m_hdlVertex_Index;
	GLuint	m_hdlProgram;
	int		m_hdl_Position;
	int		m_hdl_Uv;
	int		m_hdl_Tex0;
	int		m_hdl_Ofs;
	int		m_hdl_Pos;
	int		m_hdl_Col;


	GlFont( const char *fnFont, const char *fnShader, int width, int height );
	~GlFont();

	void Printc( int x, int y, const char c );

	void DrawFilter( int tex);

	void Color( float r, float g, float b );

//	void GetTexture();
};

