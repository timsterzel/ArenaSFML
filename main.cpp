#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"

int main()
{
    Game game(true, true);
    game.run();

    return 0;
}

