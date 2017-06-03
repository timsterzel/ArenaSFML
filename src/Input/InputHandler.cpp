#include "Input/InputHandler.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "DebugHelpers.hpp"

InputHandler::InputHandler(sf::RenderWindow *window)
: m_window{ window }
, m_lastMousePos{ 0, 0 }
, m_rightMouseClickState{ 0 }
{

}

void InputHandler::handleInput(std::queue<sf::Event> &eventQueue, 
        QueueHelper<Input> &inputQueue)
{
    handleEvents(eventQueue, inputQueue);
    handleRealTimeInput(inputQueue);
}

void InputHandler::handleEvents(std::queue<sf::Event> &eventQueue, 
        QueueHelper<Input> &inputQueue)
{
    /*
    if (sf::Joystick::isConnected(0))
    {
        std::cout << "Joystick 0 is connected\n";
    }
    */
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        eventQueue.push(event);
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
            inputQueue.push({ InputTypes::LOST_FOCUS });
        }
        else if (event.type == sf::Event::GainedFocus)
        {
            inputQueue.push({ InputTypes::GAINED_FOCUS });
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
            else if (event.key.code == sf::Keyboard::F5)
            {
                inputQueue.push({ InputTypes::CONSOLE });
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                inputQueue.push({ InputTypes::PAUSE });
                inputQueue.push({ InputTypes::BACK });
            }
            else if (event.key.code == sf::Keyboard::F5)
            {
                inputQueue.push({ InputTypes::PAUSE });
            }

        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // LControl + Left Button pressed
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                {
                    inputQueue.push({ InputTypes::LCONTROL_LEFT_CLICK });
                }
                // Only left button mouse pressed
                else
                {
                    inputQueue.push({ InputTypes::LEFT_CLICK });
                }
            }
            else if (event.mouseButton.button == sf::Mouse::Right)
            {
                inputQueue.push({ InputTypes::RIGHT_CLICK });
            }
        }
        // JOYSTICK
        else if (event.type == sf::Event::JoystickButtonPressed)
        {
            std::cout << "---Joystick---\n";
            std::cout << "ID: " << event.joystickButton.joystickId << std::endl;
            std::cout << "Button: " << event.joystickButton.button << std::endl;
            std::cout << "---!Joystick---\n";
        }
        else if (event.type == sf::Event::JoystickMoved)
        {
            if (event.joystickMove.axis == sf::Joystick::PovY)
            {
                std::cout << "X axis moved!" << std::endl;
                std::cout << "joystick id: " << event.joystickMove.joystickId 
                    << std::endl;
                std::cout << "new position: " << event.joystickMove.position 
                    << std::endl;
            }
        }

    }
}

void InputHandler::handleRealTimeInput(QueueHelper<Input> &inputQueue)
{
    // Get the current mouse pos at the window
    const sf::Vector2i CurrentMousePosPixel{ 
        sf::Mouse::getPosition(*m_window) };
    // Convert the current window mouse pos to the world coordinates
    const sf::Vector2f CurrentMousePosWorld{ 
        m_window->mapPixelToCoords(CurrentMousePosPixel) };

    inputQueue.push({ InputTypes::CURSOR_POS, CurrentMousePosWorld });
    

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) 
            && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        inputQueue.push({ InputTypes::UP_LEFT });
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) 
            && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        inputQueue.push({ InputTypes::UP_RIGHT });
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) 
            && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        inputQueue.push({ InputTypes::DOWN_LEFT });
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) 
            && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        inputQueue.push({ InputTypes::DOWN_RIGHT });
    }
    // Dont handle W A S D separately, 
    // when there are pairs like W+A or W+D or S+A or S+D
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

    // ------------------------------------------------------------------
    // Joystick 1
    sf::Vector2f curJoy1PosTmp;
    curJoy1PosTmp.x = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
    curJoy1PosTmp.y = sf::Joystick::getAxisPosition(0, sf::Joystick::V);
    sf::Vector2f curJoy1Pos;
    // Use a tolerance by detecting joysrick movement
    bool wasCur1Moved{ false };
    float joy1Tolerance{ 20.f };
    if (curJoy1PosTmp.x > joy1Tolerance || curJoy1PosTmp.x < -joy1Tolerance)
    {
        curJoy1Pos.x = curJoy1PosTmp.x;
        // Add y koordinate, too. So small movements, under the tolerance are
        // only ignored when there is a movement under the tolerance rate
        // on both axis
        curJoy1Pos.y = curJoy1PosTmp.y;
        wasCur1Moved = true;
    }
    if (curJoy1PosTmp.y > joy1Tolerance || curJoy1PosTmp.y < -joy1Tolerance)
    {
        curJoy1Pos.y = curJoy1PosTmp.y;
        curJoy1Pos.x = curJoy1PosTmp.x;
        wasCur1Moved = true;
    }
    if (wasCur1Moved) 
    {
        inputQueue.push({ InputTypes::CURSOR_POS_JOY, 
                InputDevice::JOYSTICK_1, curJoy1Pos });

        std::cout << "Joystick Cursor: " 
            << DebugHelpers::toString(curJoy1Pos) << std::endl;
    }

    //inputQueue.push({ InputTypes::CURSOR_POS, CurrentMousePosWorld });
    
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) == -100 && 
        sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) == -100)
    {
        //inputQueue.push({ InputTypes::UP_LEFT, InputDevice::JOYSTICK_1 });
        inputQueue.push({ InputTypes::UP_LEFT });
    }
    else if(sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) == -100 && 
            sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) == 100)
    {
        inputQueue.push({ InputTypes::UP_RIGHT });
    }
    else if(sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) == 100 && 
            sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) == -100)
    {
        inputQueue.push({ InputTypes::DOWN_LEFT });
    }
    else if(sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) == 100 && 
            sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) == 100) 
    {
        inputQueue.push({ InputTypes::DOWN_RIGHT });
    }
    else
    {
        if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) == -100)
        {
            inputQueue.push({ InputTypes::UP });
        }
        if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) == 100)
        {
            inputQueue.push({ InputTypes::DOWN });
        }
        if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) == -100)
        {
            inputQueue.push({ InputTypes::LEFT });
        }
        if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) == 100)
        {
            inputQueue.push({ InputTypes::RIGHT });
        }
    }


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
