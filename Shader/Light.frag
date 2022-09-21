#version 330 core

uniform float u_Metallic;
uniform float u_Smoothness;

void main()
{
	gl_FragColor = vec4(vec3(u_Metallic),1.0f);
}