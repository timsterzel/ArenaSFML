#include <SFML/Graphics.hpp>
#include "libs/GUI-SFML/include/GUI-SFML.hpp"
#include <iostream>
#include "Game.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    gsf::GUIEnvironment environment( window );

    Game game(false, true);
    game.run();

    return 0;
}
