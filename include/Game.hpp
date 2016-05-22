#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <chrono>
#include "TextureHolder.hpp"

typedef std::chrono::high_resolution_clock CLOCK;

class Game
{
    private:
        sf::RenderWindow m_window;
        sf::Sprite m_testSprite;
        sf::Font m_fontDefault;
        sf::Text m_txtStatFPS;

        // Delta time
        float m_dt;
        float m_fps;
        CLOCK::time_point m_timePoint1;
        // Options
        bool m_showStats;

        // Assets
        TextureHolder m_textureHolder;



    private:
        void determineDeltaTime();
        void processEvents();
        void render();

    public:
        Game(bool showStats);
        void run();
};

#endif // GAME_HPP
