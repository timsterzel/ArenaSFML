#include "Components/Weapon.hpp"
#include "Calc.hpp"
#include <iostream>
#include <cmath>

Weapon::Weapon(RenderLayers layer, const int damage, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder)
: Entity(layer)
, m_damage{ damage }
, m_sprite{ textureHolder.get(textureId) }
//, m_isAttacking{ false }
, m_rotationPoint{ 0.f, 0.f }
, m_relEquipPoint{ 0.f, 0.f }
{
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    setWidth(bounds.width);
    setHeight(bounds.height);
    //setEquipPoint(10.f, 0.f);
    //m_relEquipPoint.x = -bounds.width / 2.f;
    //m_relEquipPoint.y = 0.f;
    //m_sprite.setOrigin(0.f, 0.f);
}


Weapon::Weapon(RenderLayers layer, const int damage, const sf::Texture &texture, const sf::IntRect &rect)
: Entity(layer)
, m_damage{ damage }
, m_sprite{ texture, rect }
//, m_isAttacking{ false }
, m_rotationPoint{ 0.f, 0.f }
, m_relEquipPoint{ 0.f, 0.f }
{
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    setWidth(bounds.width);
    setHeight(bounds.height);
    //setEquipPoint(10.f, 0.f);
    //m_relEquipPoint.x = -bounds.width / 2.f;
    //m_relEquipPoint.y = 0.f;
    //m_sprite.setOrigin(0.f, 0.f);
}

Weapon::~Weapon()
{
    std::cout << "Destructor Weapon" << std::endl;
}

int Weapon::getDamage() const
{
    return m_damage;
}

void Weapon::setDamage(const int damage)
{
    m_damage = damage;
}

float Weapon::getSpriteWidth() const
{
    return m_sprite.getLocalBounds().width;
}

float Weapon::getSpriteHeight() const
{
    return m_sprite.getLocalBounds().height;
}

/*
bool Weapon::isAttacking() const
{
    return m_isAttacking;
}
*/
void Weapon::setRotationPoint(sf::Vector2f point)
{
    m_rotationPoint = point;
}

void Weapon::setRotationPoint(float x, float y)
{
    m_rotationPoint.x = x;
    m_rotationPoint.y = y;
}

sf::Vector2f Weapon::getRotationPoint() const
{
    return m_rotationPoint;
}

void Weapon::setEquipPoint(float x, float y)
{
    m_relEquipPoint.x = x;
    m_relEquipPoint.y = y;
    setPosition(getPosition() - m_relEquipPoint);
}

void Weapon::equip(sf::Vector2f parentEqiupPos) {
    setPosition(parentEqiupPos - m_relEquipPoint);
}

/*
void Weapon::rotateAround(sf::Vector2f pos, float degrees)
{
    rotate(degrees);
    const sf::Vector2f newPos = { Calc::rotatePointAround(getPosition(), pos, -degrees) };
    setPosition(newPos);
}
*/

void Weapon::setRotation(float angle)
{
    float actualAngle = getRotation();
    float angleToRotate = angle;
    float minAngle = std::min(actualAngle, angleToRotate);
    float maxAngle = std::max(actualAngle, angleToRotate);
    float rotateAngle = minAngle - maxAngle;
    rotate(rotateAngle);
}

void Weapon::rotate(float angle)
{
    sf::Transformable::rotate(angle);
    const sf::Vector2f newPos = { Calc::rotatePointAround(getPosition(), m_rotationPoint, -angle) };
    setPosition(newPos);
}

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
