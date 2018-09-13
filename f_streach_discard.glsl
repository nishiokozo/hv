!vs
attribute vec4 Position;
attribute vec2 Uv;

varying	vec2 uv;

//-----------------------------------------------------------------------------
void main(void)
//-----------------------------------------------------------------------------
{
	gl_Position = Position;
//	uv = Position.xy*0.5+0.5 +1.0/128.0;
//	uv = Position.xy*0.5+0.5;
		uv = Uv;


}

!fs
uniform sampler2D Tex0;
varying	vec2 uv;

//-----------------------------------------------------------------------------
void main (void)
//-----------------------------------------------------------------------------
{

	vec4	col = texture2D(Tex0, uv.xy);

//	if ( col.r == 0.0 && col.g == 0.0 && col.b == 0.0 )
	if ( col.r == 0.0 && col.g == 0.0 && col.b == 0.0 )
	{
//		gl_FragColor = vec4(0,0,1,1);
		discard;
	}
	else
	{
		gl_FragColor = texture2D(Tex0, uv.xy);
	}


}

