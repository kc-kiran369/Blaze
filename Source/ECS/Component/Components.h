#ifndef COMPONENTS_H
#define COMPONENTS_H

#include"../Source/Renderer/model.h"
#include"glm/glm.hpp"

#include"../Source/Renderer/Shader.h"

#include"../Source/Renderer/Material.h"

enum ComponentsTag
{
	TAG, TRANSFORM, RENDERER, RIGIDBODY
};

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
		shader.SetFloat("facX", transform.x);
		shader.SetFloat("facY", transform.y);
		shader.SetFloat("facZ", transform.z);

		modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		shader.SetMat4("model", modelMatrix);
	}
};

struct Renderer
{
	Model model;
	bool hasModel = false;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
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