#include "Screens/Screen.hpp"
#include "Collision/CollisionShape.hpp"
#include "Collision/CollisionCircle.hpp"
#include "Collision/CollisionRect.hpp"
#include "Components/SpriteNode.hpp"
#include "Components/Warrior.hpp"
#include "Components/Weapon.hpp"
#include "Components/Knight.hpp"
#include "Calc.hpp"
#include "Game.hpp"
#include <memory>


Screen::Screen(const bool isInDebug, Game *game, sf::RenderWindow *window, const ResourceHolder<sf::Font, Fonts> &FontHolder,
const ResourceHolder<sf::Texture, Textures> &TextureHolder, const SpriteSheetMapHolder &spriteSheetMapHolder)
: m_isInDebug { isInDebug }
, m_game{ game }
, m_window{ window }
, m_renderManager{ &m_sceneGraph }
, m_FontHolder{ FontHolder }
, m_TextureHolder{ TextureHolder }
, m_SpriteSheetMapHolder{ spriteSheetMapHolder }
{

}

Screen::~Screen()
{

}

void Screen::buildScene()
{
    // Do nothing by default
}

void Screen::handleInput(Input input, float dt)
{
    // Do nothing by default
}

void Screen::update(float dt)
{
    m_sceneGraph.update(dt);
}

void Screen::render()
{
    m_window->draw(m_renderManager);
}

