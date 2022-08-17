#version 330 core

in vec3 _position;
in vec3 _normal;
in vec2 _texCoord;

uniform sampler2D _texture;

void main()
{
//	gl_FragColor = vec4(1.0f,0.9f,0.8f,1.0f)*vec4(_normal,0.0f);
	gl_FragColor = texture(_texture,_texCoord*1.0f);
}