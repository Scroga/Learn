#include <iostream>

class Entity
{
	const size_t	   m_id	   = 0;
	const std::string  m_tag   = "Default";
	bool			   m_alive = true;

public:
	//std::shared_ptr<CTransform> cTransform;
	//std::shared_ptr<CName>      cName;
	//std::shared_ptr<CShape>     cShape;
	//std::shared_ptr<CBBox>      cBBox;

	Entity(const std::string& tag, size_t id);
	void destroy() { m_alive = false; }
	const std::string& tag() { return m_tag; }
};

/*
void GameEngine::mainLoop()
{
	m_entityManager.update();
	sUserInput();
	sMovement();
	sCollision();
	sRender();
	m_currentFrame++;


void GameEngine::sEnemySpawner()
{
	// manually creating entities no longer possible
	// each of these will be a compiler error

	auto e = std::make_shared<Entity>(args);
	auto e = new Entity(args);
	Entity e(args);

	// must use EntityManager to create entities

	auto e = m_entityManager.addEntity(args);

*/