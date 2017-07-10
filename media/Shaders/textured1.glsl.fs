/** Copyright (c) Lazu Ioan-Bogdan */

#version 410 core

in VS_OUT
{
	vec2 textureCoord;

	vec3 N;
	vec3 L;
	vec3 V;
} fs_in;

uniform sampler2D tex_diff;

// uniform sampler2D tex_ao;
// uniform sampler2D tex_env;

void main(void)
{    
    // Rename these so we don't have problems
    vec3 N_norm = normalize(fs_in.N);
    vec3 L_norm = normalize(fs_in.L);
    vec3 V_norm = normalize(fs_in.V);
    vec3 H_norm = normalize(fs_in.L + fs_in.V);

	vec2 texCoord = fs_in.textureCoord;

    vec3 diffuse_albedo = texture(tex_diff, texCoord).xyz;
	// vec3 ao = texture2D(tex_ao, texCoord).xyz;
    vec3 diffuse = max(dot(N_norm, L_norm), 0.0) * diffuse_albedo;
    
    vec3 specular_albedo = vec3(0.1);    
    float specular_power = 50.0;
    
    vec3 specular = pow(max(dot(N_norm, H_norm), 0.0), specular_power) * specular_albedo;

    // gl_FragColor = vec4(diffuse + specular, 1.0);    
	gl_FragColor = vec4(diffuse_albedo, 1.0);
}