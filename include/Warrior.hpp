#ifndef WARRIOR_HPP
#define WARRIOR_HPP
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Warrior : public Entity
{
    private:
        sf::Sprite m_sprite;

    public:
        Warrior();
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // WARRIOR_HPP
