#ifndef COLLISIONCIRCLE_HPP
#define COLLISIONCIRCLE_HPP
#include <SFML/Graphics.hpp>
#include "Collision/CollisionShape.hpp"
#include "Components/SceneNode.hpp"

class CollisionCircle : public CollisionShape
{
    private:
        float m_radius;
    public:

        explicit CollisionCircle(float radius);

        float getRadius() const;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        virtual bool isColliding(CollisionShape &collider);

    private:
        virtual bool isColliding(CollisionCircle &collider);
        virtual bool isColliding(CollisionRect &collider);
};

#endif // COLLISIONCIRCLE_HPP
