#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "Helpers.hpp"
#include "Config/ConfigManager.hpp"

int main()
{
    /*
    ConfigManager con("assets/config.ini");
    con.printConfig();
    con.set("debug_mode", false);
    con.printConfig();
    con.saveCurrentConfigToFile("assets/tmp.ini");
    */

    Game game;
    game.run();
    return 0;
}
