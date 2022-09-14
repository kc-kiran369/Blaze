#ifndef COMPONENTS_H
#define COMPONENTS_H

#include"../Source/Renderer/model.h"
#include"glm/glm.hpp"

#include"../Source/Renderer/Shader.h"

struct Tag
{
	std::string tag = "Untitled";
};

struct Transform
{
	glm::vec3 transform;
	glm::vec3 rotation;
	glm::vec3 scale;

	void OnTransformChange(Shader& shader)
	{
		shader.SetFloat("facX", transform.x);
		shader.SetFloat("facY", transform.y);
		shader.SetFloat("facZ", transform.z);
	}
};

struct Renderer
{
	Model model;
	bool hasModel = false;
	glm::mat4 modelMatrix;
};

struct Light
{
	float intensity;
	glm::vec3 color;
};

struct PointLight : Light
{

};

struct RigidBody;
struct SpiritRenderer;
struct Camera;

#endif