#include "Screens/PauseScreen.hpp"
#include "Screens/ScreenStack.hpp"

PauseScreen::PauseScreen(ScreenStack *screenStack, Context &context)
: Screen(screenStack, context)
, m_guiEnvironment{ *context.window }
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
