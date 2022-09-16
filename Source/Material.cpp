#include"Renderer/Material.h"

Material::Material(Shader& shader)
	//:m_Shader(shader)
{
	m_Metallic = 0.0f;
	m_Smoothness = 0.2f;

	m_MatType = MaterialType::STANDARD;
}

Material::~Material()
{

}
