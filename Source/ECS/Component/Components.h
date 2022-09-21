#ifndef COMPONENTS_H
#define COMPONENTS_H

#include"../Source/Renderer/model.h"
#include"glm/glm.hpp"

#include"../Source/Renderer/Shader.h"

#pragma region ESSENTIAL
enum ComponentsTag
{
	TAG, TRANSFORM, RENDERER, RIGIDBODY
};


enum class MaterialType {
	STANDARD
};
#pragma endregion


struct Tag
{
	std::string tag = "Untitled";
};

struct Transform
{
	glm::vec3 transform = glm::vec3(0.0f);;
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	void OnTransformChange(Shader& shader)
	{
		shader.SetVec3("facTrans", transform.x, transform.y, transform.z);

		shader.SetMat4("model", modelMatrix);
	}
};

struct Renderer
{
	Model model;
	bool hasModel = false;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
};

struct Material
{
private:
	Shader* m_Shader;

public:
	Material() = default;
	Material(Shader& shader)
		:m_Shader(&shader)
	{
		m_Metallic = 0.0f;
		m_Smoothness = 0.2f;
		m_Emission = 0.0f;
		m_MatType = MaterialType::STANDARD;
	}

	~Material()
	{

	}
	MaterialType m_MatType;

	Texture m_NormalMap;

	glm::vec4 m_Albedo;

	float m_Metallic;
	float m_Smoothness;
	float m_Emission;


	void UploadToShader()
	{
		m_Shader->SetFloat("u_Metallic", m_Metallic);
		m_Shader->SetVec4("u_AlbedoColor", m_Albedo.x, m_Albedo.y, m_Albedo.z, 1.0f);
	}
};

struct Light
{
	float intensity = 1.0f;
	glm::vec3 color = glm::vec3(1.0f);
};

struct RigidBody
{
	float mass = 50;
	bool useGravity = true;
};

struct SpiritRenderer;
struct Camera;

#endif