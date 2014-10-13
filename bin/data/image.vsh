#version 300 es
#define VERTEX_ARRAY 0
#define TEXCOORD_ARRAY 1
layout (location = VERTEX_ARRAY) in highp vec4 myVertex;
layout (location = TEXCOORD_ARRAY) in highp vec2 myUV;
uniform mediump mat4 myPMVMatrix;
out mediump vec2 myTexCoord;
void main(void)
{
	gl_Position = myPMVMatrix * myVertex;
	myTexCoord = myUV;
}
