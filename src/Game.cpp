#include "Game.hpp"
#include "Screens/Screen.hpp"
#include "Screens/MainGameScreen.hpp"
#include "Screens/PauseScreen.hpp"
#include "Level/Level.hpp"
#include <iostream>
#include <memory>
#include <cmath>

Game::Game(const bool showStats, const bool isInDebug, const bool isMusicOn)
: m_screenHeight{ 1024 }
, m_screenWidth{ 768 }
, m_showStats{ showStats }
, m_isInDebug{ isInDebug }
, m_referenceWorldWidth{ 800 }
, m_referenceWorldHeight{ 480 }
, m_window{ sf::VideoMode{ m_screenHeight, m_screenWidth} , "ArenaSFML" }
, m_music{ }
, m_context{ isInDebug, &m_window, &m_fontHolder, &m_textureHolder, &m_shaderHolder, &m_spriteSheetMapHolder, &m_levelHolder, &m_music }
, m_isRunning{ true }
, m_isPaused{ false }
, m_renderManager{ &m_sceneGraph }
, m_dt{ 0 }
, m_fps{ 0 }
, m_averageFpsTime{ 0.f }
, m_fpsInSec{ 0.f }
, m_fpsCnt{ 0 }
, m_averageFpsPerSec{ 0 }
, m_timePoint1{ CLOCK::now() }
, m_inputHandler{ &m_window }
, m_screenStack{ m_context }
{
    if (!isMusicOn)
    {
        m_music.setVolume(0.f);
    }
    //std::unique_ptr<Screen> actualScreen = { std::make_unique<MainGameScreen>(isInDebug, this, &m_window, m_fontHolder, m_textureHolder, m_spriteSheetMapHolder) };
    //m_actualScreen = std::move(actualScreen);
    //m_window.setFramerateLimit(60);
    m_context.guiView = m_window.getView();
    m_context.gameView = m_window.getView();
    adjustShownWorldToWindowSize(m_window.getSize().x, m_window.getSize().y);
    loadFonts();
    loadTextures();
    loadShaders();
    loadLevels();
    loadMusic();
    buildScene();
    // Register all screens
    const Level &level = *(m_context.levelHolder->getLevels()[0].get());
    m_screenStack.registerScreen<MainGameScreen, Level>(ScreenID::GAME, level);
    m_screenStack.registerScreen<PauseScreen>(ScreenID::PAUSE);
    // Show Game screen
    m_screenStack.pushScreen(ScreenID::GAME);
    //m_world.buildScene();
    //m_actualScreen->buildScene();

}

Game::~Game()
{

}

void Game::adjustShownWorldToWindowSize(unsigned int windowWidth, unsigned int windowHeight)
{
    // gameView zooms
    float scaleWidth = 
        static_cast<float>(m_referenceWorldWidth) / static_cast<float>(windowWidth);
    float scaleHeight = 
        static_cast<float>(m_referenceWorldHeight) / static_cast<float>(windowHeight);
    // We have to choose one scale so the shown area from game is approximately the 
    // same (depending on the aspect ratio), but without distort the drawn world.
    float scale = std::min(scaleWidth, scaleHeight);
    sf::FloatRect visibleArea(0, 0, windowWidth * scale, windowHeight * scale);
    sf::View gameView(visibleArea);
    m_context.gameView = gameView;
    m_window.setView(m_context.gameView);
    // gui view (No zoom, only the size of the window)
    sf::View guiView(sf::FloatRect(0, 0, windowWidth, windowHeight));
    m_context.guiView = guiView;
}

void Game::loadFonts()
{
    //m_fontHolder.load(Fonts::DEFAULT, "assets/fonts/UbuntuMono-R.ttf");
    m_fontHolder.load("default", "assets/fonts/UbuntuMono-R.ttf");
}

void Game::loadTextures()
{
    m_textureHolder.load(
            "knight", "assets/sprites/warriors/knight.png");
    m_spriteSheetMapHolder.load(
            "knight", "assets/sprites/warriors/knight.txt");
    
    m_textureHolder.load(
            "runner", "assets/sprites/warriors/runner.png");
    m_spriteSheetMapHolder.load(
            "runner", "assets/sprites/warriors/runner.txt");

    m_textureHolder.load(
            "wizard", "assets/sprites/warriors/wizard.png");
    m_spriteSheetMapHolder.load(
            "wizard", "assets/sprites/warriors/wizard.txt");
    
    m_textureHolder.load(
            "fireball", "assets/sprites/attacks/fireball.png");
    m_spriteSheetMapHolder.load(
            "fireball", "assets/sprites/attacks/fireball.txt");
    
    m_textureHolder.load(
            "level", "assets/sprites/tiles/level.png");
    m_spriteSheetMapHolder.load(
            "level", "assets/sprites/tiles/level.txt");
}

void Game::loadShaders()
{
    // Dont load shaders, if there are not supportet
    if (!sf::Shader::isAvailable())
    {
        std::cerr << "Shaders not supported" << std::endl;
        return;
    }
    m_shaderHolder.load<sf::Shader::Type>("grayscale", "assets/shaders/grayscale.frag", sf::Shader::Fragment);
}

void Game::loadLevels()
{
    m_levelHolder.load("assets/level/level1.lvl");
}

void Game::loadMusic()
{
    m_music.add("gametheme01", 
            "assets/sounds/themes/Juhani_Junkala_-_Epic_Boss_Battle.ogg");
}

void Game::buildScene()
{
    m_txtStatFPS.setFont(m_fontHolder.get("default"));
	m_txtStatFPS.setCharacterSize(12);
	m_txtStatFPS.setFillColor(sf::Color::White);
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

    m_averageFpsTime += m_dt;
    m_fpsInSec += m_fps;
    m_fpsCnt++;
    if (m_averageFpsTime >= 1.f)
    {
        m_averageFpsPerSec = m_fpsInSec / m_fpsCnt + 0.5f;
        m_averageFpsTime = 0.f;
        m_fpsInSec = 0.f;
        m_fpsCnt = 0;
    }
    m_txtStatFPS.setString("FPS: " + std::to_string(m_averageFpsPerSec) + " (" 
            + std::to_string(m_fps) + ")");
}


void Game::handleInput()
{
    std::queue<sf::Event> eventQueue;
    m_inputHandler.handleInput(eventQueue, m_inputQueue);
    while(!m_inputQueue.isEmpty())
    {
        Input input{ m_inputQueue.pop() };
        switch (input.getInputType())
        {
            case InputTypes::WINDOW_RESIZED :
                adjustShownWorldToWindowSize(
                        m_window.getSize().x, m_window.getSize().y);
                m_screenStack.windowSizeChanged();
                break;
            case InputTypes::LOST_FOCUS :
                m_isPaused = true;
                break;
            case InputTypes::GAINED_FOCUS :
                m_isPaused = false;
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
        // Let world class translate the input to commands, but only when the game 
        // is not paused
        if (!m_isPaused)
        {
            //m_world.translateInput(input, m_dt);
            //m_actualScreen->handleInput(input, m_dt);
            m_screenStack.handleInput(input, m_dt);
        }
    }
    
    while(!eventQueue.empty())
    {
        sf::Event event{ eventQueue.front() };
        eventQueue.pop();
        m_screenStack.handleEvent(event, m_dt);
    }   
}

void Game::update()
{
    if (!m_isPaused)
    {
        //m_actualScreen->update(m_dt);
        m_screenStack.update(m_dt);
        /*
        m_world.safeSceneNodeTrasform();
        //m_world.controlWorldEntities();
        m_world.handleCommands(m_dt);
        m_world.update(m_dt);
        m_world.handleCollision(m_dt);
        */
        m_sceneGraph.removeDestroyed();
        m_sceneGraph.update(m_dt);
    }
}

void Game::render()
{
    m_window.clear();
    //m_world.render();
    //m_actualScreen->render();
    m_screenStack.render();
    sf::View oldView{ m_window.getView() };
    m_window.setView(m_context.guiView);
    m_window.draw(m_renderManager);
    if (m_showStats)
    {
        m_window.draw(m_txtStatFPS);
    }
    m_window.setView(oldView);
    m_window.display();
}




