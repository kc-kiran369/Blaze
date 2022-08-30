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

Entity Scene::CreateEntity()
{
	Entity tempEntt(m_Registry.create(),this);
	return tempEntt;
}