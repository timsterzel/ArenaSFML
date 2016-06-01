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
    /*
    else
    {
        m_playerWarrior->setCommand(Commands::NONE);
    }
    */
}
