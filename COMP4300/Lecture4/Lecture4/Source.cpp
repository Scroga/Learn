#include <iostream>
#include <SFML/Graphics.hpp>

class AShape
{
public:
	sf::CircleShape circle;
	sf::RectangleShape rect;
	float speedX, speedY;

};

int main(int argc, char * argv[])
{
	const int wHeight = 720;
	const int wWidth = 1280;
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML window");
	window.setFramerateLimit(60);

	/*
	int r = 0;
	int g = 255;
	int b = 100;

	sf::CircleShape circle1(50);

	circle1.setFillColor(sf::Color(r,g,b));
	circle1.setPosition(300.0f, 300.0f);
	float circleMoveSpeed = 1.0f;
	std::vector<sf::CircleShape> circles;
	circles.push_back(circle1);

	sf::Font myFont;

	if(!myFont.loadFromFile("fonts/tech.ttf"))
	{
		std::cerr << "Could not load font\n";
		exit(-1);
	}

	sf::Text text("Some text", myFont, 24);
	text.setPosition(0, wHeight - (float)text.getCharacterSize());
	*/

	std::vector<sf::RectangleShape> rectangles;

	for (int x = 0; x < 45; x++)
	{
		for (int y = 0; y < 30; y++)
		{
			sf::RectangleShape rect(sf::Vector2f(20, 20));
			rect.setPosition(x * 20, y * 20);
			rect.setFillColor(sf::Color(x * 5, y * 5, 0));

			rectangles.push_back(rect);
		}
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				std::cout << "Window is closed" << "\n";
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				std::cout << "Key pressed with code = " << event.key.code << "\n";

				//if (event.key.code == sf::Keyboard::X)
			}
		}
		float sx = 0.5;
		float sy = 0.5;

		window.clear();

		//circle.setPosition(circle.getPosition().x + sx, circle.getPosition().y + sy);


		for (auto& rect : rectangles)
		{
			//rect.rotate(0.2f);
			window.draw(rect);
		}


		window.display();
	}

	std::cout << "Now, it doesnt work(" << "\n";

	return 0;
}