#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP
#include <SFML/Graphics.hpp>
#include <queue>

class InputHandler
{
    private:
        sf::RenderWindow *m_window;
        std::queue<> m_Commands;

    public:
        InputHandler(sf::RenderWindow *window);
        void handleInput();

    private:
        void handleEvents();
        void handleRealTimeInput();


};

#endif // INPUTHANDLER_HPP
