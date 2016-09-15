#ifndef SCREENSTACK_HPP
#define SCREENSTACK_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <vector>
#include "Screens/Screen.hpp"

class ScreenStack : private sf::NonCopyable
{
    public:
        enum class Action
        {
            Push,
            Pop,
            Clear,
        };

    private:
        std::vector<Screen::Ptr> m_stack;

        Screen::Context m_context;


    public:
        explicit ScreenStack(Screen::Context context);

        ~ScreenStack();

        virtual void handleInput(Input input, float dt);
        //void controlWorldEntities();
        //void handleCommands(float dt);
        virtual void update(float dt);

        virtual void render();

};

#endif // SCREENSTACK_HPP
