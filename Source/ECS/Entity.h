#ifndef ENTITY_H
#define ENTITY_H

#include<iostream>
#include"ENTT/entt.hpp"

#include"../Benchmark/Logger.h"
#include"../ECS/Scene.h"

class Entity
{
private:
	Scene* m_Scene = nullptr;
public:
	entt::entity m_Entity = entt::entity(0);

	Entity(entt::entity entity, Scene* scene);
	~Entity();

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args);

	template<typename T>
	T& GetComponent();

	template<typename T>
	bool HasComponent();

	void DeleteEntity();
};

template<typename T, typename ...Args>
inline T& Entity::AddComponent(Args&& ...args)
{
	if (HasComponent<T>())
	{
		Logger::Warn("Component already exists");
	}
	else
	{
		return m_Scene->m_Registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
	}
}

template<typename T>
inline T& Entity::GetComponent()
{
	if (HasComponent<T>())
	{
		return m_Scene->m_Registry.get<T>(m_Entity);
	}
	else
	{
		Logger::Warn("Component doesnot exists");
	}
}

template<typename T>
inline bool Entity::HasComponent()
{
		if (m_Scene->m_Registry.all_of<T>(m_Entity))
			return true;
		else
			return false;
}
#endif