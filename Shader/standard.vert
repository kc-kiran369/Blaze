#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;

out vec3 _position;
out vec3 _normal;
out vec2 _texCoord;

uniform mat4 ViewProjection;
uniform mat4 model = mat4(1.0f);

uniform vec3 facTrans = vec3(0.0f);

void main()
{
	_position = position;
	_normal = normal;
	_texCoord = texCoord;

	gl_Position = ViewProjection * vec4(position + facTrans, 1.0f);	
}