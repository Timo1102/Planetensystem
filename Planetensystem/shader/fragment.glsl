#version 330

in vec3 vf_color;
in vec3 vf_position;
in vec3 vf_light;

out vec4 r_color;

uniform sampler2D uni_texture;

void main()
{
	r_color = (0.66* clamp(dot(vf_light, normalize(vf_color)), 0.0, 1.0) + 0.33) * texture(uni_texture, vf_position.st);
}