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
, name{ "" }
{

}

Level::SpawnPoint::SpawnPoint(int number, sf::Vector2f position, 
        const std::string &name)
: number{ number }
, position{ position }
, name{ name }
{

}

Level::Level(sf::Texture &preview, TileSet &tileSet)
: name{ "" }
, preview{ preview }
, tileSet{ tileSet }
, spawnPoint1{ nullptr }
, spawnPoint2{ nullptr }
, spawnPoint3{ nullptr }
, spawnPoint4{ nullptr }
{

}
