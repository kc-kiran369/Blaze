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

Entity Scene::CreateEntity()
{
	Entity tempEntt(m_Registry.create(), this);
	return tempEntt;
}

void Scene::DestroyEntity(Entity entity)
{
	m_Registry.destroy(entity.m_Entity);
}
