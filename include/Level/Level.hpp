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
            
            SpawnPoint();
            SpawnPoint(int number, sf::Vector2f position);
        };

        std::string name;
        std::vector<TileData> tiles;
        std::unique_ptr<SpawnPoint> spawnPoint1;
        std::unique_ptr<SpawnPoint> spawnPoint2;
        
        Level();
};

#endif // LEVEL_HPP
