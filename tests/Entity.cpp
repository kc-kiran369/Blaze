#include"Entity.h"
#include"../Source/Logger.h"

Entity::Entity(entt::entity entity, Scene* scene)
{
	m_Entity = entity;
	m_Scene = scene;
	Logger::Warn("Entity Created");
}

Entity::~Entity()
{
	Logger::Warn("Entity Out of Scope");
}