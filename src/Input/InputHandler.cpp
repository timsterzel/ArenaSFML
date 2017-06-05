#include "Input/InputHandler.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>
#include <iostream>
#include "DebugHelpers.hpp"


InputHandler::InputHandler(sf::RenderWindow *window)
: m_window{ window }
, m_lastMousePos{ 0, 0 }
{
    m_mouseBtnStates[sf::Mouse::Button::Right] = 0;
    m_joybtnStates[0][5] = 0;
    m_joybtnStates[1][5] = 0;
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
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        handleKeyboardEvents(event, inputQueue);
        if (sf::Joystick::isConnected(0))
        {
            handleJoystickEvents(event, inputQueue, 0);
        }
        if (sf::Joystick::isConnected(1))
        {
            handleJoystickEvents(event, inputQueue, 1);
        }
        eventQueue.push(event);
        

    }
}

void InputHandler::handleKeyboardEvents(sf::Event &event,
        QueueHelper<Input> &inputQueue)
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
                inputQueue.push({ InputTypes::SPECIAL_ACTION });
            }
            // Only left button mouse pressed
            else
            {
                inputQueue.push({ InputTypes::ACTION_1 });
            }
        }
        else if (event.mouseButton.button == sf::Mouse::Right)
        {
            inputQueue.push({ InputTypes::ACTION_2 });
        }
    }
}

void InputHandler::handleJoystickEvents(sf::Event &event, 
        QueueHelper<Input> &inputQueue, unsigned int joystickId)
{
    InputDevice inputDevice{ getInputDevice(joystickId) };

    if (event.type == sf::Event::JoystickButtonPressed &&
            event.joystickButton.joystickId == joystickId)
    {
        if (event.joystickButton.button == 4)
        {
            inputQueue.push({ InputTypes::ACTION_1, inputDevice });
        }
        else if (event.joystickButton.button == 5)
        {
            inputQueue.push({ InputTypes::ACTION_2, inputDevice });
        }
    }
    else if (event.type == sf::Event::JoystickMoved)
    {
        if (event.joystickMove.axis == sf::Joystick::R)
        {
            inputQueue.push({ InputTypes::SPECIAL_ACTION, 
                    inputDevice });
        }
    }
}

void InputHandler::handleRealTimeInput(QueueHelper<Input> &inputQueue)
{
    handleKeyboardRealTimeInput(inputQueue);
    if (sf::Joystick::isConnected(0))
    {
        handleJoystickRealTimeInput(inputQueue, 0);
    }
    if (sf::Joystick::isConnected(1))
    {
        handleJoystickRealTimeInput(inputQueue, 1);
    }
}

void InputHandler::handleKeyboardRealTimeInput(QueueHelper<Input> &inputQueue)
{
    // Get the current mouse pos at the window
    const sf::Vector2i CurrentMousePosPixel{ 
        sf::Mouse::getPosition(*m_window) };
    // Convert the current window mouse pos to the world coordinates
    const sf::Vector2f CurrentMousePosWorld{ 
        m_window->mapPixelToCoords(CurrentMousePosPixel) };

    inputQueue.push({ InputTypes::MOUSE_POS, CurrentMousePosWorld });
    

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
    switch (getRealTimeMouseBtnState(sf::Mouse::Button::Right))
    {
        case 1: inputQueue.push({ InputTypes::ACTION_1_START }); 
                break;
        case 2: inputQueue.push({ InputTypes::ACTION_1_STILL }); 
                break;
        case 3: inputQueue.push({ InputTypes::ACTION_1_STOPPED }); 
                break;
    }

    m_lastMousePos.x = CurrentMousePosPixel.x;
    m_lastMousePos.y = CurrentMousePosPixel.y;
}

void InputHandler::handleJoystickRealTimeInput(QueueHelper<Input> &inputQueue, 
        unsigned int joystickId)
{
    InputDevice inputDevice{ getInputDevice(joystickId) };
    const float CursorTolerance{ 20.f };

    // Looking
    sf::Vector2f curRightPosTmp;
    curRightPosTmp.x = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::U);
    curRightPosTmp.y = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::V);
    sf::Vector2f curRightPos{ getCursorPos(curRightPosTmp, CursorTolerance) };
    if (std::abs(curRightPos.x) > CursorTolerance || 
        std::abs(curRightPos.y) > CursorTolerance)
    {
        inputQueue.push({ InputTypes::CURSOR_RIGHT_POS, inputDevice, curRightPos });
    }

    // Movement
    sf::Vector2f curLeftPosTmp;
    curLeftPosTmp.x = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X);
    curLeftPosTmp.y = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y);
    sf::Vector2f curLeftPos{ getCursorPos(curLeftPosTmp, CursorTolerance) };
    if (std::abs(curLeftPos.x) > CursorTolerance || 
        std::abs(curLeftPos.y) > CursorTolerance)
    {
        inputQueue.push({ InputTypes::CURSOR_LEFT_POS, 
                InputDevice::JOYSTICK_1, curLeftPos });
    }
    // Movement Digital axis
    if (sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovY) == -100 && 
        sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) == -100)
    {
        inputQueue.push({ InputTypes::UP_LEFT, inputDevice });
    }
    else if(sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovY) == -100 && 
            sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) == 100)
    {
        inputQueue.push({ InputTypes::UP_RIGHT, inputDevice });
    }
    else if(sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovY) == 100 && 
            sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) == -100)
    {
        inputQueue.push({ InputTypes::DOWN_LEFT, inputDevice });
    }
    else if(sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovY) == 100 && 
            sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) == 100) 
    {
        inputQueue.push({ InputTypes::DOWN_RIGHT, inputDevice });
    }
    else
    {
        if (sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovY) == -100)
        {
            inputQueue.push({ InputTypes::UP, inputDevice });
        }
        if (sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovY) == 100)
        {
            inputQueue.push({ InputTypes::DOWN, inputDevice });
        }
        if (sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) == -100)
        {
            inputQueue.push({ InputTypes::LEFT, inputDevice });
        }
        if (sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) == 100)
        {
            inputQueue.push({ InputTypes::RIGHT, inputDevice });
        }
    }

    switch (getRealTimeJoyBtnState(joystickId, 5))
    {
        case 1: inputQueue.push({ InputTypes::ACTION_1_START, inputDevice }); 
                break;
        case 2: inputQueue.push({ InputTypes::ACTION_1_STILL, inputDevice }); 
                break;
        case 3: inputQueue.push({ InputTypes::ACTION_1_STOPPED, inputDevice }); 
                break;
    }
}

char InputHandler::getRealTimeMouseBtnState(sf::Mouse::Button button)
{
    bool isPressed = { sf::Mouse::isButtonPressed(button) };
    char currentState{ m_mouseBtnStates[button] };
    char newState{ 0 };
    // Left mouse key was not pressed and is not pressed (start pressing)
    if (isPressed && currentState == 0)
    {
        newState = 1;
        m_mouseBtnStates[button] = newState;
        //inputQueue.push({ InputTypes::ACTION_1_START });
    }
    // Left mouse key was pressed and is still pressed (still pressing)
    else if (isPressed && currentState == 1)
    {
        newState = 2;
        m_mouseBtnStates[button] = newState;
        //inputQueue.push({ InputTypes::ACTION_1_STILL });
    }
    // Left mouse key was pressed and is not pressed anymore(stop pressing)
    else if (!isPressed && currentState == 2)
    {
        newState = 3;
        m_mouseBtnStates[button] = newState;
        //inputQueue.push({ InputTypes::ACTION_1_STOPPED });
    }
    // Left mouse key was not pressed and is not pressed at the moment
    else if (!isPressed && currentState == 3)
    {
        newState = 0;
        m_mouseBtnStates[button] = newState;
    }
    return newState;
}

char InputHandler::getRealTimeJoyBtnState(unsigned int joystickId, 
        unsigned int button)
{
    bool isPressed = { sf::Joystick::isButtonPressed(joystickId, button) };
    char currentState{ m_joybtnStates[joystickId][button] };
    char newState{ 0 };
    // Axis key was not pressed and is not pressed (start pressing)
    if (isPressed && currentState == 0)
    {
        newState = 1;
        m_joybtnStates[joystickId][button] = newState;
        //inputQueue.push({ InputTypes::ACTION_1_START, inputDevice });
    }
    // Axis key was pressed and is still pressed (still pressing)
    else if (isPressed && currentState == 1)
    {
        newState = 2;
        m_joybtnStates[joystickId][button] = newState;
        //inputQueue.push({ InputTypes::ACTION_1_STILL, inputDevice });
    }
    // Axis key was pressed and is not pressed anymore(stop pressing)
    else if (!isPressed && currentState == 2)
    {
        newState = 3;
        m_joybtnStates[joystickId][button] = newState;
        //inputQueue.push({ InputTypes::ACTION_1_STOPPED, inputDevice });
    }
    // Axis key was not pressed and is not pressed at the moment
    else if (!isPressed && currentState == 3)
    {
        newState = 0;
        m_joybtnStates[joystickId][button] = newState;
    }
    return newState;
}

sf::Vector2f InputHandler::getCursorPos(sf::Vector2f cursorPos, 
        float tolerance) const
{
    sf::Vector2f cursorPosNew;
    // Use a tolerance by detecting joystick movement
    if (cursorPos.x > tolerance || cursorPos.x < -tolerance)
    {
        cursorPosNew.x = cursorPos.x;
        // Add y koordinate, too. So small movements, under the tolerance are
        // only ignored when there is a movement under the tolerance rate
        // on both axis
        cursorPosNew.y = cursorPos.y;
    }
    if (cursorPos.y > tolerance || cursorPos.y < -tolerance)
    {
        cursorPosNew.y = cursorPos.y;
        cursorPosNew.x = cursorPos.x;
    }
    return cursorPos;
}

InputDevice InputHandler::getInputDevice(unsigned int joystickId) const
{
    switch(joystickId)
    {
        case 0: return InputDevice::JOYSTICK_1;
        case 1: return InputDevice::JOYSTICK_2;
    }
    // This expression should be unreachable, because only joystick ids, which are
    // definded as InputDevice should be used
    assert(false && "This block should be unreachable!");
}
