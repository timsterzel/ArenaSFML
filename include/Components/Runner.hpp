#ifndef RUNNER_HPP
#define RUNNER_HPP
#include <SFML/Graphics.hpp>
#include "Components/Warrior.hpp"
#include <iostream>

class Runner : public Warrior
{
    private:
        Animation m_animCloseAttack;
        //Animation m_animStrongAttack;
        
        float m_closeAttackStanima;
        float m_closeAttackDamageMul;
        //float m_strongAttackStanima;
        //float m_strongAttackDamageMul;


    public:
        Runner(RenderLayers layer, const int health, Textures textureId, 
                const ResourceHolder<sf::Texture, Textures> &textureHolder,
                const SpriteSheetMapHolder &spriteSheetMapHolder, 
                std::vector<Warrior*> &possibleTargetsInWord);

        virtual ~Runner();

        virtual void drawCurrent(sf::RenderTarget &target, 
                sf::RenderStates states) const;
    protected:
        virtual void weaponAdded();
    
    private:
        virtual void updateCurrent(float dt);
        virtual void updateAI(float dt);
        virtual void onCommandCurrent(const Command &command, float dt);

        void startCloseAttack();
        //void startStrongAttack();
        void startBlocking();
        void stopBlocking();
};

#endif // RUNNER_HPP