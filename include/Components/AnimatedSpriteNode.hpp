#ifndef ANIMATEDSPRITENODE_HPP
#define ANIMATEDSPRITENODE_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "Components/SpriteNode.hpp"


class AnimatedSpriteNode : public SpriteNode
{
    private:
        std::vector<sf::IntRect> m_frameRects;
        // Total time of the complete animation in seconds
        float m_totalTime;
        float m_timePerFrame;
        float m_currentFrameTime;
        int m_currentFrame;
        bool m_repeat;
    public:
        AnimatedSpriteNode(RenderLayers layer, const sf::Texture &texture, 
                bool centerOrigin, bool repeat = true);
        AnimatedSpriteNode(RenderLayers layer, const sf::Texture &texture, 
                const std::vector<sf::IntRect> frameRects, bool centerOrigin,
                float totalTime, bool repeat = true);

        virtual ~AnimatedSpriteNode();
 
        void setTotalTime(float time);
        
        virtual void updateCurrent(float dt);
    private:
        virtual void drawCurrent(sf::RenderTarget &target, 
                sf::RenderStates states) const;

};

#endif // !ANIMATEDSPRITENODE_HPP
