namespace File
{
	bool	file_malloc_Load( const char* fname, char** ppBuf, int* pLen );
	bool	file_Load( const char* fname, char* pBuf, int lenBuf, int* pLen );
	bool	file_Save( const char* fname, char* pBuf, int lenBuf );

};
