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
    //m_window->clear();
    m_context.window->draw(m_renderManager);
    //m_window->display();
}

