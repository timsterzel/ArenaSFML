#ifndef ANIMATIONSTEP_HPP
#define ANIMATIONSTEP_HPP
#include <SFML/Graphics.hpp>

class AnimationStep
{
    private:
        // The duration of the animation in seconds
        float m_duration;

    public:
        AnimationStep();
        explicit AnimationStep(float duration);
};

#endif // ANIMATIONSTEP_HPP
