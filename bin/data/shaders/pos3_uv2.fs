#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D u_texture;

varying vec2 v_texCoord;

void main (void)
{
	vec4 color = texture2D(u_texture, v_texCoord);
	if (color.a < 0.1) discard;

	gl_FragColor = color;
}
