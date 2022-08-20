#version 330 core

in vec3 _position;
in vec3 _normal;
in vec2 _texCoord;

uniform sampler2D _texture;

uniform vec4 _ambientColor;

void main()
{
	gl_FragColor = texture(_texture,_texCoord) * _ambientColor;
}