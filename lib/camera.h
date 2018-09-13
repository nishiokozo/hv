class	Camera
{
public:
	mat4	matCam;
	mat4	matView;
	vec3	vecEye;
	vec3	posEye;
	vec3	atEye;

	//------------------------------------------------------------------------------
	Camera()
	//------------------------------------------------------------------------------
	{
		ResetCamera();
	}

	//------------------------------------------------------------------------------
	void	Translate( float x, float y, float z )
	//------------------------------------------------------------------------------
	{
		matCam = mat4_GetTranslate( x, y, z )  * matCam ;
	}

	//------------------------------------------------------------------------------
	void	Rotate( float x, float y, float z )
	//------------------------------------------------------------------------------
	{
		mat4 M = mat4_GetRotateX( x ) * mat4_GetRotateY( y ) * mat4_GetRotateZ( z );

		vec3	v;
		v = matCam.GetVecT() ;
/*		v.x = matCam.m[3][0];
		v.y = matCam.m[3][1];
		v.z = matCam.m[3][2];
*/
		matCam = M * matCam ;
		
		matCam.SetVecT(v); 
/*
		matCam.m[3][0] = v.x; 
		matCam.m[3][1] = v.y; 
		matCam.m[3][2] = v.z;
*/

	}

	//------------------------------------------------------------------------------
	void	ResetCamera()
	//------------------------------------------------------------------------------
	{
		matCam.Identity();
		matView.Identity();
		vecEye = vec3(0);
		posEye = vec3(0);
		atEye = vec3(0);

		posEye = vec3( 0,0,-10);
		vecEye = normalize(vec3( 0,0,1));
		atEye = vec3(      0.14,     2.58 ,   16);

		matCam.LookFor( posEye, vecEye, vec3(0,1,0) );
		matCam.LookAt( posEye, atEye, vec3(0,1,0) );
	}

	//------------------------------------------------------------------------------
	void	UpdateCamera()
	//------------------------------------------------------------------------------
	{
		mat4_invers( matView.GetArray(), matCam.GetArray() );
		vecEye = matCam.GetVecZ();
		posEye = matCam.GetVecT();

	}
};
