#include "Animation/AnimationStep.hpp"
#include <iostream>

AnimationStep::AnimationStep()
: m_duration{ 0.f }
{

}
AnimationStep::AnimationStep(float duration)
: m_duration{ duration }
{

}

float AnimationStep::getDuration() const
{
    return m_duration;
}
