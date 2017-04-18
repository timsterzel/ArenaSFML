#include <SFML/Graphics.hpp>
//#include "libs/GUI-SFML/include/GUI-SFML.hpp"
#include <iostream>
#include "Game.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    //gsf::GUIEnvironment environment( window );
	bool soundEnabled{ false };

    Game game(false, true, soundEnabled);
    game.run();

    return 0;
}
