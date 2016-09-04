#include "Screens/Screen.hpp"
#include "Collision/CollisionShape.hpp"
#include "Collision/CollisionCircle.hpp"
#include "Collision/CollisionRect.hpp"
#include "Components/SpriteNode.hpp"
#include "Components/Warrior.hpp"
#include "Components/Weapon.hpp"
#include "Components/Knight.hpp"
#include "Calc.hpp"
#include <memory>

Screen::Screen(const bool isInDebug, sf::RenderWindow *window, const ResourceHolder<sf::Font, Fonts> &FontHolder,
const ResourceHolder<sf::Texture, Textures> &TextureHolder, const SpriteSheetMapHolder &spriteSheetMapHolder)
: m_isInDebug { isInDebug }
, m_window{ window }
, m_worldView{ m_window->getDefaultView() }
, m_renderManager{ &m_sceneGraph }
, m_FontHolder{ FontHolder }
, m_TextureHolder{ TextureHolder }
, m_SpriteSheetMapHolder{ spriteSheetMapHolder }
{

}

void Screen::buildScene()
{
    std::cout << "Screen::buildScene" << std::endl;

    std::cout << "Screen::buildScene End" << std::endl;
}

void Screen::handleInput(Input input, float dt)
{
    // do nothing by default
}

void Screen::update(float dt)
{
    m_sceneGraph.update(dt);
}

void Screen::render()
{
    std::cout << "Players is null" << std::endl;
    m_window->draw(m_renderManager);

}

