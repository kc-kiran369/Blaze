#include"ECS/Entity.h"

Entity::Entity(entt::entity entity, Scene* scene)
{
	m_Entity = entity;
	m_Scene = scene;
	Logger::Info("Entity Created");
}

Entity::Entity(const Entity& other)
{
	m_Entity = other.m_Entity;
	m_Scene = other.m_Scene;
	Logger::Warn("Entity Copied");
}

Entity::~Entity()
{
	Logger::Warn("Entity Out of Scope");
}

void Entity::DeleteEntity()
{
	m_Scene->m_Registry.destroy(m_Entity);
	//delete this;
}
