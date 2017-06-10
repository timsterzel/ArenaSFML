#include "Components/Weapon.hpp"
#include "Calc.hpp"
#include <iostream>
#include <cmath>
#include <Helpers.hpp>

Weapon::Weapon(RenderLayers layer, const float damage, 
        const std::string &textureId, 
        const ResourceHolder<sf::Texture> &textureHolder)
: Item(layer, textureId, textureHolder)
, m_damage{ damage }
, m_damageMultiplicator{ 1.f }
{
    addType(WorldObjectTypes::WEAPON);
}


Weapon::Weapon(RenderLayers layer, const float damage, const sf::Texture &texture, const sf::IntRect &rect)
: Item(layer, texture, rect)
, m_damage{ damage }
, m_damageMultiplicator{ 1.f }
{
    addType(WorldObjectTypes::WEAPON);
}
        
Weapon::Weapon(RenderLayers layer, const float damage, const sf::Texture &texture, 
    const std::vector<sf::IntRect> frameRects, bool centerOrigin, 
    float totalTime, bool repeat)
: Item(layer, texture, frameRects, centerOrigin, totalTime, repeat)
, m_damage{ damage }
, m_damageMultiplicator{ 1.f }
{
    addType(WorldObjectTypes::WEAPON);
}

Weapon::~Weapon()
{

}

float Weapon::getTotalDamage() const
{
    return m_damage * m_damageMultiplicator;
}

void Weapon::setStandartDamage(const float damage)
{
    m_damage = damage;
}

void Weapon::setDamageMultiplicator(float multiplicator)
{
    m_damageMultiplicator = multiplicator;
}

const std::string& Weapon::getAttackID() const
{
    return m_ID;
}

void Weapon::addHitID(const std::string& id)
{
    m_hitIDs.insert(id);
}

bool Weapon::wasIDAlreadyAttacked(const std::string& id)
{
    return m_hitIDs.find(id) != m_hitIDs.end();
}

void Weapon::startNewAttack()
{
    // Create a random attack id
    m_ID = Helpers::createUniqueID(30);
    m_hitIDs.clear();
}
