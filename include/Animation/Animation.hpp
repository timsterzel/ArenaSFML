#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include "Animation/AnimationStepRotation.hpp"

typedef std::chrono::high_resolution_clock CLOCK;

class Animation
{
    private:
        std::vector<AnimationStepRotation> m_rotationSteps;
        int m_actualRotationStep;

    public:
        explicit Animation(std::vector<AnimationStepRotation> rotationSteps);


};

#endif // ANIMATION_HPP
