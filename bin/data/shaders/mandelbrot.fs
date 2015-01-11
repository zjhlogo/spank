#ifdef GL_ES
precision highp float;
#endif

uniform float u_maxIterations;
uniform float u_zoom;
uniform float u_escapeRadius;
uniform vec2 u_centerPos;
uniform vec3 u_colorScale;

varying vec2 v2f_position;

float fmandel(void)
{
	vec2 c = u_centerPos + v2f_position*u_zoom;
	vec2 z = c;

	float n = 0.0;
	for (; n < u_maxIterations; ++n)
	{
		z = vec2(z.x*z.x - z.y*z.y, 2.0*z.x*z.y) + c;
		float modulus = length(z);
		if(modulus > u_escapeRadius)
		{
			return (n + 1.0 - log(log(modulus))/log(2.0));	// http://linas.org/art-gallery/escape/escape.html
		}
	}
	return 0.0;
}

void main()
{
	float n = fmandel();

//	vec3 color;
//	color.r = (sin((n/u_maxIterations+0.3)*6.282)+1.0)*0.5;
//	color.g = (sin((n/u_maxIterations+0.5)*6.282)+1.0)*0.5;
//	color.b = (sin((n/u_maxIterations+0.7)*6.282)+1.0)*0.5;
//
//	gl_FragColor = vec4(color, 1.0);

	gl_FragColor = vec4((-cos(u_colorScale*n)+1.0)/2.0, 1.0);
}
