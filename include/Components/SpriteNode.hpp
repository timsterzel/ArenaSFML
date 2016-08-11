#ifndef SPRITENODE_HPP
#define SPRITENODE_HPP
#include <SFML/Graphics.hpp>
#include "Components/SceneNode.hpp"

class SpriteNode : public SceneNode
{
    private:
        sf::Sprite m_sprite;
    public:
        SpriteNode(RenderLayers layer, const sf::Texture &texture, bool centerOrigin);
        SpriteNode(RenderLayers layer, const sf::Texture &texture, const sf::IntRect &rect, bool centerOrigin);
    private:
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

        void init(bool centerOrigin);
        void init(bool centerOrigin, const sf::IntRect &rect);

};

#endif // SPRITENODE_HPP
