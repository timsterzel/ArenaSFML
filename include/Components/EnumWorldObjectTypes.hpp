#ifndef ENUMWORLDOBJECTTYPE_HPP
#define ENUMWORLDOBJECTTYPE_HPP

enum WorldObjectTypes
{
    NONE = 0,
    PLAYER = 1 << 1,
    ENEMY = 1 << 2,
    WARRIOR = 1 << 3,
    WEAPON = 1 << 4,
    SHIELD = 1 << 5,
    // TMP
    PLAYER_TWO = 1 << 5
};

#endif // ENUMWORLDOBJECTTYPE
