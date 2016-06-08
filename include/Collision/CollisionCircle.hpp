#ifndef COLLISIONCIRCLE_HPP
#define COLLISIONCIRCLE_HPP
#include <SFML/Graphics.hpp>
#include "Collision/Collision.hpp"
#include "Components/SceneNode.hpp"

class CollisionCircle : public Collision
{
    private:
        sf::CircleShape m_circleShape;
    public:

        explicit CollisionCircle(float radius);

        sf::Vector2f getPosition() const;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        virtual bool isColliding(const Collision &collider) const;

    private:

        virtual bool isColliding(const CollisionCircle &collider) const;
};

#endif // COLLISIONCIRCLE_HPP
