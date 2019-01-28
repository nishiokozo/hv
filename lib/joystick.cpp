#include	<iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>
#undef APIENTRY
#include <GL/glew.h>
#undef GLEWAPI
#include <GL/wglew.h>

#include "vec.h"
#include "joystick.h"

//------------------------------------------------------------------------------
Joystick::Joystick( int n )
//------------------------------------------------------------------------------
{
	m_id = n;

	#define	THRESHOLD	0.2

	ValThreshold = THRESHOLD;
}

//------------------------------------------------------------------------------
static float NormalizeVal( float val, float threshold )
//------------------------------------------------------------------------------
{
			if ( val <  threshold && val > 0 ) val = 0.0;
	else	if ( val > -threshold && val < 0 ) val = 0.0;
	else	if ( val > 0.0 ) val = (val - threshold)/(1.0-threshold);
	else	if ( val < 0.0 ) val = (val + threshold)/(1.0-threshold);

	return val;
}

//------------------------------------------------------------------------------
static void NormalizeVec( float& x, float& y, float threshold )
//------------------------------------------------------------------------------
{
	vec2 V(x,y);

	float	l = length( V );

			if ( l <  threshold && l > 0 ) l = 0.0;
	else	if ( l > 1.0 ) l = 1.0;
	else	if ( l > 0.0 ) l = (l - threshold)/(1.0-threshold);

	if ( l > 0.0 )
	{
		V = l * normalize( V );
		x = V.x;
		y = V.y;
	}
	else
	{
		x = 0;
		y = 0;
	}
	
}

//------------------------------------------------------------------------------
void Joystick::SetThreshold( float val )
//------------------------------------------------------------------------------
{
	ValThreshold =  val;
}
//------------------------------------------------------------------------------
void Joystick::UpdateJoystick()
//------------------------------------------------------------------------------
{

	JOYINFOEX jix;

	jix.dwSize = sizeof(jix);
	jix.dwFlags = JOY_RETURNALL;
	int ret = joyGetPosEx(m_id, &jix);

	if ( ret == JOYERR_NOERROR )
	{

		Lx =  (float)(jix.dwXpos-32768.0f)/32768.0f;
		Ly = -(float)(jix.dwYpos-32768.0f)/32768.0f;
		Rx =  (float)(jix.dwRpos-32768.0f)/32768.0f;
		Ry = -(float)(jix.dwZpos-32768.0f)/32768.0f;

		NormalizeVec( Lx, Ly, ValThreshold );
		NormalizeVec( Rx, Ry, ValThreshold );

		now.Ru = ((jix.dwButtons & 0x08) != 0);
		now.Rd = ((jix.dwButtons & 0x01) != 0);
		now.Rl = ((jix.dwButtons & 0x04) != 0);
		now.Rr = ((jix.dwButtons & 0x02) != 0);
	//printf("jix %x\n", (int)jix.dwPOV );
		now.Lu = (jix.dwPOV == 0x0000) || (jix.dwPOV == 0x7b0c) || (jix.dwPOV == 0x1194);
		now.Ld = (jix.dwPOV == 0x4650) || (jix.dwPOV == 0x57e4) || (jix.dwPOV == 0x34bc);
		now.Ll = (jix.dwPOV == 0x6978) || (jix.dwPOV == 0x7b0c) || (jix.dwPOV == 0x57e4);
		now.Lr = (jix.dwPOV == 0x2328) || (jix.dwPOV == 0x1194) || (jix.dwPOV == 0x34bc);

	/*
		now.R1 = ((jix.dwButtons & 0x80) != 0);
		now.R2 = ((jix.dwButtons & 0x20) != 0);
		now.R3 = ((jix.dwButtons & 0x800) != 0);

		now.L1 = ((jix.dwButtons & 0x40) != 0);
		now.L2 = ((jix.dwButtons & 0x10) != 0);
		now.L3 = ((jix.dwButtons & 0x400) != 0);

		now.Se = ((jix.dwButtons & 0x200) != 0);
		now.St = ((jix.dwButtons & 0x100) != 0);
	*/

		now.L1 = ((jix.dwButtons & 0x10) != 0);
		now.L2 = ((jix.dwButtons & 0x20) != 0);

		now.R1 = ((jix.dwButtons & 0x40) != 0);
		now.R2 = ((jix.dwButtons & 0x80) != 0);

		now.R3 = ((jix.dwButtons & 0x800) != 0);
		now.L3 = ((jix.dwButtons & 0x400) != 0);


		now.Se = ((jix.dwButtons & 0x100) != 0);
		now.St = ((jix.dwButtons & 0x200) != 0);


		hi.Lu = (now.Lu && !prev.Lu);
		hi.Ld = (now.Ld && !prev.Ld);
		hi.Ll = (now.Ll && !prev.Ll);
		hi.Lr = (now.Lr && !prev.Lr);
		hi.L1 = (now.L1 && !prev.L1);
		hi.L2 = (now.L2 && !prev.L2);
		hi.L3 = (now.L3 && !prev.L3);

		hi.Ru = (now.Ru && !prev.Ru);
		hi.Rd = (now.Rd && !prev.Rd);
		hi.Rl = (now.Rl && !prev.Rl);
		hi.Rr = (now.Rr && !prev.Rr);
		hi.R1 = (now.R1 && !prev.R1);
		hi.R2 = (now.R2 && !prev.R2);
		hi.R3 = (now.R3 && !prev.R3);

		hi.Se = (now.Se && !prev.Se);
		hi.St = (now.St && !prev.St);


		low.Lu = (!now.Lu && prev.Lu);
		low.Ld = (!now.Ld && prev.Ld);
		low.Ll = (!now.Ll && prev.Ll);
		low.Lr = (!now.Lr && prev.Lr);
		low.L1 = (!now.L1 && prev.L1);
		low.L2 = (!now.L2 && prev.L2);
		low.L3 = (!now.L3 && prev.L3);

		low.Ru = (!now.Ru && prev.Ru);
		low.Rd = (!now.Rd && prev.Rd);
		low.Rl = (!now.Rl && prev.Rl);
		low.Rr = (!now.Rr && prev.Rr);
		low.R1 = (!now.R1 && prev.R1);
		low.R2 = (!now.R2 && prev.R2);
		low.R3 = (!now.R3 && prev.R3);

		low.Se = (!now.Se && prev.Se);
		low.St = (!now.St && prev.St);
	}
	else
	{
		memset( &now, 0, sizeof(now) );
		memset( &hi,  0, sizeof(hi) );
		memset( &low ,0, sizeof(low) );
		memset( &prev,0, sizeof(prev) );

		Lx = 0;
		Ly = 0;
		Rx = 0;
		Ry = 0;

		memset( &LU, 0, sizeof(LU) );
		memset( &LD, 0, sizeof(LD) );
		memset( &LL, 0, sizeof(LL) );
		memset( &LR, 0, sizeof(LR) );
		memset( &L1, 0, sizeof(L1) );
		memset( &L2, 0, sizeof(L2) );
		memset( &L3, 0, sizeof(L3) );

		memset( &RU, 0, sizeof(RU) );
		memset( &RD, 0, sizeof(RD) );
		memset( &RL, 0, sizeof(RL) );
		memset( &RR, 0, sizeof(RR) );
		memset( &R1, 0, sizeof(R1) );
		memset( &R2, 0, sizeof(R2) );
		memset( &R3, 0, sizeof(R3) );

		memset( &SE, 0, sizeof(SE) );
		memset( &ST, 0, sizeof(ST) );

	}
	


	prev = now;
	

}
