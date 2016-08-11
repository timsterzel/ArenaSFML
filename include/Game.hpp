#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include <map>
#include "World.hpp"
#include "Components/Warrior.hpp"
#include "Components/EnumWorldObjectTypes.hpp"
#include "Components/SceneNode.hpp"
#include "Input/QueueHelper.hpp"
#include "Input/InputHandler.hpp"
#include "Input/EnumInputTypes.hpp"
#include "Render/RenderManager.hpp"
#include "Resources/ResourceHolder.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Resources/SpriteSheetMapHolder.hpp"

typedef std::chrono::high_resolution_clock CLOCK;

class Game
{
    private:
        // Options
        unsigned int m_screenHeight;
        unsigned int m_screenWidth;
        bool m_showStats;
        bool m_isInDebug;

        sf::RenderWindow m_window;
        sf::Font m_fontDefault;
        sf::Text m_txtStatFPS;

        bool m_isRunning;

        SceneNode m_sceneGraph;
        RenderManager m_renderManager;

        // Delta time
        float m_dt;
        float m_fps;
        CLOCK::time_point m_timePoint1;
        // Assets
        ResourceHolder<sf::Font, Fonts> m_fontHolder;
        ResourceHolder<sf::Texture, Textures> m_textureHolder;
        SpriteSheetMapHolder m_spriteSheetMapHolder;

        // The game class handle all inputs which get later translated to commands
        QueueHelper<Input> m_inputQueue;
        InputHandler m_inputHandler;

        World m_world;

    private:
        void loadFonts();
        void loadTextures();
        void buildScene();
        void determineDeltaTime();
        void handleInput();
        void update();
        void render();

    public:
        Game(const bool showStats, const bool isInDebug);
        void run();
};

#endif // GAME_HPP
