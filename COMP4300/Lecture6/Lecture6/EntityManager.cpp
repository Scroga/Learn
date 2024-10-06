#include "EntityManager.h"

////////////////////////////////////////////////////////////
std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	// give each entity an increasing integer id
	auto e = std::make_shared<Entity>(tag, m_totalEntities++);
	m_toAdd.push_back(e);
	return e;
}

////////////////////////////////////////////////////////////
void EntityManager::update()
{
	for(auto e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}

	for(auto e : m_entities)
	{
		// if e is dead, remove it from m_entities
		// if e is dead, remove it from m_entityMap[e->tag()]

		// removeif function
	}
	m_toAdd.clear();
}