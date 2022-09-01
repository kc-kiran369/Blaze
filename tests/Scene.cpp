#include"Scene.h"
#include"Components.h"
#include"Entity.h"
#include"../Source/Logger.h"

Scene::Scene()
{
	Logger::Info("Scene Initialized");
}

Scene::~Scene()
{
	Logger::Info("Scene out of scope");
}

Entity* Scene::CreateEntity()
{
	Entity* entity = new Entity(m_Registry.create(), this);
	entity->AddComponent<Tag>("Entity");
	entity->AddComponent<Transform>();
	entity->AddComponent<Renderer>();
	entities.push_back(entity);
	return entity;
}

void Scene::DestroyEntity(Entity entity)
{
	m_Registry.destroy(entity.m_Entity);
}