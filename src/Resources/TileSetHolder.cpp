#include "Resources/TileSetHolder.hpp"
#include <cassert>

void TileSetHolder::load(const std::string &id, const std::string &fileName)
{
    tinyxml2::XMLDocument document;
    if (document.LoadFile(fileName.c_str()) != tinyxml2::XML_SUCCESS)
    {
        std::cout << "Error by loading tmx file. File path: " << fileName << std::endl;
        return;
    }
    tinyxml2::XMLElement *sceneEl{ document.FirstChildElement("tileset") };    


    //rectMap.insert( { getIdentifier(line), getIntRect(line)});
    //m_resourceMap.insert( { id, rectMap } );
}

sf::IntRect TileSetHolder::getRectData(const std::string &id) const
{
    assert(m_rectMap.find(id) != m_rectMap.end());
    return m_rectMap.at(id);
}

sf::IntRect TileSetHolder::getRectData(const std::string &id)
{
    assert(m_rectMap.find(id) != m_rectMap.end());
    return m_rectMap.at(id);
}

