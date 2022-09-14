#version 450 core

in vec3 _position;
in vec3 _normal;
in vec2 _texCoord;

uniform sampler2D _texture;

uniform vec4 _ambientColor;
float  lightIntensity = 2.5f;

uniform vec3 lightPos = {0.0f,10.0f,10.0f};

void main()
{
	vec3 lightDir = normalize(_position - lightPos);
	float diffuse = max(dot(lightDir,normalize(_normal)),0.0f);
	gl_FragColor = (_ambientColor+(diffuse*lightIntensity))* texture(_texture,_texCoord) ;
}