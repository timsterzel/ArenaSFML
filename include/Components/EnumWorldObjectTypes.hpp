#ifndef ENUMWORLDOBJECTTYPE_HPP
#define ENUMWORLDOBJECTTYPE_HPP

enum WorldObjectTypes : unsigned int
{
    NONE = 0,
    PLAYER_1 = 1 << 1,
    PLAYER_2 = 1 << 2,
    ENEMY = 1 << 3,
    WEAPON = 1 << 4,
    SHIELD = 1 << 5,
    WARRIOR = 1 << 6,
    KNIGHT = 1 << 7,
    RUNNER = 1 << 8,
    WIZARD = 1 << 9,
    PROJECTILE = 1 << 10,
    LEVEL = 1 << 11,
};

#endif // ENUMWORLDOBJECTTYPE
