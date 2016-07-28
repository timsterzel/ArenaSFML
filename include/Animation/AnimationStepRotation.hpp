#ifndef ANIMATIONSTEPROTATION_HPP
#define ANIMATIONSTEPROTATION_HPP
#include <SFML/Graphics.hpp>
#include "Animation/AnimationStep.hpp"

class AnimationStepRotation : public AnimationStep
{
    private:
        float m_rotation;

    public:
        explicit AnimationStepRotation(float rotation);
        explicit AnimationStepRotation(float rotation, float duration);
};

#endif // ANIMATIONSTEPROTATION_HPP
