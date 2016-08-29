#ifndef KNIGHT_HPP
#define KNIGHT_HPP
#include <SFML/Graphics.hpp>
#include "Components/Warrior.hpp"
#include <iostream>



class Knight : public Warrior
{
    private:
        bool m_isBlocking;
    public:
        Knight(RenderLayers layer, const int health, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder, const SpriteSheetMapHolder &spriteSheetMapHolder);

        virtual ~Knight();

        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
        virtual void updateCurrent(float dt);
        virtual void updateAI(float dt);
        virtual void onCommandCurrent(const Command &command, float dt);

        void startCloseAttack();
        void startBlocking();
        void stopBlocking();
};

#endif // KNIGHT_HPP
