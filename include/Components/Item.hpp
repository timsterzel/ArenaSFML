#ifndef ITEM_HPP
#define ITEM_HPP
#include <SFML/Graphics.hpp>
#include "Components/SpriteNode.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Resources/ResourceHolder.hpp"

class Item : public SpriteNode
{
    protected:

    private:
        //sf::Sprite m_sprite;
        //bool m_isAttacking;
        // The point of which it should be rotated
        sf::Vector2f m_rotationPoint;

    public:
        Item(RenderLayers layer, Textures textureId, 
                const ResourceHolder<sf::Texture, Textures> &textureHolder);
        Item(RenderLayers layer, const sf::Texture &texture, 
                const sf::IntRect &rect);
        Item(RenderLayers layer, const sf::Texture &texture, 
                const std::vector<sf::IntRect> frameRects, bool centerOrigin, 
                float totalTime, bool repeat = true);
        virtual ~Item();
        
        //sf::Sprite& getSprite();

        //float getSpriteWidth() const;
        //float getSpriteHeight() const;

        void setRotationPoint(sf::Vector2f point);
        void setRotationPoint(float x, float y);
        sf::Vector2f getRotationPoint() const;
        
        // To Do: find better solution
        // Call the default sfmls setRotation method
        void setRotationDefault(float rotation);
        virtual void setRotation(float angle);
        //void rotateAround(sf::Vector2f pos, float degrees);
        void rotate(float angle);

        //virtual void drawCurrent(sf::RenderTarget &target, 
        //        sf::RenderStates states) const;

};

#endif // ITEM_HPP
