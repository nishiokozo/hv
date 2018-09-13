class	Shader
{
public:


	GLuint	m_hdlProgram;
	int		m_hdl_buf_Position;
	int		m_hdl_Uv;
	int		m_hdl_var_Projection;
	int		m_hdl_var_Model;
	int		m_hdl_var_View;
	int		m_hdl_bufer_Normal;
	GLuint	m_hdl_idTexture;
	int	m_hdl_var_ColModel;
	int	m_hdl_var_PosEye;
	int	m_hdl_var_VecEye;

	Shader( const char* fn );
	void DrawShape( const Shape& shape, const mat4& M, const mat4& V, const mat4& P, const vec3& color, const vec3& posEye, const vec3& vecEye );



};
