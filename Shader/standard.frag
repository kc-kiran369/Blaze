#version 450 core

out vec4 FragColor;

in vec3 _position;
in vec3 _normal;
in vec2 _texCoord;

uniform sampler2D _texture;

uniform vec4 u_AlbedoColor;

void main()
{
	vec3 lightDir = normalize(_position - lightPos);
	float diffuse = max(dot(lightDir,normalize(_normal)),0.0f);
	FragColor = (_ambientColor+(diffuse*lightIntensity))* texture(_texture,_texCoord) ;
	if(_texture!=NULL)
	{

	}
	FragColor = texture(_texture,_texCoord);
	FragColor = u_AlbedoColor;
}