#include"Scene.h"
#include"Components.h"

Scene::Scene()
{
	//Create An Entity
	entt::entity entity1 = m_Registry.create();

	//place entity1 inside registry
	m_Registry.emplace<Transform>(entity1);

	auto s = m_Registry.view<Transform>();
}

Scene::~Scene()
{
}
