#ifdef GL_ES
precision mediump float;
#endif

uniform  mat4 u_matMVP;

attribute vec3 a_position;

void main()
{
	gl_Position = u_matMVP * vec4(a_position, 1.0);
}
