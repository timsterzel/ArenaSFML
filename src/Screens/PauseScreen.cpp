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
    std::cout << "PauseScreen::buildScene" << std::endl;

    m_txtPaused.setFont(m_context.fontHolder->get("default"));
	m_txtPaused.setCharacterSize(12);
	m_txtPaused.setFillColor(sf::Color::White);
    m_txtPaused.setString("--PAUSED--");
    m_txtPaused.setOrigin(m_txtPaused.getLocalBounds().width / 2.f, m_txtPaused.getLocalBounds().height / 2.f);
    m_txtPaused.setPosition(m_context.window->getView().getSize().x / 2.f, m_context.window->getView().getSize().y / 2.f);
    //m_sceneGraph.attachChild(std::move(background));
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
    //std::cout << "Render" << std::endl;
    //m_context.window->draw(m_renderManager);
    m_context.window->draw(m_txtPaused);
}

