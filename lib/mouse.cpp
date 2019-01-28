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

#include "mouse.h"

//------------------------------------------------------------------------------
Mouse::Mouse()
//------------------------------------------------------------------------------
{
	x = 0;
	y = 0;

	prev_x = 0;
	prev_y = 0;

	dx = 0;
	dy = 0;

	now.l = 0;
	now.r = 0;

	hi.l = 0;
	hi.r = 0;

	low.l = 0;
	low.r = 0;
}
//------------------------------------------------------------------------------
//void Mouse::UpdateMouse( HWND hWnd )
void Mouse::UpdateMouse( int _x, int _y, int _w, int _h )
//------------------------------------------------------------------------------
{
	POINT pos;
	GetCursorPos( &pos );

#if 0
	POINT    point;
	point.x = pos.x;
	point.y = pos.y;
	ScreenToClient( hWnd, &point );

	RECT    cect;
	GetClientRect( hWnd, &cect );

	prev_x = x;
	prev_y = y;

	x =  2*(float)(point.x - cect.right/2) / cect.right;
	y = -2*(float)(point.y - cect.bottom/2) / cect.bottom;
#else
	POINT    point;
	point.x = pos.x - _x;
	point.y = pos.y - _y;

	prev_x = x;
	prev_y = y;

	x =  2*(float)(point.x - _w/2) / _w;
	y = -2*(float)(point.y - _h/2) / _h;
#endif

//printf(" crect %d %d %d %d\n", cect.right, cect.bottom, cect.left, cect.top );

	dx = x - prev_x;
	dy = y - prev_y;

	now.l = ( 0 != GetAsyncKeyState(VK_LBUTTON) );
	now.r = ( 0 != GetAsyncKeyState(VK_RBUTTON) );

	hi.l = (now.l && !prev.l);
	hi.r = (now.r && !prev.r);

	low.l = (!now.l && prev.l);
	low.r = (!now.r && prev.r);


	prev = now;

	
	
}
