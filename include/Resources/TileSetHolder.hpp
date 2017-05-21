#ifndef TILESETHOLDER_HPP
#define TILESETHOLDER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include "libs/GUI-SFML/libs/tinyxml2.h"
#include "Level/TileSet.hpp"

class TileSetHolder
{
    
    private:
        std::map<std::string, std::unique_ptr<TileSet>> m_tileSets;

    public:
        void load(const std::string &fileName);
        
        bool isTileSetExisting(const std::string &id) const;

        TileSet& getTileSet(const std::string &id) const;
        TileSet& getTileSet(const std::string &id);
};


#endif // TILESETHOLDER_HPP
