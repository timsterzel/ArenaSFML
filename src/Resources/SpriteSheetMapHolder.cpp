#include "Resources/SpriteSheetMapHolder.hpp"
#include <fstream>
#include <sstream>
#include <cassert>

void SpriteSheetMapHolder::load(const std::string &id, const std::string &fileName)
{
    std::ifstream file(fileName, std::ios_base::in);
    if (!file)
    {
        std::cout << "Could not open file: " << fileName << std::endl;
        return;
    }
    std::map<std::string, sf::IntRect> rectMap;
    std::string line;
    while(std::getline(file, line))
    {
        //std::cout << "line: " << line << " Identifier: '" << getIdentifier(line) << "'" << std::endl;
        rectMap.insert( { getIdentifier(line), getIntRect(line)});
    }
    file.close();
    m_resourceMap.insert( { id, rectMap } );
}

/*
std::map<std::string, sf::IntRect> SpriteSheetMapHolder::get(const Textures &id) const
{
    return m_resourceMap[id];
}
*/

sf::IntRect SpriteSheetMapHolder::getRectData(const std::string &id, const std::string &identefier) const
{
    assert(m_resourceMap.find(id) != m_resourceMap.end());
    assert(m_resourceMap.at(id).find(identefier) != m_resourceMap.at(id).end());
    return m_resourceMap.at(id).at(identefier);
}

sf::IntRect SpriteSheetMapHolder::getRectData(const std::string &id, const std::string &identefier)
{
    assert(m_resourceMap.find(id) != m_resourceMap.end());
    assert(m_resourceMap.at(id).find(identefier) != m_resourceMap.at(id).end());
    return m_resourceMap.at(id).at(identefier);
}

/*
void SpriteSheetMapLoader::loadRectData(std::string fileName)
{
    std::ifstream file(fileName, std::ios_base::in);
    if (!file)
    {
        std::cout << "Could not open file: " << fileName << std::endl;
        return { };
    }
    std::map<std::string, sf::IntRect> rectMap;
    std::string line;
    while(std::getline(file, line))
    {
        //std::cout << "line: " << line << " Identifier: '" << getIdentifier(line) << "'" << std::endl;
        rectMap.insert( { getIdentifier(line), getIntRect(line)});
    }
    file.close();
    return rectMap;
}
*/

std::string SpriteSheetMapHolder::getIdentifier(const std::string &line) const
{
    // The identifier comes bevor the '=' and habe a white space after the identifier.
    // So we use line.find('=') -1, so we remove the white space, too.
    std::string identifier = line.substr(0, line.find('=') - 1);
    return identifier;
}

sf::IntRect SpriteSheetMapHolder::getIntRect(const std::string &line) const
{
    // Only get the numbers, which come after the '='
    std::string numbers = line.substr(line.find('=') + 1, line.length() + 1);
    std::istringstream is (numbers);
    // We now that the given bound have 4 values, so we can direct load the 4 int values from the string
    int a, b , c , d;
    if (!(is >> a >> b >> c >> d))
    {
        std::cout << "Cannot load int rect from file, wrong format?" << std::endl;
    }
    //std::cout << " a: " << a << " b: " << b << " c: " << c << " d: " << d << std::endl;
    return { a, b , c, d };
}

