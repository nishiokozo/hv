class Ed
{
	char	m_filename[256];
	int		m_buf_lenInput;
	int		m_buf_lenData;
	int		m_buf_colum;
	int		m_buf_cpos;
	int		m_buf_lenBuf;
	char*	m_buf_pBuf;
	int 	m_ofs_line;
	int		m_ofs_column;

	void	buf_insert( int pos, int c );
	int		buf_GetPosLineHead( int cur );
	int		buf_GetCurX( int cur );
	bool	buf_LineCulm2Pos( int* pPos, int cx, int cy );
	int		buf_GetCurY( int cur );
	int		buf_GetPosNextLineHead( int cur );
	int		buf_SetPosX( int pos, int colum );
	int		buf_GetPosPrevLineHead( int cur );
	void	buf_pos2line_culm( int* px, int* py, int bpos );
	void	buf_DecodeScrn( int column, int line );
	int		buf_GetCntLF();
	void	buf_normalize();

public:

	enum REQUEST
	{
		NONE,
		INSERT,
//		INPUT_HEX,
//		INPUT_ENTER,
//		INPUT_BS,
		CHANGE_INSERT,
		MAX,
	} ;


	Ed();
	~Ed();

	void LoadFile( const char* fn );
	void SaveFile( const char* fn );
	void SaveFile();
	void DecodeScreen();
//	void Insert( int c );
	void buf_moveRollUp( int n );
	void buf_moveRollDown( int n );
	void	buf_moveUp();
	void	buf_moveDown();
	void	buf_moveLeft();
	void	buf_moveRight();
	void	buf_bs();

	bool	m_flgInsert;

	//	for mon
	void hex_DecodeScreen( int adr );
	void buf_hex_DecodeScrn( int line, int culumn );
	int	m_ofs_adr;
	void	buf_moveAddTo( int v );

	void Request( REQUEST t, int c );
	void buf_input_hex( int pos, int c );

	int	m_cntHex;
	int	m_valHex;
	int	m_time;
	int	m_buf_prev_cpos;
	void	buf_input_enter();
	void	buf_input_bs();

	bool	m_flgInputbuf;
	int	m_charInputbuf;
	int	m_cntInputbuf;
	int m_adrInputbuf;
	void	buf_close_inputbuf( int pos, int c );
	void	buf_openInputbuf( int idx );
void	buf_put_header( int adr );

	bool	m_flgHexMode;
	void ModeChange();
	void UpdateScreen();

};
