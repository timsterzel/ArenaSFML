#ifndef ENUMWORLDOBJECTTYPE_HPP
#define ENUMWORLDOBJECTTYPE_HPP

enum WorldObjectTypes
{
    NONE = 0,
    PLAYER = 1 << 1,
    ENEMY = 1 << 2,
    WEAPON = 1 << 3,
    SHIELD = 1 << 4,
    WARRIOR = 1 << 5,
    KNIGHT = 1 << 6,
    RUNNER = 1 << 7,
    WIZARD = 1 << 8,
    PROJECTILE = 1 << 9,
    LEVEL = 1 << 10,
    // TMP
    PLAYER_TWO = 1 << 11
};

#endif // ENUMWORLDOBJECTTYPE
