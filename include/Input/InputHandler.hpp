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
        // Used to check if the  right mouse click was pressed first time, 
        // is still pressed, or is stop pressed
        char m_rightMouseClickState;

    public:
        InputHandler(sf::RenderWindow *window);
        // Store inmodified events in enventQueue and store events which get 
        // translated to inputs in inputQueue
        void handleInput(std::queue<sf::Event> &eventQueue, 
                QueueHelper<Input> &inputQueue);

    private:
        void handleEvents(std::queue<sf::Event> &eventQueue, 
                QueueHelper<Input> &inputQueue);
        void handleRealTimeInput(QueueHelper<Input> &inputQueue);
        void handleRealTimeRightClick(QueueHelper<Input> &inputQueue);

};

#endif // INPUTHANDLER_HPP
