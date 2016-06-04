#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include "Warrior.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "CommandQueue.hpp"
#include "InputHandler.hpp"
#include "EnumWorldObjectTypes.hpp"


typedef std::chrono::high_resolution_clock CLOCK;

class Game
{
    private:
        // Use of enum instead of enum class, so we can use Layer as int
        enum Layers
        {
            BACKGROUND,
            MAIN,
            STATISTICS,
            COUNT
        };


    private:
        // Options
        unsigned int m_screenHeight;
        unsigned int m_screenWidth;
        bool m_showStats;

        sf::RenderWindow m_window;
        sf::Font m_fontDefault;
        sf::Text m_txtStatFPS;

        bool m_isRunning;

        SceneNode m_sceneGraph;
        std::array<SceneNode*, Layers::COUNT> m_sceneLayers;

        // Delta time
        float m_dt;
        float m_fps;
        CLOCK::time_point m_timePoint1;
        // Assets
        ResourceHolder<sf::Texture, Textures> m_textureHolder;

        CommandQueue m_commandQueue;
        InputHandler m_inputHandler;

        Warrior *m_playerWarrior;

    private:
        void loadFonts();
        void loadTextures();
        void buildScene();
        void determineDeltaTime();
        void handleInput();
        void update();
        void render();

    public:
        Game(bool showStats);
        void run();
};

#endif // GAME_HPP
