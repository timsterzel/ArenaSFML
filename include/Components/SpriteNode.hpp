#ifndef SPRITE_NODE_HPP
#define SPRITE_NODE_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "Components/Entity.hpp"


class SpriteNode : public Entity
{
    private:
        sf::Sprite m_sprite;


        std::vector<sf::IntRect> m_frameRects;
        // Total time of the complete animation in seconds
        float m_totalTime;
        float m_timePerFrame;
        float m_currentFrameTime;
        std::size_t m_currentFrame;
        bool m_repeat;
    public:

        SpriteNode(RenderLayers layer, const sf::Texture &texture, 
                bool centerOrigin);
        SpriteNode(RenderLayers layer, const sf::Texture &texture, 
                const sf::IntRect &rect, bool centerOrigin);

        SpriteNode(RenderLayers layer, const sf::Texture &texture, 
                bool centerOrigin, bool repeat = true);
        SpriteNode(RenderLayers layer, const sf::Texture &texture, 
                const std::vector<sf::IntRect> frameRects, bool centerOrigin,
                float totalTime, bool repeat = true);

        virtual ~SpriteNode();
        
        
        sf::Sprite& getSprite();
        void setTotalTime(float time);
        
    protected:
        virtual void updateCurrent(float dt);
        virtual void drawCurrent(sf::RenderTarget &target, 
                sf::RenderStates states) const;

};

#endif // !SPRITE_NODE_HPP
