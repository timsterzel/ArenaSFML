#include "Components/Warrior.hpp"
#include "Calc.hpp"
#include <iostream>

Warrior::Warrior(Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder)
:m_sprite{textureHolder.get(textureId)}
{
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

int Warrior::getHealth() const
{
    return m_health;
}

void Warrior::setHealth(const int health)
{
    m_health = health;
}

void Warrior::damage(const int damage)
{
    m_health -= damage;
}

void Warrior::heal(const int health)
{
    m_health += health;
}

void Warrior::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

void Warrior::onCommandCurrent(const Command &command, float dt)
{
    // Do command handling of parent class
    //Entity::onCommand(command, dt);
    if (command.getWorldObjectType() == m_type)
    {
        m_currentVelocity.x = 0.f;
        m_currentVelocity.y = 0.f;
        switch (command.getCommandType())
        {
            case CommandTypes::LOOK_AT :
                lookAt(command.getValues());
                break;
            case CommandTypes::ROTATE :
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

void Warrior::lookAt(const sf::Vector2f LookPos)
{
    const sf::Vector2f UnitVecX(1.0, 0.f);
    // The angle which should be calculated have the coordinate systems midpoint at the players position,
    // so we have to translate the pos in relation to the player position
    const sf::Vector2f TranslatedLookPos = LookPos - getPosition();
    const float Angle = { Calc::radToDeg(Calc::getVec2Angle<sf::Vector2f, sf::Vector2f>(UnitVecX, TranslatedLookPos)) };
    const float AngleSigned = TranslatedLookPos.y < 0.f ? -Angle : Angle;
    setRotation(AngleSigned);
}

