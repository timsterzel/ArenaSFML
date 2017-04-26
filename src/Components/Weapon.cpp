#include "Components/Weapon.hpp"
#include "Calc.hpp"
#include <iostream>
#include <cmath>

Weapon::Weapon(RenderLayers layer, const float damage, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder)
: Item(layer, textureId, textureHolder)
, m_damage{ damage }
, m_damageMultiplicator{ 1.f }
{

}


Weapon::Weapon(RenderLayers layer, const float damage, const sf::Texture &texture, const sf::IntRect &rect)
: Item(layer, texture, rect)
, m_damage{ damage }
, m_damageMultiplicator{ 1.f }
{

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
