#version 330 core

in vec3 _position;
in vec3 _normal;
in vec2 _texCoord;

void main()
{
	gl_FragColor = vec4(_normal,1.0f);
}