#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include "Animation/AnimationStep.hpp"

typedef std::chrono::high_resolution_clock CLOCK;

class Animation
{
    private:
        std::vector<AnimationStep> m_steps;


    public:
        Animation();

};

#endif // ANIMATION_HPP
