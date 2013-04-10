in vec3 vf_color;
in vec3 vf_position;
in vec3 vf_light;

void main()
{
	gl_FragColor = (0.66* clamp(dot(vf_light, normalize(vf_color)), 0.0, 1.0) + 0.33) * vec4(1.0,1.0,1.0,1.0);
}