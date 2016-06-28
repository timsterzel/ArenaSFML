#include "Collision/CollisionInfo.hpp"

CollisionInfo::CollisionInfo(bool isCollision)
: m_isCollision{ isCollision }
, m_length{ 0.f }
, m_direction{ 0.f, 0.f }
, m_collidedFirst{ nullptr }
, m_collidedSecod { nullptr }
{

}

CollisionInfo::CollisionInfo(bool isCollision, float length, sf::Vector2f direction, SceneNode *collidedFirst, SceneNode *collidedSecond))
: m_isCollision{ isCollision }
, m_length{ length }
, m_direction{ direction }
, m_collidedFirst{ collidedFirst }
, m_collidedSecod { collidedSecond }
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

SceneNode* CollisionInfo::getCollidedFirst() const
{
    return m_collidedFirst;
}

SceneNode* CollisionInfo::getCollidedSecond() const
{
    return m_collidedSecond;
}
