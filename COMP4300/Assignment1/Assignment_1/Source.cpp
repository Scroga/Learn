#include <iostream>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Entity.h"

template <typename T>
void drawVector(sf::RenderWindow& window, std::vector<T>& vector)
{
	for (auto& entity : vector)
	{
		window.draw(entity.shape);
		entity.updatePosition(window.getSize().x, window.getSize().y);
	}
}

int main(int argc, char * argv[])
{
	const std::string filename = "config.txt";


	////////////////////////////////////////////////////////////
	//	Vectors
	////////////////////////////////////////////////////////////

	std::vector<Rectangle> rectangles;
	std::vector<Circle> circles;


	////////////////////////////////////////////////////////////
	//	Load Entities from file
	////////////////////////////////////////////////////////////

	std::ifstream fin("data/" + filename);
	std::string shapeType, shapeName;

	float X, Y;				// position
	float SX, SY;			// speed
	int R, G, B;			// color
	float W, H;				// size
	float Radius;			// radius

	unsigned int wWidth, wHeight;	// window size
	
	// Font

	while(fin >> shapeType)
	{
		if(shapeType == "Window")
		{
			fin >> wWidth >> wHeight;
			std::cout << "Window: "<< wWidth << " " << wHeight << std::endl;
		}
		else if(shapeType == "Font")
		{
			// Font
		}
		else if(shapeType == "Circle")
		{
			fin >> shapeName >> X >> Y >> SX >> SY >> R >> G >> B >> Radius;
			Circle circleEntity(shapeName, sf::Vector2f(X,Y), sf::Vector2f(SX, SY), sf::Color(R, G, B), Radius);
			circleEntity.printStatus();
			circles.push_back(circleEntity);
		}
		else if(shapeType == "Rectangle")
		{
			fin >> shapeName >> X >> Y >> SX >> SY >> R >> G >> B >> W >> H;
			Rectangle rectEntity(shapeName, sf::Vector2f(X, Y), sf::Vector2f(SX, SY), sf::Color(R, G, B), sf::Vector2f(W, H));
			rectEntity.printStatus();
			rectangles.push_back(rectEntity);
		}
	}


	////////////////////////////////////////////////////////////
	//	Window
	////////////////////////////////////////////////////////////

	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "MyWindow");
	window.setFramerateLimit(60);


	////////////////////////////////////////////////////////////
	//	mainLoop
	////////////////////////////////////////////////////////////

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			////////////////////////////////////////////////////////////
			//	Events
			////////////////////////////////////////////////////////////

			if(event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				float factor = 1.0f;

				if(event.key.code == sf::Keyboard::Z)
					factor = 1.5f;

				if (event.key.code == sf::Keyboard::X)
					factor = 0.5f;

				for (auto& rect : rectangles)
					rect.increaseSpeed(factor);

				for (auto& circle : circles)
					circle.increaseSpeed(factor);
			}
		}
		
		window.clear();
		drawVector(window, rectangles);
		drawVector(window, circles);
		window.display();
	}
	return 0;
}
