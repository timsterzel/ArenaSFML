#include "Warrior.hpp"

Warrior::Warrior()
{

}

void Warrior::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
