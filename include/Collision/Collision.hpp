#ifndef COLLISION_HPP
#define COLLISION_HPP
#include <SFML/Graphics.hpp>

class Collision
{
    private:

    public:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // COLLISION_HPP
