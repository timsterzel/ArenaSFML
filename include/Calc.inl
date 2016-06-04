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
