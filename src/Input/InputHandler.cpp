#include "Input/InputHandler.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

InputHandler::InputHandler(sf::RenderWindow *window)
: m_window{window}
, m_lastMousePos{ 0, 0 }
, m_rightMouseClickState{ 0 }
{

}

void InputHandler::handleInput(QueueHelper<Input> &inputQueue)
{
    handleEvents(inputQueue);
    handleRealTimeInput(inputQueue);
}

void InputHandler::handleEvents(QueueHelper<Input> &inputQueue)
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
            inputQueue.push({ InputTypes::WINDOW_RESIZED });
        }
        else if (event.type == sf::Event::LostFocus)
        {
            // Do nothing at the moment
        }
        else if (event.type == sf::Event::GainedFocus)
        {
            // Do nothing at the moment
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::F1)
            {
                inputQueue.push({ InputTypes::D1 });
            }
            else if (event.key.code == sf::Keyboard::F2)
            {
                inputQueue.push({ InputTypes::D2 });
            }
            else if (event.key.code == sf::Keyboard::F3)
            {
                inputQueue.push({ InputTypes::D3 });
            }
            else if (event.key.code == sf::Keyboard::F4)
            {
                inputQueue.push({ InputTypes::D4 });
            }

        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                inputQueue.push({ InputTypes::LEFT_CLICK });
            }
        }

    }
}

void InputHandler::handleRealTimeInput(QueueHelper<Input> &inputQueue)
{
    // Get the current mouse pos at the window
    const sf::Vector2i CurrentMousePosPixel = { sf::Mouse::getPosition(*m_window) };
    // Convert the current window mouse pos to the world coordinates
    const sf::Vector2f CurrentMousePosWorld = { m_window->mapPixelToCoords(CurrentMousePosPixel) };

    inputQueue.push({ InputTypes::CURSOR_POS, CurrentMousePosWorld });
    /*
    if (CurrentMousePos != m_lastMousePos)
    {
        const sf::Vector2i WindowCenter(static_cast<int>(m_window->getSize().x / 2), static_cast<int>(m_window->getSize().y / 2));
        const sf::Vector2i TranslatedMousePos = { CurrentMousePos - WindowCenter };
        const sf::Vector2f TranslatedMousePosF(static_cast<sf::Vector2f>(TranslatedMousePos));
        inputQueue.push({ InputTypes::TRANSLATED_CURSOR_POS, TranslatedMousePosF });


    }
    */

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        inputQueue.push({ InputTypes::UP_LEFT });
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        inputQueue.push({ InputTypes::UP_RIGHT });
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        inputQueue.push({ InputTypes::DOWN_LEFT });
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        inputQueue.push({ InputTypes::DOWN_RIGHT });
    }
    // Dont handle W A S D separately, when there are pairs like W+A or W+D or S+A or S+D
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            inputQueue.push({ InputTypes::UP });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            inputQueue.push({ InputTypes::DOWN });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            inputQueue.push({ InputTypes::LEFT });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            inputQueue.push({ InputTypes::RIGHT });
        }
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        inputQueue.push({ InputTypes::UP_A });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        inputQueue.push({ InputTypes::DOWN_A });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        inputQueue.push({ InputTypes::LEFT_A });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        inputQueue.push({ InputTypes::RIGHT_A });
    }
    handleRealTimeRightClick(inputQueue);

    m_lastMousePos.x = CurrentMousePosPixel.x;
    m_lastMousePos.y = CurrentMousePosPixel.y;
}

void InputHandler::handleRealTimeRightClick(QueueHelper<Input> &inputQueue)
{
    bool isPressed = { sf::Mouse::isButtonPressed(sf::Mouse::Right) };
    // Left mouse key was not pressed and is not pressed (start pressing)
    if (isPressed && m_rightMouseClickState == 0)
    {
        m_rightMouseClickState = 1;
        inputQueue.push({ InputTypes::RIGHT_CLICK_START });
    }
    // Left mouse key was pressed and is still pressed (still pressing)
    else if (isPressed && m_rightMouseClickState == 1)
    {
        m_rightMouseClickState = 2;
        inputQueue.push({ InputTypes::RIGHT_CLICK_STILL });
    }
    // Left mouse key was pressed and is not pressed anymore(stop pressing)
    else if (!isPressed && m_rightMouseClickState == 2)
    {
        m_rightMouseClickState = 3;
        inputQueue.push({ InputTypes::RIGHT_CLICK_STOPED });
    }
    // Left mouse key was not pressed and is not pressed at the moment
    else if (!isPressed && m_rightMouseClickState == 3)
    {
        m_rightMouseClickState = 0;
    }
}
