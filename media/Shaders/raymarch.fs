/** Copyright (c) 2016 Lazu Ioan-Bogdan */

#version 420 core

struct Ray
{
    vec3 origin;
    vec3 direction;
};

in VS_OUT
{
    vec3    ray_origin;
    vec3    ray_direction;
} fs_in;

float f(float x, float z)
{
	return sin(x)*sin(z);
	// return 0.5;
}

bool RaymarchTerrain(in Ray r, in vec3 pp)
{
	const float delt = 0.01;
	const float mint = 0.001;
	const float maxt = 10.0;
	
	float lh = 0.0;
	float ly = 0.0;
	
	for(float t = mint; t < maxt; t += delt)
	{
		vec3 p = r.origin + r.direction * t;
		float h = f(p.x, p.z); 
		
		if(p.y < h)
		{
			return true;
		}
	}
	
	return false;
}

uniform vec2 resolution;
uniform mat4 uni_proj;
uniform mat4 uni_view;

void main(void)
{    	
	vec3 p;
	p.xy = (gl_FragCoord.xy / resolution) * 2.0 - 1.0;	
	p.z = gl_FragCoord.z * 2.0 - 1.0;	

	Ray r;
	r.origin = fs_in.ray_origin;
    r.direction = normalize(fs_in.ray_direction);
	
	if(RaymarchTerrain(r, p))
	{
		gl_FragColor = vec4(0.2, 0.4, 0.6, 1.0);
	}
	else
	{
		gl_FragColor = vec4(0.8, 1.0, 0.8, 1.0);
	}
}