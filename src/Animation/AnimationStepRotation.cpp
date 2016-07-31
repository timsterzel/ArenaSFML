#include "Animation/AnimationStepRotation.hpp"
#include <iostream>

AnimationStepRotation::AnimationStepRotation(float startRotation, float totalRotation, float duration)
: AnimationStep(duration)
, m_isStartRotationSet{ true }
, m_startRotation{ startRotation }
, m_totalRotation{ totalRotation }
, m_rotationSpeed{ m_totalRotation / m_duration }
{

}

AnimationStepRotation::AnimationStepRotation(float totalRotation, float duration)
: AnimationStep(duration)
, m_isStartRotationSet{ false }
, m_totalRotation{ totalRotation }
, m_rotationSpeed{ m_totalRotation / m_duration }
{

}

bool AnimationStepRotation::isStartRotationSet() const
{
    return m_isStartRotationSet;
}

float AnimationStepRotation::getStartRotation() const
{
    return m_startRotation;
}


float AnimationStepRotation::getTotalRotation() const
{
    return m_totalRotation;
}

float AnimationStepRotation::getRotationSpeed() const
{
    return m_rotationSpeed;
}
