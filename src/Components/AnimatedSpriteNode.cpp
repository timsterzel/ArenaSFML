#include "Components/AnimatedSpriteNode.hpp"
#include <iostream>

AnimatedSpriteNode::AnimatedSpriteNode(RenderLayers layer, 
        const sf::Texture &texture, bool centerOrigin, bool repeat)
: SpriteNode(layer, texture, centerOrigin)
, m_timePerFrame{ 0.f }
, m_currentFrameTime{ 0.f }
, m_currentFrame{ 0 }
, m_repeat{ repeat }
{

}

AnimatedSpriteNode::AnimatedSpriteNode(RenderLayers layer, 
        const sf::Texture &texture, const std::vector<sf::IntRect> frameRects, 
        bool centerOrigin, float totalTime, bool repeat)
: SpriteNode(layer, texture, centerOrigin)
, m_frameRects{ frameRects }
, m_totalTime{ totalTime }
, m_timePerFrame{ 0.f }
, m_currentFrameTime{ 0.f }
, m_currentFrame{ 0 }
, m_repeat{ repeat }
{
    setTotalTime(totalTime);
    if (m_frameRects.size() > 0)
    {
        sf::IntRect frameRect{ m_frameRects[0] };
        m_sprite.setTextureRect(frameRect);
        if (centerOrigin)
        {
            setOrigin(frameRect.width / 2.f, frameRect.height / 2.f); 
        }
    }
}

AnimatedSpriteNode::~AnimatedSpriteNode()
{

}

void AnimatedSpriteNode::setTotalTime(float time)
{
    m_totalTime = time;
    std::size_t frameCnt{ m_frameRects.size() };
    if (frameCnt > 0)
    {
        m_timePerFrame = m_totalTime / frameCnt;
    }
}

void AnimatedSpriteNode::updateCurrent(float dt)
{
    m_currentFrameTime += dt;
    if (m_currentFrameTime > m_timePerFrame)
    {
        m_currentFrame++;
        if (m_currentFrame > m_frameRects.size() - 1)
        {
            m_currentFrame = 0;
        }
        m_sprite.setTextureRect(m_frameRects[m_currentFrame]);
    }
}

void AnimatedSpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}


