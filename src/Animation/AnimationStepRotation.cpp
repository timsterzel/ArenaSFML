#include "Animation/AnimationStepRotation.hpp"
#include <iostream>

/*
AnimationStepRotation::AnimationStepRotation(float rotation)
: m_rotation{ rotation }
{

}
*/

AnimationStepRotation::AnimationStepRotation(float startRotation, float totalRotation, float duration)
: AnimationStep(duration)
, m_startRotation{ startRotation }
, m_totalRotation{ totalRotation }
//, m_targetRotation{ 0.f }
, m_rotationSpeed{ m_totalRotation / m_duration }
{
    //m_targetRotation = (m_startRotation + m_totalRotation);
}

float AnimationStepRotation::getStartRotation() const
{
    return m_startRotation;
}
/*
float AnimationStepRotation::getTargetRotation() const
{
    return m_targetRotation;
}
*/

float AnimationStepRotation::getTotalRotation() const
{
    return m_totalRotation;
}

float AnimationStepRotation::getRotationSpeed() const
{
    return m_rotationSpeed;
}
