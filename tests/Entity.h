#ifndef ENTITY_H
#define ENTITY_H

#include"ENTT/entt.hpp"
#include"Scene.h"
#include<vector>

class Entity
{
private:
public:
	entt::entity m_Entity = entt::entity(0);
	Scene* m_Scene = nullptr;

	Entity() = default;
	Entity(entt::entity entity);
	~Entity();

	template<typename T,typename... Args>
	T& AddComponent(Args... args);

	template<typename T>
	T& GetComponent();
};
#endif