#ifndef LEVEL_HPP
#define LEVEL_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Level/TileSet.hpp"

struct Level
{
        struct TileData
        {
            std::string id;
            sf::Vector2f position;

            TileData();
            TileData(const std::string &id, sf::Vector2f position);
        };
        
        struct SpawnPoint
        {
            int number;
            sf::Vector2f position;
            std::string name;
            
            SpawnPoint();
            SpawnPoint(int number, sf::Vector2f position, const std::string &name);
        };

        std::string name;
        sf::Texture preview;
        TileSet &tileSet;
        std::vector<TileData> tiles;
        std::unique_ptr<SpawnPoint> spawnPoint1;
        std::unique_ptr<SpawnPoint> spawnPoint2;
        std::unique_ptr<SpawnPoint> spawnPoint3;
        std::unique_ptr<SpawnPoint> spawnPoint4;
        
        Level(sf::Texture &preview, TileSet &tileSet);
};

#endif // LEVEL_HPP
