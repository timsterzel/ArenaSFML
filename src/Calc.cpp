#include "Calc.hpp"

#define PI 3.14159265


float Calc::radToDeg(float rad)
{
    return rad * ( 180.f / PI);
}

float Calc::DegToRad(float deg)
{
    return deg * (PI / 180.f);
}
