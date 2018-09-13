///////////////////////////////////////////////////////////////////////////////
!vs
///////////////////////////////////////////////////////////////////////////////
#version 330

uniform mat4 matProj;
uniform mat4 matModel;
uniform mat4 matView;
uniform vec3	colModel;
uniform vec3	posEye;
uniform vec3	vecEye;


in	vec4 Position;
in	vec3 Normal;
out	vec3 nml;
out	vec3 pos;
out	vec3 vEye;

//-----------------------------------------------------------------------------
struct Screen
//-----------------------------------------------------------------------------
{
	vec3	N;
	float	d;

	vec3	Intersect( vec3 P, vec3 E )
	{
		float	t = d/dot(E,-N);

		vec3	Q = E*t + P;

		return Q;
	}


};

//-----------------------------------------------------------------------------
void main()
//-----------------------------------------------------------------------------
{
	vec3	V = vec3( Position * matModel * matView );
	vec3	P = vec3(0,0,0);;
	vec3	N = vec3(0,0,-1);
	vec3	E = normalize( V - P );
	Screen	screen = Screen( N, 4 );

	vec3	Q = screen.Intersect( P, E );



//	vEye = E * mat3( matView );

	vEye.x = matView[2][0];
	vEye.y = matView[2][1];
	vEye.z = matView[2][2];

	//--

	pos	= V;
	Q.z = 1.0/V.z; //vertex-shaderのz値の1-zがzバッファに書き込まれる疑惑。
//	Q.z = V.z/1000-1.0 -0.0001;
	gl_Position = vec4(Q,1); 
	nml = Normal*mat3( matModel );
}

///////////////////////////////////////////////////////////////////////////////
!fs
///////////////////////////////////////////////////////////////////////////////
#version 330

uniform vec3	colModel;

in	vec3	nml;
in	vec3	pos;
in	vec3	vEye;
out	vec4	Color0;


float	a[] = float[](1,2,3,4);


struct Light
{
	vec3	pos;
	vec3	col;
	
};


const int	cntLight = 3;
Light tblLight[cntLight];

//-----------------------------------------------------------------------------
void main ()
//-----------------------------------------------------------------------------
{
	tblLight[0] = Light( vec3( 8 ,13, 2), vec3(1,1,1) * 550.0 );
	tblLight[1] = Light( vec3(-1, -15, 20), vec3(0.4,0.6,1) * 610.0 );
	tblLight[2] = Light( vec3(-12, 12, 20), vec3(0.8,1,0.8) * 330.0 );


	vec3	A = vec3(0.1,0.1,0.1);

	vec3	E = vec3(0,0,1);
	E = normalize(vEye);

	vec3	N = normalize(nml);

	vec3	col = vec3(0,0,0);

	for ( int i = 0 ; i < cntLight ; i++ )
	{
		vec3	V = pos-tblLight[i].pos;
		vec3	L = normalize( V );
		vec3	Lc = tblLight[i].col / dot( V, V );

		vec3	R = reflect( E, N );

		float	r = 0.5;

		int	n = 30;
		float	d = (1-r) *                       max( 0, dot( -L, N ) ); 
		float 	s = (  r) * ((n+2)/(8*3.14))*pow( max( 0, dot( -L, R ) ), n );

		vec3	Cd = colModel * Lc * d;
		vec3	Cs =            Lc * s;

		col += Cd + Cs;
	}



	Color0 = vec4( col+A, 1.0);


}

