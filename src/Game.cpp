#include "Game.h"
#include <iostream>

Game::Game() :
m_window(sf::VideoMode(800, 480), "ArenaSFML")
,m_shape(100.f)
{
    m_shape.setFillColor(sf::Color::Green);
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
    while (m_window.isOpen())
    {
        processEvents();
        render();
    }

}

