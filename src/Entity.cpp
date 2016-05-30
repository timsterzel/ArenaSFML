#include "Entity.hpp"


Entity::Entity()
{

}

void Entity::setVelocity(sf::Vector2f velocity)
{
    m_velocity = { velocity };
}

void Entity::setVelocity(float velX, float velY)
{
    m_velocity.x = { velX };
    m_velocity.y = { velY };
}

sf::Vector2f Entity::getVelocity()
{
    return m_velocity;
}

void Entity::updateCurrent(float dt)
{
    // Move is the same as setPosition(getPosition() + offset) of the sf::Transformable class
    move(m_velocity * dt);
}
