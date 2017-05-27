#include "Screens/Screen.hpp"
#include "Collision/CollisionShape.hpp"
#include "Collision/CollisionCircle.hpp"
#include "Collision/CollisionRect.hpp"
#include "Components/SpriteNode.hpp"
#include "Components/Warrior.hpp"
#include "Components/Weapon.hpp"
#include "Components/Knight.hpp"
#include "Calc.hpp"
#include "Sound/MusicPlayer.hpp"
#include <memory>

Screen::Screen(ScreenStack *screenStack, Context &context)
: m_context{ context }
, m_screenStack{ screenStack }
, m_renderManager{ &m_sceneGraph }
{

}

Screen::Context::Context(
    bool isInDebugMode, 
    sf::RenderWindow *window, 
    ResourceHolder<sf::Font> *fontHolder,
    ResourceHolder<sf::Texture> *textureHolder, 
    ResourceHolder<sf::Shader> *shaderHolder,
    SpriteSheetMapHolder *spriteSheetMapHolder, 
    LevelHolder *levelHolder,
    MusicPlayer *music,
    sf::RectangleShape *background)
: isInDebugMode{ isInDebugMode }
, window{ window }
, gameView{ window->getView() }
, guiView{ window->getView() }
, fontHolder{ fontHolder }
, textureHolder{ textureHolder }
, shaderHolder{ shaderHolder }
, spriteSheetMapHolder{ spriteSheetMapHolder }
, levelHolder{ levelHolder }
, music{ music }
, background{ background }
{

}

Screen::~Screen()
{

}

void Screen::buildScene()
{
    // Do nothing by default
}

Screen::Context Screen::getContext()
{
    return m_context;
}

void Screen::windowSizeChanged()
{
    // Do nothing by default
}

bool Screen::handleInput(Input &input, float dt)
{
    return true;
}

bool Screen::handleEvent(sf::Event &event, float dt)
{
    return true;
}

bool Screen::update(float dt)
{
    m_sceneGraph.update(dt);
    return false;
}

void Screen::render()
{
    m_context.window->draw(m_renderManager);
}

