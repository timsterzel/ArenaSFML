#ifndef CALC_HPP
#define CALC_HPP


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
};

#include "Calc.inl"

#endif // CALC_HPP
