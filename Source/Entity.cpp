#include"ECS/Entity.h"


Entity::Entity(entt::entity entity, Scene* scene)
{
	m_Entity = entity;
	m_Scene = scene;
	Logger::Info("Entity Created");
}

Entity::~Entity()
{
	Logger::Warn("Entity Out of Scope");
}