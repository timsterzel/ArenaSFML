#include "SpriteNode.hpp"

SpriteNode::SpriteNode(const sf::Texture &texture)
: m_sprite(texture)
{

}

SpriteNode::SpriteNode(const sf::Texture &texture, const sf::IntRect &rect)
: m_sprite(texture, rect)
{

}

void SpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}


