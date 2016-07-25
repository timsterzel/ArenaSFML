#include "Components/Warrior.hpp"
#include "Calc.hpp"
#include "Components/Weapon.hpp"
#include <iostream>

Warrior::Warrior(const int health, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder)
: m_maxHealth{ health }
, m_currentHealth{ health }
, m_sprite{ textureHolder.get(textureId) }
, m_weapon{ nullptr }
{
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

Warrior::Warrior(Weapon *weapon, const int health, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder)
: m_maxHealth{ health }
, m_currentHealth{ health }
, m_sprite{ textureHolder.get(textureId) }
, m_weapon{ weapon }
{
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

int Warrior::getCurrentHealth() const
{
    return m_currentHealth;
}

void Warrior::setCurrentHealth(const int health)
{
    m_currentHealth = health;
}

Weapon* Warrior::getWeapon() const
{
    return m_weapon;
}

bool Warrior::isAlive() const
{
    return m_currentHealth > 0;
}

void Warrior::damage(const int damage)
{
    m_currentHealth -= damage;
}

void Warrior::heal(const int health)
{
    m_currentHealth += health;
    if (m_currentHealth > m_maxHealth)
    {
        m_currentHealth = m_maxHealth;
    }
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
    // only look to the LookPos when Warrior is not at the same position
    if (LookPos.x == getWorldPosition().x && LookPos.y == getWorldPosition().y)
    {
        return;
    }
    const sf::Vector2f UnitVecX(1.0, 0.f);
    // The angle which should be calculated have the coordinate systems midpoint at the players position,
    // so we have to translate the pos in relation to the player position
    const sf::Vector2f TranslatedLookPos = LookPos - getWorldPosition();
    const float Angle = { Calc::radToDeg(Calc::getVec2Angle<sf::Vector2f, sf::Vector2f>(UnitVecX, TranslatedLookPos)) };
    const float AngleSigned = TranslatedLookPos.y < 0.f ? -Angle : Angle;
    setRotation(AngleSigned);
}

