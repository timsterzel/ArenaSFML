#include "Components/Weapon.hpp"
#include "Calc.hpp"
#include <iostream>

Weapon::Weapon(const int damage, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder)
: m_damage{ damage }
, m_sprite{ textureHolder.get(textureId) }
, m_isAttacking{ false }
//, m_relEquipPoint{ 0.f, 0.f }
//, m_absEquipPoint{ 0.f, 0.f }
{
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    std::cout << "WIDTH: " << bounds.width << " HEIGHT: " << bounds.height << std::endl;
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    //m_relEquipPoint.x = -bounds.width / 2.f;
    //m_relEquipPoint.y = 0.f;
    //m_sprite.setOrigin(0.f, 0.f);
}

Weapon::~Weapon()
{
    std::cout << "Weapon destructor" << std::endl;
}

int Weapon::getDamage() const
{
    return m_damage;
}

void Weapon::setDamage(const int damage)
{
    m_damage = damage;
}

int Weapon::getSpriteWidth() const
{
    return m_sprite.getLocalBounds().width;
}

int Weapon::getSpriteHeight() const
{
    return m_sprite.getLocalBounds().height;
}

bool Weapon::isAttacking() const
{
    return m_isAttacking;
}

/*
void Weapon::setEquipPoint(float x, float y)
{
    m_relEquipPoint.x = x;
    m_relEquipPoint.y = y;
}
*/


void Weapon::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

void Weapon::updateCurrent(float dt)
{
    /*
    std::cout << "POS: " << getPosition().x << "|" << getPosition().y << std::endl;

    const float rotation = { -1.f * dt };
    std::cout << "rotation: " << rotation << std::endl;
    const sf::Vector2f absEqupPoint = { getPosition() + m_relEquipPoint };
    //rotate(rotation);
    // change 0.f, 0.f to equp point later
    const sf::Vector2f newPos = { Calc::rotatePointAround(getPosition(), absEqupPoint, rotation) };
    setPosition(newPos);
    std::cout << "absEqupPoint Pos: " << absEqupPoint.x << "|" << absEqupPoint.y << std::endl;
    std::cout << "m_relEquipPoint: " << m_relEquipPoint.x << "|" << m_relEquipPoint.y << std::endl;
    std::cout << "Pos New: " << newPos.x << "|" << newPos.y << std::endl;
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    */
}
