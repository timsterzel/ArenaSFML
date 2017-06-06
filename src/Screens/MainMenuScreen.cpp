#include "Screens/MainMenuScreen.hpp"
#include "Screens/ScreenStack.hpp"
#include "Screens/MainGameScreen.hpp"
#include "Screens/PauseScreen.hpp"

MainMenuScreen::MainMenuScreen(ScreenStack *screenStack, Context &context)
: Screen(screenStack, context)
, m_guiEnvironment{ *context.window }
{
    buildScene();
}

MainMenuScreen::~MainMenuScreen()
{
    std::cout << "MainMenuScreen Destructor\n";
}

void MainMenuScreen::buildScene()
{
    m_screenStack->pushScreen(ScreenID::GAME);
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_guiEnvironment.createScene("assets/gui/main_menu.xml");
    m_context.window->setView(oldView);
    
    // One Player
    gsf::TextButtonWidget* onePlayerBtn{ static_cast<gsf::TextButtonWidget*>(
            m_guiEnvironment.getWidgetByID("textButtonWidget_onePlayer")) };
    onePlayerBtn->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        const Level &level = *(m_context.levelHolder->getLevels()[0].get());
        std::map<InputDevice, WorldObjectTypes> deviceMap;
        deviceMap.insert({ InputDevice::JOYSTICK_0, 
                WorldObjectTypes::PLAYER_1 });
        // Register MainGameScreen with paramaters
        
        m_screenStack->registerScreen
            <MainGameScreen, 
            Level, 
            std::map<InputDevice, WorldObjectTypes>,
            MainGameScreen::GameMode> 
                   (ScreenID::GAME, 
                    level, 
                    deviceMap, 
                    MainGameScreen::GameMode::ONE_PLAYER);
        m_screenStack->registerScreen<PauseScreen>
            (ScreenID::PAUSE);
        m_screenStack->pushScreen(ScreenID::GAME);
    });
    // Two Player
    gsf::TextButtonWidget* twoPlayerBtn{ static_cast<gsf::TextButtonWidget*>(
            m_guiEnvironment.getWidgetByID("textButtonWidget_twoPlayer")) };
    twoPlayerBtn->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        const Level &level = *(m_context.levelHolder->getLevels()[0].get());
        std::map<InputDevice, WorldObjectTypes> deviceMap;
        deviceMap.insert({ InputDevice::JOYSTICK_0, 
                WorldObjectTypes::PLAYER_1 });
        deviceMap.insert({ InputDevice::KEYBOARD_MOUSE, 
                WorldObjectTypes::PLAYER_2 });
        // Register MainGameScreen with paramaters
        m_screenStack->registerScreen
            <MainGameScreen, 
            Level, 
            std::map<InputDevice, WorldObjectTypes>,
            MainGameScreen::GameMode> 
                   (ScreenID::GAME, 
                    level, 
                    deviceMap, 
                    MainGameScreen::GameMode::TWO_PLAYER);
        
        m_screenStack->registerScreen<PauseScreen>
            (ScreenID::PAUSE);
        m_screenStack->pushScreen(ScreenID::GAME);
    });

    gsf::TextButtonWidget* settingsBtn{ static_cast<gsf::TextButtonWidget*>(
            m_guiEnvironment.getWidgetByID("textButtonWidget_settings")) };
    settingsBtn->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        m_screenStack->pushScreen(ScreenID::SETTINGS);
    });

    gsf::TextButtonWidget* quitGameBtn{ static_cast<gsf::TextButtonWidget*>(
            m_guiEnvironment.getWidgetByID("textButtonWidget_quitGame")) };
    quitGameBtn->setOnLeftClickListener(
            [this](gsf::Widget *widget, sf::Vector2f pos)
    {
        getContext().window->close();
    });
}


void MainMenuScreen::windowSizeChanged()
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_guiEnvironment.replaceWidgets();
    m_context.window->setView(oldView);
}

bool MainMenuScreen::handleInput(Input &input, float dt)
{
    switch (input.getInputType())
    {
        case InputTypes::BACK :
        {
            m_context.window->close();
            return false;
        }
        default:
            break;
    }
    return false;
}

bool MainMenuScreen::handleEvent(sf::Event &event, float dt)
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_guiEnvironment.handleEvent(event);
    m_context.window->setView(oldView);
    return false;
}

bool MainMenuScreen::update(float dt)
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_guiEnvironment.update(dt);
    m_context.window->setView(oldView);
    return false;
}

void MainMenuScreen::render()
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    m_context.window->draw(*m_context.background);
    m_context.window->draw(m_guiEnvironment);
    m_context.window->setView(oldView);
}

