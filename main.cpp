#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"

int main()
{
    Game game(false, true);
    game.run();

    return 0;
}
