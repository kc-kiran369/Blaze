#ifndef SCENE_H
#define SCENE_H

#include"ENTT/entt.hpp"
#include "Components.h"

class Entity;

class Scene
{
public:
	Scene();
	~Scene();

	Entity* CreateEntity();
	void DestroyEntity(Entity entity);
	entt::registry m_Registry;

	std::vector<Entity*> entities;
	friend class Entity;
private:
};
#endif