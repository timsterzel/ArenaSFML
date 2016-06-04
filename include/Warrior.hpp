#ifndef WARRIOR_HPP
#define WARRIOR_HPP
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "EnumResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

class Warrior : public Entity
{
    private:
        sf::Sprite m_sprite;

    public:
        Warrior(Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder);
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // WARRIOR_HPP
