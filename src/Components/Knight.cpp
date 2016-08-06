#include "Components/Knight.hpp"
#include <Components/Weapon.hpp>
#include <iostream>

Knight::Knight(const int health, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder)
: Warrior(health, textureId, textureHolder)
{
    std::vector<AnimationStepRotation>  swordRoationSteps;
    swordRoationSteps.push_back({ 0.f, -60.f,  0.5f });
    m_animationWeapon.setRotationSteps(swordRoationSteps);

    /*
    std::vector<AnimationStepMovement>  swordMovementSteps;
    swordMovementSteps.push_back({ sf::Vector2f(0.f, 0.f), 100.f, sf::Vector2f(10.f, 0.f) , 1.5f });
    m_animationSword.setMovementSteps(swordMovementSteps);
    */
}




void Knight::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    Warrior::drawCurrent(target, states);
    // Only draw weapon when it is not nullptr
    /*
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
    */
}

void Knight::updateCurrent(float dt)
{
    Warrior::updateCurrent(dt);
    /*
    if (m_weapon)
    {
        m_animationWeapon.update(dt);
    }
    if (m_leftShoe)
    {
        m_animationLeftShoe.update(dt);
    }
    if (m_rightShoe)
    {
        m_animationRightShoe.update(dt);
    }*/
    //std::cout << "WorldPos: " << getWorldPosition().x << "|" << getWorldPosition().y
    //<< "WeaponWorldPos: " << getWorldWeaponPos().x << "|" << getWorldWeaponPos().y << std::endl;

}

void Knight::onCommandCurrent(const Command &command, float dt)
{
    // Do command handling of parent class
    //Entity::onCommand(command, dt);
    Warrior::onCommandCurrent(command, dt);a
    if (command.getWorldObjectType() == m_type)
    {
        m_currentVelocity.x = 0.f;
        m_currentVelocity.y = 0.f;
        switch (command.getCommandType())
        {
            case CommandTypes::ATTACK:
                m_animationWeapon.start();
                break;
        }
        // Move is the same as setPosition(getPosition() + offset) of the sf::Transformable class
        move(m_currentVelocity * dt);
    }
}



