#ifndef SCENE_H
#define SCENE_H

#include"ENTT/entt.hpp"
#include "Components.h"

class Scene
{
public:
	Scene();
	~Scene();
private:
	entt::registry m_Registry;
};
#endif