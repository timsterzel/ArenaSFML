#include "Collision/CollisionInfo.hpp"

CollisionInfo::CollisionInfo(bool isCollision)
: m_isCollision{ isCollision }
, m_length{ 0.f }
, m_direction{ 0.f, 0.f }
{

}

CollisionInfo::CollisionInfo(bool isCollision, float length, sf::Vector2f direction)
: m_isCollision{ isCollision }
, m_length{ length }
, m_direction{ direction }
{

}

bool CollisionInfo::isCollision() const
{
    return m_isCollision;
}

float CollisionInfo::getLength() const
{
    return m_length;
}

sf::Vector2f CollisionInfo::getDirection() const
{
    return m_direction;
}
