#version 450 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

in vec3 _position;
in vec3 _normal;
in vec2 _texCoord;

uniform sampler2D _texture;

uniform vec4 _ambientColor;

vec3 lightPos = {0.0f,10.0f,10.0f};

void main()
{
	vec3 lightDir = normalize(lightPos - _position);
	float angle = max(dot(lightDir,normalize(_normal)),0.0f);
	gl_FragColor = (_ambientColor +angle)* texture(_texture,_texCoord) ;
}