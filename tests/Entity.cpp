#include"Entity.h"

Entity::Entity(entt::entity entity,Scene* scene)
{
	m_Entity = entity;
	m_Scene = scene;
}

Entity::~Entity()
{

}