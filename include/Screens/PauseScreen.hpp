#ifndef PAUSESCREEN_HPP
#define PAUSESCREEN_HPP
#include "Screens/Screen.hpp"
#include <SFML/Graphics.hpp>

class PauseScreen : public Screen
{
    private:
        sf::Text m_txtPaused;

    public:
        PauseScreen(ScreenStack *screenStack, Context &context);

        virtual ~PauseScreen();

        virtual void buildScene();

        virtual bool handleInput(Input &input, float dt) override;
        virtual bool handleEvent(sf::Event &event, float dt) override;

        virtual bool update(float dt);

        virtual void render();
};

#endif // PAUSESCREEN_HPP
