#ifndef ENUMWORLDOBJECTSTATUS_HPP
#define ENUMWORLDOBJECTSTATUS_HPP

/*
 *  A SceneNode can have several statuses in the world.
 *  If it is "ALIVE" it is in its normal state.
 *  When it is "DEAD" it gets drawn, but is not interacting with the world.
 *  If a SceneNode is "DESTROYED" it gets remvoved from the scenegraph by the next occasion.
 */

enum class WorldObjectStatus
{
    NONE,
    ALIVE,
    DEAD,
    DESTORYED,
};

#endif // ENUMWORLDOBJECTSTATUS_HPP
