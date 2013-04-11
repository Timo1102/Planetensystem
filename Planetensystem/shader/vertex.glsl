#version 330

in vec3 att_color;
in vec3 att_normal;
in vec3 att_vertex;

out vec3 vf_color;
out vec3 vf_position;
out vec3 vf_light;
out vec2 vf_texcord;

uniform mat4 uni_perspective;
uniform mat4 uni_view;
uniform mat4 uni_model;
uniform vec3 uni_light;

void main()
{
	mat4 modelViewProjection = uni_perspective * uni_view * uni_model;
	
	gl_Position	= modelViewProjection * vec4(att_vertex, 1.0);
	vf_color = (modelViewProjection * vec4(att_vertex, 0.0)).xyz;
	vf_position = (modelViewProjection * vec4(att_vertex, 1.0)).xyz;
	vf_light = normalize((uni_perspective * uni_view * vec4(uni_light, 1.0)).xyz - (modelViewProjection * vec4(att_vertex, 1.0)).xyz);
	vf_texcord = att_vertex.xy * 0.5f + vec2(0.5f,0.5f); 

}