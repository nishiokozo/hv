class	Gra
{
	int		m_cntIndex;
	GLuint	m_hdlVertex_Position;
	GLuint	m_hdlVertex_Index;
	GLuint	m_hdlProgram;
	int		m_hdl_Position;
	static	const int m_MAX_LINES=1000;
	struct m_ModelLine
	{
		vec2	s;
		vec2	e;
	}	m_tblPosition[m_MAX_LINES];
	int		m_tblIndex[m_MAX_LINES*2];
	int		m_cntLines;

public:

	Gra();
	void Init( const char* fnShader );
	void Line( vec2 s, vec2 e );
	void UpdateGra();
};
