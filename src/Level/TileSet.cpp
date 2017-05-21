#include "Level/TileSet.hpp"
#include <cassert>

TileSet::Tile::Tile()
: id{ "" }
, type{ "" }
, isCollisionOn{ false }
, identifier{ "" }
, position{ sf::Vector2f{ 0.f, 0.f } }
, textureRect{ 0, 0, 0, 0 }
{

}

TileSet::Tile::Tile(const std::string &id, const std::string &type, 
    bool isCollisionOn, const std::string &identifier, sf::Vector2f position,
    sf::IntRect textureRect)
: id{ id }
, type{ type }
, isCollisionOn{ isCollisionOn }
, identifier{ identifier }
, position{ position } 
, textureRect{ textureRect }
{

}

TileSet::TileSet()
: m_name{ "" }
, m_texture{ nullptr }
{
    
}

TileSet::TileSet(const std::string &name, std::unique_ptr<sf::Texture> texture)
: m_name{ name }
, m_texture{ std::move(texture) }
{

}

const std::string& TileSet::getName() const
{
    return m_name;
}

sf::Texture& TileSet::getTexture() const
{
    return *m_texture.get();
}

const std::map<std::string, TileSet::Tile>& TileSet::getTiles() const
{
    return m_tiles;
}

const TileSet::Tile& TileSet::getTile(const std::string &id)
{
    assert(m_tiles.find(id) != m_tiles.end());
    return m_tiles.at(id);
}

void TileSet::addTile(TileSet::Tile &tile)
{
    m_tiles.insert(std::make_pair(tile.id, tile));
}
