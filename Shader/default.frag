#version 330 core

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

vec3 lightPos = {5.0f,5.0f,5.0f};

void main()
{
//	vec3 norm = normalize(_normal);
//	vec3 lightDir = normalize(lightPos - _position);
//	float diff = max(dot(norm,lightDir),0.0f);
//	gl_FragColor = texture(_texture,_texCoord) * (_ambientColor+diff);

	gl_FragColor = texture(_texture,_texCoord);
}