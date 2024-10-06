#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVector;

int main(int argc, char * argv[])
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "MyWindow");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		//window.draw();
		window.display();
	}
	return 0;
}