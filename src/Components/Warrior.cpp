#include "Components/Warrior.hpp"
#include "Calc.hpp"
#include "Components/Weapon.hpp"
#include <iostream>
#include <vector>

Warrior::Warrior(const int health, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder)
: m_maxHealth{ health }
, m_currentHealth{ health }
, m_sprite{ textureHolder.get(textureId) }
, m_leftShoe{ nullptr }
, m_rightShoe{ nullptr }
, m_weapon{ nullptr }
, m_upperBody{ nullptr }
, m_weaponPos(0.f, 10.f)
, m_animationSword( nullptr, false )
, m_animationLeftShoe{  nullptr ,true }
, m_animationRightShoe{  nullptr ,true }
{
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    setWidth(bounds.width);
    setHeight(bounds.height);

    std::vector<AnimationStepRotation>  swordRoationSteps;
    swordRoationSteps.push_back({ 0.f, -60.f,  0.5f });
    m_animationSword.setRotationSteps(swordRoationSteps);




    /*
    std::vector<AnimationStepMovement>  swordMovementSteps;
    swordMovementSteps.push_back({ sf::Vector2f(0.f, 0.f), 100.f, sf::Vector2f(10.f, 0.f) , 1.5f });
    m_animationSword.setMovementSteps(swordMovementSteps);
    */
}

int Warrior::getCurrentHealth() const
{
    return m_currentHealth;
}

void Warrior::setCurrentHealth(const int health)
{
    m_currentHealth = health;
}

void Warrior::setBodyParts(SpriteNode *leftShoe, SpriteNode *rightShoe, SpriteNode *upperBody)
{
    m_leftShoe = leftShoe;
    m_rightShoe = rightShoe;
    m_upperBody = upperBody;
    m_animationLeftShoe.setParent(m_leftShoe);
    m_animationRightShoe.setParent(m_rightShoe);
    std::vector<AnimationStepMovement>  leftShoeMovementSteps;
    leftShoeMovementSteps.push_back({ 2.f, sf::Vector2f(1.f, 0.f) , 0.5f });
    leftShoeMovementSteps.push_back({ 2.f, sf::Vector2f(-1.f, 0.f) , 0.5f });
    m_animationLeftShoe.setMovementSteps(leftShoeMovementSteps);
    m_animationLeftShoe.start();

    m_animationRightShoe.setMovementSteps(leftShoeMovementSteps);
    m_animationRightShoe.start();
}

void Warrior::setWeapon(Weapon *weapon)
{
    m_weapon = weapon;
    m_weapon->setRotationPoint(m_weaponPos);
    m_weapon->equip(m_weaponPos);
    m_animationSword.setParent(m_weapon);
    //m_weapon->setPosition(m_weaponPos);
    //m_weapon->setPosition(10.f, 10.f);
    //m_weapon->setParent(this);
}

Weapon* Warrior::getWeapon() const
{
    return m_weapon;
}

sf::Vector2f Warrior::getWorldWeaponPos() const
{
    return getWorldTransform() * m_weaponPos;
}

bool Warrior::isAlive() const
{
    return m_currentHealth > 0;
}

void Warrior::damage(const int damage)
{
    m_currentHealth -= damage;
}

void Warrior::heal(const int health)
{
    m_currentHealth += health;
    if (m_currentHealth > m_maxHealth)
    {
        m_currentHealth = m_maxHealth;
    }
}

void Warrior::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    //target.draw(m_sprite, states);
    // Only draw weapon when it is not nullptr
    if (m_weapon)
    {
        // Add weapons transform here, because we call drawCurrent directly
        //states.transform *= m_weapon->getTransform();
        m_weapon->draw(target, states);


        // Draw weapon pos (TMP)
        sf::CircleShape circleShape{ 3.f };
        circleShape.setFillColor(sf::Color::Green);
        circleShape.setOrigin(3.f, 3.f);
        circleShape.setPosition(getWorldWeaponPos());
        target.draw(circleShape);
    }
}

void Warrior::updateCurrent(float dt)
{
    if (m_weapon)
    {
        m_animationSword.update(dt);
    }
    if (m_leftShoe)
    {
        m_animationLeftShoe.update(dt);
    }
    if (m_rightShoe)
    {
        m_animationRightShoe.update(dt);
    }
    //std::cout << "WorldPos: " << getWorldPosition().x << "|" << getWorldPosition().y
    //<< "WeaponWorldPos: " << getWorldWeaponPos().x << "|" << getWorldWeaponPos().y << std::endl;

}

void Warrior::onCommandCurrent(const Command &command, float dt)
{
    // Do command handling of parent class
    //Entity::onCommand(command, dt);
    if (command.getWorldObjectType() == m_type)
    {
        m_currentVelocity.x = 0.f;
        m_currentVelocity.y = 0.f;
        switch (command.getCommandType())
        {
            case CommandTypes::LOOK_AT :
                lookAt(command.getValues());
                break;
            case CommandTypes::ROTATE :
                break;
            case CommandTypes::MOVE_UP:
                m_currentVelocity.y = -m_velocity.y;
                break;
            case CommandTypes::MOVE_DOWN:
                m_currentVelocity.y = m_velocity.y;
                break;
            case CommandTypes::MOVE_LEFT:
                m_currentVelocity.x = -m_velocity.x;
                break;
            case CommandTypes::MOVE_RIGHT:
                m_currentVelocity.x = m_velocity.x;
                break;
            case CommandTypes::ATTACK:
                m_animationSword.start();
                break;
        }
        // Move is the same as setPosition(getPosition() + offset) of the sf::Transformable class
        move(m_currentVelocity * dt);
    }
}

void Warrior::lookAt(const sf::Vector2f LookPos)
{
    // only look to the LookPos when Warrior is not at the same position
    if (LookPos.x == getWorldPosition().x && LookPos.y == getWorldPosition().y)
    {
        return;
    }
    const sf::Vector2f UnitVecX(1.0, 0.f);
    // The angle which should be calculated have the coordinate systems midpoint at the players position,
    // so we have to translate the pos in relation to the player position
    const sf::Vector2f TranslatedLookPos = LookPos - getWorldPosition();
    const float Angle = { Calc::radToDeg(Calc::getVec2Angle<sf::Vector2f, sf::Vector2f>(UnitVecX, TranslatedLookPos)) };
    const float AngleSigned = TranslatedLookPos.y < 0.f ? -Angle : Angle;
    setRotation(AngleSigned);
}

