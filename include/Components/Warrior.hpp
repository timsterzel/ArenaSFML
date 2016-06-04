#ifndef WARRIOR_HPP
#define WARRIOR_HPP
#include <SFML/Graphics.hpp>
#include "Components/Entity.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Resources/ResourceHolder.hpp"

class Warrior : public Entity
{
    private:
        sf::Sprite m_sprite;

    public:
        Warrior(Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder);
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // WARRIOR_HPP
