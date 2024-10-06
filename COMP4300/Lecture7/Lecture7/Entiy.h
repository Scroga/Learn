#pragma once

#include "Vec2.h"

#include <SFML/Graphics.hpp>

class Entity 
{
	Vec2f position = { 0,0 };
	Vec2f Velocity = { 0,0 };

	sf::RectangleShape shape;

public:
	Entity(Vec2f p, Vec2f v);
	Entity();

	void sMovement();

	void setPosition(Vec2f p);
	void setVelocity(Vec2f v);

	Vec2f setPosition() const;
	Vec2f setVelocity() const;
};