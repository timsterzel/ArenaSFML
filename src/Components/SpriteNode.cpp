#include "Components/SpriteNode.hpp"
#include <iostream>

SpriteNode::SpriteNode(RenderLayers layer, const sf::Texture &texture, bool centerOrigin)
: SceneNode(layer)
, m_sprite(texture)
{
    init(centerOrigin);
}

SpriteNode::SpriteNode(RenderLayers layer, const sf::Texture &texture, const sf::IntRect &rect, bool centerOrigin)
: SceneNode(layer)
, m_sprite(texture, rect)
{
    init(centerOrigin, rect);
}

SpriteNode::~SpriteNode()
{

}

void SpriteNode::init(bool centerOrigin)
{
    if (centerOrigin)
    {
        sf::FloatRect bounds = m_sprite.getLocalBounds();
        m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }
}

void SpriteNode::init(bool centerOrigin, const sf::IntRect &rect)
{
    if (centerOrigin)
    {
        m_sprite.setOrigin(rect.width / 2.f, rect.height / 2.f);
    }
}

sf::Sprite& SpriteNode::getSprite()
{
    return m_sprite;
}

void SpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    /*
    sf::Shader shader;
    if (!shader.loadFromFile("assets/shaders/grayscale.frag", sf::Shader::Fragment))
    {
        std::cout << "Error by loading Shader \n";
    }
    states.shader = &shader;
    */
    target.draw(m_sprite, states);
    //states.shader = nullptr;
}


