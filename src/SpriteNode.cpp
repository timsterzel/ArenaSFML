#include "SpriteNode.hpp"

SpriteNode::SpriteNode(const sf::Texture &texture)
{

}

SpriteNode::SpriteNode(const sf::Texture &texture, const sf::IntRect &rect)
{

}

void SpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}


