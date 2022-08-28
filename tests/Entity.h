#ifndef ENTITY_H
#define ENTITY_H

#include"ENTT/entt.hpp"
#include"Scene.h"
#include<vector>

class Entity
{
public:
	Entity();
	~Entity();
private:
	entt::entity m_Entity;
};
#endif