#include <SFML/Graphics.hpp>
//#include "libs/GUI-SFML/include/GUI-SFML.hpp"
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
