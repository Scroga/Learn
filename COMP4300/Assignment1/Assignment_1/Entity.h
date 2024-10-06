#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Entity
{
private: 
	sf::Vector2f m_speed;
	sf::Vector2f m_position;
	std::string m_name;
public:

	Entity(std::string name, sf::Vector2f position, sf::Vector2f speed)
		: m_name(name)
		, m_position(position)
		, m_speed(speed)
	{}

	void printStatus() const
	{
		std::cout << "\nName      " << m_name << std::endl;
		std::cout << "\nPosition  " << m_position.x << " : " << m_position.y << std::endl;
		std::cout << "Speed     " << m_speed.x << " : " << m_speed.y << std::endl;
	}

	void invertX() { m_speed.x *= -1; }
	void invertY() { m_speed.y *= -1; }

	sf::Vector2f getNewPosition()
	{
		m_position += m_speed;
		return m_position;
	}

	void increaseSpeed(float factor)
	{
		m_speed *= factor;
	}

	void updatePosition(float x, float y);
};

class Circle : public Entity
{
public:
	sf::CircleShape shape;
	Circle	//Circle constructor
	(
		std::string name,
		sf::Vector2f position,
		sf::Vector2f speed,
		sf::Color color,
		float radius
	)
		: Entity(name, position, speed)
	{
		shape.setPosition(position);
		shape.setRadius(radius);
		shape.setFillColor(color);
	};
	
	void updatePosition(float x, float y)
	{
		if (shape.getPosition().x < 0 || (shape.getPosition().x + (shape.getRadius() * 2)) > x)
			invertX();

		if (shape.getPosition().y < 0 || (shape.getPosition().y + (shape.getRadius() * 2)) > y)
			invertY();

		shape.setPosition(getNewPosition());
	}
};

class Rectangle : public Entity
{
public:
	sf::RectangleShape shape;

	Rectangle	//Rectangle constructor
	(
		std::string name,
		sf::Vector2f position,
		sf::Vector2f speed,
		sf::Color color,
		sf::Vector2f size
	)
		: Entity(name, position, speed)
	{
		shape.setPosition(position);
		shape.setSize(size);
		shape.setFillColor(color);
	};

	void updatePosition(float x, float y)
	{
		if (shape.getPosition().x < 0 || (shape.getPosition().x + shape.getSize().x) > x)
			invertX();

		if (shape.getPosition().y < 0 || (shape.getPosition().y + shape.getSize().y) > y)
			invertY();

		shape.setPosition(getNewPosition());
	}
};