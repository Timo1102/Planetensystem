attribute vec3 att_vertex;
attribute vec3 att_normal;
attribute vec3 att_color;

void main()
{
	//gl_Position = vec4(att_vertex, 1.0) * gl_ModelViewMatrix * gl_ProjectionMatrix;
	gl_Position	= gl_ModelViewProjectionMatrix * vec4(att_vertex, 1.0);
}