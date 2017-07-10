/** Copyright (c) Lazu Ioan-Bogdan */

#version 410 core

const float M_PI = 3.1415926535897932384626433832795;
const float M_2PI = 2.0 * M_PI;
const float M_INV_PI = 0.31830988618379067153776752674503;
const float M_INV_LOG2 = 1.4426950408889634073599246810019;

in VS_OUT
{
	vec2 textureCoord;

	vec3 N;
	vec3 L;
	vec3 V;
} fs_in;

out vec4 color;

uniform sampler2D tex_diff;
uniform sampler2D tex_ao;

uniform sampler2D tex_env;

void main(void)
{    
    // Rename these so we don't have problems
    vec3 N_norm = normalize(fs_in.N);
    vec3 L_norm = normalize(fs_in.L);
    vec3 V_norm = normalize(fs_in.V);
    vec3 H_norm = normalize(fs_in.L + fs_in.V);

	vec2 texCoord = fs_in.textureCoord;

	vec3 dir = N_norm;

	float environment_rotation = 0;
	float environment_exposure = 1;
	float lod = 0;

    vec2 pos = M_INV_PI * vec2(atan(-dir.z, -1.0 * dir.x), 2.0 * asin(dir.y));
	pos = 0.5 * pos + vec2(0.5);
	pos.x += environment_rotation;

	// Sample
	color = textureLod(tex_env, pos, lod) * environment_exposure;
}