#include "Game.hpp"
#include <iostream>
#include "Warrior.hpp"

Game::Game(bool showStats)
: m_screenHeight{800}
, m_screenWidth{480}
, m_showStats{showStats}
, m_window{sf::VideoMode{m_screenHeight, m_screenWidth}, "ArenaSFML"}
, m_isRunning{true}
, m_dt{0}
, m_fps{0}
, m_timePoint1{CLOCK::now()}
, m_playerWarrior{nullptr}
{
    //m_shape.setFillColor(sf::Color::Green);
    m_window.setFramerateLimit(60);
    if (!m_fontDefault.loadFromFile("fonts/UbuntuMono-R.ttf"))
	{
		std::cout << "Error cannot load Font" << std::endl;
	}
	m_txtStatFPS.setFont(m_fontDefault);
	m_txtStatFPS.setCharacterSize(12);
	m_txtStatFPS.setColor(sf::Color::White);

    //sf::Rect<int> rect;
    //m_textureHolder.load<sf::Rect<int>>(Textures::KNIGHT, "assets/sprites/knight.png", rect);
    m_textureHolder.load(Textures::KNIGHT, "assets/sprites/knight.png");
    std::unique_ptr<Warrior> warrior(new Warrior(Textures::KNIGHT, m_textureHolder));
    m_playerWarrior = warrior.get();
    m_playerWarrior->setPosition(m_screenHeight / 2.f, m_screenWidth / 2.f);
    m_playerWarrior->setVelocity(0.f, -30.f);
    m_sceneGraph.attachChild(std::move(warrior));
}

void Game::run()
{
    while (m_window.isOpen() && m_isRunning)
    {
        determineDeltaTime();
        processEvents();
        handleInput();
        update();
        render();
    }
}

void Game::determineDeltaTime() {
    CLOCK::time_point timePoint2 = { CLOCK::now() };
    std::chrono::duration<float> timeSpan = { timePoint2 - m_timePoint1 };
    m_timePoint1 = CLOCK::now();
    // Get deltaTime as float in seconds
    m_dt = std::chrono::duration_cast<std::chrono::duration<float,std::ratio<1>>> (timeSpan).count();
    m_fps = 1.f / m_dt;
    m_txtStatFPS.setString("FPS: " + std::to_string(m_fps));
}

void Game::processEvents()
{
    // One time events
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
    }
    // Real time input
}

void Game::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_playerWarrior->setCommand(Commands::MOVE_UP);
    }
    else
    {
        m_playerWarrior->setCommand(Commands::NONE);
    }

}

void Game::update()
{
    m_sceneGraph.update(m_dt);
}

void Game::render()
{
    std::cout << "Render" << std::endl;
    m_window.clear();
    m_window.draw(m_sceneGraph);
    //m_window.draw(m_testSprite);
    m_window.draw(m_txtStatFPS);
    m_window.display();
}



