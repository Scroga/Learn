#include <SFML/Graphics.hpp>
#include "Game.h"

int main(int argc, char * argv[])
{
	Game g("data/config.txt");
	g.run();
}
