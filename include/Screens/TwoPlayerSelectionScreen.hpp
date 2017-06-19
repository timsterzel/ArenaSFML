#ifndef TWOPLAYERSELECTIONSCREEN_HPP
#define TWOPLAYERSELECTIONSCREEN_HPP
#include "libs/GUI-SFML/include/GUI-SFML.hpp"
#include "Screens/Screen.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class TwoPlayerSelectionScreen : public Screen
{
    private:
        // <LevelName, LevelID>
        std::map<std::string, std::string> m_levels;
        
        gsf::GUIEnvironment m_guiEnvironment;
        
        gsf::CheckBoxWidget *m_p1KnightCheckBox; 
        gsf::CheckBoxWidget *m_p1RunnerCheckBox; 
        gsf::CheckBoxWidget *m_p1WizardCheckBox; 
        gsf::CheckBoxWidget *m_p2KnightCheckBox; 
        gsf::CheckBoxWidget *m_p2RunnerCheckBox; 
        gsf::CheckBoxWidget *m_p2WizardCheckBox; 
        gsf::ListBoxWidget *m_levelListBox;

        std::vector<gsf::CheckBoxWidget*> m_p1WarriorCheckBoxes;
        std::vector<gsf::CheckBoxWidget*> m_p2WarriorCheckBoxes;

    public:
        TwoPlayerSelectionScreen(ScreenStack *screenStack, Context &context);

        virtual ~TwoPlayerSelectionScreen();

        virtual void buildScene();
        
        virtual void windowSizeChanged();

        virtual bool handleInput(Input &input, float dt) override;
        virtual bool handleEvent(sf::Event &event, float dt) override;

        virtual bool update(float dt);

        virtual void render();

    private:
        void handleLevelLoading();

        void deselectDevicesWhichAreNotGiven(gsf::Widget *widget, 
                std::vector<gsf::CheckBoxWidget*> &checkBoxes);

        WorldObjectTypes getPlayer1WarriorType() const;
        WorldObjectTypes getPlayer2WarriorType() const;
};

#endif // !TWOPLAYERSELECTIONSCREEN_HPP
