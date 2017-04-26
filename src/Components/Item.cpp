#include "Components/Item.hpp"
#include "Calc.hpp"
#include <iostream>
#include <cmath>

Item::Item(RenderLayers layer, Textures textureId, 
        const ResourceHolder<sf::Texture, Textures> &textureHolder)
: Entity(layer)
, m_sprite{ textureHolder.get(textureId) }
, m_rotationPoint{ 0.f, 0.f }
{
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    setWidth(bounds.width);
    setHeight(bounds.height);
}


Item::Item(RenderLayers layer, const sf::Texture &texture, const sf::IntRect &rect)
: Entity(layer)
, m_sprite{ texture, rect }
, m_rotationPoint{ 0.f, 0.f }
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

Item::~Item()
{

}

float Item::getSpriteWidth() const
{
    return m_sprite.getLocalBounds().width;
}

float Item::getSpriteHeight() const
{
    return m_sprite.getLocalBounds().height;
}

/*
bool Item::isAttacking() const
{
    return m_isAttacking;
}
*/
void Item::setRotationPoint(sf::Vector2f point)
{
    m_rotationPoint = point;
}

void Item::setRotationPoint(float x, float y)
{
    m_rotationPoint.x = x;
    m_rotationPoint.y = y;
}

sf::Vector2f Item::getRotationPoint() const
{
    return m_rotationPoint;
}

void Item::setRotation(float angle)
{
    float actualAngle = getRotation();
    float angleToRotate = angle;
    float minAngle = std::min(actualAngle, angleToRotate);
    float maxAngle = std::max(actualAngle, angleToRotate);
    float rotateAngle = minAngle - maxAngle;
    rotate(rotateAngle);
}

void Item::rotate(float angle)
{
    sf::Transformable::rotate(angle);
    const sf::Vector2f newPos = { 
        Calc::rotatePointAround(getPosition(), m_rotationPoint, -angle) };
    setPosition(newPos);
}

void Item::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

void Item::updateCurrent(float dt)
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
