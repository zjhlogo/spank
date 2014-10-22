#ifdef GL_ES
precision mediump float;
#endif

uniform  mat4 u_matMVP;

attribute vec3 a_position;
attribute vec2 a_texCoord;

varying vec2 v_texCoord;

void main()
{
	gl_Position = u_matMVP * vec4(a_position, 1.0);
	v_texCoord = a_texCoord;
}
