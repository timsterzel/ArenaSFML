#ifndef TILESET_HPP
#define TILESET_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "libs/GUI-SFML/libs/tinyxml2.h"

class TileSet
{
    public:
        struct Tile
        {
            unsigned int id;
            std::string type;
            bool isCollisionOn;
            std::string identifier;
            sf::Vector2f position;

            Tile();
            Tile(unsigned int id, const std::string &type, bool isCollisionOn, 
                    const std::string &identifier, sf::Vector2f position);
        };
        
    private:
        std::string m_name;
        std::unique_ptr<sf::Texture> m_texture;
        std::vector<Tile> m_tiles;

    public:
        TileSet();
        TileSet(const std::string &name, std::unique_ptr<sf::Texture> texture,
                std::vector<Tile> tiles);

        const std::string& getName() const;
        sf::Texture& getTexture() const;
        const std::vector<Tile>& getTiles() const;
};

#endif // TILESET_HPP
