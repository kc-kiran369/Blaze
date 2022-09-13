#ifndef COMPONENTS_H
#define COMPONENTS_H

#include"../Source/Renderer/model.h"
#include"glm/glm.hpp"

struct Tag
{
	std::string tag = "Untitled";
};

struct Transform
{
	glm::vec3 transform;
	glm::vec3 rotation;
	glm::vec3 scale;
};

struct Renderer
{
	Model model;
	bool hasModel = false;
};

struct Light
{
	float intensity;
	glm::vec4 color;
	Transform transform;
};

struct PointLight : Light
{

};

struct RigidBody;
struct SpiritRenderer;
struct Camera;

#endif