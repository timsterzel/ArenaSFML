#ifndef WIZARD_HPP
#define WIZARD_HPP
#include <SFML/Graphics.hpp>
#include "Components/Warrior.hpp"
#include <iostream>



class Wizard : public Warrior
{

    private:
        Animation m_animCloseAttack;

    public:
        Wizard(RenderLayers layer, const int health, Textures textureId, 
                const ResourceHolder<sf::Texture, Textures> &textureHolder,
                const SpriteSheetMapHolder &spriteSheetMapHolder, 
                std::vector<Warrior*> &possibleTargetsInWord);
        ~Wizard();

        virtual void drawCurrent(sf::RenderTarget &target, 
                sf::RenderStates states) const;

    protected:
        virtual void weaponAdded();

    private:
        virtual void updateCurrent(float dt);
        virtual void onCommandCurrent(const Command &command, float dt);
        void lookAt(sf::Vector2f pos);
};

#endif // WIZARD_HPP
