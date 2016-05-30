#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"

typedef std::chrono::high_resolution_clock CLOCK;

class Game
{
    private:
        enum class Layers
        {
            Main,
            Statistics,
            Count
        };


        // Options
        unsigned int m_screenHeight;
        unsigned int m_screenWidth;
        bool m_showStats;

        sf::RenderWindow m_window;
        sf::Font m_fontDefault;
        sf::Text m_txtStatFPS;

        SceneNode m_sceneGraph;


        // Delta time
        float m_dt;
        float m_fps;
        CLOCK::time_point m_timePoint1;
        // Assets
        ResourceHolder<sf::Texture, Textures> m_textureHolder;



    private:
        void determineDeltaTime();
        void processEvents();
        void update();
        void render();

    public:
        Game(bool showStats);
        void run();
};

#endif // GAME_HPP
