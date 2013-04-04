#version 330

in vec3 att_color;
in vec3 att_normal;
in vec3 att_vertex;

out vec3 vf_color;

uniform mat4 uni_perspective;
uniform mat4 uni_modelView;

void main()
{
	gl_Position	= uni_perspective * uni_modelView * vec4(att_vertex, 1.0);
	vf_color = att_color;
}