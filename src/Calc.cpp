#include "Calc.hpp"
#include <cmath>

#define PI 3.14159265


float Calc::radToDeg(float rad)
{
    return rad * ( 180.f / PI);
}

float Calc::degToRad(float deg)
{
    return deg * (PI / 180.f);
}

/*
 * Rotation around origin:
 *           rotation matrix      P
 * ( x' ) = ( cos a  -sin a ) * ( x ) = cos a * x - sin a * y
 * ( y' )   ( sin a   cos a )   ( y ) = sin a * x + cos a * y
 * Our Coordinate system has other axes (reversed y Axes)
 * So the rotation matrix is different: *
 * ( x' ) = ( cos a   sin a ) * ( x ) = cos a * x + sin a * y
 * ( y' )   (-sin a   cos a )	( y ) =-sin a * x + cos a * y
 *
 * Rotation around specific Point:
 * The Point we want to rotate is called P and the point we
 * rotate around is called T.
 *                                       ->          ->
 *           rotation matrix     Vector: TP  Vector: OT
 * ( x' ) = ( cos a  -sin a ) * ( xp - xt) + ( xt )
 * ( y' )   ( sin a   cos a )   ( yp - yt)   ( yt )
 * ==>
 * x' = (cos a * (xp - xt) - sin a * (yp - yt)) + xt
 * y' = (sin a * (xp - xt) + cos a * (yp - yt)) + yt
 * In our coordinate system with the custom rotation matrix:
 * x' = ( cos a * (xp - xt) + sin a * (yp - yt)) + xt
 * y' = (-sin a * (xp - xt) + cos a * (yp - yt)) + yt
 *
 */
sf::Vector2f Calc::rotatePointAround(const sf::Vector2f Point, const sf::Vector2f TargetPoint, const float AngleDegree)
{
	// First we need the angle in radians instead if degrees
	const float Angle = ( PI / 180) * AngleDegree;
	const float Xp = Point.x;
	const float Yp = Point.y;
	const float Xt = TargetPoint.x;
	const float Yt = TargetPoint.y;
	// Rotate the Point
	const float Xnew = ( ( std::cos(Angle) * (Xp - Xt) + std::sin(Angle) * (Yp - Yt) ) + Xt );
	const float Ynew = ( (-std::sin(Angle) * (Xp - Xt) + std::cos(Angle) * (Yp - Yt) ) + Yt );

    return { Xnew, Ynew };
}

float Calc::clamp(const float Value, const float MinValue, const float MaxValue)
{
    return std::max(MinValue, std::min(MaxValue, Value));
}


sf::Vector2f Calc::degAngleToDirectionVector(float angle)
{
    float angleRad{ degToRad(angle) };
    float x{ std::cos(angleRad) };
    float y{ std::sin(angleRad) };
    return { x, y };
}
