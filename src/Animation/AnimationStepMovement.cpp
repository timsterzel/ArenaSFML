#include "Animation/AnimationStepMovement.hpp"
#include <iostream>
#include "Calc.hpp"

AnimationStepMovement::AnimationStepMovement(sf::Vector2f startPosition, float length, sf::Vector2f direction, float duration)
: AnimationStep(duration)
, m_startPosition{ startPosition }
, m_length{ length }
// Get the direction as normalized vector
, m_direction{ Calc::normalizeVec2<sf::Vector2f>(direction) }
// When we multiply the normalized direction with the distance the parent should move per second
// we get the movement as vector
, m_movementPerSecond{ (m_length / m_duration) * m_direction }
{
}

sf::Vector2f AnimationStepMovement::getStartPosition() const
{
    return m_startPosition;
}
/*
float AnimationStepRotation::getTargetRotation() const
{
    return m_targetRotation;
}
*/

float AnimationStepMovement::getLength() const
{
    return m_length;
}

sf::Vector2f AnimationStepMovement::getMovementSpeed() const
{
    return m_movementPerSecond;
}
