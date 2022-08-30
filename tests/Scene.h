#ifndef SCENE_H
#define SCENE_H

#include"ENTT/entt.hpp"
#include "Components.h"
//#include"Entity.h"

class Entity; 

class Scene
{
public:
	Scene();
	~Scene();

	Entity CreateEntity();
	entt::registry m_Registry;

	//friend class Entity;
private:
};
#endif