#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "Helpers.hpp"

int main()
{
    bool soundEnabled{ false };    
    Game game(false, true, soundEnabled);
    game.run();
    return 0;
}
