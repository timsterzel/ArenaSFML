#include <cmath>

#define PI 3.14159265

template<typename T, typename U>
float Calc::getVec2Scalar(const T vec1, const U vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

template<typename T>
float Calc::getVec2Length(const T vec)
{
    return std::sqrt( std::pow(vec.x, 2) + std::pow(vec.y, 2));
}

template<typename T, typename U>
float Calc::getVec2Angle(const T vec1, const U vec2)
{
    return std::acos( getVec2Scalar<T, U>(vec1, vec2) / ( getVec2Length<T>(vec1) *  getVec2Length<U>(vec2) ) );
}

template<typename T, typename U, typename V>
sf::Vector2f Calc::getVec2TripleProduct(const T VecA, const U VecB, const V VecC)
{
    const float ScaAC = Calc::getVec2Scalar<T, V>(VecA, VecC);
    const float ScaBC = Calc::getVec2Scalar<U, V>(VecB, VecC);

    const float X = VecB.x * ScaAC - VecA.x * ScaBC;
    const float Y = VecB.y * ScaAC - VecA.y * ScaBC;

    return { X, Y };
}

template<typename T>
sf::Vector2f Calc::getVec2PerpendicularLeft(const T Vec)
{
    return sf::Vector2f(Vec.y, -Vec.x);
}

template<typename T>
sf::Vector2f Calc::getVec2PerpendicularRight(const T Vec)
{
    return sf::Vector2f(-Vec.y, Vec.x);
}

template<typename T>
sf::Vector2f Calc::normalizeVec2(const T Vec)
{
    const float Length = { getVec2Length<T>(Vec) };
    return { Vec.x / Length, Vec.y / Length };
}
