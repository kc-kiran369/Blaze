#ifndef COMPONENTS_H
#define COMPONENTS_H

#include"../Source/model.h"

struct Tag
{
	const char* tag = "Untitled Entity";
};

struct Vec3
{
	float X, Y, Z;
};

struct Transform
{
	Vec3 transform;
	Vec3 rotation;
	Vec3 scale;
};

struct Renderer
{
	Model model;
	std::vector<Texture> textures;
};

struct RigidBody;
struct SpiritRenderer;
#endif