#include "SFML/Graphics.hpp"
#include "Vec2.h"

#include <iostream>

int main(int argc, char * argv[])
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Lecture7");
	window.setFramerateLimit(60);

	sf::CircleShape circle;
	circle.setRadius(window.getSize().y / 2);
	circle.setOrigin(window.getSize().x / 2, window.getSize().y / 2);
	circle.setPointCount(4);
	circle.setFillColor(sf::Color::Black);
	circle.setPosition(window.getSize().x / 2, window.getSize().y / 2);

	Vec2f f(2.0f, 3.0f);
	Vec2i i(4, 3);

	f.print();
	i.print();

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
		}


		sf::Vector2f i(1.0f, 2.0f);

		window.clear(sf::Color::White);
		window.draw(circle);
		window.display();
	}

	return 0;
}

/* Centered AABB overlap

class cTransform : public Component
{
public:
	Vec2 position	= { 0.0, 0.0}; // position is the center of rectangle
	Vec2 prevPos	= { 0.0, 0.0};
	Vec2 scale		= { 1.0, 1.0};
	Vec2 velocity	= { 0.0, 0.0};
	float angle		= 0;

};
class cBoundingBox : public Component
{
public:
	Vec2 size;
	Vec2 halfSize;
	CBoundingBox(const Vec2 & s)
		: size(s), halfSize(s.x / 2, s.y / 2) {}
};

Vec2 delta = abs (pos1 - pos2); // abs(x1 - x2), abs(y1 - y2)

Vec2 overlap = halfSize1 + halfSize2 - delat;

if(overlap > 0) -> collide

*/

/*
Creating action object

if(event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
{
	// if the current scene does not have an action associated with this key, skip the event
	if (currentScene()->getActionMap().find(event.key.coode) == currentScene()->getActionMap().end()) { continue; }

	// determine start or and action by whether it was key pres or release
	const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";

	// look up the action and send the action to the scene
	currentScene()->doAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));
*/

/*
Doing Scene action

void Scene_Menu::sDoAction(cosnt Action& action)
{
	if(action.type() == "START")
	{
		if(action.name() == "UP)
		{
			if(m_selectMenuIndex > 0) { m_selectMenuIndex--; }
			else { m_selectMenuIndex = m_menuStrings.size() - 1; }
		}
		else if(action.name() == "DOWN)
		{
			m_selectMenuIndex = (m_selectMenuIndex + 1) % m_menuStrings.size();
		}
		else if(action.name() = "PLAY)
		{
			m_game->ChangeScene("PLAY", std::make_shared<Scene_Play>(m_game, _levelPaths[m_selectedMenuIndex]));
		}
		else if(action.name() == "QUIT")
		{
			onEnd();
		}
}

*/