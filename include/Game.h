#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <chrono>

typedef std::chrono::high_resolution_clock CLOCK;

class Game
{
    private:
        sf::RenderWindow m_window;
        sf::CircleShape m_shape;
        sf::Font m_fontDefault;
        sf::Text m_txtStatFPS;

        // Delta time
        float m_dt;
        float m_fps;
        CLOCK::time_point m_timePoint1;
        // Options
        bool m_showStats;



    private:
        void determineDeltaTime();
        void processEvents();
        void render();

    public:
        Game(bool showStats);
        void run();
};

#endif // GAME_H
