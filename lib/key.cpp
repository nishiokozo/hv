#include	<iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>

#include	"win.h"
#include	"key.h"

static	struct
{
	int	ascii;
	bool flg;
} g_tblFlgKey[] = 
{
    {'*',0},    //  0    .            .      .
    {' ',0},    //  1    VK_LBUTTN    1      Left mouse button 
    {' ',0},    //  2    VK_RBUTTO    2      Right mouse button 
    {' ',0},    //  3    VK_CANCEL    3      Control-break processing 
    {' ',0},    //  4    VK_MBUTTN    4      Middle mouse button on a three-button mouse 
    {' ',0},    //  5    .            .      .
    {' ',0},    //  6    .            .      .
    {' ',0},    //  7    .            .      .
    {' ',1},    //  8    VK_BACK      8      BACKSPACE key 
    {' ',1},    //  9    VK_TAB       9      TAB key 
    {' ',0},    // 10    .            .      .
    {' ',0},    // 11    .            .      .
    {' ',0},    // 12    VK_CLEAR     0C     CLEAR key 
    {' ',1},    // 13    VK_RETURN    0D     ENTER key 
    {' ',0},    // 14    .            .      .
    {' ',0},    // 15    .            .      .
    {' ',0},    // 16    VK_SHIFT     10     SHIFT key 
    {' ',0},    // 17    VK_CONTROL   11     CTRL key 
    {' ',0},    // 18    VK_MENU      12     ALT key 
    {' ',0},    // 19    VK_PAUSE     13     PAUSE key 
    {' ',1},    // 20    VK_CAPITAL   14     C APS LOCK key 
    {' ',0},    // 21    .            .      .
    {' ',0},    // 22    .            .      .
    {' ',0},    // 23    .            .      .
    {' ',0},    // 24    .            .      .
    {' ',0},    // 25    .            .      .
    {' ',0},    // 26    .            .      .
    {' ',1},    // 27    VK_ESCAPE    1B     ESC key 
    {' ',0},    // 28    .            .      .
    {' ',0},    // 29    .            .      .
    {' ',0},    // 30    .            .      .
    {' ',0},    // 31    .            .      .
    {' ',1},    // 32    VK_SPACE     20     SPACEBAR 
    {' ',0},    // 33    VK_PRIOR     21     PAGE UP key 
    {' ',0},    // 34    VK_NEXT      22     PAGE DOWN key 
    {' ',0},    // 35    VK_END       23     END key 
    {' ',0},    // 36    VK_HOME      24     HOME key 
    {' ',1},    // 37    VK_LEFT      25     LEFT ARROW key 
    {' ',1},    // 38    VK_UP        26     UP ARROW key 
    {' ',1},    // 39    VK_RIGHT     27     RIGHT ARROW key 
    {' ',1},    // 40    VK_DOWN      28     DOWN ARROW key 
    {' ',0},    // 41    VK_SELECT    29     SELECT key 
    {' ',0},    // 42    .	          .      .
    {' ',0},    // 43    VK_EXECUTE   2B     EXECUTE key 
    {' ',0},    // 44    VK_SNAPSHOT  2C     PRINT SCREEN key 
    {' ',1},    // 45    VK_INSERT    2D     INS key 
    {' ',1},    // 46    VK_DELETE    2E     DEL key 
    {' ',0},    // 47    VK_HELP      2F     HELP key 
    {' ',1},    // 48    0            .      .
    {' ',1},    // 49    1            .      .
    {' ',1},    // 50    2            .      .
    {' ',1},    // 51    3            .      .
    {' ',1},    // 52    4            .      .
    {' ',1},    // 53    5            .      .
    {' ',1},    // 54    6            .      .
    {' ',1},    // 55    7            .      .
    {' ',1},    // 56    8            .      .
    {' ',1},    // 57    9            .      .
    {' ',0},    // 58    .            .      .
    {' ',0},    // 59    .            .      .
    {' ',0},    // 60    .            .      .
    {' ',0},    // 61    .            .      .
    {' ',0},    // 62    .            .      .
    {' ',0},    // 63    .            .      .
    {' ',1},    // 64    .            .      .
    {'A',1},    // 65    A            .      .
    {'B',1},    // 66    B            .      .
    {'C',1},    // 67    C            .      .
    {'D',1},    // 68    D            .      .
    {'E',1},    // 69    E            .      .
    {'F',1},    // 70    F            .      .
    {'G',1},    // 71    G            .      .
    {'H',1},    // 72    H            .      .
    {'I',1},    // 73    I            .      .
    {'J',1},    // 74    J            .      .
    {'K',1},    // 75    K            .      .
    {'L',1},    // 76    L            .      .
    {'M',1},    // 77    M            .      .
    {'N',1},    // 78    N            .      .
    {'O',1},    // 79    O            .      .
    {'P',1},    // 80    P            .      .
    {'Q',1},    // 81    Q            .      .
    {'R',1},    // 82    R            .      .
    {'S',1},    // 83    S            .      .
    {'T',1},    // 84    T            .      .
    {'U',1},    // 85    U            .      .
    {'V',1},    // 86    V            .      .
    {'W',1},    // 87    W            .      .
    {'X',1},    // 88    X            .      .
    {'Y',1},    // 89    Y            .      .
    {'Z',1},    // 90    Z            .      .
    {' ',0},    // 91    VK_LWIN      5B     Left Windows key on a Microsoft Natural Keyboard 
    {' ',0},    // 92    VK_RWIN      5C     Right Windows key on a Microsoft Natural Keyboard 
    {' ',0},    // 93    VK_APPS      5D     Applications key on a Microsoft Natural Keyboard 
    {' ',0},    // 94    .            .      .
    {' ',0},    // 95    .            .      .
    {'0',1},    // 96    VK_NUMPAD0   60     Numeric keypad 0 key 
    {'1',1},    // 97    VK_NUMPAD1   61     Numeric keypad 1 key 
    {'2',1},    // 98    VK_NUMPAD2   62     Numeric keypad 2 key 
    {'3',1},    // 99    VK_NUMPAD3   63     Numeric keypad 3 key 
    {'4',1},    //100    VK_NUMPAD4   64     Numeric keypad 4 key 
    {'5',1},    //101    VK_NUMPAD5   65     Numeric keypad 5 key 
    {'6',1},    //102    VK_NUMPAD6   66     Numeric keypad 6 key 
    {'7',1},    //103    VK_NUMPAD7   67     Numeric keypad 7 key 
    {'8',1},    //104    VK_NUMPAD8   68     Numeric keypad 8 key 
    {'9',1},    //105    VK_NUMPAD9   69     Numeric keypad 9 key 
    {'*',1},    //106    VK_MULTIPLY  6A     Multiply key 
    {'+',1},    //107    VK_ADD       6B     Add key 
    {' ',1},    //108    VK_SEPARATOR 6C     Separator key 
    {' ',1},    //109    VK_SUBTRACT  6D     Subtract key 
    {' ',1},    //110    VK_DECIMAL   6E     Decimal key 
    {' ',1},    //111    VK_DIVIDE    6F     Divide key 
    {' ',0},    //112    VK_F1        70     F1 key 
    {' ',0},    //113    VK_F2        71     F2 key 
    {' ',0},    //114    VK_F3        72     F3 key 
    {' ',0},    //115    VK_F4        73     F4 key 
    {' ',0},    //116    VK_F5        74     F5 key 
    {' ',0},    //117    VK_F6        75     F6 key 
    {' ',0},    //118    VK_F7        76     F7 key 
    {' ',0},    //119    VK_F8        77     F8 key 
    {' ',0},    //120    VK_F9        78     F9 key 
    {' ',0},    //121    VK_F10       79     F10 key 
    {' ',0},    //122    VK_F11       7A     F11 key 
    {' ',0},    //123    VK_F12       7B     F12 key 
    {' ',0},    //124    VK_F13       7C     F13 key 
    {' ',0},    //125    VK_F14       7D     F14 key 
    {' ',0},    //126    VK_F15       7E     F15 key 
    {' ',0},    //127    VK_F16       7F     F16 key 
    {' ',0},    //128    VK_F17       80     F17 key 
    {' ',0},    //129    VK_F18       81     F18 key 
    {' ',0},    //130    VK_F19       82     F19 key 
    {' ',0},    //131    VK_F20       83     F20 key 
    {' ',0},    //132    VK_F21       84     F21 key 
    {' ',0},    //133    VK_F22       85     F22 key 
    {' ',0},    //134    VK_F23       86     F23 key 
    {' ',0},    //135    VK_F24       87     F24 key 
    {' ',0},    //136    .            .      .
    {' ',0},    //137    .            .      .
    {' ',0},    //138    .            .      .
    {' ',0},    //139    .            .      .
    {' ',0},    //140    .            .      .
    {' ',0},    //141    .            .      .
    {' ',0},    //142    .            .      .
    {' ',0},    //143    .            .      .
    {' ',0},    //144    VK_NUMLOCK   90     NUM LOCK key 
    {' ',0},    //145    VK_SCROLL    91     SCROLL LOCK key 
    {' ',0},    //146    .            .      .
    {' ',0},    //147    .            .      .
    {' ',0},    //148    .            .      .
    {' ',0},    //149    .            .      .
    {' ',0},    //150    .            .      .
    {' ',0},    //151    .            .      .
    {' ',0},    //152    .            .      .
    {' ',0},    //153    .            .      .
    {' ',0},    //154    .            .      .
    {' ',0},    //155    .            .      .
    {' ',0},    //156    .            .      .
    {' ',0},    //157    .            .      .
    {' ',0},    //158    .            .      .
    {' ',0},    //159    .            .      .
    {' ',0},    //160    VK_LSHIFT    0xA0    Left SHIFT
    {' ',0},    //161    VK_RSHIFT    0xA1    Right SHIFT
    {' ',0},    //162    VK_LCONTROL  0xA2    Left CTRL 
    {' ',0},    //163    VK_RCONTROL  0xA3    Right CTRL
    {' ',0},    //164    VK_LMENU     0xA4    Left ALT
    {' ',0},    //165    VK_RMENU     0xA5    Right ALT
    {' ',0},    //166    .            .      .
    {' ',0},    //167    .            .      .
    {' ',0},    //168    .            .      .
    {' ',0},    //169    .            .      .
    {' ',0},    //170    .            .      .
    {' ',0},    //171    .            .      .
    {' ',0},    //172    .            .      .
    {' ',0},    //173    VK_PACKET    E7     Used to pass Unicode characters as if they were keystrokes. If VK_PACKET is used with SendInput, then the Unicode character to be delivered should be placed into the lower 16 bits of the scan code. If a keyboard message is removed from the message queue and the virtual key is VK_PACKET, then the Unicode character will be the upper 16 bits of the lparam.
    {' ',0},    //174      .            .      .
    {' ',0},    //175      .            .      .
    {' ',0},    //176      .            .      .
    {' ',0},    //177      .            .      .
    {' ',0},    //178      .            .      .
    {' ',0},    //179      .            .      .
    {' ',0},    //180      .            .      .
    {' ',0},    //181      .            .      .
    {' ',0},    //182      .            .      .
    {' ',0},    //183      .            .      .
    {' ',0},    //184      .            .      .
    {' ',0},    //185      .            .      .
    {' ',1},    //186    ; .            .      .
    {' ',1},    //187    = .            .      .
    {' ',1},    //188    , .            .      .
    {' ',1},    //189    - .            .      .
    {' ',1},    //190    . .            .      .
    {' ',1},    //191    / .            .      .
    {' ',1},    //192    ` .            .      .
    {' ',0},    //193      .            .      .
    {' ',0},    //194      .            .      .
    {' ',0},    //195      .            .      .
    {' ',0},    //196      .            .      .
    {' ',0},    //197      .            .      .
    {' ',0},    //198      .            .      .
    {' ',0},    //199      .            .      .
    {' ',0},    //200      .            .      .
    {' ',0},    //201      .            .      .
    {' ',0},    //202      .            .      .
    {' ',0},    //203      .            .      .
    {' ',0},    //204      .            .      .
    {' ',0},    //205      .            .      .
    {' ',0},    //206      .            .      .
    {' ',0},    //207      .            .      .
    {' ',0},    //208      .            .      .
    {' ',0},    //209      .            .      .
    {' ',0},    //210      .            .      .
    {' ',0},    //211      .            .      .
    {' ',0},    //212      .            .      .
    {' ',0},    //213      .            .      .
    {' ',0},    //214      .            .      .
    {' ',0},    //215      .            .      .
    {' ',0},    //216      .            .      .
    {' ',0},    //217      .            .      .
    {' ',0},    //218      .            .      .
    {' ',1},    //219    [ .            .      .
    {' ',1},    //220    \ .            .      .
    {' ',1},    //221    ] .            .      .
    {' ',1},    //222    ' .            .      .
    {' ',0},    //223      .            .      .
    {' ',0},    //224      .            .      .
    {' ',0},    //225      .            .      .
    {' ',0},    //226      .            .      .
    {' ',0},    //227      .            .      .
    {' ',0},    //228      .            .      .
    {' ',0},    //229      .            .      .
    {' ',0},    //230      .            .      .
    {' ',0},    //231      .            .      .
    {' ',0},    //232      .            .      .
    {' ',0},    //233      .            .      .
    {' ',0},    //234      .            .      .
    {' ',0},    //235      .            .      .
    {' ',0},    //236      .            .      .
    {' ',0},    //237      .            .      .
    {' ',0},    //238      .            .      .
    {' ',0},    //239      .            .      .
    {' ',0},    //240      .            .      .
    {' ',0},    //241      .            .      .
    {' ',0},    //242      .            .      .
    {' ',0},    //243      .            .      .
    {' ',0},    //244      .            .      .
    {' ',0},    //245      .            .      .
    {' ',0},    //246    VK_ATTN      F6     ATTN key 
    {' ',0},    //247    VK_CRSEL     F7     CRSEL key 
    {' ',0},    //248    VK_EXSEL     F8     EXSEL key 
    {' ',0},    //249    VK_EREOF     F9     Erase EOF key 
    {' ',0},    //250    VK_PLAY      FA     PLAY key 
    {' ',0},    //251    VK_ZOOM      FB     ZOOM key 
    {' ',0},    //252    VK_NONAME    FC     Reserved for future use 
    {' ',0},    //253    VK_PA1       FD     PA1 key 
    {' ',0},    //254    VK_OEM_CLEAR FE     CLEAR key 
    {' ',0},    //255    VK_KEYLOCK   F22    Key used to lock device
};

//-----------------------------------------------------------------------------
int vk2acii( int vk, bool flgShift, int flgCaps )
//-----------------------------------------------------------------------------
{
	bool	oomoji = flgCaps;
	if ( flgShift ) oomoji = !oomoji;

	int	c = 0;

	if ( flgShift )
	{
	    if ( vk == 0 ) {				c='\0';   }//	{'*',0},    //  0    .            .      .
	    if ( vk == VK_RIGHT ) {			c=0x1c;   }
	    if ( vk == VK_LEFT ) {			c=0x1d;   }
	    if ( vk == VK_UP ) {			c=0x1e;   }
	    if ( vk == VK_DOWN ) {			c=0x1f;   }
	    if ( vk == VK_BACK ) {			c='\b';   }//	//{' ',1},    //  8    VK_BACK      8      BACKSPACE key 
	    if ( vk == VK_TAB ) {			c='\t';   }//{' ',1},    //  9    VK_TAB       9      TAB key 
	    if ( vk == VK_RETURN ) {		c='\n';   }//{' ',1},    // 13    VK_RETURN    0D     ENTER key 
	    if ( vk == VK_ESCAPE ) {		c='\e';   }//{' ',1},    // 27    VK_ESCAPE    1B     ESC key 
	    if ( vk == VK_SPACE ) {			c=' ';   }//{' ',1},    // 32    VK_SPACE     20     SPACEBAR 
	    if ( vk == ';' ) {				c=';';   }//{'Z',1},    // 90    Z            .      .
	    if ( vk == 186 ) {				c=':';	}//{' ',1},    //186    ; .            .      .
	    if ( vk == 187 ) {				c='+';	}//{' ',1},    //187    = .            .      .
	    if ( vk == 188 ) {				c='<';	}//{' ',1},    //188    , .            .      .
	    if ( vk == 189 ) {				c='_';	}//{' ',1},    //189    - .            .      .
	    if ( vk == 190 ) {				c='>';	}//{' ',1},    //189    - .            .      .
	    if ( vk == 191 ) {				c='?';	}//{' ',1},    //191    / .            .      .
	    if ( vk == 192 ) {				c='~';	}//{' ',1},    //192    ` .            .      .
	    if ( vk == 219 ) {				c='{';	}//{' ',1},    //219    [ .            .      .
	    if ( vk == 220 ) {				c='|';	}//{' ',1},    //220    \ .            .      .
	    if ( vk == 221 ) {				c='}';	}//{' ',1},    //221    ] .            .      .
	    if ( vk == 222 ) {				c='\"';	}//{' ',1},    //222    ' .            .      .
	    if ( vk == '0' ) {				c=')';   }//{' ',1},    // 48    0            .      .
	    if ( vk == '1' ) {				c='!';   }//{' ',1},    // 49    1            .      .
	    if ( vk == '2' ) {				c='@';   }//{' ',1},    // 50    2            .      .
	    if ( vk == '3' ) {				c='#';   }//{' ',1},    // 51    3            .      .
	    if ( vk == '4' ) {				c='$';   }//{' ',1},    // 52    4            .      .
	    if ( vk == '5' ) {				c='%';   }//{' ',1},    // 53    5            .      .
	    if ( vk == '6' ) {				c='^';   }//{' ',1},    // 54    6            .      .
	    if ( vk == '7' ) {				c='&';   }//{' ',1},    // 55    7            .      .
	    if ( vk == '8' ) {				c='*';   }//{' ',1},    // 56    8            .      .
	    if ( vk == '9' ) {				c='(';   }//{' ',1},    // 57    9            .      .
	}
	else
	{
	    if ( vk == 0 ) {				c='\0';   }//	{'*',0},    //  0    .            .      .
	    if ( vk == VK_RIGHT ) {			c=0x1c;   }
	    if ( vk == VK_LEFT ) {			c=0x1d;   }
	    if ( vk == VK_UP ) {			c=0x1e;   }
	    if ( vk == VK_DOWN ) {			c=0x1f;   }
	    if ( vk == VK_BACK ) {			c='\b';   }//	//{' ',1},    //  8    VK_BACK      8      BACKSPACE key 
	    if ( vk == VK_TAB ) {			c='\t';   }//{' ',1},    //  9    VK_TAB       9      TAB key 
	    if ( vk == VK_RETURN ) {		c='\n';   }//{' ',1},    // 13    VK_RETURN    0D     ENTER key 
	    if ( vk == VK_ESCAPE ) {		c='\e';   }//{' ',1},    // 27    VK_ESCAPE    1B     ESC key 
	    if ( vk == VK_SPACE ) {			c=' ';   }//{' ',1},    // 32    VK_SPACE     20     SPACEBAR 
	    if ( vk == ';' ) {				c=';';   }//{'Z',1},    // 90    Z            .      .
	    if ( vk == 186 ) {				c=';';	}//{' ',1},    //186    ; .            .      .
	    if ( vk == 187 ) {				c='=';	}//{' ',1},    //187    = .            .      .
	    if ( vk == 188 ) {				c=',';	}//{' ',1},    //188    , .            .      .
	    if ( vk == 189 ) {				c='-';	}//{' ',1},    //189    - .            .      .
	    if ( vk == 190 ) {				c='.';	}//{' ',1},    //189    - .            .      .
	    if ( vk == 191 ) {				c='/';	}//{' ',1},    //191    / .            .      .
	    if ( vk == 192 ) {				c='`';	}//{' ',1},    //192    ` .            .      .
	    if ( vk == 219 ) {				c='[';	}//{' ',1},    //219    [ .            .      .
	    if ( vk == 220 ) {				c='\\';	}//{' ',1},    //220    \ .            .      .
	    if ( vk == 221 ) {				c=']';	}//{' ',1},    //221    ] .            .      .
	    if ( vk == 222 ) {				c='\'';	}//{' ',1},    //222    ' .            .      .
	    if ( vk == '0' ) {				c='0';   }//{' ',1},    // 48    0            .      .
	    if ( vk == '1' ) {				c='1';   }//{' ',1},    // 49    1            .      .
	    if ( vk == '2' ) {				c='2';   }//{' ',1},    // 50    2            .      .
	    if ( vk == '3' ) {				c='3';   }//{' ',1},    // 51    3            .      .
	    if ( vk == '4' ) {				c='4';   }//{' ',1},    // 52    4            .      .
	    if ( vk == '5' ) {				c='5';   }//{' ',1},    // 53    5            .      .
	    if ( vk == '6' ) {				c='6';   }//{' ',1},    // 54    6            .      .
	    if ( vk == '7' ) {				c='7';   }//{' ',1},    // 55    7            .      .
	    if ( vk == '8' ) {				c='8';   }//{' ',1},    // 56    8            .      .
	    if ( vk == '9' ) {				c='9';   }//{' ',1},    // 57    9            .      .
	}

	if ( oomoji )
	{
	    if ( vk == 'A' ) {				c='A';   }//{'A',1},    // 65    A            .      .
	    if ( vk == 'B' ) {				c='B';   }//{'B',1},    // 66    B            .      .
	    if ( vk == 'C' ) {				c='C';   }//{'C',1},    // 67    C            .      .
	    if ( vk == 'D' ) {				c='D';   }//{'D',1},    // 68    D            .      .
	    if ( vk == 'E' ) {				c='E';   }//{'E',1},    // 69    E            .      .
	    if ( vk == 'F' ) {				c='F';   }//{'F',1},    // 70    F            .      .
	    if ( vk == 'G' ) {				c='G';   }//{'G',1},    // 71    G            .      .
	    if ( vk == 'H' ) {				c='H';   }//{'H',1},    // 72    H            .      .
	    if ( vk == 'I' ) {				c='I';   }//{'I',1},    // 73    I            .      .
	    if ( vk == 'J' ) {				c='J';   }//{'J',1},    // 74    J            .      .
	    if ( vk == 'K' ) {				c='K';   }//{'K',1},    // 75    K            .      .
	    if ( vk == 'L' ) {				c='L';   }//{'L',1},    // 76    L            .      .
	    if ( vk == 'M' ) {				c='M';   }//{'M',1},    // 77    M            .      .
	    if ( vk == 'N' ) {				c='N';   }//{'N',1},    // 78    N            .      .
	    if ( vk == 'O' ) {				c='O';   }//{'O',1},    // 79    O            .      .
	    if ( vk == 'P' ) {				c='P';   }//{'P',1},    // 80    P            .      .
	    if ( vk == 'Q' ) {				c='Q';   }//{'Q',1},    // 81    Q            .      .
	    if ( vk == 'R' ) {				c='R';   }//{'R',1},    // 82    R            .      .
	    if ( vk == 'S' ) {				c='S';   }//{'S',1},    // 83    S            .      .
	    if ( vk == 'T' ) {				c='T';   }//{'T',1},    // 84    T            .      .
	    if ( vk == 'U' ) {				c='U';   }//{'U',1},    // 85    U            .      .
	    if ( vk == 'V' ) {				c='V';   }//{'V',1},    // 86    V            .      .
	    if ( vk == 'W' ) {				c='W';   }//{'W',1},    // 87    W            .      .
	    if ( vk == 'X' ) {				c='X';   }//{'X',1},    // 88    X            .      .
	    if ( vk == 'Y' ) {				c='Y';   }//{'Y',1},    // 89    Y            .      .
	    if ( vk == 'Z' ) {				c='Z';   }//{'Z',1},    // 90    Z            .      .
	}
	else
	{
	    if ( vk == 'A' ) {				c='a';   }//{'A',1},    // 65    A            .      .
	    if ( vk == 'B' ) {				c='b';   }//{'B',1},    // 66    B            .      .
	    if ( vk == 'C' ) {				c='c';   }//{'C',1},    // 67    C            .      .
	    if ( vk == 'D' ) {				c='d';   }//{'D',1},    // 68    D            .      .
	    if ( vk == 'E' ) {				c='e';   }//{'E',1},    // 69    E            .      .
	    if ( vk == 'F' ) {				c='f';   }//{'F',1},    // 70    F            .      .
	    if ( vk == 'G' ) {				c='g';   }//{'G',1},    // 71    G            .      .
	    if ( vk == 'H' ) {				c='h';   }//{'H',1},    // 72    H            .      .
	    if ( vk == 'I' ) {				c='i';   }//{'I',1},    // 73    I            .      .
	    if ( vk == 'J' ) {				c='j';   }//{'J',1},    // 74    J            .      .
	    if ( vk == 'K' ) {				c='k';   }//{'K',1},    // 75    K            .      .
	    if ( vk == 'L' ) {				c='l';   }//{'L',1},    // 76    L            .      .
	    if ( vk == 'M' ) {				c='m';   }//{'M',1},    // 77    M            .      .
	    if ( vk == 'N' ) {				c='n';   }//{'N',1},    // 78    N            .      .
	    if ( vk == 'O' ) {				c='o';   }//{'O',1},    // 79    O            .      .
	    if ( vk == 'P' ) {				c='p';   }//{'P',1},    // 80    P            .      .
	    if ( vk == 'Q' ) {				c='q';   }//{'Q',1},    // 81    Q            .      .
	    if ( vk == 'R' ) {				c='r';   }//{'R',1},    // 82    R            .      .
	    if ( vk == 'S' ) {				c='s';   }//{'S',1},    // 83    S            .      .
	    if ( vk == 'T' ) {				c='t';   }//{'T',1},    // 84    T            .      .
	    if ( vk == 'U' ) {				c='u';   }//{'U',1},    // 85    U            .      .
	    if ( vk == 'V' ) {				c='v';   }//{'V',1},    // 86    V            .      .
	    if ( vk == 'W' ) {				c='w';   }//{'W',1},    // 87    W            .      .
	    if ( vk == 'X' ) {				c='x';   }//{'X',1},    // 88    X            .      .
	    if ( vk == 'Y' ) {				c='y';   }//{'Y',1},    // 89    Y            .      .
	    if ( vk == 'Z' ) {				c='z';   }//{'Z',1},    // 90    Z            .      .
	}

	return c;
}
//-----------------------------------------------------------------------------
Key::~Key()
//-----------------------------------------------------------------------------
{
}
//-----------------------------------------------------------------------------
Key::Key()
//-----------------------------------------------------------------------------
{
	for ( int i = 0 ; i < 256 ; i++ )
	{
		m_keybtn[i].prev = 0;
		m_keybtn[i].now = 0;
		m_keybtn[i].limRepeat = 0;
	}

	for ( int i = 0 ; i < MAX_KEYBUF  ; i++ )
	{
		m_keybuf[i] = 0;
	}

	m_keycurrent = 0;


	for ( int i = 0 ; i < MAX_KEYBUF  ; i++ )
	{
		m_keybuf[i] = 0;
	}


	//	VK key buffer clear
	GetKeyboardState( m_key_state );
	for ( int i = 0 ; i < 256 ; i++ )
	{
		m_key_state[i] = m_key_state[i] & ~0x80;
	}
	SetKeyboardState( m_key_state );

//	m_limActive = 10;

				m_limRepeat1st = 20;
				m_limRepeat2nd = 4;

}

//-----------------------------------------------------------------------------
void	Key::SetRepatTime( int n, int m )
//-----------------------------------------------------------------------------
{
				m_limRepeat1st = n;
				m_limRepeat2nd = m;
}
//-----------------------------------------------------------------------------
void	Key::UpdateKey()
//-----------------------------------------------------------------------------
{
	GetKeyboardState( m_key_state );


	for ( int i = 0 ; i < 256 ; i++ )
	{
		Keybtn&	k = m_keybtn[i];

		k.prev = k.now;

		k.now = ((m_key_state[i] & 0x80) != 0 );
		k.toggle = ((m_key_state[i] & 0x01) != 0 );

		if ( k.now )
		{
			if ( !k.prev )
			{
				k.limRepeat = m_limRepeat1st;
			}
			else
			{
				k.limRepeat--;
				if ( k.limRepeat == 0 )
				{
					k.limRepeat = m_limRepeat2nd;
				}
			}
		}
		else
		{
			k.limRepeat = 0;
		}
	}

	
	for ( int i = 0 ; i < 256 ; i++ )
	{
//if ( this->repeat(i) && i < 0xf0  ) printf("vk %x %d\n", i, i);
//if ( this->repeat(i) && i < 0xf0  ) printf("vk %x %d\n", i, i);

		// keybuf:add
		if ( g_tblFlgKey[i].flg )
		{
			if (   this->repeat(i) )
			{
				for ( int j = MAX_KEYBUF-2 ; j > 0  ; j-- )
				{
					m_keybuf[j+1] = m_keybuf[j];
				}
//				m_keybuf[0] = i;
				m_keybuf[0] = vk2acii(i, this->now(VK_SHIFT), m_keybtn[VK_CAPITAL].toggle );

			}
		}

	}

	// keybuf:take
	m_keycurrent = m_keybuf[0];
	for ( int i = 0 ; i < MAX_KEYBUF-1 ; i++ )
	{
		m_keybuf[i] = m_keybuf[i+1];
	}
	m_keybuf[MAX_KEYBUF-1] = 0;

}

//-----------------------------------------------------------------------------
bool	Key::now( int val )
//-----------------------------------------------------------------------------
{
	return m_keybtn[val].now;
}
//-----------------------------------------------------------------------------
bool	Key::hi( int val )
//-----------------------------------------------------------------------------
{
	return ( !m_keybtn[val].prev && m_keybtn[val].now );
}
//-----------------------------------------------------------------------------
bool	Key::repeat( int val )
//-----------------------------------------------------------------------------
{

	return ( m_keybtn[val].limRepeat == 1 || this->hi(val) );
}


//-----------------------------------------------------------------------------
Keybtn	Key::Get( int val )
//-----------------------------------------------------------------------------
{
	return m_keybtn[val];
}
//-----------------------------------------------------------------------------
void	Key::Clear()
//-----------------------------------------------------------------------------
{
vkbuf_Clear();

	for ( int i=0 ; i < 256 ; i++ )
	{
		m_keybtn[i].prev = 0;
		m_keybtn[i].now = 0;
		m_keybtn[i].toggle = 0;
		m_keybtn[i].limRepeat = 0;
	}
	vkbuf_Clear();

	//	VK key buffer clear
	GetKeyboardState( m_key_state );
	for ( int i = 0 ; i < 256 ; i++ )
	{
		m_key_state[i] = m_key_state[i] & ~0x80;
	}
	SetKeyboardState( m_key_state );

	for ( int i = 0 ; i < MAX_KEYBUF ; i++ )
	{
		m_keybuf[i] = 0;
	}

}
//-----------------------------------------------------------------------------
Vkey	Key::inkey()
//-----------------------------------------------------------------------------
{
//	extern	int vkbuf_cnt;
	int	p1 = 0;
	int	p2 = 0;
	vkbuf_get(&p1, &p2);


	Vkey vk;

//vk2acii(p1, p2&WIN_SHIFT, p2&WIN_CAPS );	

	vk.vk = p1;
	vk.shift = (p2&(1<<WIN_SHIFT)) != 0;
	vk.caps  = (p2&(1<<WIN_CAPS)) != 0;
	vk.ctrl  = (p2&(1<<WIN_CTRL)) != 0;
	vk.alt   = (p2&(1<<WIN_ALT)) != 0;

	vk.ascii = vk2acii(p1, vk.shift, vk.caps );	

	return   vk;

//if ( c ) printf("vkbuf_cnt=%d, c =%d\n", vkbuf_cnt,c );
//	return	c;

//	return m_keycurrent;
}
	
