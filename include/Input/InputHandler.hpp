#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP
#include <SFML/Graphics.hpp>
#include "Input/QueueHelper.hpp"
#include "Input/Input.hpp"

class InputHandler
{
    private:
        sf::RenderWindow *m_window;
        sf::Vector2i m_lastMousePos;

    public:
        InputHandler(sf::RenderWindow *window);

        void handleInput(QueueHelper<Input> &inputQueue);

    private:
        void handleEvents(QueueHelper<Input> &inputQueue);
        void handleRealTimeInput(QueueHelper<Input> &inputQueue);


};

#endif // INPUTHANDLER_HPP
