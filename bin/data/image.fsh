#version 300 es
uniform sampler2D sampler2d;
in mediump vec2	myTexCoord;
layout (location = 0) out lowp vec4 oColour;
void main (void)
{
oColour = texture(sampler2d,myTexCoord);
}
