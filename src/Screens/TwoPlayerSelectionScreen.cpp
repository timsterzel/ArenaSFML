#include "Screens/TwoPlayerSelectionScreen.hpp"
#include "Screens/ScreenStack.hpp"
#include "Screens/MainGameScreen.hpp"

TwoPlayerSelectionScreen::TwoPlayerSelectionScreen(ScreenStack *screenStack, Context &context)
: Screen(screenStack, context)
, m_guiEnvironment{ *context.window }
{
    buildScene();
}

TwoPlayerSelectionScreen::~TwoPlayerSelectionScreen()
{

}

void TwoPlayerSelectionScreen::buildScene()
{
    m_screenStack->pushScreen(ScreenID::GAME);
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_guiEnvironment.createScene("assets/gui/two_player_game_selection.xml");
    m_context.window->setView(oldView);
    // Player 1
    m_p1KnightCheckBox = static_cast<gsf::CheckBoxWidget*>(
            m_guiEnvironment.getWidgetByID("checkBoxWidget_p1Knight"));
    m_p1RunnerCheckBox = static_cast<gsf::CheckBoxWidget*>(
            m_guiEnvironment.getWidgetByID("checkBoxWidget_p1Runner"));    
    m_p1WizardCheckBox = static_cast<gsf::CheckBoxWidget*>(
            m_guiEnvironment.getWidgetByID("checkBoxWidget_p1Wizard"));
    m_p1WarriorCheckBoxes.push_back(m_p1KnightCheckBox);
    m_p1WarriorCheckBoxes.push_back(m_p1RunnerCheckBox);
    m_p1WarriorCheckBoxes.push_back(m_p1WizardCheckBox);
    m_p1KnightCheckBox->setIsChecked(true);
    //m_player1WarriorCheckBoxes:  
    m_p1KnightCheckBox->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        // CheckBox should be un uncheckable, so we set it to false by every click
        // so the checkbox chnage the state every time to true.
        m_p1KnightCheckBox->setIsChecked(false);
        if (!m_p1KnightCheckBox->isChecked())
        {
            deselectDevicesWhichAreNotGiven(widget, m_p1WarriorCheckBoxes);
        }
    });
    m_p1RunnerCheckBox->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        m_p1RunnerCheckBox->setIsChecked(false);
        if (!m_p1RunnerCheckBox->isChecked())
        {
            deselectDevicesWhichAreNotGiven(widget, m_p1WarriorCheckBoxes);
        }
    });
    m_p1WizardCheckBox->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        m_p1WizardCheckBox->setIsChecked(false);
        if (!m_p1WizardCheckBox->isChecked())
        {
            deselectDevicesWhichAreNotGiven(widget, m_p1WarriorCheckBoxes);
        }
    });

    // Player 2
    m_p2KnightCheckBox = static_cast<gsf::CheckBoxWidget*>(
            m_guiEnvironment.getWidgetByID("checkBoxWidget_p2Knight"));
    m_p2RunnerCheckBox = static_cast<gsf::CheckBoxWidget*>(
            m_guiEnvironment.getWidgetByID("checkBoxWidget_p2Runner"));    
    m_p2WizardCheckBox = static_cast<gsf::CheckBoxWidget*>(
            m_guiEnvironment.getWidgetByID("checkBoxWidget_p2Wizard"));
    m_p2WarriorCheckBoxes.push_back(m_p2KnightCheckBox);
    m_p2WarriorCheckBoxes.push_back(m_p2RunnerCheckBox);
    m_p2WarriorCheckBoxes.push_back(m_p2WizardCheckBox);

    m_p2KnightCheckBox->setIsChecked(true);
    m_p2KnightCheckBox->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        m_p2KnightCheckBox->setIsChecked(false);
        if (!m_p2KnightCheckBox->isChecked())
        {
            deselectDevicesWhichAreNotGiven(widget, m_p2WarriorCheckBoxes);
        }
    });
    m_p2RunnerCheckBox->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        m_p2RunnerCheckBox->setIsChecked(false);
        if (!m_p2RunnerCheckBox->isChecked())
        {
            deselectDevicesWhichAreNotGiven(widget, m_p2WarriorCheckBoxes);
        }
    });
    m_p2WizardCheckBox->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        m_p2WizardCheckBox->setIsChecked(false);
        if (!m_p2WizardCheckBox->isChecked())
        {
            deselectDevicesWhichAreNotGiven(widget, m_p2WarriorCheckBoxes);
        }
    });
    // Level
    handleLevelLoading();

    // Buttons
    gsf::TextButtonWidget* startBtn{ static_cast<gsf::TextButtonWidget*>(
            m_guiEnvironment.getWidgetByID("textButtonWidget_start")) };
    startBtn->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        std::string levelName{ m_levelListBox->currentText() };
        std::string levelID{ m_levels[levelName] };
        MainGameScreen::GameData gameData(
                MainGameScreen::GameMode::TWO_PLAYER,
                levelID, 
                getPlayer1WarriorType(),
                getPlayer2WarriorType());
        m_screenStack->registerScreen<MainGameScreen, 
            MainGameScreen::GameData>(ScreenID::GAME, gameData);
        m_screenStack->popScreen();
        m_screenStack->pushScreen(ScreenID::GAME);
    });

    gsf::TextButtonWidget* backBtn{ static_cast<gsf::TextButtonWidget*>(
            m_guiEnvironment.getWidgetByID("textButtonWidget_back")) };
    backBtn->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        m_screenStack->popScreen();
        m_screenStack->pushScreen(ScreenID::MAINMENU);
    });
}

void TwoPlayerSelectionScreen::handleLevelLoading()
{
    m_levelListBox = static_cast<gsf::ListBoxWidget*>(
            m_guiEnvironment.getWidgetByID("listBoxWidget_level"));
    for (const auto &level : m_context.levelHolder->getLevels())
    {
        const Level &levelIns{ *level.second.get() };
        m_levels.insert(std::make_pair(levelIns.name, level.first));
        m_levelListBox->addElement(levelIns.name);
    }
}

void TwoPlayerSelectionScreen::deselectDevicesWhichAreNotGiven(
        gsf::Widget *widget, std::vector<gsf::CheckBoxWidget*> &checkBoxes)
{
    for (gsf::CheckBoxWidget *checkBox : checkBoxes)
    {
        if (checkBox != widget)
        {
            checkBox->setIsChecked(false);
        }
    }
}

WorldObjectTypes TwoPlayerSelectionScreen::getPlayer1WarriorType() const
{
    if (m_p1KnightCheckBox->isChecked())
    {
        return WorldObjectTypes::KNIGHT;
    }
    if (m_p1RunnerCheckBox->isChecked())
    {
        return WorldObjectTypes::RUNNER;
    }
    if (m_p1WizardCheckBox->isChecked())
    {
        return WorldObjectTypes::WIZARD;
    }
    assert(false && "This block should be unreachable!");
    return WorldObjectTypes::NONE;
}

WorldObjectTypes TwoPlayerSelectionScreen::getPlayer2WarriorType() const
{
    if (m_p2KnightCheckBox->isChecked())
    {
        return WorldObjectTypes::KNIGHT;
    }
    if (m_p2RunnerCheckBox->isChecked())
    {
        return WorldObjectTypes::RUNNER;
    }
    if (m_p2WizardCheckBox->isChecked())
    {
        return WorldObjectTypes::WIZARD;
    }
    assert(false && "This block should be unreachable!");
    return WorldObjectTypes::NONE;
}

void TwoPlayerSelectionScreen::windowSizeChanged()
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_guiEnvironment.replaceWidgets();
    m_context.window->setView(oldView);
}

bool TwoPlayerSelectionScreen::handleInput(Input &input, float dt)
{
    switch (input.getInputType())
    {
        case InputTypes::BACK :
        {
            m_screenStack->popScreen();
            m_screenStack->pushScreen(ScreenID::MAINMENU);
            return false;
        }
        default:
            break;
    }
    return false;
}

bool TwoPlayerSelectionScreen::handleEvent(sf::Event &event, float dt)
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_guiEnvironment.handleEvent(event);
    m_context.window->setView(oldView);
    return false;
}

bool TwoPlayerSelectionScreen::update(float dt)
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_guiEnvironment.update(dt);
    m_context.window->setView(oldView);
    return false;
}

void TwoPlayerSelectionScreen::render()
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_context.window->draw(*m_context.background);
    m_context.window->draw(m_guiEnvironment);
    m_context.window->setView(oldView);
}

