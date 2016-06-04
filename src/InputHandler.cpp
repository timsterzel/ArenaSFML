#include "InputHandler.hpp"
#include <SFML/Graphics.hpp>

InputHandler::InputHandler(sf::RenderWindow *window)
: m_window{window}
{

}

void InputHandler::handleInput(CommandQueue &commandQueue)
{
    handleEvents(commandQueue);
    handleRealTimeInput(commandQueue);
}

void InputHandler::handleEvents(CommandQueue &commandQueue)
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

void InputHandler::handleRealTimeInput(CommandQueue &commandQueue)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        commandQueue.push({CommandTypes::MOVE_UP, WorldObjectType::Player});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        commandQueue.push({CommandTypes::MOVE_DOWN, WorldObjectType::Player});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        commandQueue.push({CommandTypes::MOVE_LEFT, WorldObjectType::Player});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        commandQueue.push({CommandTypes::MOVE_RIGHT, WorldObjectType::Player});
    }
    /*
    else
    {
        m_playerWarrior->setCommand(Commands::NONE);
    }
    */
}
