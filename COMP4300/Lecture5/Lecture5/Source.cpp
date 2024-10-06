#include <iostream>
#include <SFML/Graphics.hpp>
//#include <SFML/System/Vector2.hpp>
#include "Vec2.h"

/*
class Vec2
{
public:
	float x = 0;
	float y = 0;

	Vec2() {}
	Vec2(float xin, float yin)
		: x(xin)
		, y(yin)
	{}

	Vec2 operator + (const Vec2& rhs) const
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}

	void operator += (const Vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}

	Vec2& add(const Vec2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vec2& scale(float s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	Vec2& rotate(float deg)
	{
		return *this;
	}


	void print() const
	{
		std::cout << x << " " << y << std::endl;
	}
};
*/

int main(int argc, char * argv[])
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "MyWindow");
	window.setFramerateLimit(60);

	sf::CircleShape circle(50.f, 4);
	circle.setFillColor(sf::Color::Red);
	//circle.setPosition(sf::Vector2f(100, 100));

	Vec2f v1(100, 200);
	Vec2f v2(50, 75);
	Vec2f v3(1000, 2000);

	//float dist = v1.dist(v2);
	//std::cout << dist << std::endl;
	//v1.add(v2).add(v3).scale(5).rotate(10);

	//v1.print();
	(v1 + v2).print();
	std::cout << "dist " << v1.dist(v2) << std::endl;
	std::cout << "dist " << v1.dist(v2) << std::endl;

	Vec2f vector(1, 1);
	//vector.rotate(90).print();

	//stupidRotation(vector, 90).print();

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
		//window.draw(circle);
		window.display(); 
	}
	return 0;
}

// srand(time(null)) 