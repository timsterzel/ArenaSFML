#include "Animation/Animation.hpp"
#include <iostream>
#include "Components/SceneNode.hpp"

Animation::Animation(SceneNode *parent, bool repeat)
: m_rotationSteps{ }
, m_actualRotationStep{ 0 }
, m_rotated{ 0.f }
, m_parent{ parent }
, m_repeat{ repeat }
, m_rotationAtStepStart { 0.f }
, m_isRunning{ false }
{

}

Animation::Animation(std::vector<AnimationStepRotation> rotationSteps, SceneNode *parent, bool repeat)
: m_rotationSteps{ rotationSteps }
, m_actualRotationStep{ 0 }
, m_rotated{ 0.f }
, m_parent{ parent }
, m_repeat{ repeat }
, m_rotationAtStepStart { 0.f }
, m_isRunning{ false }
{

}

void Animation::setRotationSteps(std::vector<AnimationStepRotation> rotationSteps)
{
    m_rotationSteps = rotationSteps;
}

void Animation::setParent(SceneNode *parent)
{
    m_parent = parent;
}

bool Animation::isRunning() const
{
    return m_isRunning;
}

void Animation::start()
{
    if (!m_isRunning)
    {
        m_isRunning = true;
        m_rotationAtStepStart = m_parent->getRotation();
        m_actualRotationStep = 0;
        m_rotated = 0.f;
    }
}

void Animation::update(float dt)
{
    if (!m_isRunning || m_parent == nullptr)
    {
        return;
    }
    const AnimationStepRotation rotationStep = { m_rotationSteps[m_actualRotationStep] };
    float targetRotation = { rotationStep.getRotation() };
    // The rotation should take a spicific while, so calculate the rotation which the sceneNode make now
    float actualRotation = { (targetRotation / rotationStep.getDuration()) * dt };
    m_rotated += actualRotation;
    std::cout << "Actual Rotation: " << actualRotation << " Target Rotation " << targetRotation << " Rotated: " << m_rotated << std::endl;

    if ((m_rotated * - 1) < (targetRotation * -1))
    {
        m_parent->rotate(actualRotation);
        std::cout << "Smaller then target " << std::endl;
    }
    else
    {
        // If we have the parent rotated more then it should, set it to the exact needed rotation
        m_parent->setRotation(m_rotationAtStepStart + targetRotation);
        m_rotationAtStepStart = m_parent->getRotation();
        if (m_actualRotationStep < m_rotationSteps.size() - 1)
        {
            m_actualRotationStep++;
        }
        else
        {
            m_actualRotationStep = 0;
            if (!m_repeat)
            {
                m_isRunning = false;
            }
        }
    }

}
/*
void pause()
{

}
*/
void Animation::stop()
{
    m_isRunning = false;
    m_actualRotationStep = 0;
}


/*
CLOCK::time_point timePoint2 = { CLOCK::now() };
std::chrono::duration<float> timeSpan = { timePoint2 - m_timePoint1 };
m_timePoint1 = CLOCK::now();
// Get deltaTime as float in seconds
m_dt = std::chrono::duration_cast<std::chrono::duration<float,std::ratio<1>>> (timeSpan).count();
m_fps = 1.f / m_dt;
*/
