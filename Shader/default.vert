#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;

out vec3 _position;
out vec3 _normal;
out vec2 _texCoord;

uniform mat4 MVP;

void main()
{
	_position = position;
	_normal = normal;
	_texCoord = texCoord;
	gl_Position = MVP * vec4(position,1.0f);	
}