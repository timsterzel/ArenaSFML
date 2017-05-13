#include "Components/Entity.hpp"
#include "Calc.hpp"
#include <iostream>

Entity::Entity(RenderLayers layer)
: SceneNode(layer)
, m_velocity{ 0.f }
, m_currentVelocity{ 0.f }
, m_currentDirection{ 0.f, 0.f }
, m_width{ 0.f }
, m_height{ 0.f }
{

}

Entity::~Entity()
{

}

void Entity::setVelocity(float velocity)
{
    m_velocity = velocity;
}

float Entity::getVelocity() const
{
    return m_velocity;
}

void Entity::setCurrentVelocity(float currentVelocity)
{
    m_currentVelocity = currentVelocity;
}

float Entity::getCurrentVelocity() const
{
    return m_currentVelocity;
}

void Entity::setCurrentDirection(sf::Vector2f currentDirection)
{
    m_currentDirection = currentDirection;
}

sf::Vector2f Entity::getCurrentDirection() const
{
    return m_currentDirection;
}

float Entity::getWidth() const
{
    return m_width;
}

void Entity::setWidth(float width)
{
    m_width = width;
}

float Entity::getHeight() const
{
    return m_height;
}

void Entity::setHeight(float height)
{
    m_height = height;
}

void Entity::moveInActualDirection(const float length)
{
    // If the length is zero or less then zero there is nothing to move
    if (length <= 0.f)
    {
        return;
    }
    sf::Vector2f normalizedDir = { Calc::normalizeVec2<sf::Vector2f>(m_currentDirection) };
    move(normalizedDir.x * length, normalizedDir.y * length);
}

void Entity::moveInDirection(const sf::Vector2f direction, const float length)
{
    // If the length is zero or less then zero there is nothing to move
    if (length <= 0.f)
    {
        return;
    }
    sf::Vector2f normalizedDir = { Calc::normalizeVec2<sf::Vector2f>(direction) };
    move(normalizedDir.x * length, normalizedDir.y * length);
}
/*
sf::Vector2f Entity::getWorldCenterPosition() const
{
    return getWorldPosition() - getOrigin() + sf::Vector2f(m_width, m_height);
}
*/

void Entity::updateCurrent(float dt)
{
    moveInActualDirection(dt);
    /*
    m_currentVelocity.x = 0.f;
    m_currentVelocity.y = 0.f;
    if (m_command == Commands::MOVE_UP)
    {
        m_currentVelocity.y = m_velocity.y;
    }
    // Move is the same as setPosition(getPosition() + offset) of the sf::Transformable class
    move(m_currentVelocity * dt);
    */
}

void Entity::onCommandCurrent(const Command &command, float dt)
{

}
