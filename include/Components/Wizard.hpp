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
  
        
        /*
        // Round attack
        bool m_isRoundAttacking;
        float m_roundAttackStanima;
        float m_roundAttackDamageMul;
        // The current rotation in degrees
        float m_roundAttackCurRot;
        // The total rotation in degrees
        float m_roundAttackTotalRot;
        // The angle in degrees per second
        float m_roundAttackAngleVel;
        // The Wizards rotation by starting attack
        float m_startRotationRoundAttack;
        
        // Dodge move
        bool m_isDodging;
        float m_dodgeStanima;
        float m_dodgeVelocity;
        // Total time of dodging
        float m_totalDodgeTime;
        // The time in seconds, while the current dodging running
        float m_curDodgeTime;
        // The direction of the dodging
        sf::Vector2f m_dodgeDir;
        */
    public:
        Wizard(RenderLayers layer, const int health, Textures textureId, 
                const ResourceHolder<sf::Texture, Textures> &textureHolder,
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
        /*
        void startCloseAttack();
        void startRoundAttack();
        void stopRoundAttack();
        void startDodging();
        void stopDodging();
        */
};

#endif // WIZARD_HPP
