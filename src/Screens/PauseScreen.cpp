#include "Screens/PauseScreen.hpp"
#include "Screens/ScreenStack.hpp"
#include "Sound/MusicPlayer.hpp"
#include "Sound/SoundPlayer.hpp"

PauseScreen::PauseScreen(ScreenStack *screenStack, Context &context)
: Screen(screenStack, context)
, m_guiEnvironment{ *context.window }
, m_checkBoxMusic{ nullptr }
, m_checkBoxSound{ nullptr }
{
    buildScene();
}

PauseScreen::~PauseScreen()
{

}

void PauseScreen::buildScene()
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_guiEnvironment.createScene("assets/gui/pause_menu.xml");
    m_context.window->setView(oldView);


    gsf::TextButtonWidget* resumeBtn{ static_cast<gsf::TextButtonWidget*>(
            m_guiEnvironment.getWidgetByID("textButtonWidget_resumeGame")) };
    resumeBtn->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        // Close Pause Screen
        m_screenStack->popScreen();
        return true;
    });
    gsf::TextButtonWidget* mainMenuBtn{ static_cast<gsf::TextButtonWidget*>(
            m_guiEnvironment.getWidgetByID("textButtonWidget_mainMenu")) };
    mainMenuBtn->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        // Close Pause screen and MainGameScreen
        m_screenStack->popScreen();
        m_screenStack->popScreen();
        m_screenStack->pushScreen(ScreenID::MAINMENU);
    });

    
    m_checkBoxMusic = static_cast<gsf::CheckBoxWidget*>(
        m_guiEnvironment.getWidgetByID("checkBoxWidget_music" ));
    m_checkBoxSound = static_cast<gsf::CheckBoxWidget*>(
        m_guiEnvironment.getWidgetByID("checkBoxWidget_sound" ));
    
    m_checkBoxMusic->setIsChecked(m_context.music->getVolume() > 0.f);
    m_checkBoxSound->setIsChecked(m_context.sound->getVolume() > 0.f);


    m_checkBoxMusic->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        bool isChecked{ !m_checkBoxMusic->isChecked() };
        int volumeLevel{ m_context.config->getInt("music_level", 5) };
        m_context.music->setVolume(isChecked ? volumeLevel * 10 : 0);
    });
    m_checkBoxSound->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        bool isChecked{ !m_checkBoxSound->isChecked() };
        int volumeLevel{ m_context.config->getInt("sound_level", 6) };
        m_context.sound->setVolume(isChecked ? volumeLevel * 10 : 0);
    });
}

void PauseScreen::windowSizeChanged()
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_guiEnvironment.replaceWidgets();
    m_context.window->setView(oldView);
}

bool PauseScreen::handleInput(Input &input, float dt)
{
    switch (input.getInputType())
    {
        case InputTypes::PAUSE :
        {
            m_screenStack->popScreen();
            break;
        }
        default:
            break;
    }
    return false;
}

bool PauseScreen::handleEvent(sf::Event &event, float dt)
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_guiEnvironment.handleEvent(event);
    m_context.window->setView(oldView);
    return false;
}

bool PauseScreen::update(float dt)
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_guiEnvironment.update(dt);
    m_context.window->setView(oldView);
    return false;
}

void PauseScreen::render()
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_context.window->draw(m_guiEnvironment);
    m_context.window->setView(oldView);
}
