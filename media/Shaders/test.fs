/** Copyright (c) 2016 Lazu Ioan-Bogdan */

#version 420 core

void main(void)
{    
	vec3 NDC;

	NDC.xy = (gl_FragCoord.xy / vec2(800.0, 600.0)) * 2.0 - 1.0;
	NDC.z = gl_FragCoord.z * 2.0 - 1.0;

	gl_FragColor = vec4(NDC.z, 0.0, 0.0, 1.0);
}