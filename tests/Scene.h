#ifndef SCENE_H
#define SCENE_H

#include"ENTT/entt.hpp"
#include "Components.h"

class Scene
{
public:
	Scene();
	~Scene();

	void CreateEntity(std::string name);
	entt::registry m_Registry;
private:
};
#endif