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

Screen::Context::Context(bool isInDebugMode, sf::RenderWindow *window, ResourceHolder<sf::Font, Fonts> *fontHolder,
    ResourceHolder<sf::Texture, Textures> *textureHolder, ResourceHolder<sf::Shader, Shaders> *shaderHolder,
    SpriteSheetMapHolder *spriteSheetMapHolder, MusicPlayer *music)
: isInDebugMode{ isInDebugMode }
, window{ window }
, fontHolder{ fontHolder }
, textureHolder{ textureHolder }
, shaderHolder{ shaderHolder }
, spriteSheetMapHolder{ spriteSheetMapHolder }
, music{ music }
{

}

Screen::~Screen()
{

}

void Screen::buildScene()
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

