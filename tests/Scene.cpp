#include"Scene.h"
#include"Components.h"
#include"Entity.h"

Scene::Scene()
{
	std::cout << "Scene initialized..." << std::endl;
}

Scene::~Scene()
{
	std::cout << "Scene Out of Scope" << std::endl;
}

void Scene::CreateEntity(std::string name)
{
	Entity tempEntt(m_Registry.create());
	m_Registry.emplace<Vec3>(tempEntt.m_Entity, 1.0f, 1.0f, 1.0f);
	m_Registry.emplace<Tag>(tempEntt.m_Entity, "Entity 1");
}
