#include "Game.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#define HIGHEST_COLOR_VALUE  255
#define COMPLETE_ANGLE		 360
#define M_PI				 3.14

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path)
{
	// seed the random number generator with the current time
	srand(static_cast<unsigned int>(time(0)));

	// default window configurations
	int		wWidth = 1280;
	int		wHeight = 720;
	int		wFramerateLimit = 60;
	bool	isFullScreen = false;

	// default font configurations
	std::string		fPath; // there is no default font in SFML
	int				fColorR = 255;
	int				fColorG = 255;
	int				fColorB = 255;
	int				fSize = 24;

	// read configuration file
	std::ifstream fin(path);
	if (!fin.is_open())
	{
		std::cerr << "Failed to open file \"" << path << "\"" << std::endl;
		exit(-1);
	}

	std::string keyword;

	while (fin >> keyword)
	{
		if (keyword == "Window")
		{
			fin >> wWidth
				>> wHeight
				>> wFramerateLimit
				>> isFullScreen;
		}

		if (keyword == "Font")
		{
			fin >> fPath
				>> fSize
				>> fColorR >> fColorG >> fColorB;
		}

		if (keyword == "Player")
		{
			fin >> m_playerConfig.SR
				>> m_playerConfig.CR
				>> m_playerConfig.S
				>> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB
				>> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB
				>> m_playerConfig.OT
				>> m_playerConfig.V;
		}

		if (keyword == "Enemy")
		{
			fin >> m_enemyConfig.SR
				>> m_enemyConfig.CR
				>> m_enemyConfig.SMIN
				>> m_enemyConfig.SMAX
				>> m_enemyConfig.OR >> m_enemyConfig.OG >> m_enemyConfig.OB
				>> m_enemyConfig.OT
				>> m_enemyConfig.VMIN
				>> m_enemyConfig.VMAX
				>> m_enemyConfig.L
				>> m_enemyConfig.SI;
		}

		if (keyword == "Bullet")
		{
			fin >> m_bulletConfig.SR
				>> m_bulletConfig.CR
				>> m_bulletConfig.S
				>> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB
				>> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB
				>> m_bulletConfig.OT
				>> m_bulletConfig.V
				>> m_bulletConfig.L
				>> m_bulletConfig.CD;
		}

		if (keyword == "SpecialWeapon")
		{
			fin >> m_specialWeaponConfig.SR
				>> m_specialWeaponConfig.CR
				>> m_specialWeaponConfig.L
				>> m_specialWeaponConfig.S
				>> m_specialWeaponConfig.CD;
		}

		if (keyword == "UltimateAbilitiy")
		{
			fin >> m_ultimateAbilitiyConfig.S
				>> m_ultimateAbilitiyConfig.P
				>> m_ultimateAbilitiyConfig.L;
		}
	}

	// window
	if (isFullScreen)
		m_window.create(sf::VideoMode(wWidth, wHeight), "Game", sf::Style::Fullscreen);
	else
		m_window.create(sf::VideoMode(wWidth, wHeight), "Game");

	m_window.setFramerateLimit(wFramerateLimit);

	// font
	if (!m_font.loadFromFile(fPath))
	{
		std::cerr << "Failed to open font \"" << fPath << "\"" << std::endl;
		exit(-1);
	}

	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color(fColorR, fColorG, fColorB));
	m_text.setCharacterSize(fSize);
	m_text.setPosition((float)m_text.getCharacterSize(), 0);

	spawnPlayer();
}

void Game::run()
{
	// main gameLoop
	while (m_running)
	{
		m_entities.update();

		if (!m_paused)
		{
			sEnemySpawner();
			sMovement();
			sCollision();
			sLifespan();
			sScore();

			// increment the current frame
			m_currentFrame++;
		}

		sRender();
		sUserInput();
	}
	m_window.close();
}

void Game::pause()
{
	m_paused = !m_paused;
}

void Game::stop()
{
	m_running = false;
}

#pragma region Systems
void Game::sMovement()
{
	// Player movement
	m_player->cTransform->velocity = { 0,0 };

	// check if the button is pressed and if the player doesn't go off the screen
	if (m_player->cInput->up && m_player->cTransform->position.y > m_player->cCollision->radius)
		m_player->cTransform->velocity.y = -m_playerConfig.S;

	if (m_player->cInput->down && m_player->cTransform->position.y < (m_window.getSize().y - m_player->cCollision->radius))
		m_player->cTransform->velocity.y = m_playerConfig.S;

	if (m_player->cInput->left && m_player->cTransform->position.x > m_player->cCollision->radius)
		m_player->cTransform->velocity.x = -m_playerConfig.S;

	if (m_player->cInput->right && m_player->cTransform->position.x < (m_window.getSize().x - m_player->cCollision->radius))
		m_player->cTransform->velocity.x = m_playerConfig.S;

	m_player->cTransform->position += m_player->cTransform->velocity;


	// Entities movement
	for (auto& e : m_entities.getEntities())
	{
		if (e->tag() != "player")
		{
			// checks if the entity touches the right or left border  of the screen
			if ((e->cTransform->position.x - e->cCollision->radius) < 0 || (e->cTransform->position.x + e->cCollision->radius) > m_window.getSize().x)
			{
				e->cTransform->velocity.x *= -1;
			}
			// checks if the player touches the top or bottom border  of the screen
			if ((e->cTransform->position.y - e->cCollision->radius) < 0 || (e->cTransform->position.y + e->cCollision->radius) > m_window.getSize().y)
			{
				e->cTransform->velocity.y *= -1;
			}
			e->cTransform->position += e->cTransform->velocity;
		}

		// set the position of the shape based on the entity's transform->pos
		e->cShape->circle.setPosition(e->cTransform->position.x, e->cTransform->position.y);

		e->cTransform->angle += 2.5f;

		// set the rotation of the shape 
		e->cShape->circle.setRotation(e->cTransform->angle);
	}
}

void Game::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		// this event triggers when the window is closed
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}

		// this event triggers when a key is pressed
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = true;
				break;

			case sf::Keyboard::S:
				m_player->cInput->down = true;
				break;

			case sf::Keyboard::A:
				m_player->cInput->left = true;
				break;

			case sf::Keyboard::D:
				m_player->cInput->right = true;
				break;

			case sf::Keyboard::Q:
				spawnUltimateAbilitiy(m_player);
				break;

			case sf::Keyboard::P:
				pause();
				break;

			case::sf::Keyboard::Escape:
				stop();
				break;

			default: break;
			}
		}

		// this event is triggered when a key is released
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = false;
				break;

			case sf::Keyboard::S:
				m_player->cInput->down = false;
				break;

			case sf::Keyboard::A:
				m_player->cInput->left = false;
				break;

			case sf::Keyboard::D:
				m_player->cInput->right = false;
				break;

			default: break;
			}
		}

		// this event is triggered when a mouse button is pressed
		if (event.type == sf::Event::MouseButtonPressed && !m_paused)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				spawnSpecialWeapon(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
			}
		}
	}
}

void Game::sLifespan()
{
	for (auto& e : m_entities.getEntities())
	{
		if (e->cLifespan)
		{
			if (e->cLifespan->remaining < 1)
			{
				e->destroy();
			}
			else
			{
				e->cLifespan->remaining--;

				// change the alpha channel of the fill color and the thickness color proportionally
				sf::Color currentFillColor = e->cShape->circle.getFillColor();
				sf::Color currentThicknessColor = e->cShape->circle.getOutlineColor();

				// calculate the new alpha value based on remaining lifespan
				float alphaRatio = float(e->cLifespan->remaining) / e->cLifespan->total;

				// sf::Uin8 can store values from 0 to 255
				currentFillColor.a = static_cast<sf::Uint8>(HIGHEST_COLOR_VALUE * alphaRatio);
				currentThicknessColor.a = static_cast<sf::Uint8>(HIGHEST_COLOR_VALUE * alphaRatio);

				e->cShape->circle.setFillColor(currentFillColor);
				e->cShape->circle.setOutlineColor(currentThicknessColor);
			}
		}
	}
}

void Game::sRender()
{
	m_window.clear();

	for (auto& e : m_entities.getEntities())
	{
		// draw the entity's sf::CircleShape
		m_window.draw(e->cShape->circle);
	}

	m_window.draw(m_text);

	m_window.display();
}

void Game::sEnemySpawner()
{
	if ((m_currentFrame - m_lastEnemySpawnTime) > m_enemyConfig.SI)
	{
		spawnEnemy();
	}
}

void Game::sCollision()
{
	auto bullets = m_entities.getEntities("bullet");
	auto enemies = m_entities.getEntities("enemy");
	auto smallEnemies = m_entities.getEntities("smallEnemy");

	for (auto e : enemies)
	{
		// Two entities collide if the distance between them is less than the sum of their collision radii
		if (m_player->cTransform->position.distance(e->cTransform->position) < (m_player->cCollision->radius + e->cCollision->radius))
		{
			m_player->destroy();
			spawnSmallEnemies(e);
			e->destroy();
			spawnPlayer();
		}

		for (auto b : bullets)
		{
			if (e->cTransform->position.distance(b->cTransform->position) < (e->cCollision->radius + b->cCollision->radius))
			{
				if (b->cCollision->destroy) b->destroy();

				m_player->cScore->score += (e->cShape->circle.getPointCount() * 100);
				spawnSmallEnemies(e);
				e->destroy();
			}
		}
	}

	for (auto e : smallEnemies)
	{
		for (auto b : bullets)
		{
			if (e->cTransform->position.distance(b->cTransform->position) < (e->cCollision->radius + b->cCollision->radius))
			{
				if (b->cCollision->destroy) b->destroy();

				m_player->cScore->score += (e->cShape->circle.getPointCount() * 200);
				e->destroy();
			}
		}
	}

}

void Game::sScore()
{
	m_score = m_player->cScore->score;

	if (m_score > m_bestScore)
		m_bestScore = m_score;

	// set current score to the m_text, so it can be drawn on the screen
	m_text.setString("best score: " + std::to_string(m_bestScore) + "\n" + "score: " + std::to_string(m_score));
}

#pragma endregion

#pragma region Mechanics
// spawns the main character
void Game::spawnPlayer()
{
	// create every entity by calling EntityManager.addEntity(tag)
	// this returns a std::shared_ptr<Entity>, so we use 'auto' to save typing
	auto player = m_entities.addEntity("player");

	// screen center coordinates
	float mx = m_window.getSize().x / 2.0f;
	float my = m_window.getSize().y / 2.0f;

	// give this entity a Transform so it spawns in the middle of the screen with velocity (1, 1) and 0 angle
	player->cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(1.0f, 1.0f));

	// the entity's shape will be according to the configFile
	player->cShape = std::make_shared<CShape>(m_playerConfig.SR,
		m_playerConfig.V,
		sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB),
		sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB),
		m_playerConfig.OT);

	// add an input component to the player so that we can use inputs
	player->cInput = std::make_shared<CInput>();

	// add a score component to the player so we can count enemies killed
	player->cScore = std::make_shared<CScore>(0);

	player->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);

	// since we want this Entity to be out player, set our Game's player variable to be this Entity
	m_player = player;
}

// spawns an enemy at random position
void Game::spawnEnemy()
{
	auto enemy = m_entities.addEntity("enemy");

	// formula for generating a random number in the range of [min, max]
	// r = min + (rand() % (1 + max - min)

	// random spawn (within the screen)
	float rx = m_enemyConfig.SR + (rand() % (1 + m_window.getSize().x - (2 * m_enemyConfig.SR)));
	float ry = m_enemyConfig.SR + (rand() % (1 + m_window.getSize().y - (2 * m_enemyConfig.SR)));

	// generate random velocity by random speed (vector length) and random angle
	int vecAngleDeg = rand() % COMPLETE_ANGLE;			// angle in degrees
	float vecAngleRad = vecAngleDeg * (M_PI / 180.0f);  // convert to radians

	float vecLength = m_enemyConfig.SMIN + (rand() % int(1 + m_enemyConfig.SMAX - m_enemyConfig.SMIN)); // speed

	// give this entity a Transform so it spawns at random position(within the screen) with random velocity and 0 angle
	enemy->cTransform = std::make_shared<CTransform>(Vec2(rx, ry), Vec2(vecLength * cos(vecAngleRad), vecLength * sin(vecAngleRad)));

	// random vertex count in the range of [VMIN, VMAX]
	int vertexCount = m_enemyConfig.VMIN + (rand() % (1 + m_enemyConfig.VMAX - m_enemyConfig.VMIN));

	// the entity's shape will be according to the configFile (it spawns with random fill color)
	enemy->cShape = std::make_shared<CShape>(m_enemyConfig.SR,
		vertexCount,
		sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB),
		m_enemyConfig.OT);

	enemy->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);

	// record when the most recent enemy was spawned
	m_lastEnemySpawnTime = m_currentFrame;
}

// spawns the small enemies when a big one (input entity e) explodes
void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
	const float scaler = 2.5f; // scales the size of the small entity

	// pointCount allow us to create the correct number of smallEntities and give them the proper velocity
	int pointCount = entity->cShape->circle.getPointCount();

	for (int i = pointCount - 1; i >= 0; i--)
	{
		auto smallEnemy = m_entities.addEntity("smallEnemy");

		// generate velocity for a small enemy
		int vecAngleDeg = i * (COMPLETE_ANGLE / pointCount) + entity->cTransform->angle;
		float vecAngleRad = vecAngleDeg * (M_PI / 180.0f);

		float vecLength = entity->cTransform->velocity.length();

		Vec2 velosity = Vec2(vecLength * cos(vecAngleRad), vecLength * sin(vecAngleRad));

		// give this small enemy a Transform so it spawns at the location of the input entity with calculated velocity and its angle
		smallEnemy->cTransform = std::make_shared<CTransform>(entity->cTransform->position,
			velosity,
			entity->cTransform->angle);

		smallEnemy->cShape = std::make_shared<CShape>(entity->cShape->circle.getRadius() / scaler,
			pointCount,
			entity->cShape->circle.getFillColor(),
			entity->cShape->circle.getOutlineColor(),
			entity->cShape->circle.getOutlineThickness());

		smallEnemy->cCollision = std::make_shared<CCollision>(entity->cCollision->radius / scaler);

		// give this entity a Lifespan so that it destroys when the time is up
		smallEnemy->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.L);
	}
}

// spawns a bullet from a given entity to a target location
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& targetPos)
{
	// checks the number of frames since the last bullet was spawned
	if ((m_currentFrame - m_lastBulletSpawnTime) > m_bulletConfig.CD)
	{
		auto bullet = m_entities.addEntity("bullet");

		// calculates velocity based on the mouse position on the screen and the speed given in config file
		Vec2 velosity = targetPos - entity->cTransform->position;
		velosity.normalize();
		velosity *= m_bulletConfig.S;

		bullet->cTransform = std::make_shared<CTransform>(entity->cTransform->position, velosity);

		bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR,
			m_bulletConfig.V,
			sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
			sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB),
			m_bulletConfig.OT);

		bullet->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);

		bullet->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L);

		m_lastBulletSpawnTime = m_currentFrame;
	}
}

// spawns a special weapon from a givem entity to a target location
void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity, const Vec2& targetPos)
{
	// checks the number of frames since the last special weapon was spawned
	if ((m_currentFrame - m_lastWeaponSpawnTime) > m_specialWeaponConfig.CD)
	{
		auto bullet = m_entities.addEntity("bullet");

		Vec2 velosity = targetPos - entity->cTransform->position;
		velosity.normalize();
		velosity *= m_specialWeaponConfig.S;

		bullet->cTransform = std::make_shared<CTransform>(entity->cTransform->position, velosity);

		bullet->cShape = std::make_shared<CShape>(m_specialWeaponConfig.SR,
			m_bulletConfig.V,
			sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
			sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB),
			m_bulletConfig.OT);

		// set false as the second argument so that this entity will not be destroyed after a collision
		bullet->cCollision = std::make_shared<CCollision>(m_specialWeaponConfig.CR, false);

		bullet->cLifespan = std::make_shared<CLifespan>(m_specialWeaponConfig.L);

		m_lastWeaponSpawnTime = m_currentFrame;
	}
}

// spawns an ultimate abilitiy from a givem entity 
void Game::spawnUltimateAbilitiy(std::shared_ptr<Entity> entity)
{
	// to use this ability, we have to "buy" it for a score, so it checks the number of scores
	if (entity->cScore->score > m_ultimateAbilitiyConfig.P && !m_paused)
	{
		int bulletCount = entity->cShape->circle.getPointCount() * 2;

		for (int i = bulletCount - 1; i >= 0; i--)
		{
			auto bullet = m_entities.addEntity("bullet");

			int vecAngleDeg = i * (COMPLETE_ANGLE / bulletCount) + entity->cTransform->angle;
			float vecAngleRad = vecAngleDeg * (M_PI / 180.0f);

			float vecLength = m_ultimateAbilitiyConfig.S;
			Vec2 velosity = Vec2(vecLength * cos(vecAngleRad), vecLength * sin(vecAngleRad));

			bullet->cTransform = std::make_shared<CTransform>(entity->cTransform->position, velosity);

			bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR,
				m_bulletConfig.V,
				entity->cShape->circle.getFillColor(),
				entity->cShape->circle.getOutlineColor(),
				entity->cShape->circle.getOutlineThickness());

			bullet->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR, false);

			bullet->cLifespan = std::make_shared<CLifespan>(m_ultimateAbilitiyConfig.L);
		}

		entity->cScore->score -= m_ultimateAbilitiyConfig.P;
	}
}

#pragma endregion
