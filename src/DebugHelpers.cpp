#include "DebugHelpers.hpp"
#include <iostream>

std::string DebugHelpers::toString(bool value)
{
    return value ? "true" : "false";
}

std::string DebugHelpers::toString(sf::Vector2f value)
{
    return "(" + std::to_string(value.x) + "|" + std::to_string(value.y);
}
