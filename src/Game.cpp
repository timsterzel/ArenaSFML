#include "Game.hpp"
#include <iostream>
#include <memory>


Game::Game(const bool showStats, const bool isInDebug)
: m_screenHeight{ 800 }
, m_screenWidth{ 480 }
, m_showStats{ showStats }
, m_isInDebug{ isInDebug }
, m_window{ sf::VideoMode{ m_screenHeight, m_screenWidth} , "ArenaSFML" }
, m_isRunning{ true }
, m_renderManager{ &m_sceneGraph }
, m_dt{ 0 }
, m_fps{ 0 }
, m_timePoint1{ CLOCK::now() }
, m_inputHandler{ &m_window }
, m_world{ isInDebug, &m_window, m_fontHolder, m_textureHolder, m_spriteSheetMapHolder }
{
    m_window.setFramerateLimit(60);
    loadFonts();
    loadTextures();
    buildScene();
    m_world.buildScene();
}

void Game::loadFonts()
{
    m_fontHolder.load(Fonts::DEFAULT, "assets/fonts/UbuntuMono-R.ttf");
}

void Game::loadTextures()
{
    //sf::Rect<int> rect;
    //m_textureHolder.load<sf::Rect<int>>(Textures::KNIGHT, "assets/sprites/knight.png", rect);
    m_textureHolder.load(Textures::KNIGHT, "assets/sprites/warriors/knight.png");
    m_spriteSheetMapHolder.load(Textures::KNIGHT, "assets/sprites/warriors/knight.txt");
    m_textureHolder.load(Textures::WIZARD, "assets/sprites/warriors/wizard.png");
    m_spriteSheetMapHolder.load(Textures::WIZARD, "assets/sprites/warriors/wizard.txt");
    m_textureHolder.load(Textures::CHESS_WHITE, "assets/sprites/chess_white.png");
}

void Game::buildScene()
{
    m_txtStatFPS.setFont(m_fontHolder.get(Fonts::DEFAULT));
	m_txtStatFPS.setCharacterSize(12);
	m_txtStatFPS.setColor(sf::Color::White);
}

void Game::run()
{
    while (m_window.isOpen() && m_isRunning)
    {
        determineDeltaTime();
        handleInput();
        update();
        render();
    }
}

void Game::determineDeltaTime()
{
    CLOCK::time_point timePoint2 = { CLOCK::now() };
    std::chrono::duration<float> timeSpan = { timePoint2 - m_timePoint1 };
    m_timePoint1 = CLOCK::now();
    // Get deltaTime as float in seconds
    m_dt = std::chrono::duration_cast<std::chrono::duration<float,std::ratio<1>>> (timeSpan).count();
    m_fps = 1.f / m_dt;
    m_txtStatFPS.setString("FPS: " + std::to_string(m_fps));
}


void Game::handleInput()
{
    m_inputHandler.handleInput(m_inputQueue);
    while(!m_inputQueue.isEmpty())
    {
        Input input = m_inputQueue.pop();
        if (m_isInDebug)
        {
            switch (input.getInputType())
            {
                case InputTypes::D1 :

                    break;
                case InputTypes::D2 :
                    // Show /hide statistics
                    m_showStats = !m_showStats;
                    break;
                case InputTypes::D3 :

                    break;
                case InputTypes::D4 :

                    break;
                default:
                    break;
            }
        }
        // Let world class translate the input to commands
        m_world.translateInput(input, m_dt);
    }
}

void Game::update()
{
    m_world.safeSceneNodeTrasform();
    //m_world.controlWorldEntities();
    m_world.handleCommands(m_dt);
    m_world.update(m_dt);
    m_world.handleCollision(m_dt);
    m_sceneGraph.removeDestroyed();
    m_sceneGraph.update(m_dt);
}

void Game::render()
{
    //std::cout << "Render" << std::endl;
    m_window.clear();
    m_window.draw(m_renderManager);
    m_world.render();
    if (m_showStats)
    {
        m_window.draw(m_txtStatFPS);
    }
    m_window.display();
}



