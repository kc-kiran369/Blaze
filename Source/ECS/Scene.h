#ifndef SCENE_H
#define SCENE_H

#include<sstream>
#include"ENTT/entt.hpp"
#include"Benchmark/Logger.h"
#include"ECS/Component/Components.h"

#include<string_view>
#include<sstream>

class Entity;

class Scene
{
public:
	Scene();
	~Scene();

	friend class Entity;

	Entity* CreateEntity();
	void DestroyEntity(Entity entity);
	entt::registry m_Registry;

	std::vector<Entity*> entities;
private:
};
#endif