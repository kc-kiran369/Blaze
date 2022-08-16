#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;

out vec3 _position;
out vec3 _normal;
out vec2 _texCoord;

uniform mat4 MVP;
uniform mat4 model;

void main()
{
	gl_Position = vec4(position,1.0f) * MVP*model;	
}