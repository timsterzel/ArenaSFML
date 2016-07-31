#include "Animation/AnimationStepMovement.hpp"
#include <iostream>
#include "Calc.hpp"

AnimationStepMovement::AnimationStepMovement(sf::Vector2f startPosition, float totalDistance, sf::Vector2f direction, float duration)
: AnimationStep(duration)
, m_isStartPositionSet{ true }
, m_startPosition{ startPosition }
, m_totalDistance{ totalDistance }
// Get the direction as normalized vector
, m_direction{ Calc::normalizeVec2<sf::Vector2f>(direction) }
// When we multiply the normalized direction with the distance the parent should move per second
// we get the movement as vector
, m_movementPerSecond{ (m_totalDistance / m_duration) * m_direction }
{
}

AnimationStepMovement::AnimationStepMovement(float totalDistance, sf::Vector2f direction, float duration)
: AnimationStep(duration)
, m_isStartPositionSet{ false }
, m_totalDistance{ totalDistance }
// Get the direction as normalized vector
, m_direction{ Calc::normalizeVec2<sf::Vector2f>(direction) }
// When we multiply the normalized direction with the distance the parent should move per second
// we get the movement as vector
, m_movementPerSecond{ (m_totalDistance / m_duration) * m_direction }
{
}

bool AnimationStepMovement::isStartPositionSet() const
{
    return m_isStartPositionSet;
}

sf::Vector2f AnimationStepMovement::getStartPosition() const
{
    return m_startPosition;
}

float AnimationStepMovement::getTotalDistance() const
{
    return m_totalDistance;
}

sf::Vector2f AnimationStepMovement::getMovementSpeed() const
{
    return m_movementPerSecond;
}
