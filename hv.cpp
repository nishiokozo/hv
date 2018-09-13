#include <sys.h>
#include "ed.h"

Sys	sys( "env.ini" );

unsigned char g_CEE9_sound[] =
{
	0xC9,0x00,0x03,0x00,0x00,0x00,0x06,0x1F,0x2A,0x1F,0x00,0x00,0x2E,0x00,
};
unsigned char g_D000_location_weapoins[] =
{
	0x10,0xB0,0x20,0xB0,0x00,0x00,0x40,0xB0,0x00,0x00,0x60,0xB0,0x00,0x00,0x80,0xB0,
	0x66,0x54,0x8C,0x54,0x00,0x00,0x20,0x53,0x66,0x5E,0x8C,0x5E,0x30,0x5E,0x00,0x00,
	0xC8,0x78,0x00,0x00,0xB8,0xA0,0xB8,0x90,0x00,0x00,0x80,0xB8,0x80,0xA8,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x30,0xA8,0x00,0x00,0x50,0xA8,0x00,0x00,0x70,0xA8,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xB4,0x5A,0xA5,0x74,0x4E,0x73,0x3A,0x78,
	0x1F,0x78,0x16,0x66,0x0E,0xB8,0x17,0xB8,0x20,0xBA,0x5D,0xB8,0xD9,0x98,0xEC,0x97,
	0xF2,0x81,0x3C,0xBC,0x34,0x8A,0x64,0x8E,0xAF,0x62,0xB2,0x61,0xB5,0x60,0xAA,0x45,
	0x9E,0x5B,0x4D,0x54,0x3C,0x45,0xF8,0x66,0x10,0x9E,0x1E,0x49,0x2F,0x8C,0x20,0x99,
	0x6B,0xA6,0x44,0xAB,0x44,0x74,0x74,0xAC,0x86,0x76,0x6C,0x59,0x21,0x69,0x30,0xB7,
	0x37,0xB6,0x90,0xBB,0xCD,0x9D,0x11,0x7A,0x52,0xBA,0x8A,0xB9,0xC1,0x8B,0x27,0x7C,
	0x81,0xBD,0xAF,0xB9,0xE3,0x99,0x31,0x79,0x9D,0xBD,0x8C,0xAB,0xDA,0x88,0x35,0x79,
};
/*
unsigned char g_D0E0_initial_for_carrier[] =
{
	0xC0,0x45,0xF8,0x45,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
}
unsigned char g_D0F0_initial_for_fighter[] =
{
	0xF8,0x45,0x00,0x00,0x80,0x20,0x00,0x41,0x0A,0x07,0x00,0x00,0x00,0x00,0x00,0x00,
};
*/

unsigned char	g_D102_mapdata[] = 
{
	0x00,0x01,0x00,0x01,0x00,0x01,0xA0,0x06,0x55,0x08,0xA0,0x08,0x49,0x14,0x34,0x0F,
	0x5D,0x13,0x3A,0x19,0x2B,0x19,0x5B,0x15,0x38,0x1A,0x2A,0x1B,0x59,0x17,0x37,0x1A,
	0x29,0x22,0x4D,0x1E,0x36,0x19,0x23,0x2A,0x4B,0x20,0x0A,0x06,0x23,0x15,0x2A,0x2C,
	0x49,0x30,0x1A,0x1C,0x28,0x2F,0x2B,0x07,0x17,0x36,0x0C,0x23,0x2A,0x30,0x29,0x0A,
	0x10,0x68,0x2B,0x30,0x28,0x10,0x0A,0x69,0x2A,0x31,0x27,0x12,0x08,0x6A,0x29,0x33,
	0x22,0x17,0x06,0x6C,0x27,0x35,0x20,0x88,0x26,0x36,0x20,0x89,0x24,0x37,0x1C,0x8E,
	0x22,0x3A,0x19,0x8F,0x20,0x40,0x14,0x90,0x1F,0x27,0x03,0x1A,0x10,0x92,0x1E,0x29,
	0x03,0x1B,0x0E,0x8A,0x26,0x2A,0x03,0x1C,0x0C,0x1A,0x08,0x67,0x29,0x2A,0x04,0x1D,
	0x0A,0x1B,0x09,0x60,0x2C,0x29,0x08,0x05,0x03,0x18,0x07,0x1C,0x0A,0x1B,0x0E,0x38,
	0x2C,0x2A,0x09,0x03,0x05,0x2B,0x17,0x1B,0x0E,0x37,0x2C,0x2C,0x10,0x29,0x16,0x1C,
	0x06,0x13,0x08,0x25,0x2C,0x2E,0x0F,0x31,0x0B,0x1F,0x05,0x0F,0x0E,0x23,0x2D,0x32,
	0x08,0x36,0x08,0x20,0x04,0x10,0x0F,0x21,0x2E,0x93,0x05,0x10,0x0F,0x15,0x3A,0x53,
	0x08,0x38,0x07,0x10,0x0E,0x15,0x3B,0x52,0x0A,0x37,0x07,0x0F,0x0C,0x17,0x3C,0x51,
	0x0F,0x3F,0x04,0x05,0x0A,0x19,0x3D,0x51,0x12,0x3C,0x05,0x03,0x08,0x1B,0x3E,0x50,
	0x14,0x3B,0x0D,0x1B,0x3F,0x4F,0x17,0x3A,0x0C,0x1A,0x40,0x4E,0x19,0x3A,0x0B,0x19,
	0x17,0x05,0x26,0x4E,0x1F,0x36,0x05,0x1C,0x18,0x0B,0x14,0x07,0x03,0x16,0x07,0x38,
	0x21,0x34,0x03,0x1D,0x18,0x0D,0x05,0x05,0x0A,0x1F,0x0C,0x34,0x21,0x4F,0x13,0x44,
	0x0C,0x34,0x21,0x4C,0x12,0x4F,0x09,0x2F,0x25,0x45,0x12,0x53,0x08,0x30,0x25,0x43,
	0x12,0x8B,0x25,0x41,0x13,0x35,0x02,0x57,0x25,0x3F,0x14,0x32,0x06,0x56,0x28,0x39,
	0x17,0x2B,0x0E,0x54,0x2A,0x37,0x18,0x27,0x13,0x52,0x2C,0x2D,0x21,0x27,0x14,0x50,
	0x2E,0x2B,0x22,0x27,0x15,0x4E,0x30,0x29,0x22,0x28,0x16,0x4C,0x32,0x27,0x22,0x2A,
	0x17,0x45,0x38,0x24,0x1C,0x05,0x04,0x2C,0x17,0x43,0x3A,0x1B,0x23,0x35,0x17,0x0F,
	0x05,0x2F,0x3C,0x18,0x24,0x36,0x1A,0x0B,0x07,0x20,0x06,0x09,0x43,0x0C,0x2A,0x36,
	0x1B,0x07,0x0B,0x1E,0x84,0x39,0x1A,0x05,0x10,0x0B,0x92,0x19,0x0C,0x18,0x2D,0x09,
	0x91,0x1B,0x0C,0x19,0x2D,0x07,0x91,0x1C,0x08,0x1E,0xBB,0x22,0x06,0x21,0xB6,0x26,
	0x06,0x22,0xB5,0x26,0x06,0x23,0xB4,0x27,0x05,0x23,0xB4,0x28,0x04,0x0E,0x03,0x12,
	0xB7,0x28,0x03,0x0E,0x06,0x0E,0xB9,0x28,0x03,0x0E,0x06,0x0B,0xBC,0x08,0x0E,0x14,
	0x03,0x10,0x03,0x0C,0xBB,0x08,0x0F,0x32,0xBA,0x09,0x08,0x12,0x07,0x21,0x92,0x05,
	0x1C,0x2B,0x0F,0x17,0x93,0x07,0x0F,0x39,0x0E,0x14,0x89,0x18,0x09,0x41,0x0C,0x0F,
	0x88,0x62,0x0B,0x10,0x48,0x0A,0x36,0x64,0x09,0x14,0x44,0x0C,0x33,0x50,0x08,0x2D,
	0x3E,0x19,0x0B,0x08,0x18,0x4A,0x12,0x2B,0x3C,0x1B,0x09,0x0A,0x10,0x04,0x04,0x4B,
	0x12,0x2B,0x3B,0x1D,0x08,0x0B,0x0B,0x56,0x08,0x35,0x39,0x1E,0x08,0x0C,0x09,0x31,
	0x03,0x60,0x37,0x63,0x0B,0x13,0x03,0x4A,0x37,0x64,0x0C,0x11,0x06,0x23,0x03,0x24,
	0x36,0x65,0x0D,0x0F,0x0B,0x1E,0x04,0x24,0x36,0x6D,0x06,0x0C,0x0D,0x1D,0x04,0x24,
	0x37,0x6E,0x0A,0x07,0x07,0x22,0x04,0x25,0x37,0x6F,0x09,0x27,0x0A,0x25,0x38,0x8C,
	0x04,0x0F,0x09,0x25,0x39,0x58,0x04,0x31,0x06,0x38,0x39,0x56,0x11,0x27,0x0A,0x1D,
	0x04,0x06,0x05,0x05,0x3B,0x5C,0x11,0x27,0x0A,0x1C,0x45,0xBC,0x45,0xBA,0x45,0x3B,
	0x03,0x03,0x04,0x7B,0x45,0x39,0x0C,0x74,0x47,0x3D,0x0C,0x52,0x04,0x1F,0x47,0x3F,
	0x04,0x31,0x03,0x19,0x13,0x1D,0x47,0x32,0x03,0x3F,0x04,0x19,0x13,0x1A,0x49,0x32,
	0x05,0x3C,0x06,0x1D,0x05,0x23,0x49,0x33,0x05,0x3B,0x06,0x0E,0x08,0x2F,0x49,0x35,
	0x03,0x3B,0x06,0x0F,0x09,0x2B,0x4B,0x72,0x05,0x15,0x05,0x29,0x4A,0x74,0x04,0x17,
	0x09,0x21,0x4C,0x75,0x04,0x18,0x0F,0x19,0x4C,0x76,0x04,0x18,0x13,0x15,0x4C,0x76,
	0x03,0x18,0x04,0x09,0x0B,0x13,0x4C,0x75,0x04,0x0A,0x05,0x0A,0x04,0x0E,0x07,0x13,
	0x4C,0x75,0x03,0x0B,0x06,0x09,0x04,0x26,0x4C,0x75,0x03,0x0D,0x0E,0x27,0x4C,0x85,
	0x0B,0x28,0x4C,0xB6,0x4C,0xB5,0x4E,0xB2,0x50,0xB2,0x51,0xB1,0x53,0xAF,0x53,0xAE,
	0x55,0x0E,0x03,0x9E,0x55,0x0E,0x04,0x9C,0x57,0x0E,0x04,0x19,0x09,0x36,0x03,0x42,
	0x5A,0x0E,0x04,0x17,0x0B,0x10,0x03,0x0C,0x04,0x14,0x06,0x40,0x5C,0x0C,0x06,0x11,
	0x10,0x0F,0x05,0x0A,0x06,0x0D,0x0D,0x3E,0x6E,0x0B,0x14,0x0F,0x07,0x08,0x0C,0x07,
	0x0F,0x13,0x07,0x1E,0x76,0x07,0x16,0x0F,0x1B,0x05,0x12,0x10,0x09,0x14,0x9A,0x0E,
	0x37,0x09,0x12,0x0C,0x9B,0x0B,0x3A,0x07,0x14,0x0A,0x00,0x01,0x00,0x01,0x00,0x01,
	0x63
};
unsigned	char	g_scrn[256][256];
unsigned	char	g_text[25][40];

#define	CHR_A1_RED			0xa1
#define	CHR_81_PINK			0x81
#define	CHR_40_ATTACKER_UP		0x40
#define	CHR_41_ATTACKER_MID		0x41
#define	CHR_42_ATTACKER_DOWN	0x42
#define	CHR_DIR_2_MISSILE(d,dx)	((d)+((dx==1)?0x88:0x48))

#define IS_GE_F0_TELLAIN(n)  	((n) >= 0xF0)	
#define IS_LT_40_AIR(n)  	((n) < 0x40)	
#define	IS_GE_C0_GROUND(n)	((n) >= 0xC0)
#define	IS_LT_C0_SKY(n)		((n) < 0xC0)
#define IS_GE_10_VISIBLE(n)	((n) >= 0x10)
#define IS_LT_10_UNVISIBLE(n)	((n) < 0x10)
#define IS_GE_30_PHISICAL(n)	((n) >= 0x30)
#define IS_LT_30_UNPHISICAL(n)	((n) < 0x30)

#define	var	unsigned int

struct Pos
{
	char	x;
	char	y;
};

struct Carrier
{
	var	scrn_x;
	var	scrn_y;
	var	x;
	var	y;
	var	_04;
	var	_bcd1;
	var	_bcd2;
	var	_bcd3;
	var	_cntTama08;
	var	_09;
	var	_0A;
	var	_0B;
	var	_0C;
	var	_0D;
	var	_0E;
	var	_0F;
};

class Fighter
{

public:
	var	x;
	var	y;
	var	_stat02;
	var	_chr03;
	var	_stat04;
	var	_HP05;
	var	_flagsJoy06;
	var	_chrSelfId07;
	var	_cntTama08;
	var	_09;
	var	_0A;
	var	_0B;
	var	_0C;
	var	_0D;
	var	_0E;
	var	_0F;

	enum
	{
		STAT_DOWN = 0x80
	};
};

struct Missile
{
	var	x;
	var	y;
	var	_dir02;
	var	_mlim03;
};


struct Smoke
{
	var	x;
	var	y;
	var	_chr02;
	var	_lim03;
};

struct Sight	//	4byte
{
	var	x;
	var	y;
	var	_sgt02;
	var	_lim03;
};
struct Mine
{
	var	x;
	var	y;
};
struct	Quad
{
	var	_E00;
	var	_D01;
	var	_H11;
	var	_L10;
};


/*
アドレス 	略称 	ブロック 	機能名称
00 	R0 	Tone Gen. 	Channel A Fine Tune Register
01 	R1 	Tone Gen. 	Channel A Coarse Tune Register
02 	R2 	Tone Gen. 	Channel B Fine Tune Register
03 	R3 	Tone Gen. 	Channel B Coarse Tune Register
04 	R4 	Tone Gen. 	Channel C Fine Tune Register
05 	R5 	Tone Gen. 	Channel C Coarse Tune Register
06 	R6 	Noise Gen. 	Noise Period Register
07 	R7 	Mixer, I/O 	Mixer Control - I/O Enable Register
08 	R10 	Amp. Control 	Channel A Amplitude Control Register
09 	R11 	Amp. Control 	Channel B Amplitude Control Register
0A 	R12 	Amp. Control 	Channel C Amplitude Control Register
0B 	R13 	Envelope Gen. 	Envelope Fine Tune Register
0C 	R14 	Envelope Gen. 	Envelope Coarse Tune Register
0D 	R15 	Envelope Gen. 	Envelope Shape/Cycle Control Register
0E 	R16 	I/O 	I/O Port A Data Store
0F 	R17 	I/O 	I/O Port B Data Store*/
struct PsgJoy
{
	char	_1B00_Data[255];
	char	_1C00_Reg;
};


Carrier	 g_infCarrier;//	*(0xB600)
Fighter	 g_infAttacker;//	*(0xB610 B63fh)
Fighter	 g_dummy0;//	*(0xB610 B63fh)
Fighter	 g_dummy1;//	*(0xB610 B63fh)
Fighter	 g_tblEnemy[60];//	*(0xB640)
Smoke	 g_BB00_tblSmoke[256];//	*(0xBA00)

Missile	 g_BA00_tblMissile[32];//	*(0xBA00~0xBA80)
Sight	 g_BF00_tblSightA[32];//	*(0xBF00)
Sight 	 g_BA30_tblSightB[32];//	*(0xBA30)
Mine	 g_tblMine[16];//	*(0xBF80)
//unsigned int		 g_bufen;

PsgJoy g_infPsgJoy;//		*(0x1B00 ~ 0x1C00)
Pos g_posA906 = { 6, 105 };
Pos g_posB = { 6, 106 };


	Quad	quad;



//-----------------------------------------------------------------------------
void func_RMCE2A_DecodeMap()									//			    
//-----------------------------------------------------------------------------
{
		bool	flg = true;
		unsigned int		x = 0;
		unsigned int		y = 0;
		for ( unsigned int i = 0 ; i < sizeof(g_D102_mapdata) ; i++ )
		{
			unsigned char d = g_D102_mapdata[i]-1;

			unsigned int	a = (unsigned int)(d);
			for ( unsigned int j = 0 ; j < a ; j++ )
			{
				if ( x >= 256 || y >= 128 ) 
				{
					printf("error\n" );
					exit(0);
				}
				g_scrn[y][x] = flg ? 0xFF : 0x00;
				
				x++;
				if ( x >= 256 )
				{
					x = 0;
					y++;
				}
			}
			flg = !flg;
		}
}

//-----------------------------------------------------------------------------
void func_RMCE5D_RefineMapParts( unsigned int y, unsigned int x )									//			    
//-----------------------------------------------------------------------------
{
	char	g_CE91[16] = 
	{
	//			   右左下上
		0xFF,	 // 0 0 0 0
		0xFF,	 // 0 0 0 1
		0xFF,	 // 0 0 1 0
		0xFF,	 // 0 0 1 1
		0xFF,	 // 0 1 0 0
		0xFC,	 // 0 1 0 1	*
		0xFD,	 // 0 1 1 0	*
		0xFF,	 // 0 1 1 1
		0xFF,	 // 1 0 0 0
		0xFB,	 // 1 0 0 1	*
		0xFE,	 // 1 0 1 0	*
		0xFF,	 // 1 0 1 1
		0xFF,	 // 1 1 0 0
		0xFF,	 // 1 1 0 1
		0xFF,	 // 1 1 1 0
		0xFF	 // 1 1 1 1
	};

	unsigned int a = 0;
	if ( g_scrn[y-1][x  ] != 0 ) a |= (1<<0);
	if ( g_scrn[y+1][x  ] != 0 ) a |= (1<<1);
	if ( g_scrn[y  ][x-1] != 0 ) a |= (1<<2);
	if ( g_scrn[y  ][x+1] != 0 ) a |= (1<<3);

	g_scrn[y][x] = g_CE91[a];
	return;
}
//-----------------------------------------------------------------------------
void func_RMCE4C_RefineMap()
//-----------------------------------------------------------------------------
{
	for ( unsigned int y = 1 ; y < 127 ; y++ )
	{
		for ( unsigned int x = 0 ; x < 256 ; x++ )
		{
			if ( g_scrn[y][x] != 0 ) func_RMCE5D_RefineMapParts( y, x );					//CE53: C4 5D CE	  
		}
	}

	return;
}
//-----------------------------------------------------------------------------
void func_RMCD19_LocateWeapons()									//			    
//-----------------------------------------------------------------------------
{
	unsigned int	idx = 0;

	for ( unsigned int i = 0 ; i < 8 ; i++ )
	{
		unsigned int x = g_D000_location_weapoins[idx++];
		unsigned int y = g_D000_location_weapoins[idx++]-64;
		if ( y == -64 ) y = 0;
		if ( x >= 256 || y >= 128 ) {printf("error %2d : %02Xh %02Xh in %d\n",idx,x,y, __LINE__);exit(1);}
		g_tblEnemy[i].x = x;				//CD29: DD 77 00	  
		g_tblEnemy[i].y = y;				//CD2C: DD 71 01	  
		g_tblEnemy[i]._chrSelfId07 = CHR_A1_RED;				//CD2F: DD 36 07 A1     
		g_tblEnemy[i]._09 = 0x04;				//CD33: DD 36 09 04     
		g_tblEnemy[i]._0A = x;				//CD37: DD 77 0A	  
		g_tblEnemy[i]._0B = x;				//CD3A: DD 77 0B	  
	}

	for ( unsigned int i = 8 ; i < 60 ; i++ )
	{
		unsigned int x = g_D000_location_weapoins[idx++];
		unsigned int y = g_D000_location_weapoins[idx++]-64;
		if ( y == -64 ) y = 0;
		if ( x >= 256 || y >= 128 ) {printf("error %2d : %02Xh %02Xh in %d\n",idx,x,y, __LINE__);exit(1);}
		g_tblEnemy[i].x = x;				//CD47: DD 77 00	  
		g_tblEnemy[i].y = y;			//CD4A: DD 71 01	  
		g_tblEnemy[i]._chrSelfId07 = CHR_81_PINK;				//CD4D: DD 36 07 81     
		g_tblEnemy[i]._09 = 0x02;				//CD51: DD 36 09 02     
		g_tblEnemy[i]._0A = x;				//CD55: DD 77 0A	  
		
	}

	//	床砲台
	for ( unsigned int i = 0 ; i < 14 ; i++ )
	{
		unsigned int x = g_D000_location_weapoins[idx++];
		unsigned int y = g_D000_location_weapoins[idx++]-64;
//	printf("data  %2d : %3d %3d in %d\n",idx,x,y, __LINE__);
		if ( x >= 256 || y >= 128 ) {printf("error %2d : %02Xh %02Xh in %d\n",idx,x,y, __LINE__);exit(1);}

		g_BF00_tblSightA[i].x = x;				//CD69: DD 71 00	  
		g_BF00_tblSightA[i].y = y;				//CD6C: DD 70 01	  
		g_BF00_tblSightA[i]._lim03 = 0x02;				//CD6F: DD 36 03 02     
		g_scrn[y][x  ] = 0xC1;						//CD76: ED 79	     
		g_scrn[y][x+1] = 0xD1;						//CD7B: ED 79	     
		

	}
	//	天井砲台
	for ( unsigned int i = 14 ; i < 28 ; i++ )
	{
		unsigned int x = g_D000_location_weapoins[idx++];
		unsigned int y = g_D000_location_weapoins[idx++]-64;
		if ( x >= 256 || y >= 128 ) {printf("error %2d : %02Xh %02Xh in %d\n",idx,x,y, __LINE__);exit(1);}
		g_BF00_tblSightA[i].x = x;				//CD89: DD 71 00	  
		g_BF00_tblSightA[i].y = y;				//CD8C: DD 70 01	  
		g_BF00_tblSightA[i]._lim03 = 0x01;				//CD8F: DD 36 03 01     
		g_scrn[y][x  ] = 0xC0;						//CD96: ED 79	     
		g_scrn[y][x+1] = 0xd0;						//CD9B: ED 79	     
		
	}

	//	目玉
	for ( unsigned int i = 28 ; i < 32 ; i++ )
	{
		unsigned int x = g_D000_location_weapoins[idx++];
		unsigned int y = g_D000_location_weapoins[idx++]-64;
		if ( x >= 256 || y >= 128 ) {printf("error %2d : %02Xh %02Xh in %d\n",idx,x,y, __LINE__);exit(1);}
		g_BF00_tblSightA[i].x = x;				//CDA9: DD 71 00	  
		g_BF00_tblSightA[i].y = y;				//CDAC: DD 70 01	  
		g_BF00_tblSightA[i]._lim03 = 0x02;				//CDAF: DD 36 03 02     
		g_scrn[y][x  ] = 0xc3;						//CDB6: ED 79	     
		g_scrn[y][x+1] = 0xd3;						//CDBB: ED 79	     
		
	}

	//	基地
	for ( unsigned int i = 0 ; i < 4 ; i++ )
	{
		unsigned int x = g_D000_location_weapoins[idx++];
		unsigned int y = g_D000_location_weapoins[idx++]-64;
		if ( x >= 256 || y >= 128 ) {printf("error %2d : %02Xh %02Xh in %d\n",idx,x,y, __LINE__);exit(1);}
		g_scrn[y][x  ] = 0xCD;						//CDCC: ED 51	     
		g_scrn[y][x+1] = 0xDD;						//CDCF: ED 59	     
		
	}

	//	壁
	{
		unsigned int x = 112;						//CDD4: 0E 70	     
		for ( unsigned int y = 0 ; y < 128 ; y++ )
		{
			if ( g_scrn[y][x] < 0xF0 )			//CDDF: 30 02	     
			{
				g_scrn[y][x] = 0xDF;						//CDE1: ED 51	     
			}
		}
	}

	//	地雷
	for ( unsigned int i = 0 ; i < 16 ; i++ )
	{
		unsigned int x = g_D000_location_weapoins[idx++];
		unsigned int y = g_D000_location_weapoins[idx++]-64;
		if ( x >= 256 || y >= 128 ) {printf("error %2d : %02Xh %02Xh in %d\n",idx,x,y, __LINE__);exit(1);}
		g_scrn[y][x  ] = 0xF9;						//CDF2: ED 51	     
		g_scrn[y][x+1] = 0xFA;						//CDF5: ED 59	     
		g_tblMine[i].x = x;
		g_tblMine[i].y = y;
		
	}

	return;								//CE05: C9		  
}
//-----------------------------------------------------------------------------
void func_RMCE06_ClearBuffer()									//			    
//-----------------------------------------------------------------------------
{

//	char*	p = (char*)&g_infCarrier;
//	unsigned int		size = (unsigned int)&g_bufen-(unsigned int)&g_infCarrier;
//	memset( p, 0, size );

	memset( &g_infCarrier, 0, sizeof(g_infCarrier) ); 
	memset (&g_infAttacker, 0, sizeof(g_infAttacker) );;//	*(0xB610 B63fh)
	memset (&g_dummy0, 0, sizeof(g_dummy0) );			//	*(0xB610 B63fh)
	memset (&g_dummy1, 0, sizeof(g_dummy1) );			//	*(0xB610 B63fh)
	memset (&g_tblEnemy, 0, sizeof(g_tblEnemy) );		//	*(0xB640)
	memset (&g_BB00_tblSmoke, 0, sizeof(g_BB00_tblSmoke) );//	*(0xBA00)
	memset (&g_BA00_tblMissile, 0, sizeof(g_BA00_tblMissile) );	//	*(0xBA00~0xBA80)
	memset (&g_BF00_tblSightA, 0, sizeof(g_BF00_tblSightA) );	//	*(0xBF00)
	memset (&g_BA30_tblSightB, 0, sizeof(g_BA30_tblSightB) );	//	*(0xBA30)
	memset (&g_tblMine, 0, sizeof(g_tblMine) );					//	*(0xBF80)


//	return;								//CE29: C9		  
}

//-----------------------------------------------------------------------------
void func_RMC000_GetQuad( Quad* pQuad, unsigned int y, unsigned int x )
//-----------------------------------------------------------------------------
{
	//E
	pQuad->_E00 = g_scrn[y  ][x  ];					//C000: ED 58		 

	//D
	pQuad->_D01 = g_scrn[y  ][x+1];					//C003: ED 50	     

	//H
	pQuad->_H11 = g_scrn[y+1][x+1];					//C006: ED 60	     

	//L
	pQuad->_L10 = g_scrn[y+1][x  ];					//C009: ED 68	     
	return;								//C00C: C9		  
}
//-----------------------------------------------------------------------------
bool func_RMC253_CheackQuad( Quad* pQuad )									//			    
//-----------------------------------------------------------------------------
{
//	A = 0x30						//C253: 3E 30	     
	//D
	if ( '0' < pQuad->_D01 ) return 1;							//C256: D8		  

	//E
	if ( '0' < pQuad->_E00 ) return 1;							//C258: D8		  

	//H
	if ( '0' < pQuad->_H11 ) return 1;							//C25A: D8		  

	//L
	if ( '0' < pQuad->_L10 ) return 1;
	return 0;								//C25C: C9		  
} 

//-----------------------------------------------------------------------------
void func_RMC1E5_DrawFighter( Fighter* pFighter, unsigned int y, unsigned int x )									//			    
//-----------------------------------------------------------------------------
{
	pFighter->x = x;								//C1E5: DD 71 00	  
	pFighter->y = y;								//C1E8: DD 70 01	  


	if ( pFighter->_stat04 >= 0x02 )				//JR	C,RMC202	//C1F0: 38 10
	{
		unsigned int a = pFighter->_chrSelfId07;
		a = (a & 0xE0) + 8;							//C1F6: E6 E0		     AND     E0h	  
		g_scrn[y+1][x  ] = a;						//C1FA: ED 79	     
		g_scrn[y+1][x+1] = a +0x10;					//C1FF: ED 79	     
		return;	
	}
	else
	{												//RMC202
		unsigned int a = pFighter->_chrSelfId07;				//C203: DD 7E 07		  LD	A,(IX+07h)
		g_scrn[y][x  ] = a;							//C206: ED 79	     
		g_scrn[y][x+1] = a +0x10;					//C20B: ED 79		     !OUT     (C),A
		if ( pFighter->_stat04 == 0 ) 				//C211: 20 28	     
	 	{
			unsigned int a = pFighter->_chrSelfId07+0x10;	//
			a = (a & 0xF0) + 3;
			
			if ( pFighter->_stat02 == 0 ) 		//C21E: 28 10
			{
				a++;							//C230: 1C
			}
			else
			if ( pFighter->_chr03 == 0 ) 		//C223: 28 0B 
			{
				a++;							//C230: 1C
			}
			else
			if ( (pFighter->_stat02 ^ pFighter->_chr03) < 0x80 )  // C22D: 38 02 
			{
			}
			else
			{
				a+=2;							//C22F: 1C   
			}

			//	立ちファイター表示
			g_scrn[y+1][x+1] = a;				//C233: ED 79		     !OUT     (C),A
			g_scrn[y+1][x  ] = a-0x10;			//C238: ED 79		     !OUT     (C),A
			return; 							//C23A: C9		  
		}
		else
		{										//RMC23B:									//			    
			unsigned int a = pFighter->_chrSelfId07;
			a = (a & 0xF0) + 6;					//C241: DD 7E 00		  LD	A,(IX+0x00)

			if ( (pFighter->x & 0x01) != 0 )	//C246: 28 01		     JR	Z,RMC249
			{
				a++;
			}						  	  		//RMC249:
			g_scrn[y+1][x+1] = a;				//C24B: ED 79		     !OUT     (C),A
			g_scrn[y+1][x  ] = a-0x10;			//C250: ED 79		     !OUT     (C),A
			return;								//C252: C9			  RET			
		}
	}
}

//-----------------------------------------------------------------------------
void func_RMC25E_SetDocking( Fighter *pAttacker )									//			    
//-----------------------------------------------------------------------------
{
//	unsigned int a = sys.key.inkey().ascii; //func_RM001B_BASIC_IOCS_KEYINPUT();					//C260: CD 1B 00	  
	if ( sys.key.now('2') ) 								//C265: 28 05	     
	{														//	RMC26C:									//			    
printf ("'2' stat02=0x%x  %d %d   %d %d\n", pAttacker->_stat04,  g_infCarrier.x+1, g_infCarrier.y-1, pAttacker->x, pAttacker->y);
		if ( pAttacker->_stat04 == g_infAttacker.STAT_DOWN ) return;							//C271: C8		  
		if ( g_infCarrier.x+1 != pAttacker->x ) return;		//C279: C0		  
		if ( g_infCarrier.y-1 != pAttacker->y ) return;		//C281: C0		  
		pAttacker->_stat04 = g_infAttacker.STAT_DOWN;		//C282: DD 36 04 80     
		unsigned int y = pAttacker->x;								//C286: DD 4E 00	  
		unsigned int x = pAttacker->y	;							//C289: DD 46 01	  
		g_scrn[y  ][x  ] = 0x00	;							//C28E: ED 79	     
		g_scrn[y  ][x+1] = 0x00;							//C291: ED 79	     
		g_scrn[y+1][x+1] = 'X';								//C296: ED 79	     
		g_scrn[y+1][x  ] = 'H';								//C29B: ED 79	     
		return;												//C29D: C9		  
	}
	else
	if ( sys.key.now('8') ) 								//C269: 28 33	     
	{														//	RMC29E:									//			    
printf ("'8' stat02=0x%x  %d %d   %d %d\n", pAttacker->_stat04,  g_infCarrier.x+1, g_infCarrier.y-1, pAttacker->x, pAttacker->y);
		if ( pAttacker->_stat04 != 0x80 ) return	;		//C2A3: C0		  
		unsigned int y = g_infCarrier.y;								//C2A4: ED 4B 02 B6     
		unsigned int x = g_infCarrier.x;								//C2A4: ED 4B 02 B6     
		g_scrn[y][x+1] = 0	;								//C2AB: ED 79	     
		g_scrn[y][x+2] = 0	;								//C2AE: ED 79	     
		func_RMC000_GetQuad( &quad, y-1, x+1 );				//C2B2: CD 00 C0	  
printf ("'8'.1 %d %d\n", x,y);
		if ( false == func_RMC253_CheackQuad( &quad ) )		//C2B5: CD 53 C2	  
		{
printf ("'8'.2\n");
			pAttacker->_stat04 = 0x00;						//C2B9: DD 36 04 00     
			pAttacker->_chrSelfId07 = (pAttacker->_chrSelfId07 & 0xF0) | 0x01;	//C2C4: DD 77 07	  
			func_RMC1E5_DrawFighter( pAttacker, y, x );		//C2C7: CD E5 C1	  
			return;											//C2CA: C9		  
		}
	}
	return;													//C26B: C9		  
}
//-----------------------------------------------------------------------------
void func_RMC10D_CollitionTerrain( Fighter* pFighter )
//-----------------------------------------------------------------------------
{
		unsigned int y = pFighter->y;					//C137: DD 46 01	  
		unsigned int x = pFighter->x;					//C13A: DD 4E 00	  

	if ( pFighter->_stat02 +0x80 >= 0x83 ) 		//C114: 38 04	     
	{
		pFighter->_stat02 = 0x02;				//C116: DD 36 02 02     
	}

	if ( pFighter->_stat02 +0x80 < 0x7E ) 		//C11C: 30 04	     
	{
		pFighter->_stat02 = 0xFE;				//C11E: DD 36 02 FE     
	}

	if ( pFighter->_chr03 + 0x80 >= 0x89 )		//C129: 38 04	     
	{
		pFighter->_chr03 = 0x08;				//C12B: DD 36 03 08     
	}

	if ( pFighter->_chr03 + 0x80 < 0x78 ) 		//C131: 30 04	     
	{
		pFighter->_chr03 = 0xF8;				//C133: DD 36 03 F8     
	}


	while(1)
	{
		unsigned int y = pFighter->y;					//C137: DD 46 01	  
		unsigned int x = pFighter->x;					//C13A: DD 4E 00	  

		if ( pFighter->_stat02 >= 0xFE )		////C142: 30 06	     
		{
			x--;								//C14A: 0D		  
		}
		else	
		if ( pFighter->_stat02 != 0 ) 			//C146: 28 03	     
		{
			x++;								//C148: 0C		  
		}

		unsigned int a = pFighter->_chr03;				//C14B: DD 7E 03	  

		if ( a >= 0xFC ) 						//C150: 30 11	     
		{
			y--;								//C163: 05		  
		}
		else
		if ( a >= 0xF8 ) 						//C154: 30 0C	     
		{
			y--;								//C163: 05		  
			y--;								//C163: 05		  
		}
		else
		if ( a == 0x00 ) 						//C158: 28 0A	     
		{
		}
		else
		if ( a >= 0x04 )						//C15C: 38 01	     
		{
			y++;								//C15E: 04		  
			y++;								//C15F: 04		  
		}
		else
		{
			y++;								//C15F: 04		  
		}


		while(1)
		{
			func_RMC000_GetQuad( &quad, y,x );	//C164: CD 00 C0	  
			if ( false == func_RMC253_CheackQuad( &quad ) )					//C167: CD 53 C2	  
			{
				func_RMC1E5_DrawFighter( pFighter, y, x );					//C16A: 30 79	     
				return;
			}
			a = pFighter->_chr03;					//C16C: DD 7E 03	  
			a += 0x80;								//C16F: C6 80	     
			if ( a < 0x7C ) 							////C173: 30 06	     
			{
				pFighter->_chr03 = 0xFC;				//C175: DD 36 03 FC     
				break;
			}
			if ( a < 0x81 ) 							//C17D: 30 0A	     
			{
				pFighter->_stat02 = 0x00;				//C17F: DD 36 02 00     
				pFighter->_chr03 = 0x00;				//C183: DD 36 03 00     
				break;
			}
			y = pFighter->y;						//C189: DD 46 01	  
			x = pFighter->x;						//C18C: DD 4E 00	  
			if ( a >= 0x85 ) 						//C191: 38 01	     
			{
				y++;									//C193: 04		  
			}

			while(1)
			{
				y++;							//C194: 04		  
				func_RMC000_GetQuad( &quad, y,x );					//C195: CD 00 C0	  
				if ( false == func_RMC253_CheackQuad( &quad ) )					//C198: CD 53 C2	  
				{
					pFighter->_stat02 = 0x00;				//C1C5: DD 36 02 00     
					break;
				}
				a = 0xFD;						//C19D: 3E FD	     
				if ( a >= pFighter->_stat02 ) //< 0 ) {} 				//C1A2: 38 0A	     
				{
					x++;							//C1A4: 0C		  
					func_RMC000_GetQuad( &quad, y, x );					//C1A5: CD 00 C0	  
					if ( false == func_RMC253_CheackQuad( &quad ))					//C1A8: CD 53 C2	  
					{
						pFighter->_stat02 = 0x01;		//C1CB: DD 36 02 01     
						break;
					}
					x--;								//C1AD: 0D		  
				}
				a = pFighter->_stat02;				//C1AE: DD 7E 02	  
				a += 0x80;							//C1B1: C6 80	     
				if ( a < 0x81 ) 						//C1B5: 30 0A	     
				{
					x--;								//C1B7: 0D		  
					func_RMC000_GetQuad( &quad, y,x );					//C1B8: CD 00 C0	  
					if ( false == func_RMC253_CheackQuad( &quad ))					//C1BB: CD 53 C2	  
					{
						pFighter->_stat02 = 0xFF;				//C1D1: DD 36 02 FF     
						break;
					}
					x++;							//C1C0: 0C		  
				}
				y--;							//C1C1: 05		  
				y--;							//C1C2: 05		  
			}//	go-to @@b					//C1C3: 18 CF	     

//printf("y %d %d\n", pFighter->y , y );
			if ( pFighter->y != y ) continue; 					//C1D9: 20 89	     
			pFighter->_chr03 = 0x00;				//C1DB: DD 36 03 00     
		}					//C1DF: 18 83	     
	}
}

//-----------------------------------------------------------------------------
void func_RMC00D_MoveFighter( Fighter* pFighter )									//			    
//-----------------------------------------------------------------------------
{
	unsigned int y = pFighter->y;				//C00D: DD 46 01	  
	unsigned int x = pFighter->x;				//C010: DD 4E 00	  



	if ( pFighter->_stat04 >= 0x02 )				//C018: 38 09	     
	{
		func_RMC000_GetQuad( &quad, y,x );			//C01A: CD 00 C0	  
		if ( '0' < quad._D01 ) return;				//C020: D8		  
		if ( '0' < quad._E00 ) return;				//C022: D8		  
	}

	g_scrn[y  ][x  ] = 0;					//C025: ED 79	     
	g_scrn[y  ][x+1] = 0;					//C028: ED 79	     
	g_scrn[y+1][x+1] = 0;					//C02B: ED 79	     
	g_scrn[y+1][x  ] = 0;					//C02E: ED 79	     

	func_RMC000_GetQuad( &quad, y,x );					//C030: CD 00 C0	  
	if ( '0' >= quad._H11 || '0' >= quad._L10 ) 
	{
		unsigned int	flags = pFighter->_flagsJoy06;			//C0C2: DD 7E 06		  LD	A,(IX+06h)

		if ( (flags&(1<<0)) != 0 )					//C0C7: 28 05		     JR	Z,RMC0CE
		{
			pFighter->_chr03++;					//C0C9: DD 34 03	  
			pFighter->_stat04 = 0x00;		//+		//C07E: DD 36 04 00     
			func_RMC10D_CollitionTerrain( pFighter );			//+		//C082: C3 0D C1	  
			return;
		}
		else
		{
			pFighter->_chr03--;					//C0CE: DD 35 03	  
			if ( (flags&(1<<2)) == 0 )				//C0D3: 28 08	     
			{
				pFighter->_stat02--;
			}
			else
			if ( (flags&(1<<3)) == 0 ) 
			{
				pFighter->_stat02++;
			}

			pFighter->_stat04 = 0x00;		//+		//C07E: DD 36 04 00     
			func_RMC10D_CollitionTerrain( pFighter );			//+		//C082: C3 0D C1	  
			return;
		}
	}


	if ( 0x02 < pFighter->_stat04 )			//C042: 30 0B	     
	{
		pFighter->_stat04--;					//C044: DD 35 04	  
		if ( 0x01 < pFighter->_stat04 ) goto RMC0F0;					//C04C: DA F0 C0	  
	}

	if ( pFighter->_chr03 + 0x80 >= 0x85 ) 
	{
		pFighter->_stat04 = pFighter->_chr03 -0x82;	//+			//C0ED: DD 77 04	  
	}
	else
	{
		if ( (pFighter->_flagsJoy06&(1<<0)) != 0 ) 					//C05E: 28 35	     
		{
			if ( (pFighter->_flagsJoy06&(1<<1)) != 0 )
			{
				if ( pFighter->_stat04 < 0x02 ) 						//C06B: 30 11	     
				{
					pFighter->_chr03 = 0x00;							//C06D: DD 36 03 00     
					if ( (pFighter->_flagsJoy06&(1<<2)) != 0 )				//C074: 28 0F	     
					{
						if ( (pFighter->_flagsJoy06&(1<<3)) == 0 ) 
						{
							pFighter->_stat02 = 0x02;				//C08B: DD 36 02 02     
							pFighter->_stat04 = 0x01;				//C08F: DD 36 04 01     
							func_RMC10D_CollitionTerrain( pFighter );					//C093: 18 78	     
							return;
						}
						else
						{
							pFighter->_stat02 = 0x00;				//C07A: DD 36 02 00     
							pFighter->_stat04 = 0x00;				//C07E: DD 36 04 00     
							func_RMC10D_CollitionTerrain( pFighter );					//C082: C3 0D C1	  
							return;
						}
					}
				}
				pFighter->_stat02 = 0xFE;					//C085: DD 36 02 FE     
				pFighter->_stat04 = 0x01;					//C08F: DD 36 04 01     
				func_RMC10D_CollitionTerrain( pFighter );	//C093: 18 78	     
				return;
			}
		}
		else
		{

			if ( pFighter->_stat04 >= 0x02 ) 
			{
				pFighter->_chr03 = 0xFB;					//C0BC: DD 36 03 FB     
			}
			else
			{												//C09C: 30 1E	     
				pFighter->_chr03 = 0xFF;					//C09E: DD 36 03 FF     
			}
		 
			while(1)
			{
				if ( (pFighter->_flagsJoy06&(1<<2)) != 0 )			//C0A4: 28 0A	     
				{
					if ( (pFighter->_flagsJoy06&(1<<3)) == 0 ) 
					{
						pFighter->_stat02 = 0x01;				//C0B6: DD 36 02 01     
						pFighter->_stat04 = 0x00;		//+		//C07E: DD 36 04 00     
						func_RMC10D_CollitionTerrain( pFighter );			//+		//C082: C3 0D C1	  
						return;
					}
					else
					{
						pFighter->_stat02 = 0x00;				//C0AA: DD 36 02 00     
						pFighter->_stat04 = 0x00;		//+		//C07E: DD 36 04 00     
						func_RMC10D_CollitionTerrain( pFighter );			//+		//C082: C3 0D C1	  
						return;
					}
				}
				else
				{
					pFighter->_stat02 = 0xFF;				//C0B0: DD 36 02 FF     
					pFighter->_stat04 = 0x00;		//+		//C07E: DD 36 04 00     
					func_RMC10D_CollitionTerrain( pFighter );			//+		//C082: C3 0D C1	  
					return;
				}
			}
		}
	}


RMC0F0:				
	pFighter->_stat02 = 0;									//C0F2: DD 77 02	  
	pFighter->_chr03 = 0;									//C0F5: DD 77 03	  
	pFighter->_chrSelfId07 = (pFighter->_chrSelfId07 & 0xF0) | 0x01;				//C0FF: DD 77 07	  
	if ( 0x01 >= pFighter->_stat04 )							//C107: 38 04	     
	{
		pFighter->_stat04 = 0x02;								//C109: DD 36 04 02     
	}

	func_RMC10D_CollitionTerrain( pFighter );
}

//-----------------------------------------------------------------------------
bool func_RMC3CF_CollitionAt( Fighter *pFighter, unsigned int y, unsigned int x )									//			    
//-----------------------------------------------------------------------------
{
	for ( unsigned int j = 0 ; j < 2 ; j++ )
	{
		for ( unsigned int i = 0 ; i < 4 ; i++ )
		{
			unsigned int a = g_scrn[y+1+j][x+i];	//C3D5: ED 78
			if ( a >= ' ' ) return 1;	//C3D9: 30 35
		}
	}
	if ( g_scrn[y][x  ] >= ' ' ) return 1;
	if ( g_scrn[y][x+3] >= ' ' ) return 1;
	if ( pFighter->_stat04 != g_infAttacker.STAT_DOWN	  ) return 0;
	if ( g_scrn[y][x+2] >= ' ' ) return 1;
	if ( g_scrn[y][x+1] >= ' ' ) return 1;
	return 0;
}

//-----------------------------------------------------------------------------
bool func_RMC3CF_CollitionAround( Fighter *pFighter, unsigned int* y, unsigned int* x )									//			    
//-----------------------------------------------------------------------------
{
	(*y)++;
	if ( func_RMC3CF_CollitionAt( pFighter, (*y)+1, (*x) ) == 0 ) return 0;					//C414: CD CF C3	  
	(*y)--;
	if ( func_RMC3CF_CollitionAt( pFighter, (*y)  , (*x) ) == 0 ) return 0;					//C419: CD CF C3	  
	(*y)--;
	if ( func_RMC3CF_CollitionAt( pFighter, (*y)-1, (*x) ) == 0 ) return 0;					//C41E: CD CF C3	  
	(*y)++;
	return 1;								//C424: C9		  
}

//-----------------------------------------------------------------------------
void func_RMC2CB_SetCarrierAttacker()	//	味方
//-----------------------------------------------------------------------------
{

	
	
	//	ジョイスティック入力
#if 0
	g_infPsgJoy._1C00_Reg = 0x0E;						//C2D4: ED 79	     
	g_infAttacker._flagsJoy06 = g_infPsgJoy._1B00_Data[0];				//C2D9: DD 77 06	  
#else
	g_infAttacker._flagsJoy06 = 0;

	if ( sys.key.now(VK_UP)    ) g_infAttacker._flagsJoy06 |= (1<<0);
	if ( sys.key.now(VK_DOWN)  ) g_infAttacker._flagsJoy06 |= (1<<1);
	if ( sys.key.now(VK_LEFT)  ) g_infAttacker._flagsJoy06 |= (1<<2);
	if ( sys.key.now(VK_RIGHT) ) g_infAttacker._flagsJoy06 |= (1<<3);


	JOYINFOEX jix;

	jix.dwSize = sizeof(jix);
	jix.dwFlags = JOY_RETURNALL;
	int ret = joyGetPosEx(0, &jix);

printf("jix1 %d %d \n"	,(int)ret, (int)jix.dwButtons); 

	if ( sys.joy1.now.Lu  ) g_infAttacker._flagsJoy06 |= (1<<0);
	if ( sys.joy1.now.Ld  ) g_infAttacker._flagsJoy06 |= (1<<1);
	if ( sys.joy1.now.Ll  ) g_infAttacker._flagsJoy06 |= (1<<2);
	if ( sys.joy1.now.Lr   ) g_infAttacker._flagsJoy06 |= (1<<3);

//g_infAttacker._flagsJoy06 = jix.dwButtons;
	{
		unsigned int	val = (unsigned int)g_infAttacker._flagsJoy06;

		sys.PrintHex( 0, 2, val );
	}



#endif


	func_RMC25E_SetDocking( &g_infAttacker );			//RMC25E		//C2DC: CD 5E C2	  
	if ( g_infAttacker._stat04 != g_infAttacker.STAT_DOWN )				//C2E4: 28 32		     JR	Z,RMC318
	{
		if ( (g_infAttacker._flagsJoy06 & (1<<0)) != 0	//C2EB: 28 0C		     JR	Z,RMC2F9
		 ||  (g_infAttacker._stat04 >= 2 ) 				//C2FF: 30 EC		     JR	NC,RMC2ED
		)
		{
			if ( g_infAttacker._cntTama08 < 10 )		//C2F2: 30 21		     JR	NC,RMC315
			{
				g_infAttacker._cntTama08++;				//C2F4: DD 34 08		  INC     (IX+08h)
			}
		}
		else
		{
			if ( g_infAttacker._cntTama08 >= 2  )		//C306: 30 08		     JR	NC,RMC310
			{
				g_infAttacker._cntTama08 -= 2;			//C312: DD 77 08		  LD	(IX+08h),A
			}
			else
			{
				g_infAttacker._flagsJoy06 |= 1;			//C30B: DD 77 06		  LD	(IX+06h),A
			}
		}
		func_RMC00D_MoveFighter( &g_infAttacker );		//C315: CD 0D C0		  CALL    RMC00D
	}

	{
		unsigned int	val = (unsigned int)g_infAttacker._flagsJoy06;

		sys.PrintHex( 0, 3, val );
	}



	unsigned int y = g_infCarrier.y;				//C318: ED 4B 02 B6     
	unsigned int x = g_infCarrier.x;				//C318: ED 4B 02 B6     

/*
	{
		unsigned int i;
		for ( i = 0 ; i < 4 ; i++ )
		{
			g_scrn[y+1][x+i] = 0;		//C322: ED 79		     !OUT     (C),A
		}
		g_scrn[y][x+i-1] = 0;			//C32A: ED 79		     !OUT     (C),A
	}
	g_scrn[y][x] = 0;					//C32E: ED 79		     !OUT     (C),A
*/
	//	キャリアー消去
	g_scrn[y  ][x  ] = 0;
	g_scrn[y  ][x+3] = 0;
	g_scrn[y+1][x  ] = 0;
	g_scrn[y+1][x+1] = 0;
	g_scrn[y+1][x+2] = 0;
	g_scrn[y+1][x+3] = 0;



	{
		bool flg = false ;

		if ( g_infAttacker._stat04 == g_infAttacker.STAT_DOWN )	//C336: 28 12	     
		{
			//	台座部消去
			g_scrn[y][x+1] = 0;			//C34E: ED 79		     !OUT     (C),A
			g_scrn[y][x+2] = 0;			//C351: ED 79		     !OUT     (C),A
		}
		else
		if ( g_infAttacker.x - x < 3 && g_infAttacker.y - y == 2 )
		{

			if ( (g_infAttacker._flagsJoy06&(1<<2)) == 0 )	//C359: 20 05	     
			{
				g_infAttacker._stat02 = 0xFF;				//C35B: DD 36 02 FF     
				y--;										//C35F: 0D		  
			}
			if ( (g_infAttacker._flagsJoy06&(1<<3)) == 0 )	//C362: 20 05	     
			{
				g_infAttacker._stat02 = 0x01;				//C364: DD 36 02 01     
				y++;										//C368: 0C		  
			}

			if ( func_RMC3CF_CollitionAround( &g_infAttacker, &y, &x ) == 1 )	
			{
				flg = true;
			}
		}

		if ( flg == false )
		{
			y = g_infCarrier.y;					//C36E: ED 4B 02 B6     
			x = g_infCarrier.x;					//C36E: ED 4B 02 B6     
			func_RMC3CF_CollitionAround( &g_infAttacker, &y, &x );					//C372: CD 13 C4	  
		}
	}	
	g_infCarrier.y = y;							//C375: ED 43 02 B6     
	g_infCarrier.x = x;							//C375: ED 43 02 B6     

	{
		unsigned int	val = (unsigned int)g_infAttacker._flagsJoy06;

		sys.PrintHex( 0, 4, val );
	}

	//	キャリアにて補充
	if ( g_infAttacker._stat04 == g_infAttacker.STAT_DOWN )				//C37E: 20 1E	     
	{
		x++;									//C380: 0C		  
		y--;									//C381: 05		  
		g_infAttacker.y = y;					//C382: DD 70 01	  
		g_infAttacker.x = x;					//C385: DD 71 00	  
		if ( g_infAttacker._HP05 < 32 )			//C38D: 30 04	     
		{
			g_infAttacker._HP05++;				//C390: DD 77 05	  
		}

		if ( g_infAttacker._cntTama08 < 10 )	//C398: 30 04	     
		{
			g_infAttacker._cntTama08++;			//C39B: DD 77 08	  
		}
	}

	y = g_infCarrier.y;							//C39E: ED 4B 02 B6     
	x = g_infCarrier.x;							//C39E: ED 4B 02 B6     

	//	キャリアの表示
	g_scrn[y  ][x  ] = 'i';						//C3A4: ED 79	     
	g_scrn[y  ][x+3] = 'l';						//C3AB: ED 79	     
	g_scrn[y+1][x+3] = '|';						//C3B0: ED 79	     
	g_scrn[y+1][x+2] = '{';						//C3B4: ED 79	     
	g_scrn[y+1][x+1] = 'z';						//C3B8: ED 79	     
	g_scrn[y+1][x  ] = 'y';						//C3BC: ED 79	     

	//	ドックインファイターの表示
	if ( g_infAttacker._stat04 == g_infAttacker.STAT_DOWN )
	{
		g_scrn[y  ][x+1] = 'j'; 						//C3C8: ED 79	     
		g_scrn[y  ][x+2] = 'k';						//C3CC: ED 79	     
	}

	return;								//C3CE: C9		  
}
//-----------------------------------------------------------------------------
void func_RMC55D_MoveEnemy()									//			    
//-----------------------------------------------------------------------------
{
	for ( unsigned int i = 0 ; i < 60 ; i++ )
	{
		if ( g_tblEnemy[i].y )
		{
			func_RMC00D_MoveFighter( &g_tblEnemy[i] );					//C56F: CD 0D C0	  
		}
	}

}

//-----------------------------------------------------------------------------
void	DrawVram2( unsigned int y, unsigned int x )
//-----------------------------------------------------------------------------
{

	g_infCarrier.scrn_y = y;				//CCFE: ED 43 00 B6     
	g_infCarrier.scrn_x = x;				//CCFE: ED 43 00 B6     

	for ( unsigned int j = 0 ; j < 25 ; j++ )
	{
		for ( unsigned int i = 0 ; i < 40 ; i++ )
		{
			unsigned int q = x+i;
			if ( q > 255 ) q =0;
			g_text[j][i] = g_scrn[y+j][q];						//CD0D: ED 79	     
		}

	}
}
//-----------------------------------------------------------------------------
void func_RMCCB9_DrawVram()									//			    
//-----------------------------------------------------------------------------
{
	unsigned int y = g_infCarrier.scrn_y;			//CCC1: ED 4B 00 B6     
	unsigned int x = g_infCarrier.scrn_x;			//CCC1: ED 4B 00 B6     

	while(1)
	{										//RMCCC5:									//			    
		unsigned int fy = g_infAttacker.y;			//CCC5: 3A 11 B6	  
		if ( fy < 6 )
		{
			fy = 6;							//CCCC: 3E 46	     
		}
		if ( fy >= 121 )					//CCD0: 38 02	     
		{
			fy = 121;						//CCD2: 3E B9	     
		}
	
		fy -= y;							//CCD4: 90		  
		if ( fy < 0 ) 
		{
			DrawVram2( y, x );				//CCD5: 38 27	     
			return;
		}
		if ( fy < 6 )						//CCD9: 30 03	     
		{
			y--;							//CCDB: 05		  
		}
		else
		if ( fy >= 19 )						//CCE0: 38 03	     
		{
			y++;							//CCE2: 04		  
		}
		else
		{
			break;
		}
	}

	while(1)
	{
		while(1)
		{
			if ( (g_infAttacker._stat02&(1<<7)) == 0 ) break; //CCEE: 28 07	     
			if ( g_infAttacker.x- x >= 16 ) 
			{
				DrawVram2( y, x );					//CCF2: 30 0A	     
				return;
			}
			x--;									//CCF4: 0D		  
		} 											//CCF5: 18 EE	     
		if ( g_infAttacker.x- x < 34 ) 
		{
			DrawVram2( y, x );						//CCF9: 38 03	     
			return;
		}
		x++;										//CCFB: 0C		  
	}												//CCFC: 18 E7	     


	return;											//CD18: C9		  
}
//-----------------------------------------------------------------------------
void func_CEA1_Initialize()
//-----------------------------------------------------------------------------
{
	func_RMCE06_ClearBuffer();					//CEA1: CD 06 CE	  
	func_RMCE2A_DecodeMap();					//CEA4: CD 2A CE	  
	func_RMCE4C_RefineMap();					//CEA7: CD 4C CE	  
	func_RMCD19_LocateWeapons();					//CEAA: CD 19 CD	  

	g_infCarrier.scrn_x		 	= 192;	//0xC0;
	g_infCarrier.scrn_y		 	= 5;	//0x45-64;
	g_infCarrier.x	 	= 248-16;	//0xF8;
	g_infCarrier.y	 	= 5;	//0x45-64;
	g_infCarrier._04	 	= 0x05;
	g_infCarrier._bcd1	 	= 0x00;
	g_infCarrier._bcd2	 	= 0x00;
	g_infCarrier._bcd3	 	= 0x00;
	g_infCarrier._cntTama08 	= 0x00;
	g_infCarrier._09		= 0x00;
	g_infCarrier._0A		= 0x00;
	g_infCarrier._0B		= 0x00;
	g_infCarrier._0C		= 0x00;
	g_infCarrier._0D		= 0x00;
	g_infCarrier._0E		= 0x00;
	g_infCarrier._0F		= 0x00;

	g_infAttacker.x			= 248;	//0xF8;
	g_infAttacker.y			= 5;	//0x45-64;
	g_infAttacker._stat02	= 0x00;
	g_infAttacker._chr03	= 0x00;
	g_infAttacker._stat04	= g_infAttacker.STAT_DOWN;
	g_infAttacker._HP05		= 0x20;
	g_infAttacker._flagsJoy06	= 0x00;
	g_infAttacker._chrSelfId07	= CHR_41_ATTACKER_MID;
	g_infAttacker._cntTama08	= 0x0A;
	g_infAttacker._09		= 0x07;
	g_infAttacker._0A		= 0x00;
	g_infAttacker._0B		= 0x00;
	g_infAttacker._0C		= 0x00;
	g_infAttacker._0D		= 0x00;
	g_infAttacker._0E		= 0x00;
	g_infAttacker._0F		= 0x00;

	g_dummy0.y = 0;
	g_dummy1.y = 0;

printf("1 car pos %d %d \n", g_infCarrier.x,g_infCarrier.y);
	func_RMC2CB_SetCarrierAttacker();						//CEB8: CD CB C2	  
	func_RMC55D_MoveEnemy();								//CEBB: CD 5D C5	  
	func_RMCCB9_DrawVram();									//CEBE: CD B9 CC	  

	unsigned int y = g_posA906.y;
	unsigned int x = g_posA906.x;

	g_scrn[y  ][x] = 0xCE;									//CEC6: ED 79	     
	g_scrn[y+1][x] = 0xCF;									//CECA: ED 79	     
	g_scrn[y+2][x] = 0xDE;									//CECF: ED 79	     


	for ( unsigned int i = 0 ; i < sizeof(g_CEE9_sound) ; i++ )
	{
		g_infPsgJoy._1C00_Reg = i;							//CEDA: ED 79		     !OUT     (C),A
		g_infPsgJoy._1B00_Data[0] = g_CEE9_sound[i];		//CEDD: ED 51		     !OUT     (C),D

	}

	return;													//CEE8: C9		  
}
//-----------------------------------------------------------------------------
void func_RMC6E8_MissileInput()									//			    
//-----------------------------------------------------------------------------
{
	unsigned int	num = 0;
	if ( g_infAttacker._HP05 == 0 ) return;				//C6F1: C8			  RET     Z
	if ( (g_infAttacker._stat04 & 0x7f) >= 2 ) return; 	//C6F9: D0			  RET     NC
	{
		unsigned int	i;
		for ( i= 0 ; i < 4 ; i++ )
		{
			if ( 0 == g_BA00_tblMissile[i].y )
			{
				num = i;
				break;
			}
		}
		if ( i >= 4 ) return;
	}

//	unsigned int a = sys.key.inkey().ascii;//func_RM001B_BASIC_IOCS_KEYINPUT();					//C711: CD 1B 00	  
	unsigned int y = g_infAttacker.y;
	unsigned int x = g_infAttacker.x;

	
	if ( sys.key.hi('7') ) x++;					//C718: FE 37		     CP	37h

	unsigned int dir = 0;
	unsigned int d = 0;
	if ( sys.key.hi('1') ) 
	{
printf ("missile-1\n");
		dir = 3;
		d = CHR_42_ATTACKER_DOWN;				//C72F: 14		  
	}
	else
	if ( sys.key.hi('4') ) 						//C727: 28 07	     
	{
printf ("missile-4\n");
		dir = 2;
		d = CHR_41_ATTACKER_MID;				//C731: 14		  
	}
	else
	if ( sys.key.hi('7') )						//C72B: 28 05	     
	{
printf ("missile-7\n");
		dir = 1;
		d = CHR_40_ATTACKER_UP;
	}
	else
	{
		return;									//C72D: C9		  
	}



	if ( g_infAttacker._stat04 != g_infAttacker.STAT_DOWN )
	{
		g_BA00_tblMissile[num].x = y;			//C739: FD 71 00	  
		g_BA00_tblMissile[num].y = x;			//C73C: FD 70 01	  
		g_BA00_tblMissile[num]._dir02 = dir;	//C73F: FD 73 02	  
		g_BA00_tblMissile[num]._mlim03 = 16;		//C742: FD 36 03 10     
		g_infAttacker._chrSelfId07 = d;			//C746: DD 72 07	  

		unsigned int y = g_infAttacker.y;				//C749: ED 4B 10 B6     
		unsigned int x = g_infAttacker.x;				//C749: ED 4B 10 B6     
		g_scrn[y][x  ] = d;						//C74D: ED 51	     
		g_scrn[y][x+1] = d + 0x10;				//C753: ED 79	     
		g_infAttacker._HP05--;					//C755: DD 35 05	  
		return;									//C758: C9		  
	}
	else
	{
		unsigned int y = g_infCarrier.y;					//C759: ED 4B 02 B6     
		unsigned int x = g_infCarrier.x;					//C759: ED 4B 02 B6     
		g_BA00_tblMissile[num].x = x;			//C75D: FD 71 00	  
		g_BA00_tblMissile[num].y = y; 			//C760: FD 70 01	  
		g_BA00_tblMissile[num]._dir02 = dir;	//C763: FD 73 02	  
		g_BA00_tblMissile[num]._mlim03 = 3;		//C766: FD 36 03 03     
		return;									//C76A: C9		  
	}
}
//-----------------------------------------------------------------------------
unsigned int		DAA( unsigned int val, bool* pFlg )
//-----------------------------------------------------------------------------
{
	if ( *pFlg )
	{
		val += 1;
		if ( val > 255 )
		{
			val &= 0xff;
		}
		else
		{
			*pFlg = false;
		}
	}

	return	val;

}

//-----------------------------------------------------------------------------
void func_RMCBCD_ChangeBCD( unsigned int a )									//			    
//-----------------------------------------------------------------------------
{
	bool	flgCarry = false;
	g_infCarrier._bcd1 = DAA( a + g_infCarrier._bcd1, &flgCarry  );					//CBD3: 77		  
	g_infCarrier._bcd2 = DAA( a + g_infCarrier._bcd2, &flgCarry  );					//CBD9: 77		  
	g_infCarrier._bcd3 = DAA( a + g_infCarrier._bcd3, &flgCarry  );					//CBDF: 77		  
	g_infCarrier._0F = 0x20;					//CBE3: 36 20	     
	return;										//CBE6: C9		  
}

//-----------------------------------------------------------------------------
char* func_RMC426_TCB( unsigned int a, char* ptr, unsigned int cnt, unsigned int size )									//			    
//-----------------------------------------------------------------------------
{

	for ( unsigned int i = 0 ; i < cnt ; i++ )
	{
		if ( a == ptr[0x01] ) return ptr;							//C429: C8		  
		ptr += size	;					//C42A: FD 19	     
	}
	
	return 0;
}

//-----------------------------------------------------------------------------
void func_RMC926_SetSmoke( unsigned int y, unsigned int x, unsigned int a, unsigned int cnt, unsigned int size )									//			    
//-----------------------------------------------------------------------------
{
	Smoke* pSmoke = (Smoke*)func_RMC426_TCB( 0, (char*)&g_BB00_tblSmoke, cnt, size );					//C929: CD 26 C4	  
	pSmoke->x = x;						//C92D: FD 71 00	  
	pSmoke->y = y;						//C930: FD 70 01	  
	pSmoke->_chr02 = a;					//C933: FD 77 02	  
	pSmoke->_lim03 = 32;					//C936: FD 36 03 20     
	return;								//C93A: C9		  
}


//-----------------------------------------------------------------------------
void func_RMCC58_Mine( Mine *pMine )									//			    
//-----------------------------------------------------------------------------
{
	if ( pMine->x != g_infAttacker.x ) return;		//CC5F: C0		  
	if ( pMine->y-2 != g_infAttacker.y ) return;	//CC67: C0		  

	g_infAttacker._chr03 = 0xF9;					//CC6C: FD 36 03 F9     
	g_infAttacker._09--;							//CC70: FD 35 09	  
	unsigned int x = pMine->x;								//CC73: DD 4E 00	  
	unsigned int y = pMine->y;								//CC76: DD 46 01	  

	pMine->y = 0;									//CC79: DD 36 01 00     
	unsigned int h = 0xFD;
	unsigned int l = 0xFE;									//CC7D: 21 FE FD	  
	g_scrn[y][x-1] = h;								//CC81: ED 61	     
	g_scrn[y][x  ] = '*';							//CC86: ED 79	     

	func_RMC926_SetSmoke( y, x, '*', 255, 4 );		//CC92: CD 26 C9	  

	g_scrn[y][x+1] = '&';							//CC98: ED 79	     
	func_RMC926_SetSmoke( y, x, '&', 255, 4 );		//CC9A: CD 26 C9	  

	g_scrn[y][x+2] = l;								//CC9F: ED 69	     

	func_RMC00D_MoveFighter( &g_infAttacker );		//CCAB: CD 0D C0	  
	func_RMCBCD_ChangeBCD( 0x00 ); 					//CCB4: CD CD CB	  
	return;											//CCB7: C9		  
}
//-----------------------------------------------------------------------------
void func_RMCC42_Mines()									//			    
//-----------------------------------------------------------------------------
{
	for ( unsigned int i = 0 ; i < 16 ; i++ )
	{
		if ( g_tblMine[i].y != 0 ) func_RMCC58_Mine( &g_tblMine[i] );					//CC4D: C4 58 CC	  
	}
}
//-----------------------------------------------------------------------------
void func_RMC6B8_UpdateSmoke()									//			    
//-----------------------------------------------------------------------------
{

	for ( unsigned int i = 0 ; i < 256 ; i++ )
	{
		unsigned int a = g_BB00_tblSmoke[i]._lim03;					//C6C1: DD 7E 03	  
		if ( a != 0 )										//C6C6: 28 1A	     
		{
			g_BB00_tblSmoke[i]._lim03--;						//C6C8: DD 35 03	  
			if ( g_BB00_tblSmoke[i]._lim03 == 0 )				//C6CB: 20 15	     
			{
				unsigned int y = g_BB00_tblSmoke[i].y;				//C6CD: DD 46 01	  
				unsigned int x = g_BB00_tblSmoke[i].x;			//C6D4: DD 4E 00	  

				g_BB00_tblSmoke[i].y = 0;					//C6D0: DD 36 01 00     

				if ( g_scrn[y][x] == g_BB00_tblSmoke[i]._chr02 )	//C6DC: 20 04	     
				{
					g_scrn[y][x] = 0;						//C6E0: ED 79	     
				}
			}
		}
	}

}
//-----------------------------------------------------------------------------
void func_RMC837_MissileSetLost( Missile *pMissile )
//-----------------------------------------------------------------------------
{
	unsigned int x = pMissile->x;								//C837: DD 4E 00		  LD	C,(IX+00h)
	unsigned int y = pMissile->y;								//C83A: DD 46 01		  LD	B,(IX+01h)

	unsigned int a = 0;
	if ( pMissile->_mlim03 != 0 ) 						//C842: 28 1F		     goto	Z,RMC863
	{
		unsigned int dir = pMissile->_dir02;						//C844: DD 7E 02		  dir = (IX+02h)
		if ( dir == 0x14 )								//C849: 20 04		     goto	NZ,RMC84F
		{
			a = 0x15;									//C84B: 3E 15		     dir = 15h
		}
		else
		if ( dir == 4 )									//C851: 20 04		     goto	NZ,RMC857
		{
			a = 0x14;									//C853: 3E 14		     dir = 14h
		}												//RMC857:
		else
		if ( dir < 0x10 )								//C859: 30 04		     goto	NC,RMC85F
		{
			a = dir + 0x23;								//C85B: C6 23		     dir = dir + 23h
		}												//			    RMC85F:
		else
		{
			a = dir + 0x17;								//C85F: C6 17		     dir = dir + 17h
		}
	}
	else
	{
		a = 0x27;										//C863: 3E 27		     a = 27h
	}

	if ( IS_LT_40_AIR( g_scrn[y][x] ) )					//C86A: 30 0A		     goto	NC,RMC876
	{
		if ( IS_GE_10_VISIBLE( g_scrn[y][x] ) )			//C86E: 38 06		     goto	C,RMC876
		{
			if ( (a & 0x0F) >= 4 )						//C874: 30 20		     goto	NC,RMC896
			{
				//	移動先が爆風の中
printf("<<<lost missile>>> 1\n");
				pMissile->y = 0;						//C896: DD 36 01 00	     LD	(IX+01h),00h
				return;									//C89B: C9			  RET
			}
		}
	}
	g_scrn[y][x] = a;									//C876: ED 59		     g_scrn[y][x] = E

	Smoke* pSmoke = (Smoke*)func_RMC426_TCB( 0, (char*)g_BB00_tblSmoke, 255, 4 );		//C885: CD 26 C4		  CALL    RMC426

	pSmoke->x = x;										//C889: FD 71 00		  LD	(IY+00h),C
	pSmoke->y = y;										//C88C: FD 70 01		  LD	(IY+01h),B
	pSmoke->_chr02 = a;									//C88F: FD 77 02		  LD	(IY+02h),a
	pSmoke->_lim03 = 0x10;								//C892: FD 36 03 10	     LD	(IY+03h),10h

printf("<<<lost missile>>> 2 a=0x%2X x=%d y=%d\n", a, x,y );
	pMissile->y = 0;									//C896: DD 36 01 00	     LD	(IX+01h),00h
}
//-----------------------------------------------------------------------------
void func_RMC93B_Missile( /*IX*/Missile* pMissile, /*IY*/Fighter* pFighter, unsigned int dir_x )									//			    
//-----------------------------------------------------------------------------
{
	unsigned int dir = pMissile->_dir02;								//C93B: DD 7E 02		  LD	A,(IX+02h)
	unsigned int e = 0;									//C93E: 1E 01		     LD	E,01h
	if ( (dir & (1<<3)) == 0 ) 			//C940: CB 5F		     BIT     3,A
	{
		if ( (dir >= 0x10 ) )						//C946: 30 02		     JR	NC,RMC94A
		{
			e = 1;	//上下方向の移動量
		}
		else
		{
			e = -1;
		}
	}

	pFighter->_stat02 = e;					//C94A: FD 73 02	  

	unsigned int	a = 0;

	if ( dir == 0x14 ) 
	{
		a = 0xFC;							//C95F: 3E FC	     
	}
	else
	if ( dir == 0x04 ) 
	{
		a = 4;									//C963: 3E 04                 LD      A,04h
	}
	else
	{
		a = dir &= 0x0F;							//C955: E6 0F	     
		a -= 0x02;							//C957: D6 02	     
		a *= 2;								//C959: CB 27	     
		a *= 2;								//C95B: CB 27	     
	}

	pFighter->_chr03 = a;						//C965: FD 77 03	  
	func_RMC00D_MoveFighter( /*IX*/pFighter );	//C970: CD 0D C0	  

	if ( dir_x != -1 ) 							//C979: 28 05		     JR	Z,RMC980
	{
		func_RMCBCD_ChangeBCD( 0x03 ) ;			//C97D: CD CD CB	  
	}

	func_RMC837_MissileSetLost( /*IX*/pMissile );

}
//-----------------------------------------------------------------------------
void func_RMC9C9( Missile* pMissile, unsigned int a )
//-----------------------------------------------------------------------------
{
	if ( a >= 0x80 ) return;								//C9CB: D2 8E CA		  JP	NC,RMCA8E
	if ( a < 0x69 ) return; 								//C9D0: DA 8E CA		  JP	C,RMCA8E
	g_infCarrier._0F = 0x20;								//C9D5: 32 0F B6		  LD	(RMB60F),A
	if ( a != 0x6a && a != 0x6b ) 							//C9DF: 28 0A		     JR	Z,RMC9EB
	{
		g_infAttacker._09--;								//C9EB: FD 35 19		  DEC     (IY+19h)
		func_RMC837_MissileSetLost( /*IX*/pMissile );	//C9EE: C3 37 C8		  JP	RMC837
		return;
	}
	g_infCarrier._04--;										//C9E5: FD 35 04		  DEC     (IY+04h)
	func_RMC837_MissileSetLost( /*IX*/pMissile );		//C9E8: C3 37 C8		  JP	RMC837
	return;

}
//-----------------------------------------------------------------------------
void func_RMC983( Missile* pMissile, unsigned int a, unsigned int y, unsigned int x )
//-----------------------------------------------------------------------------
{
	if ( (a & 0xF0) != 0x40 )					//C987: 28 09		     JR	Z,RMC992
	{
		if ( (a&0xF0) != 0x80 )					//C98B: 28 05		     JR	Z,RMC992
		{
			if ( (a&0xF0) != 0x90 )				//C990: 20 37		     JR	NZ,RMC9C9
			{
				func_RMC9C9( pMissile, a );
				return;
			}
		}
	}

	Missile*	pMissileIY = 0;
	{
		unsigned int cnt = 32;							//C996: 26 20		     LD	H,20h
		for ( unsigned int i ; i < 32 ; i++ )
		{
			if ( g_BA00_tblMissile[i].y == y 
			&&   g_BA00_tblMissile[i].x == x ) 
			{
				pMissileIY = &g_BA00_tblMissile[i];
				break;
			}
		}
	}
	if ( pMissileIY )
	{

printf("<<<lost missile>>> 3 \n");
		pMissile->y = 0;						//C9AF: DD 36 01 00	     LD	(IX+01h),00h
		pMissileIY->y = 0;						//C9B3: FD 36 01 00	     LD	(IY+01h),00h

		unsigned int a = 0x27;							//C9C0: 3E 27		     LD	A,27h
		g_scrn[y][x] = a;						//C9C2: ED 79		     !OUT     (C),A
		func_RMC926_SetSmoke( y, x, a, 255, 4 );	//C9C4: CD 26 C9		  CALL    RMC926
	}
}

//-----------------------------------------------------------------------------
void func_RMC5E3_DrawSmoke( unsigned int a, unsigned int y, unsigned int x )									//			    
//-----------------------------------------------------------------------------
{
	if ( g_scrn[y][x] >= '0' ) return;			//C5E8: D0		  
	g_scrn[y][x] = a;							//C5EA: ED 79	     
	Smoke* pSmoke = (Smoke*)func_RMC426_TCB( 0, (char*)&g_BB00_tblSmoke, 255, 4 );					//C5F8: CD 26 C4	  
	pSmoke->x = x;								//C5FC: FD 71 00	  
	pSmoke->y = y;								//C5FF: FD 70 01	  
	pSmoke->_chr02 = a;							//C602: FD 77 02	  
	pSmoke->_lim03 = 0x20;						//C605: FD 36 03 20     
	return;										//C609: C9		  
}

//-----------------------------------------------------------------------------
void func_RMC5A9_DrawSmokes( Missile *pMissile, unsigned int y, unsigned int x )									//			    
//-----------------------------------------------------------------------------
{
printf("<<<lost missile>>> 4\n");
	pMissile->y = 0;									//C5A9: DD 36 01 00     
	func_RMC5E3_DrawSmoke(0x2F,y,x);					//C5AF: CD E3 C5	  
	func_RMC5E3_DrawSmoke(0x2B,y-1,x);					//C5B5: CD E3 C5	  
	func_RMC5E3_DrawSmoke(0x26,y-1,x+1);				//C5BB: CD E3 C5	  
	func_RMC5E3_DrawSmoke(0x2D,y,x+1);					//C5C1: CD E3 C5	  
	func_RMC5E3_DrawSmoke(0x24,y+1,x+1);				//C5C7: CD E3 C5	  
	func_RMC5E3_DrawSmoke(0x2E,y+1,x);					//C5CD: CD E3 C5	  
	func_RMC5E3_DrawSmoke(0x28,y+1,x-1);				//C5D3: CD E3 C5	  
	func_RMC5E3_DrawSmoke(0x2C,y,x-1);					//C5D9: CD E3 C5	  
	func_RMC5E3_DrawSmoke(0x2A,y-1,x-1);				//C5DF: CD E3 C5	  
	return;												//C5E2: C9		  
}
//-----------------------------------------------------------------------------
void func_RMCA77( Missile *pMissile, unsigned int a, unsigned int y, unsigned int x )
//-----------------------------------------------------------------------------
{
	if ( a >= 0xd0 )									//CA79: 38 01		     JR	C,RMCA7C
	{
		x--;											//CA7B: 0D			  DEC     x
	}

	func_RMCBCD_ChangeBCD( 0x60 );						//CA7E: CD CD CB		  CALL    RMCBCD
	g_scrn[y][x  ] = 0;									//CA83: ED 51		     !OUT     (x),D
	g_scrn[y][x+1] = 0;									//CA86: ED 51		     !OUT     (x),D
	func_RMC5A9_DrawSmokes( /*IX*/pMissile, y, x );		//CA89: CD A9 C5		  CALL    RMC5A9

}
//-----------------------------------------------------------------------------
void func_RMCA56( Missile* pMissile, Sight* pSight, unsigned int y, unsigned int x )			//			    RMCA56:
//-----------------------------------------------------------------------------
{
	func_RMCBCD_ChangeBCD( 0x03 );						//CA58: CD CD CB		  CALL    RMCBCD
	pSight->_lim03--;										//CA5B: FD 35 03		  DEC     (IY+03h)
	if ( pSight->_lim03 != 0 ) 							//CA5E: C2 37 C8		  JP	NZ,RMC837
	{
		func_RMC837_MissileSetLost( /*IX*/pMissile );
	}

	pSight->y = 0;										//CA61: FD 36 01 00	     LD	(IY+01h),00h
	g_scrn[y][x  ] = 0;									//CA67: ED 51		     !OUT     (C),D
	g_scrn[y][x+1] = 0;									//CA6A: ED 51		     !OUT     (C),D
	func_RMC5A9_DrawSmokes( /*IX*/pMissile, y, x );		//CA6D: CD A9 C5		  CALL    RMC5A9
	func_RMCBCD_ChangeBCD( 0x47 );						//CA73: CD CD CB		  CALL    RMCBCD
}
//-----------------------------------------------------------------------------
void	func_RMCA34( Missile* pMissile, unsigned int a, unsigned int y, unsigned int x )
//-----------------------------------------------------------------------------
{
	if ( a >= 0xd0 )									//CA36: 38 01		     JR	C,RMCA39
	{
		x--;											//CA38: 0D			  DEC     C
	}

	Sight*	pSightA_IY = 0;
	unsigned int	cnt = 32;										//CA40: 26 20		     LD	H,20h
	for ( unsigned int i = 0 ; i < cnt ; i++ )
	{
		if ( g_BF00_tblSightA[i].y == y 
		&& g_BF00_tblSightA[i].x == x )
		{
			pSightA_IY = &g_BF00_tblSightA[i];
			break;
		}
	}
	
	if ( pSightA_IY )	func_RMCA56( pMissile, pSightA_IY, y, x );
}
//-----------------------------------------------------------------------------
void func_RMCA1B( Missile* pMissile )
//-----------------------------------------------------------------------------
{
	unsigned int x = 0xAA;
	unsigned int y = 0x06;										//CA1B: 01 06 AA		  LD	BC,AA06h
	g_scrn[y-1][x] = 0;									//CA21: ED 79		     g_scrn[y][x] = a
	g_scrn[y  ][x] = 0;									//CA24: ED 79		     g_scrn[y][x] = a
	g_scrn[y+1][x] = 0;									//CA27: ED 79		     g_scrn[y][x] = a
	func_RMC5A9_DrawSmokes( /*IX*/pMissile, y, x );		//CA2A: CD A9 C5		  CALL    RMC5A9
	func_RMCBCD_ChangeBCD( 0x70 );						//CA30: CD CD CB		  CALL    RMCBCD
}
//-----------------------------------------------------------------------------
void func_RMC9F1( Missile* pMissile, unsigned int a, unsigned int y, unsigned int x, unsigned int dir_x )				//			    RMC9F1:
//-----------------------------------------------------------------------------
{
	if ( a >= 0xe0 ) return;							//C9F3: D2 8E CA		  JP	NC,RMCA8E

	if ( dir_x == 1 ) 										//C9FA: CA 37 C8		  JP	Z,RMC837
	{
		func_RMC837_MissileSetLost( /*IX*/pMissile );
		return;
	}

	if ( a != 0xdf )									//CA00: 28 10		     JR	Z,RMCA12
	{
		if ( (a & 0x0f) >= 0x0e ) 
		{
			func_RMCA1B( /*IX*/pMissile );				//CA07: 30 12		     JR	NC,RMCA1B
			return;
		}

		if ( (a&0x0f) == 0x0d ) 
		{
			func_RMCA77( pMissile, a, y, x );			//CA0E: 28 67		     JR	Z,RMCA77
			return;
		}
		func_RMCA34( pMissile, a, y, x );				//CA10: 18 22		     JR	RMCA34
		return;
	}

	func_RMC837_MissileSetLost( /*IX*/pMissile );	//CA18: C3 37 C8		  JP	RMC837
	return;

}

//-----------------------------------------------------------------------------
void func_RMC831_CollitionMissile( Missile *pMissile, unsigned int y, unsigned int x, unsigned int dir_x )									//			    
//-----------------------------------------------------------------------------
{
	unsigned int a = g_scrn[y][x];								//C831: ED 78		     a = g_scrn[y][x]

	if ( IS_GE_F0_TELLAIN(a) )							//C835: 38 65		     JR	C,RMC89C
	{
		func_RMC837_MissileSetLost( /*IX*/pMissile );
		return;
	}
	else
	{
		if ( IS_LT_40_AIR(a) ) return;							//C89E: DA 8E CA		  JR	C,RMCA8E
		if ( IS_GE_C0_GROUND(a) ) 
		{
			func_RMC9F1( /*IX*/pMissile, a, y, x, dir_x );	//C8A3: D2 F1 C9		  JP	NC,RMC9F1
			return;
		}
		if ( (a ^ dir_x) >= 0x80 ) return;					//C8AB: D0			  RET     NC
		if ( (a & 0x0f) >= 9 ) 
		{
			func_RMC983( /*IX*/pMissile, a, y, x );		//C8B1: D2 83 C9		  JP	NC,RMC983
			return;
		}
		g_infCarrier._0F = 0x20;						//C8B6: 32 0F B6		  LD	(RMB60F),a
		if ( (a & 0x1f) >= 0x10 ) 						//C8BE: 38 01		     JR	C,RMC8C1
		{
			x--;										//C8C0: 0D			  x--;
		}												//			    RMC8C1:
		if ( (a & 0x0f) >= 0x03 ) 						//C8C5: 38 01		     JR	C,RMC8C8
		{
			y--;										//C8C7: 05			  DEC     y
		}

		{
			Fighter*	pFighter = &g_infAttacker;		//C8C8: FD 21 10 B6	     LD	IY,B610h
			unsigned int		cnt = 63;							//C8CF: 26 3F		     LD	H,3Fh

			unsigned int	i;
			for ( i = 0 ; i < cnt ; i++ )
			{
				if ( pFighter[i].y == y ) break;
			}

			pFighter[i]._09--; 							//C8E7: FD 35 09		  DEC     (IY+09h)
			if ( pFighter[i]._09 >= 0 ) 
			{
				func_RMC93B_Missile( /*IX*/pMissile, /*IY*/pFighter, dir_x );			//C8EA: 20 4F		     JR	NZ,RMC93B
				return;
			}
			pFighter[i].y = 0;							//C8EC: FD 36 01 00	     LD	(IY+01h),00h
printf("<<<lost missile>>> 5\n");
			pMissile->y = 0;							//C8F0: DD 36 01 00	     LD	(IX+01h),00h
		}

//		LD	IY,g_BB00_tblSmoke						//C8F4: FD 21 00 BB	     LD	IY,BB00h
		a = 0x2a;
		g_scrn[y  ][x  ] = a;						//C8FF: ED 79		     g_scrn[y][x] = a
		func_RMC926_SetSmoke( y, x, a, 255, 4 );	//C901: CD 26 C9		  CALL    RMC926

		a = 0x26;
		g_scrn[y  ][x+1] = a;						//C907: ED 79		     g_scrn[y][x] = a
		func_RMC926_SetSmoke( y, x, a, 255, 4 );	//C909: CD 26 C9		  CALL    RMC926

		a = 0x24;
		g_scrn[y+1][x  ] = a;						//C90F: ED 79		     g_scrn[y][x] = a
		func_RMC926_SetSmoke( y, x, a, 255, 4 );	//C911: CD 26 C9		  CALL    RMC926

		a = 0x28;
		g_scrn[y+1][x] = a;							//C917: ED 79		     g_scrn[y][x] = a
		func_RMC926_SetSmoke( y, x, a, 255, 4 );	//C919: CD 26 C9		  CALL    RMC926

		if ( dir_x == -1 )								//C91F: 28 05		     JR	Z,RMC926
		{
			func_RMC926_SetSmoke( y, x, a, 255, 4 );
			return;
		}
		func_RMCBCD_ChangeBCD( 0x30 );				//C923: CD CD CB		  CALL    RMCBCD

		func_RMC926_SetSmoke( y, x, a, 255, 4 );
	}
}
//-----------------------------------------------------------------------------
void func_C7EC_MissileMove( Missile* pMissile, unsigned int y, unsigned int x, unsigned int dir_x )
//-----------------------------------------------------------------------------
{
	pMissile->_mlim03--;					//C7EC: DD 35 03	  
	if ( pMissile->_mlim03 == 0 ) 
	{
		func_RMC837_MissileSetLost( /*IX*/pMissile );					//C7EF: CC 37 C8	  
	}

	unsigned int dir = pMissile->_dir02;						//C7F2: DD 7E 02		  LD	A,(IX+02h)

	if ( dir == 0x14 ) 
	{
		//	ミサイル移動　上
		y--;										//C7F9: 05			  DEC     B
	}
	else
	if ( dir == 0x04 )
	{
		//	ミサイル移動　下
		y++;									//C800: 04			  INC     B
	}
	else
	{
		if ( dir >= 0x10 )
		{
			//	ミサイル移動　右方向
			x++;								//C807: 0C			  INC     C
			x++;								//C808: 0C			  INC     C
		}
		x--;									//C809: 0D			  DEC     C
		//	ミサイル移動　斜上・中・斜下
		y += (dir & 0x0f) - 2;					//C80E: 80			  ADD     B
	}

	unsigned int a = g_scrn[y][x];							//C810: ED 78	     

	if ( a < 0x10 ) goto RMC81D;								//C814: 38 07	     

	if ( a < 0x30 ) goto RMC829;								//C818: 38 0F	     

	func_RMC831_CollitionMissile( pMissile, y, x, dir_x );			//C81A: D4 31 C8	  

RMC81D:

	g_scrn[y][x] = CHR_DIR_2_MISSILE( dir, dir_x );							//C827: ED 79	     

RMC829:
	pMissile->x = x;								//C829: DD 71 00	  
	pMissile->y = y;								//C82C: DD 70 01	  
	return;		
}
//-----------------------------------------------------------------------------
void func_RMC7A4_Missile( Missile* pMissile, unsigned int dir_x )									//			    
//-----------------------------------------------------------------------------
{
	unsigned int x = pMissile->x;							//C7A4: DD 4E 00	  
	unsigned int y = pMissile->y;							//C7A7: DD 46 01	  
	unsigned int a = g_scrn[y][x];							//C7AA: ED 78	     


	if ( IS_GE_10_VISIBLE(a) ) 						//C7AE: 38 07		     JR	C,RMC7B7
	{
		if ( IS_LT_30_UNPHISICAL(a) ) 
		{
			func_C7EC_MissileMove( pMissile, y, x, dir_x );	//C7B2: 38 38		     JR	C,RMC7EC	
			return;
		}
		func_RMC831_CollitionMissile( pMissile, y, x, dir_x );					//C7B4: D4 31 C8	  
	}

	{
		//	軌跡
		unsigned int dir = pMissile->_dir02;
		if ( (dir&(1<<2)) != 0 )
		{
			//垂直
			a = 0x11;
		}
		else
		{														//C7C3
			if ( dir < 0x10 )
			{
				a = 0x14 -dir;
			} 											//C7CB
			a += 0x20;
		}
	}

	g_scrn[y][x] = a;						//C7CD: ED 79	     

	Smoke*	pSmokeIY = 0;
	{
		for ( unsigned int i = 0 ; i < 255 ; i++ )
		{
			if ( g_BB00_tblSmoke[i].y == 0 )
			{
				pSmokeIY = &g_BB00_tblSmoke[i];
				break;
			}
		}
		// IY
		if ( pSmokeIY )
		{
			pSmokeIY->x = x;						//C7DF: FD 71 00	  
			pSmokeIY->y = y;						//C7E2: FD 70 01	  
			pSmokeIY->_chr02 = a;					//C7E5: FD 77 02	  
			pSmokeIY->_lim03 = 8;					//C7E8: FD 36 03 08     
		}
	}	

	func_C7EC_MissileMove( pMissile, y, x, dir_x );

}
//-----------------------------------------------------------------------------
void func_RMC76B_UpdateMisile()									//			    
//-----------------------------------------------------------------------------
{
	for ( unsigned int i = 0 ; i < 12 ; i++ )
	{
		if ( g_BA00_tblMissile[i].y != 0 )				//C777: 28 05	     
		{
			func_RMC7A4_Missile( &g_BA00_tblMissile[i], 0xFF );					//C77B: CD A4 C7	  
		}
	}

	for ( unsigned int i = 12 ; i < 32 ; i++ )
	{
		if ( g_BA00_tblMissile[i].y != 0 )				//C791: 28 05	     
		{
			func_RMC7A4_Missile( &g_BA00_tblMissile[i], 0x01 );					//C795: CD A4 C7	  
//printf("m %d\n", i );
		}
	}

}
//-----------------------------------------------------------------------------
void func_RMCAC7_Score1( unsigned int y, unsigned int x, unsigned int a )									//			    
//-----------------------------------------------------------------------------
{
	unsigned int d = 0xFF;						//CAC7: 16 FF	     
	unsigned int	e = 8;
	
	for ( unsigned int i = 0 ; i < 8 ; i++ )
	{
		a -= 4;
		if ( a < 0 ) 
		{
			d = 0xfc;

			while(1)
			{
				a++;
				if ( a == 0 ) break;
				d *= 4;
			}
			g_scrn[y][x] = d;
			d = 0;
			
			while(1)
			{
				x++;
				if ( x >= 256 )
				{
					x = 0;
					y++;
				}
				e--;
				if ( e == 0 ) return;
				g_scrn[y][x] = d;
			}
		}
		else
		{
			g_scrn[y][x] = d;
			x++;
			if ( x > 255 ) 
			{
				x = 0;
				y++;
			}
		}
	}
	return;
}	
//-----------------------------------------------------------------------------
void func_RMCAC7_Score2( unsigned int y, unsigned int x, unsigned int a )									//			    
//-----------------------------------------------------------------------------
{
	unsigned char g_CB22_DATA[8] = { 0x00, 0x3e, 0x22, 0x44, 0x44, 0x88, 0xf8, 0x00 };


	for ( unsigned int i = 0 ; i < 8 ; i++ )
	{
		g_scrn[y+8*i][x] = g_CB22_DATA[a*8+i];						//CAFF: ED 79	     
	}
	return;								//CB0C: C9		  
}

//-----------------------------------------------------------------------------
void func_RMCAC7_Score3( unsigned int y, unsigned int x, unsigned int a )									//			    
//-----------------------------------------------------------------------------
{
	func_RMCAC7_Score2( y, x  , a/16 );					//CB16: CD EC CA	  
	func_RMCAC7_Score2( y, x+1, a%16 );					//CB1D: CD EC CA	  
	return;								//CB21: C9		  
}
//-----------------------------------------------------------------------------
void func_RMCA90_ScoreUpdate()									//			    
//-----------------------------------------------------------------------------
{
	func_RMCAC7_Score1( 0xD1, 0xAE, g_infAttacker._cntTama08*2);					//CA98: CD C7 CA	  
	func_RMCAC7_Score1( 0xD1, 0xFE, g_infAttacker._HP05 );					//CAA1: CD C7 CA	  
	func_RMCAC7_Score2( 0xC2, 0x4E, g_infAttacker._09 );					//CAAA: CD EC CA	  
	func_RMCAC7_Score2( 0xC2, 0x9E, g_infCarrier._04 );					//CAB3: CD EC CA	  


	for ( unsigned int i = 0 ; i < 3 ; i++ )
	{
		if ( i == 0 ) func_RMCAC7_Score3( 0xC2, 0xEE + i*2, g_infCarrier._bcd3 );					//CABF: CD 0D CB	  
		if ( i == 1 ) func_RMCAC7_Score3( 0xC2, 0xEE + i*2, g_infCarrier._bcd2 );					//CABF: CD 0D CB	  
		if ( i == 2 ) func_RMCAC7_Score3( 0xC2, 0xEE + i*2, g_infCarrier._bcd1 );					//CABF: CD 0D CB	  
	}

	return;								//CAC6: C9		  
}

//-----------------------------------------------------------------------------
void func_RMCB72_Sound()									//			    
//-----------------------------------------------------------------------------
{
	{
		unsigned int a = g_infAttacker._cntTama08;			//CB75: 3A 18 B6	  
		a += 36;						//CB78: C6 24	     
		if ( a >= 47 )			//CB7C: 38 02	     
		{
			a = 46;						//CB7E: 3E 2E	     
		}
		g_infPsgJoy._1C00_Reg = 0x0B;						//CB82: ED 59	     
		g_infPsgJoy._1B00_Data[0] = a;						//CB85: ED 79	     

		a = g_infCarrier._0F;				//CB88: 3A 0F B6	  
		if ( a != 0x00 )			//CB8D: 28 01	     
		{
			a--;							//CB8F: 3D		  
		}
		g_infCarrier._0F = a;				//CB90: 32 0F B6	  

		if ( a > 0x20 )
		{
			a = 0x1F;						//CB97: 3E 1F	     
		}
		g_infPsgJoy._1C00_Reg = 0x09;						//CB9B: ED 59	     
		g_infPsgJoy._1B00_Data[0] = a/2;						//CBA0: ED 79	     
	}

	{
		unsigned int	a = 0;			//CBA3: 16 00		     LD	D,00h
		for ( unsigned int i = 0 ; i < 4 ; i++ )
		{
			if ( g_BA00_tblMissile[i].y != 0 )			//CBB0: 28 07		     JR	Z,RMCBB9
			{
				if ( g_BA00_tblMissile[i]._mlim03 >= a )	//CBB6: 38 01		     JR	C,RMCBB9
				{
					a = g_BA00_tblMissile[i]._mlim03;			//CBB8: 57			  LD	D,A
				}
			}
		}
		g_infPsgJoy._1C00_Reg = 0x0a;			//CBC7: ED 59		     !OUT     (C),E
		g_infPsgJoy._1B00_Data[0] = a;			//CBCA: ED 79		     !OUT     (C),A
	}
}
//-----------------------------------------------------------------------------
void func_RMCF38_DrawBomb()									//			    
//-----------------------------------------------------------------------------
{
/*
	{
		char* pDE = 0x0000					//CF38: 11 00 00	  
		char* pHL = 0x0000					//CF3B: 21 00 00	  
		LDIR								//CF41: ED B0	     
		for ( unsigned int i = 0 ; i < 0x1000 ; i++ )
		{
			pDE[i] = pHL[i];
		}
	}
*/

	unsigned int y = g_posA906.y;
	unsigned int x = g_posA906.x;
	if ( g_scrn[y][x] != 0 ) 					//CF4A: 28 4F	     
	{
		if ( g_infAttacker._09-1 >= 0x80 ) 
		{
			y = g_infAttacker.y;			//CF84: ED 4B 10 B6     
			x = g_infAttacker.x;			//CF84: ED 4B 10 B6     
			//	アッタッカー爆発パターン
			g_scrn[y  ][x  ] = '*';						//CF8A: ED 79	     
			g_scrn[y  ][x+1] = '&';						//CF8F: ED 79	     
			g_scrn[y+1][x+1] = '$';						//CF94: ED 79	     
			g_scrn[y+1][x  ] = '(';  		//CF99: ED 79 		    
		}
		else
		if ( g_infCarrier._04-1 >= 0x80 )							//CF5A: D8			  RET     C
		{
			y = g_infCarrier.y;				//CF5B: ED 4B 02 B6     
			x = g_infCarrier.x;				//CF5B: ED 4B 02 B6     
			//	キャリアー爆発パターン
			g_scrn[y  ][x  ] = '*';						//CF61: ED 79	     
			g_scrn[y  ][x+1] = '+';						//CF66: ED 79	     
			g_scrn[y  ][x+2] = '+';						//CF69: ED 79	     
			g_scrn[y  ][x+3] = '&';						//CF6E: ED 79	     
			g_scrn[y+1][x+3] = '$';						//CF73: ED 79	     
			g_scrn[y+1][x+2] = '.';						//CF78: ED 79	     
			g_scrn[y+1][x+1] = '.';						//CF7B: ED 79	     
			g_scrn[y+1][x  ] = '(';						//CF80: ED 79	     

		}
		return;
	}

	g_infPsgJoy._1C00_Reg	 	= 0x07;
	g_infPsgJoy._1B00_Data[0]	 = 0x2F;
	g_infPsgJoy._1C00_Reg	 	= 0x09;
	g_infPsgJoy._1B00_Data[0]	 = 0x31;
	g_infPsgJoy._1C00_Reg	 	= 0x0c;
	g_infPsgJoy._1B00_Data[0]	 = 0x80;
	g_infPsgJoy._1C00_Reg	 	= 0x0d;
	g_infPsgJoy._1B00_Data[0]	 = 0x03;

	func_RMCBCD_ChangeBCD( 0x00 ); 					//CFC3: CD CD CB	  
	func_RMCCB9_DrawVram();					//CFC6: CD B9 CC	  
	func_RMCA90_ScoreUpdate();					//CFC9: CD 90 CA	  
	return;								//CFCD: C9		  
}

//-----------------------------------------------------------------------------
void func_RMCC02_Sight( Sight *pSight )									//			    
//-----------------------------------------------------------------------------
{
	unsigned int x = pSight->x;				//CC02: DD 4E 00	  
	unsigned int y = pSight->y;				//CC05: DD 46 01	  

	pSight->_sgt02--;					//CC0B: DD 35 02	  
	if ( (0x07 & pSight->_sgt02) == 0 ) 					//CC13: 20 05	     
	{
		pSight->_sgt02 = rand()&0xff;				//CC17: DD 77 02	  
	}
	if ( (pSight->_sgt02&(1<<3)) != 0 )				//CC1F: 28 02	     
	{
		y--;							//CC21: 05		  
		y--;							//CC22: 05		  
	}
	if ( g_scrn[y+1][x  ] != 0 ) return;						//CC26: C0		  
	if ( g_scrn[y+1][x+1] != 0 ) return;						//CC2A: C0		  
	pSight->y = y+1;				//CC2C: DD 70 01	  
	g_scrn[y+1][x  ] = 0xC3;					//CC32: ED 61	     
	g_scrn[y+1][x+1] = 0xd3;						//CC35: ED 69	     

	g_scrn[y  ][x  ] = 0;						//CC3C: ED 79	     
	g_scrn[y  ][x+1] = 0;						//CC3F: ED 79	     
	return;								//CC41: C9		  
}

//-----------------------------------------------------------------------------
void func_RMCBE8_UpdateSight()									//			    
//-----------------------------------------------------------------------------
{
	for ( unsigned int i = 28 ; i < 32 ; i++ )
	{
		if ( g_BF00_tblSightA[i].y != 0 ) func_RMCC02_Sight( /*IX*/&g_BF00_tblSightA[i] );					//CBF3: C4 02 CC	  
	}

}

//-----------------------------------------------------------------------------
void	func_RMC4E5_think2( Fighter* pEnemy, unsigned int hx, unsigned int hy, unsigned int dy, unsigned int dx )									//			    
//-----------------------------------------------------------------------------
{
	unsigned int  x = pEnemy->x;
	unsigned int  y = pEnemy->y;

	if ( dx >= 0x80 ) return;						//C4E8: D0		  
	if ( rand()&0xDE ) 				//C4ED: 20 0E	     
	{
		if ( (rand()&0x3E) != 0 ) return;						//C501: C0		  
		hx = 0x00;						//C502: 2E 00	     
	}
	else
	{
		if ( dy >= 0x80 ) 
		{
			hx = 0x01;						//C4F8: 2E 01	     
			x++;							//C4FA: 0C		  
		}
		else
		{
			hx = 0xFF;						//C4F4: 2E FF	     
		}
	}

	if ( pEnemy->_stat04 >= 0x02 ) return;						//C509: D0		  

	Sight* pSightB = (Sight*)func_RMC426_TCB(  0, (char*)g_BA30_tblSightB, 20, 4 );					//C515: CD 26 C4	  
	if ( pSightB == 0 ) return;							//C519: C8		  

	pEnemy->_chrSelfId07 = (pEnemy->_chrSelfId07 & 0xF0) + hx + 1;				//C521: DD 77 07	  
	pSightB->x = x;							//C524: FD 71 00	  
	pSightB->y = y;							//C527: FD 70 01	  
	pSightB->_sgt02 = hx+0x12;				//C52E: FD 77 02		  LD	(IY+02h),A
	pSightB->_lim03 = 0x10;					//C532: FD 36 03 10     
	hx--;									//C536: 2D		  

	if ( hx == 0 )
	{
		x--;							//C539: 0D		  
	
	}
	g_scrn[y][x  ] = pEnemy->_chrSelfId07;						//C53A: ED 79	     
	g_scrn[y][x+1] = pEnemy->_chrSelfId07+1;						//C53E: ED 79	     
	return;
}

//-----------------------------------------------------------------------------
void	func_RMC4D1_think1( Fighter* pEnemy, unsigned int dy, unsigned int dx )									//			    
//-----------------------------------------------------------------------------
{
	pEnemy->_cntTama08++;					//C4D1: DD 34 08	  
	if ( (pEnemy->_cntTama08 & 0x04 ) == 0 ) 
	{
		pEnemy->_flagsJoy06 = 0xFA;				//C4E1: DD 36 06 FA     
	}
	else
	{
		pEnemy->_flagsJoy06 = 0xFF;				//C4DB: DD 36 06 FF     
	}

}
//-----------------------------------------------------------------------------
void	func_RMC476_ThinkA0( Fighter* pEnemy, unsigned int hy, unsigned int hx )
//-----------------------------------------------------------------------------
{
	unsigned int y = pEnemy->y;				//C476: DD 46 01	  
	unsigned int x = pEnemy->x;				//C479: DD 4E 00	  
	unsigned int dx = hx - x;							//C47E: 57		  
	unsigned int dy = 0x00;						//C47F: 1E 00	     
	if ( dx < 0 ) 					//C481: 38 4E		     JR	C,RMC4D1
	{
			func_RMC4D1_think1( pEnemy, dy, dx );
			func_RMC4E5_think2( pEnemy, hx, hy, dy, dx );
			return;
	}
	dy = y - hy;						//C485: 5F		  
	if ( dy >= 0 )			//C486: 38 05		     JR	C,RMC48D
	{
		if ( dy >= dx ) 
		{
			func_RMC4D1_think1( pEnemy, dy, dx );		//C489: 30 46	     
			func_RMC4E5_think2( pEnemy, hx, hy, dy, dx );
			return;
		}
	}
	else
	{
		dy = -dy;								//C48D: ED 44	     
		if ( dy >= dx ) 
		{
			func_RMC4D1_think1( pEnemy, dy,  dx );				//C490: 30 3F	     
			func_RMC4E5_think2( pEnemy, hx, hy, dy, dx );
			return;
		}
	}

	pEnemy->_cntTama08++;							//C492: DD 34 08	  
	if ( (pEnemy->_cntTama08 & 0x3 ) != 0 ) 
	{
			func_RMC4E5_think2( pEnemy, hx, hy, dy, dx );
			return;
	}

	pEnemy->_cntTama08 = (rand()&0x03)+1;				//C4A9: DD 77 08	  

	unsigned int a = rand();								//C4AC: ED 5F		     LD	A,R
	if ( (a & (1<<1)) == 0 )					//C4B0: 28 0C		     JR	Z,RMC4BE
	{
		a = 0xF7;								//C4BE: 3E F7		     LD	A,F7h
	}
	else
	if ( (a & (1<<2)) == 0  )				//C4B4: 28 04		     JR	Z,RMC4BA
	{
		a = 0xFF;							//C4BA: 3E FF		     LD	A,FFh
	}
	else
	{	
		a = 0xfb;							//C4B6: 3E FB		     LD	A,FBh
	}

	if ( (rand() & (1<<3)) != 0 )			//C4C5: 28 04		     JR	Z,RMC4CB
	{
		a &= 0xFE;							//C4C8: E6 FE		     AND     FEh
	}
	pEnemy->_flagsJoy06 = a;					//C4CC: DD 77 06		  LD	(IX+06h),A

	func_RMC4E5_think2( pEnemy, hx, hy, dy, dx );	//C4CF: 18 14		     JR	RMC4E5
}

//-----------------------------------------------------------------------------
void func_RMC430_EnemyThink( Fighter *pEnemy )
//-----------------------------------------------------------------------------
{
	unsigned int	hx = 0;
	unsigned int	hy = 0;
	unsigned int a = g_infAttacker.x;			//C430: 3A 10 B6	  
	a -= 0x28;						//C433: D6 28	     
	if ( a < 0 )					//C435: 30 02	     
	{
		a = 0x00;						//C437: 3E 00	     
	}
	if ( a >= pEnemy->_0A )				//C43C: 38 30		     JR	C,RMC46E
	{
		unsigned int a = g_infCarrier.x - 0x28;				//C43E: 3A 02 B6	  
		if ( a < 0 )					//C443: 30 02		     JR	NC,RMC447
		{
			a = 0;						//C445: 3E 00	     
		}
		if ( a < pEnemy->_0A ) 			//C44A: 38 27		     JR	C,RMC473
		{
			hy = g_infCarrier.y;		//C473: 2A 02 B6	  
			hx = g_infCarrier.x;		//C473: 2A 02 B6	  
		}
		else
		{
			a = pEnemy->_0A;						//C44C: DD 7E 0A	  
			a -= pEnemy->x;							//C44F: DD 96 00	  
			if ( a < 0 ) 
			{
				a = 0xFB;							//C45B: 16 FB	     
			}
			else
			{
				if ( a < 0x14 ) return;				//C456: D8		  
				a = 0xF7;							//C457: 16 F7	     
			}
			if ( (pEnemy->_cntTama08&0x04) != 0 )	//C463: 28 02	     
			{
				a &= 0xFE;							//C465: E6 FE	     
			}
			pEnemy->_flagsJoy06 = a;				//C467: DD 77 06	  
			pEnemy->_cntTama08++;					//C46A: DD 34 08	  
			return;									//C46D: C9		  
		}
	}
	else
	{
		hx = g_infAttacker.x;			//C46E: 2A 10 B6	  
		hy = g_infAttacker.y;			//C46E: 2A 10 B6	  
	}
	func_RMC476_ThinkA0( pEnemy, hy, hx );
}


//-----------------------------------------------------------------------------
void func_RMC57A_UpdateRedEnemy()									//			    
//-----------------------------------------------------------------------------
{
	for ( unsigned int i = 0 ; i < 8 ; i++ )
	{
		unsigned int a = 0;							//C583: 3A 15 B6	  
		if ( g_infAttacker._HP05 >= 10 )
		{
			a = g_tblEnemy[i]._0A;			//C58F: DD 7E 0A		  LD	A,(IX+0Ah)
			if ( a != g_tblEnemy[i]._0B )	//C595: 28 01 
			{
				a--;
			}
		}
		else
		{
			a = g_infAttacker.x;			//C58A: 3A 10 B6		  LD	A,(RMB610)
		}

		g_tblEnemy[i]._0A = a;				//C598: DD 77 0A	   LD	(IX+0Ah),A
		func_RMC430_EnemyThink( /*IX*/&g_tblEnemy[i] );					//C59E: CD 30 C4	  
	}

}
//-----------------------------------------------------------------------------
void func_RMC541_UpdateGreenEnemy()									//			    
//-----------------------------------------------------------------------------
{
	for ( unsigned int i = 0 ; i < 60 ; i++ )
	{
		if ( g_tblEnemy[i].y )
		{
			func_RMC430_EnemyThink( /*IX*/&g_tblEnemy[i] );					//C553: CD 30 C4	  
		}
	}

}

//-----------------------------------------------------------------------------
void func_RMC626_Sight( Sight* pSight )									//			    
//-----------------------------------------------------------------------------
{
	if ( ( rand() & 0xd1 ) != 0 ) return;						//C62A: C0		  

	Sight* pSightB = (Sight*)func_RMC426_TCB( 0, (char*)&g_BA30_tblSightB, 20, 4 );					//C636: CD 26 C4	  
	if ( pSightB == 0 ) return;							//C63A: C8		  
	unsigned int x = pSight->x;				//C63B: DD 4E 00	  
	unsigned int y = pSight->y;				//C63E: DD 46 01	  
	unsigned int dx = g_infAttacker.x - x;						//C645: 5F		  
	unsigned int dy = g_infAttacker.y - y;						//C64A: 57		  

	unsigned int	r = 0;
	if ( dy >= 0x80 )					//C64D: 38 02	     
	{
		r = -dy;							//C64F: ED 44	     
	}
	else
	{
		r = dy;
	}
	x++;							//C652: 0C		  
	if ( dx >= 0x80 )
	{
		x--;							//C65A: 0D		  
		r = -dx -r;
	}
	else
	{
		r = dx -r;						//C65C: 67		  
	}
	
	unsigned int	sgt = 0;
	if ( (rand() & 0x08) != 0 ) 				//C661: 28 23	     
	{
		if ( r < 0x80 ) 						//C666: 30 0F	     
		{
			if ( dx < 0x80 )			//C66B: 30 05	     
			{
				sgt = 0x12;						//C66D: 2E 12	     
				x++;							//C66F: 0C		  
			
			}
			sgt = 0x02;						//C672: 2E 02	     
			x--;							//C674: 0D		  

		}
		if ( dy < 0x80 )			//C67A: 30 05	     
		{
			sgt = 0x04;						//C67C: 2E 04	     
			y++;							//C67E: 04		  
		
		}
		sgt = 0x14;						//C681: 2E 14	     
		y--;							//C683: 05		  
	}
	else
	{

		if ( dy >= 0x80 ) 
		{
			y--;							//C690: 05		  
			sgt = 0x01;						//C691: 2E 01	     
		}
		else
		{
			y++;							//C68B: 04		  
			sgt = 0x03;						//C68C: 2E 03	     
		}
		x--;							//C696: 0D		  
		if ( dx < 0x80 ) 			//C697: 30 06	     
		{
			x++;							//C699: 0C		  
			x++;							//C69A: 0C		  
			sgt = 0x10 + sgt;						//C69E: 6F		  
		}
	}

	if ( g_scrn[y][x] >= 0x10 ) return;						//C6A3: D0		  
	pSightB->x = x;	//C6A4: FD 71 00	  
	pSightB->y = y;				//C6A7: FD 70 01	  
	pSightB->_sgt02 = sgt;				//C6AA: FD 75 02	  
	pSightB->_lim03 = 0x20;				//C6AD: FD 36 03 20     
	g_scrn[y][x] = 0x88+sgt;						//C6B4: ED 79	     
	return;								//C6B6: C9		  
}
//-----------------------------------------------------------------------------
void func_RMC60A_ShotSight()									//			    
//-----------------------------------------------------------------------------
{
	for ( unsigned int i = 0 ; i < 32 ; i++ )
	{
		if ( g_BF00_tblSightA[i].y != 0 )					//C618: 28 07	     
		{
			func_RMC626_Sight( &g_BF00_tblSightA[i] );					//C61C: CD 26 C6	  
		}
	}
}

//-----------------------------------------------------------------------------
int main( int argc, char* argv[] )
//-----------------------------------------------------------------------------
{
	Ed	ed;
	if ( argc >= 2 )
	{
		ed.LoadFile( argv[1] );
	}

	func_CEA1_Initialize();


	while ( sys.UpdateSys() )
	{


		{
			Vkey c = sys.key.inkey();

			if ( c.ascii )
			{
//					if ( c.ascii == 'W' ) 		{SendMessage(sys.win.m_hWnd , WM_CLOSE , 0 , 0);continue;}
			
				if ( c.ctrl )
				{
					if ( c.ascii == '\\' ) 	ed.ModeChange();
					else
					if ( c.vk == 'Q' ) 		{SendMessage(sys.win.m_hWnd , WM_CLOSE , 0 , 0);continue;}
					else
					if ( c.vk == 'W' ) 		{SendMessage(sys.win.m_hWnd , WM_CLOSE , 0 , 0);continue;}
					else
					if ( c.vk == 'S' ) 		ed.SaveFile();
					else
					if ( c.vk == VK_UP ) 	ed.buf_moveRollUp(16);
					else
					if ( c.vk == VK_DOWN )	ed.buf_moveRollDown(16);
				}
				else
				{

					if ( c.vk == VK_RIGHT ) {ed.buf_moveRight();}
					else
					if ( c.vk == VK_LEFT ) 	{ed.buf_moveLeft();}
					else
					if ( c.vk == VK_UP ) 	{ed.buf_moveUp();}
					else
					if ( c.vk == VK_DOWN ) 	{ed.buf_moveDown();	}
					else
					if ( c.vk == VK_INSERT ) ed.Request( Ed::CHANGE_INSERT, 0 );


				}

				if ( !c.ctrl && !c.alt )
				{
					{
						ed.Request( Ed::INSERT, c.ascii );
					}
				}

			}
		}

		ed.UpdateScreen();

		func_RMC2CB_SetCarrierAttacker();			//CF00: CD CB C2	  
if ( sys.key.now(VK_LEFT)    ) g_infAttacker.x--;
if ( sys.key.now(VK_RIGHT)    ) g_infAttacker.x++;
if ( sys.key.now(VK_UP)    ) g_infAttacker.y--;
if ( sys.key.now(VK_DOWN)    ) g_infCarrier.x--;
		func_RMC6E8_MissileInput();					//CF03: CD E8 C6	  
		func_RMCC42_Mines();						//CF06: CD 42 CC	  
		func_RMCCB9_DrawVram();						//CF09: CD B9 CC	  
		func_RMC6B8_UpdateSmoke();					//CF0C: CD B8 C6	  
		func_RMC76B_UpdateMisile();					//CF0F: CD 6B C7	  
		func_RMC55D_MoveEnemy();					//CF12: CD 5D C5	  
		func_RMCA90_ScoreUpdate();					//CF15: CD 90 CA	  
		func_RMCB72_Sound();						//CF18: CD 72 CB	  
		func_RMCF38_DrawBomb();						//CF1B: CD 38 CF	  
		func_RMCCB9_DrawVram();						//CF1E: CD B9 CC	  
		func_RMCBE8_UpdateSight();					//CF21: CD E8 CB	  
		func_RMC57A_UpdateRedEnemy();				//CF24: CD 7A C5	  
		func_RMC541_UpdateGreenEnemy();				//CF27: CD 41 C5	  
		func_RMC6B8_UpdateSmoke();					//CF2A: CD B8 C6	  
		func_RMC76B_UpdateMisile();					//CF2D: CD 6B C7	  	  
		func_RMC60A_ShotSight();					//CF30: CD 0A C6	  
		func_RMCF38_DrawBomb();						//CF33: CD 38 CF	  

		glClearColor(0,0,0,0);
		glClear( GL_COLOR_BUFFER_BIT );

		if ( sys.mouse.now.l )
		{
//			sys.m_pBitmap->PutColor( (sys.mouse.x/2.0+0.5)*sys.win.m_buf_w, (sys.mouse.y/2.0+0.5)*sys.win.m_buf_h, 1.0, 1, 0 );
		}

		static	bool flgG = true;
		if ( sys.key.hi('G') ) flgG = !flgG;
		
		if( flgG )
		{
			for ( unsigned int y = 0 ; y < 25 ; y++ )
			{
				for ( unsigned int x = 0 ; x < 40 ; x++ )
				{
					unsigned int a = g_text[y][x];
	//				sys.m_scrn_buf[y*sys.m_scrn_W + x] = a;
					extern	void pcgtest_DrawChar( int lx, int ly, int c );pcgtest_DrawChar( x, y, a );

				}
			}
		}
		else
		{
			for ( unsigned int y = 0 ; y < 256 ; y++ )
			{
				for ( unsigned int x = 0 ; x < 256 ; x++ )
				{
					unsigned int	a = g_scrn[y][x];
					if ( a > 0 && IS_LT_C0_SKY(a) ) 
					{
						sys.m_pBitmap->PutColor( x , y, 0.5, 1, 1 );
					}
					else
					if ( a >= 0xfb  )
					{
						sys.m_pBitmap->PutColor( x , y, 0.5, 0, 0 );
					}
					else
					if ( a )
					{
						sys.m_pBitmap->PutColor( x , y, 1, 1, 0 );
					}
					else
					{
						sys.m_pBitmap->PutColor( x , y, 0, 0, 0 );
					}

				}
			}
/*
			for ( unsigned int y = 0 ; y < 25 ; y++ )
			{
				for ( unsigned int x = 0 ; x < 40 ; x++ )
				{
					if ( g_text[y][x] )
					{
						unsigned int	scale = 2;
						for ( unsigned int i = 0 ; i < scale ; i++ )
						{
							for ( unsigned int j = 0 ; j < scale ; j++ )
							{
								sys.m_pBitmap->PutColor( x*scale+i , y*scale+128+j, 1, 0, 0 );
							}
						}
					}
				}
			}
*/

		}
//		extern	void pcgtest_Draw();		pcgtest_Draw();
	}

	return( 0 );

}
