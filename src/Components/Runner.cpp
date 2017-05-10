#include "Components/Runner.hpp"
#include "Components/Weapon.hpp"
#include "Components/Item.hpp"
#include "Collision/CollisionRect.hpp"
#include "Collision/CollisionHandler.hpp"
#include "Calc.hpp"
#include <iostream>

Runner::Runner(RenderLayers layer, const int health, Textures textureId, 
        const ResourceHolder<sf::Texture, Textures> &textureHolder,
        const SpriteSheetMapHolder &spriteSheetMapHolder, 
        std::vector<Warrior*> &possibleTargetsInWord)
: Warrior(layer, health, textureId, textureHolder, spriteSheetMapHolder, 
        possibleTargetsInWord)
, m_animCloseAttack( nullptr, false )
//, m_animStrongAttack( nullptr, false )
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
//, m_strongAttackStanima{ 30.f }
//, m_strongAttackDamageMul{ 3.f }
, m_isDodging{ false }
, m_dodgeStanima{ 30.f }
, m_dodgeVelocity{ 300.f }
, m_totalDodgeTime{ 0.2 }
, m_curDodgeTime{ 0.f }
{
    setVelocity(80.f);
    // Animation
    std::vector<AnimationStepRotation>  swordRoationStepsCloseAtt;
    swordRoationStepsCloseAtt.push_back({ 0.f, -60.f,  0.3f });
    m_animCloseAttack.setRotationSteps(swordRoationStepsCloseAtt);
    
    /*
    std::vector<AnimationStepMovement>  swordMovementStepsStrongAtt;
    swordMovementStepsStrongAtt.push_back({ -5.f, { 1, 0 },  0.3f });
    swordMovementStepsStrongAtt.push_back({ 5.f, { 1, 0 },  0.3f });
    m_animStrongAttack.setMovementSteps(swordMovementStepsStrongAtt);
    */

    std::unique_ptr<Weapon> sword(new Weapon(RenderLayers::WEAPON, 10.f, 
                textureHolder.get(textureId), 
                spriteSheetMapHolder.getRectData(textureId, "sword")));
    sword->setType(WorldObjectTypes::WEAPON);
    sword->setPosition(0.f, 0.f);
    //swordPlayer->setRotationPoint(0.f, swordPlayer->getSpriteHeight() / 2.f);
    sword->setOrigin(-10.f, 0.f);
    std::unique_ptr<CollisionShape> collisionShapeSword(new CollisionRect(
                { sword->getSpriteWidth(), sword->getSpriteHeight() }));
    sword->setCollisionShape(std::move(collisionShapeSword));
    setWeapon(sword.get());
    attachChild(std::move(sword));

    std::unique_ptr<CollisionShape> closeCombatArea(new CollisionCircle(9.f));
    m_closeCombatArea = std::move(closeCombatArea);
    m_closeCombatArea->setParent(this);
    m_closeCombatArea->setPosition(9.f, 0.f);
    m_closeCombatArea->setDraw(true);
    /*
    std::vector<AnimationStepMovement>  swordMovementSteps;
    swordMovementSteps.push_back({ sf::Vector2f(0.f, 0.f), 100.f, sf::Vector2f(10.f, 0.f) , 1.5f });
    m_animationSword.setMovementSteps(swordMovementSteps);
    */
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
            case CommandTypes::ACTION1:
                startCloseAttack();
                break;
            case CommandTypes::ACTION2:
                startDodging();
                break;
            case CommandTypes::ACTION3:
                startRoundAttack();
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
    CollisionInfo collisionInfo = m_closeCombatArea->isColliding(*m_actualTarget->getCollisionShape());
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
    if (m_weapon != nullptr)
    {
        std::cout << "Weapon is not null\n";
    }
    if (m_weapon && !m_animCloseAttack.isRunning() && 
            m_currentStamina >= m_closeAttackStanima)
    {
        m_animCloseAttack.start();
        m_weapon->setIsCollisionCheckOn(true);
        m_weapon->setDamageMultiplicator(m_closeAttackDamageMul);
        m_weapon->startNewAttack();
        removeStanima(m_closeAttackStanima);
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
        setIsCollisionCheckOn(false);
        m_isDodging = true;
        m_curDodgeTime = 0.f;
        // The dodge direction is the direction where the runner looking at
        m_dodgeDir = Calc::degAngleToDirectionVector(getRotation());
        removeStanima(m_dodgeStanima);
    }
}

void Runner::stopDodging()
{
    m_isDodging = false;
    setIsCollisionCheckOn(true);
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
