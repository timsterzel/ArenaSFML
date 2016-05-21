#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
    private:
        sf::RenderWindow m_window;
        sf::CircleShape m_shape;


    private:
        void processEvents();
        void render();

    public:
        Game();
        void run();
};

#endif // GAME_H
