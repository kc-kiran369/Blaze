#ifndef COMPONENTS_H
#define COMPONENTS_H

#include"../Source/Renderer/model.h"
#include"glm/glm.hpp"
//#include"glm/ext/matrix_transform.hpp"

struct Tag
{
	std::string tag = "Untitled";
};


//struct Vec3
//{
//	float X, Y, Z;
//};

struct Transform
{
	/*Vec3 transform;
	Vec3 rotation;
	Vec3 scale;*/
	glm::vec3 transform;
};

struct Renderer
{
	Model model;
	bool hasModel = false;
};

struct RigidBody;
struct SpiritRenderer;
struct Light;
struct Camera;

#endif