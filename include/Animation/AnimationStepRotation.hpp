#ifndef ANIMATIONSTEPROTATION_HPP
#define ANIMATIONSTEPROTATION_HPP
#include <SFML/Graphics.hpp>
#include "Animation/AnimationStep.hpp"

class AnimationStepRotation : public AnimationStep
{
    private:
        // If a start rotation is set the parent can get rotated to this position at the beginning,
        // else the animation is relative to parents rotation
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
