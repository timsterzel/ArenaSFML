#include "Warrior.hpp"
#include <iostream>

Warrior::Warrior(Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder)
:m_sprite(textureHolder.get(textureId))
{
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Warrior::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
