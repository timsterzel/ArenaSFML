#include "Screens/PauseScreen.hpp"

PauseScreen::PauseScreen(ScreenStack *screenStack, Context context)
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

    m_txtPaused.setFont(m_context.fontHolder->get(Fonts::DEFAULT));
	m_txtPaused.setCharacterSize(12);
	m_txtPaused.setColor(sf::Color::White);
    m_txtPaused.setString("--PAUSED--");
    m_txtPaused.setOrigin(m_txtPaused.getLocalBounds().width / 2.f, m_txtPaused.getLocalBounds().height / 2.f);
    m_txtPaused.setPosition(m_context.window->getSize().x / 2.f, m_context.window->getSize().y / 2.f);
    //m_sceneGraph.attachChild(std::move(background));
}

void PauseScreen::handleInput(Input input, float dt)
{

}

void PauseScreen::update(float dt)
{
    //m_sceneGraph.removeDestroyed();
    //m_sceneGraph.update(dt);
}

void PauseScreen::render()
{
    //std::cout << "Render" << std::endl;
    //m_context.window->draw(m_renderManager);
    m_context.window->draw(m_txtPaused);
}

