#include "Components/SpriteNode.hpp"

SpriteNode::SpriteNode(const sf::Texture &texture, bool centerOrigin)
: m_sprite(texture)
{
    init(centerOrigin);
}

SpriteNode::SpriteNode(const sf::Texture &texture, const sf::IntRect &rect, bool centerOrigin)
: m_sprite(texture, rect)
{
    init(centerOrigin);
}

void SpriteNode::init(bool centerOrigin)
{
    if (centerOrigin)
    {
        sf::FloatRect bounds = m_sprite.getLocalBounds();
        m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }

}

void SpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}


