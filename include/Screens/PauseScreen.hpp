#ifndef PAUSESCREEN_HPP
#define PAUSESCREEN_HPP
#include "libs/GUI-SFML/include/GUI-SFML.hpp"
#include "Screens/Screen.hpp"
#include <SFML/Graphics.hpp>

class PauseScreen : public Screen
{
    private:
        gsf::GUIEnvironment m_guiEnvironment;
        gsf::CheckBoxWidget* m_checkBoxMusic;
        gsf::CheckBoxWidget* m_checkBoxSound;
    public:
        PauseScreen(ScreenStack *screenStack, Context &context);

        virtual ~PauseScreen();

        virtual void buildScene();
        
        virtual void windowSizeChanged();

        virtual bool handleInput(Input &input, float dt) override;
        virtual bool handleEvent(sf::Event &event, float dt) override;

        virtual bool update(float dt);

        virtual void render();
};

#endif // PAUSESCREEN_HPP
