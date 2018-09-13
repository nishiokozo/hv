class	Env
{
public:
	char*	m_pBuf; 
	int		m_len;
	char	m_str[256];

	Env();
	~Env();
	void 	Load( const char* fn );
	bool	FindValue( const char* name, char* str, int len );
	float	GetFloat( const char* name );
	int		GetInt( const char* name );
	string	GetString( const char* name );
};

