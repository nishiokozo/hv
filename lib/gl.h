namespace Gl
{
	void	MakeCuttent( HDC hDC, HGLRC hGLRC );
	bool	WGLExtensionSupported(const char *extension_name);
	void	EnableOpenGL(HWND hWnd, HDC hDC, HGLRC * hGLRC);
	void	DisableOpenGL(HWND hWnd, HGLRC* hGLRC);

	void	SetTexture( int target, int hdl_Texture, int num, GLuint hdl_idTexture );
	bool	printShaderInfoLog( GLuint shader );
	void 	shader_Remove( GLuint hdlProgram );
	void 	shader_LoadFile( GLuint*	pHdlProgram, const char* fn );

	void	CreateBuffer( GLuint* pHdl, int type, int size, void* tbl );
	void	SetBuffer( GLint hdlTag, GLuint hdlBuffer, int type, int sizeVal, int defVal );
	void	CreateTexture( GLuint*  p_hdl_Texture, int target, int format, int width, int height, int min, int mag, int wraps, int wrapt );
	void	LoadTexture( int target, GLuint hdl_Texture, int innerformat, int width, int height, int format, int type, void* pBuf );


	void	TexSubImage2D( int target, int level, GLuint hdl_Texture, int innerformat, int x0, int y0, int width, int height, int format, int type, void* pBuf );

};
