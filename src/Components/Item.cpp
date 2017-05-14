#include "Components/Item.hpp"
#include "Calc.hpp"
#include <iostream>
#include <cmath>

Item::Item(RenderLayers layer, Textures textureId, 
        const ResourceHolder<sf::Texture, Textures> &textureHolder)
: SpriteNode(layer, textureHolder.get(textureId), true, false)
//, m_sprite{ textureHolder.get(textureId) }
, m_rotationPoint{ 0.f, 0.f }
{
    /*
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    setWidth(bounds.width);
    setHeight(bounds.height);
    */
    
}


Item::Item(RenderLayers layer, const sf::Texture &texture, const sf::IntRect &rect)
: SpriteNode(layer, texture, rect, true)
//, m_sprite{ texture, rect }
, m_rotationPoint{ 0.f, 0.f }
{
    /*   
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    setWidth(bounds.width);
    setHeight(bounds.height);
    */
}

Item::Item(RenderLayers layer, const sf::Texture &texture, 
    const std::vector<sf::IntRect> frameRects, bool centerOrigin, 
    float totalTime, bool repeat)
: SpriteNode(layer, texture, frameRects, centerOrigin, totalTime, repeat)
, m_rotationPoint{ 0.f, 0.f }
{

}

Item::~Item()
{

}

/*
sf::Sprite& Item::getSprite()
{
    return m_sprite;
}

float Item::getSpriteWidth() const
{
    return m_sprite.getLocalBounds().width;
}

float Item::getSpriteHeight() const
{
    return m_sprite.getLocalBounds().height;
}
*/

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

void Item::setRotationDefault(float rotation)
{
    Transformable::setRotation(rotation);
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

/*
void Item::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
*/
