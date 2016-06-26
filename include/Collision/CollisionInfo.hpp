#ifndef COLLISIONINFO_HPP
#define COLLISIONINFO_HPP
#include <SFML/Graphics.hpp>

class CollisionInfo
{
    private:
        bool m_isCollision;
        float m_length;
        sf::Vector2f m_direction;
    public:
        explicit CollisionInfo(bool isCollision);
        CollisionInfo(bool isCollision, float length, sf::Vector2f direction);

        bool isCollision() const;
        float getLength() const;
        sf::Vector2f getDirection() const;
};

#endif // COLLISIONINFO_HPP
