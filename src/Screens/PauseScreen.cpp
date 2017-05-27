#include "Screens/PauseScreen.hpp"

PauseScreen::PauseScreen(ScreenStack *screenStack, Context &context)
: Screen(screenStack, context)
{
    buildScene();
}

PauseScreen::~PauseScreen()
{

}

void PauseScreen::buildScene()
{
    m_txtPaused.setFont(m_context.fontHolder->get("default"));
	m_txtPaused.setCharacterSize(32);
	m_txtPaused.setFillColor(sf::Color::White);
    m_txtPaused.setString("--PAUSED--");
    m_txtPaused.setOrigin(m_txtPaused.getLocalBounds().width / 2.f, 
            m_txtPaused.getLocalBounds().height / 2.f);
    m_txtPaused.setPosition(m_context.guiView.getSize().x / 2.f, 
            m_context.guiView.getSize().y / 2.f);
}

void PauseScreen::windowSizeChanged()
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    //m_guiEnvironment.replaceWidgets();
    sf::Vector2f viewSize{ m_context.guiView.getSize() };
    m_txtPaused.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);
    m_context.window->setView(oldView);
}

bool PauseScreen::handleInput(Input &input, float dt)
{
    switch (input.getInputType())
    {
        case InputTypes::PAUSE :
        {
            // Let the Game screen handle this input
            return true;
            break;
        }
        default:
            break;
    }
    return false;
}

bool PauseScreen::handleEvent(sf::Event &event, float dt)
{
    return true;
}

bool PauseScreen::update(float dt)
{
    //m_sceneGraph.removeDestroyed();
    //m_sceneGraph.update(dt);
    return false;
}

void PauseScreen::render()
{
    sf::View oldView{ m_context.window->getView() };
    m_context.window->setView(m_context.guiView);
    //std::cout << "Render" << std::endl;
    //m_context.window->draw(m_renderManager);
    m_context.window->draw(m_txtPaused);
    m_context.window->setView(oldView);
}

