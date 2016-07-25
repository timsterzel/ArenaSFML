#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <SFML/Graphics.hpp>
#include "Components/Entity.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Resources/ResourceHolder.hpp"

class Weapon : public Entity
{
    protected:
        int m_damage;

    private:
        sf::Sprite m_sprite;


    public:
        Weapon(const int damage, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder);

        int getDamage() const;
        void setDamage(const int damage);

        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

};

#endif // WEAPON_HPP
