#include"Entity.h"

Entity::Entity(entt::entity entity)
{
	m_Entity = entity;
}

template<typename T, typename ...Args>
T& Entity::AddComponent(Args ...args)
{
	if (all_of<T>)
	{
		std::cout << "Component Already exists." << std::endl;
	}
	return m_Scene->m_Registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
}

template<typename T>
inline T& Entity::GetComponent()
{
	return m_Scene->m_Registry.get<T>(m_Entity);
}

Entity::~Entity()
{

}