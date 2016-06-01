#include "InputHandler.hpp"
#include <SFML/Graphics.hpp>

InputHandler::InputHandler(sf::RenderWindow *window)
: m_window{window}
{

}

void InputHandler::handleInput()
{
    handleEvents();
    handleRealTimeInput();
}

void InputHandler::handleEvents()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window->close();
        }
    }
}

void InputHandler::handleRealTimeInput()
{

}
