#ifndef ENTITY_H
#define ENTITY_H

#include"ENTT/entt.hpp"
#include"Scene.h"

class Entity
{
private:
public:
	entt::entity m_Entity = entt::entity(NULL);
	Scene* m_Scene = nullptr;

	Entity() = default;
	Entity(entt::entity entity, Scene* scene);
	~Entity();

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args);

	template<typename T>
	T& GetComponent();

	template<typename T>
	bool HasComponent();
};

template<typename T, typename ...Args>
inline T& Entity::AddComponent(Args&& ...args)
{
	/*if (m_Scene->m_Registry.all_of<T>(m_Entity))
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
template<typename T>
inline bool Entity::HasComponent()
{
	if (m_Scene->m_Registry.all_of<T>(m_Entity))
		return true;
	else
		return false;
}
#endif