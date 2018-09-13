class Joystick
{
	int	m_id;
public:
	struct JOYOBJ
	{
		bool	now;
		bool	prev;
		bool	hi;
		bool	low;
	};
		JOYOBJ	LU;
		JOYOBJ	LD;
		JOYOBJ	LL;
		JOYOBJ	LR;
		JOYOBJ	L1;
		JOYOBJ	L2;
		JOYOBJ	L3;

		JOYOBJ	RU;
		JOYOBJ	RD;
		JOYOBJ	RL;
		JOYOBJ	RR;
		JOYOBJ	R1;
		JOYOBJ	R2;
		JOYOBJ	R3;

		JOYOBJ	SE;
		JOYOBJ	ST;


	struct JOYBUTTON
	{
		bool	Lu;
		bool	Ld;
		bool	Ll;
		bool	Lr;
		bool	L1;
		bool	L2;
		bool	L3;

		bool	Ru;
		bool	Rd;
		bool	Rl;
		bool	Rr;
		bool	R1;
		bool	R2;
		bool	R3;

		bool	Se;
		bool	St;
	};

	JOYBUTTON	now;
	JOYBUTTON	hi;
	JOYBUTTON	low;
	JOYBUTTON	prev;

	float	Lx;
	float	Ly;
	float	Rx;
	float	Ry;

	float	ValThreshold;
	
	Joystick( int n );
	void UpdateJoystick();

	void SetThreshold( float val );

};
