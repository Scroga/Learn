#pragma once

#include "Vec2.h"
#include "SFML/Graphics.hpp"

class CTransform
{
public:
	Vec2	position = { 0.0, 0.0 };
	Vec2	velocity = { 0.0, 0.0 };
	float	angle = 0;

	CTransform(const Vec2& p, const Vec2& v, const float a)
		: position(p), velocity(v), angle(a) {}

	CTransform(const Vec2& p, const Vec2& v)
		: position(p), velocity(v) {}
};

class CShape
{
public:
	sf::CircleShape circle;

	CShape(const float radius, const float points, const sf::Color& fill, const sf::Color& outline, const float thickness)
		: circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}

	// give this shape random fill color
	CShape(const float radius, const float points, const sf::Color& outline, const float thickness)
		: circle(radius, points)
	{
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;

		circle.setFillColor(sf::Color(r, g, b));
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
};

class CCollision
{
public:
	float radius = 0;
	bool  destroy = true;   // destroy an entity after it collides with another entity

	CCollision(const float r, bool d)
		: radius(r), destroy(d) {}

	CCollision(const float r)
		: radius(r) {}
};

class CInput
{
public:
	bool up = false;
	bool left = false;
	bool right = false;
	bool down = false;
	bool shoot = false;

	CInput() {}
};

class CScore
{
public:
	int score = 0;

	CScore(int s)
		: score(s) {}
};

class CLifespan
{
public:
	int remaining = 0;	// amount of lifespan remaining on the entity
	int total = 0;		// the total initial amout of lifespan

	CLifespan(int t)
		: remaining(t), total(t) {}
};
