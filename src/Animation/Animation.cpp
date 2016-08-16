#include "Animation/Animation.hpp"
#include <iostream>
#include "Calc.hpp"
#include <cmath>
#include "Components/SceneNode.hpp"

Animation::Animation(SceneNode *parent, bool repeat)
: m_repeat{ repeat }
, m_rotationSteps{ }
, m_actualRotationStep{ 0 }
, m_rotated{ 0.f }
, m_parent{ parent }
, m_isRotationRunning{ false }
, m_isMovementRunning{ false }
, m_startAfterSeconds{ 0.f }
, m_pastStartTime{ 0.f }
{

}

Animation::Animation(std::vector<AnimationStepRotation> rotationSteps, std::vector<AnimationStepMovement> movementSteps, SceneNode *parent, bool repeat)
: m_repeat{ repeat }
, m_rotationSteps{ rotationSteps }
, m_actualRotationStep{ 0 }
, m_rotated{ 0.f }
, m_movementSteps{ movementSteps }
, m_actualMovementStep{ 0 }
, m_moved{ 0.f }
, m_parent{ parent }
, m_isRotationRunning{ false }
, m_isMovementRunning{ false }
, m_startAfterSeconds{ 0.f }
, m_pastStartTime{ 0.f }
{

}

void Animation::setRotationSteps(std::vector<AnimationStepRotation> rotationSteps)
{
    m_rotationSteps = rotationSteps;
}

void Animation::setMovementSteps(std::vector<AnimationStepMovement> movementSteps)
{
    m_movementSteps = movementSteps;
}

void Animation::setParent(SceneNode *parent)
{
    m_parent = parent;
}

bool Animation::isRunning() const
{
    return m_isRotationRunning || m_isMovementRunning;
}

void Animation::setStartTime(float startTime)
{
    m_startAfterSeconds = startTime;
}

void Animation::start()
{
    if (!isRunning())
    {
        if (m_rotationSteps.size() > 0)
        {
            m_isRotationRunning = true;
            startRotationStep(0);
        }
        if (m_movementSteps.size() > 0)
        {
            m_isMovementRunning = true;
            startMovementStep(0);
        }
    }
}

void Animation::startRotationStep(int index)
{
    m_actualRotationStep = index;
    const AnimationStepRotation rotationStep = { m_rotationSteps[index] };
    if (rotationStep.isStartRotationSet())
    {
        m_parent->setRotation(rotationStep.getStartRotation());
    }
    m_rotated = 0.f;
    std::cout << "Rotation Parent Start Step: " << m_parent->getRotation() << std::endl;
}

void Animation::startMovementStep(int index)
{
    m_actualMovementStep = index;
    const AnimationStepMovement movementStep = { m_movementSteps[index] };
    if (movementStep.isStartPositionSet())
    {
        m_parent->setPosition(movementStep.getStartPosition());
    }
    m_moved = 0.f;
}

void Animation::update(float dt)
{
    if (m_pastStartTime < m_startAfterSeconds && isRunning())
    {
        std::cout << "LOWER !!!!!!!!!!!!!!!!!";
        m_pastStartTime += dt;
        return;
    }
    if (!isRunning() || m_parent == nullptr)
    {
        return;
    }
    if (m_isRotationRunning)
    {
        updateRotation(dt);
    }
    if (m_isMovementRunning)
    {
        updateMovement(dt);
    }
}

void Animation::updateRotation(float dt)
{
    const AnimationStepRotation rotationStep = { m_rotationSteps[m_actualRotationStep] };
    // The rotation should take a spicific while, so calculate the rotation which the sceneNode make now
    float actualRotation = { rotationStep.getRotationSpeed() * dt };
    m_rotated += actualRotation;
    m_parent->rotate(actualRotation);
    if (std::fabs(m_rotated) >= std::fabs(rotationStep.getTotalRotation()))
    {
        if (m_actualRotationStep < m_rotationSteps.size() - 1)
        {
            startRotationStep(m_actualRotationStep + 1);
        }
        else
        {
            if (m_repeat)
            {
                startRotationStep(0);
            }
            else
            {
                m_isRotationRunning = false;
            }

        }
    }
}

void Animation::updateMovement(float dt)
{
    const AnimationStepMovement movementStep = { m_movementSteps[m_actualMovementStep] };
    // The movement should take a spicific while, so calculate the movement which the sceneNode make now
    sf::Vector2f actualMovement = { movementStep.getMovementSpeed() * dt };
    m_moved += Calc::getVec2Length<sf::Vector2f>(actualMovement);
    m_parent->move(actualMovement);
    if (std::fabs(m_moved) >= std::fabs(movementStep.getTotalDistance()))
    {
        if (m_actualMovementStep < m_movementSteps.size() - 1)
        {
            startMovementStep(m_actualMovementStep + 1);
        }
        else
        {
            if (m_repeat)
            {
                startMovementStep(0);
            }
            else
            {
                m_isMovementRunning = false;
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
    m_isRotationRunning = false;
    m_isMovementRunning = false;
}


/*
CLOCK::time_point timePoint2 = { CLOCK::now() };
std::chrono::duration<float> timeSpan = { timePoint2 - m_timePoint1 };
m_timePoint1 = CLOCK::now();
// Get deltaTime as float in seconds
m_dt = std::chrono::duration_cast<std::chrono::duration<float,std::ratio<1>>> (timeSpan).count();
m_fps = 1.f / m_dt;
*/
