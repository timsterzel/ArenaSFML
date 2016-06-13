#include "Collision/CollisionRect.hpp"
#include "Collision/CollisionHandler.hpp"

CollisionRect::CollisionRect(sf::Vector2f rectSize)
: m_width{ rectSize.x }
, m_height{ rectSize.y }
{

}

float CollisionRect::getWidth() const
{
    return m_width;
}

float CollisionRect::getHeight() const
{
    return m_height;
}

float CollisionRect::getWorldRotation() const
{
    float rotation = { getRotation() };
    if (m_parent != nullptr)
    {
        rotation += m_parent->getWorldRotation();
    }
    return rotation;
}

void CollisionRect::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape rect({ m_width, m_height });
    rect.setFillColor(sf::Color(255, 0, 0, 160));
    rect.setOrigin(m_width / 2.f, m_height / 2.f);
    target.draw(rect, states);
}

bool CollisionRect::isColliding(const CollisionShape &collider) const
{
    return collider.isColliding(*this);
}

bool CollisionRect::isColliding(const CollisionCircle &collider) const
{
    return CollisionHandler::isColliding(*this, collider);
}

bool CollisionRect::isColliding(const CollisionRect &collider) const
{
    return CollisionHandler::isColliding(*this, collider);
}
