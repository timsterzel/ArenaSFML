#include "Game.hpp"
#include <iostream>
#include <memory>
#include <cmath>

Game::Game(const bool showStats, const bool isInDebug)
: m_screenHeight{ 1024 }
, m_screenWidth{ 768 }
, m_showStats{ showStats }
, m_isInDebug{ isInDebug }
, m_referenceWorldWidth{ 800 }
, m_referenceWorldHeight{ 480 }
, m_window{ sf::VideoMode{ m_screenHeight, m_screenWidth} , "ArenaSFML" }
, m_isRunning{ true }
, m_isPaused{ false }
, m_renderManager{ &m_sceneGraph }
, m_dt{ 0 }
, m_fps{ 0 }
, m_timePoint1{ CLOCK::now() }
, m_inputHandler{ &m_window }
, m_world{ isInDebug, &m_window, m_fontHolder, m_textureHolder, m_spriteSheetMapHolder }
{
    m_window.setFramerateLimit(60);
    adjustShownWorldToWindowSize(m_window.getSize().x, m_window.getSize().y);
    loadFonts();
    loadTextures();
    buildScene();
    m_world.buildScene();
}

void Game::adjustShownWorldToWindowSize(unsigned int windowWidth, unsigned int windowHeight)
{
    float scaleWidth = static_cast<float>(m_referenceWorldWidth) / static_cast<float>(windowWidth);
    float scaleHeight = static_cast<float>(m_referenceWorldHeight) / static_cast<float>(windowHeight);
    // We have to choose one scale so the shown area from game is approximately the same (depending on the aspect ratio), but without distort
    // the drawn world.
    float scale = std::min(scaleWidth, scaleHeight);
    sf::FloatRect visibleArea(0, 0, windowWidth * scale, windowHeight * scale);
    sf::View view(visibleArea);
    m_window.setView(view);
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
        switch (input.getInputType())
        {
            case InputTypes::WINDOW_RESIZED :
                adjustShownWorldToWindowSize(m_window.getSize().x, m_window.getSize().y);
                break;
            case InputTypes::LOST_FOCUS :
                m_isPaused = true;
                std::cout << "Lost Focus" << std::endl;
                break;
            case InputTypes::GAINED_FOCUS :
                m_isPaused = false;
                std::cout << "Gained Focus" << std::endl;
                break;
            default:
                break;
        }
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
        // Let world class translate the input to commands, bit only when the game is not paused
        if (!m_isPaused)
        {
            m_world.translateInput(input, m_dt);
        }
    }
}

void Game::update()
{
    if (!m_isPaused)
    {
        m_world.safeSceneNodeTrasform();
        //m_world.controlWorldEntities();
        m_world.handleCommands(m_dt);
        m_world.update(m_dt);
        m_world.handleCollision(m_dt);
        m_sceneGraph.removeDestroyed();
        m_sceneGraph.update(m_dt);
    }
}

void Game::render()
{
    m_window.clear();
    m_window.draw(m_renderManager);
    m_world.render();
    if (m_showStats)
    {
        m_window.draw(m_txtStatFPS);
    }
    m_window.display();
}



