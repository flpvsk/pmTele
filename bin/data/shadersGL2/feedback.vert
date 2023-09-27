#version 120

varying vec2 v_tex0coord;

void main(void)
{
	v_tex0coord = gl_MultiTexCoord0.xy;
	gl_Position = ftransform();
}
