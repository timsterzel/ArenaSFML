#ifndef ANIMATIONSTEPROTATION_HPP
#define ANIMATIONSTEPROTATION_HPP
#include <SFML/Graphics.hpp>
#include "Animation/AnimationStep.hpp"

class AnimationStepRotation : public AnimationStep
{
    private:
        bool m_isStartRotationSet;
        float m_startRotation;
        float m_totalRotation;
        // The Rotation speed in degrees per second
        float m_rotationSpeed;

    public:
        AnimationStepRotation(float startRotation, float totalRotation, float duration);
        AnimationStepRotation(float totalRotation, float duration);

        bool isStartRotationSet() const;
        float getStartRotation() const;
        //float getTargetRotation() const;
        float getTotalRotation() const;
        float getRotationSpeed() const;
};

#endif // ANIMATIONSTEPROTATION_HPP
