#ifndef MAINMENUSCREEN_HPP
#define MAINMENUSCREEN_HPP
#include "libs/GUI-SFML/include/GUI-SFML.hpp"
#include "Screens/Screen.hpp"
#include <SFML/Graphics.hpp>

class MainMenuScreen : public Screen
{
    private:
        gsf::GUIEnvironment m_guiEnvironment;
    public:
        MainMenuScreen(ScreenStack *screenStack, Context &context);

        virtual ~MainMenuScreen();

        virtual void buildScene();
        
        virtual void windowSizeChanged();

        virtual bool handleInput(Input &input, float dt) override;
        virtual bool handleEvent(sf::Event &event, float dt) override;

        virtual bool update(float dt);

        virtual void render();
};

#endif // !MAINMENUSCREEN_HPP
