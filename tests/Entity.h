#ifndef ENTITY_H
#define ENTITY_H

#include"ENTT/entt.hpp"
#include"Scene.h"

class Entity
{
private:
public:
	entt::entity m_Entity;
	Scene* m_Scene = nullptr;

	Entity() = default;
	Entity(entt::entity entity, Scene* scene);
	~Entity();

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args);

	template<typename T>
	T& GetComponent();
};

template<typename T, typename ...Args>
inline T& Entity::AddComponent(Args&& ...args)
{
	/*if (all_of<T>)
	{
		std::cout << "Component Already exists." << std::endl;
	}*/
	return m_Scene->m_Registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
}

template<typename T>
inline T& Entity::GetComponent()
{
	return m_Scene->m_Registry.get<T>(m_Entity);
}
#endif