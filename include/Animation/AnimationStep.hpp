#ifndef ANIMATIONSTEP_HPP
#define ANIMATIONSTEP_HPP
#include <SFML/Graphics.hpp>

class AnimationStep
{
    protected:
        // The duration of the animation in seconds
        float m_duration;

    public:
        AnimationStep();
        explicit AnimationStep(float duration);

        float getDuration() const;
};

#endif // ANIMATIONSTEP_HPP
