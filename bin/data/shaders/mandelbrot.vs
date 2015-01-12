#ifdef GL_ES
precision highp float;
#endif

uniform  mat4 u_matMVP;

attribute vec3 a_position;

varying vec2 v2f_position;

void main()
{
	gl_Position = u_matMVP * vec4(a_position, 1.0);
	v2f_position = a_position.xy;
}
