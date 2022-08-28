#ifndef COMPONENTS_H
#define COMPONENTS_H

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

#endif