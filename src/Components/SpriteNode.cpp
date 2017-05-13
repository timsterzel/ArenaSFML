#include "Components/SpriteNode.hpp"
#include <iostream>

SpriteNode::SpriteNode(RenderLayers layer, const sf::Texture &texture, bool centerOrigin)
: Entity(layer)
, m_sprite(texture)
, m_timePerFrame{ 0.f }
, m_currentFrameTime{ 0.f }
, m_currentFrame{ 0 }
, m_repeat{ false }
{
    if (centerOrigin)
    {
        sf::FloatRect bounds = m_sprite.getLocalBounds();
        m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }
}

SpriteNode::SpriteNode(RenderLayers layer, const sf::Texture &texture, const sf::IntRect &rect, bool centerOrigin)
: Entity(layer)
, m_sprite(texture, rect)
, m_timePerFrame{ 0.f }
, m_currentFrameTime{ 0.f }
, m_currentFrame{ 0 }
, m_repeat{ false }
{
    if (centerOrigin)
    {
        m_sprite.setOrigin(rect.width / 2.f, rect.height / 2.f);
    }
}

SpriteNode::SpriteNode(RenderLayers layer, 
        const sf::Texture &texture, bool centerOrigin, bool repeat)
//: SpriteNode(layer, texture, centerOrigin)
: Entity{ layer }
, m_sprite{ texture }
, m_timePerFrame{ 0.f }
, m_currentFrameTime{ 0.f }
, m_currentFrame{ 0 }
, m_repeat{ repeat }
{

}

SpriteNode::SpriteNode(RenderLayers layer, 
        const sf::Texture &texture, const std::vector<sf::IntRect> frameRects, 
        bool centerOrigin, float totalTime, bool repeat)
//: SpriteNode(layer, texture, centerOrigin)
: Entity{ layer }
, m_sprite{ texture }
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
            m_sprite.setOrigin(frameRect.width / 2.f, frameRect.height / 2.f);
        }
    }
}

SpriteNode::~SpriteNode()
{

}

sf::Sprite& SpriteNode::getSprite()
{
    return m_sprite;
}

void SpriteNode::setTotalTime(float time)
{
    m_totalTime = time;
    std::size_t frameCnt{ m_frameRects.size() };
    if (frameCnt > 0)
    {
        m_timePerFrame = m_totalTime / frameCnt;
    }
}

void SpriteNode::updateCurrent(float dt)
{
    if (m_frameRects.size() <= 0)
    {
        return;
    }
    m_currentFrameTime += dt;
    if (m_currentFrameTime > m_timePerFrame)
    {
        m_currentFrame++;
        if (m_currentFrame > m_frameRects.size() - 1)
        {
            m_currentFrame = 0;
        }
        m_sprite.setTextureRect(m_frameRects[m_currentFrame]);
        m_currentFrameTime = 0.f;
    }
}

void SpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}


