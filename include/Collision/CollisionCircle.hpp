#ifndef COLLISIONCIRCLE_HPP
#define COLLISIONCIRCLE_HPP
#include <SFML/Graphics.hpp>
#include "Collision/Collision.hpp"

class CollisionCircle : public Collision
{
    private:
        sf::CircleShape m_circleShape;
    public:

        explicit CollisionCircle(float radius);

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // COLLISIONCIRCLE_HPP
