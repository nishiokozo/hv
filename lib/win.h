class	Win
{
public:
	bool	FlgActive;

	char	m_classname[256];

	boolean	m_flgError;
	HWND	m_hWnd;
	HDC		m_hDC;
//	HGLRC	m_hGLRC;

	int	m_x;
	int	m_y;
	int	m_w;
	int	m_h;
	int	m_buf_w;
	int	m_buf_h;

	int			m_Interval;
	double		m_Fps;
	bool		m_ShowFlg;
	double		m_ShowSec;

	LARGE_INTEGER m_frequency; 
	double		m_timerFrame;
	double		m_measure_timerSec;
	double		m_measure_timerPaint;
	uint64_t	m_measure_counterPaint;



	Win( const char* classname, LRESULT CALLBACK (*)(HWND, UINT, WPARAM, LPARAM) );
	//Win( const char* classname );
	~Win();
	void	OpenWin( int x, int y, int w, int h, int buf_w, int buf_h, const char* name );
	void	OpenWin2( int x, int y, int w, int h, int buf_w, int buf_h, const char* name );
	void	CloseWin();
	bool	Message();

	void	SwapBuffer();
	void	ShowWin();

	void EnableOpenGL(HWND hWnd, HDC * pHDC, HGLRC * hGLRC);
	void DisableOpenGL(HWND hWnd, HDC* hDC, HGLRC* hGLRC);
	void MakeCurrentGL();

	static LRESULT CALLBACK WndProc
	(
		  HWND	hWnd
		, UINT	uMsg
		, WPARAM wParam
		, LPARAM lParam
	);

};
//extern	char vkbuf_get();
extern	void vkbuf_get( int* p1, int* p2 );
extern	void vkbuf_Clear();
enum
{
	WIN_SHIFT,
	WIN_CTRL,
	WIN_ALT,
	WIN_CAPS,
};
