#include <iostream>
#include <vector>
#include <map>
#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map   <std::string, EntityVec>	 EntityMap;

class EntityManager
{
	EntityVec m_entities;
	EntityVec m_toAdd;
	EntityMap m_entityMap;
	size_t    m_totalEntities = 0;

public:
	EntityManager();
	void update();
	std::shared_ptr<Entity> addEntity(const std::string& tag);
	EntityVec& getEntities();
	EntityVec& getEntities(const std::string& tag);

};

// shared_ptr ????

////////////////////////////////////////////////////////////

/*
EntityManager m_entities;

void spawnEnemy()
{
	auto e		  = m_entities.addEntity("enemy")

	auto e = std::shared_ptr<Entity>(new Entity(args)) // hacky code line (because of private constructor)

	e->cTransform = std::make_shared<CTransform>(args);
	e->cShape	  = std::make_shared<cShape>(args);
}

void collisions()
{
	for(auto b : m_entities.getEntities("bullet")
		for(auto e : m_entities.getEntites("enemy")
			if(Physics::CheckCollision(b, e));
				b->destroy(); e->destroy();
}

*/