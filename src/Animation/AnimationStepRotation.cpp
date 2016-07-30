#include "Animation/AnimationStepRotation.hpp"
#include <iostream>

/*
AnimationStepRotation::AnimationStepRotation(float rotation)
: m_rotation{ rotation }
{

}
*/

AnimationStepRotation::AnimationStepRotation(float rotation, float duration)
: AnimationStep(duration)
, m_rotation{ rotation }
{

}

float AnimationStepRotation::getRotation() const
{
    return m_rotation;
}
