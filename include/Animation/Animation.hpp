#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation/AnimationStepMovement.hpp"
#include "Animation/AnimationStepRotation.hpp"

class SceneNode;

class Animation
{
    private:
        bool m_repeat;
        std::vector<AnimationStepRotation> m_rotationSteps;
        size_t m_actualRotationStep;
        float m_rotated;

        std::vector<AnimationStepMovement> m_movementSteps;
        size_t m_actualMovementStep;
        float m_moved;

        SceneNode *m_parent;

        bool m_isRotationRunning;
        bool m_isMovementRunning;
        // Update animation after the given time, instead of immediately
        float m_startAfterSeconds;
        // The time which is over since start and before the animation updating began
        float m_pastStartTime;
    public:
        Animation(SceneNode *parent, bool repeat);
        Animation(std::vector<AnimationStepRotation> rotationSteps, std::vector<AnimationStepMovement> movementSteps, SceneNode *parent, bool repeat);

        void setRotationSteps(std::vector<AnimationStepRotation> rotationSteps);
        void setMovementSteps(std::vector<AnimationStepMovement> movementSteps);
        void setParent(SceneNode *parent);
        bool isRunning() const;

        void setStartTime(float startTime);

        void start();
        void update(float dt);
        //void pause();
        void stop();

    private:
        void startRotationStep(int index);
        void startMovementStep(int index);
        void updateRotation(float dt);
        void updateMovement(float dt);


};

#endif // ANIMATION_HPP
