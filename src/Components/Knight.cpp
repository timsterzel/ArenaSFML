#include "Components/Knight.hpp"
#include "Components/Weapon.hpp"
#include "Components/Item.hpp"
#include "Collision/CollisionRect.hpp"
#include "Collision/CollisionHandler.hpp"
#include "Calc.hpp"
#include <iostream>

Knight::Knight(RenderLayers layer, const int health, const std::string &textureId,
        const ResourceHolder<sf::Texture> &textureHolder,
        const SpriteSheetMapHolder &spriteSheetMapHolder, 
        std::vector<Warrior*> &possibleTargetsInWord)
: Warrior(layer, health, textureId, textureHolder, spriteSheetMapHolder, 
        possibleTargetsInWord)
, m_animCloseAttack{ nullptr, false }
//, m_animStrongAttack{ nullptr, false }
, m_WeaponDamage{ 30.f }
, m_closeAttackStanima{ 10.f }
, m_closeAttackDamageMul{ 1.f }
, m_isStrongAttackRunning{ false }
, m_strongAttackStanima{ 80.f }
, m_strongAttackDamageMul{ 2.f }
, m_strongAttackVelocity{ 160.f }
, m_totalStrongAttackTime{ 0.3f }
, m_curStrongAttackTime{ 0.f }
{
    setVelocity(60.f);
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
    
    std::unique_ptr<Weapon> sword(new Weapon(RenderLayers::WEAPON, m_WeaponDamage, 
                textureHolder.get(textureId), 
                spriteSheetMapHolder.getRectData(textureId, "sword")));
    sword->setType(WorldObjectTypes::WEAPON);
    sword->setOrigin(0.f, -10.f);
    std::unique_ptr<CollisionShape> collisionShapeSword(new CollisionRect(
                { sword->getSpriteWidth(), sword->getSpriteHeight() }));
    sword->setCollisionShape(std::move(collisionShapeSword));
    setWeapon(sword.get());
    attachChild(std::move(sword));
    

    std::unique_ptr<Item> shield(new Item(RenderLayers::WEAPON, 
                textureHolder.get(textureId), 
                spriteSheetMapHolder.getRectData(textureId, "shield")));
    shield->setType(WorldObjectTypes::SHIELD);
    shield->setRotation(90.f);
    std::unique_ptr<CollisionShape> collisionShapeShield(
            new CollisionRect({ shield->getSpriteWidth(), 
                shield->getSpriteHeight() }));
    shield->setCollisionShape(std::move(collisionShapeShield));
    // Shield pos
    m_shieldEquipPos = sf::Vector2f{ getWidth() / 2.f - 3.f, 0.f };
    shield->setPosition(m_shieldEquipPos);
    m_shield = shield.get();
    attachChild(std::move(shield));

    std::unique_ptr<CollisionShape> closeCombatArea(new CollisionCircle(9.f));
    m_closeCombatArea = std::move(closeCombatArea);
    m_closeCombatArea->setParent(this);
    m_closeCombatArea->setPosition(9.f, 0.f);

    // Collision shape
    std::unique_ptr<CollisionShape> collisionShape{ 
        std::make_unique<CollisionCircle>(12.f) };
    setCollisionShape(std::move(collisionShape));
}

Knight::~Knight()
{

}

Item* Knight::getShield() const
{
    return m_shield;
}

void Knight::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    Warrior::drawCurrent(target, states);
}

void Knight::updateCurrent(float dt)
{
    if(m_isStrongAttackRunning) 
    {
        m_curStrongAttackTime += dt;
        //m_currentDirection = m_strongAttackDir;
        moveInDirection(m_strongAttackDir, m_strongAttackVelocity * dt);
        if (m_curStrongAttackTime > m_totalStrongAttackTime)
        {
            stopStrongAttack();
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
            /*
            else if (m_animStrongAttack.isRunning())
            {
                m_animStrongAttack.update(dt);
            }
            */
            else
            {
                m_weapon->setIsCollisionCheckOn(false);
            }
        }


    }
}

void Knight::onCommandCurrent(const Command &command, float dt)
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
            case CommandTypes::ACTION_START:
                startBlocking();
                break;
            case CommandTypes::SPECIAL_ACTION:
                startStrongAttack();
                break;
            case CommandTypes::ACTION_STOP:
                stopBlocking();
                break;
            default:
                break;

        }

        // Move is the same as setPosition(getPosition() + offset) of the 
        // sf::Transformable class
        //move(m_currentVelocity * dt);
        //moveInDirection(m_currentDirection, m_currentVelocity * dt);
        moveInActualDirection(m_currentVelocity * dt);
    }
}

void Knight::updateAI(float dt)
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

void Knight::startCloseAttack()
{
    if (m_weapon && !m_animCloseAttack.isRunning() &&
            !isBlocking() &&
            m_currentStamina >= m_closeAttackStanima)
    {
        m_animCloseAttack.start();
        m_weapon->setIsCollisionCheckOn(true);
        m_weapon->setDamageMultiplicator(m_closeAttackDamageMul);
        m_weapon->startNewAttack();
        removeStanima(m_closeAttackStanima);
    }
}

void Knight::stopCloseAttack()
{
    if (m_weapon)
    {
        m_weapon->setRotation(0.f);
    }
}

void Knight::startStrongAttack()
{
    if (m_weapon && /*!m_animStrongAttack.isRunning() &&*/ 
            /*!isBlocking() &&*/ 
            m_currentStamina >= m_strongAttackStanima)
    {
        m_isStrongAttackRunning = true;
        m_curStrongAttackTime = 0.f;
        // The attack direction is the direction where the knight looking at
        m_strongAttackDir = Calc::degAngleToDirectionVector(getRotation() + 90.f);
        m_weapon->setRotation(0.f);
        //m_animStrongAttack.start();
        m_weapon->setIsCollisionCheckOn(true);
        m_weapon->setDamageMultiplicator(m_strongAttackDamageMul);
        m_weapon->startNewAttack();
        removeStanima(m_strongAttackStanima);
        startBlocking();
    }
}

void Knight::stopStrongAttack()
{
    m_isStrongAttackRunning = false;
    stopBlocking();
}

void Knight::startBlocking()
{
    m_animCloseAttack.stop();
    if (m_shield && !m_isBlocking)
    {
        m_isBlocking = true;
        //m_shield->setRotation(270.f);
        //m_shield->setPosition(10.f, 0.f);
        m_shield->setRotation(0.f);
        m_shield->setPosition(0.f, 10.f);
    }
}

void Knight::stopBlocking()
{
    {
        m_isBlocking = false;
        //m_shield->setRotation(0.f);
        //m_shield->setPosition(m_shieldEquipPos);
        m_shield->setRotation(90.f);
        m_shield->setPosition(m_shieldEquipPos);
    }
}

void Knight::weaponAdded()
{
    m_animCloseAttack.setParent(m_weapon);
    //m_animStrongAttack.setParent(m_weapon);
}

void Knight::handleDamage(Weapon *weapon)
{

    if (m_shield && weapon->isColliding(*m_shield).isCollision() && isBlocking())
    {
        weapon->addHitID(getID());
        float actualStanima{ getCurrentStanima() };
        float weaponDamage{ weapon->getTotalDamage() };
        // If warrior has enough stanima, warrior lose stanima
        // instead of health
        if (actualStanima >= weaponDamage)
        {
            removeStanima(weaponDamage);
        }
        // Else the warrior remove as much health, which the warrior
        // cant block with stanima
        else
        {
            setCurrentStanima(0.f);
            damage(weaponDamage - actualStanima);
            stopBlocking();
        }
    }
    else
    {
        Warrior::handleDamage(weapon);
    }
}
