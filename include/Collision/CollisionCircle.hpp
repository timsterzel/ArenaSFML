#ifndef COLLISIONCIRCLE_HPP
#define COLLISIONCIRCLE_HPP
#include <SFML/Graphics.hpp>
#include "Collision/CollisionShape.hpp"
#include "Components/SceneNode.hpp"

class CollisionCircle : public CollisionShape
{
    private:
        sf::CircleShape m_circleShape;
    public:

        explicit CollisionCircle(float radius);

        float getRadius() const;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        virtual bool isColliding(const CollisionShape &collider) const;

    private:
        virtual bool isColliding(const CollisionCircle &collider) const;
        virtual bool isColliding(const CollisionRect &collider) const;
};

#endif // COLLISIONCIRCLE_HPP
