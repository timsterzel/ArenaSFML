#include "Game.h"
#include <iostream>

Game::Game(bool showStats):
m_window(sf::VideoMode(800, 480), "ArenaSFML")
,m_shape(100.f)
,m_dt(0)
,m_fps(0)
,m_timePoint1(CLOCK::now())
,m_showStats(showStats)
{
    m_shape.setFillColor(sf::Color::Green);
    m_window.setFramerateLimit(60);
    if (!m_fontDefault.loadFromFile("fonts/UbuntuMono-R.ttf"))
	{
		std::cout << "Error cannot load Font" << std::endl;
	}
	m_txtStatFPS.setFont(m_fontDefault);
	m_txtStatFPS.setCharacterSize(12);
	m_txtStatFPS.setColor(sf::Color::White);

}

void Game::determineDeltaTime() {
    CLOCK::time_point timePoint2 = CLOCK::now();
    std::chrono::duration<float> timeSpan = timePoint2 - m_timePoint1;
    m_timePoint1 = CLOCK::now();
    // Get deltaTime as float in seconds
    m_dt = std::chrono::duration_cast<std::chrono::duration<float,std::ratio<1>>> (timeSpan).count();
    m_fps = 1.f / m_dt;
    m_txtStatFPS.setString("FPS: " + std::to_string(m_fps));
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
    }
}

void Game::render()
{
    std::cout << "Render" << std::endl;
    m_window.clear();
    m_window.draw(m_shape);
    m_window.draw(m_txtStatFPS);
    m_window.display();
}

void Game::run()
{
    while (m_window.isOpen())
    {
        determineDeltaTime();
        processEvents();
        render();
    }

}

