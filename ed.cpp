#include <sys.h>
#include "ed.h"
//extern	Sys	sys( const char* );
extern class Sys sys;


//int	g_lx = 0;
//int	g_ly = 0;
void	cls()
{
			for ( int h = 0 ; h < sys.m_scrn_H ; h++ )
			{
				for ( int w = 0 ; w < sys.m_scrn_W ; w++ )
				{
					long long a = (long long)sys.m_scrn_buf;
					a += (h*sys.m_scrn_W + w);
					*(int*)(a) = ' ';
				}
			}
}
/*
void	locate( int x, int y )
{
	if ( x < 0 ) x = 0;
	if ( x >= sys.m_scrn_W ) x = sys.m_scrn_W-1;
	if ( y < 0 ) y = 0;
	if ( y >= sys.m_scrn_H ) y = sys.m_scrn_H-1;
	g_lx = x;
	g_ly = y;

}

void	printc( const char c )
{
		sys.m_scrn_buf[g_ly*sys.m_scrn_W + g_lx] = c;
}
void	printstr( const char *str  )
{
	int len = strlen( str );

	for ( int i = 0 ; i < len ; i++ )
	{
		const char c = str[i];
		sys.m_scrn_buf[g_ly*sys.m_scrn_W + g_lx+i] = c;
	}
	

}
*/

//-----------------------------------------------------------------------------
void	Ed::buf_moveAddTo( int v )
//-----------------------------------------------------------------------------
{
		buf_close_inputbuf( m_adrInputbuf, m_charInputbuf );

	m_buf_cpos += v;
//	m_cntHex = 0;
	m_time = 0x0;
	
//	printf("addto\n");

}

//-----------------------------------------------------------------------------
int	Ed::buf_GetPosLineHead( int cur )
//-----------------------------------------------------------------------------
{
	int	pos = cur-1;

	while( pos > 0 )
	{
		if ( m_buf_pBuf[pos] == '\n' )
		{
			pos++;
			break;
		}
		pos--;
	}

	if ( pos < 0 )
	{
		pos = 0;
	}
	return pos;
}
//-----------------------------------------------------------------------------
void	Ed::buf_moveRight()
//-----------------------------------------------------------------------------
{
	if ( m_flgHexMode )
	{
		buf_moveAddTo(1);
	}
	else
	{
		int	bpos = m_buf_cpos;

		if ( bpos < m_buf_lenData )
		{
			m_buf_cpos = bpos+1;
		}

		m_buf_colum = buf_GetCurX( m_buf_cpos );
	}
}
//-----------------------------------------------------------------------------
void	Ed::buf_moveLeft()
//-----------------------------------------------------------------------------
{
	if ( m_flgHexMode )
	{
		buf_moveAddTo(-1);
	}
	else
	{
		int	bpos = m_buf_cpos-1;

		if ( bpos >= 0 )
		{
			m_buf_cpos = bpos;
		}

		m_buf_colum = buf_GetCurX( m_buf_cpos );
	}
}
//-----------------------------------------------------------------------------
void	Ed::buf_bs()
//-----------------------------------------------------------------------------
{
	if ( m_buf_cpos < 1 ) return;
	
	for ( int i = m_buf_cpos ; i < m_buf_lenData ; i++ )
	{
		m_buf_pBuf[i-1] = m_buf_pBuf[i];
	}

	m_buf_lenData--;

	buf_moveLeft();

}
//-----------------------------------------------------------------------------
bool 	Ed::buf_LineCulm2Pos( int* pPos, int cx, int cy )
//-----------------------------------------------------------------------------
{
	bool	ret = true;

	int	i = 0;

	{
		int	y = 0;
		for (  ; i < m_buf_lenData ; i++ )
		{
			if ( y == cy ) break;
			if ( '\n' == m_buf_pBuf[i] ) y++;
		}
	}

	{
		int	x = 0; 
		for (  ; i < m_buf_lenData  ; i++ )
		{
			if ( x == cx ) break;
			if ( x > cx ) 
			{
				ret = false;
				break;
			}
			if ( '\n' == m_buf_pBuf[i] ) 
			{
				ret = false;
				break;
			}
			if ( '\t' == m_buf_pBuf[i] ) x+=4;
			else
			x++;
		}
	}

	if (  i >= m_buf_lenData  ) ret = false;


	*pPos = i;

	return ret;
	
}

//-----------------------------------------------------------------------------
void	Ed::buf_insert( int pos, int c )
//-----------------------------------------------------------------------------
{

	{
		for ( int i = m_buf_lenData ; i > pos ; i-- )
		{
			m_buf_pBuf[i] = m_buf_pBuf[i-1];
		}
			m_buf_pBuf[pos] = c;

		m_buf_lenData++;

		buf_moveRight();
	}
//printf("insert %d, %d\n", c,m_buf_lenData );
}
//-----------------------------------------------------------------------------
int	hex2i( const char* str )
//-----------------------------------------------------------------------------
{
	int	val = 0;
	int	len = strlen(str);
	for ( int i = 0 ; i < len ; i++ )
	{
		int	a = 0;
		switch ( str[i] )
		{
			case '0':			a = 0; break;
			case '1':			a = 1; break;
			case '2':			a = 2; break;
			case '3':			a = 3; break;
			case '4':			a = 4; break;
			case '5':			a = 5; break;
			case '6':			a = 6; break;
			case '7':			a = 7; break;
			case '8':			a = 8; break;
			case '9':			a = 9; break;
			case 'a':case 'A':	a = 10; break;
			case 'b':case 'B':	a = 11; break;
			case 'c':case 'C':	a = 12; break;
			case 'd':case 'D':	a = 13; break;
			case 'e':case 'E':	a = 14; break;
			case 'f':case 'F':	a = 15; break;
		}
		val += a*pow(16,len-1-i); 
	}
	return val;
	
}

//-----------------------------------------------------------------------------
int	hex2i( int c )
//-----------------------------------------------------------------------------
{
	int	a = 0;
	{
		switch ( c )
		{
			case '0':			a = 0; break;
			case '1':			a = 1; break;
			case '2':			a = 2; break;
			case '3':			a = 3; break;
			case '4':			a = 4; break;
			case '5':			a = 5; break;
			case '6':			a = 6; break;
			case '7':			a = 7; break;
			case '8':			a = 8; break;
			case '9':			a = 9; break;
			case 'a':case 'A':	a = 10; break;
			case 'b':case 'B':	a = 11; break;
			case 'c':case 'C':	a = 12; break;
			case 'd':case 'D':	a = 13; break;
			case 'e':case 'E':	a = 14; break;
			case 'f':case 'F':	a = 15; break;
		}
	}
	return a;
	
}

//-----------------------------------------------------------------------------
void	Ed::buf_input_bs()
//-----------------------------------------------------------------------------
{

//	if ( m_buf_cpos < 1 ) return;
	
	if ( m_cntInputbuf == 0 && m_buf_cpos > 0 )
	{
		if ( m_buf_cpos == m_buf_lenData ) m_buf_lenData--;
			buf_moveAddTo(-1);

		m_cntInputbuf=1;
		buf_openInputbuf(1);
	}
	else
	if ( m_cntInputbuf > 0 )
	{
		m_cntInputbuf--;
		buf_openInputbuf(0);
	}




}
//-----------------------------------------------------------------------------
void	Ed::buf_input_enter()
//-----------------------------------------------------------------------------
{
	int next = (m_buf_cpos /16+1)*16;

//	int cnt =0;
	for (  ; m_buf_lenData < next ; m_buf_lenData++ )
	{
		m_buf_pBuf[m_buf_lenData] = 0x00;

//		cnt++;
	}

//	m_buf_lenInput += next*2-m_buf_cpos;

//	m_buf_cpos = next;
//	m_cntHex = 0;
//	m_time = 0x0;

	buf_moveAddTo( next-m_buf_cpos );

	
}
//-----------------------------------------------------------------------------
void	Ed::buf_close_inputbuf( int pos, int c )
//-----------------------------------------------------------------------------
{
	if ( m_flgInputbuf )
	{
		m_flgInputbuf = false;

		//	last pop only
		if ( (m_buf_lenData == pos ) ) 
		{
			m_buf_lenData++;
		}

			m_buf_pBuf[pos] = c;
	}
}

//-----------------------------------------------------------------------------
void	Ed::buf_openInputbuf( int idx )
//-----------------------------------------------------------------------------
{
	if ( m_flgInputbuf == false )
	{
		if ( m_buf_cpos < m_buf_lenData || idx > 0 ) 
		{
			m_charInputbuf = m_buf_pBuf[m_buf_cpos];
		}
		else
		{
			m_charInputbuf = 0;
		}
		m_adrInputbuf = m_buf_cpos;
		m_cntInputbuf = idx;
		m_flgInputbuf = true;
	}
}
//-----------------------------------------------------------------------------
void	Ed::buf_input_hex( int cpos, int c )
//-----------------------------------------------------------------------------
{

/*

	//	last pop only
	if ( (m_buf_lenData == cpos/2 ) && (cpos%2) == 0 ) 
	{
		m_buf_pBuf[m_buf_lenData] = 0x00;
		m_buf_lenData++;
	}
*/


	{
	//			m_buf_lenInput++;
		{
	//		int a = 0;
			if ( m_cntInputbuf % 2 == 0  ) 
			{
	//			a = m_buf_pBuf[cpos/2];
				m_charInputbuf = (m_charInputbuf&0xf) | ((hex2i(c)<<4)&0xf0);
			}
			else
			{
				m_charInputbuf = (hex2i(c)&0xf) | (m_charInputbuf&0xf0);
			}

			m_cntInputbuf++;
			if ( m_cntInputbuf >=2 )
			{
				buf_moveAddTo(1);
			}
		}
	}

}
//-----------------------------------------------------------------------------
int	Ed::buf_GetCntLF()
//-----------------------------------------------------------------------------
{
	int	lf = 0;
	for ( int i = 0 ; i < m_buf_lenData ; i++ )
	{
		if ( m_buf_pBuf[i] == '\n' ) lf++;
	
	}
	return lf;
}
//-----------------------------------------------------------------------------
int	Ed::buf_GetCurX( int cur )
//-----------------------------------------------------------------------------
{
	int	st = buf_GetPosLineHead( cur );

	int	x = 0;

	for( int i = st ; i < cur ; i++ )
	{
		if ( m_buf_pBuf[i] == '\t' ) x += 4;
		else
		x++;
	}
	return x;
}
//-----------------------------------------------------------------------------
int	Ed::buf_GetCurY( int cur )
//-----------------------------------------------------------------------------
{
	int	lf = 0;
	for ( int i = 0 ; i < cur ; i++ )
	{
		if ( m_buf_pBuf[i] == '\n' ) lf++;
	
	}
	return lf;
}

//-----------------------------------------------------------------------------
int	Ed::buf_GetPosNextLineHead( int cur )
//-----------------------------------------------------------------------------
{
	int	pos = cur;

	while( pos < m_buf_lenData )
	{
		if ( m_buf_pBuf[pos] == '\n' )
		{
			pos++;
			break;
		}
		pos++;
	}

	if ( pos >= m_buf_lenData )
	{
		pos = m_buf_lenData-1;
	}
	return pos;

}
//-----------------------------------------------------------------------------
int	Ed::buf_SetPosX( int pos, int colum )
//-----------------------------------------------------------------------------
{
	int	cnt = 0;
	int	x = 0;
	for ( int i = pos ; i < m_buf_lenData ; i++ )
	{
		if ( x >= colum ) break;
		if ( m_buf_pBuf[i] == '\n' ) break;
		if ( m_buf_pBuf[i] == '\t' ) x += 4;
		else
		x++;
		if ( x > colum ) break;

		cnt++;
	}

	return pos + cnt;
}

//-----------------------------------------------------------------------------
void	Ed::buf_moveDown()
//-----------------------------------------------------------------------------
{
	if ( m_flgHexMode )
	{
		buf_moveAddTo(16);
	}
	else
	{

		int	next_line = buf_GetPosNextLineHead( m_buf_cpos );
		m_buf_cpos = buf_SetPosX( next_line, m_buf_colum );
	}
}
//-----------------------------------------------------------------------------
int	Ed::buf_GetPosPrevLineHead( int cur )
//-----------------------------------------------------------------------------
{
	int	cnt = 0;
	int	i = 0;
	for ( i = cur-1 ; i > 0 ; i-- )
	{
		if ( m_buf_pBuf[i] == '\n' ) cnt++;
		if ( cnt >= 2 ) 
		{	
			i++;
			break;
		}
	}
	if ( i < 0 ) i = 0;


	return i;
}

//-----------------------------------------------------------------------------
void	Ed::buf_moveUp()
//-----------------------------------------------------------------------------
{
	if ( m_flgHexMode )
	{
		buf_moveAddTo(-16);
	}
	else
	{
		int prev_line = buf_GetPosPrevLineHead(m_buf_cpos);
		m_buf_cpos = buf_SetPosX( prev_line, m_buf_colum );
	}
}

//-----------------------------------------------------------------------------
void	Ed::buf_pos2line_culm( int* px, int* py, int bpos )
//-----------------------------------------------------------------------------
{
	int	last = 0;
	{
		int	y = 0;
		for ( int i = 0 ; i < bpos ; i++ )
		{
			if ( '\n' == m_buf_pBuf[i] ) 
			{
				last = i+1;
				y++;
			}
		}
		*py = y;
	}

	{
		int	x = 0;
		for ( int i = last ; i < bpos ; i++ )
		{
			if ( '\t' == m_buf_pBuf[i] ) 
				x+=4;
			else
				x++;
		}
		*px = x;
	}

}

//-----------------------------------------------------------------------------
void	Ed::buf_DecodeScrn( int line, int culumn )
//-----------------------------------------------------------------------------
{

	cls();

	int	bpos = 0;
	int	x = 0;
	int	y = 0;

	int	aline = line;
	bool	flgLF = false;

culumn = 0;

	buf_LineCulm2Pos( &bpos, culumn, line );
	while( y < sys.m_scrn_H && bpos < m_buf_lenData )
	{
		int	ox = x;
		int	oy = y;


		int	spos = y*sys.m_scrn_W + x;
		int	c = m_buf_pBuf[bpos];
		if ( c == '\n' )
		{
			if ( x < sys.m_scrn_W )
			sys.m_scrn_buf[spos] = 0x1f;	//	 『↓』
			y++;
			x = 0;
			flgLF = true;
		}
		else
		if ( c == '\t' )
		{
			if ( x < sys.m_scrn_W )
			sys.m_scrn_buf[spos] = 0x1c;	//	 『→』
			x += 4;
		}
		else
		{
			if ( x < sys.m_scrn_W )
			sys.m_scrn_buf[spos] = c;
			x++;
		}

		if ( x <= sys.m_scrn_W )
		{
			if ( m_buf_cpos == bpos )	sys.m_scrn_buf[spos] = '_';
		}
/*	 
		if ( flgLF )
		{
			flgLF = false;
			aline++;
			buf_LineCulm2Pos( &bpos, culumn, aline );
		}
		else
*/
		bpos++;
	}


	if ( bpos == m_buf_lenData )
	{
		sys.m_scrn_buf[y*sys.m_scrn_W + x] = 0;//	 『^@』
	}


}

//-----------------------------------------------------------------------------
int	b2hex( int c )
//-----------------------------------------------------------------------------
{
	int	a;
		switch ( c )
		{
			case 0x0:			a = '0'; break;
			case 0x1:			a = '1'; break;
			case 0x2:			a = '2'; break;
			case 0x3:			a = '3'; break;
			case 0x4:			a = '4'; break;
			case 0x5:			a = '5'; break;
			case 0x6:			a = '6'; break;
			case 0x7:			a = '7'; break;
			case 0x8:			a = '8'; break;
			case 0x9:			a = '9'; break;
			case 0xa:			a = 'A'; break;
			case 0xb:			a = 'B'; break;
			case 0xc:			a = 'C'; break;
			case 0xd:			a = 'D'; break;
			case 0xe:			a = 'E'; break;
			case 0xf:			a = 'F'; break;
		}
	return a;
	
}
//-----------------------------------------------------------------------------
void	Ed::buf_put_header( int adr )
//-----------------------------------------------------------------------------
{
			
	
}
//-----------------------------------------------------------------------------
void	Ed::buf_hex_DecodeScrn( int line, int culumn )
//-----------------------------------------------------------------------------
{

	cls();

	int	bpos = 0;
	int	x = 0;
	int	y = 0;

//	int	aline = line;
//	bool	flgLF = false;

	int	cnt = 0;
	m_time++;
culumn = 0;

//	buf_LineCulm2Pos( &bpos, culumn, line );

bpos = line*16;

	int	sumv = 0;
	int	sumh = 0;

	int 	inputbuf_spos = -1;
	int	spos = 0;
	
	while( y < sys.m_scrn_H && bpos <= m_buf_lenData )
	{

		spos = y*sys.m_scrn_W+x;

		if ( x == 0 )
		{
			int adr = bpos+m_ofs_adr;
//			buf_put_header( bpos+m_ofs_adr );
			//	disp header
			{
				if ( (adr & 0x00ff ) == 0x00 )
				{
					sumv = 0;
					sumh = 0;
					

					char	str[256];
					sprintf(str, "Add  +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F :Sum" );
					for ( int i = 0 ; i < strlen(str) ; i++ )	
					{
						sys.m_scrn_buf[spos+i] = str[i];	
					}
						y++;	spos = y*sys.m_scrn_W+x;
				}
			}

			//	disp address
			{
				char	str[256];
				sprintf(str, "%04X", adr );

				sys.m_scrn_buf[spos+0] = str[0];
				sys.m_scrn_buf[spos+1] = str[1];
				sys.m_scrn_buf[spos+2] = str[2];
				sys.m_scrn_buf[spos+3] = str[3];

				x+=5;
			}


			continue;
		}

		{

			if (  bpos < m_buf_lenData )
			{
				int	c = m_buf_pBuf[bpos];
				{
					if ( x < sys.m_scrn_W )
					{
						int	h = (c >>4) & 0x0f;
						int	l = (c    ) & 0x0f;

						{
							sys.m_scrn_buf[spos  ] = b2hex( h );
							sys.m_scrn_buf[spos+1] = b2hex( l );
						}
						x+=2;
					}
				}
			}


			cnt++;


			if ( ( cnt % 1 ) == 0 )
			{
				sys.m_scrn_buf[spos+2] = ' ';
				x++;
			}
//			if ( m_flgInputbuf == false);


			if ( bpos < m_buf_lenData )
			if ( ( cnt % 16 ) == 0 )
			{
				//	horizonal Sum
				int	sum = 0 ;
				for ( int i = 0 ; i < 16 ; i++ )
				{
					sum += m_buf_pBuf[bpos-i];
				}
				sumv += sum;
				{
					int	h = (sum >>4) & 0x0f;
					int	l = (sum    ) & 0x0f;
					sys.m_scrn_buf[spos+3] = ':';
					sys.m_scrn_buf[spos+4] = b2hex( h );
					sys.m_scrn_buf[spos+5] = b2hex( l );
				}
				
				x = 0;
				y++;
			}

	
		}


			// for inputbuf
		if ( m_adrInputbuf == bpos )
		{

			{


				{
					{
						if ( m_cntInputbuf == 1 )
						{
							int	h = (m_charInputbuf >>4) & 0x0f;
							sys.m_scrn_buf[spos+0] = b2hex( h );
						}
						else
						if ( m_cntInputbuf == 2 )
						{
							int	l = (m_charInputbuf    ) & 0x0f;
							sys.m_scrn_buf[spos+1] = b2hex( l );
						}

						if ( (m_time & 0x10) == 0)
						{
							sys.m_scrn_buf[spos+m_cntInputbuf] = '_';
						}
					}
				}
			}
		}


		bpos++;


		//	virtical Sum
		if ( x == 0 )
		{
			spos = y*sys.m_scrn_W+x;
			int	adr = bpos+m_ofs_adr;
			if ( (adr & 0x00ff ) == 0x00 )
			{
				char	str[256];
				sprintf(str, "---------------------------------------------------------" );
				for ( int i = 0 ; i < strlen(str) ; i++ )	
				{
					sys.m_scrn_buf[spos+i] = str[i];
				}
						y++;	spos = y*sys.m_scrn_W+x;

				sprintf(str, "Sum " );

				sumh = 0;
				for ( int j = 0 ; j < 16 ; j++ )
				{
					int	sum = 0 ;
					for ( int i = 0 ; i < 16 ; i++ )
					{
						sum += m_buf_pBuf[bpos-i*16-16 + j];
					}
					sumh += sum;
					sprintf(str, "%s %02X", str, sum&0xff );
				}
					sprintf(str, "%s :%02X(%02X)", str, sumv&0xff, sumh&0xff );



				for ( int i = 0 ; i < strlen(str) ; i++ )	
				{
					sys.m_scrn_buf[spos+i] = str[i];
				}
						y++;	spos = y*sys.m_scrn_W+x;


			}
		}


	}




}

//-----------------------------------------------------------------------------
Ed::~Ed()
//-----------------------------------------------------------------------------
{
	if ( m_buf_pBuf ) free( m_buf_pBuf );
}
//-----------------------------------------------------------------------------
Ed::Ed()
//-----------------------------------------------------------------------------
{

	m_flgInputbuf = false;
	m_charInputbuf = 0;
	m_cntInputbuf = 0;
	m_adrInputbuf = 0;

	m_flgInsert = false;

	m_filename[0]	=0;
//	m_buf_lenInput	=0;
	m_buf_lenData	=0;
	m_buf_colum		=0;
	m_buf_cpos		=0;
	m_buf_lenBuf	=0;
	m_buf_pBuf		=0;
	m_ofs_line 		=0;
	m_ofs_column	=0;
m_ofs_adr = 0;
//m_cntHex = 0;
m_time = 0x00;
//m_buf_prev_cpos		=0;
m_flgHexMode = false;

	m_buf_lenBuf = 1000*1024;
	m_buf_pBuf = (char*)malloc( m_buf_lenBuf );
	memset( m_buf_pBuf, 0, m_buf_lenBuf );

	cls();

//	buf_openInputbuf(0);
}
//-----------------------------------------------------------------------------
void Ed::SaveFile()
//-----------------------------------------------------------------------------
{
						File::file_Save( m_filename, m_buf_pBuf, m_buf_lenData );
}

//-----------------------------------------------------------------------------
void Ed::LoadFile( const char* fname )
//-----------------------------------------------------------------------------
{

	{
		strcpy( m_filename, fname );
		printf("[%s]\n", fname );

		File::file_Load( fname, m_buf_pBuf, m_buf_lenBuf, &m_buf_lenData );
		printf(" size = %d\n", m_buf_lenData);
	}
}

//-----------------------------------------------------------------------------
void Ed::UpdateScreen()
//-----------------------------------------------------------------------------
{
	if ( m_flgHexMode )
	{
		hex_DecodeScreen( 0xc000 );
	}
	else
	{
		DecodeScreen();
	}
}
//-----------------------------------------------------------------------------
void Ed::DecodeScreen()
//-----------------------------------------------------------------------------
{

		if ( m_buf_cpos < 0 ) m_buf_cpos = 0;
		if ( m_buf_cpos >= m_buf_lenData ) m_buf_cpos = m_buf_lenData;

		//	normalize	offset line
		{
			int	y = buf_GetCurY( m_buf_cpos );
			if ( y >= m_ofs_line+sys.m_scrn_H-4 ) 
			{
				m_ofs_line++;
			}
		}
		{
			int	y = buf_GetCurY( m_buf_cpos );
			if ( y < m_ofs_line+4 ) 
			{
				m_ofs_line--;
			}
		}
		if ( m_ofs_line >= buf_GetCntLF() ) m_ofs_line = buf_GetCntLF()-1;
		if ( m_ofs_line < 0 ) m_ofs_line = 0;

		//	normalize	offset column
		{
			int	x = buf_GetCurX( m_buf_cpos );
			if ( x >= m_ofs_column+sys.m_scrn_W-4 ) 
			{
				m_ofs_column++;
			}
		}
		{
			int	x = buf_GetCurX( m_buf_cpos );
			if ( x < m_ofs_column+4 ) 
			{
				m_ofs_column--;
			}
		}
		if ( m_ofs_column < 0 ) m_ofs_column = 0;


		buf_DecodeScrn( m_ofs_line, m_ofs_column );
}
//-----------------------------------------------------------------------------
void Ed::hex_DecodeScreen( int adr )
//-----------------------------------------------------------------------------
{

		if ( m_buf_cpos < 0 ) m_buf_cpos = 0;
		if ( m_buf_cpos >= m_buf_lenData ) m_buf_cpos = m_buf_lenData;
//printf("%d %d\n", m_buf_cpos, m_buf_lenData*2);
		//	normalize	offset line
		{
			int	y = m_buf_cpos / 16;
			if ( y >= m_ofs_line+sys.m_scrn_H-8 ) 
			{
				m_ofs_line++;
			}
		}
		{
			int	y = m_buf_cpos / 16;
			if ( y < m_ofs_line+4 ) 
			{
				m_ofs_line--;
			}
		}
		if ( m_ofs_line >= m_buf_lenData/16 ) m_ofs_line = m_buf_lenData/16;
		if ( m_ofs_line < 0 ) m_ofs_line = 0;



		m_ofs_adr = adr;


	buf_openInputbuf(0);

		buf_hex_DecodeScrn( m_ofs_line, m_ofs_column );

//	m_buf_prev_cpos = m_buf_cpos;
}

//-----------------------------------------------------------------------------
int	ishex( const int c )
//-----------------------------------------------------------------------------
{
	bool	a = false;

		switch ( c )
		{
			case '0':			a = true; break;
			case '1':			a = true; break;
			case '2':			a = true; break;
			case '3':			a = true; break;
			case '4':			a = true; break;
			case '5':			a = true; break;
			case '6':			a = true; break;
			case '7':			a = true; break;
			case '8':			a = true; break;
			case '9':			a = true; break;
			case 'a':case 'A':	a = true; break;
			case 'b':case 'B':	a = true; break;
			case 'c':case 'C':	a = true; break;
			case 'd':case 'D':	a = true; break;
			case 'e':case 'E':	a = true; break;
			case 'f':case 'F':	a = true; break;
		}
	return a;
}

//-----------------------------------------------------------------------------
void Ed::Request( REQUEST t, int c )
//-----------------------------------------------------------------------------
{
	switch( t )
	{
	case INSERT:
		if ( m_flgHexMode )
		{
					if ( c == '\n' )	buf_input_enter();
					else
					if ( c == '\b' )	buf_input_bs();
					else
					if ( ishex(c) )
					{
						buf_input_hex( m_buf_cpos, c );
					}
					else
					if ( isgraph(c) )
					{
						buf_input_hex( m_buf_cpos, 0 );
					}
		}
		else
		{
					if ( c == '\b' )	buf_bs();
					else
					if ( isgraph(c) || c == ' ' || c == '\n' || c == '\b' )
					{
						buf_insert( m_buf_cpos, c ); break;
					}
		}
		break;
	case CHANGE_INSERT: m_flgInsert = !m_flgInsert; break;
//	case INPUT_HEX:		
//					break;
//	case INPUT_ENTER:	buf_input_enter(); break;
//	case INPUT_BS:		buf_input_bs(); break;
	default:	printf("error\n");break;
	}
}
/*
//-----------------------------------------------------------------------------
void Ed::Insert( int c )
//-----------------------------------------------------------------------------
{

		buf_insert( m_buf_cpos, c );
						
}
*/
//-----------------------------------------------------------------------------
void Ed::buf_moveRollUp( int n )
//-----------------------------------------------------------------------------
{
	if ( m_flgHexMode )
	{
		buf_moveAddTo(-16*16);
	}
	else
	{

						m_ofs_line-=n;
						for ( int i = 0 ; i < n ; i++ ) buf_moveUp();
	}

}
//-----------------------------------------------------------------------------
void Ed::buf_moveRollDown( int n )
//-----------------------------------------------------------------------------
{
	if ( m_flgHexMode )
	{
		buf_moveAddTo(16*16);
	}
	else
	{
						m_ofs_line+=n;
						for ( int i = 0 ; i < n ; i++ ) buf_moveDown();
	}
}
//-----------------------------------------------------------------------------
void Ed::ModeChange()
//-----------------------------------------------------------------------------
{
	m_flgHexMode = !m_flgHexMode;
}
