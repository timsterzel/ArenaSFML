#include "Components/Entity.hpp"
#include "Calc.hpp"
#include <iostream>

Entity::Entity()
{

}

void Entity::setVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}

void Entity::setVelocity(float velX, float velY)
{
    m_velocity.x = velX;
    m_velocity.y = velY;
}

sf::Vector2f Entity::getVelocity() const
{
    return m_velocity;
}

void Entity::moveInActualDirection(const float length)
{
    sf::Vector2f normalizedDir = { Calc::normalizeVec2<sf::Vector2f>(m_velocity) };
    move(normalizedDir.x * length, normalizedDir.y * length);
}

void Entity::moveInDirection(const sf::Vector2f direction, const float length)
{
    sf::Vector2f normalizedDir = { Calc::normalizeVec2<sf::Vector2f>(direction) };
    move(normalizedDir.x * length, normalizedDir.y * length);
}

void Entity::updateCurrent(float dt)
{
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


