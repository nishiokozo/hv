!vs
attribute vec4 Position;
attribute vec2 Uv;

uniform vec2	Ofs;
uniform vec2	Pos;

varying	vec2 uv;




//-----------------------------------------------------------------------------
void main(void)
//-----------------------------------------------------------------------------
{
	gl_Position = Position;

	gl_Position -= vec4(Pos,0,0);

//	uv = Position.xy*0.5+0.5;
	uv = Uv + Ofs;
//	uv = Uv + vec2(1.0/16.0,0);

}

!fs
uniform sampler2D Tex0;
varying	vec2 uv;
uniform vec4	Col;

//-----------------------------------------------------------------------------
void main (void)
//-----------------------------------------------------------------------------
{

	vec4	col = texture2D(Tex0, uv.xy);

//	if ( col.r == 0.0 && col.g == 0.0 && col.b == 0.0 )
	if ( col.r <= 0.1 && col.g <= 0.1 && col.b <= 0.1 )
	{
		gl_FragColor = vec4(0,0,1,1);
//		discard;
	}
	else
	{
	}
//		gl_FragColor = texture2D(Tex0, uv.xy);

	//	float3 col = texture2D(Tex0, uv.xy);
col *= Col;
		gl_FragColor = col;


}

