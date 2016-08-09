#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "Resources/SpriteSheetMapLoader.hpp"
int main()
{
    //SpriteSheetMapLoader::loadRectData("assets/sprites/Warriors/knight.txt");
    Game game(true, true);
    game.run();

    return 0;
}
