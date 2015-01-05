#ifdef GL_ES
precision highp float;
#endif

uniform float u_maxIterations;
uniform float u_zoom;

uniform vec2 u_centerPos;

varying vec3 v2f_position;

void main()
{
	float real = v2f_position.x * u_zoom + u_centerPos.x;
	float imag = v2f_position.y * u_zoom + u_centerPos.y;

	float Creal = real;
	float Cimag = imag;

	float r2 = 0.0;
	float iter;
	for (iter = 0.0; iter < u_maxIterations && r2 < 4.0; ++iter)
	{
		float tempreal = real;
		real = (tempreal * tempreal) - (imag * imag) + Creal;
		imag = 2.0 * tempreal * imag + Cimag;
		r2 = (real * real) + (imag * imag);
	}

	vec3 color;
	color.r = (sin((iter/u_maxIterations+0.3)*6.282)+1.0)*0.5;
	color.g = (sin((iter/u_maxIterations+0.5)*6.282)+1.0)*0.5;
	color.b = (sin((iter/u_maxIterations+0.7)*6.282)+1.0)*0.5;

	gl_FragColor = vec4(color, 1.0);
}
