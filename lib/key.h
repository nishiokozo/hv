struct Vkey
{
	int		vk;
	int		ascii;
	bool	shift;
	bool	ctrl;
	bool	alt;
	bool	caps;
};
struct Keybtn
{
	bool	prev;
	bool	now;
	bool	toggle;
	int		limRepeat;
} ;

struct Key
{
	BYTE	m_key_state[256];

	Keybtn	m_keybtn[256];


	static const int MAX_KEYBUF = 256;
	int	m_keybuf[MAX_KEYBUF];

	int	m_keycurrent;
	int	m_limActive;

	int m_limRepeat1st;
	int m_limRepeat2nd;
	
//	static	const int MAX_KEYBUF = 256;
//	chat	m_keybuf[MAX_KEYBUF];

	~Key();
	Key();
	void	key_update_atKey();
	void	key_update_atSync();
	void	UpdateKey();
	bool	now( int val );
	bool	hi( int val );
	bool	low( int val );
	bool	repeat( int val );

	Vkey		inkey();

	void	Clear();

	void	SetRepatTime( int n, int m );

	Keybtn	Get( int val );
	
};
