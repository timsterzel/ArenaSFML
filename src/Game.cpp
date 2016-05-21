#include "Game.h"
#include <iostream>

Game::Game() :
m_window(sf::VideoMode(800, 480), "ArenaSFML")
,m_shape(100.f)
{
    m_shape.setFillColor(sf::Color::Green);
    m_window.setFramerateLimit(60);
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
    m_window.display();

}

void Game::run()
{
    CLOCK::time_point timePoint1 = CLOCK::now();
    while (m_window.isOpen())
    {
        CLOCK::time_point timePoint2 = CLOCK::now();
        std::chrono::duration<float> timeSpan = timePoint2 - timePoint1;
        timePoint1 = CLOCK::now();
        // Get deltaTime as float in seconds
        float dt = std::chrono::duration_cast<std::chrono::duration<float,std::ratio<1>>> (timeSpan).count();
        float fps = 1.f / dt;
        std::cout << "DeltaTime: " << dt <<  " FPS: " << fps << std::endl;

        processEvents();
        render();
    }

}

