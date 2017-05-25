#ifndef WIZARD_HPP
#define WIZARD_HPP
#include <SFML/Graphics.hpp>
#include "Components/Warrior.hpp"
#include <iostream>

class Wizard : public Warrior
{
    private:
        Animation m_animFireballAttack;
        //Animation m_animStrongAttack;
        
        // Fireball Attack
        float m_fireballAttackStanima;
        // Store the int rects of the firebatt texture
        std::vector<sf::IntRect> m_fireballFrameRects;
        float m_fireballDamage;
        
        bool m_isHealing;
        // How much health is resored per second
        float m_healRestoreRate;
        // How much stanima per second get removed by healing
        float m_healStanimaRate;
        float m_currentHealColorStep;
        // The time it takes to inteprole from one color to the next
        float m_totalHealColorStepTime;
        float m_currentHealColorStepTime;
        
    public:
        Wizard(RenderLayers layer, const int health, const std::string &textureId, 
                const ResourceHolder<sf::Texture> &textureHolder,
                const SpriteSheetMapHolder &spriteSheetMapHolder, 
                std::vector<Warrior*> &possibleTargetsInWord);

        virtual ~Wizard();

        virtual void drawCurrent(sf::RenderTarget &target, 
                sf::RenderStates states) const;
    protected:
        virtual void weaponAdded();
    
    private:
        virtual void updateCurrent(float dt);
        virtual void updateAI(float dt);
        virtual void onCommandCurrent(const Command &command, float dt);
        // Update the color of the warrior
        void updateHealColor(float dt);

        void startFireballAttack();
        void startHealing();
        void stopHealing();
        // Apply color to all sprites of wizard
        void applyColor(sf::Color color);
        // Restore the default color of the sprites
        void removeColorEffects();
};

#endif // WIZARD_HPP
