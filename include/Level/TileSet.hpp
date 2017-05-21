#ifndef TILESET_HPP
#define TILESET_HPP
#include <SFML/Graphics.hpp>
#include <map>
#include "libs/GUI-SFML/libs/tinyxml2.h"

class TileSet
{
    public:
        struct Tile
        {
            std::string id;
            std::string type;
            bool isCollisionOn;
            std::string identifier;
            sf::Vector2f position;
            sf::IntRect textureRect;

            Tile();
            Tile(const std::string &id, const std::string &type, bool isCollisionOn, 
                    const std::string &identifier, sf::Vector2f position, 
                    sf::IntRect textureRect);
        };
        
    private:
        std::string m_name;
        std::unique_ptr<sf::Texture> m_texture;
        std::map<std::string, Tile> m_tiles;

    public:
        TileSet();
        TileSet(const std::string &name, std::unique_ptr<sf::Texture> texture);

        const std::string& getName() const;
        sf::Texture& getTexture() const;
        const std::map<std::string, Tile>& getTiles() const;
        const Tile& getTile(const std::string &id); 

        void addTile(Tile &tile);
};

#endif // TILESET_HPP
