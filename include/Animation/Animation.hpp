#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include "Animation/AnimationStepRotation.hpp"

class SceneNode;

typedef std::chrono::high_resolution_clock CLOCK;

class Animation
{
    private:
        bool m_repeat;
        std::vector<AnimationStepRotation> m_rotationSteps;
        int m_actualRotationStep;
        float m_rotated;

        SceneNode *m_parent;
        // The rotation of the parent before starting rotating when a new step starts
        float m_rotationAtStepStart;

        bool m_isRunning;

    public:
        Animation(SceneNode *parent, bool repeat);
        Animation(std::vector<AnimationStepRotation> rotationSteps, SceneNode *parent, bool repeat);

        void setRotationSteps(std::vector<AnimationStepRotation> rotationSteps);
        void setParent(SceneNode *parent);
        bool isRunning() const;

        void start();
        void update(float dt);
        //void pause();
        void stop();
};

#endif // ANIMATION_HPP
