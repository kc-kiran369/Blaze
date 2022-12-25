#pragma once
#include"Texture.h"
#include"ShaderLibrary.h"
class Material
{
private:
	ShaderLibrary* m_ShaderLib;
public:
	Material() = default;
	Texture Albedo, Roughness, Specular;
	float _Albedo, _Roughness, _Specular;
};