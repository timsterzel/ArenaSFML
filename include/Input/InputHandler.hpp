#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP
#include <SFML/Graphics.hpp>
#include <queue>
#include "Input/QueueHelper.hpp"
#include "Input/Input.hpp"

class InputHandler
{
    private:
        sf::RenderWindow *m_window;
        sf::Vector2i m_lastMousePos;
        // Store if buttons are pressed, still pressed or released
        // Map: <Button, state>
        std::map<sf::Mouse::Button, char> m_mouseBtnStates;
        // States of joystick btns
        // First map: <joystickId, stateMap>
        // Second map: <button, state>
        std::map<unsigned int, std::map<unsigned int, char>> m_joybtnStates;

    public:
        InputHandler(sf::RenderWindow *window);
        // Store inmodified events in enventQueue and store events which get 
        // translated to inputs in inputQueue
        void handleInput(std::queue<sf::Event> &eventQueue, 
                QueueHelper<Input> &inputQueue);
        

    private:
        void handleEvents(std::queue<sf::Event> &eventQueue, 
                QueueHelper<Input> &inputQueue);
        void handleKeyboardEvents(sf::Event &event, 
                QueueHelper<Input> &inputQueue);
        void handleJoystickEvents(sf::Event &event, 
                QueueHelper<Input> &inputQueue, unsigned int joystickId);

        void handleRealTimeInput(QueueHelper<Input> &inputQueue);
        void handleKeyboardRealTimeInput(QueueHelper<Input> &inputQueue);
        void handleJoystickRealTimeInput(QueueHelper<Input> &inputQueue, 
                unsigned int joystickId);
        
        char getRealTimeMouseBtnState(sf::Mouse::Button button);
        char getRealTimeJoyBtnState(unsigned int joystickId, unsigned int button);

        sf::Vector2f getCursorPos(sf::Vector2f cursorPos, float tolerance) const;
        // Translates the joystickId to InptDevice
        InputDevice getInputDevice(unsigned int joystickId) const;

};

#endif // INPUTHANDLER_HPP
