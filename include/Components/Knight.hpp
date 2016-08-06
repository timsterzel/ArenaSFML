#ifndef KNIGHT_HPP
#define KNIGHT_HPP
#include <SFML/Graphics.hpp>
#include "Components/Warrior.hpp"



class Knight : public Warrior
{

    private:

    public:
        Knight(const int health, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder);

        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
        virtual void updateCurrent(float dt);
        virtual void onCommandCurrent(const Command &command, float dt);
        void lookAt(sf::Vector2f pos);
};

#endif // KNIGHT_HPP
