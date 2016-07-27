#ifndef SPRITENODE_HPP
#define SPRITENODE_HPP
#include <SFML/Graphics.hpp>
#include "Components/SceneNode.hpp"

class SpriteNode : public SceneNode
{
    private:
        sf::Sprite m_sprite;
    public:
        SpriteNode(const sf::Texture &texture);
        SpriteNode(const sf::Texture &texture, const sf::IntRect &rect);
    private:
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

};

#endif // SPRITENODE_HPP
