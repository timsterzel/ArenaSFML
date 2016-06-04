#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP
#include <SFML/Graphics.hpp>
#include <queue>
#include "Command.hpp"
#include "CommandQueue.hpp"

class InputHandler
{
    private:
        sf::RenderWindow *m_window;
        sf::Vector2i m_lastMousePos;

    public:
        InputHandler(sf::RenderWindow *window);

        void handleInput(CommandQueue &commandQueue);

    private:
        void handleEvents(CommandQueue &commandQueue);
        void handleRealTimeInput(CommandQueue &commandQueue);


};

#endif // INPUTHANDLER_HPP
