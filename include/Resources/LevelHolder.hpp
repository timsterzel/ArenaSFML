#ifndef LEVELHOLDER_HPP
#define LEVELHOLDER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include "Level/Level.hpp"
#include "libs/GUI-SFML/libs/tinyxml2.h"
#include "Resources/TileSetHolder.hpp"

class LevelHolder
{
    
    private:
        std::vector<std::unique_ptr<Level>> m_levels;
    public:
        void load(const std::string &fileName, TileSetHolder &tileSetHolder);

        std::vector<std::unique_ptr<Level>>& getLevels();
};


#endif // !LEVELHOLDER_HPP
