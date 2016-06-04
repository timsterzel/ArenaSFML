#include "InputHandler.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Calc.hpp"

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
        else if (event.type == sf::Event::Resized)
        {
            // Do nothing at the moment
        }
        else if (event.type == sf::Event::LostFocus)
        {
            // Do nothing at the moment
        }
        else if (event.type == sf::Event::GainedFocus)
        {
            // Do nothing at the moment
        }

    }
}

void InputHandler::handleRealTimeInput(CommandQueue &commandQueue)
{
    const sf::Vector2i UnitVecX(1, 0);
    const sf::Vector2i WindowCenter(static_cast<int>(m_window->getSize().x / 2), static_cast<int>(m_window->getSize().y / 2));
    const sf::Vector2i CurrentMousePos = { sf::Mouse::getPosition(*m_window) };
    /*  The angle which should be calculated have the coordinate systems midpoint a the center of the window,
     *   so we have to translate the mouse position so its relativ to the center of the window */
    const sf::Vector2i TranslatedMousePos = { CurrentMousePos - WindowCenter };
    // Calculate angle between the unit vector and the translated mouse position
    const float Angle = { Calc::radToDeg(Calc::getVec2Angle<sf::Vector2i, sf::Vector2i>(UnitVecX, TranslatedMousePos)) };
    const float AngleSigned = TranslatedMousePos.y < 0 ? -Angle : Angle;
    if (CurrentMousePos != m_lastMousePos)
    {
        commandQueue.push({ CommandTypes::ROTATE, WorldObjectType::Player, { AngleSigned, 0.f } });
    }

    std::cout << " mouse angle: " << AngleSigned << std::endl;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        commandQueue.push({ CommandTypes::MOVE_UP, WorldObjectType::Player });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        commandQueue.push({ CommandTypes::MOVE_DOWN, WorldObjectType::Player });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        commandQueue.push({ CommandTypes::MOVE_LEFT, WorldObjectType::Player });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        commandQueue.push({ CommandTypes::MOVE_RIGHT, WorldObjectType::Player });
    }

    m_lastMousePos.x = CurrentMousePos.x;
    m_lastMousePos.y = CurrentMousePos.y;
    /*
    else
    {
        m_playerWarrior->setCommand(Commands::NONE);
    }
    */
}
