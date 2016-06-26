#ifndef CALC_HPP
#define CALC_HPP
#include <SFML/Graphics.hpp>

class Calc
{
    private:

    public:

        static float radToDeg(float rad);
        static float DegToRad(float deg);

        template<typename T, typename U>
        static float getVec2Scalar(const T vec1, const U vec2);

        template<typename T>
        static float getVec2Length(const T vec);

        template<typename T, typename U>
        static float getVec2Angle(const T vec1, const U vec2);

        template<typename T, typename U, typename V>
        static sf::Vector2f getVec2TripleProduct(const T VecA, const U VecB, const V VecC);

        template<typename T>
        static sf::Vector2f getVec2PerpendicularLeft(const T Vec);

        template<typename T>
        static sf::Vector2f getVec2PerpendicularRight(const T Vec);

        template<typename T>
        static sf::Vector2f normalizeVec2(const T Vec);

        static sf::Vector2f rotatePointAround(const sf::Vector2f Point, const sf::Vector2f TargetPoint, const float AngleDegree);
        static float clamp(const float Value, const float MinValue, const float MaxValue);


};

#include "Calc.inl"

#endif // CALC_HPP
