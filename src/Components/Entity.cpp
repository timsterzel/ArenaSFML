#include "Components/Entity.hpp"
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
    if (command.getWorldObjectType() == m_type)
    {
        m_currentVelocity.x = 0.f;
        m_currentVelocity.y = 0.f;
        switch (command.getCommandType())
        {
            case CommandTypes::ROTATE:
                setRotation(command.getValues().x - 90.f);
                break;
            case CommandTypes::MOVE_UP:
                m_currentVelocity.y = -m_velocity.y;
                break;
            case CommandTypes::MOVE_DOWN:
                m_currentVelocity.y = m_velocity.y;
                break;
            case CommandTypes::MOVE_LEFT:
                m_currentVelocity.x = -m_velocity.x;
                break;
            case CommandTypes::MOVE_RIGHT:
                m_currentVelocity.x = m_velocity.x;
                break;
        }
        // Move is the same as setPosition(getPosition() + offset) of the sf::Transformable class
        move(m_currentVelocity * dt);
    }
}
