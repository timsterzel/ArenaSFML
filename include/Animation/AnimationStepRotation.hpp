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
        AnimationStepRotation(float rotation, float duration);

        float getRotation() const;
};

#endif // ANIMATIONSTEPROTATION_HPP
