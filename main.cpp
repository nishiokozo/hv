#include <sys.h>
#include "ed.h"
#include "pcg.h"

Sys	sys( "env.ini" );

Bmp	bmpfont("font.bmp");


enum
{
	PSG_0,
	PSG_1,
	PSG_2,
	PSG_3,
	PSG_4,
	PSG_5,
	PSG_noise_06,
	PSG_mixer_07,
	PSG_volA_08,
	PSG_volB_09,
	PSG_volC_0A,	//0A
	PSG_envLo_0B,	//0B
	PSG_envHi_0A,	//0C
	PSG_wave_0D,	//0D
	PSG_14,	//0E
	PSG_15,	//0F
};

int	cnt_sp = 0;

int	m1,m2,m3,m4;

int	cl = 0;
long long	cl2 = 0;
long long	cl3 = 0;
#if 0
	#define	GOS(cmd)		cmd
	#define	RET(cmd)		cmd
#else
	#define	GOS(cmd)		\
	{\
		int sp1 = cnt_sp;\
		int sp2 = cntSP;\
		if(flgTrace)printf("st.gos.%d) %d %d\n", __LINE__, cnt_sp, cntSP );\
		cnt_sp++;\
		if (cnt_sp>255){printf("stop at GOS %d in %d at %s\n",cnt_sp, __LINE__,__FILE__ ); exit(0);}\
		{\
			cmd\
		}\
		if(flgTrace)printf("en.gos.%d) %d %d %c\n", __LINE__, cnt_sp, cntSP, (sp1!=cnt_sp||sp2!=cntSP)?'X':'-' );\
	}
	#define	RET(cmd)		{cnt_sp--;if (cnt_sp<0  )exit(0);cmd;}
#endif

unsigned	char	IO[0xffff];
unsigned	char	MEM[0xffff];


int		a;
int		_a;

int	tblSP[256];
int*	SP = tblSP;

#if 1
//int		tblAdr[256];
//int*	sp = tblAdr;
	int*	tblAdr[256];
	int**	sp = tblAdr;
#else
int&	sp = SP;
#endif

#if 0
unsigned	char	A,B,C,D,E,H,L;
unsigned	char	_A,_B_,_C_,_D,_E,_H,_L_;
unsigned	char	XH,XL;
unsigned	char	YH,YL;
#else

enum
{
	AFH,
	AFL,
	BCH,
	BCL,
	DEH,
	DEL,
	HLH,
	HLL,
	IXH,
	IXL,
	IYH,
	IYL,
	_AFH,
	_AFL,
	_BCH,
	_BCL,
	_DEH,
	_DEL,
	_HLH,
	_HLL,

	REG_MAX
};
unsigned char	reg[REG_MAX];
unsigned char	raf[4]={0,0,0,0};
unsigned char	rbc[4]={0,0,0,0};
unsigned char	rde[4]={0,0,0,0};
unsigned char	rhl[4]={0,0,0,0};
unsigned char	rix[4]={0,0,0,0};
unsigned char	riy[4]={0,0,0,0};

struct FLAG
{
	unsigned char	f1 : 1;
	unsigned char	Z : 1;
	unsigned char	f3 : 1;
	unsigned char	f4 : 1;
	unsigned char	f5 : 1;
	unsigned char	C : 1;
	unsigned char	f7 : 1;
	unsigned char	f8 : 1;
};
FLAG	aa;
bool	fc,fz;

unsigned char&	 A = raf[1];
FLAG&	 		 F = *((FLAG*)&raf[0]);
unsigned short&  AF = ((unsigned short*)raf)[0];

unsigned char&	 B = rbc[1];
unsigned char&	 C = rbc[0];
unsigned short&  BC = ((unsigned short*)rbc)[0];

unsigned char&	 D = rde[1];
unsigned char&	 E = rde[0];
unsigned short&  DE = ((unsigned short*)rde)[0];

unsigned char&	 H = rhl[1];
unsigned char&	 L = rhl[0];
unsigned short&  HL = ((unsigned short*)rhl)[0];

unsigned char&	 XH = rix[1];
unsigned char&	 XL = rix[0];
unsigned short&  IX = ((unsigned short*)rix)[0];

unsigned char&	 YH = riy[1];
unsigned char&	 YL = riy[0];
unsigned short&  IY = ((unsigned short*)riy)[0];

unsigned char&	 _A = reg[_AFH];
FLAG&	 		 _F = *((FLAG*)&reg[_AFH]);
//unsigned char&	 _F = reg[_AFL];
unsigned short&  _AF = ((unsigned short*)reg)[_AFL];

unsigned char&	 _B_ = reg[_BCH];
unsigned char&	 _C_ = reg[_BCL];
unsigned short&  _BC = ((unsigned short*)reg)[_BCL];

unsigned char&	 _D = reg[_DEH];
unsigned char&	 _E = reg[_DEL];
unsigned short&  _DE = ((unsigned short*)reg)[_DEL];

unsigned char&	 _H = reg[_HLH];
unsigned char&	 _L_ = reg[_HLL];
unsigned short&  _HL = ((unsigned short*)reg)[_HLL];

#endif




int	maxSP = 0;
int	cntSP = 0;
void decSP(int line)
{
	--cntSP;
	if ( cntSP < 0 ) 
	{
		printf("SP ERROR DEC %d max =%d",line ,maxSP );
		exit(1);
	}
}
void incSP(int line)
{

	cntSP++;

	if ( maxSP < cntSP ) maxSP = cntSP;

	if ( cntSP >255 ) 
	{
		printf("SP ERROR INC %d max =%d",line, maxSP );
		exit(1);
	}
}

unsigned	char	g_text[255][255];

unsigned char*	RM001F = &MEM[0x001f];	//	IOCS

unsigned char*	RMB600 = &MEM[0xb600];
unsigned char*	RMB601 = &MEM[0xB601];
unsigned char*	RMB602 = &MEM[0xB602];
unsigned char*	RMB603 = &MEM[0xB603];
unsigned char*	RMB604 = &MEM[0xB604];
unsigned char*	RMB605 = &MEM[0xB605];
unsigned char*	RMB606 = &MEM[0xB606];
unsigned char*	RMB607 = &MEM[0xB607];
unsigned char*	RMB608 = &MEM[0xB608];
unsigned char*	RMB609 = &MEM[0xB609];
unsigned char*	RMB60A = &MEM[0xB60A];
unsigned char*	RMB60B = &MEM[0xB60B];
unsigned char*	RMB60C = &MEM[0xB60C];
unsigned char*	RMB60D = &MEM[0xB60D];
unsigned char*	RMB60E = &MEM[0xB60E];
unsigned char*	RMB60F = &MEM[0xB60F];

unsigned char*	RMB610 = &MEM[0xb610];
unsigned char*	RMB611 = &MEM[0xB611];
unsigned char*	RMB612 = &MEM[0xB612];
unsigned char*	RMB613 = &MEM[0xB613];
unsigned char*	RMB614 = &MEM[0xB614];
unsigned char*	RMB615 = &MEM[0xB615];
unsigned char*	RMB616 = &MEM[0xB616];
unsigned char*	RMB617 = &MEM[0xB617];
unsigned char*	RMB618 = &MEM[0xB618];
unsigned char*	RMB619 = &MEM[0xB619];
unsigned char*	RMB61A = &MEM[0xB61A];
unsigned char*	RMB61B = &MEM[0xB61B];
unsigned char*	RMB61C = &MEM[0xB61C];
unsigned char*	RMB61D = &MEM[0xB61D];
unsigned char*	RMB61E = &MEM[0xB61E];
unsigned char*	RMB61F = &MEM[0xB61F];

unsigned char*	RMD100 = &MEM[0xD100];

			static	bool g_flgMap = false;


//-----------------------------------------------------------------------------
void	InitX1()
//-----------------------------------------------------------------------------
{
	for ( int i = 0 ;  i < 0xffff ; i++ )
	{
		IO[i]	= 0;
		MEM[i]	= 0;
	}
	for ( int i = 0 ;  i < 0xff ; i++ )
	{
		tblAdr[i] = 0;
		tblSP[i] = 0;
	}

	A=B=C=D=E=H=L = 0;
	_A=_B_=_C_=_D=_E=_H=_L_ = 0;
	XH=XL = 0;
	YH=YL = 0;

	a= 0;

	sp = tblAdr;
	SP = tblSP;

	memset( reg, 0, sizeof(reg) );


	F.Z = false;
	F.C = false;

	int	len = 0;
	File::file_Load( "hv.bin", (char*)&MEM[0xC000], 0xffff, &len );
//	printf(" hv.len = %d\n", len );


}
static	bool flgTrace = false;
void	tron() {flgTrace=true;}
void	troff() {flgTrace=false;}

void p( const char* str )
{
	if ( flgTrace ) printf("%2d)%2d)%s\n", cnt_sp,cntSP,str );
}
//-----------------------------------------------------------------------------
void DrawPatternOnBitmap( int px, int py, int* tblPattern, int cntPattern )
//-----------------------------------------------------------------------------
{
					{
						int s = 0;
						int x = 0;
						int y = 0;
						while ( s < cntPattern )
						{
							{
								int r = tblPattern[s];
								for ( int i = 0; i < 8; i++ )
								{
									int a = (r << i)&0x80; 
									
									if ( a < 0.0 ) a = 0.0;
									if ( a > 1.0 ) a = 1.0;
									if ( a ) sys.pGram->PutColor( px+x*8+i , py+y, a, a, a );
								}
							}
							y++;
							if ( y >= 8 )
							{
								y = 0;
								x++;
							}
							s++;
						}
					}
}
//-----------------------------------------------------------------------------
void DrawScreen()
//-----------------------------------------------------------------------------
{

#define	IS_LT_C0_SKY(n)		((n) < 0xC0)
			
			if (!g_flgMap)
			{
				for ( unsigned int y = 0 ; y < 25 ; y++ )
				{
					for ( unsigned int x = 0 ; x < 40 ; x++ )
					{
						unsigned int a = g_text[y][x];
						pcg_DrawChar( (*sys.pGram), x*8, y*8, a );
					}
				}

				{
					for ( int y = 0; y < 200; y++ )
					{
						for ( int x = 0; x < 40; x++ )
						{
							int r = IO[ 0xc000 +  (x/1) + ((y & 7)<<11) + ((y/8)*40) ];
							for ( int i = 0; i < 8; i++ )
							{
								int a = (r << i)&0x80; 
								
								if ( a < 0.0 ) a = 0.0;
								if ( a > 1.0 ) a = 1.0;
								if ( a ) sys.pGram->PutColor( x*8+i , y, a, a, a );
							}
						}
					}
				}
				{ // HOVER
					int tblPattern[] = {0x11,0x11,0x22,0x22,0x7c,0x44,0x89,0x89,0x3e,0x22,0x44,0x44,0x88,0x88,0x10,0xf0,0x81,0x82,0x84,0x88,0x91,0xa1,0xc2,0x83,0x7d,0x41,0x82,0x82,0xf7,0x05,0x08,0xe8,0xf0,0x10,0x20,0x20,0xc0,0x00,0x80,0x80};
					int cntPattern = sizeof(tblPattern)/sizeof(int);
					DrawPatternOnBitmap( 224,72,tblPattern,cntPattern );
				}
				{// MISSILE
					int tblPattern[] = {0x08,0x19,0x19,0x2a,0x2a,0x4c,0x4c,0x88,0x87,0x82,0x84,0x84,0x89,0x88,0x90,0xbb,0x7d,0x41,0x82,0x82,0xf7,0x10,0x20,0xef,0xf7,0x02,0x04,0x04,0xc9,0x49,0x92,0xbb,0x41,0x41,0x82,0x82,0x07,0x04,0x08,0xef,0xf0,0x00,0x00,0x00,0xc0,0x00,0x00,0x80};
					int cntPattern = sizeof(tblPattern)/sizeof(int);
					DrawPatternOnBitmap( 224,88,tblPattern,cntPattern );
				}
				{// FIGHTER
					int tblPattern[] = {
					0x1f,0x10,0x20,0x20,0x7c,0x40,0x81,0x83,
					0x77,0x24,0x48,0x48,0x93,0x91,0x22,0xbe,
					0xc8,0x48,0x91,0x11,0x3e,0x22,0x44,0x44,
					0xbe,0x88,0x11,0x11,0x23,0x22,0x44,0x47,
					0xfb,0x82,0x04,0x04,0x7f,0x0a,0x11,0xd1,
					0xe0,0x20,0x40,0x40,0x80};
					int cntPattern = sizeof(tblPattern)/sizeof(int);
					DrawPatternOnBitmap( 224,104,tblPattern,cntPattern );
				}
				{// CARRIER
					int tblPattern[] = {0x1f,0x10,0x20,0x20,0x40,0x40,0x81,0xfa,0x04,0x0c,0x14,0x24,0x44,0xfc,0x05,0x05,0x3e,0x22,0x44,0x44,0xf9,0xa1,0x12,0x12,0x7d,0x44,0x89,0x89,0xf2,0x42,0x24,0x2e,0xdf,0xa0,0x20,0x20,0x7d,0x41,0x82,0xfa,0x7c,0x44,0x88,0x88,0xf0,0x40,0x20,0x20};
					int cntPattern = sizeof(tblPattern)/sizeof(int);
					DrawPatternOnBitmap( 224,120,tblPattern,cntPattern );
				}
				{// SCORE
					int tblPattern[] = {0x1f,0x10,0x20,0x20,0x7c,0x04,0x09,0xf9,0x3e,0x20,0x41,0x41,0x82,0x82,0x04,0xf7,0xf9,0x89,0x12,0x12,0x27,0x25,0x48,0xc8,0xf3,0x12,0x24,0x24,0xcf,0x08,0x90,0x9f,0xe0,0x00,0x00,0x00,0x80};
					int cntPattern = sizeof(tblPattern)/sizeof(int);
					DrawPatternOnBitmap( 224,136,tblPattern,cntPattern );
				}
				{// 0
					int tblPattern[] = {0x00,0x3e,0x22,0x44,0x44,0x88,0xf8,0x00};
					int cntPattern = sizeof(tblPattern)/sizeof(int);
					DrawPatternOnBitmap( 288,144,tblPattern,cntPattern );
				}

			}


//g_flgMap = true;
			if (g_flgMap)
			{
				for ( unsigned int y = 64 ; y < 192 ; y++ )
				{
					for ( unsigned int x = 0 ; x < 256 ; x++ )
					{
int	px = 32;
int	py = -32;
						unsigned int	a = IO[y*256+x];
						if ( a > 0 && IS_LT_C0_SKY(a) ) 
						{
							sys.pGram->PutColor( x+px, y+py, 0.5, 1, 1 );
						}
						else
						if ( a >= 0xfb  )
						{
							sys.pGram->PutColor( x+px, y+py, 0.5, 0, 0 );
						}
						else
						if ( a )
						{
							sys.pGram->PutColor( x+px, y+py, 1, 1, 0 );
						}
						else
						{
							sys.pGram->PutColor( x+px, y+py, 0, 0, 0 );
						}

					}
				}
			}


}

int InputJoystick()
{
	int A = 0;																				 		 		 		 		 		 ////c:A = 0;

	float p = sqrtf( sys.
	joy0.Ly*sys.joy0.Ly + sys.joy0.Lx*sys.joy0.Lx );
	float r = (atan2( sys.joy0.Ly, sys.joy0.Lx )+pi)/2.0f/pi;

	int	d = r*8+0.5;
	if ( d >= 8 ) d = 0;

	if ( p > 0.3 )
	{
		switch(d)
		{
			case 0:A |= (1<<2);
				break;
			case 1:A |= (1<<2)|(1<<2);
				break;
			case 2:A |= (1<<1);
				break;
			case 3:A |= (1<<1)|(1<<3);
				break;
			case 4:A |= (1<<3);
				break;
			case 5:A |= (1<<3)|(1<<0);
				break;
			case 6:A |= (1<<0);
				break;
			case 7:A |= (1<<0)|(1<<2);
				break;
			default:
			printf( "ana stick err\n");
		}
	

	}

	if ( sys.joy0.hi.L2 ) g_flgMap = !g_flgMap ;

	if ( sys.key.now(VK_UP)) A |= (1<<0);										////c: 	if ( sys.key.now(VK_UP)) A |= (1<<0);
	if ( sys.key.now(VK_DOWN)	) A |= (1<<1);									////c:	if ( sys.key.now(VK_DOWN)	) A |= (1<<1);
	if ( sys.key.now(VK_LEFT)	) A |= (1<<2);									////c:	if ( sys.key.now(VK_LEFT)	) A |= (1<<2);
	if ( sys.key.now(VK_RIGHT) ) A |= (1<<3);									////c:	if ( sys.key.now(VK_RIGHT) ) A |= (1<<3);
	if ( sys.joy0.now.Lu ) A |= (1<<0);											////c: 	if ( sys.key.now(VK_UP)) A |= (1<<0);
	if ( sys.joy0.now.Ld ) A |= (1<<1);											////c:	if ( sys.key.now(VK_DOWN)	) A |= (1<<1);
	if ( sys.joy0.now.Ll ) A |= (1<<2);											////c:	if ( sys.key.now(VK_LEFT)	) A |= (1<<2);
	if ( sys.joy0.now.Lr ) A |= (1<<3);											////c:	if ( sys.key.now(VK_RIGHT) ) A |= (1<<3);


	return ~A;
}

//-----------------------------------------------------------------------------
void	PutTitle()
//-----------------------------------------------------------------------------
{
		Bmp	title( "hv-title.bmp" );

		bool	flgLoop = true;


		while(sys.pWin1->FlgActive && flgLoop)
		{

			sys.Clear();

			int a = sys.Input();

			if ( a != 0 || sys.joy0.hi.St || sys.joy0.hi.Ru || sys.joy0.hi.Rd || sys.joy0.hi.Rl || sys.joy0.hi.Rr  ) 
			{
				flgLoop = false;
			}

//			sys_draw( title );
//				sys.pWin1->SwapBuffer();

			sys.pGram->Load( title.m_pBuf, title.m_width, title.m_height  );
			sys.Draw();

		}
}

//-----------------------------------------------------------------------------
void	PutExplain()
//-----------------------------------------------------------------------------
{

		bool	flgLoop = true;

		
		flgLoop = true;
		while(sys.pWin1->FlgActive && flgLoop)
		{
			int a = sys.Input();

#if 0
			if ( sys.joy0.hi.L1 )
			{	
							sys.sound.mml_play( "T100V15o4c3-g#dcfc#dcc7R:V15O3#D5F#GGG7R:V15O2G7GGR" );
			}
			else
			if ( sys.joy0.hi.L2 )
			{
							sys.sound.mml_play( "T100V15o4c1-gcfcfgdg+c7r:v11o3g1eg+ca+c+db+d+g7r:v11o3e1ceafabgb+e7r");
			}
			else
#endif
			if ( a != 0 || sys.joy0.hi.St || sys.joy0.hi.Ru || sys.joy0.hi.Rd || sys.joy0.hi.Rl || sys.joy0.hi.Rr  ) 
			{
				flgLoop = false;
			}

				{                             ////c:		{
			sys.Clear();
//					sys.pGram->Clear();

//					sys.m_pFont->Color(1,1,1);
					int	x = 5;
					int	y = 2;
					sys.font_Printc( *sys.pGram,  x+0, y, 'T' );
					sys.font_Printc( *sys.pGram,  x+1, y, 'E' );
					sys.font_Printc( *sys.pGram,  x+2, y, 'N' );
					sys.font_Printc( *sys.pGram,  x+3, y, 'K' );
					sys.font_Printc( *sys.pGram,  x+4, y, 'E' );
					sys.font_Printc( *sys.pGram,  x+5, y, 'Y' );

					sys.font_Printc( *sys.pGram,  x+7 , y , 'o' );
					sys.font_Printc( *sys.pGram,  x+8 , y , 'r' );

					sys.font_Printc( *sys.pGram,  x+10 , y , 'T' );
					sys.font_Printc( *sys.pGram,  x+11 , y , 'R' );
					sys.font_Printc( *sys.pGram,  x+12 , y , 'I' );
					sys.font_Printc( *sys.pGram,  x+13 , y , 'G' );
					sys.font_Printc( *sys.pGram,  x+14 , y , 'G' );
					sys.font_Printc( *sys.pGram,  x+15 , y , 'E' );
					sys.font_Printc( *sys.pGram,  x+16 , y , 'R' );

					y++;
					y++;

					pcg_DrawChar( (*sys.pGram), (x+1)*8,  y*8, 'I' );
					pcg_DrawChar( (*sys.pGram), (x+13)*8, y*8, 'A' );
					pcg_DrawChar( (*sys.pGram), (x+14)*8, y*8, 'Q' );
					y++;

					pcg_DrawChar( (*sys.pGram), (x+12)*8, y*8, 'i' );
					pcg_DrawChar( (*sys.pGram), (x+13)*8, y*8, 'D' );
					pcg_DrawChar( (*sys.pGram), (x+14)*8, y*8, 'T' );
					pcg_DrawChar( (*sys.pGram), (x+15)*8, y*8, 'l' );
					y++;

					pcg_DrawChar( (*sys.pGram), (x+12)*8, y*8, 'y' );
					pcg_DrawChar( (*sys.pGram), (x+13)*8, y*8, 'z' );
					pcg_DrawChar( (*sys.pGram), (x+14)*8, y*8, '{' );
					pcg_DrawChar( (*sys.pGram), (x+15)*8, y*8, '|' );
					y++;

					pcg_DrawChar( (*sys.pGram), (x+ 1)*8, y*8, 'J' );
					pcg_DrawChar( (*sys.pGram), (x+ 4)*8, y*8, 'A' );
					pcg_DrawChar( (*sys.pGram), (x+ 5)*8, y*8, 'Q' );
					y++;

					pcg_DrawChar( (*sys.pGram), (x+ 4)*8, y*8, 'D' );
					pcg_DrawChar( (*sys.pGram), (x+ 5)*8, y*8, 'T' );
					pcg_DrawChar( (*sys.pGram), (x+12)*8, y*8, 'i' );
					pcg_DrawChar( (*sys.pGram), (x+13)*8, y*8, 'j' );
					pcg_DrawChar( (*sys.pGram), (x+14)*8, y*8, 'k' );
					pcg_DrawChar( (*sys.pGram), (x+15)*8, y*8, 'l' );
					y++;
					pcg_DrawChar( (*sys.pGram), (x+12)*8, y*8, 'y' );
					pcg_DrawChar( (*sys.pGram), (x+13)*8, y*8, 'z' );
					pcg_DrawChar( (*sys.pGram), (x+14)*8, y*8, '{' );
					pcg_DrawChar( (*sys.pGram), (x+15)*8, y*8, '|' );
					y++;

					pcg_DrawChar( (*sys.pGram), (x+ 1)*8, y*8, 'K' );
					y++;

					x = 3;
					y = 4;
					sys.font_Printc( *sys.pGram,  x+0 , y+0, '7' );
					sys.font_Printc( *sys.pGram,  x+1 , y+0, '.' );
					sys.font_Printc( *sys.pGram,  x+2 , y+0, '.' );
					sys.font_Printc( *sys.pGram,  x+0 , y+3, '4' );
					sys.font_Printc( *sys.pGram,  x+1 , y+3, '.' );
					sys.font_Printc( *sys.pGram,  x+2 , y+3, '.' );
					sys.font_Printc( *sys.pGram,  x+0 , y+6, '1' );
					sys.font_Printc( *sys.pGram,  x+1 , y+6, '.' );
					sys.font_Printc( *sys.pGram,  x+2 , y+6, '.' );

					sys.font_Printc( *sys.pGram,  x-2 , y+0, 'C' );
					sys.font_Printc( *sys.pGram,  x-2 , y+3, 'X' );
					sys.font_Printc( *sys.pGram,  x-2 , y+6, 'Z' );

					x = 20;
					y = 4;
					sys.font_Printc( *sys.pGram,  x+5 , y+1, '.' );
					sys.font_Printc( *sys.pGram,  x+6 , y+1, '.' );
					sys.font_Printc( *sys.pGram,  x+7 , y+1, '8' );
					sys.font_Printc( *sys.pGram,  x+5,  y+4, '.' );
					sys.font_Printc( *sys.pGram,  x+6,  y+4, '.' );
					sys.font_Printc( *sys.pGram,  x+7,  y+4, '2' );


					x = 21;
					y = 5;
					sys.font_Printc( *sys.pGram,  x+9  , y, 'S' );
					sys.font_Printc( *sys.pGram,  x+10 , y, 'P' );
					sys.font_Printc( *sys.pGram,  x+11 , y, 'A' );
					sys.font_Printc( *sys.pGram,  x+12 , y, 'C' );
					sys.font_Printc( *sys.pGram,  x+13 , y, 'E' );

					x = 21;
					y = 8;
					sys.font_Printc( *sys.pGram,  x+9  , y, 'S' );
					sys.font_Printc( *sys.pGram,  x+10 , y, 'P' );
					sys.font_Printc( *sys.pGram,  x+11 , y, 'A' );
					sys.font_Printc( *sys.pGram,  x+12 , y, 'C' );
					sys.font_Printc( *sys.pGram,  x+13 , y, 'E' );

					x = 5;
					y = 17;
					sys.font_Printc( *sys.pGram,  x+ 0 , y, 'J' );
					sys.font_Printc( *sys.pGram,  x+ 1 , y, 'O' );
					sys.font_Printc( *sys.pGram,  x+ 2 , y, 'Y' );
					sys.font_Printc( *sys.pGram,  x+ 3 , y, 'S' );
					sys.font_Printc( *sys.pGram,  x+ 4 , y, 'T' );
					sys.font_Printc( *sys.pGram,  x+ 5 , y, 'I' );
					sys.font_Printc( *sys.pGram,  x+ 6 , y, 'C' );
					sys.font_Printc( *sys.pGram,  x+ 7 , y, 'K' );
					sys.font_Printc( *sys.pGram,  x+ 8 , y, ' ' );
					sys.font_Printc( *sys.pGram,  x+ 9 , y, '.' );
					sys.font_Printc( *sys.pGram,  x+10 , y, '.' );
					sys.font_Printc( *sys.pGram,  x+11 , y, ' ' );
					sys.font_Printc( *sys.pGram,  x+12 , y, 'M' );
					sys.font_Printc( *sys.pGram,  x+13 , y, 'O' );
					sys.font_Printc( *sys.pGram,  x+14 , y, 'V' );
					sys.font_Printc( *sys.pGram,  x+15 , y, 'E' );


					x = 5;
					y = 18;
					sys.font_Printc( *sys.pGram,  x+ 0 , y, ' ' );
					sys.font_Printc( *sys.pGram,  x+ 1 , y, 'T' );
					sys.font_Printc( *sys.pGram,  x+ 2 , y, 'R' );
					sys.font_Printc( *sys.pGram,  x+ 3 , y, 'I' );
					sys.font_Printc( *sys.pGram,  x+ 4 , y, 'G' );
					sys.font_Printc( *sys.pGram,  x+ 5 , y, 'G' );
					sys.font_Printc( *sys.pGram,  x+ 6 , y, 'E' );
					sys.font_Printc( *sys.pGram,  x+ 7 , y, 'R' );
					sys.font_Printc( *sys.pGram,  x+ 8 , y, ' ' );
					sys.font_Printc( *sys.pGram,  x+ 9 , y, '.' );
					sys.font_Printc( *sys.pGram,  x+10 , y, '.' );
					sys.font_Printc( *sys.pGram,  x+11 , y, ' ' );
					sys.font_Printc( *sys.pGram,  x+12 , y, 'A' );
					sys.font_Printc( *sys.pGram,  x+13 , y, 'T' );
					sys.font_Printc( *sys.pGram,  x+14 , y, 'T' );
					sys.font_Printc( *sys.pGram,  x+15 , y, 'A' );
					sys.font_Printc( *sys.pGram,  x+16 , y, 'C' );
					sys.font_Printc( *sys.pGram,  x+17 , y, 'K' );


					x = 5;
					y = 13;
					sys.font_Printc( *sys.pGram,  x+ 0 , y, 'C' );
					sys.font_Printc( *sys.pGram,  x+ 1 , y, 'U' );
					sys.font_Printc( *sys.pGram,  x+ 2 , y, 'R' );
					sys.font_Printc( *sys.pGram,  x+ 3 , y, 'S' );
					sys.font_Printc( *sys.pGram,  x+ 4 , y, 'O' );
					sys.font_Printc( *sys.pGram,  x+ 5 , y, 'R' );
					sys.font_Printc( *sys.pGram,  x+ 6 , y, ' ' );
					sys.font_Printc( *sys.pGram,  x+ 7 , y, '.' );
					sys.font_Printc( *sys.pGram,  x+ 8 , y, '.' );
					sys.font_Printc( *sys.pGram,  x+ 9 , y, '.' );
					sys.font_Printc( *sys.pGram,  x+10 , y, '.' );
					sys.font_Printc( *sys.pGram,  x+11 , y, ' ' );
					sys.font_Printc( *sys.pGram,  x+12 , y, 'M' );
					sys.font_Printc( *sys.pGram,  x+13 , y, 'O' );
					sys.font_Printc( *sys.pGram,  x+14 , y, 'V' );
					sys.font_Printc( *sys.pGram,  x+15 , y, 'E' );

					sys.font_Printc( *sys.pGram,  x+ 9 , y+2, 'o' );
					sys.font_Printc( *sys.pGram,  x+10 , y+2, 'r' );


					x = 7;
					y = 22;
					sys.font_Printc( *sys.pGram,  x+ 0 , y, 'P' );
					sys.font_Printc( *sys.pGram,  x+ 1 , y, 'U' );
					sys.font_Printc( *sys.pGram,  x+ 2 , y, 'S' );
					sys.font_Printc( *sys.pGram,  x+ 3 , y, 'H' );
					sys.font_Printc( *sys.pGram,  x+ 4 , y, ' ' );
					sys.font_Printc( *sys.pGram,  x+ 5 , y, 'A' );
					sys.font_Printc( *sys.pGram,  x+ 6 , y, 'N' );
					sys.font_Printc( *sys.pGram,  x+ 7 , y, 'Y' );
					sys.font_Printc( *sys.pGram,  x+ 8 , y, ' ' );
					sys.font_Printc( *sys.pGram,  x+ 9 , y, 'K' );
					sys.font_Printc( *sys.pGram,  x+10 , y, 'E' );
					sys.font_Printc( *sys.pGram,  x+11 , y, 'Y' );

			sys.Draw();
//					sys.pGram->UpdateTexture();                             ////c:			sys.pGram->UpdateTexture();
//					sys_draw( *sys.pGram->m_pTexture );
//				sys.pWin1->SwapBuffer();

				} 

		}

}
//-----------------------------------------------------------------------------
void	PutSleep( double sec )
//-----------------------------------------------------------------------------
{
		bool	flgLoop = true;

		double	st = 0;
		double	tm = 0;
		//--
	
		st = sys.GetPerformanceCounter();
		
		flgLoop = true;
		while(sys.pWin1->FlgActive && flgLoop)
		{
			tm = sys.GetPerformanceCounter();
			if ( tm-st > sec ) flgLoop = false;

			sys.Input();

//			sys.pWin1->Message();
			sys.Draw();

		}

}
//-----------------------------------------------------------------------------
int main( int argc, char* argv[] )
//-----------------------------------------------------------------------------
{
	if ( argc > 1 ) 
	{
		int	n = atoi( argv[1] );
		SetThreadAffinityMask(GetCurrentThread(), 1<<n ); 
	}


	sys.joy0.SetThreshold(0.4);

	pcg_Init();
	
	InitX1();

	PutTitle();
flgTrace = false;
//		sys.sound.psg_Set(7,0b111000);
//		PutSleep( 0.1 );

	while(sys.pWin1->FlgActive)
	{


		sys.sound.mml_play( "T60V15o5E0R" );
		PutSleep( 0.1 );

		if (sys.pWin1->FlgActive)
		{
			PutExplain();

			sys.joy0.UpdateJoystick();                             ////c:			sys.joy0.UpdateJoystick();
			sys.key.UpdateKey();                             ////c:			sys.key.UpdateKey();

			if (sys.pWin1->FlgActive)
			{

				GOS( *(sp++) = (int*)&&TMP1;	goto RMCEA1_Initialize;	TMP1:a=a;)

				GOS( *(sp++) = (int*)&&TMP2;	goto RMCF00;	TMP2:a=a;)

				if ( sys.pWin1->FlgActive )
				{
					PutSleep( 5 );
					if (sys.pWin1->FlgActive)
					{

						sys.sound.psg_Set( 7, 0b111000 );
						if ( IO[0xa906] != 0)
						{
							sys.sound.mml_play( "T100v12o4c3-g#dcfc#dcc7R:V12O3#D5F#GGG7R:V12O2G7GGR" );
						}
						else
						{
							sys.sound.mml_play( "T100v12o4c1-gcfcfgdg+c7r:v11o3g1eg+ca+c+db+d+g7r:v11o3e1ceafabgb+e7r");
						}
						PutSleep( 4 );
						if (sys.pWin1->FlgActive)
						{
							while(sys.pWin1->FlgActive)
							{
								{                             ////c:		{

									int x = 3;
									int	y = 10;
									for ( int i = 0 ; i < 17 ; i++ )
									{
		//								pcg_DrawChar( (*sys.pGram), x+i*8, y, ' ' );
									}
									sys.font_Printc( *sys.pGram,  x+ 0 , y, ' ' );
									sys.font_Printc( *sys.pGram,  x+ 1 , y, 'R' );
									sys.font_Printc( *sys.pGram,  x+ 2 , y, 'E' );
									sys.font_Printc( *sys.pGram,  x+ 3 , y, 'P' );
									sys.font_Printc( *sys.pGram,  x+ 4 , y, 'L' );
									sys.font_Printc( *sys.pGram,  x+ 5 , y, 'A' );
									sys.font_Printc( *sys.pGram,  x+ 6 , y, 'Y' );
									sys.font_Printc( *sys.pGram,  x+ 7 , y, ' ' );
									sys.font_Printc( *sys.pGram,  x+ 8 , y, '?' );
									sys.font_Printc( *sys.pGram,  x+ 9 , y, '(' );
									sys.font_Printc( *sys.pGram,  x+10 , y, 'Y' );
									sys.font_Printc( *sys.pGram,  x+11 , y, ' ' );
									sys.font_Printc( *sys.pGram,  x+12 , y, 'o' );
									sys.font_Printc( *sys.pGram,  x+13 , y, 'r' );
									sys.font_Printc( *sys.pGram,  x+14 , y, ' ' );
									sys.font_Printc( *sys.pGram,  x+15 , y, 'N' );
									sys.font_Printc( *sys.pGram,  x+16 , y, ')' );


//									sys.pGram->UpdateTexture();                             ////c:			sys.pGram->UpdateTexture();
								} 
								int	key = sys.Input();

								if ( key == 'Y' || key == 'y' || sys.joy0.hi.Rr ) break;
								if ( key == 'N' || key == 'n' || sys.joy0.hi.Rd ) SendMessage( sys.pWin1->m_hWnd , WM_CLOSE , 0 , 0);

								sys.Draw();

							}
						}

					}
				}
			}
		}

	}

		printf("See you again!\n");

	return 0;

{
RM001B:	

	A = 0;
	if ( sys.key.repeat('Q') ) A = 0x37;
	if ( sys.key.repeat('W') ) A = 0x37;
	if ( sys.key.repeat('E') ) A = 0x37;
	if ( sys.key.repeat('C') ) A = 0x37;
	if ( sys.key.repeat('7') ) A = 0x37;

	if ( sys.key.repeat('A') ) A = 0x34;
	if ( sys.key.repeat('S') ) A = 0x34;
	if ( sys.key.repeat('X') ) A = 0x34;
	if ( sys.key.repeat('4') ) A = 0x34;

	if ( sys.key.repeat('Z') ) A = 0x31;
	if ( sys.key.repeat('1') ) A = 0x31;




	if ( sys.joy0.now.Ru ) A = 0x37;
	if ( sys.joy0.now.Rl ) A = 0x34;
	if ( sys.joy0.now.Rd ) A = 0x31;


	if ( sys.joy0.hi.Rr ||	sys.key.hi(VK_SPACE)) 
	{
		if ( RMB610[4] == 0x80 )
		{
			A = 0x38;
		}
		else
		{
			A = 0x32;
		}

	}
	RET(goto **(--sp);)	//	IOCS	key input

p("     ");A=~A;                             ////c:A=~A;

p("     ");RMC000:                             //RMC000:
p(" C000");a = IO[BC]          ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      E,(C)
p(" C002");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C003");a = IO[BC]          ;D = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      D,(C)
p(" C005");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C006");a = IO[BC]          ;H = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      H,(C)
p(" C008");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C009");a = IO[BC]          ;L = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      L,(C)
p(" C00B");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C00C");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC00D:                             //RMC00D:
p(" C00D");                    ;B = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      B,(IX+01h)
p(" C010");                    ;C = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      C,(IX+00h)
p(" C013");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C016");a = A - 0x02        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      02h
p(" C018");                    ;if (  F.C ) {cl+=12;goto RMC023;}else{cl+= 7;}               ;                                   //      JR      C,RMC023
p(" C01A");                    ;GOS(*(sp++) = (int*)&&C01A;goto RMC000;C01A:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC000
p(" C01D");                    ;A = 0x30              ;                                  ;/*cl+= 7*/;                             //      LD      A,30h
p(" C01F");a = A - D           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      D
p(" C020");                    ;if (  F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     C
p(" C021");a = A - E           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      E
p(" C022");                    ;if (  F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     C
p("     ");RMC023:                             //RMC023:
p(" C023");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C025");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C027");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C028");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C02A");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C02B");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C02D");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C02E");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C030");                    ;GOS(*(sp++) = (int*)&&C030;goto RMC000;C030:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC000
p(" C033");                    ;A = 0x30              ;                                  ;/*cl+= 7*/;                             //      LD      A,30h
p(" C035");a = A - H           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      H
p(" C036");cl+=10              ;if ( !F.C ) goto RMC0C2   ;                                  ;                                   //      JP      NC,RMC0C2
p(" C039");a = A - L           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      L
p(" C03A");cl+=10              ;if ( !F.C ) goto RMC0C2   ;                                  ;                                   //      JP      NC,RMC0C2
p(" C03D");                    ;A = 0x02              ;                                  ;/*cl+= 7*/;                             //      LD      A,02h
p(" C03F");a = A - MEM[IX+0x04];                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      CP      (IX+04h)
p(" C042");                    ;if ( !F.C ) {cl+=12;goto RMC04F;}else{cl+= 7;}               ;                                   //      JR      NC,RMC04F
p(" C044");a = MEM[IX+0x04] - 1;MEM[IX+0x04] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      DEC     (IX+04h)
p(" C047");                    ;A = 0x01              ;                                  ;/*cl+= 7*/;                             //      LD      A,01h
p(" C049");a = A - MEM[IX+0x04];                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      CP      (IX+04h)
p(" C04C");cl+=10              ;if (  F.C ) goto RMC0F0   ;                                  ;                                   //      JP      C,RMC0F0
p("     ");RMC04F:                             //RMC04F:
p(" C04F");                    ;A = MEM[IX+0x03]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+03h)
p(" C052");a = A + 0x80        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     80h
p(" C054");a = A - 0x85        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      85h
p(" C056");cl+=10              ;if ( !F.C ) goto RMC0EB   ;                                  ;                                   //      JP      NC,RMC0EB
p(" C059");                    ;A = MEM[IX+0x06]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+06h)
p(" C05C");a = A & (1<<0)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     0,A
p(" C05E");                    ;if (  F.Z ) {cl+=12;goto RMC095;}else{cl+= 7;}               ;                                   //      JR      Z,RMC095
p(" C060");a = A & (1<<1)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     1,A
p(" C062");cl+=10              ;if (  F.Z ) goto RMC0F0   ;                                  ;                                   //      JP      Z,RMC0F0
p(" C065");                    ;D = A                 ;                                  ;/*cl+= 4*/;                             //      LD      D,A
p(" C066");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C069");a = A - 0x02        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      02h
p(" C06B");                    ;if ( !F.C ) {cl+=12;goto RMC07E;}else{cl+= 7;}               ;                                   //      JR      NC,RMC07E
p(" C06D");                    ;MEM[IX+0x03] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+03h),00h
p(" C071");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C072");a = A & (1<<2)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     2,A
p(" C074");                    ;if (  F.Z ) {cl+=12;goto RMC085;}else{cl+= 7;}               ;                                   //      JR      Z,RMC085
p(" C076");a = A & (1<<3)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     3,A
p(" C078");                    ;if (  F.Z ) {cl+=12;goto RMC08B;}else{cl+= 7;}               ;                                   //      JR      Z,RMC08B
p(" C07A");                    ;MEM[IX+0x02] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),00h
p("     ");RMC07E:                             //RMC07E:
p(" C07E");                    ;MEM[IX+0x04] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+04h),00h
p(" C082");                    ;goto RMC10D               ;                                  ;/*cl+=10*/;                             //      JP      RMC10D
p("     ");RMC085:                             //RMC085:
p(" C085");                    ;MEM[IX+0x02] = 0xFE   ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),FEh
p(" C089");                    ;goto RMC08F               ;                                  ;/*cl+=12*/;                             //      JR      RMC08F
p("     ");RMC08B:                             //RMC08B:
p(" C08B");                    ;MEM[IX+0x02] = 0x02   ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),02h
p("     ");RMC08F:                             //RMC08F:
p(" C08F");                    ;MEM[IX+0x04] = 0x01   ;                                  ;/*cl+=19*/;                             //      LD      (IX+04h),01h
p(" C093");                    ;goto RMC10D               ;                                  ;/*cl+=12*/;                             //      JR      RMC10D
p("     ");RMC095:                             //RMC095:
p(" C095");                    ;D = A                 ;                                  ;/*cl+= 4*/;                             //      LD      D,A
p(" C096");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C099");a = A - 0x02        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      02h
p(" C09B");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C09C");                    ;if ( !F.C ) {cl+=12;goto RMC0BC;}else{cl+= 7;}               ;                                   //      JR      NC,RMC0BC
p(" C09E");                    ;MEM[IX+0x03] = 0xFF   ;                                  ;/*cl+=19*/;                             //      LD      (IX+03h),FFh
p("     ");RMC0A2:                             //RMC0A2:
p(" C0A2");a = A & (1<<2)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     2,A
p(" C0A4");                    ;if (  F.Z ) {cl+=12;goto RMC0B0;}else{cl+= 7;}               ;                                   //      JR      Z,RMC0B0
p(" C0A6");a = A & (1<<3)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     3,A
p(" C0A8");                    ;if (  F.Z ) {cl+=12;goto RMC0B6;}else{cl+= 7;}               ;                                   //      JR      Z,RMC0B6
p(" C0AA");                    ;MEM[IX+0x02] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),00h
p(" C0AE");                    ;goto RMC07E               ;                                  ;/*cl+=12*/;                             //      JR      RMC07E
p("     ");RMC0B0:                             //RMC0B0:
p(" C0B0");                    ;MEM[IX+0x02] = 0xFF   ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),FFh
p(" C0B4");                    ;goto RMC07E               ;                                  ;/*cl+=12*/;                             //      JR      RMC07E
p("     ");RMC0B6:                             //RMC0B6:
p(" C0B6");                    ;MEM[IX+0x02] = 0x01   ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),01h
p(" C0BA");                    ;goto RMC07E               ;                                  ;/*cl+=12*/;                             //      JR      RMC07E
p("     ");RMC0BC:                             //RMC0BC:
p(" C0BC");                    ;MEM[IX+0x03] = 0xFB   ;                                  ;/*cl+=19*/;                             //      LD      (IX+03h),FBh
p(" C0C0");                    ;goto RMC0A2               ;                                  ;/*cl+=12*/;                             //      JR      RMC0A2
p("     ");RMC0C2:                             //RMC0C2:
p(" C0C2");                    ;A = MEM[IX+0x06]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+06h)
p(" C0C5");a = A & (1<<0)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     0,A
p(" C0C7");                    ;if (  F.Z ) {cl+=12;goto RMC0CE;}else{cl+= 7;}               ;                                   //      JR      Z,RMC0CE
p(" C0C9");a = MEM[IX+0x03] + 1;MEM[IX+0x03] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      INC     (IX+03h)
p(" C0CC");                    ;goto RMC07E               ;                                  ;/*cl+=12*/;                             //      JR      RMC07E
p("     ");RMC0CE:                             //RMC0CE:
p(" C0CE");a = MEM[IX+0x03] - 1;MEM[IX+0x03] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      DEC     (IX+03h)
p(" C0D1");a = A & (1<<2)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     2,A
p(" C0D3");                    ;if (  F.Z ) {cl+=12;goto RMC0DD;}else{cl+= 7;}               ;                                   //      JR      Z,RMC0DD
p(" C0D5");a = A & (1<<3)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     3,A
p(" C0D7");                    ;if (  F.Z ) {cl+=12;goto RMC0E1;}else{cl+= 7;}               ;                                   //      JR      Z,RMC0E1
p(" C0D9");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C0DB");                    ;goto RMC0E3               ;                                  ;/*cl+=12*/;                             //      JR      RMC0E3
p("     ");RMC0DD:                             //RMC0DD:
p(" C0DD");                    ;A = 0xFF              ;                                  ;/*cl+= 7*/;                             //      LD      A,FFh
p(" C0DF");                    ;goto RMC0E3               ;                                  ;/*cl+=12*/;                             //      JR      RMC0E3
p("     ");RMC0E1:                             //RMC0E1:
p(" C0E1");                    ;A = 0x01              ;                                  ;/*cl+= 7*/;                             //      LD      A,01h
p("     ");RMC0E3:                             //RMC0E3:
p(" C0E3");a = A + MEM[IX+0x02];A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      ADD     (IX+02h)
p(" C0E6");                    ;MEM[IX+0x02] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),A
p(" C0E9");                    ;goto RMC07E               ;                                  ;/*cl+=12*/;                             //      JR      RMC07E
p("     ");RMC0EB:                             //RMC0EB:
p(" C0EB");a = A - 0x82        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      SUB     82h
p(" C0ED");                    ;MEM[IX+0x04] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+04h),A
p("     ");RMC0F0:                             //RMC0F0:
p(" C0F0");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C0F2");                    ;MEM[IX+0x02] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),A
p(" C0F5");                    ;MEM[IX+0x03] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+03h),A
p(" C0F8");                    ;A = MEM[IX+0x07]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+07h)
p(" C0FB");a = A & 0xF0        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     F0h
p(" C0FD");a = A | 0x01        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      OR      01h
p(" C0FF");                    ;MEM[IX+0x07] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+07h),A
p(" C102");                    ;A = 0x01              ;                                  ;/*cl+= 7*/;                             //      LD      A,01h
p(" C104");a = A - MEM[IX+0x04];                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      CP      (IX+04h)
p(" C107");                    ;if (  F.C ) {cl+=12;goto RMC10D;}else{cl+= 7;}               ;                                   //      JR      C,RMC10D
p(" C109");                    ;MEM[IX+0x04] = 0x02   ;                                  ;/*cl+=19*/;                             //      LD      (IX+04h),02h
p("     ");RMC10D:                             //RMC10D:
p(" C10D");                    ;A = MEM[IX+0x02]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+02h)
p(" C110");a = A + 0x80        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     80h
p(" C112");a = A - 0x83        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      83h
p(" C114");                    ;if (  F.C ) {cl+=12;goto RMC11A;}else{cl+= 7;}               ;                                   //      JR      C,RMC11A
p(" C116");                    ;MEM[IX+0x02] = 0x02   ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),02h
p("     ");RMC11A:                             //RMC11A:
p(" C11A");a = A - 0x7E        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      7Eh
p(" C11C");                    ;if ( !F.C ) {cl+=12;goto RMC122;}else{cl+= 7;}               ;                                   //      JR      NC,RMC122
p(" C11E");                    ;MEM[IX+0x02] = 0xFE   ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),FEh
p("     ");RMC122:                             //RMC122:
p(" C122");                    ;A = MEM[IX+0x03]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+03h)
p(" C125");a = A + 0x80        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     80h
p(" C127");a = A - 0x89        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      89h
p(" C129");                    ;if (  F.C ) {cl+=12;goto RMC12F;}else{cl+= 7;}               ;                                   //      JR      C,RMC12F
p(" C12B");                    ;MEM[IX+0x03] = 0x08   ;                                  ;/*cl+=19*/;                             //      LD      (IX+03h),08h
p("     ");RMC12F:                             //RMC12F:
p(" C12F");a = A - 0x78        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      78h
p(" C131");                    ;if ( !F.C ) {cl+=12;goto RMC137;}else{cl+= 7;}               ;                                   //      JR      NC,RMC137
p(" C133");                    ;MEM[IX+0x03] = 0xF8   ;                                  ;/*cl+=19*/;                             //      LD      (IX+03h),F8h
p("     ");RMC137:                             //RMC137:
p(" C137");                    ;B = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      B,(IX+01h)
p(" C13A");                    ;C = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      C,(IX+00h)
p(" C13D");                    ;A = MEM[IX+0x02]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+02h)
p(" C140");a = A - 0xFE        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      FEh
p(" C142");                    ;if ( !F.C ) {cl+=12;goto RMC14A;}else{cl+= 7;}               ;                                   //      JR      NC,RMC14A
p(" C144");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" C146");                    ;if (  F.Z ) {cl+=12;goto RMC14B;}else{cl+= 7;}               ;                                   //      JR      Z,RMC14B
p(" C148");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C149");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p("     ");RMC14A:                             //RMC14A:
p(" C14A");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p("     ");RMC14B:                             //RMC14B:
p(" C14B");                    ;A = MEM[IX+0x03]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+03h)
p(" C14E");a = A - 0xFC        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      FCh
p(" C150");                    ;if ( !F.C ) {cl+=12;goto RMC163;}else{cl+= 7;}               ;                                   //      JR      NC,RMC163
p(" C152");a = A - 0xF8        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      F8h
p(" C154");                    ;if ( !F.C ) {cl+=12;goto RMC162;}else{cl+= 7;}               ;                                   //      JR      NC,RMC162
p(" C156");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" C158");                    ;if (  F.Z ) {cl+=12;goto RMC164;}else{cl+= 7;}               ;                                   //      JR      Z,RMC164
p(" C15A");a = A - 0x04        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      04h
p(" C15C");                    ;if (  F.C ) {cl+=12;goto RMC15F;}else{cl+= 7;}               ;                                   //      JR      C,RMC15F
p(" C15E");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p("     ");RMC15F:                             //RMC15F:
p(" C15F");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C160");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C161");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p("     ");RMC162:                             //RMC162:
p(" C162");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p("     ");RMC163:                             //RMC163:
p(" C163");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p("     ");RMC164:                             //RMC164:
p(" C164");                    ;GOS(*(sp++) = (int*)&&C164;goto RMC000;C164:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC000
p(" C167");                    ;GOS(*(sp++) = (int*)&&C167;goto RMC253;C167:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC253
p(" C16A");                    ;if ( !F.C ) {cl+=12;goto RMC1E5;}else{cl+= 7;}               ;                                   //      JR      NC,RMC1E5
p(" C16C");                    ;A = MEM[IX+0x03]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+03h)
p(" C16F");a = A + 0x80        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     80h
p(" C171");a = A - 0x7C        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      7Ch
p(" C173");                    ;if ( !F.C ) {cl+=12;goto RMC17B;}else{cl+= 7;}               ;                                   //      JR      NC,RMC17B
p(" C175");                    ;MEM[IX+0x03] = 0xFC   ;                                  ;/*cl+=19*/;                             //      LD      (IX+03h),FCh
p(" C179");                    ;goto RMC137               ;                                  ;/*cl+=12*/;                             //      JR      RMC137
p("     ");RMC17B:                             //RMC17B:
p(" C17B");a = A - 0x81        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      81h
p(" C17D");                    ;if ( !F.C ) {cl+=12;goto RMC189;}else{cl+= 7;}               ;                                   //      JR      NC,RMC189
p(" C17F");                    ;MEM[IX+0x02] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),00h
p(" C183");                    ;MEM[IX+0x03] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+03h),00h
p(" C187");                    ;goto RMC137               ;                                  ;/*cl+=12*/;                             //      JR      RMC137
p("     ");RMC189:                             //RMC189:
p(" C189");                    ;B = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      B,(IX+01h)
p(" C18C");                    ;C = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      C,(IX+00h)
p(" C18F");a = A - 0x85        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      85h
p(" C191");                    ;if (  F.C ) {cl+=12;goto RMC194;}else{cl+= 7;}               ;                                   //      JR      C,RMC194
p(" C193");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p("     ");RMC194:                             //RMC194:
p(" C194");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C195");                    ;GOS(*(sp++) = (int*)&&C195;goto RMC000;C195:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC000
p(" C198");                    ;GOS(*(sp++) = (int*)&&C198;goto RMC253;C198:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC253
p(" C19B");                    ;if ( !F.C ) {cl+=12;goto RMC1C5;}else{cl+= 7;}               ;                                   //      JR      NC,RMC1C5
p(" C19D");                    ;A = 0xFD              ;                                  ;/*cl+= 7*/;                             //      LD      A,FDh
p(" C19F");a = A - MEM[IX+0x02];                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      CP      (IX+02h)
p(" C1A2");                    ;if (  F.C ) {cl+=12;goto RMC1AE;}else{cl+= 7;}               ;                                   //      JR      C,RMC1AE
p(" C1A4");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C1A5");                    ;GOS(*(sp++) = (int*)&&C1A5;goto RMC000;C1A5:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC000
p(" C1A8");                    ;GOS(*(sp++) = (int*)&&C1A8;goto RMC253;C1A8:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC253
p(" C1AB");                    ;if ( !F.C ) {cl+=12;goto RMC1CB;}else{cl+= 7;}               ;                                   //      JR      NC,RMC1CB
p(" C1AD");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p("     ");RMC1AE:                             //RMC1AE:
p(" C1AE");                    ;A = MEM[IX+0x02]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+02h)
p(" C1B1");a = A + 0x80        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     80h
p(" C1B3");a = A - 0x81        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      81h
p(" C1B5");                    ;if ( !F.C ) {cl+=12;goto RMC1C1;}else{cl+= 7;}               ;                                   //      JR      NC,RMC1C1
p(" C1B7");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C1B8");                    ;GOS(*(sp++) = (int*)&&C1B8;goto RMC000;C1B8:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC000
p(" C1BB");                    ;GOS(*(sp++) = (int*)&&C1BB;goto RMC253;C1BB:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC253
p(" C1BE");                    ;if ( !F.C ) {cl+=12;goto RMC1D1;}else{cl+= 7;}               ;                                   //      JR      NC,RMC1D1
p(" C1C0");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p("     ");RMC1C1:                             //RMC1C1:
p(" C1C1");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C1C2");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C1C3");                    ;goto RMC194               ;                                  ;/*cl+=12*/;                             //      JR      RMC194
p("     ");RMC1C5:                             //RMC1C5:
p(" C1C5");                    ;MEM[IX+0x02] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),00h
p(" C1C9");                    ;goto RMC1D5               ;                                  ;/*cl+=12*/;                             //      JR      RMC1D5
p("     ");RMC1CB:                             //RMC1CB:
p(" C1CB");                    ;MEM[IX+0x02] = 0x01   ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),01h
p(" C1CF");                    ;goto RMC1D5               ;                                  ;/*cl+=12*/;                             //      JR      RMC1D5
p("     ");RMC1D1:                             //RMC1D1:
p(" C1D1");                    ;MEM[IX+0x02] = 0xFF   ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),FFh
p("     ");RMC1D5:                             //RMC1D5:
p(" C1D5");                    ;A = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+01h)
p(" C1D8");a = A - B           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      B
p(" C1D9");                    ;if ( !F.Z ) {cl+=12;goto RMC164;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC164
p(" C1DB");                    ;MEM[IX+0x03] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+03h),00h
p(" C1DF");                    ;goto RMC164               ;                                  ;/*cl+=12*/;                             //      JR      RMC164
p(" C1E1");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" C1E2");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" C1E3");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" C1E4");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p("     ");RMC1E5:                             //RMC1E5:
p(" C1E5");                    ;MEM[IX+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IX+00h),C
p(" C1E8");                    ;MEM[IX+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),B
p(" C1EB");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C1EE");a = A - 0x02        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      02h
p(" C1F0");                    ;if (  F.C ) {cl+=12;goto RMC202;}else{cl+= 7;}               ;                                   //      JR      C,RMC202
p(" C1F2");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C1F3");                    ;A = MEM[IX+0x07]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+07h)
p(" C1F6");a = A & 0xE0        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     E0h
p(" C1F8");a = A + 0x08        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     08h
p(" C1FA");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C1FC");a = A + 0x10        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     10h
p(" C1FE");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C1FF");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C201");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC202:                             //RMC202:
p(" C202");                    ;D = A                 ;                                  ;/*cl+= 4*/;                             //      LD      D,A
p(" C203");                    ;A = MEM[IX+0x07]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+07h)
p(" C206");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C208");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C209");a = A + 0x10        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     10h
p(" C20B");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C20D");                    ;E = A                 ;                                  ;/*cl+= 4*/;                             //      LD      E,A
p(" C20E");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C20F");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" C211");                    ;if ( !F.Z ) {cl+=12;goto RMC23B;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC23B
p(" C213");                    ;A = E                 ;                                  ;/*cl+= 4*/;                             //      LD      A,E
p(" C214");a = A & 0xF0        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     F0h
p(" C216");a = A + 0x03        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     03h
p(" C218");                    ;E = A                 ;                                  ;/*cl+= 4*/;                             //      LD      E,A
p(" C219");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C21B");a = A - MEM[IX+0x02];                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      CP      (IX+02h)
p(" C21E");                    ;if (  F.Z ) {cl+=12;goto RMC230;}else{cl+= 7;}               ;                                   //      JR      Z,RMC230
p(" C220");a = A - MEM[IX+0x03];                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      CP      (IX+03h)
p(" C223");                    ;if (  F.Z ) {cl+=12;goto RMC230;}else{cl+= 7;}               ;                                   //      JR      Z,RMC230
p(" C225");                    ;A = MEM[IX+0x02]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+02h)
p(" C228");a = A ^ MEM[IX+0x03];A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+=19*/;                             //      XOR     (IX+03h)
p(" C22B");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C22D");                    ;if (  F.C ) {cl+=12;goto RMC231;}else{cl+= 7;}               ;                                   //      JR      C,RMC231
p(" C22F");a = E + 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     E
p("     ");RMC230:                             //RMC230:
p(" C230");a = E + 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     E
p("     ");RMC231:                             //RMC231:
p(" C231");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C232");                    ;A = E                 ;                                  ;/*cl+= 4*/;                             //      LD      A,E
p(" C233");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C235");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C236");a = A - 0x10        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      SUB     10h
p(" C238");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C23A");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC23B:                             //RMC23B:
p(" C23B");                    ;A = E                 ;                                  ;/*cl+= 4*/;                             //      LD      A,E
p(" C23C");a = A & 0xF0        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     F0h
p(" C23E");a = A + 0x06        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     06h
p(" C240");                    ;E = A                 ;                                  ;/*cl+= 4*/;                             //      LD      E,A
p(" C241");                    ;A = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+00h)
p(" C244");a = A & 0x01        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     01h
p(" C246");                    ;if (  F.Z ) {cl+=12;goto RMC249;}else{cl+= 7;}               ;                                   //      JR      Z,RMC249
p(" C248");a = E + 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     E
p("     ");RMC249:                             //RMC249:
p(" C249");                    ;A = E                 ;                                  ;/*cl+= 4*/;                             //      LD      A,E
p(" C24A");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C24B");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C24D");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C24E");a = A - 0x10        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      SUB     10h
p(" C250");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C252");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC253:                             //RMC253:
p(" C253");                    ;A = 0x30              ;                                  ;/*cl+= 7*/;                             //      LD      A,30h
p(" C255");a = A - D           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      D
p(" C256");                    ;if (  F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     C
p(" C257");a = A - E           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      E
p(" C258");                    ;if (  F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     C
p(" C259");a = A - H           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      H
p(" C25A");                    ;if (  F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     C
p(" C25B");a = A - L           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      L
p(" C25C");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p(" C25D");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p("     ");RMC25E:                             //RMC25E:
p(" C25E");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C260");                    ;GOS(*(sp++) = (int*)&&C260;goto RM001B;C260:a=a;)               ;/*cl+=17*/;                             //      CALL    RM001B

p(" C263");a = A - 0x32        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      32h
p(" C265");                    ;if (  F.Z ) {cl+=12;goto RMC26C;}else{cl+= 7;}               ;                                   //      JR      Z,RMC26C
p(" C267");a = A - 0x38        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      38h
p(" C269");                    ;if (  F.Z ) {cl+=12;goto RMC29E;}else{cl+= 7;}               ;                                   //      JR      Z,RMC29E
p(" C26B");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC26C:                             //RMC26C:
p(" C26C");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C26F");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C271");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z
p(" C272");                    ;A = RMB602[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB602)
p(" C275");a = A + 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     A
p(" C276");a = A - MEM[IX+0x00];                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      CP      (IX+00h)
p(" C279");                    ;if ( !F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NZ
p(" C27A");                    ;A = RMB603[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB603)
p(" C27D");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" C27E");a = A - MEM[IX+0x01];                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      CP      (IX+01h)
p(" C281");                    ;if ( !F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NZ
p(" C282");                    ;MEM[IX+0x04] = 0x80   ;                                  ;/*cl+=19*/;                             //      LD      (IX+04h),80h
p(" C286");                    ;C = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      C,(IX+00h)
p(" C289");                    ;B = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      B,(IX+01h)
p(" C28C");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C28E");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C290");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C291");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C293");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C294");                    ;A = 0x58              ;                                  ;/*cl+= 7*/;                             //      LD      A,58h
p(" C296");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C298");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C299");                    ;A = 0x48              ;                                  ;/*cl+= 7*/;                             //      LD      A,48h
p(" C29B");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C29D");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC29E:                             //RMC29E:
p(" C29E");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C2A1");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C2A3");                    ;if ( !F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NZ
p(" C2A4");                    ;C = RMB602[0];B = RMB602[1]   ;                                  ;/*cl+=20*/;                             //      LD      BC,(RMB602)
p(" C2A8");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C2A9");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C2AB");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C2AD");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C2AE");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C2B0");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C2B1");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C2B2");                    ;GOS(*(sp++) = (int*)&&C2B2;goto RMC000;C2B2:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC000
p(" C2B5");                    ;GOS(*(sp++) = (int*)&&C2B5;goto RMC253;C2B5:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC253
p(" C2B8");                    ;if (  F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     C
p(" C2B9");                    ;MEM[IX+0x04] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+04h),00h
p(" C2BD");                    ;A = MEM[IX+0x07]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+07h)
p(" C2C0");a = A & 0xF0        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     F0h
p(" C2C2");a = A | 0x01        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      OR      01h
p(" C2C4");                    ;MEM[IX+0x07] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+07h),A
p(" C2C7");                    ;GOS(*(sp++) = (int*)&&C2C7;goto RMC1E5;C2C7:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC1E5
p(" C2CA");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC2CB:                             //RMC2CB:
p(" C2CB");                    ;IX = 0xB610             ;                                  ;/*cl+=14*/;                             //      LD      IX,B610h
p(" C2CF");                    ;BC = 0x1C00             ;                                  ;/*cl+=10*/;                             //      LD      BC,1C00h
p(" C2D2");                    ;A = 0x0E              ;                                  ;/*cl+= 7*/;                             //      LD      A,0Eh
p(" C2D4");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C2D6");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C2D7");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p("     ");A = InputJoystick();                             ////c:A = InputJoystick();

p(" C2D9");                    ;MEM[IX+0x06] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+06h),A
p(" C2DC");                    ;GOS(*(sp++) = (int*)&&C2DC;goto RMC25E;C2DC:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC25E
p(" C2DF");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C2E2");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C2E4");                    ;if (  F.Z ) {cl+=12;goto RMC318;}else{cl+= 7;}               ;                                   //      JR      Z,RMC318
p(" C2E6");                    ;A = MEM[IX+0x06]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+06h)
p(" C2E9");a = A & (1<<0)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     0,A
p(" C2EB");                    ;if (  F.Z ) {cl+=12;goto RMC2F9;}else{cl+= 7;}               ;                                   //      JR      Z,RMC2F9
p("     ");RMC2ED:                             //RMC2ED:
p(" C2ED");                    ;A = MEM[IX+0x08]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+08h)
p(" C2F0");a = A - 0x0A        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      0Ah
p(" C2F2");                    ;if ( !F.C ) {cl+=12;goto RMC315;}else{cl+= 7;}               ;                                   //      JR      NC,RMC315
p(" C2F4");a = MEM[IX+0x08] + 1;MEM[IX+0x08] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      INC     (IX+08h)
p(" C2F7");                    ;goto RMC315               ;                                  ;/*cl+=12*/;                             //      JR      RMC315
p("     ");RMC2F9:                             //RMC2F9:
p(" C2F9");                    ;D = A                 ;                                  ;/*cl+= 4*/;                             //      LD      D,A
p(" C2FA");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C2FD");a = A - 0x02        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      02h
p(" C2FF");                    ;if ( !F.C ) {cl+=12;goto RMC2ED;}else{cl+= 7;}               ;                                   //      JR      NC,RMC2ED
p(" C301");                    ;A = MEM[IX+0x08]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+08h)
p(" C304");a = A - 0x02        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      02h
p(" C306");                    ;if ( !F.C ) {cl+=12;goto RMC310;}else{cl+= 7;}               ;                                   //      JR      NC,RMC310
p(" C308");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C309");a = A | 0x01        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      OR      01h
p(" C30B");                    ;MEM[IX+0x06] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+06h),A
p(" C30E");                    ;goto RMC315               ;                                  ;/*cl+=12*/;                             //      JR      RMC315
p("     ");RMC310:                             //RMC310:
p(" C310");a = A - 0x02        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      SUB     02h
p(" C312");                    ;MEM[IX+0x08] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+08h),A
p("     ");RMC315:                             //RMC315:
p(" C315");                    ;GOS(*(sp++) = (int*)&&C315;goto RMC00D;C315:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC00D
p("     ");RMC318:                             //RMC318:
p(" C318");                    ;C = RMB602[0];B = RMB602[1]   ;                                  ;/*cl+=20*/;                             //      LD      BC,(RMB602)
p(" C31C");                    ;*(SP++)=BC            ;                                  ;/*cl+=11*/;                             //      PUSH    BC
p(" C31D");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C31F");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C320");                    ;E = 0x04              ;                                  ;/*cl+= 7*/;                             //      LD      E,04h
p("     ");RMC322:                             //RMC322:
p(" C322");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C324");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C325");a = E - 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     E
p(" C326");                    ;if ( !F.Z ) {cl+=12;goto RMC322;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC322
p(" C328");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C329");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C32A");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C32C");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p(" C32D");                    ;*(SP++)=BC            ;                                  ;/*cl+=11*/;                             //      PUSH    BC
p(" C32E");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C330");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C333");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C335");                    ;HL=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     HL
p(" C336");                    ;if (  F.Z ) {cl+=12;goto RMC34A;}else{cl+= 7;}               ;                                   //      JR      Z,RMC34A
p(" C338");                    ;A = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+00h)
p(" C33B");a = A - C           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      SUB     C
p(" C33C");a = A - 0x03        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      03h
p(" C33E");                    ;if ( !F.C ) {cl+=12;goto RMC36E;}else{cl+= 7;}               ;                                   //      JR      NC,RMC36E
p(" C340");                    ;A = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+01h)
p(" C343");a = A - B           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      SUB     B
p(" C344");a = A - 0x02        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      02h
p(" C346");                    ;if ( !F.Z ) {cl+=12;goto RMC36E;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC36E
p(" C348");                    ;goto RMC354               ;                                  ;/*cl+=12*/;                             //      JR      RMC354
p("     ");RMC34A:                             //RMC34A:
p(" C34A");                    ;*(SP++)=HL            ;                                  ;/*cl+=11*/;                             //      PUSH    HL
p(" C34B");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C34D");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C34E");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C350");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C351");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C353");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p("     ");RMC354:                             //RMC354:
p(" C354");                    ;A = MEM[IX+0x06]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+06h)
p(" C357");a = A & (1<<2)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     2,A
p(" C359");                    ;if ( !F.Z ) {cl+=12;goto RMC360;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC360
p(" C35B");                    ;MEM[IX+0x02] = 0xFF   ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),FFh
p(" C35F");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p("     ");RMC360:                             //RMC360:
p(" C360");a = A & (1<<3)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     3,A
p(" C362");                    ;if ( !F.Z ) {cl+=12;goto RMC369;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC369
p(" C364");                    ;MEM[IX+0x02] = 0x01   ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),01h
p(" C368");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p("     ");RMC369:                             //RMC369:
p(" C369");                    ;GOS(*(sp++) = (int*)&&C369;goto RMC413;C369:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC413
p(" C36C");                    ;if ( !F.C ) {cl+=12;goto RMC375;}else{cl+= 7;}               ;                                   //      JR      NC,RMC375
p("     ");RMC36E:                             //RMC36E:
p(" C36E");                    ;C = RMB602[0];B = RMB602[1]   ;                                  ;/*cl+=20*/;                             //      LD      BC,(RMB602)
p(" C372");                    ;GOS(*(sp++) = (int*)&&C372;goto RMC413;C372:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC413
p("     ");RMC375:                             //RMC375:
p(" C375");                    ;RMB602[0] = C;RMB602[1] = B   ;                                  ;/*cl+=20*/;                             //      LD      (RMB602),BC
p(" C379");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C37C");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C37E");                    ;if ( !F.Z ) {cl+=12;goto RMC39E;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC39E
p(" C380");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C381");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C382");                    ;MEM[IX+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),B
p(" C385");                    ;MEM[IX+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IX+00h),C
p(" C388");                    ;A = MEM[IX+0x05]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+05h)
p(" C38B");a = A - 0x20        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      20h
p(" C38D");                    ;if ( !F.C ) {cl+=12;goto RMC393;}else{cl+= 7;}               ;                                   //      JR      NC,RMC393
p(" C38F");a = A + 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     A
p(" C390");                    ;MEM[IX+0x05] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+05h),A
p("     ");RMC393:                             //RMC393:
p(" C393");                    ;A = MEM[IX+0x08]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+08h)
p(" C396");a = A - 0x0A        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      0Ah
p(" C398");                    ;if ( !F.C ) {cl+=12;goto RMC39E;}else{cl+= 7;}               ;                                   //      JR      NC,RMC39E
p(" C39A");a = A + 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     A
p(" C39B");                    ;MEM[IX+0x08] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+08h),A
p("     ");RMC39E:                             //RMC39E:
p(" C39E");                    ;C = RMB602[0];B = RMB602[1]   ;                                  ;/*cl+=20*/;                             //      LD      BC,(RMB602)
p(" C3A2");                    ;A = 0x69              ;                                  ;/*cl+= 7*/;                             //      LD      A,69h
p(" C3A4");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C3A6");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C3A7");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C3A8");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C3A9");a = A + 0x03        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     03h
p(" C3AB");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C3AD");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C3AE");                    ;A = 0x7C              ;                                  ;/*cl+= 7*/;                             //      LD      A,7Ch
p(" C3B0");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C3B2");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" C3B3");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C3B4");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C3B6");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" C3B7");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C3B8");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C3BA");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" C3BB");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C3BC");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C3BE");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C3C1");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C3C3");                    ;if ( !F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NZ
p(" C3C4");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C3C5");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C3C6");                    ;A = 0x6A              ;                                  ;/*cl+= 7*/;                             //      LD      A,6Ah
p(" C3C8");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C3CA");a = A + 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     A
p(" C3CB");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C3CC");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C3CE");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC3CF:                             //RMC3CF:
p(" C3CF");                    ;*(SP++)=BC            ;                                  ;/*cl+=11*/;                             //      PUSH    BC
p(" C3D0");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C3D1");                    ;D = 0x02              ;                                  ;/*cl+= 7*/;                             //      LD      D,02h
p("     ");RMC3D3:                             //RMC3D3:
p(" C3D3");                    ;E = 0x04              ;                                  ;/*cl+= 7*/;                             //      LD      E,04h
p("     ");RMC3D5:                             //RMC3D5:
p(" C3D5");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" C3D7");a = A - 0x30        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      30h
p(" C3D9");                    ;if ( !F.C ) {cl+=12;goto RMC410;}else{cl+= 7;}               ;                                   //      JR      NC,RMC410
p(" C3DB");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C3DC");a = E - 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     E
p(" C3DD");                    ;if ( !F.Z ) {cl+=12;goto RMC3D5;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC3D5
p(" C3DF");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C3E0");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C3E1");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C3E2");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C3E3");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C3E4");a = D - 1           ;D = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     D
p(" C3E5");                    ;if ( !F.Z ) {cl+=12;goto RMC3D3;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC3D3
p(" C3E7");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p(" C3E8");                    ;*(SP++)=BC            ;                                  ;/*cl+=11*/;                             //      PUSH    BC
p(" C3E9");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" C3EB");a = A - 0x30        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      30h
p(" C3ED");                    ;if ( !F.C ) {cl+=12;goto RMC410;}else{cl+= 7;}               ;                                   //      JR      NC,RMC410
p(" C3EF");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C3F0");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C3F1");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C3F2");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" C3F4");a = A - 0x30        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      30h
p(" C3F6");                    ;if ( !F.C ) {cl+=12;goto RMC410;}else{cl+= 7;}               ;                                   //      JR      NC,RMC410
p(" C3F8");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C3FB");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C3FD");                    ;if ( !F.Z ) {cl+=12;goto RMC40D;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC40D
p(" C3FF");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C400");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" C402");a = A - 0x30        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      30h
p(" C404");                    ;if ( !F.C ) {cl+=12;goto RMC410;}else{cl+= 7;}               ;                                   //      JR      NC,RMC410
p(" C406");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C407");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" C409");a = A - 0x30        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      30h
p(" C40B");                    ;if ( !F.C ) {cl+=12;goto RMC410;}else{cl+= 7;}               ;                                   //      JR      NC,RMC410
p("     ");RMC40D:                             //RMC40D:
p(" C40D");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p(" C40E");a = A & A           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 4*/;                             //      AND     A
p(" C40F");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC410:                             //RMC410:
p(" C410");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p(" C411");                    ;                      ;                   ;F.C=1         ;/*cl+= 4*/;                             //      SCF
p(" C412");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC413:                             //RMC413:
p(" C413");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C414");                    ;GOS(*(sp++) = (int*)&&C414;goto RMC3CF;C414:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC3CF
p(" C417");                    ;if ( !F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NC
p(" C418");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C419");                    ;GOS(*(sp++) = (int*)&&C419;goto RMC3CF;C419:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC3CF
p(" C41C");                    ;if ( !F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NC
p(" C41D");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C41E");                    ;GOS(*(sp++) = (int*)&&C41E;goto RMC3CF;C41E:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC3CF
p(" C421");                    ;if ( !F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NC
p(" C422");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C423");                    ;                      ;                   ;F.C=1         ;/*cl+= 4*/;                             //      SCF
p(" C424");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p(" C425");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p("     ");RMC426:                             //RMC426:
p(" C426");a = A - MEM[IY+0x01];                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      CP      (IY+01h)
p(" C429");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z
p(" C42A");a = IY + DE         ;IY = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IY,DE
p(" C42C");a = H - 1           ;H = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     H
p(" C42D");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z
p(" C42E");                    ;goto RMC426               ;                                  ;/*cl+=12*/;                             //      JR      RMC426
p("     ");RMC430:                             //RMC430:
p(" C430");                    ;A = RMB610[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB610)
p(" C433");a = A - 0x28        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      SUB     28h
p(" C435");                    ;if ( !F.C ) {cl+=12;goto RMC439;}else{cl+= 7;}               ;                                   //      JR      NC,RMC439
p(" C437");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p("     ");RMC439:                             //RMC439:
p(" C439");a = A - MEM[IX+0x0A];                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      CP      (IX+0Ah)
p(" C43C");                    ;if (  F.C ) {cl+=12;goto RMC46E;}else{cl+= 7;}               ;                                   //      JR      C,RMC46E
p(" C43E");                    ;A = RMB602[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB602)
p(" C441");a = A - 0x28        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      SUB     28h
p(" C443");                    ;if ( !F.C ) {cl+=12;goto RMC447;}else{cl+= 7;}               ;                                   //      JR      NC,RMC447
p(" C445");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p("     ");RMC447:                             //RMC447:
p(" C447");a = A - MEM[IX+0x0A];                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      CP      (IX+0Ah)
p(" C44A");                    ;if (  F.C ) {cl+=12;goto RMC473;}else{cl+= 7;}               ;                                   //      JR      C,RMC473
p(" C44C");                    ;A = MEM[IX+0x0A]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+0Ah)
p(" C44F");a = A - MEM[IX+0x00];A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      SUB     (IX+00h)
p(" C452");                    ;if (  F.C ) {cl+=12;goto RMC45B;}else{cl+= 7;}               ;                                   //      JR      C,RMC45B
p(" C454");a = A - 0x14        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      14h
p(" C456");                    ;if (  F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     C
p(" C457");                    ;D = 0xF7              ;                                  ;/*cl+= 7*/;                             //      LD      D,F7h
p(" C459");                    ;goto RMC45D               ;                                  ;/*cl+=12*/;                             //      JR      RMC45D
p("     ");RMC45B:                             //RMC45B:
p(" C45B");                    ;D = 0xFB              ;                                  ;/*cl+= 7*/;                             //      LD      D,FBh
p("     ");RMC45D:                             //RMC45D:
p(" C45D");                    ;A = MEM[IX+0x08]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+08h)
p(" C460");a = A & 0x04        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     04h
p(" C462");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C463");                    ;if (  F.Z ) {cl+=12;goto RMC467;}else{cl+= 7;}               ;                                   //      JR      Z,RMC467
p(" C465");a = A & 0xFE        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     FEh
p("     ");RMC467:                             //RMC467:
p(" C467");                    ;MEM[IX+0x06] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+06h),A
p(" C46A");a = MEM[IX+0x08] + 1;MEM[IX+0x08] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      INC     (IX+08h)
p(" C46D");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC46E:                             //RMC46E:
p(" C46E");                    ;L = RMB610[0];H = RMB610[1]   ;                                  ;/*cl+=16*/;                             //      LD      HL,(RMB610)
p(" C471");                    ;goto RMC476               ;                                  ;/*cl+=12*/;                             //      JR      RMC476
p("     ");RMC473:                             //RMC473:
p(" C473");                    ;L = RMB602[0];H = RMB602[1]   ;                                  ;/*cl+=16*/;                             //      LD      HL,(RMB602)
p("     ");RMC476:                             //RMC476:
p(" C476");                    ;B = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      B,(IX+01h)
p(" C479");                    ;C = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      C,(IX+00h)
p(" C47C");                    ;A = L                 ;                                  ;/*cl+= 4*/;                             //      LD      A,L
p(" C47D");a = A - C           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      SUB     C
p(" C47E");                    ;D = A                 ;                                  ;/*cl+= 4*/;                             //      LD      D,A
p(" C47F");                    ;E = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      E,00h
p(" C481");                    ;if (  F.C ) {cl+=12;goto RMC4D1;}else{cl+= 7;}               ;                                   //      JR      C,RMC4D1
p(" C483");                    ;A = B                 ;                                  ;/*cl+= 4*/;                             //      LD      A,B
p(" C484");a = A - H           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      SUB     H
p(" C485");                    ;E = A                 ;                                  ;/*cl+= 4*/;                             //      LD      E,A
p(" C486");                    ;if (  F.C ) {cl+=12;goto RMC48D;}else{cl+= 7;}               ;                                   //      JR      C,RMC48D
p(" C488");a = A - D           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      D
p(" C489");                    ;if ( !F.C ) {cl+=12;goto RMC4D1;}else{cl+= 7;}               ;                                   //      JR      NC,RMC4D1
p(" C48B");                    ;goto RMC492               ;                                  ;/*cl+=12*/;                             //      JR      RMC492
p("     ");RMC48D:                             //RMC48D:
p(" C48D");a = A               ;A = -a                ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 8*/;                             //      NEG
p(" C48F");a = A - D           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      D
p(" C490");                    ;if ( !F.C ) {cl+=12;goto RMC4D1;}else{cl+= 7;}               ;                                   //      JR      NC,RMC4D1
p("     ");RMC492:                             //RMC492:
p(" C492");a = MEM[IX+0x08] + 1;MEM[IX+0x08] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      INC     (IX+08h)
p(" C495");                    ;A = MEM[IX+0x08]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+08h)
p(" C498");a = A & 0x03        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     03h
p(" C49A");                    ;if ( !F.Z ) {cl+=12;goto RMC4E5;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC4E5
p(" C49C");a = rand()          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 9*/;                             //      LD      A,R
p(" C49E");a = A               ;A=(a>>1)|((a<<7)&0xff);F.Z=((a&0xff)==0)  ;F.C=a&1       ;/*cl+= 2*/;                             //      RRC     A
p(" C4A0");a = A               ;A=(a>>1)|((a<<7)&0xff);F.Z=((a&0xff)==0)  ;F.C=a&1       ;/*cl+= 2*/;                             //      RRC     A
p(" C4A2");a = A               ;A=(a>>1)|((a<<7)&0xff);F.Z=((a&0xff)==0)  ;F.C=a&1       ;/*cl+= 2*/;                             //      RRC     A
p(" C4A4");a = A               ;A=(a>>1)|((a<<7)&0xff);F.Z=((a&0xff)==0)  ;F.C=a&1       ;/*cl+= 2*/;                             //      RRC     A
p(" C4A6");a = A & 0x03        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     03h
p(" C4A8");a = A + 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     A
p(" C4A9");                    ;MEM[IX+0x08] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+08h),A
p(" C4AC");a = rand()          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 9*/;                             //      LD      A,R
p(" C4AE");a = A & (1<<1)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     1,A
p(" C4B0");                    ;if (  F.Z ) {cl+=12;goto RMC4BE;}else{cl+= 7;}               ;                                   //      JR      Z,RMC4BE
p(" C4B2");a = A & (1<<2)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     2,A
p(" C4B4");                    ;if (  F.Z ) {cl+=12;goto RMC4BA;}else{cl+= 7;}               ;                                   //      JR      Z,RMC4BA
p(" C4B6");                    ;A = 0xFB              ;                                  ;/*cl+= 7*/;                             //      LD      A,FBh
p(" C4B8");                    ;goto RMC4C0               ;                                  ;/*cl+=12*/;                             //      JR      RMC4C0
p("     ");RMC4BA:                             //RMC4BA:
p(" C4BA");                    ;A = 0xFF              ;                                  ;/*cl+= 7*/;                             //      LD      A,FFh
p(" C4BC");                    ;goto RMC4C0               ;                                  ;/*cl+=12*/;                             //      JR      RMC4C0
p("     ");RMC4BE:                             //RMC4BE:
p(" C4BE");                    ;A = 0xF7              ;                                  ;/*cl+= 7*/;                             //      LD      A,F7h
p("     ");RMC4C0:                             //RMC4C0:
p(" C4C0");                    ;a=A;A=_A;_A=a;        ;a=F.C;F.C=fc;fc=a; a=F.Z;F.Z=fz;fz=a;;                                           ;/*cl+= 4*/;                             //      EX      AF,AF'
p(" C4C1");a = rand()          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 9*/;                             //      LD      A,R
p(" C4C3");a = A & (1<<3)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     3,A
p(" C4C5");                    ;if (  F.Z ) {cl+=12;goto RMC4CB;}else{cl+= 7;}               ;                                   //      JR      Z,RMC4CB
p(" C4C7");                    ;a=A;A=_A;_A=a;        ;a=F.C;F.C=fc;fc=a; a=F.Z;F.Z=fz;fz=a;;                                           ;/*cl+= 4*/;                             //      EX      AF,AF'
p(" C4C8");a = A & 0xFE        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     FEh
p(" C4CA");                    ;a=A;A=_A;_A=a;        ;a=F.C;F.C=fc;fc=a; a=F.Z;F.Z=fz;fz=a;;                                           ;/*cl+= 4*/;                             //      EX      AF,AF'
p("     ");RMC4CB:                             //RMC4CB:
p(" C4CB");                    ;a=A;A=_A;_A=a;        ;a=F.C;F.C=fc;fc=a; a=F.Z;F.Z=fz;fz=a;;                                           ;/*cl+= 4*/;                             //      EX      AF,AF'
p(" C4CC");                    ;MEM[IX+0x06] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+06h),A
p(" C4CF");                    ;goto RMC4E5               ;                                  ;/*cl+=12*/;                             //      JR      RMC4E5
p("     ");RMC4D1:                             //RMC4D1:
p(" C4D1");a = MEM[IX+0x08] + 1;MEM[IX+0x08] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      INC     (IX+08h)
p(" C4D4");                    ;A = MEM[IX+0x08]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+08h)
p(" C4D7");a = A & 0x04        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     04h
p(" C4D9");                    ;if (  F.Z ) {cl+=12;goto RMC4E1;}else{cl+= 7;}               ;                                   //      JR      Z,RMC4E1
p(" C4DB");                    ;MEM[IX+0x06] = 0xFF   ;                                  ;/*cl+=19*/;                             //      LD      (IX+06h),FFh
p(" C4DF");                    ;goto RMC4E5               ;                                  ;/*cl+=12*/;                             //      JR      RMC4E5
p("     ");RMC4E1:                             //RMC4E1:
p(" C4E1");                    ;MEM[IX+0x06] = 0xFA   ;                                  ;/*cl+=19*/;                             //      LD      (IX+06h),FAh
p("     ");RMC4E5:                             //RMC4E5:
p(" C4E5");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C4E6");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C4E8");                    ;if ( !F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NC
p(" C4E9");a = rand()          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 9*/;                             //      LD      A,R
p(" C4EB");a = A & 0xDE        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     DEh
p(" C4ED");                    ;if ( !F.Z ) {cl+=12;goto RMC4FD;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC4FD
p(" C4EF");                    ;A = E                 ;                                  ;/*cl+= 4*/;                             //      LD      A,E
p(" C4F0");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C4F2");                    ;if ( !F.C ) {cl+=12;goto RMC4F8;}else{cl+= 7;}               ;                                   //      JR      NC,RMC4F8
p(" C4F4");                    ;L = 0xFF              ;                                  ;/*cl+= 7*/;                             //      LD      L,FFh
p(" C4F6");                    ;goto RMC504               ;                                  ;/*cl+=12*/;                             //      JR      RMC504
p("     ");RMC4F8:                             //RMC4F8:
p(" C4F8");                    ;L = 0x01              ;                                  ;/*cl+= 7*/;                             //      LD      L,01h
p(" C4FA");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C4FB");                    ;goto RMC504               ;                                  ;/*cl+=12*/;                             //      JR      RMC504
p("     ");RMC4FD:                             //RMC4FD:
p(" C4FD");a = rand()          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 9*/;                             //      LD      A,R
p(" C4FF");a = A & 0x3E        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     3Eh
p(" C501");                    ;if ( !F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NZ
p(" C502");                    ;L = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      L,00h
p("     ");RMC504:                             //RMC504:
p(" C504");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C507");a = A - 0x02        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      02h
p(" C509");                    ;if ( !F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NC
p(" C50A");                    ;IY = 0xBA30             ;                                  ;/*cl+=14*/;                             //      LD      IY,BA30h
p(" C50E");                    ;DE = 0x0004             ;                                  ;/*cl+=10*/;                             //      LD      DE,0004h
p(" C511");                    ;H = 0x14              ;                                  ;/*cl+= 7*/;                             //      LD      H,14h
p(" C513");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C515");                    ;GOS(*(sp++) = (int*)&&C515;goto RMC426;C515:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC426
p(" C518");a = A - H           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      H
p(" C519");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z
p(" C51A");                    ;A = MEM[IX+0x07]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+07h)
p(" C51D");a = A & 0xF0        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     F0h
p(" C51F");a = A + L           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      ADD     L
p(" C520");a = A + 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     A
p(" C521");                    ;MEM[IX+0x07] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+07h),A
p(" C524");                    ;MEM[IY+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IY+00h),C
p(" C527");                    ;MEM[IY+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IY+01h),B
p(" C52A");                    ;*(SP++)=AF            ;                                  ;/*cl+=11*/;                             //      PUSH    AF
p(" C52B");                    ;A = 0x12              ;                                  ;/*cl+= 7*/;                             //      LD      A,12h
p(" C52D");a = A + L           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      ADD     L
p(" C52E");                    ;MEM[IY+0x02] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IY+02h),A
p(" C531");                    ;AF=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     AF
p(" C532");                    ;MEM[IY+0x03] = 0x10   ;                                  ;/*cl+=19*/;                             //      LD      (IY+03h),10h
p(" C536");a = L - 1           ;L = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     L
p(" C537");                    ;if ( !F.Z ) {cl+=12;goto RMC53A;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC53A
p(" C539");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p("     ");RMC53A:                             //RMC53A:
p(" C53A");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C53C");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C53D");a = A + 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     A
p(" C53E");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C540");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC541:                             //RMC541:
p(" C541");                    ;IX = 0xB640             ;                                  ;/*cl+=14*/;                             //      LD      IX,B640h
p(" C545");                    ;B = 0x3C              ;                                  ;/*cl+= 7*/;                             //      LD      B,3Ch
p(" C547");                    ;DE = 0x0010             ;                                  ;/*cl+=10*/;                             //      LD      DE,0010h
p("     ");RMC54A:                             //RMC54A:
p(" C54A");                    ;A = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+01h)
p(" C54D");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" C54F");                    ;if (  F.Z ) {cl+=12;goto RMC558;}else{cl+= 7;}               ;                                   //      JR      Z,RMC558
p(" C551");                    ;*(SP++)=DE            ;                                  ;/*cl+=11*/;                             //      PUSH    DE
p(" C552");                    ;*(SP++)=BC            ;                                  ;/*cl+=11*/;                             //      PUSH    BC
p(" C553");                    ;GOS(*(sp++) = (int*)&&C553;goto RMC430;C553:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC430
p(" C556");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p(" C557");                    ;DE=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     DE
p("     ");RMC558:                             //RMC558:
p(" C558");a = IX + DE         ;IX = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IX,DE
p(" C55A");                    ;if ( --B > 0 ) {cl+=13;goto RMC54A;}else{cl+=8;}             ;                                    //      DJNZ    RMC54A
p(" C55C");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC55D:                             //RMC55D:
p(" C55D");                    ;IX = 0xB640             ;                                  ;/*cl+=14*/;                             //      LD      IX,B640h
p(" C561");                    ;B = 0x3C              ;                                  ;/*cl+= 7*/;                             //      LD      B,3Ch
p(" C563");                    ;DE = 0x0010             ;                                  ;/*cl+=10*/;                             //      LD      DE,0010h
p("     ");RMC566:                             //RMC566:
p(" C566");                    ;A = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+01h)
p(" C569");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" C56B");                    ;if (  F.Z ) {cl+=12;goto RMC574;}else{cl+= 7;}               ;                                   //      JR      Z,RMC574
p(" C56D");                    ;*(SP++)=DE            ;                                  ;/*cl+=11*/;                             //      PUSH    DE
p(" C56E");                    ;*(SP++)=BC            ;                                  ;/*cl+=11*/;                             //      PUSH    BC
p(" C56F");                    ;GOS(*(sp++) = (int*)&&C56F;goto RMC00D;C56F:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC00D
p(" C572");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p(" C573");                    ;DE=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     DE
p("     ");RMC574:                             //RMC574:
p(" C574");a = IX + DE         ;IX = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IX,DE
p(" C576");                    ;if ( --B > 0 ) {cl+=13;goto RMC566;}else{cl+=8;}             ;                                    //      DJNZ    RMC566
p(" C578");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p(" C579");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p("     ");RMC57A:                             //RMC57A:
p(" C57A");                    ;IX = 0xB640             ;                                  ;/*cl+=14*/;                             //      LD      IX,B640h
p(" C57E");                    ;B = 0x08              ;                                  ;/*cl+= 7*/;                             //      LD      B,08h
p(" C580");                    ;DE = 0x0010             ;                                  ;/*cl+=10*/;                             //      LD      DE,0010h
p("     ");RMC583:                             //RMC583:
p(" C583");                    ;A = RMB615[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB615)
p(" C586");a = A - 0x10        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      10h
p(" C588");                    ;if ( !F.C ) {cl+=12;goto RMC58F;}else{cl+= 7;}               ;                                   //      JR      NC,RMC58F
p(" C58A");                    ;A = RMB610[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB610)
p(" C58D");                    ;goto RMC598               ;                                  ;/*cl+=12*/;                             //      JR      RMC598
p("     ");RMC58F:                             //RMC58F:
p(" C58F");                    ;A = MEM[IX+0x0A]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+0Ah)
p(" C592");a = A - MEM[IX+0x0B];                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      CP      (IX+0Bh)
p(" C595");                    ;if (  F.Z ) {cl+=12;goto RMC598;}else{cl+= 7;}               ;                                   //      JR      Z,RMC598
p(" C597");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p("     ");RMC598:                             //RMC598:
p(" C598");                    ;MEM[IX+0x0A] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+0Ah),A
p(" C59B");                    ;*(SP++)=BC            ;                                  ;/*cl+=11*/;                             //      PUSH    BC
p(" C59C");                    ;*(SP++)=DE            ;                                  ;/*cl+=11*/;                             //      PUSH    DE
p(" C59D");                    ;*(SP++)=AF            ;                                  ;/*cl+=11*/;                             //      PUSH    AF
p(" C59E");                    ;GOS(*(sp++) = (int*)&&C59E;goto RMC430;C59E:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC430
p(" C5A1");                    ;AF=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     AF
p(" C5A2");                    ;DE=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     DE
p(" C5A3");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p(" C5A4");a = IX + DE         ;IX = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IX,DE
p(" C5A6");                    ;if ( --B > 0 ) {cl+=13;goto RMC583;}else{cl+=8;}             ;                                    //      DJNZ    RMC583
p(" C5A8");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC5A9:                             //RMC5A9:
p(" C5A9");                    ;MEM[IX+0x01] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),00h
p(" C5AD");                    ;A = 0x2F              ;                                  ;/*cl+= 7*/;                             //      LD      A,2Fh
p(" C5AF");                    ;GOS(*(sp++) = (int*)&&C5AF;goto RMC5E3;C5AF:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC5E3
p(" C5B2");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C5B3");                    ;A = 0x2B              ;                                  ;/*cl+= 7*/;                             //      LD      A,2Bh
p(" C5B5");                    ;GOS(*(sp++) = (int*)&&C5B5;goto RMC5E3;C5B5:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC5E3
p(" C5B8");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C5B9");                    ;A = 0x26              ;                                  ;/*cl+= 7*/;                             //      LD      A,26h
p(" C5BB");                    ;GOS(*(sp++) = (int*)&&C5BB;goto RMC5E3;C5BB:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC5E3
p(" C5BE");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C5BF");                    ;A = 0x2D              ;                                  ;/*cl+= 7*/;                             //      LD      A,2Dh
p(" C5C1");                    ;GOS(*(sp++) = (int*)&&C5C1;goto RMC5E3;C5C1:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC5E3
p(" C5C4");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C5C5");                    ;A = 0x24              ;                                  ;/*cl+= 7*/;                             //      LD      A,24h
p(" C5C7");                    ;GOS(*(sp++) = (int*)&&C5C7;goto RMC5E3;C5C7:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC5E3
p(" C5CA");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C5CB");                    ;A = 0x2E              ;                                  ;/*cl+= 7*/;                             //      LD      A,2Eh
p(" C5CD");                    ;GOS(*(sp++) = (int*)&&C5CD;goto RMC5E3;C5CD:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC5E3
p(" C5D0");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C5D1");                    ;A = 0x28              ;                                  ;/*cl+= 7*/;                             //      LD      A,28h
p(" C5D3");                    ;GOS(*(sp++) = (int*)&&C5D3;goto RMC5E3;C5D3:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC5E3
p(" C5D6");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C5D7");                    ;A = 0x2C              ;                                  ;/*cl+= 7*/;                             //      LD      A,2Ch
p(" C5D9");                    ;GOS(*(sp++) = (int*)&&C5D9;goto RMC5E3;C5D9:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC5E3
p(" C5DC");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C5DD");                    ;A = 0x2A              ;                                  ;/*cl+= 7*/;                             //      LD      A,2Ah
p(" C5DF");                    ;GOS(*(sp++) = (int*)&&C5DF;goto RMC5E3;C5DF:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC5E3
p(" C5E2");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC5E3:                             //RMC5E3:
p(" C5E3");                    ;D = A                 ;                                  ;/*cl+= 4*/;                             //      LD      D,A
p(" C5E4");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" C5E6");a = A - 0x30        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      30h
p(" C5E8");                    ;if ( !F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NC
p(" C5E9");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C5EA");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C5EC");                    ;IY = 0xBB00             ;                                  ;/*cl+=14*/;                             //      LD      IY,BB00h
p(" C5F0");                    ;DE = 0x0004             ;                                  ;/*cl+=10*/;                             //      LD      DE,0004h
p(" C5F3");                    ;H = 0xFF              ;                                  ;/*cl+= 7*/;                             //      LD      H,FFh
p(" C5F5");                    ;*(SP++)=AF            ;                                  ;/*cl+=11*/;                             //      PUSH    AF
p(" C5F6");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C5F8");                    ;GOS(*(sp++) = (int*)&&C5F8;goto RMC426;C5F8:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC426
p(" C5FB");                    ;AF=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     AF
p(" C5FC");                    ;MEM[IY+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IY+00h),C
p(" C5FF");                    ;MEM[IY+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IY+01h),B
p(" C602");                    ;MEM[IY+0x02] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IY+02h),A
p(" C605");                    ;MEM[IY+0x03] = 0x20   ;                                  ;/*cl+=19*/;                             //      LD      (IY+03h),20h
p(" C609");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC60A:                             //RMC60A:
p(" C60A");                    ;IX = 0xBF00             ;                                  ;/*cl+=14*/;                             //      LD      IX,BF00h
p(" C60E");                    ;DE = 0x0004             ;                                  ;/*cl+=10*/;                             //      LD      DE,0004h
p(" C611");                    ;B = 0x20              ;                                  ;/*cl+= 7*/;                             //      LD      B,20h
p("     ");RMC613:                             //RMC613:
p(" C613");                    ;A = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+01h)
p(" C616");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" C618");                    ;if (  F.Z ) {cl+=12;goto RMC621;}else{cl+= 7;}               ;                                   //      JR      Z,RMC621
p(" C61A");                    ;*(SP++)=BC            ;                                  ;/*cl+=11*/;                             //      PUSH    BC
p(" C61B");                    ;*(SP++)=DE            ;                                  ;/*cl+=11*/;                             //      PUSH    DE
p(" C61C");                    ;GOS(*(sp++) = (int*)&&C61C;goto RMC626;C61C:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC626
p(" C61F");                    ;DE=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     DE
p(" C620");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p("     ");RMC621:                             //RMC621:
p(" C621");a = IX + DE         ;IX = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IX,DE
p(" C623");                    ;if ( --B > 0 ) {cl+=13;goto RMC613;}else{cl+=8;}             ;                                    //      DJNZ    RMC613
p(" C625");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC626:                             //RMC626:
p(" C626");a = rand()          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 9*/;                             //      LD      A,R
p(" C628");a = A & 0xD1        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     D1h
p(" C62A");                    ;if ( !F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NZ
p(" C62B");                    ;IY = 0xBA30             ;                                  ;/*cl+=14*/;                             //      LD      IY,BA30h
p(" C62F");                    ;DE = 0x0004             ;                                  ;/*cl+=10*/;                             //      LD      DE,0004h
p(" C632");                    ;H = 0x14              ;                                  ;/*cl+= 7*/;                             //      LD      H,14h
p(" C634");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C636");                    ;GOS(*(sp++) = (int*)&&C636;goto RMC426;C636:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC426
p(" C639");a = A - H           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      H
p(" C63A");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z
p(" C63B");                    ;C = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      C,(IX+00h)
p(" C63E");                    ;B = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      B,(IX+01h)
p(" C641");                    ;A = RMB610[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB610)
p(" C644");a = A - C           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      SUB     C
p(" C645");                    ;E = A                 ;                                  ;/*cl+= 4*/;                             //      LD      E,A
p(" C646");                    ;A = RMB611[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB611)
p(" C649");a = A - B           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      SUB     B
p(" C64A");                    ;D = A                 ;                                  ;/*cl+= 4*/;                             //      LD      D,A
p(" C64B");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C64D");                    ;if (  F.C ) {cl+=12;goto RMC651;}else{cl+= 7;}               ;                                   //      JR      C,RMC651
p(" C64F");a = A               ;A = -a                ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 8*/;                             //      NEG
p("     ");RMC651:                             //RMC651:
p(" C651");                    ;H = A                 ;                                  ;/*cl+= 4*/;                             //      LD      H,A
p(" C652");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C653");                    ;A = E                 ;                                  ;/*cl+= 4*/;                             //      LD      A,E
p(" C654");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C656");                    ;if (  F.C ) {cl+=12;goto RMC65B;}else{cl+= 7;}               ;                                   //      JR      C,RMC65B
p(" C658");a = A               ;A = -a                ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 8*/;                             //      NEG
p(" C65A");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p("     ");RMC65B:                             //RMC65B:
p(" C65B");a = A - H           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      SUB     H
p(" C65C");                    ;H = A                 ;                                  ;/*cl+= 4*/;                             //      LD      H,A
p(" C65D");a = rand()          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 9*/;                             //      LD      A,R
p(" C65F");a = A & 0x08        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     08h
p(" C661");                    ;if (  F.Z ) {cl+=12;goto RMC686;}else{cl+= 7;}               ;                                   //      JR      Z,RMC686
p(" C663");                    ;A = H                 ;                                  ;/*cl+= 4*/;                             //      LD      A,H
p(" C664");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C666");                    ;if ( !F.C ) {cl+=12;goto RMC677;}else{cl+= 7;}               ;                                   //      JR      NC,RMC677
p(" C668");                    ;A = E                 ;                                  ;/*cl+= 4*/;                             //      LD      A,E
p(" C669");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C66B");                    ;if ( !F.C ) {cl+=12;goto RMC672;}else{cl+= 7;}               ;                                   //      JR      NC,RMC672
p(" C66D");                    ;L = 0x12              ;                                  ;/*cl+= 7*/;                             //      LD      L,12h
p(" C66F");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C670");                    ;goto RMC69F               ;                                  ;/*cl+=12*/;                             //      JR      RMC69F
p("     ");RMC672:                             //RMC672:
p(" C672");                    ;L = 0x02              ;                                  ;/*cl+= 7*/;                             //      LD      L,02h
p(" C674");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C675");                    ;goto RMC69F               ;                                  ;/*cl+=12*/;                             //      JR      RMC69F
p("     ");RMC677:                             //RMC677:
p(" C677");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C678");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C67A");                    ;if ( !F.C ) {cl+=12;goto RMC681;}else{cl+= 7;}               ;                                   //      JR      NC,RMC681
p(" C67C");                    ;L = 0x04              ;                                  ;/*cl+= 7*/;                             //      LD      L,04h
p(" C67E");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C67F");                    ;goto RMC69F               ;                                  ;/*cl+=12*/;                             //      JR      RMC69F
p("     ");RMC681:                             //RMC681:
p(" C681");                    ;L = 0x14              ;                                  ;/*cl+= 7*/;                             //      LD      L,14h
p(" C683");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C684");                    ;goto RMC69F               ;                                  ;/*cl+=12*/;                             //      JR      RMC69F
p("     ");RMC686:                             //RMC686:
p(" C686");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C687");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C689");                    ;if ( !F.C ) {cl+=12;goto RMC690;}else{cl+= 7;}               ;                                   //      JR      NC,RMC690
p(" C68B");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C68C");                    ;L = 0x03              ;                                  ;/*cl+= 7*/;                             //      LD      L,03h
p(" C68E");                    ;goto RMC693               ;                                  ;/*cl+=12*/;                             //      JR      RMC693
p("     ");RMC690:                             //RMC690:
p(" C690");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C691");                    ;L = 0x01              ;                                  ;/*cl+= 7*/;                             //      LD      L,01h
p("     ");RMC693:                             //RMC693:
p(" C693");                    ;A = E                 ;                                  ;/*cl+= 4*/;                             //      LD      A,E
p(" C694");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C696");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C697");                    ;if ( !F.C ) {cl+=12;goto RMC69F;}else{cl+= 7;}               ;                                   //      JR      NC,RMC69F
p(" C699");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C69A");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C69B");                    ;A = 0x10              ;                                  ;/*cl+= 7*/;                             //      LD      A,10h
p(" C69D");a = A + L           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      ADD     L
p(" C69E");                    ;L = A                 ;                                  ;/*cl+= 4*/;                             //      LD      L,A
p("     ");RMC69F:                             //RMC69F:
p(" C69F");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" C6A1");a = A - 0x10        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      10h
p(" C6A3");                    ;if ( !F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NC
p(" C6A4");                    ;MEM[IY+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IY+00h),C
p(" C6A7");                    ;MEM[IY+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IY+01h),B
p(" C6AA");                    ;MEM[IY+0x02] = L      ;                                  ;/*cl+=19*/;                             //      LD      (IY+02h),L
p(" C6AD");                    ;MEM[IY+0x03] = 0x20   ;                                  ;/*cl+=19*/;                             //      LD      (IY+03h),20h
p(" C6B1");                    ;A = 0x88              ;                                  ;/*cl+= 7*/;                             //      LD      A,88h
p(" C6B3");a = A + L           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      ADD     L
p(" C6B4");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C6B6");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p(" C6B7");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p("     ");RMC6B8:                             //RMC6B8:
p(" C6B8");                    ;IX = 0xBB00             ;                                  ;/*cl+=14*/;                             //      LD      IX,BB00h
p(" C6BC");                    ;DE = 0x0004             ;                                  ;/*cl+=10*/;                             //      LD      DE,0004h
p(" C6BF");                    ;H = 0xFF              ;                                  ;/*cl+= 7*/;                             //      LD      H,FFh
p("     ");RMC6C1:                             //RMC6C1:
p(" C6C1");                    ;A = MEM[IX+0x03]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+03h)
p(" C6C4");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" C6C6");                    ;if (  F.Z ) {cl+=12;goto RMC6E2;}else{cl+= 7;}               ;                                   //      JR      Z,RMC6E2
p(" C6C8");a = MEM[IX+0x03] - 1;MEM[IX+0x03] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      DEC     (IX+03h)
p(" C6CB");                    ;if ( !F.Z ) {cl+=12;goto RMC6E2;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC6E2
p(" C6CD");                    ;B = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      B,(IX+01h)
p(" C6D0");                    ;MEM[IX+0x01] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),00h
p(" C6D4");                    ;C = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      C,(IX+00h)
p(" C6D7");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" C6D9");a = A - MEM[IX+0x02];                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      CP      (IX+02h)
p(" C6DC");                    ;if ( !F.Z ) {cl+=12;goto RMC6E2;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC6E2
p(" C6DE");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C6E0");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p("     ");RMC6E2:                             //RMC6E2:
p(" C6E2");a = IX + DE         ;IX = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IX,DE
p(" C6E4");a = H - 1           ;H = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     H
p(" C6E5");                    ;if ( !F.Z ) {cl+=12;goto RMC6C1;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC6C1
p(" C6E7");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC6E8:                             //RMC6E8:
p(" C6E8");                    ;IX = 0xB610             ;                                  ;/*cl+=14*/;                             //      LD      IX,B610h
p(" C6EC");                    ;A = MEM[IX+0x05]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+05h)
p(" C6EF");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" C6F1");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z
p(" C6F2");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C6F5");a = A & 0x7F        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     7Fh
p(" C6F7");a = A - 0x02        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      02h
p(" C6F9");                    ;if ( !F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NC
p(" C6FA");                    ;IY = 0xBA00             ;                                  ;/*cl+=14*/;                             //      LD      IY,BA00h
p(" C6FE");                    ;DE = 0x0004             ;                                  ;/*cl+=10*/;                             //      LD      DE,0004h
p(" C701");                    ;H = 0x04              ;                                  ;/*cl+= 7*/;                             //      LD      H,04h
p(" C703");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C705");                    ;GOS(*(sp++) = (int*)&&C705;goto RMC426;C705:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC426
p(" C708");                    ;*(SP++)=IY            ;                                  ;/*cl+=15*/;                             //      PUSH    IY
p(" C70A");                    ;HL=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     HL
p(" C70B");                    ;A = L                 ;                                  ;/*cl+= 4*/;                             //      LD      A,L
p(" C70C");a = A - 0x10        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      10h
p(" C70E");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z
p(" C70F");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C711");                    ;GOS(*(sp++) = (int*)&&C711;goto RM001B;C711:a=a;)               ;/*cl+=17*/;                             //      CALL    RM001B
p(" C714");                    ;C = RMB610[0];B = RMB610[1]   ;                                  ;/*cl+=20*/;                             //      LD      BC,(RMB610)
p(" C718");a = A - 0x37        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      37h
p(" C71A");                    ;if ( !F.Z ) {cl+=12;goto RMC71D;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC71D
p(" C71C");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p("     ");RMC71D:                             //RMC71D:
p(" C71D");                    ;E = 0x01              ;                                  ;/*cl+= 7*/;                             //      LD      E,01h
p(" C71F");                    ;D = 0x40              ;                                  ;/*cl+= 7*/;                             //      LD      D,40h
p(" C721");a = A - 0x31        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      31h
p(" C723");                    ;if (  F.Z ) {cl+=12;goto RMC72E;}else{cl+= 7;}               ;                                   //      JR      Z,RMC72E
p(" C725");a = A - 0x34        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      34h
p(" C727");                    ;if (  F.Z ) {cl+=12;goto RMC730;}else{cl+= 7;}               ;                                   //      JR      Z,RMC730
p(" C729");a = A - 0x37        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      37h
p(" C72B");                    ;if (  F.Z ) {cl+=12;goto RMC732;}else{cl+= 7;}               ;                                   //      JR      Z,RMC732
p(" C72D");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC72E:                             //RMC72E:
p(" C72E");a = E + 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     E
p(" C72F");a = D + 1           ;D = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     D
p("     ");RMC730:                             //RMC730:
p(" C730");a = E + 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     E
p(" C731");a = D + 1           ;D = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     D
p("     ");RMC732:                             //RMC732:
p(" C732");                    ;A = MEM[IX+0x04]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+04h)
p(" C735");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C737");                    ;if (  F.Z ) {cl+=12;goto RMC759;}else{cl+= 7;}               ;                                   //      JR      Z,RMC759
p(" C739");                    ;MEM[IY+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IY+00h),C
p(" C73C");                    ;MEM[IY+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IY+01h),B
p(" C73F");                    ;MEM[IY+0x02] = E      ;                                  ;/*cl+=19*/;                             //      LD      (IY+02h),E
p(" C742");                    ;MEM[IY+0x03] = 0x10   ;                                  ;/*cl+=19*/;                             //      LD      (IY+03h),10h
p(" C746");                    ;MEM[IX+0x07] = D      ;                                  ;/*cl+=19*/;                             //      LD      (IX+07h),D
p(" C749");                    ;C = RMB610[0];B = RMB610[1]   ;                                  ;/*cl+=20*/;                             //      LD      BC,(RMB610)
p(" C74D");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p(" C74F");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C750");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C751");a = A + 0x10        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     10h
p(" C753");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C755");a = MEM[IX+0x05] - 1;MEM[IX+0x05] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      DEC     (IX+05h)
p(" C758");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC759:                             //RMC759:
p(" C759");                    ;C = RMB602[0];B = RMB602[1]   ;                                  ;/*cl+=20*/;                             //      LD      BC,(RMB602)
p(" C75D");                    ;MEM[IY+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IY+00h),C
p(" C760");                    ;MEM[IY+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IY+01h),B
p(" C763");                    ;MEM[IY+0x02] = E      ;                                  ;/*cl+=19*/;                             //      LD      (IY+02h),E
p(" C766");                    ;MEM[IY+0x03] = 0x03   ;                                  ;/*cl+=19*/;                             //      LD      (IY+03h),03h
p(" C76A");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET


p("     ");RMC76B:                             //RMC76B:
p(" C76B");                    ;IX = 0xBA00             ;                                  ;/*cl+=14*/;                             //      LD      IX,BA00h
p(" C76F");                    ;B = 0x0C              ;                                  ;/*cl+= 7*/;                             //      LD      B,0Ch
p("     ");RMC771:                             //RMC771:
p(" C771");                    ;*(SP++)=BC            ;                                  ;/*cl+=11*/;                             //      PUSH    BC
p(" C772");                    ;A = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+01h)
p(" C775");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" C777");                    ;if (  F.Z ) {cl+=12;goto RMC77E;}else{cl+= 7;}               ;                                   //      JR      Z,RMC77E
p(" C779");                    ;L = 0xFF              ;                                  ;/*cl+= 7*/;                             //      LD      L,FFh
p(" C77B");                    ;GOS(*(sp++) = (int*)&&C77B;goto RMC7A4;C77B:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC7A4
p("     ");RMC77E:                             //RMC77E:
p(" C77E");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p(" C77F");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" C781");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" C783");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" C785");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" C787");                    ;if ( --B > 0 ) {cl+=13;goto RMC771;}else{cl+=8;}             ;                                    //      DJNZ    RMC771
p(" C789");                    ;B = 0x14              ;                                  ;/*cl+= 7*/;                             //      LD      B,14h
p("     ");RMC78B:                             //RMC78B:
p(" C78B");                    ;*(SP++)=BC            ;                                  ;/*cl+=11*/;                             //      PUSH    BC
p(" C78C");                    ;A = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+01h)
p(" C78F");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" C791");                    ;if (  F.Z ) {cl+=12;goto RMC798;}else{cl+= 7;}               ;                                   //      JR      Z,RMC798
p(" C793");                    ;L = 0x01              ;                                  ;/*cl+= 7*/;                             //      LD      L,01h
p(" C795");                    ;GOS(*(sp++) = (int*)&&C795;goto RMC7A4;C795:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC7A4
p("     ");RMC798:                             //RMC798:
p(" C798");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p(" C799");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" C79B");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" C79D");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" C79F");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" C7A1");                    ;if ( --B > 0 ) {cl+=13;goto RMC78B;}else{cl+=8;}             ;                                    //      DJNZ    RMC78B
p(" C7A3");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET


p("     ");RMC7A4:                             //RMC7A4:
p(" C7A4");                    ;C = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      C,(IX+00h)
p(" C7A7");                    ;B = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      B,(IX+01h)
p(" C7AA");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" C7AC");a = A - 0x10        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      10h
p(" C7AE");                    ;if (  F.C ) {cl+=12;goto RMC7B7;}else{cl+= 7;}               ;                                   //      JR      C,RMC7B7
p(" C7B0");a = A - 0x30        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      30h
p(" C7B2");                    ;if (  F.C ) {cl+=12;goto RMC7EC;}else{cl+= 7;}               ;                                   //      JR      C,RMC7EC
p(" C7B4");cl+=17              ;if ( !F.C ) {GOS(*(sp++) = (int*)&&C7B4;goto RMC831;C7B4:a=a;);};                                   //      CALL    NC,RMC831
p("     ");RMC7B7:                             //RMC7B7:
p(" C7B7");                    ;D = A                 ;                                  ;/*cl+= 4*/;                             //      LD      D,A
p(" C7B8");                    ;A = MEM[IX+0x02]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+02h)
p(" C7BB");a = A & (1<<2)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     2,A
p(" C7BD");                    ;if (  F.Z ) {cl+=12;goto RMC7C3;}else{cl+= 7;}               ;                                   //      JR      Z,RMC7C3
p(" C7BF");                    ;A = 0x11              ;                                  ;/*cl+= 7*/;                             //      LD      A,11h
p(" C7C1");                    ;goto RMC7CD               ;                                  ;/*cl+=12*/;                             //      JR      RMC7CD
p("     ");RMC7C3:                             //RMC7C3:
p(" C7C3");a = A - 0x10        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      10h
p(" C7C5");                    ;if (  F.C ) {cl+=12;goto RMC7CB;}else{cl+= 7;}               ;                                   //      JR      C,RMC7CB
p(" C7C7");a = A               ;A = -a                ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 8*/;                             //      NEG
p(" C7C9");a = A + 0x14        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     14h
p("     ");RMC7CB:                             //RMC7CB:
p(" C7CB");a = A + 0x20        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     20h
p("     ");RMC7CD:                             //RMC7CD:
p(" C7CD");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C7CF");                    ;*(SP++)=AF            ;                                  ;/*cl+=11*/;                             //      PUSH    AF
p(" C7D0");                    ;IY = 0xBB00             ;                                  ;/*cl+=14*/;                             //      LD      IY,BB00h
p(" C7D4");                    ;DE = 0x0004             ;                                  ;/*cl+=10*/;                             //      LD      DE,0004h
p(" C7D7");                    ;H = 0xFF              ;                                  ;/*cl+= 7*/;                             //      LD      H,FFh
p(" C7D9");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C7DB");                    ;GOS(*(sp++) = (int*)&&C7DB;goto RMC426;C7DB:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC426
p(" C7DE");                    ;AF=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     AF
p(" C7DF");                    ;MEM[IY+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IY+00h),C
p(" C7E2");                    ;MEM[IY+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IY+01h),B
p(" C7E5");                    ;MEM[IY+0x02] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IY+02h),A
p(" C7E8");                    ;MEM[IY+0x03] = 0x08   ;                                  ;/*cl+=19*/;                             //      LD      (IY+03h),08h
p("     ");RMC7EC:                             //RMC7EC:
p(" C7EC");a = MEM[IX+0x03] - 1;MEM[IX+0x03] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      DEC     (IX+03h)
p(" C7EF");cl+=17              ;if (  F.Z ) {GOS(*(sp++) = (int*)&&C7EF;goto RMC837;C7EF:a=a;);};                                   //      CALL    Z,RMC837
p(" C7F2");                    ;A = MEM[IX+0x02]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+02h)
p(" C7F5");a = A - 0x14        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      14h
p(" C7F7");                    ;if ( !F.Z ) {cl+=12;goto RMC7FC;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC7FC
p(" C7F9");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" C7FA");                    ;goto RMC810               ;                                  ;/*cl+=12*/;                             //      JR      RMC810
p("     ");RMC7FC:                             //RMC7FC:
p(" C7FC");a = A - 0x04        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      04h
p(" C7FE");                    ;if ( !F.Z ) {cl+=12;goto RMC803;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC803
p(" C800");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C801");                    ;goto RMC810               ;                                  ;/*cl+=12*/;                             //      JR      RMC810
p("     ");RMC803:                             //RMC803:
p(" C803");a = A - 0x10        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      10h
p(" C805");                    ;if (  F.C ) {cl+=12;goto RMC809;}else{cl+= 7;}               ;                                   //      JR      C,RMC809
p(" C807");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C808");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p("     ");RMC809:                             //RMC809:
p(" C809");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C80A");a = A & 0x0F        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     0Fh
p(" C80C");a = A - 0x02        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      SUB     02h
p(" C80E");a = A + B           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      ADD     B
p(" C80F");                    ;B = A                 ;                                  ;/*cl+= 4*/;                             //      LD      B,A
p("     ");RMC810:                             //RMC810:
p(" C810");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" C812");a = A - 0x10        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      10h
p(" C814");                    ;if (  F.C ) {cl+=12;goto RMC81D;}else{cl+= 7;}               ;                                   //      JR      C,RMC81D
p(" C816");a = A - 0x30        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      30h
p(" C818");                    ;if (  F.C ) {cl+=12;goto RMC829;}else{cl+= 7;}               ;                                   //      JR      C,RMC829
p(" C81A");cl+=17              ;if ( !F.C ) {GOS(*(sp++) = (int*)&&C81A;goto RMC831;C81A:a=a;);};                                   //      CALL    NC,RMC831
p("     ");RMC81D:                             //RMC81D:
p(" C81D");                    ;A = MEM[IX+0x02]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+02h)
p(" C820");a = A + 0x48        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     48h
p(" C822");a = L - 1           ;L = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     L
p(" C823");                    ;if ( !F.Z ) {cl+=12;goto RMC827;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC827
p(" C825");a = A + 0x40        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     40h
p("     ");RMC827:                             //RMC827:
p(" C827");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p("     ");RMC829:                             //RMC829:
p(" C829");                    ;MEM[IX+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IX+00h),C
p(" C82C");                    ;MEM[IX+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),B
p(" C82F");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p(" C830");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP

p("     ");RMC831:                             //RMC831:
p(" C831");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" C833");a = A - 0xF0        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      F0h
p(" C835");                    ;if (  F.C ) {cl+=12;goto RMC89C;}else{cl+= 7;}               ;                                   //      JR      C,RMC89C

p("     ");RMC837:                             //RMC837:
p(" C837");                    ;C = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      C,(IX+00h)
p(" C83A");                    ;B = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      B,(IX+01h)
p(" C83D");                    ;A = MEM[IX+0x03]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+03h)
p(" C840");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" C842");                    ;if (  F.Z ) {cl+=12;goto RMC863;}else{cl+= 7;}               ;                                   //      JR      Z,RMC863
p(" C844");                    ;A = MEM[IX+0x02]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+02h)
p(" C847");a = A - 0x14        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      14h
p(" C849");                    ;if ( !F.Z ) {cl+=12;goto RMC84F;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC84F
p(" C84B");                    ;A = 0x15              ;                                  ;/*cl+= 7*/;                             //      LD      A,15h
p(" C84D");                    ;goto RMC865               ;                                  ;/*cl+=12*/;                             //      JR      RMC865
p("     ");RMC84F:                             //RMC84F:
p(" C84F");a = A - 0x04        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      04h
p(" C851");                    ;if ( !F.Z ) {cl+=12;goto RMC857;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC857
p(" C853");                    ;A = 0x14              ;                                  ;/*cl+= 7*/;                             //      LD      A,14h
p(" C855");                    ;goto RMC865               ;                                  ;/*cl+=12*/;                             //      JR      RMC865
p("     ");RMC857:                             //RMC857:
p(" C857");a = A - 0x10        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      10h
p(" C859");                    ;if ( !F.C ) {cl+=12;goto RMC85F;}else{cl+= 7;}               ;                                   //      JR      NC,RMC85F
p(" C85B");a = A + 0x23        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     23h
p(" C85D");                    ;goto RMC865               ;                                  ;/*cl+=12*/;                             //      JR      RMC865
p("     ");RMC85F:                             //RMC85F:
p(" C85F");a = A + 0x17        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     17h
p(" C861");                    ;goto RMC865               ;                                  ;/*cl+=12*/;                             //      JR      RMC865
p("     ");RMC863:                             //RMC863:
p(" C863");                    ;A = 0x27              ;                                  ;/*cl+= 7*/;                             //      LD      A,27h
p("     ");RMC865:                             //RMC865:
p(" C865");                    ;E = A                 ;                                  ;/*cl+= 4*/;                             //      LD      E,A
p(" C866");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" C868");a = A - 0x40        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      40h
p(" C86A");                    ;if ( !F.C ) {cl+=12;goto RMC876;}else{cl+= 7;}               ;                                   //      JR      NC,RMC876
p(" C86C");a = A - 0x10        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      10h
p(" C86E");                    ;if (  F.C ) {cl+=12;goto RMC876;}else{cl+= 7;}               ;                                   //      JR      C,RMC876
p(" C870");a = A & 0x0F        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     0Fh
p(" C872");a = A - 0x04        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      04h
p(" C874");                    ;if ( !F.C ) {cl+=12;goto RMC896;}else{cl+= 7;}               ;                                   //      JR      NC,RMC896
p("     ");RMC876:                             //RMC876:
p(" C876");                    ;IO[BC] = E            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),E
p(" C878");                    ;A = E                 ;                                  ;/*cl+= 4*/;                             //      LD      A,E
p(" C879");                    ;*(SP++)=AF            ;                                  ;/*cl+=11*/;                             //      PUSH    AF
p(" C87A");                    ;IY = 0xBB00             ;                                  ;/*cl+=14*/;                             //      LD      IY,BB00h
p(" C87E");                    ;DE = 0x0004             ;                                  ;/*cl+=10*/;                             //      LD      DE,0004h
p(" C881");                    ;H = 0xFF              ;                                  ;/*cl+= 7*/;                             //      LD      H,FFh
p(" C883");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C885");                    ;GOS(*(sp++) = (int*)&&C885;goto RMC426;C885:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC426
p(" C888");                    ;AF=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     AF
p(" C889");                    ;MEM[IY+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IY+00h),C
p(" C88C");                    ;MEM[IY+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IY+01h),B
p(" C88F");                    ;MEM[IY+0x02] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IY+02h),A
p(" C892");                    ;MEM[IY+0x03] = 0x10   ;                                  ;/*cl+=19*/;                             //      LD      (IY+03h),10h
p("     ");RMC896:                             //RMC896:
p(" C896");                    ;MEM[IX+0x01] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),00h
p(" C89A");//      POP     DE                             ////      POP     DE
p("     ");sp--;cnt_sp--;                             ////c:sp--;cnt_sp--;
p(" C89B");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET

p("     ");RMC89C:                             //RMC89C:
p(" C89C");a = A - 0x40        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      40h
p(" C89E");cl+=10              ;if (  F.C ) goto RMCA8E   ;                                  ;                                   //      JP      C,RMCA8E
p(" C8A1");a = A - 0xC0        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      C0h
p(" C8A3");cl+=10              ;if ( !F.C ) goto RMC9F1   ;                                  ;                                   //      JP      NC,RMC9F1
p(" C8A6");                    ;D = A                 ;                                  ;/*cl+= 4*/;                             //      LD      D,A
p(" C8A7");a = A ^ L           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 4*/;                             //      XOR     L
p(" C8A8");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C8AA");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C8AB");                    ;if ( !F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NC
p(" C8AC");a = A & 0x0F        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     0Fh
p(" C8AE");a = A - 0x09        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      09h
p(" C8B0");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C8B1");cl+=10              ;if ( !F.C ) goto RMC983   ;                                  ;                                   //      JP      NC,RMC983
p(" C8B4");                    ;A = 0x20              ;                                  ;/*cl+= 7*/;                             //      LD      A,20h
p(" C8B6");                    ;RMB60F[0] = A             ;                                  ;/*cl+=13*/;                             //      LD      (RMB60F),A
p(" C8B9");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C8BA");a = A & 0x1F        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     1Fh
p(" C8BC");a = A - 0x10        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      10h
p(" C8BE");                    ;if (  F.C ) {cl+=12;goto RMC8C1;}else{cl+= 7;}               ;                                   //      JR      C,RMC8C1
p(" C8C0");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p("     ");RMC8C1:                             //RMC8C1:
p(" C8C1");a = A & 0x0F        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     0Fh
p(" C8C3");a = A - 0x03        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      03h
p(" C8C5");                    ;if (  F.C ) {cl+=12;goto RMC8C8;}else{cl+= 7;}               ;                                   //      JR      C,RMC8C8
p(" C8C7");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p("     ");RMC8C8:                             //RMC8C8:
p(" C8C8");                    ;IY = 0xB610             ;                                  ;/*cl+=14*/;                             //      LD      IY,B610h
p(" C8CC");                    ;DE = 0x0010             ;                                  ;/*cl+=10*/;                             //      LD      DE,0010h
p(" C8CF");                    ;H = 0x3F              ;                                  ;/*cl+= 7*/;                             //      LD      H,3Fh
p("     ");RMC8D1:                             //RMC8D1:
p(" C8D1");                    ;A = B                 ;                                  ;/*cl+= 4*/;                             //      LD      A,B
p(" C8D2");                    ;GOS(*(sp++) = (int*)&&C8D2;goto RMC426;C8D2:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC426
p(" C8D5");                    ;A = MEM[IY+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IY+00h)
p(" C8D8");a = IY + DE         ;IY = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IY,DE
p(" C8DA");a = H - 1           ;H = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     H
p(" C8DB");a = H + 1           ;H = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     H
p(" C8DC");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z
p(" C8DD");a = H - 1           ;H = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     H
p(" C8DE");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z
p(" C8DF");a = A - C           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      C
p(" C8E0");                    ;if ( !F.Z ) {cl+=12;goto RMC8D1;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC8D1
p(" C8E2");                    ;DE = 0xFFF0             ;                                  ;/*cl+=10*/;                             //      LD      DE,FFF0h
p(" C8E5");a = IY + DE         ;IY = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IY,DE
p(" C8E7");a = MEM[IY+0x09] - 1;MEM[IY+0x09] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      DEC     (IY+09h)
p(" C8EA");                    ;if ( !F.Z ) {cl+=12;goto RMC93B;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC93B
p(" C8EC");                    ;MEM[IY+0x01] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IY+01h),00h
p(" C8F0");                    ;MEM[IX+0x01] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),00h
p(" C8F4");                    ;IY = 0xBB00             ;                                  ;/*cl+=14*/;                             //      LD      IY,BB00h
p(" C8F8");                    ;DE = 0x0004             ;                                  ;/*cl+=10*/;                             //      LD      DE,0004h
p(" C8FB");                    ;H = 0xFF              ;                                  ;/*cl+= 7*/;                             //      LD      H,FFh
p(" C8FD");                    ;A = 0x2A              ;                                  ;/*cl+= 7*/;                             //      LD      A,2Ah
p(" C8FF");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C901");                    ;GOS(*(sp++) = (int*)&&C901;goto RMC926;C901:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC926
p(" C904");                    ;A = 0x26              ;                                  ;/*cl+= 7*/;                             //      LD      A,26h
p(" C906");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" C907");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C909");                    ;GOS(*(sp++) = (int*)&&C909;goto RMC926;C909:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC926
p(" C90C");                    ;A = 0x24              ;                                  ;/*cl+= 7*/;                             //      LD      A,24h
p(" C90E");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" C90F");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C911");                    ;GOS(*(sp++) = (int*)&&C911;goto RMC926;C911:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC926
p(" C914");                    ;A = 0x28              ;                                  ;/*cl+= 7*/;                             //      LD      A,28h
p(" C916");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" C917");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C919");                    ;GOS(*(sp++) = (int*)&&C919;goto RMC926;C919:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC926
p(" C91C");//      POP     AF                             ////      POP     AF
p("     ");sp--;cnt_sp--;                             ////c:sp--;cnt_sp--;
p(" C91D");                    ;A = L                 ;                                  ;/*cl+= 4*/;                             //      LD      A,L
p(" C91E");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" C91F");                    ;if (  F.Z ) {cl+=12;goto RMC926;}else{cl+= 7;}               ;                                   //      JR      Z,RMC926
p(" C921");                    ;A = 0x30              ;                                  ;/*cl+= 7*/;                             //      LD      A,30h
p(" C923");                    ;GOS(*(sp++) = (int*)&&C923;goto RMCBCD;C923:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCBCD
p("     ");RMC926:                             //RMC926:
p(" C926");                    ;*(SP++)=AF            ;                                  ;/*cl+=11*/;                             //      PUSH    AF
p(" C927");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" C929");                    ;GOS(*(sp++) = (int*)&&C929;goto RMC426;C929:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC426
p(" C92C");                    ;AF=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     AF
p(" C92D");                    ;MEM[IY+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IY+00h),C
p(" C930");                    ;MEM[IY+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IY+01h),B
p(" C933");                    ;MEM[IY+0x02] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IY+02h),A
p(" C936");                    ;MEM[IY+0x03] = 0x20   ;                                  ;/*cl+=19*/;                             //      LD      (IY+03h),20h
p(" C93A");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC93B:                             //RMC93B:
p(" C93B");                    ;A = MEM[IX+0x02]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+02h)
p(" C93E");                    ;E = 0x01              ;                                  ;/*cl+= 7*/;                             //      LD      E,01h
p(" C940");a = A & (1<<3)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     3,A
p(" C942");                    ;if ( !F.Z ) {cl+=12;goto RMC949;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC949
p(" C944");a = A - 0x10        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      10h
p(" C946");                    ;if ( !F.C ) {cl+=12;goto RMC94A;}else{cl+= 7;}               ;                                   //      JR      NC,RMC94A
p(" C948");a = E - 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     E
p("     ");RMC949:                             //RMC949:
p(" C949");a = E - 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     E
p("     ");RMC94A:                             //RMC94A:
p(" C94A");                    ;MEM[IY+0x02] = E      ;                                  ;/*cl+=19*/;                             //      LD      (IY+02h),E
p(" C94D");a = A - 0x14        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      14h
p(" C94F");                    ;if (  F.Z ) {cl+=12;goto RMC95F;}else{cl+= 7;}               ;                                   //      JR      Z,RMC95F
p(" C951");a = A - 0x04        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      04h
p(" C953");                    ;if (  F.Z ) {cl+=12;goto RMC963;}else{cl+= 7;}               ;                                   //      JR      Z,RMC963
p(" C955");a = A & 0x0F        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     0Fh
p(" C957");a = A - 0x02        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      SUB     02h
p(" C959");a = A<<1            ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 8*/;                             //      SLA     A
p(" C95B");a = A<<1            ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 8*/;                             //      SLA     A
p(" C95D");                    ;goto RMC965               ;                                  ;/*cl+=12*/;                             //      JR      RMC965
p("     ");RMC95F:                             //RMC95F:
p(" C95F");                    ;A = 0xFC              ;                                  ;/*cl+= 7*/;                             //      LD      A,FCh
p(" C961");                    ;goto RMC965               ;                                  ;/*cl+=12*/;                             //      JR      RMC965
p("     ");RMC963:                             //RMC963:
p(" C963");                    ;A = 0x04              ;                                  ;/*cl+= 7*/;                             //      LD      A,04h
p("     ");RMC965:                             //RMC965:
p(" C965");                    ;MEM[IY+0x03] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IY+03h),A
p(" C968");                    ;*(SP++)=BC            ;                                  ;/*cl+=11*/;                             //      PUSH    BC
p(" C969");                    ;*(SP++)=HL            ;                                  ;/*cl+=11*/;                             //      PUSH    HL
p(" C96A");                    ;*(SP++)=IX            ;                                  ;/*cl+=15*/;                             //      PUSH    IX
p(" C96C");                    ;*(SP++)=IY            ;                                  ;/*cl+=15*/;                             //      PUSH    IY
p(" C96E");                    ;IX=*(--SP)            ;                                  ;/*cl+=14*/;                             //      POP     IX
p(" C970");                    ;GOS(*(sp++) = (int*)&&C970;goto RMC00D;C970:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC00D
p(" C973");                    ;IX=*(--SP)            ;                                  ;/*cl+=14*/;                             //      POP     IX
p(" C975");                    ;HL=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     HL
p(" C976");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p(" C977");                    ;A = L                 ;                                  ;/*cl+= 4*/;                             //      LD      A,L
p(" C978");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" C979");                    ;if (  F.Z ) {cl+=12;goto RMC980;}else{cl+= 7;}               ;                                   //      JR      Z,RMC980
p(" C97B");                    ;A = 0x03              ;                                  ;/*cl+= 7*/;                             //      LD      A,03h
p(" C97D");                    ;GOS(*(sp++) = (int*)&&C97D;goto RMCBCD;C97D:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCBCD
p("     ");RMC980:                             //RMC980:
p(" C980");                    ;goto RMC837               ;                                  ;/*cl+=10*/;                             //      JP      RMC837
p("     ");RMC983:                             //RMC983:
p(" C983");a = A & 0xF0        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     F0h
p(" C985");a = A - 0x40        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      40h
p(" C987");                    ;if (  F.Z ) {cl+=12;goto RMC992;}else{cl+= 7;}               ;                                   //      JR      Z,RMC992
p(" C989");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C98B");                    ;if (  F.Z ) {cl+=12;goto RMC992;}else{cl+= 7;}               ;                                   //      JR      Z,RMC992
p(" C98D");a = A - 0x90        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      90h
p(" C98F");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C990");                    ;if ( !F.Z ) {cl+=12;goto RMC9C9;}else{cl+= 7;}               ;                                   //      JR      NZ,RMC9C9
p("     ");RMC992:                             //RMC992:
p(" C992");                    ;IY = 0xBA00             ;                                  ;/*cl+=14*/;                             //      LD      IY,BA00h
p(" C996");                    ;H = 0x20              ;                                  ;/*cl+= 7*/;                             //      LD      H,20h
p(" C998");                    ;DE = 0x0004             ;                                  ;/*cl+=10*/;                             //      LD      DE,0004h
p("     ");RMC99B:                             //RMC99B:
p(" C99B");                    ;A = B                 ;                                  ;/*cl+= 4*/;                             //      LD      A,B
p(" C99C");                    ;GOS(*(sp++) = (int*)&&C99C;goto RMC426;C99C:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC426
p(" C99F");                    ;A = C                 ;                                  ;/*cl+= 4*/;                             //      LD      A,C
p(" C9A0");a = A - MEM[IY+0x00];                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+=19*/;                             //      CP      (IY+00h)
p(" C9A3");                    ;if (  F.Z ) {cl+=12;goto RMC9AF;}else{cl+= 7;}               ;                                   //      JR      Z,RMC9AF
p(" C9A5");                    ;A = H                 ;                                  ;/*cl+= 4*/;                             //      LD      A,H
p(" C9A6");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" C9A8");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z
p(" C9A9");a = H - 1           ;H = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     H
p(" C9AA");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z
p(" C9AB");a = IY + DE         ;IY = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IY,DE
p(" C9AD");                    ;goto RMC99B               ;                                  ;/*cl+=12*/;                             //      JR      RMC99B
p("     ");RMC9AF:                             //RMC9AF:
p(" C9AF");                    ;MEM[IX+0x01] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),00h
p(" C9B3");                    ;MEM[IY+0x01] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IY+01h),00h
p(" C9B7");                    ;IY = 0xBB00             ;                                  ;/*cl+=14*/;                             //      LD      IY,BB00h
p(" C9BB");                    ;DE = 0x0004             ;                                  ;/*cl+=10*/;                             //      LD      DE,0004h
p(" C9BE");                    ;H = 0xFF              ;                                  ;/*cl+= 7*/;                             //      LD      H,FFh
p(" C9C0");                    ;A = 0x27              ;                                  ;/*cl+= 7*/;                             //      LD      A,27h
p(" C9C2");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" C9C4");                    ;GOS(*(sp++) = (int*)&&C9C4;goto RMC926;C9C4:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC926
p(" C9C7");//      POP     DE                             ////      POP     DE
p("     ");sp--;cnt_sp--;                             ////c:sp--;cnt_sp--;
p(" C9C8");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMC9C9:                             //RMC9C9:
p(" C9C9");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" C9CB");cl+=10              ;if ( !F.C ) goto RMCA8E   ;                                  ;                                   //      JP      NC,RMCA8E
p(" C9CE");a = A - 0x69        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      69h
p(" C9D0");cl+=10              ;if (  F.C ) goto RMCA8E   ;                                  ;                                   //      JP      C,RMCA8E
p(" C9D3");                    ;A = 0x20              ;                                  ;/*cl+= 7*/;                             //      LD      A,20h
p(" C9D5");                    ;RMB60F[0] = A             ;                                  ;/*cl+=13*/;                             //      LD      (RMB60F),A
p(" C9D8");                    ;IY = 0xB600             ;                                  ;/*cl+=14*/;                             //      LD      IY,B600h
p(" C9DC");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C9DD");a = A - 0x6A        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      6Ah
p(" C9DF");                    ;if (  F.Z ) {cl+=12;goto RMC9EB;}else{cl+= 7;}               ;                                   //      JR      Z,RMC9EB
p(" C9E1");a = A - 0x6B        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      6Bh
p(" C9E3");                    ;if (  F.Z ) {cl+=12;goto RMC9EB;}else{cl+= 7;}               ;                                   //      JR      Z,RMC9EB
p(" C9E5");a = MEM[IY+0x04] - 1;MEM[IY+0x04] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      DEC     (IY+04h)
p(" C9E8");                    ;goto RMC837               ;                                  ;/*cl+=10*/;                             //      JP      RMC837
p("     ");RMC9EB:                             //RMC9EB:
p(" C9EB");a = MEM[IY+0x19] - 1;MEM[IY+0x19] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      DEC     (IY+19h)
p(" C9EE");                    ;goto RMC837               ;                                  ;/*cl+=10*/;                             //      JP      RMC837
p("     ");RMC9F1:                             //RMC9F1:
p(" C9F1");a = A - 0xE0        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      E0h
p(" C9F3");cl+=10              ;if ( !F.C ) goto RMCA8E   ;                                  ;                                   //      JP      NC,RMCA8E
p(" C9F6");                    ;D = A                 ;                                  ;/*cl+= 4*/;                             //      LD      D,A
p(" C9F7");                    ;A = L                 ;                                  ;/*cl+= 4*/;                             //      LD      A,L
p(" C9F8");a = A - 0x01        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      01h
p(" C9FA");cl+=10              ;if (  F.Z ) goto RMC837   ;                                  ;                                   //      JP      Z,RMC837
p(" C9FD");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" C9FE");a = A - 0xDF        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      DFh
p(" CA00");                    ;if (  F.Z ) {cl+=12;goto RMCA12;}else{cl+= 7;}               ;                                   //      JR      Z,RMCA12
p(" CA02");a = A & 0x0F        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     0Fh
p(" CA04");a = A - 0x0E        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      0Eh
p(" CA06");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" CA07");                    ;if ( !F.C ) {cl+=12;goto RMCA1B;}else{cl+= 7;}               ;                                   //      JR      NC,RMCA1B
p(" CA09");a = A & 0x0F        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     0Fh
p(" CA0B");a = A - 0x0D        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      0Dh
p(" CA0D");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" CA0E");                    ;if (  F.Z ) {cl+=12;goto RMCA77;}else{cl+= 7;}               ;                                   //      JR      Z,RMCA77
p(" CA10");                    ;goto RMCA34               ;                                  ;/*cl+=12*/;                             //      JR      RMCA34
p("     ");RMCA12:                             //RMCA12:
p(" CA12");                    ;MEM[IX+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IX+00h),C
p(" CA15");                    ;MEM[IX+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),B
p(" CA18");                    ;goto RMC837               ;                                  ;/*cl+=10*/;                             //      JP      RMC837
p("     ");RMCA1B:                             //RMCA1B:
p(" CA1B");                    ;BC = 0xAA06             ;                                  ;/*cl+=10*/;                             //      LD      BC,AA06h
p(" CA1E");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" CA1F");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" CA21");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CA23");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CA24");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CA26");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CA27");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CA29");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" CA2A");                    ;GOS(*(sp++) = (int*)&&CA2A;goto RMC5A9;CA2A:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC5A9
p(" CA2D");//      POP     DE                             ////      POP     DE
p("     ");sp--;cnt_sp--;                             ////c:sp--;cnt_sp--;
p(" CA2E");                    ;A = 0x70              ;                                  ;/*cl+= 7*/;                             //      LD      A,70h
p(" CA30");                    ;GOS(*(sp++) = (int*)&&CA30;goto RMCBCD;CA30:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCBCD
p(" CA33");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMCA34:                             //RMCA34:
p(" CA34");a = A - 0xD0        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      D0h
p(" CA36");                    ;if (  F.C ) {cl+=12;goto RMCA39;}else{cl+= 7;}               ;                                   //      JR      C,RMCA39
p(" CA38");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p("     ");RMCA39:                             //RMCA39:
p(" CA39");                    ;IY = 0xBF00             ;                                  ;/*cl+=14*/;                             //      LD      IY,BF00h
p(" CA3D");                    ;DE = 0x0004             ;                                  ;/*cl+=10*/;                             //      LD      DE,0004h
p(" CA40");                    ;H = 0x20              ;                                  ;/*cl+= 7*/;                             //      LD      H,20h
p("     ");RMCA42:                             //RMCA42:
p(" CA42");                    ;A = B                 ;                                  ;/*cl+= 4*/;                             //      LD      A,B
p(" CA43");                    ;GOS(*(sp++) = (int*)&&CA43;goto RMC426;CA43:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC426
p(" CA46");                    ;A = MEM[IY+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IY+00h)
p(" CA49");a = A - C           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      C
p(" CA4A");                    ;if (  F.Z ) {cl+=12;goto RMCA56;}else{cl+= 7;}               ;                                   //      JR      Z,RMCA56
p(" CA4C");                    ;A = H                 ;                                  ;/*cl+= 4*/;                             //      LD      A,H
p(" CA4D");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" CA4F");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z
p(" CA50");a = H - 1           ;H = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     H
p(" CA51");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z
p(" CA52");a = IY + DE         ;IY = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IY,DE
p(" CA54");                    ;goto RMCA42               ;                                  ;/*cl+=12*/;                             //      JR      RMCA42
p("     ");RMCA56:                             //RMCA56:
p(" CA56");                    ;A = 0x03              ;                                  ;/*cl+= 7*/;                             //      LD      A,03h
p(" CA58");                    ;GOS(*(sp++) = (int*)&&CA58;goto RMCBCD;CA58:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCBCD
p(" CA5B");a = MEM[IY+0x03] - 1;MEM[IY+0x03] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      DEC     (IY+03h)
p(" CA5E");cl+=10              ;if ( !F.Z ) goto RMC837   ;                                  ;                                   //      JP      NZ,RMC837
p(" CA61");                    ;MEM[IY+0x01] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IY+01h),00h
p(" CA65");                    ;D = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      D,00h
p(" CA67");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p(" CA69");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CA6A");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p(" CA6C");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" CA6D");                    ;GOS(*(sp++) = (int*)&&CA6D;goto RMC5A9;CA6D:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC5A9
p(" CA70");//      POP     DE                             ////      POP     DE
p("     ");sp--;cnt_sp--;                             ////c:sp--;cnt_sp--;
p(" CA71");                    ;A = 0x47              ;                                  ;/*cl+= 7*/;                             //      LD      A,47h
p(" CA73");                    ;GOS(*(sp++) = (int*)&&CA73;goto RMCBCD;CA73:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCBCD
p(" CA76");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMCA77:                             //RMCA77:
p(" CA77");a = A - 0xD0        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      D0h
p(" CA79");                    ;if (  F.C ) {cl+=12;goto RMCA7C;}else{cl+= 7;}               ;                                   //      JR      C,RMCA7C
p(" CA7B");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p("     ");RMCA7C:                             //RMCA7C:
p(" CA7C");                    ;A = 0x60              ;                                  ;/*cl+= 7*/;                             //      LD      A,60h
p(" CA7E");                    ;GOS(*(sp++) = (int*)&&CA7E;goto RMCBCD;CA7E:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCBCD
p(" CA81");                    ;D = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      D,00h
p(" CA83");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p(" CA85");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CA86");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p(" CA88");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" CA89");                    ;GOS(*(sp++) = (int*)&&CA89;goto RMC5A9;CA89:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC5A9
p(" CA8C");//      POP     DE                             ////      POP     DE
p("     ");sp--;cnt_sp--;                             ////c:sp--;cnt_sp--;
p(" CA8D");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMCA8E:                             //RMCA8E:
p(" CA8E");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p(" CA8F");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p("     ");RMCA90:                             //RMCA90:
p(" CA90");                    ;A = RMB618[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB618)
p(" CA93");                    ;BC = 0xD1AE             ;                                  ;/*cl+=10*/;                             //      LD      BC,D1AEh
p(" CA96");a = A<<1            ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 8*/;                             //      SLA     A
p(" CA98");                    ;GOS(*(sp++) = (int*)&&CA98;goto RMCAC7;CA98:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCAC7
p(" CA9B");                    ;A = RMB615[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB615)
p(" CA9E");                    ;BC = 0xD1FE             ;                                  ;/*cl+=10*/;                             //      LD      BC,D1FEh
p(" CAA1");                    ;GOS(*(sp++) = (int*)&&CAA1;goto RMCAC7;CAA1:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCAC7
p(" CAA4");                    ;A = RMB619[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB619)
p(" CAA7");                    ;BC = 0xC24E             ;                                  ;/*cl+=10*/;                             //      LD      BC,C24Eh
p(" CAAA");                    ;GOS(*(sp++) = (int*)&&CAAA;goto RMCAEC;CAAA:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCAEC
p(" CAAD");                    ;A = RMB604[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB604)
p(" CAB0");                    ;BC = 0xC29E             ;                                  ;/*cl+=10*/;                             //      LD      BC,C29Eh
p(" CAB3");                    ;GOS(*(sp++) = (int*)&&CAB3;goto RMCAEC;CAB3:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCAEC
p(" CAB6");                    ;BC = 0xC2EE             ;                                  ;/*cl+=10*/;                             //      LD      BC,C2EEh
p(" CAB9");                    ;D = 0x03              ;                                  ;/*cl+= 7*/;                             //      LD      D,03h
p(" CABB");                    ;HL = 0xB607             ;                                  ;/*cl+=10*/;                             //      LD      HL,B607h
p("     ");RMCABE:                             //RMCABE:
p(" CABE");                    ;A = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      A,(HL)
p(" CABF");                    ;GOS(*(sp++) = (int*)&&CABF;goto RMCB0D;CABF:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCB0D
p(" CAC2");                    ;HL--                  ;                                  ;/*cl+= 6*/;                             //      DEC     HL
p(" CAC3");a = D - 1           ;D = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     D
p(" CAC4");                    ;if ( !F.Z ) {cl+=12;goto RMCABE;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCABE
p(" CAC6");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMCAC7:                             //RMCAC7:
p(" CAC7");                    ;D = 0xFF              ;                                  ;/*cl+= 7*/;                             //      LD      D,FFh
p(" CAC9");                    ;E = 0x08              ;                                  ;/*cl+= 7*/;                             //      LD      E,08h
p("     ");RMCACB:                             //RMCACB:
p(" CACB");a = A - 0x04        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      SUB     04h
p(" CACD");                    ;if (  F.C ) {cl+=12;goto RMCAD6;}else{cl+= 7;}               ;                                   //      JR      C,RMCAD6
p(" CACF");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p(" CAD1");                    ;BC++                  ;                                  ;/*cl+= 6*/;                             //      INC     BC
p(" CAD2");a = E - 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     E
p(" CAD3");                    ;if ( !F.Z ) {cl+=12;goto RMCACB;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCACB
p(" CAD5");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMCAD6:                             //RMCAD6:
p(" CAD6");                    ;D = 0xFC              ;                                  ;/*cl+= 7*/;                             //      LD      D,FCh
p("     ");RMCAD8:                             //RMCAD8:
p(" CAD8");a = A + 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     A
p(" CAD9");                    ;if (  F.Z ) {cl+=12;goto RMCAE1;}else{cl+= 7;}               ;                                   //      JR      Z,RMCAE1
p(" CADB");a = D<<1            ;D = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 8*/;                             //      SLA     D
p(" CADD");a = D<<1            ;D = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 8*/;                             //      SLA     D
p(" CADF");                    ;goto RMCAD8               ;                                  ;/*cl+=12*/;                             //      JR      RMCAD8
p("     ");RMCAE1:                             //RMCAE1:
p(" CAE1");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p(" CAE3");                    ;D = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      D,00h
p("     ");RMCAE5:                             //RMCAE5:
p(" CAE5");                    ;BC++                  ;                                  ;/*cl+= 6*/;                             //      INC     BC
p(" CAE6");a = E - 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     E
p(" CAE7");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z
p(" CAE8");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p(" CAEA");                    ;goto RMCAE5               ;                                  ;/*cl+=12*/;                             //      JR      RMCAE5
p("     ");RMCAEC:                             //RMCAEC:
p(" CAEC");                    ;*(SP++)=HL            ;                                  ;/*cl+=11*/;                             //      PUSH    HL
p(" CAED");                    ;*(SP++)=DE            ;                                  ;/*cl+=11*/;                             //      PUSH    DE
p(" CAEE");                    ;*(SP++)=BC            ;                                  ;/*cl+=11*/;                             //      PUSH    BC
p(" CAEF");a = A<<1            ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 8*/;                             //      SLA     A
p(" CAF1");a = A<<1            ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 8*/;                             //      SLA     A
p(" CAF3");a = A<<1            ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 8*/;                             //      SLA     A
p(" CAF5");                    ;D = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      D,00h
p(" CAF7");                    ;E = A                 ;                                  ;/*cl+= 4*/;                             //      LD      E,A
p(" CAF8");                    ;HL = 0xCB22             ;                                  ;/*cl+=10*/;                             //      LD      HL,CB22h
p(" CAFB");a = HL + DE         ;HL = a                ;                   ;F.C=a>>16     ;/*cl+=13*/;                             //      ADD     HL,DE
p(" CAFC");                    ;D = 0x08              ;                                  ;/*cl+= 7*/;                             //      LD      D,08h
p("     ");RMCAFE:                             //RMCAFE:
p(" CAFE");                    ;A = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      A,(HL)
p(" CAFF");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CB01");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CB02");                    ;A = 0x08              ;                                  ;/*cl+= 7*/;                             //      LD      A,08h
p(" CB04");a = A + B           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      ADD     B
p(" CB05");                    ;B = A                 ;                                  ;/*cl+= 4*/;                             //      LD      B,A
p(" CB06");a = D - 1           ;D = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     D
p(" CB07");                    ;if ( !F.Z ) {cl+=12;goto RMCAFE;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCAFE
p(" CB09");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p(" CB0A");                    ;DE=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     DE
p(" CB0B");                    ;HL=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     HL
p(" CB0C");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMCB0D:                             //RMCB0D:
p(" CB0D");                    ;*(SP++)=AF            ;                                  ;/*cl+=11*/;                             //      PUSH    AF
p(" CB0E");a = A               ;A=(a>>1)              ;F.Z=((a&0xff)==0)  ;F.C=a&1       ;/*cl+= 8*/;                             //      SRL     A
p(" CB10");a = A               ;A=(a>>1)              ;F.Z=((a&0xff)==0)  ;F.C=a&1       ;/*cl+= 8*/;                             //      SRL     A
p(" CB12");a = A               ;A=(a>>1)              ;F.Z=((a&0xff)==0)  ;F.C=a&1       ;/*cl+= 8*/;                             //      SRL     A
p(" CB14");a = A               ;A=(a>>1)              ;F.Z=((a&0xff)==0)  ;F.C=a&1       ;/*cl+= 8*/;                             //      SRL     A
p(" CB16");                    ;GOS(*(sp++) = (int*)&&CB16;goto RMCAEC;CB16:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCAEC
p(" CB19");                    ;BC++                  ;                                  ;/*cl+= 6*/;                             //      INC     BC
p(" CB1A");                    ;AF=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     AF
p(" CB1B");a = A & 0x0F        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 7*/;                             //      AND     0Fh
p(" CB1D");                    ;GOS(*(sp++) = (int*)&&CB1D;goto RMCAEC;CB1D:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCAEC
p(" CB20");                    ;BC++                  ;                                  ;/*cl+= 6*/;                             //      INC     BC
p(" CB21");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMCB72:                             //RMCB72:
p(" CB72");                    ;BC = 0x1C00             ;                                  ;/*cl+=10*/;                             //      LD      BC,1C00h
p("     ");RMCB75:                             //RMCB75:
p(" CB75");                    ;A = RMB618[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB618)
p(" CB78");a = A + 0x24        ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     24h
p(" CB7A");a = A - 0x2F        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      2Fh
p(" CB7C");                    ;if (  F.C ) {cl+=12;goto RMCB80;}else{cl+= 7;}               ;                                   //      JR      C,RMCB80
p(" CB7E");                    ;A = 0x2E              ;                                  ;/*cl+= 7*/;                             //      LD      A,2Eh
p("     ");RMCB80:                             //RMCB80:
p(" CB80");                    ;E = 0x0B              ;                                  ;/*cl+= 7*/;                             //      LD      E,0Bh
p(" CB82");                    ;IO[BC] = E            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),E
p(" CB84");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" CB85");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p("     ");	sys.sound.psg_Set( E, A );                             ////c:	sys.sound.psg_Set( E, A );
p(" CB87");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CB88");                    ;A = RMB60F[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB60F)
p(" CB8B");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" CB8D");                    ;if (  F.Z ) {cl+=12;goto RMCB90;}else{cl+= 7;}               ;                                   //      JR      Z,RMCB90
p(" CB8F");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p("     ");RMCB90:                             //RMCB90:
p(" CB90");                    ;RMB60F[0] = A             ;                                  ;/*cl+=13*/;                             //      LD      (RMB60F),A
p(" CB93");a = A - 0x20        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      20h
p(" CB95");                    ;if (  F.C ) {cl+=12;goto RMCB99;}else{cl+= 7;}               ;                                   //      JR      C,RMCB99
p(" CB97");                    ;A = 0x1F              ;                                  ;/*cl+= 7*/;                             //      LD      A,1Fh
p("     ");RMCB99:                             //RMCB99:
p(" CB99");                    ;E = 0x09              ;                                  ;/*cl+= 7*/;                             //      LD      E,09h
p(" CB9B");                    ;IO[BC] = E            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),E
p(" CB9D");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" CB9E");a = A               ;A=(a>>1)              ;F.Z=((a&0xff)==0)  ;F.C=a&1       ;/*cl+= 8*/;                             //      SRL     A
p(" CBA0");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p("     ");	sys.sound.psg_Set( E, A );                             ////c:	sys.sound.psg_Set( E, A );
p(" CBA2");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CBA3");                    ;D = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      D,00h
p(" CBA5");                    ;IX = 0xBA00             ;                                  ;/*cl+=14*/;                             //      LD      IX,BA00h
p(" CBA9");                    ;E = 0x04              ;                                  ;/*cl+= 7*/;                             //      LD      E,04h
p("     ");RMCBAB:                             //RMCBAB:
p(" CBAB");                    ;A = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+01h)
p(" CBAE");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" CBB0");                    ;if (  F.Z ) {cl+=12;goto RMCBB9;}else{cl+= 7;}               ;                                   //      JR      Z,RMCBB9
p(" CBB2");                    ;A = MEM[IX+0x03]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+03h)
p(" CBB5");a = A - D           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      D
p(" CBB6");                    ;if (  F.C ) {cl+=12;goto RMCBB9;}else{cl+= 7;}               ;                                   //      JR      C,RMCBB9
p(" CBB8");                    ;D = A                 ;                                  ;/*cl+= 4*/;                             //      LD      D,A
p("     ");RMCBB9:                             //RMCBB9:
p(" CBB9");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" CBBB");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" CBBD");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" CBBF");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" CBC1");a = E - 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     E
p(" CBC2");                    ;if ( !F.Z ) {cl+=12;goto RMCBAB;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCBAB
p(" CBC4");                    ;A = D                 ;                                  ;/*cl+= 4*/;                             //      LD      A,D
p(" CBC5");                    ;E = 0x0A              ;                                  ;/*cl+= 7*/;                             //      LD      E,0Ah
p(" CBC7");                    ;IO[BC] = E            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),E
p(" CBC9");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" CBCA");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p("     ");	sys.sound.psg_Set( E, A );                             ////c:	sys.sound.psg_Set( E, A );
p(" CBCC");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMCBCD:                             //RMCBCD:
p(" CBCD");                    ;*(SP++)=HL            ;                                  ;/*cl+=11*/;                             //      PUSH    HL
p(" CBCE");                    ;HL = 0xB605             ;                                  ;/*cl+=10*/;                             //      LD      HL,B605h
p(" CBD1");a = A + MEM[HL]     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADD     (HL)
p(" CBD2");{	int	h = (A>>4)&0x0f;	int l = (A&0x0f);	F.C = 0;	if ( l >= 10 )	{l-=10;h++;}	if ( h >= 10 )	{h-=10;F.C=1;}	A = (h<<4)|l;}		;/*cl+= 4*/;                             //      DAA
p(" CBD3");                    ;MEM[HL] = A           ;                                  ;/*cl+= 7*/;                             //      LD      (HL),A
p(" CBD4");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CBD5");                    ;A = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      A,(HL)
p(" CBD6");a = A + 0x00 + F.C  ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADC     00h
p(" CBD8");{	int	h = (A>>4)&0x0f;	int l = (A&0x0f);	F.C = 0;	if ( l >= 10 )	{l-=10;h++;}	if ( h >= 10 )	{h-=10;F.C=1;}	A = (h<<4)|l;}		;/*cl+= 4*/;                             //      DAA
p(" CBD9");                    ;MEM[HL] = A           ;                                  ;/*cl+= 7*/;                             //      LD      (HL),A
p(" CBDA");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CBDB");                    ;A = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      A,(HL)
p(" CBDC");a = A + 0x00 + F.C  ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      ADC     00h
p(" CBDE");{	int	h = (A>>4)&0x0f;	int l = (A&0x0f);	F.C = 0;	if ( l >= 10 )	{l-=10;h++;}	if ( h >= 10 )	{h-=10;F.C=1;}	A = (h<<4)|l;}		;/*cl+= 4*/;                             //      DAA
p(" CBDF");                    ;MEM[HL] = A           ;                                  ;/*cl+= 7*/;                             //      LD      (HL),A
p(" CBE0");                    ;HL = 0xB60F             ;                                  ;/*cl+=10*/;                             //      LD      HL,B60Fh
p(" CBE3");                    ;MEM[HL] = 0x20        ;                                  ;/*cl+=10*/;                             //      LD      (HL),20h
p(" CBE5");                    ;HL=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     HL
p(" CBE6");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p(" CBE7");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p("     ");RMCBE8:                             //RMCBE8:
p(" CBE8");                    ;IX = 0xBF70             ;                                  ;/*cl+=14*/;                             //      LD      IX,BF70h
p(" CBEC");                    ;E = 0x04              ;                                  ;/*cl+= 7*/;                             //      LD      E,04h
p("     ");RMCBEE:                             //RMCBEE:
p(" CBEE");                    ;A = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+01h)
p(" CBF1");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" CBF3");cl+=17              ;if ( !F.Z ) {GOS(*(sp++) = (int*)&&CBF3;goto RMCC02;CBF3:a=a;);};                                   //      CALL    NZ,RMCC02
p(" CBF6");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" CBF8");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" CBFA");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" CBFC");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" CBFE");a = E - 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     E
p(" CBFF");                    ;if ( !F.Z ) {cl+=12;goto RMCBEE;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCBEE
p(" CC01");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMCC02:                             //RMCC02:
p(" CC02");                    ;C = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      C,(IX+00h)
p(" CC05");                    ;B = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      B,(IX+01h)
p(" CC08");                    ;*(SP++)=BC            ;                                  ;/*cl+=11*/;                             //      PUSH    BC
p(" CC09");                    ;IY=*(--SP)            ;                                  ;/*cl+=14*/;                             //      POP     IY
p(" CC0B");a = MEM[IX+0x02] - 1;MEM[IX+0x02] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      DEC     (IX+02h)
p(" CC0E");                    ;A = 0x07              ;                                  ;/*cl+= 7*/;                             //      LD      A,07h
p(" CC10");a = A & MEM[IX+0x02];A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+=19*/;                             //      AND     (IX+02h)
p(" CC13");                    ;if ( !F.Z ) {cl+=12;goto RMCC1A;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCC1A
p(" CC15");a = rand()          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 9*/;                             //      LD      A,R
p(" CC17");                    ;MEM[IX+0x02] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+02h),A
p("     ");RMCC1A:                             //RMCC1A:
p(" CC1A");                    ;A = MEM[IX+0x02]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+02h)
p(" CC1D");a = A & (1<<3)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     3,A
p(" CC1F");                    ;if (  F.Z ) {cl+=12;goto RMCC23;}else{cl+= 7;}               ;                                   //      JR      Z,RMCC23
p(" CC21");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" CC22");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p("     ");RMCC23:                             //RMCC23:
p(" CC23");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CC24");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" CC26");                    ;if ( !F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NZ
p(" CC27");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CC28");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" CC2A");                    ;if ( !F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NZ
p(" CC2B");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" CC2C");                    ;MEM[IX+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),B
p(" CC2F");                    ;HL = 0xC3D3             ;                                  ;/*cl+=10*/;                             //      LD      HL,C3D3h
p(" CC32");                    ;IO[BC] = H            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),H
p(" CC34");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CC35");                    ;IO[BC] = L            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),L
p(" CC37");                    ;*(SP++)=IY            ;                                  ;/*cl+=15*/;                             //      PUSH    IY
p(" CC39");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p(" CC3A");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" CC3C");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CC3E");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CC3F");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CC41");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMCC42:                             //RMCC42:
p(" CC42");                    ;IX = 0xBF80             ;                                  ;/*cl+=14*/;                             //      LD      IX,BF80h
p(" CC46");                    ;E = 0x10              ;                                  ;/*cl+= 7*/;                             //      LD      E,10h
p("     ");RMCC48:                             //RMCC48:
p(" CC48");                    ;A = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+01h)
p(" CC4B");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" CC4D");cl+=17              ;if ( !F.Z ) {GOS(*(sp++) = (int*)&&CC4D;goto RMCC58;CC4D:a=a;);};                                   //      CALL    NZ,RMCC58
p(" CC50");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" CC52");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" CC54");a = E - 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     E
p(" CC55");                    ;if ( !F.Z ) {cl+=12;goto RMCC48;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCC48
p(" CC57");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMCC58:                             //RMCC58:
p(" CC58");                    ;HL = 0xB610             ;                                  ;/*cl+=10*/;                             //      LD      HL,B610h
p(" CC5B");                    ;A = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+00h)
p(" CC5E");a = A - MEM[HL]     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      (HL)
p(" CC5F");                    ;if ( !F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NZ
p(" CC60");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CC61");                    ;A = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      A,(IX+01h)
p(" CC64");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" CC65");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" CC66");a = A - MEM[HL]     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      (HL)
p(" CC67");                    ;if ( !F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     NZ
p(" CC68");                    ;IY = 0xB610             ;                                  ;/*cl+=14*/;                             //      LD      IY,B610h
p(" CC6C");                    ;MEM[IY+0x03] = 0xF9   ;                                  ;/*cl+=19*/;                             //      LD      (IY+03h),F9h
p(" CC70");a = MEM[IY+0x09] - 1;MEM[IY+0x09] = a      ;F.Z=((a&0xff)==0)  ;              ;/*cl+=23*/;                             //      DEC     (IY+09h)
p(" CC73");                    ;C = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      C,(IX+00h)
p(" CC76");                    ;B = MEM[IX+0x01]      ;                                  ;/*cl+=19*/;                             //      LD      B,(IX+01h)
p(" CC79");                    ;MEM[IX+0x01] = 0x00   ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),00h
p(" CC7D");                    ;HL = 0xFDFE             ;                                  ;/*cl+=10*/;                             //      LD      HL,FDFEh
p(" CC80");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" CC81");                    ;IO[BC] = H            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),H
p(" CC83");                    ;A = 0x2A              ;                                  ;/*cl+= 7*/;                             //      LD      A,2Ah
p(" CC85");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CC86");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CC88");                    ;IY = 0xBB00             ;                                  ;/*cl+=14*/;                             //      LD      IY,BB00h
p(" CC8C");                    ;*(SP++)=DE            ;                                  ;/*cl+=11*/;                             //      PUSH    DE
p(" CC8D");                    ;DE = 0x0004             ;                                  ;/*cl+=10*/;                             //      LD      DE,0004h
p(" CC90");                    ;H = 0xFF              ;                                  ;/*cl+= 7*/;                             //      LD      H,FFh
p(" CC92");                    ;GOS(*(sp++) = (int*)&&CC92;goto RMC926;CC92:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC926
p(" CC95");                    ;A = 0x26              ;                                  ;/*cl+= 7*/;                             //      LD      A,26h
p(" CC97");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CC98");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CC9A");                    ;GOS(*(sp++) = (int*)&&CC9A;goto RMC926;CC9A:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC926
p(" CC9D");                    ;DE=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     DE
p(" CC9E");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CC9F");                    ;IO[BC] = L            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),L
p(" CCA1");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" CCA2");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" CCA3");                    ;*(SP++)=BC            ;                                  ;/*cl+=11*/;                             //      PUSH    BC
p(" CCA4");                    ;*(SP++)=HL            ;                                  ;/*cl+=11*/;                             //      PUSH    HL
p(" CCA5");                    ;*(SP++)=IX            ;                                  ;/*cl+=15*/;                             //      PUSH    IX
p(" CCA7");                    ;IX = 0xB610             ;                                  ;/*cl+=14*/;                             //      LD      IX,B610h
p(" CCAB");                    ;GOS(*(sp++) = (int*)&&CCAB;goto RMC00D;CCAB:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC00D
p(" CCAE");                    ;IX=*(--SP)            ;                                  ;/*cl+=14*/;                             //      POP     IX
p(" CCB0");                    ;HL=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     HL
p(" CCB1");                    ;BC=*(--SP)            ;                                  ;/*cl+=10*/;                             //      POP     BC
p(" CCB2");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" CCB4");                    ;GOS(*(sp++) = (int*)&&CCB4;goto RMCBCD;CCB4:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCBCD
p(" CCB7");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p(" CCB8");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP


p("     ");RMCCB9:                             //RMCCB9:
p(" CCB9");                    ;BC = 0x3000             ;                                  ;/*cl+=10*/;                             //      LD      BC,3000h
p(" CCBC");                    ;IX = 0xB600             ;                                  ;/*cl+=14*/;                             //      LD      IX,B600h
p(" CCC0");a=B;B=_B_;_B_=a; a=C;C=_C_;_C_=a; a=D;D=_D;_D=a; a=E;E=_E;_E=a; a=H;H=_H;_H=a; a=L;L=_L_;_L_=a;/*cl+= 4*/;                             //      EXX
p(" CCC1");                    ;C = RMB600[0];B = RMB600[1]   ;                                  ;/*cl+=20*/;                             //      LD      BC,(RMB600)
p("     ");RMCCC5:                             //RMCCC5:
p(" CCC5");                    ;A = RMB611[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB611)
p(" CCC8");a = A - 0x46        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      46h
p(" CCCA");                    ;if ( !F.C ) {cl+=12;goto RMCCCE;}else{cl+= 7;}               ;                                   //      JR      NC,RMCCCE
p(" CCCC");                    ;A = 0x46              ;                                  ;/*cl+= 7*/;                             //      LD      A,46h
p("     ");RMCCCE:                             //RMCCCE:
p(" CCCE");a = A - 0xB9        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      B9h
p(" CCD0");                    ;if (  F.C ) {cl+=12;goto RMCCD4;}else{cl+= 7;}               ;                                   //      JR      C,RMCCD4
p(" CCD2");                    ;A = 0xB9              ;                                  ;/*cl+= 7*/;                             //      LD      A,B9h
p("     ");RMCCD4:                             //RMCCD4:
p(" CCD4");a = A - B           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      SUB     B
p(" CCD5");                    ;if (  F.C ) {cl+=12;goto RMCCFE;}else{cl+= 7;}               ;                                   //      JR      C,RMCCFE
p(" CCD7");a = A - 0x06        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      06h
p(" CCD9");                    ;if ( !F.C ) {cl+=12;goto RMCCDE;}else{cl+= 7;}               ;                                   //      JR      NC,RMCCDE
p(" CCDB");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" CCDC");                    ;goto RMCCC5               ;                                  ;/*cl+=12*/;                             //      JR      RMCCC5
p("     ");RMCCDE:                             //RMCCDE:
p(" CCDE");a = A - 0x13        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      13h
p(" CCE0");                    ;if (  F.C ) {cl+=12;goto RMCCE5;}else{cl+= 7;}               ;                                   //      JR      C,RMCCE5
p(" CCE2");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CCE3");                    ;goto RMCCC5               ;                                  ;/*cl+=12*/;                             //      JR      RMCCC5
p("     ");RMCCE5:                             //RMCCE5:
p(" CCE5");                    ;A = RMB610[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB610)
p(" CCE8");a = A - C           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      SUB     C
p(" CCE9");                    ;E = MEM[IX+0x12]      ;                                  ;/*cl+=19*/;                             //      LD      E,(IX+12h)
p(" CCEC");a = E & (1<<7)     ;                      ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 8*/;                             //      BIT     7,E
p(" CCEE");                    ;if (  F.Z ) {cl+=12;goto RMCCF7;}else{cl+= 7;}               ;                                   //      JR      Z,RMCCF7
p(" CCF0");a = A - 0x10        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      10h
p(" CCF2");                    ;if ( !F.C ) {cl+=12;goto RMCCFE;}else{cl+= 7;}               ;                                   //      JR      NC,RMCCFE
p(" CCF4");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" CCF5");                    ;goto RMCCE5               ;                                  ;/*cl+=12*/;                             //      JR      RMCCE5
p("     ");RMCCF7:                             //RMCCF7:
p(" CCF7");a = A - 0x22        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      22h
p(" CCF9");                    ;if (  F.C ) {cl+=12;goto RMCCFE;}else{cl+= 7;}               ;                                   //      JR      C,RMCCFE
p(" CCFB");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CCFC");                    ;goto RMCCE5               ;                                  ;/*cl+=12*/;                             //      JR      RMCCE5
p("     ");RMCCFE:                             //RMCCFE:
p(" CCFE");                    ;RMB600[0] = C;RMB600[1] = B   ;                                  ;/*cl+=20*/;                             //      LD      (RMB600),BC
p(" CD02");                    ;E = 0x19              ;                                  ;/*cl+= 7*/;                             //      LD      E,19h
p("     ");{                             ////c:{
p("     ");int x = 0;                             ////c:int x = 0;
p("     ");int y = 0;                             ////c:int y = 0;
p("     ");RMCD04:                             //RMCD04:
p(" CD04");                    ;D = 0x28              ;                                  ;/*cl+= 7*/;                             //      LD      D,28h
p(" CD06");                    ;C = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      C,(IX+00h)
p("     ");RMCD09:                             //RMCD09:
p(" CD09");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" CD0B");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CD0C");a=B;B=_B_;_B_=a; a=C;C=_C_;_C_=a; a=D;D=_D;_D=a; a=E;E=_E;_E=a; a=H;H=_H;_H=a; a=L;L=_L_;_L_=a;/*cl+= 4*/;                             //      EXX
p(" CD0D");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p("     ");g_text[y][x] =A;                             ////c:g_text[y][x] =A;
p("     ");x++;                             ////c:x++;
p("     ");if ( x >= 40 ){                             ////c:if ( x >= 40 ){
p("     ");	x = 0;                             ////c:	x = 0;
p("     ");	y++;                             ////c:	y++;
p("     ");}                             ////c:}
p(" CD0F");                    ;BC++                  ;                                  ;/*cl+= 6*/;                             //      INC     BC
p(" CD10");a=B;B=_B_;_B_=a; a=C;C=_C_;_C_=a; a=D;D=_D;_D=a; a=E;E=_E;_E=a; a=H;H=_H;_H=a; a=L;L=_L_;_L_=a;/*cl+= 4*/;                             //      EXX
p(" CD11");a = D - 1           ;D = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     D
p(" CD12");                    ;if ( !F.Z ) {cl+=12;goto RMCD09;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCD09
p(" CD14");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CD15");a = E - 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     E
p(" CD16");                    ;if ( !F.Z ) {cl+=12;goto RMCD04;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCD04
p("     ");}                             ////c:}
p(" CD18");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET


p("     ");
RMCD19:                             //RMCD19:
p(" CD19");                    ;IX = 0xB640             ;                                  ;/*cl+=14*/;                             //      LD      IX,B640h
p(" CD1D");                    ;HL = 0xD000             ;                                  ;/*cl+=10*/;                             //      LD      HL,D000h
p(" CD20");                    ;DE = 0x0010             ;                                  ;/*cl+=10*/;                             //      LD      DE,0010h
p(" CD23");                    ;B = 0x08              ;                                  ;/*cl+= 7*/;                             //      LD      B,08h
p("     ");RMCD25:                             //RMCD25:
p(" CD25");                    ;A = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      A,(HL)
p(" CD26");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CD27");                    ;C = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      C,(HL)
p(" CD28");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CD29");                    ;MEM[IX+0x00] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+00h),A
p(" CD2C");                    ;MEM[IX+0x01] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),C
p(" CD2F");                    ;MEM[IX+0x07] = 0xA1   ;                                  ;/*cl+=19*/;                             //      LD      (IX+07h),A1h
p(" CD33");                    ;MEM[IX+0x09] = 0x04   ;                                  ;/*cl+=19*/;                             //      LD      (IX+09h),04h
p(" CD37");                    ;MEM[IX+0x0A] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+0Ah),A
p(" CD3A");                    ;MEM[IX+0x0B] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+0Bh),A
p(" CD3D");a = IX + DE         ;IX = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IX,DE
p(" CD3F");                    ;if ( --B > 0 ) {cl+=13;goto RMCD25;}else{cl+=8;}             ;                                    //      DJNZ    RMCD25
p(" CD41");                    ;B = 0x34              ;                                  ;/*cl+= 7*/;                             //      LD      B,34h
p("     ");RMCD43:                             //RMCD43:
p(" CD43");                    ;A = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      A,(HL)
p(" CD44");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CD45");                    ;C = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      C,(HL)
p(" CD46");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CD47");                    ;MEM[IX+0x00] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+00h),A
p(" CD4A");                    ;MEM[IX+0x01] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),C
p(" CD4D");                    ;MEM[IX+0x07] = 0x81   ;                                  ;/*cl+=19*/;                             //      LD      (IX+07h),81h
p(" CD51");                    ;MEM[IX+0x09] = 0x02   ;                                  ;/*cl+=19*/;                             //      LD      (IX+09h),02h
p(" CD55");                    ;MEM[IX+0x0A] = A      ;                                  ;/*cl+=19*/;                             //      LD      (IX+0Ah),A
p(" CD58");a = IX + DE         ;IX = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IX,DE
p(" CD5A");                    ;if ( --B > 0 ) {cl+=13;goto RMCD43;}else{cl+=8;}             ;                                    //      DJNZ    RMCD43
p(" CD5C");                    ;IX = 0xBF00             ;                                  ;/*cl+=14*/;                             //      LD      IX,BF00h
p(" CD60");                    ;DE = 0x0004             ;                                  ;/*cl+=10*/;                             //      LD      DE,0004h
p(" CD63");                    ;A = 0x0E              ;                                  ;/*cl+= 7*/;                             //      LD      A,0Eh
p("     ");RMCD65:                             //RMCD65:
p(" CD65");                    ;C = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      C,(HL)
p(" CD66");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CD67");                    ;B = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      B,(HL)
p(" CD68");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CD69");                    ;MEM[IX+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IX+00h),C
p(" CD6C");                    ;MEM[IX+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),B
p(" CD6F");                    ;MEM[IX+0x03] = 0x02   ;                                  ;/*cl+=19*/;                             //      LD      (IX+03h),02h
p(" CD73");                    ;a=A;A=_A;_A=a;        ;a=F.C;F.C=fc;fc=a; a=F.Z;F.Z=fz;fz=a;;                                           ;/*cl+= 4*/;                             //      EX      AF,AF'
p(" CD74");                    ;A = 0xC1              ;                                  ;/*cl+= 7*/;                             //      LD      A,C1h
p(" CD76");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CD78");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CD79");                    ;A = 0xD1              ;                                  ;/*cl+= 7*/;                             //      LD      A,D1h
p(" CD7B");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CD7D");                    ;a=A;A=_A;_A=a;        ;a=F.C;F.C=fc;fc=a; a=F.Z;F.Z=fz;fz=a;;                                           ;/*cl+= 4*/;                             //      EX      AF,AF'
p(" CD7E");a = IX + DE         ;IX = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IX,DE
p(" CD80");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" CD81");                    ;if ( !F.Z ) {cl+=12;goto RMCD65;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCD65
p(" CD83");                    ;A = 0x0E              ;                                  ;/*cl+= 7*/;                             //      LD      A,0Eh
p("     ");RMCD85:                             //RMCD85:
p(" CD85");                    ;C = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      C,(HL)
p(" CD86");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CD87");                    ;B = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      B,(HL)
p(" CD88");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CD89");                    ;MEM[IX+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IX+00h),C
p(" CD8C");                    ;MEM[IX+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),B
p(" CD8F");                    ;MEM[IX+0x03] = 0x01   ;                                  ;/*cl+=19*/;                             //      LD      (IX+03h),01h
p(" CD93");                    ;a=A;A=_A;_A=a;        ;a=F.C;F.C=fc;fc=a; a=F.Z;F.Z=fz;fz=a;;                                           ;/*cl+= 4*/;                             //      EX      AF,AF'
p(" CD94");                    ;A = 0xC0              ;                                  ;/*cl+= 7*/;                             //      LD      A,C0h
p(" CD96");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CD98");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CD99");                    ;A = 0xD0              ;                                  ;/*cl+= 7*/;                             //      LD      A,D0h
p(" CD9B");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CD9D");                    ;a=A;A=_A;_A=a;        ;a=F.C;F.C=fc;fc=a; a=F.Z;F.Z=fz;fz=a;;                                           ;/*cl+= 4*/;                             //      EX      AF,AF'
p(" CD9E");a = IX + DE         ;IX = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IX,DE
p(" CDA0");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" CDA1");                    ;if ( !F.Z ) {cl+=12;goto RMCD85;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCD85
p(" CDA3");                    ;A = 0x04              ;                                  ;/*cl+= 7*/;                             //      LD      A,04h
p("     ");RMCDA5:                             //RMCDA5:
p(" CDA5");                    ;C = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      C,(HL)
p(" CDA6");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CDA7");                    ;B = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      B,(HL)
p(" CDA8");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CDA9");                    ;MEM[IX+0x00] = C      ;                                  ;/*cl+=19*/;                             //      LD      (IX+00h),C
p(" CDAC");                    ;MEM[IX+0x01] = B      ;                                  ;/*cl+=19*/;                             //      LD      (IX+01h),B
p(" CDAF");                    ;MEM[IX+0x03] = 0x02   ;                                  ;/*cl+=19*/;                             //      LD      (IX+03h),02h
p(" CDB3");                    ;a=A;A=_A;_A=a;        ;a=F.C;F.C=fc;fc=a; a=F.Z;F.Z=fz;fz=a;;                                           ;/*cl+= 4*/;                             //      EX      AF,AF'
p(" CDB4");                    ;A = 0xC3              ;                                  ;/*cl+= 7*/;                             //      LD      A,C3h
p(" CDB6");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CDB8");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CDB9");                    ;A = 0xD3              ;                                  ;/*cl+= 7*/;                             //      LD      A,D3h
p(" CDBB");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CDBD");                    ;a=A;A=_A;_A=a;        ;a=F.C;F.C=fc;fc=a; a=F.Z;F.Z=fz;fz=a;;                                           ;/*cl+= 4*/;                             //      EX      AF,AF'
p(" CDBE");a = IX + DE         ;IX = a                ;                   ;F.C=a>>16     ;/*cl+=15*/;                             //      ADD     IX,DE
p(" CDC0");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" CDC1");                    ;if ( !F.Z ) {cl+=12;goto RMCDA5;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCDA5
p(" CDC3");                    ;A = 0x04              ;                                  ;/*cl+= 7*/;                             //      LD      A,04h
p(" CDC5");                    ;DE = 0xCDDD             ;                                  ;/*cl+=10*/;                             //      LD      DE,CDDDh
p("     ");RMCDC8:                             //RMCDC8:
p(" CDC8");                    ;C = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      C,(HL)
p(" CDC9");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CDCA");                    ;B = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      B,(HL)
p(" CDCB");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CDCC");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p(" CDCE");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CDCF");                    ;IO[BC] = E            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),E
p(" CDD1");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" CDD2");                    ;if ( !F.Z ) {cl+=12;goto RMCDC8;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCDC8
p(" CDD4");                    ;C = 0x70              ;                                  ;/*cl+= 7*/;                             //      LD      C,70h
p(" CDD6");                    ;B = 0x40              ;                                  ;/*cl+= 7*/;                             //      LD      B,40h
p(" CDD8");                    ;D = 0xDF              ;                                  ;/*cl+= 7*/;                             //      LD      D,DFh
p(" CDDA");                    ;E = 0xF0              ;                                  ;/*cl+= 7*/;                             //      LD      E,F0h
p("     ");RMCDDC:                             //RMCDDC:
p(" CDDC");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" CDDE");a = A - E           ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 4*/;                             //      CP      E
p(" CDDF");                    ;if ( !F.C ) {cl+=12;goto RMCDE3;}else{cl+= 7;}               ;                                   //      JR      NC,RMCDE3
p(" CDE1");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p("     ");RMCDE3:                             //RMCDE3:
p(" CDE3");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CDE4");                    ;A = B                 ;                                  ;/*cl+= 4*/;                             //      LD      A,B
p(" CDE5");a = A - 0xC0        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      C0h
p(" CDE7");                    ;if (  F.C ) {cl+=12;goto RMCDDC;}else{cl+= 7;}               ;                                   //      JR      C,RMCDDC
p(" CDE9");                    ;DE = 0xF9FA             ;                                  ;/*cl+=10*/;                             //      LD      DE,F9FAh
p(" CDEC");                    ;A = 0x10              ;                                  ;/*cl+= 7*/;                             //      LD      A,10h
p("     ");RMCDEE:                             //RMCDEE:
p(" CDEE");                    ;C = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      C,(HL)
p(" CDEF");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CDF0");                    ;B = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      B,(HL)
p(" CDF1");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CDF2");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p(" CDF4");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CDF5");                    ;IO[BC] = E            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),E
p(" CDF7");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" CDF8");                    ;if ( !F.Z ) {cl+=12;goto RMCDEE;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCDEE
p(" CDFA");                    ;HL = 0xD0C0             ;                                  ;/*cl+=10*/;                             //      LD      HL,D0C0h
p(" CDFD");                    ;DE = 0xBF80             ;                                  ;/*cl+=10*/;                             //      LD      DE,BF80h
p(" CE00");                    ;BC = 0x0020             ;                                  ;/*cl+=10*/;                             //      LD      BC,0020h
p(" CE03");do{MEM[DE++] = MEM[HL++]; BC--;cl+=(BC!=0)?21:16; }while( BC != 0 );          ;                                    //      LDIR
p(" CE05");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p("     ");RMCE06:                             //RMCE06:
p(" CE06");                    ;BC = 0x2000             ;                                  ;/*cl+=10*/;                             //      LD      BC,2000h
p(" CE09");                    ;A = 0x27              ;                                  ;/*cl+= 7*/;                             //      LD      A,27h
p(" CE0B");                    ;D = 0x04              ;                                  ;/*cl+= 7*/;                             //      LD      D,04h
p(" CE0D");                    ;E = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      E,00h
p("     ");RMCE0F:                             //RMCE0F:
p(" CE0F");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CE11");                    ;BC++                  ;                                  ;/*cl+= 6*/;                             //      INC     BC
p(" CE12");a = E - 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     E
p(" CE13");                    ;if ( !F.Z ) {cl+=12;goto RMCE0F;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCE0F
p(" CE15");a = D - 1           ;D = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     D
p(" CE16");                    ;if ( !F.Z ) {cl+=12;goto RMCE0F;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCE0F
p(" CE18");                    ;HL = 0xB600             ;                                  ;/*cl+=10*/;                             //      LD      HL,B600h
p(" CE1B");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" CE1D");                    ;D = 0x0A              ;                                  ;/*cl+= 7*/;                             //      LD      D,0Ah
p(" CE1F");                    ;E = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      E,00h
p("     ");RMCE21:                             //RMCE21:
p(" CE21");                    ;MEM[HL] = A           ;                                  ;/*cl+= 7*/;                             //      LD      (HL),A
p(" CE22");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CE23");a = E - 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     E
p(" CE24");                    ;if ( !F.Z ) {cl+=12;goto RMCE21;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCE21
p(" CE26");a = D - 1           ;D = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     D
p(" CE27");                    ;if ( !F.Z ) {cl+=12;goto RMCE21;}else{cl+= 7;}               ;                                   //      JR      NZ,RMCE21
p(" CE29");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET


p("     ");RMCE2A:                             //RMCE2A:
p(" CE2A");                    ;A = 0xFF              ;                                  ;/*cl+= 7*/;                             //      LD      A,FFh
p(" CE2C");                    ;IX = 0xD101             ;                                  ;/*cl+=14*/;                             //      LD      IX,D101h
p(" CE30");                    ;BC = 0x4000             ;                                  ;/*cl+=10*/;                             //      LD      BC,4000h
p(" CE33");                    ;L = RMD100[0];H = RMD100[1]   ;                                  ;/*cl+=16*/;                             //      LD      HL,(RMD100)
p("     ");RMCE36:                             //RMCE36:
p(" CE36");                    ;IX++                  ;                                  ;/*cl+=10*/;                             //      INC     IX
p(" CE38");                    ;E = MEM[IX+0x00]      ;                                  ;/*cl+=19*/;                             //      LD      E,(IX+00h)
p("     ");RMCE3B:                             //RMCE3B:
p(" CE3B");a = E - 1           ;E = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     E
p(" CE3C");                    ;if (  F.Z ) {cl+=12;goto RMCE43;}else{cl+= 7;}               ;                                   //      JR      Z,RMCE43
p(" CE3E");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CE40");                    ;BC++                  ;                                  ;/*cl+= 6*/;                             //      INC     BC
p(" CE41");                    ;goto RMCE3B               ;                                  ;/*cl+=12*/;                             //      JR      RMCE3B

p("     ");RMCE43:                             //RMCE43:
p(" CE43");                    ;HL--                  ;                                  ;/*cl+= 6*/;                             //      DEC     HL
p(" CE44");                    ;a=A;A=_A;_A=a;        ;a=F.C;F.C=fc;fc=a; a=F.Z;F.Z=fz;fz=a;;                                           ;/*cl+= 4*/;                             //      EX      AF,AF'
p(" CE45");                    ;A = H                 ;                                  ;/*cl+= 4*/;                             //      LD      A,H
p(" CE46");a = A | L           ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;/*cl+= 4*/;                             //      OR      L
p(" CE47");                    ;if (  F.Z ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     Z

p(" CE48");                    ;a=A;A=_A;_A=a;        ;a=F.C;F.C=fc;fc=a; a=F.Z;F.Z=fz;fz=a;;                                           ;/*cl+= 4*/;                             //      EX      AF,AF'
p(" CE49");                    ;A = ~A                ;                                  ;/*cl+= 4*/;                             //      CPL
p(" CE4A");                    ;goto RMCE36               ;                                  ;/*cl+=12*/;                             //      JR      RMCE36

p("     ");RMCE4C:                             //RMCE4C:
p(" CE4C");                    ;BC = 0x4100             ;                                  ;/*cl+=10*/;                             //      LD      BC,4100h
p("     ");RMCE4F:                             //RMCE4F:
p(" CE4F");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" CE51");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" CE53");cl+=17              ;if ( !F.Z ) {GOS(*(sp++) = (int*)&&CE53;goto RMCE5D;CE53:a=a;);};                                   //      CALL    NZ,RMCE5D
p(" CE56");                    ;BC++                  ;                                  ;/*cl+= 6*/;                             //      INC     BC
p(" CE57");                    ;A = B                 ;                                  ;/*cl+= 4*/;                             //      LD      A,B
p(" CE58");a = A - 0xBF        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      BFh
p(" CE5A");                    ;if (  F.C ) {cl+=12;goto RMCE4F;}else{cl+= 7;}               ;                                   //      JR      C,RMCE4F
p(" CE5C");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET


p("     ");RMCE5D:                             //RMCE5D:
p(" CE5D");                    ;E = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      E,00h
p(" CE5F");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" CE60");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" CE62");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" CE64");                    ;if (  F.Z ) {cl+=12;goto RMCE68;}else{cl+= 7;}               ;                                   //      JR      Z,RMCE68
p(" CE66");                    ;E |= (1<<0)          ;                                  ;/*cl+= 8*/;                             //      SET     0,E
p("     ");RMCE68:                             //RMCE68:
p(" CE68");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CE69");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CE6A");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" CE6C");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" CE6E");                    ;if (  F.Z ) {cl+=12;goto RMCE72;}else{cl+= 7;}               ;                                   //      JR      Z,RMCE72
p(" CE70");                    ;E |= (1<<1)          ;                                  ;/*cl+= 8*/;                             //      SET     1,E
p("     ");RMCE72:                             //RMCE72:
p(" CE72");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" CE73");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" CE74");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" CE76");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" CE78");                    ;if (  F.Z ) {cl+=12;goto RMCE7C;}else{cl+= 7;}               ;                                   //      JR      Z,RMCE7C
p(" CE7A");                    ;E |= (1<<2)          ;                                  ;/*cl+= 8*/;                             //      SET     2,E
p("     ");RMCE7C:                             //RMCE7C:
p(" CE7C");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CE7D");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CE7E");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" CE80");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" CE82");                    ;if (  F.Z ) {cl+=12;goto RMCE86;}else{cl+= 7;}               ;                                   //      JR      Z,RMCE86
p(" CE84");                    ;E |= (1<<3)          ;                                  ;/*cl+= 8*/;                             //      SET     3,E
p("     ");RMCE86:                             //RMCE86:
p(" CE86");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" CE87");                    ;D = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      D,00h
p(" CE89");                    ;HL = 0xCE91             ;                                  ;/*cl+=10*/;                             //      LD      HL,CE91h
p(" CE8C");a = HL + DE         ;HL = a                ;                   ;F.C=a>>16     ;/*cl+=13*/;                             //      ADD     HL,DE
p(" CE8D");                    ;A = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      A,(HL)
p(" CE8E");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CE90");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET

p("     ");RMCEA1_Initialize:                             //RMCEA1_Initialize:
p(" CEA1");                    ;GOS(*(sp++) = (int*)&&CEA1;goto RMCE06;CEA1:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCE06
p(" CEA4");                    ;GOS(*(sp++) = (int*)&&CEA4;goto RMCE2A;CEA4:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCE2A
p(" CEA7");                    ;GOS(*(sp++) = (int*)&&CEA7;goto RMCE4C;CEA7:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCE4C
p(" CEAA");                    ;GOS(*(sp++) = (int*)&&CEAA;goto RMCD19;CEAA:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCD19
p(" CEAD");                    ;HL = 0xD0E0             ;                                  ;/*cl+=10*/;                             //      LD      HL,D0E0h
p(" CEB0");                    ;DE = 0xB600             ;                                  ;/*cl+=10*/;                             //      LD      DE,B600h
p(" CEB3");                    ;BC = 0x0020             ;                                  ;/*cl+=10*/;                             //      LD      BC,0020h
p(" CEB6");do{MEM[DE++] = MEM[HL++]; BC--;cl+=(BC!=0)?21:16; }while( BC != 0 );          ;                                    //      LDIR
p(" CEB8");                    ;GOS(*(sp++) = (int*)&&CEB8;goto RMC2CB;CEB8:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC2CB
p(" CEBB");                    ;GOS(*(sp++) = (int*)&&CEBB;goto RMC55D;CEBB:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC55D
p(" CEBE");                    ;GOS(*(sp++) = (int*)&&CEBE;goto RMCCB9;CEBE:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCCB9
p(" CEC1");                    ;BC = 0xA906             ;                                  ;/*cl+=10*/;                             //      LD      BC,A906h
p(" CEC4");                    ;A = 0xCE              ;                                  ;/*cl+= 7*/;                             //      LD      A,CEh
p(" CEC6");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CEC8");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CEC9");a = A + 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     A
p(" CECA");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CECC");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CECD");                    ;A = 0xDE              ;                                  ;/*cl+= 7*/;                             //      LD      A,DEh
p(" CECF");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CED1");                    ;BC = 0x1C00             ;                                  ;/*cl+=10*/;                             //      LD      BC,1C00h
p(" CED4");                    ;HL = 0xCEE9             ;                                  ;/*cl+=10*/;                             //      LD      HL,CEE9h
p(" CED7");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p("     ");RMCED9:                             //RMCED9:
p(" CED9");                    ;D = MEM[HL]           ;                                  ;/*cl+= 7*/;                             //      LD      D,(HL)
p(" CEDA");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CEDC");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" CEDD");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p("     ");	sys.sound.psg_Set( A, D );                             ////c:	sys.sound.psg_Set( A, D );
p(" CEDF");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CEE0");a = A - 0x0D        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      0Dh
p(" CEE2");                    ;if (  F.Z ) {cl+=12;goto RMCEE8;}else{cl+= 7;}               ;                                   //      JR      Z,RMCEE8
p(" CEE4");a = A + 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     A
p(" CEE5");                    ;HL++                  ;                                  ;/*cl+= 6*/;                             //      INC     HL
p(" CEE6");                    ;goto RMCED9               ;                                  ;/*cl+=12*/;                             //      JR      RMCED9
p("     ");RMCEE8:                             //RMCEE8:
//MEM[0xB619] = 100;
//MEM[0xB604] = 100;
p(" CEE8");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET
p(" CEE9");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" CEEA");                    ;BC++                  ;                                  ;/*cl+= 6*/;                             //      INC     BC
p(" CEEB");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" CEEC");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" CEED");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" CEEE");                    ;B = 0x1F              ;                                  ;/*cl+= 7*/;                             //      LD      B,1Fh
p(" CEF0");                    ;L = RM001F[0];H = RM001F[1]   ;                                  ;/*cl+=16*/;                             //      LD      HL,(RM001F)
p(" CEF3");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" CEF4");                    ;L = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      L,00h
p(" CEF6");                    ;a=A;A=_A;_A=a;        ;a=F.C;F.C=fc;fc=a; a=F.Z;F.Z=fz;fz=a;;                                           ;/*cl+= 4*/;                             //      EX      AF,AF'
p(" CEF7");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" CEF8");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" CEF9");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" CEFA");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" CEFB");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" CEFC");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" CEFD");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" CEFE");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p(" CEFF");                    ;_a=a                   ;                                  ;/*cl+= 4*/;                             //      NOP
p("     ");RMCF00:                             //RMCF00:
p("     ");	while(1){                             ////c:	while(1){
p("     ");		{                             ////c:		{
//	if ( sys.key.repeat('T') ) sys.sound.Beep();
p("     ");			sys.joy0.UpdateJoystick();                             ////c:			sys.joy0.UpdateJoystick();
p("     ");			sys.key.UpdateKey();                             ////c:			sys.key.UpdateKey();
p("     ");			if ( sys.key.hi(VK_ESCAPE) ) SendMessage( sys.pWin1->m_hWnd , WM_CLOSE , 0 , 0);                             ////c:			if ( sys.key.hi(VK_ESCAPE) ) SendMessage( sys.pWin1->m_hWnd , WM_CLOSE , 0 , 0);
p("     ");		}                             ////c:		}
p("     ");			if ( sys.key.hi('G') ) g_flgMap = !g_flgMap;                             ////c:			if ( sys.key.hi('G') ) g_flgMap = !g_flgMap;
p(" CF00");                    ;GOS(*(sp++) = (int*)&&CF00;goto RMC2CB;CF00:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC2CB
p(" CF03");                    ;GOS(*(sp++) = (int*)&&CF03;goto RMC6E8;CF03:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC6E8
p(" CF06");                    ;GOS(*(sp++) = (int*)&&CF06;goto RMCC42;CF06:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCC42
p(" CF09");                    ;GOS(*(sp++) = (int*)&&CF09;goto RMCCB9;CF09:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCCB9
p("     ");		{                             ////c:		{
			sys.Clear();
//p("     ");			glClearColor(0,0.0,0,0);                             ////c:			glClearColor(0,0.0,0,0);
//p("     ");			glClear( GL_COLOR_BUFFER_BIT );                             ////c:			glClear( GL_COLOR_BUFFER_BIT );
p("     ");			DrawScreen();
			sys.Draw();
			if (sys.pWin1->FlgActive == false )  break;

//p("     ");			sys.pGram->UpdateTexture();                             ////c:			sys.pGram->UpdateTexture();
//p("     ");			sys.m_pFilter->DrawFilter( sys.pGram->m_pTexture );                             ////c:			sys.m_pFilter->DrawFilter( sys.pGram->m_pTexture );
//p("     ");			if ( sys.pWin1->SwapBuffer()  == false ) break;                             ////c:			if ( sys.pWin1->SwapBuffer()  == false ) break;
p("     ");		}                             ////c:		}
p(" CF0C");                    ;GOS(*(sp++) = (int*)&&CF0C;goto RMC6B8;CF0C:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC6B8
p(" CF0F");                    ;GOS(*(sp++) = (int*)&&CF0F;goto RMC76B;CF0F:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC76B
p(" CF12");                    ;GOS(*(sp++) = (int*)&&CF12;goto RMC55D;CF12:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC55D
p(" CF15");                    ;GOS(*(sp++) = (int*)&&CF15;goto RMCA90;CF15:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCA90
p(" CF18");                    ;GOS(*(sp++) = (int*)&&CF18;goto RMCB72;CF18:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCB72
p(" CF1B");                    ;GOS(*(sp++) = (int*)&&CF1B;goto RMCF38;CF1B:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCF38
p(" CF1E");                    ;GOS(*(sp++) = (int*)&&CF1E;goto RMCCB9;CF1E:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCCB9
p("     ");		{                             ////c:		{
			sys.Clear();
//p("     ");			glClearColor(0,0.0,0,0);                             ////c:			glClearColor(0,0.0,0,0);
//p("     ");			glClear( GL_COLOR_BUFFER_BIT );                             ////c:			glClear( GL_COLOR_BUFFER_BIT );
p("     ");			DrawScreen();
			sys.Draw();
			if (sys.pWin1->FlgActive == false )  break;
//p("     ");			sys.pGram->UpdateTexture();                             ////c:			sys.pGram->UpdateTexture();
//p("     ");			sys.m_pFilter->DrawFilter( sys.pGram->m_pTexture );                             ////c:			sys.m_pFilter->DrawFilter( sys.pGram->m_pTexture );
//p("     ");			if ( sys.pWin1->SwapBuffer()  == false ) break;                             ////c:			if ( sys.pWin1->SwapBuffer()  == false ) break;
p("     ");		}                             ////c:		}

p(" CF21");                    ;GOS(*(sp++) = (int*)&&CF21;goto RMCBE8;CF21:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCBE8
p(" CF24");                    ;GOS(*(sp++) = (int*)&&CF24;goto RMC57A;CF24:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC57A
p(" CF27");                    ;GOS(*(sp++) = (int*)&&CF27;goto RMC541;CF27:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC541
p(" CF2A");                    ;GOS(*(sp++) = (int*)&&CF2A;goto RMC6B8;CF2A:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC6B8
p(" CF2D");                    ;GOS(*(sp++) = (int*)&&CF2D;goto RMC76B;CF2D:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC76B
p(" CF30");                    ;GOS(*(sp++) = (int*)&&CF30;goto RMC60A;CF30:a=a;)               ;/*cl+=17*/;                             //      CALL    RMC60A
p(" CF33");                    ;GOS(*(sp++) = (int*)&&CF33;goto RMCF38;CF33:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCF38
p(" CF36");//      JR      RMCF00                             ////      JR      RMCF00
p("     ");}                             ////c:}

p("     ");RMCF38:                             //RMCF38:
p(" CF38");                    ;DE = 0x0000             ;                                  ;/*cl+=10*/;                             //      LD      DE,0000h
p(" CF3B");                    ;HL = 0x0000             ;                                  ;/*cl+=10*/;                             //      LD      HL,0000h
p(" CF3E");                    ;BC = 0x1000             ;                                  ;/*cl+=10*/;                             //      LD      BC,1000h
p(" CF41");do{MEM[DE++] = MEM[HL++]; BC--;cl+=(BC!=0)?21:16; }while( BC != 0 );          ;                                    //      LDIR

if ( sys.key.hi('B') ) MEM[0xB610+ 9] = 0;//chk
//if ( sys.key.hi('N') ) MEM[0xB600+ 4] = 0;//chk
if ( sys.key.hi('M') )  IO[0xA906   ] = 0;//chk

if ( sys.joy0.now.Se && sys.joy0.hi.St ) MEM[0xB610+ 9] = 0;//chk;


//	敵基地破壊判定
p(" CF43");                    ;BC = 0xA906             ;                                  ;/*cl+=10*/;                             //      LD      BC,A906h
p(" CF46");a = IO[BC]          ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+=12*/;                             //      !IN      A,(C)
p(" CF48");a = A - 0x00        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      00h
p(" CF4A");                    ;if (  F.Z ) {cl+=12;;goto RMCF9B;}else{cl+= 7;}               ;                                   //      JR      Z,RMCF9B

//	アタッカー死亡判定
p(" CF4C");                    ;A = RMB619[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB619)
p(" CF4F");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" CF50");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" CF52");                    ;if ( !F.C ) {cl+=12;goto RMCF84;}else{cl+= 7;}               ;                                   //      JR      NC,RMCF84

//	キャリアー死亡判定
p(" CF54");                    ;A = RMB604[0]             ;                                  ;/*cl+=13*/;                             //      LD      A,(RMB604)
p(" CF57");a = A - 1           ;A = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     A
p(" CF58");a = A - 0x80        ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;/*cl+= 7*/;                             //      CP      80h
p(" CF5A");                    ;if (  F.C ) {cl+=11;RET(goto **(--sp););}else{cl+=5;}          ;                                    //      RET     C

p(" CF5B");                    ;C = RMB602[0];B = RMB602[1]   ;                                  ;/*cl+=20*/;                             //      LD      BC,(RMB602)
p(" CF5F");                    ;A = 0x2A              ;                                  ;/*cl+= 7*/;                             //      LD      A,2Ah
p(" CF61");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CF63");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CF64");                    ;A = 0x2B              ;                                  ;/*cl+= 7*/;                             //      LD      A,2Bh
p(" CF66");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CF68");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CF69");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CF6B");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CF6C");                    ;A = 0x26              ;                                  ;/*cl+= 7*/;                             //      LD      A,26h
p(" CF6E");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CF70");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CF71");                    ;A = 0x24              ;                                  ;/*cl+= 7*/;                             //      LD      A,24h
p(" CF73");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CF75");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" CF76");                    ;A = 0x2E              ;                                  ;/*cl+= 7*/;                             //      LD      A,2Eh
p(" CF78");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CF7A");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" CF7B");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CF7D");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" CF7E");                    ;A = 0x28              ;                                  ;/*cl+= 7*/;                             //      LD      A,28h
p(" CF80");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CF82");                    ;goto RMCF9B               ;                                  ;/*cl+=12*/;                             //      JR      RMCF9B
p("     ");RMCF84:                             //RMCF84:
p(" CF84");                    ;C = RMB610[0];B = RMB610[1]   ;                                  ;/*cl+=20*/;                             //      LD      BC,(RMB610)
p(" CF88");                    ;A = 0x2A              ;                                  ;/*cl+= 7*/;                             //      LD      A,2Ah
p(" CF8A");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CF8C");a = C + 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     C
p(" CF8D");                    ;A = 0x26              ;                                  ;/*cl+= 7*/;                             //      LD      A,26h
p(" CF8F");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CF91");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CF92");                    ;A = 0x24              ;                                  ;/*cl+= 7*/;                             //      LD      A,24h
p(" CF94");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p(" CF96");a = C - 1           ;C = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     C
p(" CF97");                    ;A = 0x28              ;                                  ;/*cl+= 7*/;                             //      LD      A,28h
p(" CF99");                    ;IO[BC] = A            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),A
p("     ");RMCF9B:                             //RMCF9B:
p(" CF9B");                    ;BC = 0x1C00             ;                                  ;/*cl+=10*/;                             //      LD      BC,1C00h
p(" CF9E");                    ;DE = 0x072F             ;                                  ;/*cl+=10*/;                             //      LD      DE,072Fh
p(" CFA1");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p(" CFA3");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" CFA4");                    ;IO[BC] = E            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),E
p("     ");	sys.sound.psg_Set( D, E );                             ////c:	sys.sound.psg_Set( D, E );
p(" CFA6");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CFA7");                    ;DE = 0x0931             ;                                  ;/*cl+=10*/;                             //      LD      DE,0931h
p(" CFAA");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p(" CFAC");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" CFAD");                    ;IO[BC] = E            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),E
p("     ");	sys.sound.psg_Set( D, E );                             ////c:	sys.sound.psg_Set( D, E );
p(" CFAF");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CFB0");                    ;DE = 0x0C80             ;                                  ;/*cl+=10*/;                             //      LD      DE,0C80h
p(" CFB3");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p(" CFB5");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" CFB6");                    ;IO[BC] = E            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),E
p("     ");	sys.sound.psg_Set( D, E );                             ////c:	sys.sound.psg_Set( D, E );
p(" CFB8");a = B + 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      INC     B
p(" CFB9");                    ;DE = 0x0D03             ;                                  ;/*cl+=10*/;                             //      LD      DE,0D03h
p(" CFBC");                    ;IO[BC] = D            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),D
p(" CFBE");a = B - 1           ;B = a                 ;F.Z=((a&0xff)==0)  ;              ;/*cl+= 4*/;                             //      DEC     B
p(" CFBF");                    ;IO[BC] = E            ;                                  ;/*cl+=12*/;                             //      !OUT     (C),E
p("     ");	sys.sound.psg_Set( D, E );                             ////c:	sys.sound.psg_Set( D, E );
p(" CFC1");                    ;A = 0x00              ;                                  ;/*cl+= 7*/;                             //      LD      A,00h
p(" CFC3");                    ;GOS(*(sp++) = (int*)&&CFC3;goto RMCBCD;CFC3:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCBCD
p(" CFC6");                    ;GOS(*(sp++) = (int*)&&CFC6;goto RMCCB9;CFC6:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCCB9
p("     ");		{                             ////c:		{
			sys.Clear();
//p("     ");			glClearColor(0,0.0,0,0);                             ////c:			glClearColor(0,0.0,0,0);
//p("     ");			glClear( GL_COLOR_BUFFER_BIT );                             ////c:			glClear( GL_COLOR_BUFFER_BIT );
p("     ");			DrawScreen();
			sys.Draw();
//p("     ");			sys.pGram->UpdateTexture();                             ////c:			sys.pGram->UpdateTexture();
//p("     ");			sys.m_pFilter->DrawFilter( sys.pGram->m_pTexture );                             ////c:			sys.m_pFilter->DrawFilter( sys.pGram->m_pTexture );
//p("     ");			sys.pWin1->SwapBuffer();                             ////c:			sys.pWin1->SwapBuffer();
p("     ");		}                             ////c:		}
p(" CFC9");                    ;GOS(*(sp++) = (int*)&&CFC9;goto RMCA90;CFC9:a=a;)               ;/*cl+=17*/;                             //      CALL    RMCA90
p(" CFCC");//      POP     DE                             ////      POP     DE
p("     ");sp--;cnt_sp--;                             ////c:sp--;cnt_sp--;
p(" CFCD");                    ;RET(goto **(--sp);)         ;                                  ;/*cl+=10*/;                             //      RET




}

}
