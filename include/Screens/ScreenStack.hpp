#ifndef SCREENSTACK_HPP
#define SCREENSTACK_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <vector>
#include <functional>
#include "Screens/Screen.hpp"
#include "Screens/ScreenIdentifiers.hpp"

class ScreenStack : private sf::NonCopyable
{
    public:
        enum class Action
        {
            PUSH,
            POP,
            CLEAR,
        };

    private:

        struct PendingChange
        {
            Action action;
            ScreenID screenID;

            explicit PendingChange(Action action, ScreenID screenID);
        };

    private:
        std::vector<Screen::Ptr> m_stack;
        std::vector<PendingChange> m_pendingList;
        Screen::Context &m_context;
        std::map<ScreenID, std::function<Screen::Ptr()>> m_factories;

    public:
        explicit ScreenStack(Screen::Context &context);

        ~ScreenStack();

        template <typename T>
        void registerScreen(ScreenID screenID);
        virtual void handleInput(Input &input, float dt);
        virtual void handleEvent(sf::Event &event, float dt);
        //void controlWorldEntities();
        //void handleCommands(float dt);
        virtual void update(float dt);
        virtual void render();

        void pushScreen(ScreenID screenID);
        void popScreen();
        void clearScreens();

        bool isEmpty() const;
        
        // Called when the window size changed
        void windowSizeChanged();
    private:
        Screen::Ptr createScreen(ScreenID screenID);
        // With this method we can change the stack safety.
        // So eg. a screen is not removed immediately when pop is called.
        // It gets removed when this method is called.
        void applyPendingChanges();

};

#include "Screens/ScreenStack.inl"

#endif // SCREENSTACK_HPP
