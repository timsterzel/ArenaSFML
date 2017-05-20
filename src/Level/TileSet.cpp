#include "Level/TileSet.hpp"

TileSet::Tile::Tile()
: id{ 0 }
, type{ "" }
, isCollisionOn{ false }
, identifier{ "" }
, position{ sf::Vector2f{ 0.f, 0.f } }
{

}

TileSet::Tile::Tile(unsigned int id, const std::string &type, 
    bool isCollisionOn, const std::string &identifier, sf::Vector2f position)
: id{ id }
, type{ type }
, isCollisionOn{ isCollisionOn }
, identifier{ identifier }
, position{ position } 
{

}

TileSet::TileSet()
: m_name{ "" }
, m_texture{ nullptr }
{
    
}

TileSet::TileSet(const std::string &name, std::unique_ptr<sf::Texture> texture,
    std::vector<Tile> tiles)
: m_name{ name }
, m_texture{ std::move(texture) }
, m_tiles{ tiles }
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

const std::vector<TileSet::Tile>& TileSet::getTiles() const
{
    return m_tiles;
}
