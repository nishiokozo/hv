////////////////////////////////////////////////////////////////////////////////
class	GlFilter
////////////////////////////////////////////////////////////////////////////////
{
public:

	//	for common
	int		m_cntIndex;
	GLuint	m_hdlVertex_Position;
	GLuint	m_hdlVertex_Index;
	GLuint	m_hdlVertex_Uv;
	GLuint	m_hdlProgram;
	int		m_hdl_Position;
	int		m_hdl_Tex0;
	int		m_hdl_Uv;
	
	~GlFilter();
	GlFilter( const char* fnShader );

	void DrawFilterTexture( Texture* pTex );

};
