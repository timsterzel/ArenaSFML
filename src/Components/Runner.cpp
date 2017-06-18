#include "Components/Runner.hpp"
#include "Components/Weapon.hpp"
#include "Components/Item.hpp"
#include "Collision/CollisionRect.hpp"
#include "Collision/CollisionHandler.hpp"
#include "Calc.hpp"
#include <iostream>

Runner::Runner(RenderLayers layer, SoundPlayer &sound, const int health, 
        const std::string &textureId,
        const ResourceHolder<sf::Texture> &textureHolder,
        const SpriteSheetMapHolder &spriteSheetMapHolder, 
        std::vector<Warrior*> &possibleTargetsInWord)
: Warrior(layer, sound, health, textureId, textureHolder, spriteSheetMapHolder, 
        possibleTargetsInWord)
, m_animCloseAttack( nullptr, false )
// Close Attack
, m_closeAttackStanima{ 10.f }
, m_closeAttackDamageMul{ 1.f }
// Round Attack
, m_isRoundAttacking{ false }
, m_roundAttackStanima{ 40.f }
, m_roundAttackDamageMul{ 1.5f }
, m_roundAttackCurRot{ 0.f }
, m_roundAttackTotalRot{ 360.f }
, m_roundAttackAngleVel{ 720.f }
, m_startRotationRoundAttack{ 0.f }
, m_isDodging{ false }
, m_dodgeStanima{ 30.f }
, m_dodgeVelocity{ 300.f }
, m_totalDodgeTime{ 0.2 }
, m_curDodgeTime{ 0.f }
{
    addType(WorldObjectTypes::RUNNER);
    setVelocity(80.f);
    // Animation
    std::vector<AnimationStepRotation>  swordRoationStepsCloseAtt;
    swordRoationStepsCloseAtt.push_back({ 0.f, -60.f,  0.3f });
    m_animCloseAttack.setRotationSteps(swordRoationStepsCloseAtt);
    m_animCloseAttack.setOnAnimationStoppedListener([this]()
    {
        stopCloseAttack();
    });
    m_animCloseAttack.setOnAnimationCompletedListener([this]()
    {
        stopCloseAttack();
    });

    std::unique_ptr<Weapon> sword(new Weapon(RenderLayers::WEAPON, 10.f, 
                textureHolder.get(textureId), 
                spriteSheetMapHolder.getRectData(textureId, "sword")));
    sword->setPosition(0.f, 0.f);
    sword->setOrigin(0.f, -10.f);
    std::unique_ptr<CollisionShape> collisionShapeSword(new CollisionRect(
                { sword->getSpriteWidth(), sword->getSpriteHeight() }));
    sword->setCollisionShape(std::move(collisionShapeSword));
    setWeapon(sword.get());
    attachChild(std::move(sword));

    std::unique_ptr<CollisionShape> closeCombatArea(new CollisionCircle(9.f));
    m_closeCombatArea = std::move(closeCombatArea);
    m_closeCombatArea->setParent(this);
    m_closeCombatArea->setPosition(9.f, 0.f);
    // Collision shape
    std::unique_ptr<CollisionShape> collisionShape{ 
        std::make_unique<CollisionCircle>(10.f) };
    setCollisionShape(std::move(collisionShape));
}

Runner::~Runner()
{

}

void Runner::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    Warrior::drawCurrent(target, states);
}

void Runner::updateCurrent(float dt)
{
    if(m_isDodging) 
    {
        m_curDodgeTime += dt;
        moveInDirection(m_dodgeDir, m_dodgeVelocity * dt);
        if (m_curDodgeTime > m_totalDodgeTime)
        {
            stopDodging();
        }
    }
    else if(m_isRoundAttacking) 
    {
        m_roundAttackCurRot += m_roundAttackAngleVel * dt;
        setRotation(m_startRotationRoundAttack + m_roundAttackCurRot);
        if (m_roundAttackCurRot >= m_roundAttackTotalRot)
        {
            stopRoundAttack();
        }
    }
    else
    {
        Warrior::updateCurrent(dt);
        if (m_weapon)
        {
            if (m_animCloseAttack.isRunning())
            {
                m_animCloseAttack.update(dt);
            }
            else
            {
                m_weapon->setIsCollisionCheckOn(false);
            }
        }
    }
}

void Runner::onCommandCurrent(const Command &command, float dt)
{
    // Do command handling of parent class
    //Entity::onCommand(command, dt);
    Warrior::onCommandCurrent(command, dt);
    if (command.getWorldObjectType() & m_type)
    {
        m_currentVelocity = 0.f;
        m_currentDirection.x = 0.f;
        m_currentDirection.y = 0.f;
        switch (command.getCommandType())
        {
            case CommandTypes::ACTION_1:
                startCloseAttack();
                break;
            case CommandTypes::ACTION_2:
                startRoundAttack();
                break;
            case CommandTypes::SPECIAL_ACTION:
                startDodging();
                break;
            /*
            case CommandTypes::START_BLOCKING:
                startBlocking();
                break;
            case CommandTypes::STOP_BLOCKING:
                stopBlocking();
                break;
            */
            default:
                break;

        }

        // Move is the same as setPosition(getPosition() + offset) of the sf::Transformable class
        //move(m_currentVelocity * dt);
        //moveInDirection(m_currentDirection, m_currentVelocity * dt);
        moveInActualDirection(m_currentVelocity * dt);
    }
}

void Runner::updateAI(float dt)
{
    m_isMoving = false;
    Warrior::updateAI(dt);
    if (!m_actualTarget)
    {
        return;
    }

    lookAt(m_actualTarget->getPosition());
    CollisionInfo collisionInfo = 
        m_closeCombatArea->isColliding(*m_actualTarget->getCollisionShape());
    if (collisionInfo.isCollision())
    {
        startCloseAttack();
    }
    else
    {
        // Follow target
        m_currentVelocity = m_velocity;
        m_currentDirection = m_actualTarget->getWorldPosition() - getWorldPosition();
        m_isMoving = true;
        moveInActualDirection(m_currentVelocity * dt);
    }
}

void Runner::makeTransparent()
{
    m_leftShoe->getSprite().setColor(sf::Color(255, 255, 255, 128));
    m_rightShoe->getSprite().setColor(sf::Color(255, 255, 255, 128));
    m_upperBody->getSprite().setColor(sf::Color(255, 255, 255, 128));
    if (m_weapon)
    {
        m_weapon->getSprite().setColor(sf::Color(255, 255, 255, 128));
    }
}
        
void Runner::makeInTransparent()
{
    m_leftShoe->getSprite().setColor(sf::Color::White);
    m_rightShoe->getSprite().setColor(sf::Color::White);
    m_upperBody->getSprite().setColor(sf::Color::White);
    if (m_weapon)
    {
        m_weapon->getSprite().setColor(sf::Color::White);
    }
}

void Runner::startCloseAttack()
{
    if (m_weapon && !m_animCloseAttack.isRunning() && 
            m_currentStamina >= m_closeAttackStanima)
    {
        m_animCloseAttack.start();
        m_weapon->setIsCollisionCheckOn(true);
        m_weapon->setDamageMultiplicator(m_closeAttackDamageMul);
        m_weapon->startNewAttack();
        removeStanima(m_closeAttackStanima);
        m_sound.play("swoosh1");
    }
}

void Runner::stopCloseAttack()
{
    if (m_weapon)
    {
        m_weapon->setRotation(0.f);
    }
}

void Runner::startRoundAttack()
{
    if (!m_isDodging && !m_isRoundAttacking && 
            m_currentStamina >= m_roundAttackStanima && m_weapon)
    {
        m_isRoundAttacking = true;
        m_roundAttackCurRot = 0.f;
        m_startRotationRoundAttack = getRotation();
        m_weapon->setRotation(270.f);
        m_weapon->setIsCollisionCheckOn(true);
        m_weapon->setDamageMultiplicator(m_roundAttackDamageMul);
        m_weapon->startNewAttack();
        removeStanima(m_roundAttackStanima);
    }
}

void Runner::stopRoundAttack()
{
    m_isRoundAttacking = false;
    m_weapon->setRotation(0.f);
    m_weapon->setIsCollisionCheckOn(false);
}

void Runner::startDodging()
{
    if (!m_isRoundAttacking && m_currentStamina >= m_dodgeStanima)
    {
        makeTransparent();
        //setIsCollisionCheckOn(false);
        // Only should collide with level objects
        setColisionWhiteListTypes(WorldObjectTypes::LEVEL);
        m_isDodging = true;
        m_curDodgeTime = 0.f;
        // The dodge direction is the direction where the runner looking at
        m_dodgeDir = Calc::degAngleToDirectionVector(getRotation() + 90.f);
        removeStanima(m_dodgeStanima);
        m_sound.play("dodge");
    }
}

void Runner::stopDodging()
{
    m_isDodging = false;
    clearCollisionWhiteListTypes();
    makeInTransparent();
}
/*
void Runner::startStrongAttack()
{
    if (m_weapon && !m_animStrongAttack.isRunning() && 
            m_currentStamina >= m_strongAttackStanima)
    {
        m_weapon->setRotation(0.f);
        m_animStrongAttack.start();
        m_weapon->setIsCollisionCheckOn(true);
        m_weapon->setDamageMultiplicator(m_strongAttackDamageMul);
        m_weapon->startNewAttack();
        removeStanima(m_strongAttackStanima);
    }
}
*/

void Runner::weaponAdded()
{
    m_animCloseAttack.setParent(m_weapon);
    //m_animStrongAttack.setParent(m_weapon);
}
