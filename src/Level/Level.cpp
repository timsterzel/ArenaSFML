#include "Level/Level.hpp"

Level::TileData::TileData()
: id{ "" }
, position{ 0.f, 0.f }
{

}

Level::TileData::TileData(const std::string &id, sf::Vector2f position)
: id{ id }
, position{ position }
{

}

Level::SpawnPoint::SpawnPoint()
: number{ 0 }
, position{ 0.f, 0.f }
{

}

Level::SpawnPoint::SpawnPoint(int number, sf::Vector2f position)
: number{ number }
, position{ position }
{

}

Level::Level()
: name{ "" }
, spawnPoint1{ nullptr }
, spawnPoint2{ nullptr }
{

}
