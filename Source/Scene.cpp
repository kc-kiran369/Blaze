#include"ECS/Scene.h"
#include"ECS/Entity.h"

Scene::Scene()
{
	Logger::Info("Scene Initialized");
}

Scene::~Scene()
{
	Logger::Info("Scene out of scope");
	for (auto entity : entities)
	{
		delete entity;
	}
}

Entity* Scene::CreateEntity()
{
	Entity* entity = new Entity(m_Registry.create(), this);

	std::stringstream name;
	name << "Entity" << ((int)entity->m_Entity) + 1;

	entity->AddComponent<Tag>(name.str());
	entity->AddComponent<Transform>();
	entity->AddComponent<Renderer>().model;
	entities.push_back(entity);
	return entity;
}

void Scene::DestroyEntity(Entity entity)
{
	m_Registry.destroy(entity.m_Entity);
}