#ifndef COLLISIONINFO_HPP
#define COLLISIONINFO_HPP
#include <SFML/Graphics.hpp>
#include "Components/SceneNode.hpp"

class CollisionInfo
{
    private:
        bool m_isCollision;
        float m_length;
        sf::Vector2f m_direction;
        SceneNode *m_collidedFirst;
        SceneNode *m_collidedSecond;

    public:
        explicit CollisionInfo(bool isCollision);
        CollisionInfo(bool isCollision, float length, sf::Vector2f direction, SceneNode *collidedFirst, SceneNode *collidedSecond);

        bool isCollision() const;
        float getLength() const;
        sf::Vector2f getDirection() const;
        SceneNode* getCollidedFirst() const;
        SceneNode* getCollidedSecond() const;
};

#endif // COLLISIONINFO_HPP
