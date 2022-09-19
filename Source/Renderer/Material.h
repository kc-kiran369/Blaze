#ifndef MATERIAL_H
#define MATERIAL_H

#include"Texture.h"
#include"Shader.h"

enum class MaterialType {
	STANDARD
};

class Material
{
	Shader& m_Shader;
public:
	Texture m_Albedo;
	Texture m_NormalMap;

	float m_Metallic;
	float m_Smoothness;

	MaterialType m_MatType;

	Material() = default;
	Material(Shader& shader);
	~Material();
};

#endif // !MATERIAL_H
