class Mouse
{
public:
	float	x;
	float	y;

	float	prev_x;
	float	prev_y;

	float	dx;
	float	dy;

	struct	BUTTON
	{
		bool	l;
		bool	r;
	};

	BUTTON	now;
	BUTTON	hi;
	BUTTON	low;
	BUTTON	prev;

	Mouse();
	void UpdateMouse( int _x, int _y, int _w, int _h );

};
