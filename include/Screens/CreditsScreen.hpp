#ifndef CREDITSSCREEN_HPP
#define CREDITSSCREEN_HPP
#include "libs/GUI-SFML/include/GUI-SFML.hpp"
#include "Screens/Screen.hpp"
#include <SFML/Graphics.hpp>

class CreditsScreen : public Screen
{
    private:
        gsf::GUIEnvironment m_guiEnvironment;

    public:
        CreditsScreen(ScreenStack *screenStack, Context &context);

        virtual void buildScene();
        
        virtual bool handleInput(Input &input, float dt) override;
        virtual bool handleEvent(sf::Event &event, float dt) override;

        virtual bool update(float dt);

        virtual void render();

        virtual void windowSizeChanged();
};

#endif // !CREDITSSCREEN_HPP
